#include "error.h"

void printError(int error)
{
    printf("error: ");
    switch(error){
        case ERROR_TOKEN:
            printf("Wrong token input\n");
            break;

        case ERROR_ARITHMETIC:
            printf("Arithmetic error(cannot devide by zero)\n");
            break;

        case ERROR_ARGUMENT:
            fprintf(stderr, "Too many command-line argument\n");
            exit(1);

        default:
            fprintf(stderr, "Wrong error num\n");
            exit(1);
    }
}