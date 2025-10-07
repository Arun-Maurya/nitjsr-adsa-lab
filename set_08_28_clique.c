#include <stdio.h>

#define MAX 20

int n, e, m;
int graph[MAX][MAX];

// Check if all vertices in subset[] form a clique
int isClique(int subset[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (graph[subset[i]][subset[j]] == 0)
                return 0; // Missing edge → not a clique
        }
    }
    return 1;
}

// Backtracking function to find clique of size m
int findClique(int subset[], int size, int vertex) {
    if (size == m) {
        if (isClique(subset, size))
            return 1;
        return 0;
    }
    if (vertex >= n) return 0;

    // Include current vertex
    subset[size] = vertex;
    if (findClique(subset, size + 1, vertex + 1))
        return 1;

    // Exclude current vertex
    if (findClique(subset, size, vertex + 1))
        return 1;

    return 0;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        graph[u][v] = graph[v][u] = 1; // Undirected graph
    }

    printf("Enter size of clique to search (m): ");
    scanf("%d", &m);

    int subset[MAX];
    if (findClique(subset, 0, 0))
        printf("Graph contains a clique of size %d.\n", m);
    else
        printf("Graph does NOT contain a clique of size %d.\n", m);

    return 0;
}
