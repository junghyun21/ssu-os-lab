#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define NO_ERROR 1
#define NO_INPUT 2
#define ERROR_TOKEN 3
#define ERROR_ARITHMETIC 4
#define ERROR_ARGUMENT 5

void printError(int error); // 에러 문구 출력

#endif