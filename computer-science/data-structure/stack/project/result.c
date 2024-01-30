#include "result.h"

evalStackPointer evalTop = NULL;

// 스택 언더플로우 처리
void resultStackEmpty()
{
    fprintf(stderr, "[Result] Stack is empty cannot delete elements\n");
    exit(1);
}

// 삽입
void evalPush(int *intEval, double *doubleEval)
{
    // 스택에 새로 삽입할 값을 저장할 메모리 할당
    evalStackPointer newNode;
    newNode = (evalStackPointer)malloc(sizeof(*newNode));
    if(newNode == NULL){
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    
    // 새로 생성한 원소 초기화
    newNode->intEval = intEval;
    newNode->doubleEval = doubleEval;
    newNode->link = evalTop;

    // 새로 생성한 원소를 top으로 지정
    evalTop = newNode;
}

// 삭제
int evalPop(int **intEval, double **doubleEval)
{
    evalStackPointer temp = evalTop;

    // 빈 스택이면 삭제 불가능
    if(!temp)
        resultStackEmpty();
    
    evalTop = evalTop->link;

    // 실수 타입일 때
    if(temp->intEval == NULL){
        *intEval = NULL;
        *doubleEval = temp->doubleEval;

        free(temp);

        return DOUBLE;
    }
    // 정수 타입일 때
    else{
        *intEval = temp->intEval;
        *doubleEval = NULL;

        free(temp);

        return INTEGER;
    }
}

// 수식의 결과값을 가져옴
int getResult(void **result)
{
    Token token;
    char operand[MAX_EXPR_SIZE];
    char symbol;
    int *intResPtr, intOp1, intOp2;
    double *doubleResPtr, doubleOp1, doubleOp2;
    int n = 0, i = 0;
    bool isDouble = false;
    bool isNegative = false;
    bool hasDivide = false;
    bool hasMod = false;

    // 후위표기법의 식에서 순방향으로 토큰을 하나씩 가져옴
    for(token = getToken(postExpr, &symbol, n++); token != EOS; token = getToken(postExpr, &symbol, n++)){
        if(token == SPACE)
            continue;
        // 피연산자인 경우: 스택에 저장
        else if(token == NUM){
            operand[i++] = symbol; 
            
            while((token = getToken(postExpr, &symbol, n++)) != SPACE){
                if(token == DOT)
                    isDouble = true;
                operand[i++] = symbol;
            }
            operand[i] = '\0';


            // 피연산자가 실수인 경우
            if(isDouble){
                doubleResPtr = (double *)malloc(sizeof(double));

                // 문자열을 실수로 변경 -> 음수인 경우, 음수로 저장
                *doubleResPtr = strtod(operand, NULL);
                if(isNegative)
                    *doubleResPtr = -(*doubleResPtr);

                evalPush(NULL, doubleResPtr);
            }
            // 피연산자가 정수인 경우
            else{
                intResPtr = (int *)malloc(sizeof(int));
                
                // 문자열을 정수로 변경 -> 음수인 경우, 음수로 저장
                *intResPtr = atoi(operand);
                if(isNegative)
                    *intResPtr = -(*intResPtr);

                evalPush(intResPtr, NULL);
            }

            isDouble = false;
            isNegative = false;

            i = 0;
        }
        // 연산자인 경우: 스택 내 위에서 첫 번째, 두 번째 원소에 대해 연산 진행
        else{   
            // -가 입력된 경우 연산자인지 음수인지 구분 필요
            // 음수인 경우
            if(token == MINUS){
                if((token = getToken(postExpr, &symbol, n)) != SPACE && token != EOS){
                    isNegative = true;
                    continue;
                }
                else{
                    token = MINUS;
                    symbol = '-';
                }
            }

            if(token == DIVIDE)
                hasDivide = true;
            if(token == MOD)
                hasMod = true;

            // 두 개의 피연산자 중 뒤의 피연산자가 integer일때
            if(evalPop(&intResPtr, &doubleResPtr) == INTEGER){
                intOp2 = *intResPtr;
                //free(intResPtr);

                // 0으로 나누는 경우: 스택을 모두 비우고, 에러 반환
                if((hasDivide || hasMod) && intOp2 == 0){
                    while(evalTop != NULL)
                        evalPop(&intResPtr, &doubleResPtr);
                        
                    return ERROR_ARITHMETIC;
                }

                // 정수 피연산자와 정수 피연산자
                if(evalPop(&intResPtr, &doubleResPtr) == INTEGER){
                    intOp1 = *intResPtr;
                    //free(intResPtr);

                    switch (token){
                        case PLUS:
                            *intResPtr = intOp1 + intOp2;
                            evalPush(intResPtr, NULL);
                            break;

                        case MINUS:
                            *intResPtr = intOp1 - intOp2;
                            evalPush(intResPtr, NULL);
                            break;

                        case TIMES:
                            *intResPtr = intOp1 * intOp2;
                            evalPush(intResPtr, NULL);
                            break;

                        case DIVIDE:
                            *intResPtr = intOp1 / intOp2;
                            evalPush(intResPtr, NULL);
                            break;

                        case MOD:
                            *intResPtr = intOp1 % intOp2;
                            evalPush(intResPtr, NULL);
                            break;

                        case POWER:
                            *intResPtr = (int)pow(intOp1, intOp2);
                            evalPush(intResPtr, NULL);
                            break;

                        default: 
                            fprintf(stderr, "getResult(): wrong operator\n");
                            exit(1);
                    }

                }
                // 실수 피연산자와 정수 피연산자
                else{
                    doubleOp1 = *doubleResPtr;

                    switch (token){
                        case PLUS:
                            *doubleResPtr = doubleOp1 + intOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case MINUS:
                            *doubleResPtr = doubleOp1 - intOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case TIMES:
                            *doubleResPtr = doubleOp1 * intOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case DIVIDE:
                            *doubleResPtr = doubleOp1 / intOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case MOD:
                            *doubleResPtr = fmod(doubleOp1, intOp2);
                            evalPush(NULL, doubleResPtr);
                            break;

                        case POWER:
                            *doubleResPtr = pow(doubleOp1, intOp2);
                            evalPush(NULL, doubleResPtr);
                            break;

                        default: 
                            fprintf(stderr, "getResult(): wrong operator\n");
                            exit(1);
                    }

                }
            }
            // 두 개의 피연산자 중 뒤의 피연산자가 double일 때
            else{
                doubleOp2 = *doubleResPtr;
                //free(doubleResPtr);
                
                // 0으로 나누는 경우: 스택을 모두 비우고, 에러 반환
                if((hasDivide || hasMod) && doubleOp2 == 0.){
                    while(evalTop != NULL)
                        evalPop(&intResPtr, &doubleResPtr);
                        
                    return ERROR_ARITHMETIC;
                }

                // 정수 피연산자와 실수 피연산자
                if(evalPop(&intResPtr, &doubleResPtr) == INTEGER){
                    intOp1 = *intResPtr;
                    //free(intResPtr);

                    doubleResPtr = (double *)malloc(sizeof(double));

                    switch (token){
                        case PLUS:
                            *doubleResPtr = intOp1 + doubleOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case MINUS:
                            *doubleResPtr = intOp1 - doubleOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case TIMES:
                            *doubleResPtr = intOp1 * doubleOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case DIVIDE:
                            *doubleResPtr = intOp1 / doubleOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case MOD:
                            *doubleResPtr = fmod(intOp1, doubleOp2);
                            evalPush(NULL, doubleResPtr);
                            break;

                        case POWER:
                            *doubleResPtr = pow(intOp1, doubleOp2);
                            evalPush(NULL, doubleResPtr);
                            break;
                        
                        default: 
                            fprintf(stderr, "getResult(): wrong operator\n");
                            exit(1);
                    }

                }
                // 실수 피연산자와 실수 피연산자
                else{
                    doubleOp1 = *doubleResPtr;


                    switch (token){
                        case PLUS:
                            *doubleResPtr = doubleOp1 + doubleOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case MINUS:
                            *doubleResPtr = doubleOp1 - doubleOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case TIMES:
                            *doubleResPtr = doubleOp1 * doubleOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case DIVIDE:
                            *doubleResPtr = doubleOp1 / doubleOp2;
                            evalPush(NULL, doubleResPtr);
                            break;

                        case MOD:
                            *doubleResPtr = fmod(doubleOp1, doubleOp2);
                            evalPush(NULL, doubleResPtr);
                            break;

                        case POWER:
                            *doubleResPtr = pow(doubleOp1, doubleOp2);
                            evalPush(NULL, doubleResPtr);
                            break;
                        
                        default: 
                            fprintf(stderr, "getResult(): wrong operator\n");
                            exit(1);
                    }
 
                } // 실수 피연산자와 실수 피연산자인 경우
            } // 두 개의 피연산자 중 뒤의 피연산자가 실수인 경우

            hasDivide = false;
            hasMod = false;
        } // token이 연산자인 경우

    } // token을 가져와서 검사하는 반복문

    // 연산이 끝났을 때, 마지막 스택에 남아있는 원소가 결과값
    if(evalPop(&intResPtr, &doubleResPtr) == INTEGER){
        *result = intResPtr;
        return INTEGER;
    }
    else{
        *result = doubleResPtr;
        return DOUBLE;
    }
}

// 수식의 계산 결과 출력
void printResult(ExprType exprType)
{
    void *result; // 결과값을 가리킬 포인터
    int resultType;

    if(exprType == ALL)
        printf("result: %s\n", inExpr);

    else{
        // 만약 0으로 나누려고 할 때에는 에러 문구 출력
        if((resultType = getResult(&result)) == ERROR_ARITHMETIC)
            printError(ERROR_ARITHMETIC);

        else{
            if(resultType == INTEGER)
                printf("result: %d\n", *(int *)result);
            else
                printf("result: %f\n", *(double *)result);

            free(result);
        }
    }
}
