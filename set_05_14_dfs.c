#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int timeCounter;       // global DFS time counter
int adj[MAX][MAX];     // adjacency matrix
int n;                 // number of vertices
int visited[MAX];      // 0=not visited, 1=discovered, 2=finished
int disc[MAX], finish[MAX];

// DFS function
void DFS(int u) {
    visited[u] = 1;               // vertex discovered
    disc[u] = ++timeCounter;

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {  // if edge u->v exists
            if (visited[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS(v);
            }
            else if (visited[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            }
            else if (visited[v] == 2) {
                if (disc[u] < disc[v])
                    printf("Forward Edge: %d -> %d\n", u, v);
                else
                    printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    visited[u] = 2;               // vertex finished
    finish[u] = ++timeCounter;
}

// Driver code
int main() {
    int e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // initialize
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v) for directed graph:\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;  // directed edge
    }

    timeCounter = 0;
    printf("\nDFS Edge Classification:\n");
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0)
            DFS(i);
    }

    printf("\nDiscovery and Finish Times:\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: disc=%d, finish=%d\n", i, disc[i], finish[i]);
    }

    return 0;
}
/*
// input

Enter number of vertices: 4
Enter number of edges: 5
Enter edges (u v):
0 1
0 2
1 2
2 0
2 3

// output 
DFS Edge Classification:
Tree Edge: 0 -> 1
Tree Edge: 1 -> 2
Back Edge: 2 -> 0
Tree Edge: 2 -> 3

Discovery and Finish Times:
Vertex 0: disc=1, finish=8
Vertex 1: disc=2, finish=7
Vertex 2: disc=3, finish=6
Vertex 3: disc=4, finish=5


*/