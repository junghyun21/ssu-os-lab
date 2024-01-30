#include "expr.h"

char preExpr[MAX_EXPR_SIZE] = {0, }; // 최종적으로 저장할 전위표기법의 식
char inExpr[MAX_EXPR_SIZE] = {0, };; // 최종적으로 저장할 중위표기법의 식
char postExpr[MAX_EXPR_SIZE] = {0, };; // 최종적으로 저장할 후위표기법의 식

// 수식 초기화
void initExpr()
{
    memset(preExpr, 0, sizeof(preExpr));
    memset(inExpr, 0, sizeof(preExpr));
    memset(postExpr, 0, sizeof(preExpr));
}

// 올바른 수식이 들어왔는지 및 exit가 입력되었는지 확인
int checkExpr(const char *expr, bool *isExit)
{
    Token token;
    char symbol;
    int n = 0;
    int lparenCnt = 0, rparenCnt = 0; // 여는 괄호 및 닫는 괄호의 개수
    int operand = 0, operator = 0; // 피연산자 및 연산자의 개수
    bool hasDot = false;
    bool hasNumAfterDot = false;
    bool isEOS = false;

    // 공백이 입력되었는지 검사
    if(expr[0] == '\0')
        return NO_INPUT;

    // exit가 입력되었는지 검사
    // 수식이 명령행 인자로 입력된 경우에는 한 번만 실행 후 프로그램이 종료될 예정 -> isExit == true
    if(!(*isExit)){
        if(expr[0] == 'e' && expr[1] == 'x' && expr[2] == 'i' && expr[3] == 't'){
            *isExit = true;
            return NO_ERROR;
        }
    }

    // 입력받은 수식(문자열)에서 문자 하나씩 검사
    for(token = getToken(expr, &symbol, n++); token != EOS; token = getToken(expr, &symbol, n++)){
        isEOS = false;

        // 숫자 또는 잘못된 문자가 입력된 경우
        if(token == NUM){
            // 잘못된 문자가 입력된 경우
            if(symbol < '0' || symbol > '9')
                return ERROR_TOKEN;

            // 올바른 문자가 입력된 경우: 해당 피연산자 검사가 끝날 때까지 반복
            while((token = getToken(expr, &symbol, n++)) != SPACE){
                // 숫자 또는 잘못된 문자가 입력된 경우
                if(token == NUM){
                    // 잘못된 문자가 입력된 경우: 에러
                    if(symbol < '0' || symbol > '9')
                        return ERROR_TOKEN;

                    // .이 입력된 이후 숫자가 입력된 경우
                    if(hasDot)
                        hasNumAfterDot = true;
                }
                // .이 들어온 경우
                else if(token == DOT){
                    // 만약 해당 피연산자에 .이 있는데 .이 또 입력된 경우에는 에러
                    if(hasDot == true)
                        return ERROR_TOKEN;
                    else
                        hasDot = true;
                }
                // 연산식이 모두 입력 완료된 경우
                else if(token == EOS){
                    // 소수점 뒤에 숫자가 더 입력되지 않은 경우: 에러
                    if(hasDot && !hasNumAfterDot)
                        return ERROR_TOKEN;
                    
                    isEOS = true;
                    break;
                }
                // 그 외의 연산자가 입력된 경우: 피연산자와 연산자 간의 토큰 분리가 안되었으므로 에러
                else
                    return ERROR_TOKEN;
            }

            // 소수점 뒤에 숫자가 더 입력되지 않은 경우: 에러
            if(hasDot && !hasNumAfterDot)
                return ERROR_TOKEN;

            hasDot = false;
            hasNumAfterDot = false;

            ++operand;
        }
        // 숫자 입력 없이 바로 .이 입력된 경우: 에러
        else if(token == DOT){
            return ERROR_TOKEN;
        }
        // 열린 괄호가 입력된 경우
        else if(token == LPAREN){
            ++lparenCnt;

            // 연산식이 모두 입력 완료된 경우: 열린 괄호 입력 후에는 반드시 닫힌 괄호가 와야하므로 에러
            // 괄호 이후에 공백이 입력되지 않으면 에러
            if((token = getToken(expr, &symbol, n++)) == EOS || token != SPACE)
                return ERROR_TOKEN;

        }
        // 닫힌 괄호가 입력된 경우
        else if(token == RPAREN){
            // 닫힌 괄호는 열린 괄호의 개수보다 많을 수 없음
            if(lparenCnt < ++rparenCnt)
                return ERROR_TOKEN;
            
            // 연산식이 모두 입력 완료된 경우
            if((token = getToken(expr, &symbol, n++)) == EOS)
                isEOS = true;

            // 연산자 이후 공백이 입력되지 않으면 에러
            else if(token != SPACE)
                return ERROR_TOKEN;

        }  
        // 그 외 연산자가 입력된 경우: 연산자 이후 무조건 공백이 들어와야함
        else{
            // -가 입력된 경우: 음수인지 연산자인지 구분 필요
            if(token == MINUS){
                // 음수인 경우
                if((token = getToken(expr, &symbol, n)) != SPACE && token != EOS)
                    continue;
                
            }

            ++operator;

            // 연산식이 모두 입력 완료된 경우: checkExpr() 함수 성공적으로 종료
            if((token = getToken(expr, &symbol, n++)) == EOS)
                isEOS = true;

            // 연산자 이후 공백이 입력되지 않으면 에러
            else if(token != SPACE)
                return ERROR_TOKEN;
        }

        // 반복문 내부에서 토큰 확인 도중 수식이 종료된 경우
        if(isEOS)
            --n;
    }

    // 열린 괄호와 닫힌 괄호의 개수가 맞아야 올바른 수식임
    // 피연산자는 최소 1개가 있어야 하며, 피연산자의 개수보다 연산자의 개수보다 하나 많아야함
    if(lparenCnt == rparenCnt && operand > 0 && operand - operator == 1)
        return NO_ERROR;
    else
        return ERROR_TOKEN;    
}

// 입력 받은 수식이 어떤 표기법인지 확인
ExprType recongnizeExpr(const char *expr)
{
    Token token;
    char symbol;
    int i, n = 0;

    // 전위: 연산자 + ... + 피연산자
    // 중위: 피연산자 + 연산자 + 피연산자
    // 후위: 피연산자 + ... + 연산자
    i = 1;
    while(i < 3){
        token = getToken(expr, &symbol, n++);

        // 공백이 나온 경우 무시
        if(token == SPACE)
            continue;

        // 괄호가 입력된 경우: 중위(infix)
        if(token == LPAREN || token == RPAREN)
            return INFIX;

        if(i == 1){
            // 첫번째 입력된 값이 피연산자인 경우: 중위 or 후위 or 모두 해당
            if(token == NUM)
                while((token = getToken(expr, &symbol, n++)) != SPACE){
                    if(token == EOS){
                        return ALL;
                    }
                }
            
            // 첫번째 입력된 값이 연산자인 경우: 전위표기법의 식
            else{
                if(token == MINUS)
                    if(getToken(expr, &symbol, n) != SPACE)
                        continue;

                return PREFIX;
            } 
        }

        if(i == 2){
            // 두번째 입력된 값이 피연산자인 경우: 후위
            if(token == NUM){
                return POSTFIX;
            }
            // 두번째 입력된 값이 연산자인 경우: 중위
            else{
                if(token == MINUS)
                    if(getToken(expr, &symbol, n) != SPACE)
                        return POSTFIX;

                return INFIX;
            } 
        }   
    
        ++i;
    }

    return -1;
}

// 수식에서 토큰을 하나씩 가져옴
Token getToken(const char *expr, char *symbol, int n)
{
    // expr에 해당하는 수식에서 토큰을 하나 가져옴
    *symbol = expr[n];

    // 토큰이 해당되는 열거형 상수 반환
    switch (*symbol){
        case '(':
            return LPAREN;

        case ')':
            return RPAREN;

        case '+':
            return PLUS;

        case '-':
            return MINUS;

        case '*':
            return TIMES;

        case '/':
            return DIVIDE;

        case '%':
            return MOD;

        case '^':
            return POWER;

        case '.':
            return DOT;

        case '\0':
            return EOS;

        case ' ':
            return SPACE;
        
        default:
            return NUM;
    } 
}

// 최종 표기법에 해당 토큰 저장
void saveToken(char *expr, Token token, int n)
{
    switch (token)
    {
        case PLUS:
            *(expr + n) = '+';
            break;

        case MINUS:
            *(expr + n) = '-';
            break;

        case TIMES:
            *(expr + n) = '*';
            break;

        case DIVIDE:
            *(expr + n) = '/';
            break;

        case MOD:
            *(expr + n) = '%';
            break;
        
        case POWER:
            *(expr + n) = '^';
            break;

        case EOS:
            *(expr + n) = '\0';
            break;

        case SPACE:
            *(expr + n) = ' ';
            break;

        default:
            fprintf(stderr, "saveToken(): wrong token\n");
            exit(1);
    }
}

// 수식 출력
void printExpr(ExprType exprType)
{
    switch (exprType){
        case PREFIX:
            printf("infix: impossible\n");
            printf("prefix: possible\n");
            displayExpr();
            printf("postfix: impossible\n");
            break;

        case INFIX:
            printf("infix: possible\n");
            displayExpr();
            printf("prefix: impossible\n");
            printf("postfix: impossible\n");
            break;

        case POSTFIX:
            printf("infix: impossible\n");
            printf("prefix: impossible\n");
            printf("postfix: possible\n");
            displayExpr();
            break;

        case ALL:
            printf("infix: possible\n");
            displayExpr();
            printf("prefix: possible\n");
            displayExpr();
            printf("postfix: possible\n");
            displayExpr();
            break;
    }

    printf("\n");
}

void displayExpr()
{
    printf("- IN: %s\n", inExpr);
    printf("- PR: %s\n", preExpr);
    printf("- PO: %s\n", postExpr);
}

