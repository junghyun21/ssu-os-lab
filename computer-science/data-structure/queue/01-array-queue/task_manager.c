#include <stdio.h>

#define MAX_QUEUE_SIZE 100

typedef struct Task{
    int id; // 작업 ID
    char description[100]; // 작업 설명
}Task;

Task queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int isQueueFull();
int isQueueEmpty();
void enQueue(Task task);
Task deQueue();
void printTask(Task task);

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
                if(!isQueueFull()){
                    Task newTesk;
                    newTesk.id = rear + 2; // 작업의 고유한 이름 설정
                    printf("> Enter task description: ");
                    scanf(" %[^\n]", newTesk.description); // 개행문자가 나올 때까지 문자 입력받음
                    enQueue(newTesk);
                    printf("Task added successfully.\n");
                }
                else{
                    printf("Queue is full. Cannot add a new task.\n");
                }
                break;

            // 작업을 진행(삭제)하는 경우
            case 2:
                // 큐가 비어있는 상태가 아닐 때에 작업 삭제 진행
                if(!isQueueEmpty()){
                    Task task = deQueue();
                    printf("Processing Task...\n");
                    printTask(task);
                    printf("Task processed successfully.\n");
                }
                else{
                    printf("Queue is empty. No task process.\n");
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
    }

    return 0;
}

int isQueueFull()
{
    return rear == MAX_QUEUE_SIZE - 1;
}

int isQueueEmpty()
{
    return front == rear;
}

void enQueue(Task task)
{
    if(isQueueFull()){
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue[++rear] = task;
}

Task deQueue()
{
    if(isQueueEmpty()){
        printf("Queue is empty. Cannot dequeue.\n");
        Task emptyTask;
        emptyTask.id = -1; // 비어있음을 나타내는 특정 값을 저장하여 반환
        return emptyTask;
    }
    return queue[++front];
}

void printTask(Task task)
{
    printf("Take ID: %d\n", task.id);
    printf("Description: %s\n", task.description);
}