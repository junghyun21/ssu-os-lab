#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode *treePointer;
typedef struct treeNode{
    char data;
    treePointer left;
    treePointer right;
}treeNode;

treePointer makeRootNode(char data, treePointer left, treePointer right); // 새로운 노드를 생성하는 함수
void preorder(treePointer root); // 전위 순회 (루트->왼쪽->오른쪽)
void inorder(treePointer root); // 중위 순회 (왼쪽->루트->오른쪽)
void postorder(treePointer root); // 후위 순회 (왼쪽->오른쪽->루트)

int main(int argc, char *argv[])
{
    // 수식에 대한 이진 트리 생성 (A * B - C / D)
    treePointer n7 = makeRootNode('D', NULL, NULL);
    treePointer n6 = makeRootNode('C', NULL, NULL);
    treePointer n5 = makeRootNode('B', NULL, NULL);
    treePointer n4 = makeRootNode('A', NULL, NULL);
    treePointer n3 = makeRootNode('/', n6, n7);
    treePointer n2 = makeRootNode('*', n4, n5);
    treePointer n1 = makeRootNode('-', n2, n3);

    // 전위, 중위, 후위표기법의 수식 출력
    // 순회 함수를 처음 호출 할 때에는 트리의 루트 노드를 전달
    fprintf(stdout, "preorder: ");
    preorder(n1);
    fprintf(stdout, "\n");

    fprintf(stdout, "inorder: ");
    inorder(n1);
    fprintf(stdout, "\n");

    fprintf(stdout, "postorder: ");
    postorder(n1);
    fprintf(stdout, "\n");

    return 0;
}

treePointer makeRootNode(char data, treePointer left, treePointer right)
{
    treePointer root;
    root = (treePointer)malloc(sizeof(*root));

    root->data = data;
    root->left = left;
    root->right = right;

    return root;
}

void preorder(treePointer root)
{
    if(root){
        fprintf(stdout, "%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(treePointer root)
{
    if(root){
        inorder(root->left);
        fprintf(stdout, "%c ", root->data);
        inorder(root->right);
    }
}

void postorder(treePointer root)
{
    if(root){
        postorder(root->left);
        postorder(root->right);
        fprintf(stdout, "%c ", root->data);
    }
}