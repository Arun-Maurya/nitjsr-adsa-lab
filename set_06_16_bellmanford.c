#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge
typedef struct {
    int src, dest, weight;
} Edge;

// Structure to represent a graph
typedef struct {
    int V, E;     // Number of vertices and edges
    Edge* edge;   // Array of edges
} Graph;

// Function to create a graph
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

// Bellman-Ford algorithm
void BellmanFord(Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].src;
        int v = graph->edge[j].dest;
        int weight = graph->edge[j].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle!\n");
            return;
        }
    }

    // Print distances
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d \t\t INF\n", i);
        else
            printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Driver code
int main() {
    int V = 5;  // Number of vertices
    int E = 8;  // Number of edges
    Graph* graph = createGraph(V, E);

    // Adding edges (src, dest, weight)
    graph->edge[0] = (Edge){0, 1, -1};
    graph->edge[1] = (Edge){0, 2, 4};
    graph->edge[2] = (Edge){1, 2, 3};
    graph->edge[3] = (Edge){1, 3, 2};
    graph->edge[4] = (Edge){1, 4, 2};
    graph->edge[5] = (Edge){3, 2, 5};
    graph->edge[6] = (Edge){3, 1, 1};
    graph->edge[7] = (Edge){4, 3, -3};

    BellmanFord(graph, 0);

    free(graph->edge);
    free(graph);
    return 0;
}
