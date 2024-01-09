#include <stdio.h>
#include <stdlib.h>

#define TOWER_NUM 3
#define TOP 0

enum Tower{START, TO, END};

void hanoi(int**, int, int, enum Tower, enum Tower, enum Tower);

int main()
{
    int *tower[TOWER_NUM];
    int n;

    fprintf(stdout, "원판의 개수를 입력: ");
    scanf("%d", &n);

    // 세 개의 기둥에 대해 동적 할당
    for(int i = 0; i < TOWER_NUM; i++)
        tower[i] = (int*)malloc((n + 1) * sizeof(int));

    // 각 기둥들 초기화
    // 첫번째 기둥 (초기에 원판들이 모두 쌓여있는 기둥)
    tower[START][TOP] = n; // 해당 기둥에 쌓여있는 원판의 개수
    for(int i = 1; i <= n; i++)
        tower[START][i] = n - i + 1;

    // 두번째 기둥 (가운데에 위치한 기둥)
    // 세번째 기둥 (최종적으로 원판들이 모두 쌓여있을 기둥)
    tower[TO][TOP] = 0; // 해당 기둥에 쌓여있는 원판의 개수
    tower[END][TOP] = 0; // 해당 기둥에 쌓여있는 원판의 개수
    for(int i = 1; i <= n; i++){
        tower[TO][i] = 0;
        tower[END][i] = 0;
    }

    hanoi(tower, n, n, START, TO, END);

    fprintf(stdout, "원판의 총 이동횟수: %d회\n", (1 << n) - 1);

    return 0;
}

void hanoi(int **tower, int total_n, int n, enum Tower start, enum Tower to, enum Tower end)
{
    if(n > 0){
        int startTopIdx, endTopIdx;

        // 1단계: 가장 큰 원판을 제외한 모든 원판 start -> to 이동
        // 이 때 목적지 기둥(end)은 잠시 거쳐가는 경유 기둥(to)이 됨
        hanoi(tower, total_n, n - 1, start, end, to);

        // 2단계: 가장 큰 원판 하나 남았을 때, 바로 start -> end 이동
        startTopIdx = tower[start][TOP];
        endTopIdx = tower[end][TOP];

        tower[end][++endTopIdx] = tower[start][startTopIdx];
        tower[start][startTopIdx--] = 0;

        tower[end][TOP] = endTopIdx;
        tower[start][TOP] = startTopIdx;

        // 변경된 하노이탑 출력
        for(int i = total_n; i > 0; i--)
            fprintf(stdout, "%-3d | %-3d | %-3d\n", tower[START][i], tower[TO][i], tower[END][i]);
        fprintf(stdout, "----------------\n");

        // 3단계: 가장 큰 원판을 제외한 모든 원판 to -> end 이동
        // 이 때 시작 기둥(start)은 잠시 거쳐가는 경유 기둥(to)이 됨
        hanoi(tower, total_n, n - 1, to, start, end);
    }

    return;
}