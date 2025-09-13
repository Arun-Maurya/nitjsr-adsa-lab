#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3  // Minimum degree (B-Tree order). Each node can have [T-1 .. 2*T-1] keys

// Node structure
typedef struct BTreeNode {
    int keys[2*T - 1];           // Keys
    struct BTreeNode* children[2*T]; // Child pointers
    int n;                       // Current number of keys
    bool leaf;                   // Is leaf?
} BTreeNode;

// BTree structure
typedef struct BTree {
    BTreeNode* root;
} BTree;

// Create a new B-Tree node
BTreeNode* createNode(bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->children[i] = NULL;
    return node;
}

// Create an empty B-Tree
BTree* createTree() {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->root = createNode(true);
    return tree;
}

// Search key in subtree rooted at node
BTreeNode* searchItem(BTreeNode* node, int key) {
    int i = 0;
    while (i < node->n && key > node->keys[i])
        i++;

    if (i < node->n && node->keys[i] == key)
        return node;

    if (node->leaf)
        return NULL;

    return searchItem(node->children[i], key);
}

// Split child y of node x
void splitChild(BTreeNode* x, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];

    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    for (int j = x->n; j >= i+1; j--)
        x->children[j+1] = x->children[j];

    x->children[i+1] = z;

    for (int j = x->n - 1; j >= i; j--)
        x->keys[j+1] = x->keys[j];

    x->keys[i] = y->keys[T-1];
    x->n++;
}

// Insert into non-full node
void insertNonFull(BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;

        if (x->children[i+1]->n == 2*T - 1) {
            splitChild(x, i+1, x->children[i+1]);

            if (k > x->keys[i+1])
                i++;
        }
        insertNonFull(x->children[i+1], k);
    }
}

// Insert a key
void insertItem(BTree* tree, int k) {
    BTreeNode* r = tree->root;

    if (r->n == 2*T - 1) {
        BTreeNode* s = createNode(false);
        tree->root = s;
        s->children[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, k);
    } else {
        insertNonFull(r, k);
    }
}

// Get predecessor
int getPred(BTreeNode* x, int idx) {
    BTreeNode* cur = x->children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}

// Get successor
int getSucc(BTreeNode* x, int idx) {
    BTreeNode* cur = x->children[idx+1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

// Merge two children
void merge(BTreeNode* x, int idx) {
    BTreeNode* c1 = x->children[idx];
    BTreeNode* c2 = x->children[idx+1];

    c1->keys[T-1] = x->keys[idx];

    for (int i = 0; i < c2->n; i++)
        c1->keys[i+T] = c2->keys[i];

    if (!c1->leaf) {
        for (int i = 0; i <= c2->n; i++)
            c1->children[i+T] = c2->children[i];
    }

    for (int i = idx+1; i < x->n; i++)
        x->keys[i-1] = x->keys[i];

    for (int i = idx+2; i <= x->n; i++)
        x->children[i-1] = x->children[i];

    c1->n += c2->n + 1;
    x->n--;

    free(c2);
}

// Borrow from previous
void borrowFromPrev(BTreeNode* x, int idx) {
    BTreeNode* child = x->children[idx];
    BTreeNode* sibling = x->children[idx-1];

    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i+1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->children[i+1] = child->children[i];
    }

    child->keys[0] = x->keys[idx-1];
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    x->keys[idx-1] = sibling->keys[sibling->n-1];

    child->n++;
    sibling->n--;
}

// Borrow from next
void borrowFromNext(BTreeNode* x, int idx) {
    BTreeNode* child = x->children[idx];
    BTreeNode* sibling = x->children[idx+1];

    child->keys[child->n] = x->keys[idx];
    if (!child->leaf)
        child->children[child->n+1] = sibling->children[0];

    x->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i-1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->children[i-1] = sibling->children[i];
    }

    child->n++;
    sibling->n--;
}

// Fill child idx if it has less than T-1 keys
void fill(BTreeNode* x, int idx) {
    if (idx != 0 && x->children[idx-1]->n >= T)
        borrowFromPrev(x, idx);
    else if (idx != x->n && x->children[idx+1]->n >= T)
        borrowFromNext(x, idx);
    else {
        if (idx != x->n)
            merge(x, idx);
        else
            merge(x, idx-1);
    }
}

// Delete from node
void deleteNode(BTreeNode* x, int k) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < k)
        idx++;

    if (idx < x->n && x->keys[idx] == k) {
        if (x->leaf) {
            for (int i = idx+1; i < x->n; i++)
                x->keys[i-1] = x->keys[i];
            x->n--;
        } else {
            if (x->children[idx]->n >= T) {
                int pred = getPred(x, idx);
                x->keys[idx] = pred;
                deleteNode(x->children[idx], pred);
            } else if (x->children[idx+1]->n >= T) {
                int succ = getSucc(x, idx);
                x->keys[idx] = succ;
                deleteNode(x->children[idx+1], succ);
            } else {
                merge(x, idx);
                deleteNode(x->children[idx], k);
            }
        }
    } else {
        if (x->leaf) return;

        bool flag = (idx == x->n);

        if (x->children[idx]->n < T)
            fill(x, idx);

        if (flag && idx > x->n)
            deleteNode(x->children[idx-1], k);
        else
            deleteNode(x->children[idx], k);
    }
}

// Delete a key
void deleteItem(BTree* tree, int k) {
    if (!tree->root) return;

    deleteNode(tree->root, k);

    if (tree->root->n == 0) {
        BTreeNode* tmp = tree->root;
        if (tree->root->leaf)
            tree->root = NULL;
        else
            tree->root = tree->root->children[0];
        free(tmp);
    }
}

// Delete entire tree
void deleteTreeNode(BTreeNode* node) {
    if (node) {
        if (!node->leaf) {
            for (int i = 0; i <= node->n; i++)
                deleteTreeNode(node->children[i]);
        }
        free(node);
    }
}

void deleteTree(BTree* tree) {
    if (tree->root)
        deleteTreeNode(tree->root);
    free(tree);
}

// Traverse (inorder-like)
void traverse(BTreeNode* node) {
    if (node) {
        int i;
        for (i = 0; i < node->n; i++) {
            if (!node->leaf)
                traverse(node->children[i]);
            printf("%d ", node->keys[i]);
        }
        if (!node->leaf)
            traverse(node->children[i]);
    }
}

// Main test
int main() {
    BTree* tree = createTree();

    insertItem(tree, 10);
    insertItem(tree, 20);
    insertItem(tree, 5);
    insertItem(tree, 6);
    insertItem(tree, 12);
    insertItem(tree, 30);
    insertItem(tree, 7);
    insertItem(tree, 17);

    printf("Traversal: ");
    traverse(tree->root);
    printf("\n");

    deleteItem(tree, 6);
    printf("After deleting 6: ");
    traverse(tree->root);
    printf("\n");

    deleteItem(tree, 13);
    printf("After deleting 13 (not present): ");
    traverse(tree->root);
    printf("\n");

    BTreeNode* found = searchItem(tree->root, 17);
    if (found) printf("Found 17\n");
    else printf("Not found 17\n");

    deleteTree(tree);
    return 0;
}
