#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TOWER_NUM 3

void myFunc(int**, int, int, int);

int main()
{
    int i, n, move;
    int *tower[TOWER_NUM];

    fprintf(stdout, "하노이 탑의 원판 개수 입력: ");
    scanf("%d", &n);

    // 세 개의 기둥에 대해 동적 할당
    for(i = 0; i < TOWER_NUM; i++)
        tower[i] = (int*)malloc((n + 1) * sizeof(int));
    
    // 각 기둥들 초기화
    // 첫번째 기둥 (초기에 원판들이 모두 쌓여있는 기둥)
    tower[0][0] = n; // 해당 기둥에 쌓여있는 원판의 개수
    for(i = 1; i <= n; i++)
        tower[0][i] = n - i + 1;

    // 두번째 기둥 (가운데에 위치한 기둥)
    // 세번째 기둥 (최종적으로 원판들이 모두 쌓여있을 기둥)
    tower[1][0] = 0; // 해당 기둥에 쌓여있는 원판의 개수
    tower[2][0] = 0; // 해당 기둥에 쌓여있는 원판의 개수
    for(i = 1; i <= n; i++){
        tower[1][i] = 0;
        tower[2][i] = 0;
    }

    // 초기 상태
    for(i = n; i > 0; i--)
        fprintf(stdout, "%-3d | %-3d | %-3d\n", tower[0][i], tower[1][i], tower[2][i]);
    fprintf(stdout, "----------------\n");

    move = (1 << n) - 1; // 원반의 이동 횟수는 2^n - 1
    
    myFunc(tower, move, n, 0);
    
    return 0;
}

// tower: 각 기둥에 위치한 원판 정보
//      : tower[0] == 첫번째, tower[1] == 두번째, tower[2] == 세번째
// move: 남은 이동 횟수
// n: 원판의 총 개수
// recentDisk: 가장 최근에 이동시킨 원판
void myFunc(int **tower, int move, int n, int recentDisk)
{
    // 기본 입력
    if(move == 0){
        fprintf(stdout, "원판의 총 이동횟수: %d회\n", (1 << n) - 1);
        return;
    }
    // 재귀 입력
    else{
        int oldTowerTopIdx = -1, newTowerTopIdx = -1;

        // 첫번째 이동일 때, 첫번째 기둥의 맨 위 원판 이동
        // 홀수이면 세번째 기둥으로, 짝수이면 두번째 기둥으로 이동
        if(move == (1 << n) - 1){
            // 첫번째 기둥의 맨 위 원판이 저장된 곳의 위치
            oldTowerTopIdx = tower[0][0];

            // 홀수
            if(n % 2){
                newTowerTopIdx = tower[2][0];

                tower[2][++newTowerTopIdx] = tower[0][oldTowerTopIdx];
                tower[0][oldTowerTopIdx--] = 0;

                tower[2][0] = newTowerTopIdx;
                tower[0][0] = oldTowerTopIdx;
        
                recentDisk = tower[2][newTowerTopIdx];
            }
            // 짝수
            else{
                newTowerTopIdx = tower[1][0];

                tower[1][++newTowerTopIdx] = tower[0][oldTowerTopIdx];
                tower[0][oldTowerTopIdx--] = 0;

                tower[1][0] = newTowerTopIdx;
                tower[0][0] = oldTowerTopIdx;

                recentDisk = tower[1][newTowerTopIdx];
            }
        }
        // 두번째 이동부터
        else{
            int sortTower[TOWER_NUM] = {0, };
            int tops[TOWER_NUM] = {0, };
            int oldTowerIdx, newTowerIdx;
            int i, j, towerTop, emptyCnt = 0;
            bool isMove = false;

            // 각 기둥의 맨 위에 존재하는 원판들의 크기에 따라 기둥의 인덱스를 내림차순으로 정렬
            // 원판 크기가 0인 것(실제로 원판이 존재하지 않는 것)은 제일 뒤에 정렬됨
            for(i = 0; i < TOWER_NUM; i++){
                towerTop = tower[i][0];

                tops[i] = tower[i][towerTop];
                sortTower[i] = i;

                // 해당 원판의 크기가 0이 아니라면 정렬
                if(tops[i]){
                    for(j = 0; j < i; j++){
                        if(tops[i] > tops[j]){
                            // tops 배열 정렬 (각 기둥의 맨 위의 원판 크기 정렬하여 저장)
                            int temp = tops[i];
                            tops[i] = tops[j];
                            tops[j] = temp;

                            // sortTower 배열 정렬 (원판의 크기에 따라 내림차순으로 기둥의 순서 지정)
                            // 원판의 크기가 클 수록 인덱스가 작아짐
                            temp = sortTower[i];
                            sortTower[i] = sortTower[j];
                            sortTower[j] = temp;
                        }
                    }
                }
                // 원판의 크기가 0이라면 빈 기둥의 개수 카운트
                else
                    ++emptyCnt;
            }
            
            // 각 기둥의 맨 위에 있는 원판들 중 이동시킬 원판 선택
            for(i = 0; i < TOWER_NUM; i++){
                oldTowerIdx = sortTower[i]; // 이동시킬 원판이 위치한 기둥
                oldTowerTopIdx = tower[oldTowerIdx][0]; // 이동시킬 원판이 위치한 기둥 내 인덱스
                
                // 기둥 맨 위에 있는 원판의 크기가 0이 아닐 때
                // (0이면 실제로 기둥 내에 원판이 없음으로 이동시킬 원판도 존재하지 않음)
                // 해당 원판이 직전 단계에서 이동하지 않았을 때
                if(tower[oldTowerIdx][oldTowerTopIdx] && tower[oldTowerIdx][oldTowerTopIdx] != recentDisk){
                    // 해당 원판이 이동 가능한 기둥의 개수에 따라 경우의 수 나뉨
                    // 이동 가능한 기둥의 개수
                    // = 자신보다 크기가 큰 원판의 개수(tops에서 자신이 위치한 인덱스와 동일)
                    // - 원판이 아예 없는 빈 기둥의 개수 (기둥 맨 위에 있는 원판의 크기가 0인 것들의 개수) 
                    switch(i){
                        // 빈기둥 없이 모두 자신보다 큰 원판인 경우
                        case 2:
                            newTowerIdx = sortTower[0];
                            newTowerTopIdx = tower[newTowerIdx][0];

                            isMove = true;

                            // 이웃한 원판들의 차가 홀수인 곳으로 이동
                            if((tower[newTowerIdx][newTowerTopIdx] - tower[oldTowerIdx][oldTowerTopIdx]) % 2 == 0){
                                newTowerIdx = sortTower[1];
                                newTowerTopIdx = tower[newTowerIdx][0];
                            }

                            break;

                        // 자신보다 큰 원판이 하나 있거나, 빈기둥이 하나 있는 경우
                        case 1: 
                            newTowerIdx = sortTower[0];
                            newTowerTopIdx = tower[newTowerIdx][0];

                            // 이웃한 원판들의 차는 홀수여야만 함
                            if((tower[newTowerIdx][newTowerTopIdx] - tower[oldTowerIdx][oldTowerTopIdx]) % 2)
                                isMove = true;
                            // 빈기둥이 있을 때, 빈기둥으로 이동
                            else{
                                if(emptyCnt){
                                    newTowerIdx = sortTower[2];
                                    newTowerTopIdx = tower[newTowerIdx][2];

                                    isMove = true;
                                }
                            }

                            break;

                        // 자신보다 큰 원판이 없고, 이동 가능한 기둥이 빈기둥만 존재하는 경우
                        default:
                            continue;
                    }
                }

                // 이동 가능한 기둥이 있다면 이동
                if(isMove)
                    break;
            
            }

            // 만약 어떠한 원판도 이동시키지 못했다면, 가장 큰 원판을 빈 기둥으로 이동
            // 맨 첫번째 단계를 제외하고 빈기둥은 1개 이하
            // sortTower(기둥에 가장 위에 위치한 원판의 크기를 내림차순으로 정렬한 배열)에서 마지막에 위치한 기둥이 빈기둥
            if(i == TOWER_NUM){
                oldTowerIdx = sortTower[0];
                oldTowerTopIdx = tower[oldTowerIdx][0];    

                newTowerIdx = sortTower[2];
                newTowerTopIdx = tower[newTowerIdx][0];
            }

            // 원판 이동 및 변경된 top 값 저장
            tower[newTowerIdx][++newTowerTopIdx] = tower[oldTowerIdx][oldTowerTopIdx];
            tower[oldTowerIdx][oldTowerTopIdx--] = 0;

            tower[newTowerIdx][0] = newTowerTopIdx;
            tower[oldTowerIdx][0] = oldTowerTopIdx;
    
            recentDisk = tower[newTowerIdx][newTowerTopIdx];
        }

        // 변경된 하노이탑 출력
        for(int i = n; i > 0; i--)
            fprintf(stdout, "%-3d | %-3d | %-3d\n", tower[0][i], tower[1][i], tower[2][i]);
        fprintf(stdout, "----------------\n");

        return myFunc(tower, --move, n, recentDisk);
    }
}
