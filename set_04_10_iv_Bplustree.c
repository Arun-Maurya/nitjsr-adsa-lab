#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 3   // Order of B+ Tree (max children per node)

// Node structure
typedef struct BPTreeNode {
    int keys[M];
    struct BPTreeNode* children[M+1];
    int n;             // number of keys
    bool leaf;         // is leaf?
    struct BPTreeNode* next; // for leaf node linking
} BPTreeNode;

// B+ Tree structure
typedef struct BPTree {
    BPTreeNode* root;
} BPTree;

// Create a new node
BPTreeNode* createNode(bool leaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->leaf = leaf;
    node->n = 0;
    node->next = NULL;
    for (int i = 0; i < M+1; i++)
        node->children[i] = NULL;
    return node;
}

// Create tree
BPTree* createTree() {
    BPTree* tree = (BPTree*)malloc(sizeof(BPTree));
    tree->root = createNode(true);
    return tree;
}

// Search
BPTreeNode* searchItem(BPTree* tree, int key) {
    BPTreeNode* cur = tree->root;
    while (!cur->leaf) {
        int i = 0;
        while (i < cur->n && key >= cur->keys[i])
            i++;
        cur = cur->children[i];
    }
    for (int i = 0; i < cur->n; i++) {
        if (cur->keys[i] == key)
            return cur;
    }
    return NULL;
}

// Split child node
void splitChild(BPTreeNode* parent, int idx) {
    BPTreeNode* child = parent->children[idx];
    int mid = child->n / 2;

    BPTreeNode* newChild = createNode(child->leaf);
    newChild->n = child->n - mid;

    // Move keys
    for (int i = 0; i < newChild->n; i++)
        newChild->keys[i] = child->keys[mid+i];

    if (!child->leaf) {
        for (int i = 0; i <= newChild->n; i++)
            newChild->children[i] = child->children[mid+i];
        child->n = mid;
    } else {
        newChild->next = child->next;
        child->next = newChild;
        child->n = mid;
    }

    for (int i = parent->n; i > idx; i--) {
        parent->children[i+1] = parent->children[i];
        parent->keys[i] = parent->keys[i-1];
    }

    parent->children[idx+1] = newChild;
    parent->keys[idx] = newChild->keys[0];
    parent->n++;
}

// Insert non-full
void insertNonFull(BPTreeNode* node, int key) {
    if (node->leaf) {
        int i = node->n - 1;
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n++;
    } else {
        int i = node->n - 1;
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->children[i]->n == M) {
            splitChild(node, i);
            if (key >= node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// Insert
void insertItem(BPTree* tree, int key) {
    BPTreeNode* root = tree->root;
    if (root->n == M) {
        BPTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;
        splitChild(newRoot, 0);
        int i = (key >= newRoot->keys[0]);
        insertNonFull(newRoot->children[i], key);
        tree->root = newRoot;
    } else {
        insertNonFull(root, key);
    }
}

// Delete from leaf (basic version: just removes key)
void deleteItem(BPTree* tree, int key) {
    BPTreeNode* cur = tree->root;
    while (!cur->leaf) {
        int i = 0;
        while (i < cur->n && key >= cur->keys[i])
            i++;
        cur = cur->children[i];
    }

    int i;
    for (i = 0; i < cur->n; i++) {
        if (cur->keys[i] == key)
            break;
    }
    if (i == cur->n) return; // not found

    for (; i < cur->n-1; i++)
        cur->keys[i] = cur->keys[i+1];
    cur->n--;
}

// Delete entire tree
void deleteTreeNode(BPTreeNode* node) {
    if (node) {
        if (!node->leaf) {
            for (int i = 0; i <= node->n; i++)
                deleteTreeNode(node->children[i]);
        }
        free(node);
    }
}

void deleteTree(BPTree* tree) {
    if (tree->root)
        deleteTreeNode(tree->root);
    free(tree);
}

// Traverse all leaves
void traverse(BPTree* tree) {
    BPTreeNode* cur = tree->root;
    while (!cur->leaf)
        cur = cur->children[0];

    while (cur) {
        for (int i = 0; i < cur->n; i++)
            printf("%d ", cur->keys[i]);
        cur = cur->next;
    }
    printf("\n");
}

// Main test
int main() {
    BPTree* tree = createTree();

    insertItem(tree, 5);
    insertItem(tree, 15);
    insertItem(tree, 25);
    insertItem(tree, 35);
    insertItem(tree, 45);

    printf("Traversal: ");
    traverse(tree);

    BPTreeNode* found = searchItem(tree, 25);
    if (found) printf("Found 25\n");
    else printf("Not found 25\n");

    deleteItem(tree, 25);
    printf("After deleting 25: ");
    traverse(tree);

    deleteTree(tree);
    return 0;
}
