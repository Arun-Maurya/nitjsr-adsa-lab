#include <stdio.h>
#include <stdlib.h>

/* ----------- Node structure ----------- */
typedef struct Node {
    int key;
    int height;
    struct Node *left, *right;
} Node;

typedef struct {
    Node* root;
} AVLTree;

/* ----------- Helper functions ----------- */
int height(Node* n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->height = 1;
    n->left = n->right = NULL;
    return n;
}

/* ----------- Rotations ----------- */
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

/* ----------- Core AVL operations ----------- */
Node* insertNode(Node* node, int key) {
    if (!node) return createNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;  // duplicate not allowed

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Balance cases
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* cur = node;
    while (cur->left) cur = cur->left;
    return cur;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with one child or none
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            // Node with two children
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balance cases
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* ----------- User-facing API ----------- */
AVLTree* createTree() {
    AVLTree* t = (AVLTree*)malloc(sizeof(AVLTree));
    t->root = NULL;
    return t;
}

void deleteTreeRecursive(Node* root) {
    if (!root) return;
    deleteTreeRecursive(root->left);
    deleteTreeRecursive(root->right);
    free(root);
}

void deleteTree(AVLTree* t) {
    deleteTreeRecursive(t->root);
    free(t);
}

void insertItem(AVLTree* t, int key) {
    t->root = insertNode(t->root, key);
}

void deleteItem(AVLTree* t, int key) {
    t->root = deleteNode(t->root, key);
}

Node* searchItem(Node* root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return searchItem(root->left, key);
    return searchItem(root->right, key);
}

/* ----------- Traversal for testing ----------- */
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

/* ----------- Demo ----------- */
int main() {
    AVLTree* t = createTree();

    insertItem(t, 10);
    insertItem(t, 20);
    insertItem(t, 30);
    insertItem(t, 40);
    insertItem(t, 50);
    insertItem(t, 25);

    printf("Inorder traversal: ");
    inorder(t->root);
    printf("\n");

    deleteItem(t, 40);
    printf("After deleting 40: ");
    inorder(t->root);
    printf("\n");

    Node* s = searchItem(t->root, 25);
    if (s) printf("Found: %d\n", s->key);
    else   printf("Not found\n");

    deleteTree(t);
    return 0;
}

