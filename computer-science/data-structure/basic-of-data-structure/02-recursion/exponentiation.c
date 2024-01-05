#include <stdio.h>

int myFunc(int, int);

int main()
{
    int base, exp, res;

    fprintf(stdout, "거듭 제곱 계산을 할 밑 입력: ");
    scanf("%d", &base);

    fprintf(stdout, "거듭 제곱 계산을 할 지수 입력: ");
    scanf("%d", &exp);

    res = myFunc(base, exp);

    fprintf(stdout, "결과값: %d\n", res);

    return 0;
}

int myFunc(int base, int exp)
{
    // 기본 입력
    if(exp == 0){
        return 1;
    }
    // 재귀 입력
    else{
        return base * myFunc(base, exp - 1);
    }
}
