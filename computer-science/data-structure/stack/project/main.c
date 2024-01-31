#include <stdio.h>
#include "precedence.h"
#include "expr.h"
#include "convert.h"
#include "result.h"
#include "error.h"

int main(int argc, char *argv[])
{
    char expr[MAX_EXPR_SIZE]; // 입력받은 수식 저장
    int errorNum;
    ExprType exprType;
    bool isExit = false;

    // 수식을 프로그램 실행 도중에 받아야 하는 경우: exit 입력 시 프로그램 종료
    if(argc == 1){
        while(!isExit){
            // 식을 저장했던 곳들 모두 초기화
            initExpr();
            
            // 수식 입력받기
            printf("input expression: ");
            fgets(expr, sizeof(expr), stdin);
            expr[strlen(expr) - 1] = '\0'; // fgets()는 개행문자도 읽어오기 때문에 널문자로 바꿔줌

            // 올바른 수식이 들어왔는지 검사하고, exit가 입력된 경우에는 프로그램 종료
            errorNum = checkExpr(expr, &isExit);
            if(isExit)
                break;

            // 수식 입력과 관련한 예외 처리
            switch (errorNum){
                // 아무것도 입력되지 않은 경우: 다시 입력받기
                case NO_INPUT:
                    continue;
                // 잘못된 수식(토큰)이 입력된 경우: 에러 문구 출력 후 종료
                case ERROR_TOKEN:
                    printError(ERROR_TOKEN);
                    continue;
            }

            // 기존의 식이 어떤 표기법이였는지 확인하고, 식 변환
            exprType = convertExpr(expr);

            // 변환한 식과 수식의 계산 결과 출력
            printExpr(exprType);        
            printResult(exprType);
            
        }
    }

    // 명령행 인자에 수식이 입력된 경우: 한 번 실행 후 프로그램 종료
    else if(argc == 2){
        // 한 번만 실행하고 종료시킬 예정으로, true로 설정
        isExit = true;

        // 올바른 수식이 들어왔는지 검사
        // 잘못된 수식(토큰)이 입력된 경우에는 에러 문구 출력 후 종료
        if(checkExpr(argv[1], &isExit) == ERROR_TOKEN)
            printError(ERROR_TOKEN);

        // 기존의 식이 어떤 표기법이였는지 확인하고, 식 변환
        exprType = convertExpr(argv[1]);

        // 변환한 식과 수식의 계산 결과 출력
        printExpr(exprType);            
        printResult(exprType);
    }

    // 명령행 인지가 더 들어온 경우: 에러 출력 후 종료
    else
        printError(ERROR_ARGUMENT);
    
    return 0;
}