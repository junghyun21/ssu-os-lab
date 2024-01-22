#include <stdio.h>
#include <stdlib.h>

// 이중 연결 리스트의 노드 구조체
struct Node{
    int data;
    struct Node* llink;
    struct Node* rlink;
};
typedef struct Node Node;

void insertNode(Node **head, Node *prevNode, int data);

int main()
{
    Node *head = NULL;
    Node *currentNode;

    // 리스트 초기화: fisrtNode 라는 노드를 하나 가지고 있는 연결 리스트
    Node *firstNode = (Node*)malloc(sizeof(Node));
    firstNode->data = 1;
    firstNode->llink = NULL;
    firstNode->rlink = NULL;

    head = firstNode;

    // firstNode 뒤에 새로운 노드 삽입
    insertNode(&head, firstNode, 2);
    insertNode(&head, firstNode, 3);
    insertNode(&head, firstNode, 4);
    insertNode(&head, firstNode, 5);

    // 리스트 출력
    currentNode = head;
    while(currentNode != NULL){
        printf("%d ", currentNode->data);
        currentNode = currentNode->rlink;
    }
    printf("\n");

    return 0;
}

/* 이중 연결 리스트에 노드를 삽입하는 함수
    - head: 연결 리스트의 첫 번째 노드
    - prevNode: 삽입할 위치의 앞 노드
    - data: 삽입할 노드에 저장될 데이터*/
void insertNode(Node **head, Node *prevNode, int data)
{
    // 새로운 노드 생성
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    // 만약 새로운 노드가 리스트의 첫 번째 노드라면, 헤더 업데이트
    if(*head == NULL || prevNode == NULL){ // || prevNode == *head) 
        newNode->llink = NULL;
        newNode->rlink = NULL;
       
        *head = newNode;
    }
    else{
        // 새로운 노드의 연결 설정
        newNode->llink = prevNode;
        newNode->rlink = prevNode->rlink;

        // 이전 노드와 다음 노드의 연결 설정
        prevNode->rlink = newNode;
        if(newNode->rlink != NULL)
            newNode->rlink->llink = newNode;
    }
}