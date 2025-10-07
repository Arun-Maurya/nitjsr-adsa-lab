#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int n;
int **dist;

int nearestNeighbor() {
    int *visited = (int *)calloc(n, sizeof(int));
    int cost = 0;
    int current = 0;
    visited[current] = 1;

    for (int count = 1; count < n; count++) {
        int next = -1, minDist = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[current][i] < minDist) {
                minDist = dist[current][i];
                next = i;
            }
        }
        cost += minDist;
        current = next;
        visited[current] = 1;
    }
    cost += dist[current][0]; // return to start
    free(visited);
    return cost;
}

int main() {
    int sizes[] = {10, 20, 40, 60, 100};
    printf("TSP approximate running time for different sizes (Nearest Neighbor):\n");
    printf("Nodes\tTime (ms)\tTSP Cost\n");

    for (int s = 0; s < 5; s++) {
        n = sizes[s];
        // Allocate distance matrix
        dist = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            dist[i] = (int *)malloc(n * sizeof(int));
        }

        // Fill random distances (1-100)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) dist[i][j] = 0;
                else dist[i][j] = rand() % 100 + 1;
            }
        }

        clock_t start = clock();
        int cost = nearestNeighbor();
        clock_t end = clock();

        double time_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        printf("%d\t%.2f\t\t%d\n", n, time_ms, cost);

        // Free memory
        for (int i = 0; i < n; i++) free(dist[i]);
        free(dist);
    }
    return 0;
}
