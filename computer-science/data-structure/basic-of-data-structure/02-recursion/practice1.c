#include <stdio.h>
#include <stdlib.h>

void myFunc(int *, int *, int, int, int, int);

int main()
{
    int *front, *back;
    int n;

    printf("Input: ");
    scanf("%d", &n);

    front = (int *)malloc(n * sizeof(int));
    back = (int *)malloc(n * sizeof(int));

    myFunc(front, back, n, 0, 0, 0);

    free(front);
    free(back);

    return 0;
}

void myFunc(int *front, int *back, int n, int idx, int frontSum, int backSum)
{
    if(idx == n){
        if(frontSum == backSum){
            for(int i = 0; i < n; i++)
                printf("%d", front[i]);

            for(int i = 0; i < n; i++)
                printf("%d", back[i]);

            printf("\n");
        }
    }
    else{
        front[idx] = 0;
        back[idx] = 0;
        
        myFunc(front, back, n, idx + 1, frontSum, backSum);

        front[idx] = 1;
        back[idx] = 1;

        myFunc(front, back, n, idx + 1, frontSum + 1, backSum + 1);

        front[idx] = 1;
        back[idx] = 0;

        myFunc(front, back, n, idx + 1, frontSum + 1, backSum);

        front[idx] = 0;
        back[idx] = 1;

        myFunc(front, back, n, idx + 1, frontSum, backSum + 1);
    }

    return;
}