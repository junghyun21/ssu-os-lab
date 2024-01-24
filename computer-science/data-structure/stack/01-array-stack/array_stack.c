#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_CODE -1

// stack의 원소 정의
typedef struct Element{
    int key;
} Element;

Element *stack; // 동적 배열을 이용한 스택의 구현
int capacity = 1; // 스택의 최대 크기
int top = -1; // 초기에는 스택이 비어있는 상태

void stackFull();
Element stackEmpty();
int isFull();
int isEmpty();
void push(Element item);
Element pop();
void printStack();

int main(int argc, char *argv[])
{
    Element item1, item2, item3;

    stack = (Element *)malloc(sizeof(Element));

    item1.key = 10;
    item2.key = 20;
    item3.key = 30;

    printStack(); // 스택이 비어있는 상태

    push(item1); // item 1 삽입
    printStack();

    push(item2); // item 2 삽입
    printStack();

    push(item3); // item 3 삽입
    printStack();

    pop(); // item 3 삭제
    printStack();

    pop(); // item 2 삭제
    printStack();

    pop(); // item 1 삭제
    printStack();

    return 0;
}

// 스택이 가득 찬 경우에 원소를 삽입하고자 함 -> 스택의 용량 2배 늘리기
void stackFull()
{
    capacity *= 2;
    stack = realloc(stack, capacity * sizeof(*stack)); // sizeof(*stack): 스택이 가리키는 타입의 사이즈 == sizeof(Element)
}

// 스택이 비어있는 경우에 원소를 삭제하고자 함 -> 오류 코드 반환
Element stackEmpty()
{
    Element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Stack is empty, cannot delete element\n");
    return temp;
}

// 스택이 가득 차있는지 검사
int isFull()
{
    if(top >= capacity - 1)
        return true; // 가득 차있음
    else    
        return false; // 가득 차있지 않음
}

// 스택이 비어있는지 검사
int isEmpty()
{
    if(top == -1)
        return true; // 비어있음
    else   
        return false; // 비어있지 않음
}

// 전역 변수인 stack에 원소 item 삽입
void push(Element item)
{
    if(isFull())
        stackFull();
    
    stack[++top] = item;
}

// 전역 변수인 stack에서 top에 위치한 원소 삭제
Element pop()
{
    if(isEmpty())
        return stackEmpty();
    else
        return stack[top--];
}

// 스택 원소 출력
void printStack()
{
    int i;

    fprintf(stdout, "Stack: ");
    for(i = 0; i <= top; i++)
        fprintf(stdout, "%d ", stack[i].key);
    fprintf(stdout, "\n");
}