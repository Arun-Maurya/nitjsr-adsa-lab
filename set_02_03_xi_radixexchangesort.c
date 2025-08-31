#include <stdio.h>

// Function to swap two numbers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Radix Exchange Sort (Binary QuickSort)
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0)
        return;

    int i = left, j = right;

    while (i <= j) {
        // Move i while the bit is 0
        while (i <= right && ((arr[i] >> bit) & 1) == 0)
            i++;
        // Move j while the bit is 1
        while (j >= left && ((arr[j] >> bit) & 1) == 1)
            j--;

        if (i < j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    // Recursive calls for left and right partitions
    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

// Function to get the maximum bit position
int getMaxBit(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bit = 0;
    while (max > 0) {
        bit++;
        max >>= 1;
    }
    return bit - 1; // Highest bit index
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

    int maxBit = getMaxBit(arr, n);
    radixExchangeSort(arr, 0, n - 1, maxBit);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
