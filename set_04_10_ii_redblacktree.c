#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree {
    Node *root;
    Node *NIL;  // Sentinel NIL node
} RBTree;

// Utility: create a new Red-Black Tree
RBTree* createTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->NIL = (Node*)malloc(sizeof(Node));
    tree->NIL->color = BLACK;
    tree->NIL->left = tree->NIL->right = tree->NIL->parent = NULL;
    tree->root = tree->NIL;
    return tree;
}

// Create a new node
Node* createNode(RBTree* tree, int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = tree->NIL;
    return node;
}

// Left Rotate
void leftRotate(RBTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == tree->NIL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right Rotate
void rightRotate(RBTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != tree->NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == tree->NIL)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Fix insertion violations
void insertFix(RBTree* tree, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {  // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { // Case 2
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;  // Case 3
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {  // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { // Case 2
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;  // Case 3
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// Insert a node
void insertItem(RBTree* tree, int key) {
    Node* z = createNode(tree, key);
    Node* y = tree->NIL;
    Node* x = tree->root;

    while (x != tree->NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else if (z->key > x->key) x = x->right;
        else return; // No duplicates
    }

    z->parent = y;
    if (y == tree->NIL)
        tree->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    insertFix(tree, z);
}

// Search a node
Node* searchItem(RBTree* tree, int key) {
    Node* current = tree->root;
    while (current != tree->NIL && current->key != key) {
        if (key < current->key) current = current->left;
        else current = current->right;
    }
    return (current == tree->NIL) ? NULL : current;
}

// Find minimum
Node* treeMinimum(RBTree* tree, Node* x) {
    while (x->left != tree->NIL) x = x->left;
    return x;
}

// Fix delete violations
void deleteFix(RBTree* tree, Node* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

// Transplant nodes
void rbTransplant(RBTree* tree, Node* u, Node* v) {
    if (u->parent == tree->NIL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// Delete a node
void deleteItem(RBTree* tree, int key) {
    Node* z = searchItem(tree, key);
    if (!z) return;

    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;

    if (z->left == tree->NIL) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->NIL) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = treeMinimum(tree, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);
    if (yOriginalColor == BLACK)
        deleteFix(tree, x);
}

// Delete the whole tree
void deleteTreeHelper(RBTree* tree, Node* node) {
    if (node != tree->NIL) {
        deleteTreeHelper(tree, node->left);
        deleteTreeHelper(tree, node->right);
        free(node);
    }
}

void deleteTree(RBTree* tree) {
    deleteTreeHelper(tree, tree->root);
    free(tree->NIL);
    free(tree);
}

// Inorder traversal
void inorder(RBTree* tree, Node* root) {
    if (root != tree->NIL) {
        inorder(tree, root->left);
        printf("%d(%s) ", root->key, root->color == RED ? "R" : "B");
        inorder(tree, root->right);
    }
}

// Main test
int main() {
    RBTree* tree = createTree();

    insertItem(tree, 10);
    insertItem(tree, 20);
    insertItem(tree, 30);
    insertItem(tree, 15);
    insertItem(tree, 25);

    printf("Inorder: ");
    inorder(tree, tree->root);
    printf("\n");

    deleteItem(tree, 20);
    printf("After deletion of 20: ");
    inorder(tree, tree->root);
    printf("\n");

    Node* found = searchItem(tree, 25);
    if (found) printf("Found %d\n", found->key);
    else printf("Not Found\n");

    deleteTree(tree);
    return 0;
}
