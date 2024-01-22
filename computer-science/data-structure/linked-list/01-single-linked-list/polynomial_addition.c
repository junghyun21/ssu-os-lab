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
void polyAdd(Header *resultList, Header list1, Header list2);
void polyDelete(Header *list);
void polyPrint(Header list);

int main()
{
    Header list1, list2, list3;

    // 연결 리스트의 헤드 노드 초기화
    init(&list1);
    init(&list2);
    init(&list3);

    // 다항식 1 생성: 3x^5 - 2x^3 + 2x^2 + 7
    insertNodeLast(&list1, 3, 5);
    insertNodeLast(&list1, 2, 3);
    insertNodeLast(&list1, 2, 2);

    // 다항식 2 생성: 8x^7 + 4x^3 - 3x
    insertNodeLast(&list2, 8, 6);
    insertNodeLast(&list2, 3, 4);
    insertNodeLast(&list2, 10, 2);

    // 다항식 3 = 다항식 1 + 다항식 2
    polyAdd(&list3, list1, list2);

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

// 두 개의 다항식의 덧셈 결과를 새로운 연결 리스트에 저장
void polyAdd(Header *resultList, Header list1, Header list2)
{
    Node *a, *b;
    int sum;

    a = list1.head;
    b = list2.head;

    // a와 b가 모두 NULL이 아닌 동안 반복
    while(a && b){
        switch (COMPARE(a->expon, b->expon))
        {
            case -1: // a->expon < b->expon
                insertNodeLast(resultList, b->coef, b->expon);
                b = b->next;
                break;
            
            case 0: // a->expon == b->expon
                sum = a->coef + b->coef;
                if(sum != 0)
                    insertNodeLast(resultList, sum, a->expon);
                
                a = a->next;
                b = b->next;
                break;

            case 1: // a->expon > b->expon
                insertNodeLast(resultList, a->coef, a->expon);
                a = a->next;
        }
    }

    // 하나의 다항식이 먼저 끝나면, 님은 다항식을 모두 결과 다항식의 값으로 더함
    for(; a != NULL; a = a->next)
        insertNodeLast(resultList, a->coef, a->expon);

    for(; b != NULL; b = b->next)
        insertNodeLast(resultList, b->coef, b->expon);
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