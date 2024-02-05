#include <stdio.h>
#include <stdlib.h>

// 원형 큐 구조체 정의 (이를 통해 여러 개의 큐 생성 가능)
typedef struct CircularQueue{
    int *data; // 데이터 배열
    int front; // 큐의 앞 포인터
    int rear; // 큐의 뒷 포인터
    int size; // 큐의 현재 크기
    int capacity; // 큐의 최대 용량
}CircularQueue;

CircularQueue *initializeQueue(int capacity); // 원형 큐 초기화 함수
int isEmpty(CircularQueue *queue); // 큐가 비어있는지 확인하는 함수
int isFull(CircularQueue *queue); // 큐가 가득찼는지 확인하는 함수
void enQueue(CircularQueue *queue, int item); // 큐에 원소를 삽입하는 함수
int deQueue(CircularQueue *queue); // 큐에서 원소를 삭제하고 반환하는 함수
void displayQueue(CircularQueue *queue); // 큐를 출력하는 함수

int main()
{
    // 큐의 최대 용량이 5인 원형 큐를 생성하고 초기화하는 함수
    CircularQueue *queue = initializeQueue(5);

    // 큐에 데이터 삽입
    enQueue(queue, 1);
    enQueue(queue, 2);
    enQueue(queue, 3);
    displayQueue(queue);

    // 큐에서 데이터 삭제
    deQueue(queue);
    displayQueue(queue);

    // 큐에 데이터 삽입
    enQueue(queue, 4);
    enQueue(queue, 5);
    displayQueue(queue);

    // 큐가 가득 찼으므로, 데이터 삽입 시에 큐가 확장됨
    enQueue(queue, 6);
    enQueue(queue, 7);
    enQueue(queue, 8);
    displayQueue(queue);

    free(queue->data);
    free(queue);
    
    return 0;
}

CircularQueue *initializeQueue(int capacity)
{
    CircularQueue *queue = (CircularQueue *)malloc(sizeof(CircularQueue));
    queue->data = (int *)malloc(capacity * sizeof(int));
    queue->front = 0; // 가장 먼저 들어온 원소를 가리키는 인덱스
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;

    return queue;
}

int isEmpty(CircularQueue *queue)
{
    return queue->size == 0;
}

int isFull(CircularQueue *queue)
{
    return queue->size == queue->capacity;
}

void enQueue(CircularQueue *queue, int item)
{
    // 큐가 가득 찬 경우, 큐의 확장이 필요함
    if(isFull(queue)){
        int newCapacity = queue->capacity * 2;
        int *newData = (int *)malloc(newCapacity * sizeof(int));
        int i, j;

        // 기존 큐의 데이터를 새로운 큐로 복사
        for(i = 0, j = queue->front; i < queue->size; i++){
            newData[i] = queue->data[j];
            j = (j + 1) % queue->capacity; 
        }

        // 이전의 데이터 배열을 해제하고, 새로운 데이터 배열을 가리킴
        free(queue->data);
        queue->data = newData;
        queue->front = 0;
        queue->rear = queue->size - 1;
        queue->capacity = newCapacity;
    }

    // 데이터 삽입
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->size++;
}

int deQueue(CircularQueue *queue)
{
    // 에러 처리 또는 다른 방법으로 처리 가능
    if(isEmpty(queue)){
        printf("큐가 비어있음\n");
        return -1;
    }

    // 데이터 삭제
    int item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return item;
}

void displayQueue(CircularQueue *queue)
{
    int i, j;
    
    printf("Queue: ");
    for(i = 0, j = queue->front; i < queue->size; i++){
        printf("%d ", queue->data[j]);
        j = (j + 1) % queue->capacity;
    }
    printf("\n");
}