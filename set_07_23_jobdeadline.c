#include <stdio.h>
#include <stdlib.h>

struct Job {
    char id;        // Job ID (like A, B, C, ...)
    int deadline;   // Deadline of job
    int profit;     // Profit if job is done before or on deadline
};

// Comparator function to sort jobs by descending profit
int compare(const void *a, const void *b) {
    struct Job *j1 = (struct Job *)a;
    struct Job *j2 = (struct Job *)b;
    return j2->profit - j1->profit; // descending order
}

// Function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

void jobSequencing(struct Job jobs[], int n) {
    // Sort jobs by profit
    qsort(jobs, n, sizeof(struct Job), compare);

    // Find maximum deadline
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    // Create slot array to store job result
    char result[maxDeadline];
    int slot[maxDeadline];
    for (int i = 0; i < maxDeadline; i++)
        slot[i] = 0;  // all slots empty

    int totalProfit = 0;

    // Schedule each job
    for (int i = 0; i < n; i++) {
        // find a free slot for this job (from its deadline backwards)
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == 0) {
                result[j] = jobs[i].id;   // assign job
                slot[j] = 1;              // mark slot as occupied
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Print job sequence
    printf("Job sequence: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i])
            printf("%c ", result[i]);
    }

    printf("\nTotal Profit: %d\n", totalProfit);
}

int main() {
    struct Job jobs[] = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);

    return 0;
}
