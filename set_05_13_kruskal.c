#include <stdio.h>

#define MAX 30

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];

// Find function for Union-Find
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Union function
void union_set(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

int main() {
    int n, e;
    Edge edges[MAX], temp;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // Initialize parent[]
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // Sort edges by weight (simple bubble sort)
    for (int i = 0; i < e - 1; i++) {
        for (int j = 0; j < e - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    printf("\nEdges in Minimum Spanning Tree:\n");
    int cost = 0, count = 0;
    for (int i = 0; i < e && count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u) != find(v)) {
            printf("%d - %d (weight %d)\n", u, v, edges[i].w);
            cost += edges[i].w;
            union_set(u, v);
            count++;
        }
    }

    printf("Minimum Cost of Spanning Tree = %d\n", cost);

    return 0;
}
