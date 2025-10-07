#include <stdio.h>

void coinChange(int coins[], int n, int amount) {
    int count[50] = {0};  // to store count of each coin

    printf("Coins used:\n");

    for (int i = 0; i < n; i++) {
        if (amount >= coins[i]) {
            count[i] = amount / coins[i];   // number of coins of this denomination
            amount = amount % coins[i];     // remaining amount
        }
    }

    // Display result
    for (int i = 0; i < n; i++) {
        if (count[i] != 0)
            printf("%d x %d\n", coins[i], count[i]);
    }
}

int main() {
    int coins[] = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1}; // Indian currency
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount;

    printf("Enter the amount: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}
