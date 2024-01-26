#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPR_SIZE 100 // 수식의 최대 길이
#define MAX_STACK_SIZE 100 // 스택의 최대 사이즈

// 보통 우선순위 데이터 타입은 각 연산자에 대한 우선순위 값을 저장하기 위한 정수 또는 열거형 타입으로 구현함
typedef enum{
    LPAREN, RPAREN, PLUS, MINUS, TIMES, DIVIDE, MOD, EOS, OPERAND
}Precedence;

char expr[MAX_EXPR_SIZE] = {0, }; // 입력 받을 중위표기법의 수식
char postexpr[MAX_EXPR_SIZE] = {0, }; // 출력할 후위표기법의 수식
char *postfixExpr = postexpr; 
Precedence stack[MAX_STACK_SIZE]; // stack 내부에는 각 연산자들에 해당하는 우선순위 값이 저장됨

int evalStack[MAX_STACK_SIZE]; // 수식의 결과 값을 구하기 위해 피연산자도 저장하기 위한 스택
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0}; // in-stack precedence: 스택 내에서 우선순위가 가장 높은 연산자의 우선순위 (top에 위치한 값)
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0}; // incoming precedence: 들어오는 연산자의 우선순위
int top = -1; // 후위표기법의 수식을 구하기 위한 스택의 top
int evalTop = -1; // 입력받은 수식의 결과를 구하기 위한 스택의 top

void stackFull(const char *type); // 스택 오버플로우 처리
void stackEmpty(const char *type); // 스택 언더플로우 처리
void push(Precedence item); // 연산자들의 우선순위 값을 stack에 저장 
void evalPush(int item); // 수식의 중간 과정 값들을 evalStack에 저장
Precedence pop(); // stack 내의 원소 삭제
int evalPop(); // evalStack 내의 원소 삭제
void printToken(Precedence token); // token에 해당하는 연산자를 최종 후위표기식에 저장
Precedence getToken(char *symbol, int *n); // 연산순위를 stack에 저장하기 위해 토큰에 해당하는 연산순위 가져옴
int getEvalToken(char *symbol, int *n); // 수식의 결과값을 계산하기 위해 변환해둔 후위표기식에서 토큰 가져옴
void postfix();
int eval();

int main(int argc, char *argv[])
{
    fprintf(stdout, "input infix: ");
    scanf("%s", expr);
    postfix(); // 후위표기법으로 변환 후, 해당 식 출력
    fprintf(stdout, "result: %d\n", eval());

    return 0;
}

void stackFull(const char *type)
{
    fprintf(stderr, "%s Stack is full cannot add elements\n", type);
    exit(EXIT_FAILURE);
}

void stackEmpty(const char *type)
{
    fprintf(stderr, "%s Stack is empty cannot delete elements\n", type);
    exit(EXIT_FAILURE);
}

void push(Precedence item)
{
    if(top >= MAX_STACK_SIZE - 1)
        stackFull("Token");
    stack[++top] = item;
}

void evalPush(int item)
{
    if(evalTop >= MAX_STACK_SIZE - 1)
        stackFull("Eval");
    evalStack[++evalTop] = item;
}

Precedence pop()
{
    if(top == -1)
        stackEmpty("Token");
    
    return stack[top--];
}

int evalPop()
{
    if(evalTop == -1)
        stackEmpty("Eval");

    return evalStack[evalTop--];
}

void printToken(Precedence token)
{
    switch (token){
    case PLUS:
        *postfixExpr++ = '+';
        break;

    case MINUS:
        *postfixExpr++ = '-';
        break;

    case TIMES:
        *postfixExpr++ = '*';
        break;

    case DIVIDE:
        *postfixExpr++ = '/';
        break;

    case MOD:
        *postfixExpr++ = '%';
        break;
    
    default:
        break;
    }
}

Precedence getToken(char *symbol, int *n)
{
    *symbol = expr[(*n)++]; // 입력받은 수식에서 토큰을 하나 가져옴
    switch (*symbol){
        case '(':
            return LPAREN;

        case ')':
            return RPAREN;

        case '+':
            return PLUS;

        case '-':
            return MINUS;

        case '/':
            return DIVIDE;

        case '*':
            return TIMES;

        case '%':
            return MOD;

        case '\0':
            return EOS;
        
        default:
            return OPERAND;
    } 

}

int getEvalToken(char *symbol, int *n)
{
    *symbol = postexpr[(*n)++]; // 변환해둔 후위표기법의 식에서 토큰 가져옴
    switch (*symbol){
        case '(':
            return LPAREN;

        case ')':
            return RPAREN;

        case '+':
            return PLUS;

        case '-':
            return MINUS;

        case '/':
            return DIVIDE;

        case '*':
            return TIMES;

        case '%':
            return MOD;

        case '\0':
            return EOS;
        
        default:
            return OPERAND;
    } 
}

void postfix()
{
    char symbol; // 수식에서 가져온 토큰
    Precedence token; // 해당 토큰의 종류(== 해당 토큰의 우선순위를 저장해둔 배열에서의 인덱스)
    int n = 0; // 입력받은 수식에서 토큰의 현재 인덱스
    top = 0; // 현재 스택에는 EOS가 들어있는 상태
    stack[0] = EOS; // 항상 모든 연산자들보다 우선순위가 높음: 0
    
    for(token = getToken(&symbol, &n); token != EOS; token = getToken(&symbol, &n)){
        // 피연산자는 스택을 거치지 않고 바로 expr 문자열에 저장
        if(token == OPERAND)
            *postfixExpr++ = symbol;
        // 닫힌 괄호: 열린 괄호가 나올 때까지 pop() 
        else if(token == RPAREN){
            while(stack[top] != LPAREN)
                printToken(pop()); // 열린 괄호가 나오기 전까지 연산자들을 expr 문자열에 저장
            pop(); // 열린 괄호도 삭제
        }
        // 그 외의 모든 연산자
        // 열린 괄호는 어떤 연산자가 나오든 
        else{
            // 연산자 우선순위가 높을 수록(값이 클 수록) 스택의 위쪽에 위치함
            // 새로 들어오는 연산자의 우선순위가 top의 우선순위보다 낮으면, top을 삭제
            while(isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }

    }

    // 스택에 남아있는 연산자들도 모두 expr 문자열에 저장
    while((token = pop()) != EOS)
        printToken(token);
    
    fprintf(stdout, "postfix: %s\n", postexpr);
}

int eval()
{
    Precedence token;
    char symbol;
    int n = 0;
    evalTop = -1;
    int op1, op2; // 피연산자

    token = getEvalToken(&symbol, &n); // 후위표기식(expr)에서 토큰 하나씩 가져옴
    while(token != EOS){
        // 피연산자인 경우: 스택에 저장
        if(token == OPERAND)
            evalPush(symbol - '0');
        // 연산자인 경우: 스택 내 위에서 두 개의 원소에 대해 연산 진행 
        else{
            op2 = evalPop();
            op1 = evalPop();

            switch (token){
                case PLUS:
                    evalPush(op1 + op2);
                    break;

                case MINUS:
                    evalPush(op1 - op2);
                    break;

                case TIMES:
                    evalPush(op1 * op2);
                    break;

                case DIVIDE:
                    evalPush(op1 / op2);
                    break;

                case MOD:
                    evalPush(op1 % op2);
                    break;
            }
        }
        token = getEvalToken(&symbol, &n);

    }

    return evalPop(); // 마지막에 스택에 남아있는 원소는 결과값
}