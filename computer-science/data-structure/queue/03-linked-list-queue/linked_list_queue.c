#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct queueNode{
    Element item;
    struct queueNode *link;
}queueNode;

// 큐를 나타내기 위한 구조체
typedef struct queueType{
    queueNode *front; // 큐의 맨 앞(첫번째) 원소
    queueNode *rear; // 큐의 맨 끝(마지막) 원소
}queueType;

void error(char *message); // 에러 처리
void init(queueType *q); // 생성된 큐 초기화
int queueEmpty(queueType *q); // 큐가 비어있으면 1, 그렇지 않으면 0 반환
void addQueue(queueType * q, Element item); // 큐에 원소를 삽입
Element deleteQueue(queueType * q); // 큐에서 원소 삭제
Element peek(queueType *q); // 큐의 맨 앞 원소를 확인

int main(int argc, char *argv[])
{
    // 새로운 큐 하나 생성 및 초기화
    queueType q;
    init(&q);

    // 생성한 큐에 원소 삽입
    addQueue(&q, 1);
    addQueue(&q, 2);
    addQueue(&q, 3);

    // 큐에서 원소 하나씩 삭제하며, 삭제한 원소 출력
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));
    fprintf(stdout, "deleteQueue() = %d\n", deleteQueue(&q));

    return 0;
}

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(queueType *q)
{
    q->front = q->rear = NULL;
}

int queueEmpty(queueType *q)
{
    return (q->front == NULL);
}

void addQueue(queueType * q, Element item)
{
    queueNode *temp = (queueNode *)malloc(sizeof(queueNode));

    if(temp == NULL){
        error("메모리를 할당할 수 없습니다.\n");
    }
    else{
        // 새로 생성한 노드 초기화
        temp->item = item;
        temp->link = NULL;

        // 큐가 비어있는 상태라면, front와 rear는 모두 새로 생성한 노드를 가리킴
        if(queueEmpty(q)){
            q->front = temp;
            q->rear = temp;
        }
        else{
            q->rear->link = temp;
            q->rear = temp;
        }
    }
}

Element deleteQueue(queueType * q)
{
    queueNode *temp = q->front;
    Element item;

    // 큐가 비어있는 상태라면, 에러 처리
    if(queueEmpty(q))
        error("큐가 비어있습니다.\n");

    item = temp->item;
    q->front = q->front->link;
    // 삭제할 원소가 큐에서 남은 마지막 원소라면, rear의 값도 조정해줘야 함
    if(q->front == NULL)
        q->rear = NULL;
    free(temp);

    return item;
}

Element peek(queueType *q)
{
    if(queueEmpty(q))
        error("큐가 비어있습니다.\n");

    return q->front->item;
}