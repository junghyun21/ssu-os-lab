#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

Node *createNode(int data);
void insertNode(Node **head, int data);
// void deleteByValue(Node **head, int value);
void printCircularList(Node *head);

int main()
{
    Node *head = NULL; // 빈 원형 연결 리스트 생성

    // 노드 3개(1, 4, 7)를 삭제한 원형 연결 리스트 출력
    printf("빈 원형 연결 리스트 출력: ");
    printCircularList(head);

    // 노드 추가
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    insertNode(&head, 4);
    insertNode(&head, 5);
    insertNode(&head, 6);
    insertNode(&head, 7);

    // 원형 연결 리스트 출력
    printf("노드를 7개 추가한 원형 연결 리스트 출력: ");
    printCircularList(head);

    // // 노드 삭제
    // deleteByValue(&head, 1);
    // printCircularList(head);
    // deleteByValue(&head, 4);
    // printCircularList(head);
    // deleteByValue(&head, 7);
    // printCircularList(head);
    // deleteByValue(&head, 10);
    // printCircularList(head);
    
    // // 노드 3개(1, 4, 7)를 삭제 & 존재하지 않는 노드를 삭제한 원형 연결 리스트 출력
    // printf("노드 삭제 후 원형 연결 리스트 출력: ");
    // printCircularList(head);

    return 0;
}

/* 새로운 노드를 생성하고 노드 내 데이터 값을 초기화하는 함수
    - data: 노드 내 저장될 데이터 */
Node *createNode(int data)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

/* 연결 리스트의 첫 번째 위치(head가 가리키는 곳)에 삽입하는 함수
    - head: 연결 리스트의 시작 노드
    - data: 새롭게 생성되어 저장될 노드에 저장될 데이터 */
// 기존에 head가 가리키던 노드는 맨 뒤로 이동
void insertNode(Node **head, int data)
{
    Node *newNode = createNode(data);

    // 빈 리스트인 경우, 자기 자신을 가리킴
    if(*head == NULL){
        *head = newNode;
        newNode->next = newNode;
    }
    // 빈 리스트가 아닌 경우, 첫 번째 위치에 노드 삽입
    // 기존의 첫 번째 위치의 노드는 맨 뒤로 이동(*head(newNode)를 가리키도록)
    else{
        newNode->next = (*head)->next;
        (*head)->next = newNode;
        *head = newNode;
    }
}

// /* 주어진 값을 가지고 있는 노드 삭제 
//     - value: 주어진 값 */
// void deleteByValue(Node **head, int value)
// {   
//     // 빈 리스트이면 노드 삭제 불가
//     if(*head == NULL)
//         fprintf(stdout, "노드 삭제 불가\n");
//     else{
//         Node *temp = *head; // 삭제할 노드
//         Node *prev = temp; // 삭제할 노드의 앞 노드

//         // 원형 리스트는 NULL이 없음
//         while(temp->data != value){
//             prev = temp;
//             temp = temp->next;

//             // 한 바퀴 다 돌았는데 value와 동일한 데이터를 가지는 노드를 찾지 못한 경우
//             if(temp == *head){
//                 fprintf(stdout, "%d를 저장한 노드는 존재하지 않습니다.\n", value);
//                 return;
//             }
//         }

//         fprintf(stdout, "%d를 저장한 노드 삭제\n", value);

//         // 삭제할 노드(temp)가 시작 노드(*head)인 경우
//         if(temp == *head){
//             // 리스트 내에 노드가 하나만 있었던 경우
//             if(temp->next == *head){
//                 free(temp);
//                 *head = NULL;
//             }
//             // 리스트 내에 노드기 여러 개 있었던 경우
//             // head를 다음 노드로 이동
//             else{
//                 *head = temp->next;
//                 prev->next = *head;
//                 free(temp);
//             }
//         }
//         // 삭제할 노드(temp)가 시작 노드(*head)가 아닌 경우
//         else{
//             prev->next = temp->next;
//             free(temp);
//         }
//     }
// } 

/* 원형 연결 리스트를 출력하는 함수
    - head: 연결 리스트의 시작 지점 */
void printCircularList(Node *head)
{
    if(head == NULL)
        fprintf(stdout, "리스트는 비어있습니다.\n");
    else{
        Node *curr = head->next;
        do{
            fprintf(stdout, "%d -> ", curr->data);
            curr = curr->next;
        }while(curr != head->next);

        fprintf(stdout, "...\n");
    }
}