#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
#define ERROR_CODE -1

typedef struct Task{
    int id; // 작업 ID
    char description[100]; // 작업 설명
}Task;

Task queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

void queueFull(); // 큐가 가득 찼을때 호출되어, 오류 메시지 출력 및 프로그램 종료
Task queueEmpty(); // 큐가 비어있을 때 호출
void addQueue(Task task); // 큐에 원소 삽입, rear 순환적으로 갱신
Task deleteQueue(); // 큐 내의 원소 삭제, front 순환적으로 갱신
void printQueue(); // 큐를 순환하며 원소 출력

int main()
{
    int choice;
    while(1){
        printf("1. Add Task\n2. Process Task\n3. Exit\n> Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // 작업을 추가하는 경우
            case 1:
                // 큐가 가득 찬 상태가 아닐 때에 작업 추가 진행
                if((rear + 1) % MAX_QUEUE_SIZE == front){
                    printf("Queue is full. Cannot add a new task\n");
                }
                else{
                    Task newTesk;
                    newTesk.id = rear + 2; // 작업의 고유한 이름 설정
                    printf("> Enter task description: ");
                    scanf(" %[^\n]", newTesk.description); // 개행문자가 나올 때까지 문자 입력받음
                    addQueue(newTesk);
                    printf("Task added successfully.\n");
                }
                break;

            // 작업을 진행(삭제)하는 경우
            case 2:
                // 큐가 비어있는 상태가 아닐 때에 작업 삭제 진행
                if(rear == front){
                    printf("Queue is empty. No task process.\n");
                }
                else{
                    Task task = deleteQueue();
                    printf("Processing Task...\n");
                    printf("Task ID: %d\n", task.id);
                    printf("Task processed successfully.\n");
                }
                break;

            // 프로그램 종료
            case 3:
                printf("Exiting the program.\n");
                return 0;

            // 잘못된 값을 입력한 경우
            default:
                printf("Invaild choice. Please try again.\n");
                break;

        }

        printQueue();
    }

    return 0;
}

void queueFull()
{
    fprintf(stderr, "Queue is full, Cannot add element\n");
    exit(EXIT_FAILURE);
}

Task queueEmpty()
{
    Task emptyTask;
    emptyTask.id = ERROR_CODE;
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    return emptyTask;
}

void addQueue(Task task)
{
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if(rear == front)
        queueFull();
    queue[rear] = task;
}

Task deleteQueue()
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
    fprintf(stdout, "Queue: \n");

    // 큐가 비어있을 때
    if(front == rear){
        printf("Empty\n");
        return;
    }

    i = (front + 1) % MAX_QUEUE_SIZE;
    while(1){
        printf("Take ID: %d\n", queue[i].id);
        printf("Description: %s\n", queue[i].description);

        if(i == rear)
            break;

        i = (i + 1) % MAX_QUEUE_SIZE;
    }
}