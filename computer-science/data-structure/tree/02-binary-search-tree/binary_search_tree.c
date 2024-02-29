#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

TreeNode *createNode(int data); // 새로운 노드를 생성
TreeNode *findMin(TreeNode *node); // 가장 작은 값을 가지는 노드 찾음
TreeNode *insert(TreeNode *root, int data); // 노드 삽입
TreeNode *deleteNode(TreeNode *root, int data); // 노드 삭제
void printInorder(TreeNode *root); // 이진 탐색 트리를 중위 순회하며 노드의 값 출력

int main()
{
    TreeNode *root = NULL;

    // 이진 탐색 트리에 노드 삽입
    root = insert(root, 12);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 22);

    printf("Inorder Traversal (Original Tree): ");
    printInorder(root);
    printf("\n");

    // 노드 삭제
    int keyToDelete = 20;
    root = deleteNode(root, keyToDelete);

    printf("Inorder Traversal (After Deleting 20): ");
    printInorder(root);
    printf("\n");

    // 노드 추가
    int keyToInsert = 30;
    root = insert(root, keyToInsert);

    printf("Inorder Traversal (After Inserting 30): " );
    printInorder(root);
    printf("\n");

    return 0;
}

TreeNode *createNode(int data)
{   
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    return newNode;
}

TreeNode *findMin(TreeNode *node)
{
    // 트리 중에서 가장 왼쪽 서브트리에 위치한 노드의 값이 가장 작은 값
    while(node->left != NULL)
        node = node->left;

    return node;
}

TreeNode *insert(TreeNode *root, int data)
{
    if(root == NULL)
        return createNode(data);

    if(root->data > data)
        root->left = insert(root->left, data);
    else if(root->data < data)
        root->right = insert(root->right, data);
    
    return root;
}

TreeNode *deleteNode(TreeNode *root, int data)
{
    // 트리가 비어있는 경우에는 NULL 반환
    if(root == NULL)
        return root;
    
    // 삭제할 노드 찾기
    if(root->data > data)
        root->left = deleteNode(root->left, data);
    else if(root->data < data)
        root->right = deleteNode(root->right, data);
    // 삭제할 노드를 찾은 경우
    else{
        // 해당 노드의 차수가 0일 때
        if(root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }
        // 해당 노드의 차수가 1일 때
        else if(root->left == NULL){
            TreeNode *temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right == NULL){
            TreeNode *temp = root;
            root = root->left;
            free(temp);
        }
        // 해당 노드의 차수가 2일 때
        else{
            TreeNode *temp = findMin(root);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}

void printInorder(TreeNode *root)
{
    if(root != NULL){
        printInorder(root->left);
        printf("%d ", root->data);
        printInorder(root->right);
    }
}