#include "convert.h"

StackPointer top = NULL;
ToInfixStackPointer toInfixTop = NULL;
int exprLength = 0;

// 스택 언더플로우 처리
void stackEmpty(const char *str)
{
    fprintf(stderr, "[Convert: %s] Stack is empty cannot delete elements\n", str);
    exit(1);
}

// 삽입
void push(Token token)
{
    // 스택에 새로 삽입할 값을 저장할 메모리 할당
    StackPointer newNode;
    newNode = (StackPointer)malloc(sizeof(*newNode));
    if(newNode == NULL){
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    // 새로 생성한 원소 초기화
    newNode->token = token;
    newNode->link = top;

    // 새로 생성한 원소를 top으로 지정
    top = newNode;
}

// 삭제
void pop(Token *token)
{
    StackPointer temp = top;

    // 빈 스택이면 삭제 불가능
    if(!temp)
        stackEmpty("Stack");
    
    *token = temp->token; 
    top = temp->link;

    free(temp); 
}

// 삽입
void toInfixPush(Token token, char *midExpr)
{
    ToInfixStackPointer newNode;
    newNode = (ToInfixStackPointer)malloc(sizeof(*newNode));
    if(newNode == NULL){
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    // 새로 생성한 원소 초기화
    newNode->token = token;
    strcpy(newNode->midExpr, midExpr);
    newNode->link = toInfixTop;

    // 새로 생성한 원소를 top으로 지정
    toInfixTop = newNode;
}

// 삭제
void toInfixPop(char *midExpr)
{
    ToInfixStackPointer temp = toInfixTop;

    // 빈 스택이면 삭제 불가능
    if(!temp)
        stackEmpty("ToInfixStackPointer");
    
    strcpy(midExpr, temp->midExpr);
    toInfixTop = temp->link;

    free(temp); 
}

// 스택에 있는 연산식의 우선순위가 token보다 낮을 경우 괄호 처리
void modifyExpr(Token token)
{
    ToInfixStackPointer temp = toInfixTop;
    char tempMidExpr[MAX_EXPR_SIZE];
    int len = 0;

    // 스택의 모든 원소를 검사하고, 괄호 처리가 필요한 경우 괄호처리
    while(temp != NULL){
        // 배열 내 모든 원소를 널문자로 초기화해주었기 때문에, 따로 널문자를 신경 쓸 필요가 없음
        memset(tempMidExpr, 0, sizeof(tempMidExpr));

        // 이전에 진행했던 연산보다 우선순위가 높은 연산자가 들어올 경우, 괄호 처리
        // 연산이 없었던 경우는 무시
        // 이미 괄호가 추가된 수식에는 괄호 추가 하지 않음
        if(temp->token != NUM && isp[temp->token] <= icp[token]){
            len = strlen(temp->midExpr);
            if(temp->midExpr[0] != '(' || temp->midExpr[len - 1] != ')'){
                // 괄호 추가
                tempMidExpr[0] = '(';
                tempMidExpr[1] = ' ';
                strcat(tempMidExpr, temp->midExpr);

                // temp->midExpr의 널문자 뒤에는 모두 널문자로 초기화되어있다는 보장이 없음
                len = strlen(tempMidExpr);
                tempMidExpr[len] = ' ';
                tempMidExpr[len + 1] = ')';
                tempMidExpr[len + 2] = '\0';

                // 괄호를 추가한 수식으로 변경
                strcpy(temp->midExpr, tempMidExpr);
            }
        }

        temp = temp->link;
        len = 0;
    }
}

// 입력받은 수식 변환
ExprType convertExpr(char *expr)
{
    // 입력받은 수식의 종류(전위/중위/후위) 판단
    ExprType exprType = recongnizeExpr(expr);

    // 전위/중위/후위표기법의 식으로 변환
    switch (exprType){
        // 전위표기법의 식이 입력된 경우
        case PREFIX:
            strcpy(preExpr, expr); // 최종 전위표기법 식에 저장
            exprLength = strlen(preExpr); // 전위를 중위로 바꿀 때에는 역순으로 읽기 때문에 기존 식의 길이 알아야함
            prefixToInfix(); // 전위 -> 중위
            infixToPostfix(); // 중위 -> 후위
            break;
        
        // 중위표기법의 식이 입력된 경우
        case INFIX: 
            strcpy(inExpr, expr); // 최종 중위표기법 식에 저장
            exprLength = strlen(inExpr); // 중위를 전위로 바꿀 때에는 역순으로 읽기 때문에 기존 식의 길이 알아야함
            infixToPrefix(); // 중위 -> 전위
            infixToPostfix(); // 중위 -> 후위
            break;

        // 후위표기법의 식이 입력된 경우
        case POSTFIX:
            strcpy(postExpr, expr); // 최종 후위표기법 식에 저장
            postfixToInfix(); // 후위 -> 중위
            exprLength = strlen(inExpr); // 중위를 전위로 바꿀 때에는 역순으로 읽기 때문에 기존 식의 길이 알아야함
            infixToPrefix(); // 중위 -> 전위
            break;

        // 모든 표기법에 해당하는 경우
        case ALL:
            strcpy(preExpr, expr); // 최종 전위표기법 식에 저장
            strcpy(inExpr, expr); // 최종 중위표기법 식에 저장
            strcpy(postExpr, expr); // 최종 후휘표기법 식에 저장
            break;
    }

    return exprType;
}

// 중위표기법 -> 후위표기법
void infixToPostfix()
{
    char symbol;
    Token token, popToken;
    int inN = 0; // 현재 읽고 있는 수식의 위치(인덱스)
    int postN = 0; // 현재 저장하고 있는 최종 수식의 위치(인덱스)
    
    push(EOS); // EOS는 모든 연산자들보다 우선순위가 낮음 -> 스택의 가장 밑에 깔려 있음

    // 중위표기식(infixExpr)에서 토큰을 하나씩 가져오기
    // 입력된 문자열(expr)의 개수만큼 반복 ('\0'은 제외됨)
    for(token = getToken(inExpr, &symbol, inN++); token != EOS; token = getToken(inExpr, &symbol, inN++)){

        // 공백이 입력된 경우 무시
        if(token == SPACE)
            continue;
        // 피연산자는 스택을 거치지 않고 바로 최종 식에 저장
        else if(token == NUM){
            *(postExpr + (postN++)) = symbol;

            while((token = getToken(inExpr, &symbol, inN++)) != SPACE){
                if(token == EOS)
                    break;
                else
                    *(postExpr + (postN++)) = symbol;
            }

            saveToken(postExpr, SPACE, postN++); // 연산자와 피연산자 간에 공백 있어야 함
        }
        // 닫힌 괄호는 열린 괄호가 나올때까지 stack내 값 삭제
        // 닫힌 괄호와 열린 괄호는 최종 식에 저장하지 않음
        // token에는 삭제된 토큰이 저장됨
        else if(token == RPAREN){

            while(top->token != LPAREN){
                pop(&popToken);
                saveToken(postExpr, popToken, postN++); // 최종 식에 토큰에 해당하는 연산자 저장
                saveToken(postExpr, SPACE, postN++); // 연산자 간에 공백 있어야 함
            }
            pop(&popToken); // 열린 괄호도 삭제
        }
        // 열린 괄호를 포함한 그 외의 모든 연산자
        // 연산자의 우선순위가 높을 수록(값이 클 수록) 스택의 위쪽에 위치함
        // 새로 들어오는 연산자의 우선순위가 top의 우선순위보다 낮다면, top 삭제
        else{
            // -가 입력된 경우에는 연산자인지 음수인지 구분 필요
            // 연산자가 아닌 음수인 경우
            if(token == MINUS){
                if(getToken(inExpr, &symbol, inN) != SPACE){
                    saveToken(postExpr, token, postN++); // -를 최종 식에 저장
                    continue;
                }
            }

            while(isp[top->token] >= icp[token]){
                pop(&popToken);
                saveToken(postExpr, popToken, postN++);
                saveToken(postExpr, SPACE, postN++); // 연산자 간에 공백 있어야 함
            }
            push(token); // 새로 들어온 연산자를 스택에 저장
        }
    }

    // 스택에 남아있는 연산자들 모두 최종식에 저장
    for(pop(&popToken); popToken != EOS; pop(&popToken)){
        saveToken(postExpr, popToken, postN++);
        saveToken(postExpr, SPACE, postN++); // 연산자 간에 공백 있어야 함
    }

    // 식의 마지막은 공백으로 끝나므로, 널문자 처리
    postExpr[--postN] = '\0';

}

// 중위표기법 -> 전위표기법
void infixToPrefix()
{
    char symbol;
    Token token, popToken;
    int inN = exprLength - 1; // 현재 읽고 있는 수식의 위치(인덱스)
    int preN = MAX_EXPR_SIZE - 1; // 현재 저장하고 있는 최종 수식의 위치(인덱스)
    
    push(EOS); // EOS는 모든 연산자들보다 우선순위가 낮음 -> 스택의 가장 밑에 깔려 있음
    *(preExpr + (preN--)) = '\0'; // 마지막 문자는 널문자여야함

    for(token = getToken(inExpr, &symbol, inN--); inN + 1 >= 0; token = getToken(inExpr, &symbol, inN--)){
        // 공백이 입력된 경우 무시
        if(token == SPACE)
            continue;
        // 피연산자는 스택을 거치지 않고 바로 최종 식에 역순으로 저장
        else if(token == NUM){
            *(preExpr + (preN--)) = symbol;

            // 음수인 경우도 저장됨
            while((token = getToken(inExpr, &symbol, inN--)) != SPACE){
                if(inN + 1 < 0)
                    break;
                if(token == MINUS)
                    saveToken(preExpr, MINUS, preN--);
                else
                    *(preExpr + (preN--)) = symbol;
            }

            saveToken(preExpr, SPACE, preN--); // 연산자와 피연산자 간에 공백 있어야함
        }
        // 열린 괄호는 닫힌 괄호가 나올때까지 stack내 값 삭제
        // 열린 괄호와 닫힌 괄호는 최종 식에 저장하지 않음
        // token에는 삭제된 토큰이 저장됨
        else if(token == LPAREN){
            while(top->token != RPAREN){
                pop(&popToken);
                saveToken(preExpr, popToken, preN--); // 최종 식에 토큰에 해당하는 연산자 저장
                saveToken(preExpr, SPACE, preN--); // 연산자 간에 공백 있어야함
            }
            pop(&popToken); // 닫힌 괄호도 삭제
        }
        // 닫힌 괄호를 포함한 그 외의 모든 연산자
        // 연산자의 우선순위가 높을 수록(값이 클 수록) 스택의 위쪽에 위치함
        // 새로 들어오는 연산자의 우선순위가 top의 우선순위보다 낮다면, top 삭제
        else{
            while(isp[top->token] > icp[token]){
                pop(&popToken);
                saveToken(preExpr, popToken, preN--);
                saveToken(preExpr, SPACE, preN--); // 연산자 간에 공백 있어야함
            }
            push(token); // 새로 들어온 연산자를 스택에 저장
        }
    }

    // 스택에 남아있는 연산자들 모두 최종식에 저장
    for(pop(&popToken); popToken != EOS; pop(&popToken)){
        saveToken(preExpr, popToken, preN--);
        saveToken(preExpr, SPACE, preN--);
    }


    // 문자열을 역순으로 배열의 끝부터 저장했기 때문에, 문자열을 배열의 맨 앞으로 이동
    // 기존의 문자열의 시작 위치는 preN + 2 (맨 앞에 공백이 저장되었기 때문에 이를 제외해야함)
    preN += 2;
    memmove(preExpr, preExpr + preN, MAX_EXPR_SIZE - preN);
}

// 후위표기법 -> 중위표기법
void postfixToInfix()
{
    char midExpr1[MAX_EXPR_SIZE] = "", midExpr2[MAX_EXPR_SIZE] = "";
    char operator[4];
    char symbol;
    Token token;
    int n = 0, i = 0; // 읽어올 수식의 위치(인덱스)

    // 후위표기식(postfixExpr)에서 토큰을 하나씩 가져오기
    for(token = getToken(postExpr, &symbol, n++); token != EOS; token = getToken(postExpr, &symbol, n++)){
        // 공백이 입력된 경우 무시
        if(token == SPACE)
            continue;
        // 피연산자는 스택에 저장
        else if(token == NUM){
            midExpr1[i++] = symbol;

            while(getToken(postExpr, &symbol, n++) != SPACE)
                midExpr1[i++] = symbol;
            midExpr1[i] = '\0';

            toInfixPush(NUM, midExpr1);

            // 초기화
            i = 0;
            memset(midExpr1, 0, sizeof(midExpr1));
        }
        // 연산자인 경우
        // 기존의 연산(스택)들을 살펴보고, 우선순위가 낮은 연산에 괄호 처리
        // 스택에서 두 개 꺼내서 문자열(식) 합치기
        else{
            // -가 입력된 경우에는 연산자인지 음수인지 구분 필요
            // 연산자가 아닌 음수인 경우
            if(token == MINUS){
                if((token = getToken(postExpr, &symbol, n)) != SPACE && token != EOS){
                    saveToken(midExpr1, token, i++);
                    continue;
                }
                else{
                    token = MINUS;
                    symbol = '-';
                }
            }

            // 괄호처리가 필요한 연산식에 모두 괄호 처리
            modifyExpr(token);

            // 피연산자 두 개 가져옴
            toInfixPop(midExpr2);
            toInfixPop(midExpr1);

            // 연산자 앞 뒤로 공백 있어야함
            operator[0] = ' ';
            operator[1] = symbol;
            operator[2] = ' ';
            operator[3] = '\0';

            // 피연산자 + 연산자 + 피연산자
            strcat(midExpr1, operator);
            strcat(midExpr1, midExpr2);

            // 중간식과 해당 식에서 사용한 연산자(토큰)을 스택에 저장
            toInfixPush(token, midExpr1);

            memset(midExpr1, 0, sizeof(midExpr1)); // 초기화
            memset(midExpr2, 0, sizeof(midExpr2)); // 초기화
        }
    }

    // 스택에서 마지막에 pop한 문자열을 중위표기법의 식에 저장
    toInfixPop(midExpr1);
    strcpy(inExpr, midExpr1);
}

// 전위표기법 -> 중위표기법
void prefixToInfix()
{
    char midExpr1[MAX_EXPR_SIZE] = "", midExpr2[MAX_EXPR_SIZE] = "";
    char operator[4];
    char symbol;
    Token token;
    int n = exprLength - 1, i = MAX_EXPR_SIZE - 2; // 읽어올 수식의 위치(인덱스), i는 맨 마지막에 널문자를 둬야하므로 -2

    // 전위표기식(prefixExpr)에서 토큰을 역순으로 하나씩 가져오기
    for(token = getToken(preExpr, &symbol, n--); n + 1 >= 0; token = getToken(preExpr, &symbol, n--)){
        // 공백이 입력된 경우 무시
        if(token == SPACE)
            continue;
        // 피연산자는 스택에 저장
        else if(token == NUM){
            midExpr1[i--] = symbol;

            // 음수인 경우도 저장됨
            while(getToken(preExpr, &symbol, n--) != SPACE){
                if(n + 1 < 0)
                    break;
                midExpr1[i--] = symbol;
            }

            // 문자열을 역순으로 배열의 끝부터 저장했기 때문에, 문자열을 배열의 맨 앞으로 이동
            // 기존의 문자열의 시작 위치는 i + 1

            memmove(midExpr1, midExpr1 + i + 1, MAX_EXPR_SIZE - i);
            
            i = MAX_EXPR_SIZE - 2;

            toInfixPush(NUM, midExpr1);

            memset(midExpr1, 0, sizeof(midExpr1)); // 초기화
        }
        // 연산자인 경우
        // 기존의 연산(스택)들을 살펴보고, 우선순위가 낮은 연산에 괄호 처리
        // 스택에서 두 개 꺼내서 문자열(식) 합치기
        else{
            // 괄호처리가 필요한 연산식에 모두 괄호 처리
            modifyExpr(token);

            // 피연산자 두 개 가져옴
            toInfixPop(midExpr1);
            toInfixPop(midExpr2);

            // 연산자 앞 뒤로 공백 있어야함
            operator[0] = ' ';
            operator[1] = symbol;
            operator[2] = ' ';
            operator[3] = '\0';

            // 피연산자 + 연산자 + 피연산자
            strcat(midExpr1, operator);
            strcat(midExpr1, midExpr2);

            // 중간식과 해당 식에서 사용한 연산자(토큰)을 스택에 저장
            toInfixPush(token, midExpr1);

            memset(midExpr1, 0, sizeof(midExpr1)); // 초기화
            memset(midExpr2, 0, sizeof(midExpr2)); // 초기화
        }
    }

    // 스택에서 마지막에 pop한 문자열을 중위표기법의 식에 저장
    toInfixPop(midExpr1);
    strcpy(inExpr, midExpr1);
}