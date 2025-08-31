#include <stdio.h>
#include <stdlib.h>

// Function to find minimum element in array
int getMin(int arr[], int n) {
    int min = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

// Function to find maximum element in array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Address Calculation Sort (like hashing into positions)
void addressCalculationSort(int arr[], int n) {
    int min = getMin(arr, n);
    int max = getMax(arr, n);

    int range = max - min + 1;

    // Allocate auxiliary array initialized with 0
    int *temp = (int *)calloc(range, sizeof(int));

    // Store frequency of each element
    for (int i = 0; i < n; i++)
        temp[arr[i] - min]++;

    // Reconstruct sorted array
    int k = 0;
    for (int i = 0; i < range; i++) {
        while (temp[i] > 0) {
            arr[k++] = i + min;
            temp[i]--;
        }
    }

    free(temp);
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
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    addressCalculationSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
