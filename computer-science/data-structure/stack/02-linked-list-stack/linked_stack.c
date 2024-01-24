#include <stdio.h>
#include <stdlib.h>

typedef struct Element{
    int key;
}Element;

typedef struct Stack *stackPointer;
typedef struct Stack{
    Element data;
    stackPointer link;
}Stack;

void push(stackPointer *top, Element item);
int pop(stackPointer *top, Element *item);
int peek(stackPointer top, Element *item);
void printStack(stackPointer top);

int main()
{
    stackPointer top = NULL; // 연결 리스트 기반의 스택 하나 생성
    Element data1, data2, data3, data4;
    Element temp;

    // 각 요소들의 데이터 필드 초기화
    data1.key = 10;
    data2.key = 20;
    data3.key = 30;
    data4.key = 40;

    // 요소 삽입
    push(&top, data1);
    fprintf(stdout, "push: %4d\n", data1.key);
    push(&top, data2);
    fprintf(stdout, "push: %4d\n", data2.key);
    push(&top, data3);
    fprintf(stdout, "push: %4d\n", data3.key);
    push(&top, data4);
    fprintf(stdout, "push: %4d\n", data4.key);

    // 스택 출력
    printStack(top);

    // 스택의 맨 위에 위치한 원소(top) 확인
    peek(top, &temp);
    fprintf(stdout, "peek: %4d\n", temp.key);

    // 요소 삭제
    pop(&top, &temp);
    fprintf(stdout, "pop: %4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop: %4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop: %4d\n", temp.key);
    pop(&top, &temp);
    fprintf(stdout, "pop: %4d\n", temp.key);

    // 스택 출력
    printStack(top);

    return 0;
}

// 스택의 top에 원소 item 삽입
void push(stackPointer *top, Element item)
{
    stackPointer newNode;
    newNode = (stackPointer)malloc(sizeof(*newNode));
    if(newNode == NULL){
        fprintf(stderr, "메모리 할당 에러\n");
        exit(1);
    }

    newNode->data = item;
    newNode->link = *top;
    *top = newNode;
}

// 스택의 top에 있는 원소 삭제
// 삭제한 원소는 item에 저장
// 성공적으로 삭제 시 1 리턴, 실패 시 0 리턴
int pop(stackPointer *top, Element *item)
{
    stackPointer temp = *top;

    item->key = -1; // 삭제된 key라는 뜻

    // temp == NULL이면 빈 리스트
    if(!temp)
        return 0;

    *item = temp->data;
    *top = temp->link;
    free(temp);

    return 1;
}

// 스택의 맨 위 원소(top)를 확인하는 함수
// 맨 위의 원소는 item에 저장
// 성공적으로 확인 시 1 리턴, 실패 시 0 리턴
int peek(stackPointer top, Element *item)
{
    // 빈 스택인 경우
    if(top == NULL)
        return 0;
    else{
        *item = top->data;
        return 1;
    }
}

// 스택 출력
void printStack(stackPointer top)
{
    printf("stack: ");

    // 빈 스택인 경우
    if(top == NULL)
        printf("empty\n");
    else{
        for(; top; top = top->link)
            printf("%4d ", top->data.key);
        printf("\n");
    }
}