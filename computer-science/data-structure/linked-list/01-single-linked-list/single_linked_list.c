#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
    int data;
    listPointer link;
}listNode;
/*
typedef struct{
    int data;
    listPointer link;
}listNode;

위와 같이 구조체 선언 시, 불완전한 클래스 형식에 대한 포인터는 사용할 수 없다는 오류 문구 뜸
*/

listPointer createNode(int data, listPointer link);
void insertHead(listPointer *head, listPointer newNode);
void insert(listPointer *head, listPointer x, listPointer newNode);
void delete(listPointer *head, listPointer trail, listPointer removeNode);
listPointer search(listPointer head, int data);
void printList(listPointer head);

int main()
{
    listPointer head = NULL; // 초기 연결 리스트의 시작 노드는 NULL 상태 (연결 리스트가 비어있음)
    listPointer temp = NULL;

    // 노드 5개를 생성하여 헤더 위치(맨 앞)에 삽입 
    insertHead(&head, createNode(10, NULL));
    insertHead(&head, createNode(20, NULL));
    insertHead(&head, createNode(30, NULL));
    insertHead(&head, createNode(40, NULL));
    insertHead(&head, createNode(50, NULL));

    fprintf(stdout, "노드 5개를 생성하여 헤더 위치에 삽입: ");
    printList(head);

    // 데이터가 30인 노드 찾기
    temp = search(head, 30);

    // 새로 생성한 노드를 데이터가 30인 노드 뒤에 삽입하기
    insert(&head, temp, createNode(25, NULL));

    fprintf(stdout, "데이터가 30인 노드 뒤에 새로 생성한 노드 삽입: ");
    printList(head);

    // 데이터가 30인 노드 다음의 노드 삭제하기
    delete(&head, temp, temp->link);

    fprintf(stdout, "데이터가 30인 노드 뒤의 노드 삭제: ");
    printList(head);

    // 첫 번째 노드 삭제
    delete(&head, NULL, head);

    fprintf(stdout, "첫 번째 노드 삭제: ");
    printList(head);

    return 0;
}

/* 새로운 노드 생성
    - data: 노드 내 저장할 데이터
    - link: 해당 노드가 가리키는 다음 노드 */
listPointer createNode(int data, listPointer link)
{
    listPointer newNode = (listPointer)malloc(sizeof(listNode));

    if(newNode == NULL){
        fprintf(stderr, "메모리 할당 에러\n");
        exit(1);
    }

    newNode->data = data;
    newNode->link = link;

    return newNode;
}

/* 새로운 노드를 리스트의 헤더에 삽입
    - head: 해당 리스트의 첫 번째 노드
    - newNode: 삽입할 노드 */
void insertHead(listPointer *head, listPointer newNode)
{
    newNode->link = *head;
    *head = newNode;
}

/* 새로운 노드를 특정 노드 뒤에 삽입
    - head: 해당 리스트의 첫 번째 노드
    - x: 삽입할 노드의 앞에 위치한 노드
    - newNode: x 노드 뒤에 삽입될 노드 */
void insert(listPointer *head, listPointer x, listPointer newNode)
{
    // head != NULL : 특정 x 노드 뒤에 새로운 노드 삽입
    if(head){
        newNode->link = x->link;
        x->link = newNode;
    }
    // head == NULL : 헤더에 새로운 노드 삽입 (빈 리스트일 때)
    else{
        newNode->link = NULL;
        *head = newNode;
    }
}

/* 노드 삭제
    - head: 해당 리스트의 첫 번째 노드
    - trail: 삭제될 노드의 선행 노드
    - removeNode: 삭제될 노드 */
void delete(listPointer *head, listPointer trail, listPointer removeNode)
{
    // trail != NULL: 삭제될 노드는 첫 번째 노드가 아님
    if(trail)
        trail->link = removeNode->link;
    // trail == NULL: 삭제될 노드는 첫 번째 노드임
    else
        *head = (*head)->link;

    free(removeNode);
}

/* 특정 데이터를 가지고 있는 노드를 탐색
    - head: 해당 리스트의 첫 번째 노드
    - data: 해당 데이터를 가지고 있는 노드 반환 */
listPointer search(listPointer head, int data)
{
    // head NULL일 때까지 반복
    for(; head; head = head->link)
        if(head->data == data)
            return head;
    
    return NULL;
}

/* 리스트 출력 
    - head: 해당 리스트의 첫 번째 노드 */
void printList(listPointer head)
{
    for(; head; head = head->link)
        fprintf(stdout, "%4d ", head->data);
    
    fprintf(stdout, "\n");
}