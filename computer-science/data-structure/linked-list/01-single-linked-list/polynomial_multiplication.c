#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x, y) ((x) < (y)) ? -1 : (((x) == (y)) ? 0 : 1)

// 연결리스트 노드의 구조
typedef struct Node{
    int coef; // 계수(coefficient)
    int expon; // 지수(exponent)
    struct Node *next;
}Node;

// 연결리스트의 헤더 (헤드노드는 연결리스트의 노드와 동일할 필요가 없음)
typedef struct Header{
    int length;
    Node *head;
    Node *tail;
}Header;

void init(Header *list);
void insertNodeLast(Header *list, int coef, int expon);
void polyMul(Header *resultList, Header *list1, Header *list2);
void polyDelete(Header *list);
void polyPrint(Header list);

int main()
{
    Header list1, list2, list3;

    // 연결 리스트의 헤드 노드 초기화
    init(&list1);
    init(&list2);
    init(&list3);

    // 다항식 1 생성
    insertNodeLast(&list1, 3, 3);
    insertNodeLast(&list1, 2, 2);
    insertNodeLast(&list1, 2, 1);

    // 다항식 2 생성
    insertNodeLast(&list2, 8, 3);
    insertNodeLast(&list2, 3, 2);
    insertNodeLast(&list2, 10, 0);

    // 다항식 3 = 다항식 1 * 다항식 2
    polyMul(&list3, &list1, &list2);

    fprintf(stdout, "A의 다항식: ");
    polyPrint(list1);

    fprintf(stdout, "B의 다항식: ");
    polyPrint(list2);

    fprintf(stdout, "결과 다항식: ");
    polyPrint(list3);

    // 다항식 모두 삭제
    polyDelete(&list1);
    polyDelete(&list2);
    polyDelete(&list3);

    return 0;
}

// 연결 리스트 초기화 (헤드 노드 초기화)
void init(Header *list)
{
    list->length = 0;
    list->head = list->tail = NULL;
}

// 새로운 노드를 연결 리스트의 마지막에 삽입
void insertNodeLast(Header *list, int coef, int expon)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if(newNode == NULL){
        fprintf(stderr, "메모리 할당 에러\n");
        exit(1);
    }
        
    newNode->coef = coef;
    newNode->expon = expon;
    newNode->next = NULL;

    // 빈 리스트일 때
    if(list->tail == NULL){
        list->head = list->tail = newNode;
    }
    // 기존에 다른 노드가 있었을 때
    else{
        list->tail->next = newNode;
        list->tail = newNode;
    }

    ++list->length;
}

// 두 개의 다항식의 곱셈 결과를 새로운 연결 리스트에 저장
void polyMul(Header *resultList, Header *list1, Header *list2)
{
    Node *a = list1->head;
    Node *b = list2->head;
    int *multiply, i, highest;

    // 각 다항식은 내림차순으로 정리되어 있으므로,
    // 각 다항식의 첫 항을 곱해주면 최고차항을 알 수 있음
    highest = a->expon * b->expon;

    // 최고 차항의 지수 크기만큼 동적 배열 할당
    // calloc(): 메모리를 할당하고 모든 비트를 0으로 초기화
    multiply = (int *)calloc(highest + 1, sizeof(int));

    // 각 항들 곱해주기
    while(a != NULL){
        if(b != NULL){
            if(multiply[a->expon + b->expon] == 0)
                multiply[a->expon + b->expon] = a->coef * b->coef;
            else
                multiply[a->expon + b->expon] += a->coef * b->coef;

            b = b->next;
        }
        else{
            a = a->next;
            b = list2->head;
        }
    }

    // 각 지수에 대응되는 배열 index에 0이 아닌 숫자가 있으면 결과식에 삽입
    for(i = highest; i >= 0; --i)
        if(multiply[i] != 0)
            insertNodeLast(resultList, multiply[i], i);
}

// 연결 리스트 전체 삭제
void polyDelete(Header *list)
{
    Node *temp = list->head;
    Node *deletedNode;

    // temp가 마지막 노드일 때까지 반복
    while(temp->next != NULL){
        deletedNode = temp;
        temp = deletedNode->next;
        list->head = temp;

        free(deletedNode);
    }
    free(temp);
}

// 다항식 출력
void polyPrint(Header list)
{
    Node *p = list.head;

    for(; p; p = p->next){
        fprintf(stdout, "%dX^%d", p->coef, p->expon);
        // 마지막 노드가 아니라면
        if(p->next != NULL)
            fprintf(stdout, " + ");
    }
    fprintf(stdout, "\n");
}