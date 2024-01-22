#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node{
    int data;
    struct node *prev; // 이전 노드를 가리키는 포인터
    struct node *next; // 다음 노드를 가리키는 포인터
}Node;

Node *createNode(int data);
void insert(int pos, int data, Node **start);
void deleteByPosition(int pos, Node **start);
void deleteByValue(int value, Node **start);
void traverse(Node *x);
void traverseInReverse(Node *x);
int menu(void);

int main()
{
    Node *start = NULL;
    int input;
    int pos;

    while(1)
    {
        switch (menu())
        {
            case 1: // 연결 리스트의 끝 지점에 데이터 삽입
                fprintf(stdout, "저장할 자연수 데이터를 입력하세요: ");
                scanf("%d", &input);
                insert(INT_MAX, input, &start);
                break;

            case 2: // 연결 리스트의 시작 지점에 데이터 삽입
                fprintf(stdout, "저장할 자연수 데이터를 입력하세요: ");
                scanf("%d", &input);
                insert(1, input, &start);
                break;

            case 3: // 특정 위치에 데이터 삽입
                fprintf(stdout, "데이터를 저장할 리스트 내의 위치를 입력하세요: ");
                scanf("%d", &pos);

                fprintf(stdout, "저장할 자연수 데이터를 입력하세요: ");
                scanf("%d", &input);
                insert(pos, input, &start);
                break;

            case 4: // 특정 위치의 데이터 삭제
                fprintf(stdout, "삭제할 데이터의 리스트 내 위치를 입력하세요: ");
                scanf("%d", &pos);
                deleteByPosition(pos, &start);
                break;

            case 5: // 특정 데이터 자체를 삭제
                fprintf(stdout, "삭제할 데이터를 입력하세요: ");
                scanf("%d", &input);
                deleteByValue(input, &start);
                break;

            case 6: // 연결 리스트를 시작 지점부터 출력
                traverse(start);
                break;

            case 7: // 연결 리스트를 끝 지점부터 출력
                traverseInReverse(start);
                break;

            case 8: // 프로그램 종료
                exit(0);
        }
    }

    return 0;
}

/* 주어진 데이터를 가지고 새로운 노드를 생성하여 해당 노드의 주소를 반환하는 함수
    - data: 노드에 저장할 데이터 */
Node *createNode(int data)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    
    return newNode;
}

/* 노드를 삽입하는 함수
    - pos: 노드를 삽입할 위치
    - data: 저장할 데이터
    - start: 연결 리스트의 시작 노드 */
void insert(int pos, int data, Node **start)
{
    // 연결 리스트의 시작 위치는 1이라고 설정
    // 따라서 삽입하고자 하는 위치가 1보다 작은 경우에는 삽입 불가
    if(pos < 1){
        puts("삽입이 불가능한 위치");
        return;
    }

    // 빈 리스트인 경우
    if(*start == NULL){
        *start = createNode(data);
        (*start)->prev = NULL;
        (*start)->next = NULL;
    }
    else{
        Node *curr = *start;

        // 맨 끝에 삽입하는 경우 (pos = INT_MAX)
        // : pos > 1이 false가 되기 전에 curr->next가 NULL이 됨 (리스트의 맨 끝에 도착) 
        // 특정 위치에 삽입하는 경우: pos = 특정 위치 값
        // : pos > 1이 false가 되는 순간의 curr이 삽입할 위치에 있는 노드
        // : 만약 pos가 연결 리스트의 길이보다 크다면, curr->next가 먼저 NULL이 됨
        for(; curr->next && pos > 1; --pos)
            curr = curr->next;

        // curr->next가 먼저 NULL이 되어 리스트의 맨 끝에 삽입할 때
        if(pos > 1){
            Node *newNode = createNode(data);
            newNode->prev = curr;
            newNode->next = curr->next;
            curr->next = newNode;
        }
        // 첫 번째 위치에 노드를 삽입할 때
        else if(curr == *start){
            Node *newNode = createNode(data);
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev = newNode;
            *start = newNode;
        }
        // 그 외의 지정한 위치(pos)에 노드를 삽입할 때
        else{
            Node *newNode = createNode(data);
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev->next = newNode;
            curr->prev = newNode;
        }
    }
}

/* 주어진 위치에 있는 노드 삭제
    - pos: 삭제할 노드의 위치
    - start: 연결 리스트의 시작 노드 */
void deleteByPosition(int pos, Node **start)
{
    // 연결 리스트의 시작 위치는 1이기 때문에 시작 위치 이전(pos < 1)에는 노드 존재하지 않음
    // 연결 리스트가 비어있는 상태(*start == NULL)에서는 노드를 삭제할 수 없음
    if(pos < 1 || *start == NULL)
        puts("노드 삭제 불가능");
    // 첫 번째 노드를 삭제할 때
    else if(pos == 1){
        Node *temp = *start;
        *start = (*start)->next;
        free(temp);
    }
    // 첫 번째 노드 이후의 노드를 삭제할 때
    else{
        Node *temp = *start;

        for(; temp && pos > 1; --pos)
            temp = temp->next;

        // pos의 위치가 연결 리스트보다 긴 경우
        if(temp == NULL)
            puts("노드 삭제 불가능");
        else{
            temp->prev->next = temp->next;
            // 삭제할 노드가 리스트의 맨 끝 노드가 아닐 때
            if(temp->next)
                temp->next->prev = temp->prev;
            free(temp);
        }
    }
}

/* 주어진 데이터를 저장하고 있는 노드 삭제
    - value: 주어진 데이터
    - start: 연결 리스트의 시작 노드 */
void deleteByValue(int value, Node **start)
{
    // 빈 리스트인 경우 삭제 작업 불가능
    if(*start == NULL)
        puts("노드 삭제 불가능");
    // 빈 리스트가 아닐 때, 해당 value를 저장하고 있는 노드 찾기
    else{
        Node *temp = *start;

        for(; temp && temp->data != value; temp = temp->next)
            ;

        // value를 저장하고 있는 노드가 존재하지 않는 경우
        if(temp == NULL)
            puts("노드 삭제 불가능");
        // value를 저장한 노드(== temp)를 발견한 경우
        else{
            temp->prev->next = temp->next;
            // 삭제하고자 하는 노드가 마지막 노드가 아닌 경우
            // 만약 마지막 노드라면, 삭제하는 노드 다음의 노드에 대한 포인터 수정은 할 필요가 없음
            if(temp->next != NULL)
                temp->next->prev = temp->prev;

            free(temp);
        }
    }
}

/* 연결 리스트를 시작 지점부터 순회하는 함수
    - x: 연결 리스트의 시작 지점*/
void traverse(Node *x)
{
    int cnt = 1;

    // x != NULL이 아닌 동안 반복 (연결 리스트가 끝나기 전까지 반복)
    while(x){
        fprintf(stdout, "%d번째: %-3d ", cnt++, x->data);
        x = x->next;
    }
    fprintf(stdout, "\n");
}

/* 연결 리스트를 끝 지점부터 순회하는 함수
    - x: 연결 리스트의 시작 지점*/
void traverseInReverse(Node *x)
{
    int cnt = 1;

    // 리스트 내의 노드 개수 세기 (리스트의 가장 마지막으로 이동)
    while(x->next){
        x = x->next;
        cnt++;
    }

    while(x){
        fprintf(stdout, "%d번째: %-3d ", cnt--, x->data);
        x = x->prev;
    }
    fprintf(stdout, "\n");
}

int menu(void)
{
    int choice;

    puts("[1] 연결 리스트의 끝 지점에 데이터 삽입");
    puts("[2] 연결 리스트의 시작 지점에 데이터 삽입");
    puts("[3] 특정 위치에 데이터 삽입");
    puts("[4] 특정 위치의 데이터 삭제");
    puts("[5] 특정 데이터 자체를 삭제");
    puts("[6] 연결 리스트를 시작 지점부터 출력");
    puts("[7] 연결 리스트를 끝 지점부터 출력");
    puts("[8] 프로그램 종료");

    fprintf(stdout, ">> ");
    scanf("%d", &choice);

    return choice;
}