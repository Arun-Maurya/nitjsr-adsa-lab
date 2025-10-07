#include <stdio.h>

#define MAX 20

int n, e;
int graph[MAX][MAX];
int path[MAX];

// Check if vertex v can be added to path[pos]
int isSafe(int v, int pos) {
    // Check if this vertex is adjacent to the previous one
    if (graph[path[pos - 1]][v] == 0)
        return 0;

    // Check if vertex is already in the path
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

// Recursive utility to solve Hamiltonian Cycle
int hamCycleUtil(int pos) {
    // Base case: If all vertices are included
    if (pos == n) {
        // Check if last vertex connects to first
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    // Try next vertex as next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamCycleUtil(pos + 1))
                return 1;

            // Backtrack
            path[pos] = -1;
        }
    }

    return 0;
}

// Function to find Hamiltonian Cycle
int hamCycle() {
    for (int i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0; // start at vertex 0

    if (hamCycleUtil(1) == 0) {
        printf("No Hamiltonian cycle exists.\n");
        return 0;
    }

    printf("Hamiltonian Cycle found: ");
    for (int i = 0; i < n; i++)
        printf("%d ", path[i]);
    printf("%d\n", path[0]); // return to start

    return 1;
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
        graph[u][v] = graph[v][u] = 1; // undirected
    }

    hamCycle();

    return 0;
}
