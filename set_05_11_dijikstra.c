#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6                                                                                 // Number of vertices

                                                                        // find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

//print the result
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra’s algorithm
void dijkstra(int graph[V][V], int src) {
    int distance[V];                                                   // dist[i] will hold shortest distance from src to i
    bool visited[V];                                               // visited[i] will be true if vertex i is finalized

                                                              // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

                                                                               // Distance from source to itself is always 0
    distance[src] = 0;

                                                                                 // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(distance, visited);
        visited[u] = true;
                                                                         /* Update dist[v] only if not visited, there is
                                                                            an edge, and total weight < current dist[v]*/
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX
                && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

                                                                          // Print the constructed distance array
    printSolution(distance);
}

int main() {
                                                                          /* Example graph represented using adjacency matrix
                                                                           0 means no edge */
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 2, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 2, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    int src = 0;                                                               // source vertex
    dijkstra(graph, src);

    return 0;
}
