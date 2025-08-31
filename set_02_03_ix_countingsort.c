#include <stdio.h>

// Function to find the maximum element in the array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
// Counting Sort function
void countingSort(int arr[], int n) {
    int max = getMax(arr, n);
    int count[max + 1];
    int output[n];

   // Initialize count array with 0
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    // Store the count of each element
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // Store cumulative count
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Build the output array (stable sorting)
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy output array to original array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
// Function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
// Main function
int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d non-negative integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    countingSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
