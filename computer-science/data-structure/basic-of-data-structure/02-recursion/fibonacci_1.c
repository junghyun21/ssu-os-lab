#include <stdio.h>
#include <stdlib.h>

void myFunc(int*, int, int);

int main()
{
    int n;
    int *res;

    fprintf(stdout, "피보나치 수열의 항의 개수를 입력: ");
    scanf("%d", &n);

    res = (int*)malloc(n * sizeof(int)); // 수열을 저장할 공간

    myFunc(res, n, 0);
    
    fprintf(stdout, "피보나치 수열 출력: ");
    for(int i = 0; i < n; i++){
        fprintf(stdout, "%d ", res[i]);
    }
    fprintf(stdout, "\n");

    return 0;
}

void myFunc(int *sequence, int n, int term)
{
    // 기본 입력
    if(n == 0){
        return;
    }
    // 재귀 입력
    else
    {
        // 첫번째와 두번째 항은 1
        if(term < 2){
            sequence[term] = 1;
        }
        // 세번쩨 항부터는 앞의 두 항의 합
        else{
            sequence[term] = sequence[term - 1] + sequence[term - 2];
        }

        return myFunc(sequence, n - 1, term + 1);
    }
}
