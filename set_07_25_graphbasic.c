#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int n;
int graph[MAX][MAX];
int visited[MAX];
int stackArr[MAX];
int top = -1;
int timeCounter = 0;

// =========================
// Utility Functions
// =========================
void initVisited() {
    for (int i = 0; i < n; i++)
        visited[i] = 0;
}

// =========================
// 1️⃣ Strongly Connected Components (Kosaraju)
// =========================
void dfs1(int v) {
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i])
            dfs1(i);
    }
    stackArr[++top] = v;
}

void dfs2(int v, int revGraph[MAX][MAX]) {
    printf("%d ", v);
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (revGraph[v][i] && !visited[i])
            dfs2(i, revGraph);
    }
}

void findSCCs() {
    initVisited();
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs1(i);

    int revGraph[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            revGraph[i][j] = graph[j][i];

    initVisited();
    printf("\nStrongly Connected Components:\n");
    while (top >= 0) {
        int v = stackArr[top--];
        if (!visited[v]) {
            dfs2(v, revGraph);
            printf("\n");
        }
    }
}

// =========================
// 2️⃣ Articulation Points & Bridges (Tarjan)
// =========================
void APBUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[]) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++timeCounter;

    for (int v = 0; v < n; v++) {
        if (!graph[u][v]) continue;

        if (!visited[v]) {
            children++;
            parent[v] = u;
            APBUtil(v, visited, disc, low, parent, ap);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            // Articulation point condition
            if (parent[u] == -1 && children > 1)
                ap[u] = true;
            if (parent[u] != -1 && low[v] >= disc[u])
                ap[u] = true;

            // Bridge condition
            if (low[v] > disc[u])
                printf("Bridge: (%d - %d)\n", u, v);
        }
        else if (v != parent[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

void findArticulationPointsAndBridges() {
    bool visited[MAX] = {false};
    int disc[MAX], low[MAX], parent[MAX];
    bool ap[MAX] = {false};
    timeCounter = 0;

    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        visited[i] = false;
    }

    printf("\nBridges:\n");
    for (int i = 0; i < n; i++)
        if (!visited[i])
            APBUtil(i, visited, disc, low, parent, ap);

    printf("\nArticulation Points:\n");
    for (int i = 0; i < n; i++)
        if (ap[i])
            printf("%d ", i);
    printf("\n");
}

// =========================
// 3️⃣ Biconnected Components (Simplified using Tarjan idea)
// =========================
typedef struct {
    int u, v;
} Edge;

Edge edgeStack[MAX];
int edgeTop = -1;

void pushEdge(int u, int v) {
    edgeStack[++edgeTop].u = u;
    edgeStack[edgeTop].v = v;
}

void popBCC(int u, int v) {
    printf("{ ");
    while (edgeTop >= 0) {
        Edge e = edgeStack[edgeTop--];
        printf("(%d-%d) ", e.u, e.v);
        if (e.u == u && e.v == v)
            break;
    }
    printf("}\n");
}

void BCCUtil(int u, int disc[], int low[], int parent[]) {
    static int time = 0;
    int children = 0;
    disc[u] = low[u] = ++time;

    for (int v = 0; v < n; v++) {
        if (!graph[u][v]) continue;

        if (disc[v] == -1) {
            children++;
            parent[v] = u;
            pushEdge(u, v);
            BCCUtil(v, disc, low, parent);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]))
                popBCC(u, v);
        }
        else if (v != parent[u] && disc[v] < disc[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
            pushEdge(u, v);
        }
    }
}

void findBCCs() {
    int disc[MAX], low[MAX], parent[MAX];
    for (int i = 0; i < n; i++) {
        disc[i] = -1;
        low[i] = -1;
        parent[i] = -1;
    }

    printf("\nBiconnected Components:\n");
    for (int i = 0; i < n; i++)
        if (disc[i] == -1)
            BCCUtil(i, disc, low, parent);
}

// =========================
// 🧠 Main Function with Switch Menu
// =========================
int main() {
    int choice;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    do {
        printf("\n\n===== GRAPH ANALYSIS MENU =====\n");
        printf("1. Find Strongly Connected Components (SCC)\n");
        printf("2. Find Articulation Points and Bridges\n");
        printf("3. Find Biconnected Components (BCC)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                findSCCs();
                break;
            case 2:
                findArticulationPointsAndBridges();
                break;
            case 3:
                findBCCs();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
