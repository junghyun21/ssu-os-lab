#include <stdio.h>
#include <stdlib.h>
// #include <memory.h>

typedef struct treeNode
{
    int data;
    struct treeNode *left;
    struct treeNode *right;
}treeNode;

//      n1
//     /  \
//   n2    n3
int main()
{
    // 트리의 노드 생성
    treeNode *n1, *n2, *n3;
    n1 = (treeNode *)malloc(sizeof(treeNode));
    n2 = (treeNode *)malloc(sizeof(treeNode));
    n3 = (treeNode *)malloc(sizeof(treeNode));

    // 첫 번째 노드 설정
    n1->data = 10;
    n1->left = n2;
    n1->right = n3;

    // 두 번째 노드 설정
    n2->data = 20;
    n2->left = NULL;
    n2->right = NULL;

    // 세 번째 노드 설정
    n3->data = 30;
    n3->left = NULL;
    n3->right = NULL;

    return 0;
}