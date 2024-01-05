#include <stdio.h>

int myFunc(int);

int main()
{
    int n, res;

    fprintf(stdout, "팩토리얼 계산할 숫자를 입력: ");
    scanf("%d", &n);

    res = myFunc(n);

    fprintf(stdout, "결과값: %d\n", res);

    return 0;
}

int myFunc(int n)
{
    // 기본 입력
    if(n == 0){
        return 1; 
    }
    // 재귀 입력
    else{
        return n * myFunc(n - 1); 
    }
}