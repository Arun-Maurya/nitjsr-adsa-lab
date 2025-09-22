#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int graph[MAX][MAX];   // adjacency matrix
int visited[MAX], stack[MAX], inStack[MAX];
int n;                 // number of vertices
int top = -1;

int minCycle = INT_MAX, maxCycle = 0;

// push to recursion stack
void push(int v) {
    stack[++top] = v;
    inStack[v] = 1;
}

// pop from recursion stack
void pop() {
    inStack[stack[top]] = 0;
    top--;
}

// find cycle length when back edge detected
void processCycle(int start, int end) {
    int length = 1; // include end vertex
    for (int i = top; i >= 0; i--) {
        if (stack[i] == end) break;
        length++;
    }
    if (length < minCycle) minCycle = length;
    if (length > maxCycle) maxCycle = length;
}

void dfs(int u) {
    visited[u] = 1;
    push(u);

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                dfs(v);
            } else if (inStack[v]) {
                // found a cycle
                processCycle(u, v);
            }
        }
    }

    pop();
}

int main() {
    int edges, u, v, directed;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Is the graph directed? (1=Yes, 0=No): ");
    scanf("%d", &directed);

    // initialize graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        if (!directed) graph[v][u] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i);
    }

    if (minCycle == INT_MAX) {
        printf("No cycles found.\n");
    } else {
        printf("Smallest cycle length: %d\n", minCycle);
        printf("Largest cycle length: %d\n", maxCycle);
    }

    return 0;
}
 /* input formate
4
5
1
0 1
1 2
2 0
2 3
3 1

n=4 (vertices: 0,1,2,3)

e=5 edges

Directed (1)

Edges: (0→1), (1→2), (2→0), (2→3), (3→1)

Cycles are {0,1,2}, {1,2,3}

Smallest cycle length = 3, Largest = 3


 */