#include <stdio.h>

#define MAX 50
#define TRUE 1
#define FALSE 0

int n, e;
int graph[MAX][MAX];
int color[MAX];  // 0 = uncolored, 1 = color1, -1 = color2

int isBipartite() {
    int queue[MAX], front, rear;

    for (int i = 0; i < n; i++)
        color[i] = 0;  // Uncolored initially

    // Check each component (in case of disconnected graph)
    for (int start = 0; start < n; start++) {
        if (color[start] != 0)
            continue;

        front = rear = 0;
        queue[rear++] = start;
        color[start] = 1; // Start coloring with 1

        while (front < rear) {
            int u = queue[front++];

            for (int v = 0; v < n; v++) {
                if (graph[u][v]) {
                    if (color[v] == 0) {
                        // Assign alternate color
                        color[v] = -color[u];
                        queue[rear++] = v;
                    } else if (color[v] == color[u]) {
                        // Same color on both sides → not bipartite
                        return FALSE;
                    }
                }
            }
        }
    }
    return TRUE;
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

    if (isBipartite())
        printf("The graph is Bipartite.\n");
    else
        printf("The graph is NOT Bipartite.\n");

    return 0;
}
