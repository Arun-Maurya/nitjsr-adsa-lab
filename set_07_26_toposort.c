#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top = -1;
int n; // number of vertices

void topoDFS(int v) {
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i])
            topoDFS(i);
    }

    // push to stack after visiting all neighbours
    stack[++top] = v;
}

void topologicalSort() {
    // Mark all nodes as unvisited
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    // Call DFS from each unvisited node
    for (int i = 0; i < n; i++)
        if (!visited[i])
            topoDFS(i);

    // Print stack in reverse order
    printf("\nTopological Order:\n");
    while (top >= 0)
        printf("%d ", stack[top--]);
    printf("\n");
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    topologicalSort();
    return 0;
}
