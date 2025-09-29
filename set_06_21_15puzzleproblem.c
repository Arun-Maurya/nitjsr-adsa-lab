#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 4   // 4x4 board

// Directions for blank tile (down, left, up, right)
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// Node structure for puzzle state
typedef struct Node {
    int mat[N][N];
    int x, y;       // blank tile coordinates
    int cost;       // f = g + h
    int level;      // g = depth
    struct Node* parent;
} Node;

// Function to create a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    memcpy(node->mat, mat, sizeof(node->mat));

    // Swap blank with target tile
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->parent = parent;
    node->level = level;
    node->cost = INT_MAX;

    return node;
}

// Manhattan distance heuristic
int calculateCost(int mat[N][N], int goal[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] != 0) {
                int val = mat[i][j];
                int goalX = (val - 1) / N;
                int goalY = (val - 1) % N;
                if (val == 0) { goalX = N-1; goalY = N-1; }
                cost += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return cost;
}

// Print puzzle matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == 0) printf("   ");
            else printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Print path from root to solution
void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Priority queue (min-heap) for nodes
typedef struct {
    Node** arr;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (Node**)malloc(capacity * sizeof(Node*));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap->arr[idx]->cost < heap->arr[parent]->cost) {
            swap(&heap->arr[idx], &heap->arr[parent]);
            idx = parent;
        } else break;
    }
}

void heapifyDown(MinHeap* heap, int idx) {
    int left, right, smallest;
    while (1) {
        left = 2 * idx + 1;
        right = 2 * idx + 2;
        smallest = idx;

        if (left < heap->size && heap->arr[left]->cost < heap->arr[smallest]->cost)
            smallest = left;
        if (right < heap->size && heap->arr[right]->cost < heap->arr[smallest]->cost)
            smallest = right;

        if (smallest != idx) {
            swap(&heap->arr[idx], &heap->arr[smallest]);
            idx = smallest;
        } else break;
    }
}

void push(MinHeap* heap, Node* node) {
    if (heap->size == heap->capacity) return;
    heap->arr[heap->size] = node;
    heapifyUp(heap, heap->size);
    heap->size++;
}

Node* pop(MinHeap* heap) {
    if (heap->size == 0) return NULL;
    Node* root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapifyDown(heap, 0);
    return root;
}

int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Solve the puzzle
void solve(int initial[N][N], int x, int y, int goal[N][N]) {
    MinHeap* heap = createHeap(100000);

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, goal);
    push(heap, root);

    while (heap->size > 0) {
        Node* min = pop(heap);

        // If goal reached
        if (calculateCost(min->mat, goal) == 0) {
            printf("Solution found in %d moves:\n\n", min->level);
            printPath(min);
            return;
        }

        // Generate all possible moves
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = child->level + calculateCost(child->mat, goal);
                push(heap, child);
            }
        }
    }
}

int main() {
    // Example initial state
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    // Goal state
    int goal[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    int x = 1, y = 2;  // blank tile location in initial state

    solve(initial, x, y, goal);

    return 0;
}
