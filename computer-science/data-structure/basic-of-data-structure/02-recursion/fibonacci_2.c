#include <stdio.h>

int fibo(int);

int main()
{
    int n;

    fprintf(stdout, "피보나치 수열의 항의 개수를 입력: ");
    scanf("%d", &n);
    
    fprintf(stdout, "피보나치 수열 출력: ");
    for(int i = 1; i <= n; i++)
        fprintf(stdout, "%d ", fibo(i));
    fprintf(stdout, "\n");

    return 0;
}

int fibo(int n)
{
    // 첫번째와 두번째 항은 1
    if(n < 3)
        return 1;
    // 세번쩨 항부터는 앞의 두 항의 합
    else
        return fibo(n - 1) + fibo(n - 2);
}