#include <stdio.h>
#include <stdlib.h>

// Structure for stack node
typedef struct {
    int left, right, state;
} StackNode;

// Function to merge two subarrays
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int i, j, k;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

// Iterative Merge Sort using one stack
void mergeSort(int arr[], int n) {
    StackNode stack[1000];  // stack to simulate recursion
    int top = -1;

    // Push initial problem (whole array)
    stack[++top] = (StackNode){0, n - 1, 0};

    while (top >= 0) {
        StackNode node = stack[top--];
        int l = node.left;
        int r = node.right;
        int state = node.state;

        if (l < r) {
            int m = (l + r) / 2;

            if (state == 0) {
                // Push current node back with state=1 (to merge later)
                stack[++top] = (StackNode){l, r, 1};
                // Push right subarray
                stack[++top] = (StackNode){m + 1, r, 0};
                // Push left subarray
                stack[++top] = (StackNode){l, m, 0};
            } else {
                // Merge step
                merge(arr, l, m, r);
            }
        }
    }
}

int main() {
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    mergeSort(arr, n);

    printf("Sorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
