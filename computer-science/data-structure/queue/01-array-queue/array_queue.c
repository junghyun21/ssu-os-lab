#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

// 큐 내에 저장될 원소
typedef struct Element{
    int key;
}Element;

// 큐 생성 및 front와 reat 초기화 -> 현재 큐는 비어있는 상태
Element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int isQueueFull(); // 큐가 가득 차있는 상태인지 검사
int isQueueEmpty(); // 큐가 비어있는 상태인지 검사
void enQueue(Element item); // 큐에 원소 추가
Element deQueue(); // 큐 내의 원소 삭제

int main()
{
    Element item, removedItem;

    // 원소 초기화
    item.key = 26;

    // 원소 삽입
    enQueue(item);
    printf("Enqueued: %d\n", item.key);

    // 원소 삭제
    removedItem = deQueue();
    printf("Dequeued: %d\n", removedItem.key);

    return 0;
}

int isQueueFull()
{
    // 큐의 앞부분은 비어있는데, 큐가 가득 차있다고 오해받을 수 있음
    return rear == MAX_QUEUE_SIZE - 1;
}

int isQueueEmpty()
{
    // rear와 front가 동일한 경우는 큐가 비어있는 상태밖에 없음
    // rear == -1 && front == -1
    return rear == front;
}

void enQueue(Element item)
{
    // 큐에 원소 삽입하기 전에, 큐가 가득 차있는 상태인지 검사
    if(isQueueFull()){
        printf("Queue is full. Cannot enqueue.\n");
        exit(1);
    }
    queue[++rear] = item;
}

Element deQueue()
{
    // 큐 내 원소 삭제 전에, 큐가 비어있는 상태인지 검사
    if(isQueueEmpty()){
        printf("Queue is Empty. Cannot dequeue.\n");
        exit(1);
    }
    return queue[++front];
}