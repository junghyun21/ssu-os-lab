#ifndef EXPR_H
#define EXPR_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "precedence.h"
#include "error.h"

#define MAX_EXPR_SIZE 100 // 입력받을 수식의 최대 길이

typedef enum ExprType{
    PREFIX, INFIX, POSTFIX, ALL
}ExprType;

extern int exprLength;

extern char preExpr[MAX_EXPR_SIZE]; // 최종적으로 저장할 전위표기법의 식
extern char inExpr[MAX_EXPR_SIZE]; // 최종적으로 저장할 중위표기법의 식
extern char postExpr[MAX_EXPR_SIZE]; // 최종적으로 저장할 후위표기법의 식

void initExpr(); // 식을 저장했던 곳들 초기화
int checkExpr(const char *expr, bool *isExit); // 올바른 수식이 들어왔는지 및 exit가 입력되었는지 확인
ExprType recongnizeExpr(const char *expr); // 입력 받은 수식이 어떤 표기법인지 확인

Token getToken(const char *expr, char *symbol, int n); // 수식에서 토큰을 하나씩 가져옴
void saveToken(char *expr, Token token, int n); // 최종 표기법에 해당 토큰 저장

// 수식 출력
void printExpr(ExprType exprType);
void displayExpr();

#endif