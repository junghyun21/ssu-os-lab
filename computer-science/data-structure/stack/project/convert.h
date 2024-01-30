#ifndef EXPR_CONVERT_H
#define EXPR_CONVERT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "precedence.h"
#include "expr.h"

#define MAX_EXPR_SIZE 100 // 수식의 최대 길이

// 중위표기법의 식을 전위/후위표기법의 식으로 변환할 때 사용할 스택의 원소
typedef struct Stack *StackPointer;
typedef struct Stack{
    Token token;
    StackPointer link;
}Stack;

// 전위/후위표기법의 식을 중위표기법의 식으로 변환할 때 사용할 스택의 원소
typedef struct ToInfixStack *ToInfixStackPointer;
typedef struct ToInfixStack{
    Token token;
    char midExpr[MAX_EXPR_SIZE];
    ToInfixStackPointer link;
}ToInfixStack;

extern StackPointer top;
extern ToInfixStackPointer toInfixTop;

void stackEmpty(const char *str); // 스택 언더플로우 처리
void push(Token token); // 삽입
void pop(Token *token); // 삭제
void toInfixPush(Token token, char *midExpr); // 삽입
void toInfixPop(char *midExpr); // 삭제
void modifyExpr(Token token); // 현재 들어오는 연산자보다 우선순위가 낮은 원소는 모두 괄호 추가

ExprType convertExpr(char *expr); // 식 변환
void infixToPostfix(); // 중위표기법 -> 후위표기법
void infixToPrefix(); // 중위표기법 -> 전위표기법 (역순으로 읽기 때문에 기존 식의 길이 알아야함)
void postfixToInfix(); // 후위표기법 -> 중위표기법
void prefixToInfix(); // 전위표기법 -> 중위표기법 (역순으로 읽기 때문에 기존 식의 길이 알아야함)

#endif