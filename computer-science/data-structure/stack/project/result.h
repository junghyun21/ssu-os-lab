#ifndef RESULT_H
#define RESULT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "precedence.h"
#include "expr.h"
#include "error.h"

#define INTEGER 0
#define DOUBLE 1

typedef struct evalStack *evalStackPointer;
typedef struct evalStack{
    int *intEval;
    double *doubleEval;
    evalStackPointer link;
}evalStack;

extern evalStackPointer evalTop;

void resultStackEmpty(); // 스택 언더플로우 처리
void evalPush(int *intEval, double *doubleEval); // 삽입
int evalPop(int **intEval, double **doubleEval); // 삭제

Token getPostToken(char *symbol, int *n); // 수식에서 토큰을 하나씩 가져옴

int getResult(void **result); // 수식의 결과값을 가져옴 (실패하면 error 리턴)
void printResult(ExprType exprType); // 수식의 결과 출력

#endif