#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct{
    int heap[MAX_ELEMENT];
    int heapSize;
}HeapType;

HeapType *createHeap();
void push(HeapType *h, int item);
int pop(HeapType * h);
void printHeap(HeapType *h);

int main(int argc, char *argv[])
{
    int i, n, item;
    HeapType *heap = createHeap();

    fprintf(stdout, "push: [10] [45] [19] [11] [49]\n");

    push(heap, 10);
    push(heap, 45);
    push(heap, 19);
    push(heap, 11);
    push(heap, 49);

    printHeap(heap);
    n = heap->heapSize;

    for(i = 1; i <= n; i++){
        item = pop(heap);
        fprintf(stdout, "delete : [%d]\n", item);
    }

    return 0;
}

HeapType *createHeap()
{
    HeapType *h = (HeapType *)malloc(sizeof(HeapType));
    h->heapSize = 0;

    return h;
}

void push(HeapType *h, int item)
{
    int i;

    h->heapSize = h->heapSize + 1;

    i = h->heapSize;

    // 추가할 원소가 부모 노드보다 작으면 반복 종료
    while((i != 1) && item > h->heap[i / 2]){
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

int pop(HeapType * h)
{
    int parent, child;
    int item, temp;

    item = h->heap[1]; // 삭제할 노드의 값 (루트 노드)
    temp = h->heap[h->heapSize]; // 힙의 맨 끝에 있는 노드
    h->heapSize--;

    parent = 1;
    child = 2;

    while(child <= h->heapSize){
        // 두 개의 자식 중 더 큰 값을 갖는 자식의 인덱스 찾기
        if((child < h->heapSize) && (h->heap[child] < h->heap[child + 1]))
            child++;

        // 부모 노드의 값이 자식 노드의 값보다 크면 반복 종료
        if(temp >= h->heap[child])
            break;

        h->heap[parent] = h->heap[child];

        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;

    return item;
}

void printHeap(HeapType *h)
{
    int i;
    fprintf(stdout, "Heap: ");
    for(i = 1; i <= h->heapSize; i++)
        fprintf(stdout, "[%d] ", h->heap[i]);
    fprintf(stdout, "\n");
}