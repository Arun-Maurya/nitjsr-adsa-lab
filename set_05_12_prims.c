#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6                                             // Number of vertices

                                                       // Function to find the vertex with minimum key value
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed MST
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

// Prim’s algorithm
void primMST(int graph[V][V]){
    int parent[V];                                                              // Store constructed MST
    int key[V];                                                                // Key values used to pick min weight edge
    bool mstSet[V];                                                            // To represent vertices included in MST

                                                                             // Initialize all keys as infinite
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

                                                                                   // First node always included in MST
    key[0] = 0;                                                                   // Start from vertex 0
    parent[0] = -1;                                                             // First node is root of MST

    // MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        // Update key and parent for adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print MST
    printMST(parent, graph);
}

int main() {
                                                                      /* Example graph using adjacency matrix */
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 2, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 2, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    primMST(graph);

    return 0;
}
