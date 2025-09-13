#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

void preordermorris(Node* root) {
    Node* cur = root;
    while (cur) {
        if (!cur->left) {
            printf("%d ", cur->data);
            cur = cur->right;
        } else {
            Node* pre = cur->left;
            while (pre->right && pre->right != cur) pre = pre->right;
            if (!pre->right) {              
                printf("%d ", cur->data); 
                pre->right = cur;
                cur = cur->left;
            } else {                        
                pre->right = NULL;
                cur = cur->right;
            }
        }
    }
}


int main() {

    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right=createNode(8);
     printf("Preorder (Morris): ");
    preordermorris(root);
    printf("\n");

    return 0;
}
