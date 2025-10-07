#include <stdio.h>
#include <stdbool.h>

#define V 4   // Number of vertices in the graph

// Function to check if current color assignment is safe
bool isSafe(int v, int graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c)
            return false;
    }
    return true;
}

// A recursive utility function to solve m Coloring problem
bool graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    // If all vertices are assigned a color, return true
    if (v == V)
        return true;

    // Try different colors for vertex v
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c; // Assign color

            // Recur for next vertex
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            // If assigning color c doesn't lead to a solution
            color[v] = 0; // Backtrack
        }
    }

    return false;
}

// Function to solve the m Coloring problem
bool graphColoring(int graph[V][V], int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0; // Initialize all colors to 0

    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("Solution does not exist\n");
        return false;
    }

    printf("Solution exists: Assigned colors are\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i + 1, color[i]);
    
    return true;
}

// Driver function
int main() {
    // Example graph (Adjacency Matrix)
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3;  // Number of colors

    graphColoring(graph, m);

    return 0;
}
