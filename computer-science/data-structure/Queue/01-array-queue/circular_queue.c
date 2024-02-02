#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
#define ERROR_CODE -1

typedef struct Element{
    int key;
}Element;

Element queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

void queueFull(); // 큐가 가득 찼을때 호출되어, 오류 메시지 출력 및 프로그램 종료
Element queueEmpty(); // 큐가 비어있을 때 호출
void addQueue(Element item); // 큐에 원소 삽입, rear 순환적으로 갱신
Element deleteQueue(); // 큐 내의 원소 삭제, front 순환적으로 갱신
void printQueue(); // 큐를 순환하며 원소 출력

int main()
{
    Element item1, item2, item3;

    // 원소 초기화
    item1.key = 10;
    item2.key = 20;
    item3.key = 30;
    
    // 원소 삽입
    addQueue(item1);
    printQueue();
    
    addQueue(item2);
    printQueue();
    
    addQueue(item3);
    printQueue();

    // 원소 삭제
    deleteQueue();
    printQueue();

    deleteQueue();
    printQueue();

    deleteQueue();
    printQueue();

    // 원소 추가
    addQueue(item1);
    printQueue();
    
    addQueue(item2);
    printQueue();
    
    addQueue(item3);
    printQueue();

    addQueue(item1);
    printQueue();
    
    addQueue(item2);
    printQueue();
    
    return 0;
}

void queueFull()
{
    fprintf(stderr, "Queue is full, Cannot add element\n");
    exit(EXIT_FAILURE);
}

Element queueEmpty()
{
    Element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    return temp;
}

void addQueue(Element item)
{
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if(rear == front)
        queueFull();
    queue[rear] = item;
}

Element deleteQueue()
{
    if(front == rear)
        queueEmpty();
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

void printQueue()
{
    int i;

    fprintf(stdout, "front: %d, rear: %d\n", front, rear);
    fprintf(stdout, "Queue: ");

    // 큐가 비어있을 때
    if(front == rear){
        printf("\n");
        return;
    }

    i = front;
    while(1){
        i = (i + 1) % MAX_QUEUE_SIZE;
        fprintf(stdout, "[%d]%d ", i, queue[i].key);
        if(i == rear)
            break;
    }
    fprintf(stdout, "\n" );
}
