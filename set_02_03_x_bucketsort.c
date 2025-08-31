#include <stdio.h>
#include <stdlib.h>

// Insertion Sort for individual buckets
void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bucket Sort function
void bucketSort(float arr[], int n) {
    // Create n empty buckets
    float buckets[n][n];   // each bucket can hold up to n elements
    int bucketCount[n];    // track count of elements in each bucket

    for (int i = 0; i < n; i++)
        bucketCount[i] = 0;

    // Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int idx = n * arr[i];  // index in bucket
        buckets[idx][bucketCount[idx]++] = arr[i];
    }

    // Sort each bucket
    for (int i = 0; i < n; i++) {
        insertionSort(buckets[i], bucketCount[i]);
    }

    // Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucketCount[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

// Function to print array
void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%.2f ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    float arr[n];
    printf("Enter %d floating numbers between 0 and 1:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }

    bucketSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
