#include <stdio.h>
#include <stdbool.h>

#define N 4  // You can change this to solve for different N

// Function to print the board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j])
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

// Check if a queen can be placed at board[row][col]
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check this column on upper rows
    for (i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper right diagonal
    for (i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive backtracking function
bool solveNQueens(int board[N][N], int row) {
    // Base case: all queens are placed
    if (row >= N) {
        printBoard(board);  // Print one solution
        return true;
    }

    bool res = false;

    // Try placing queen in all columns of current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1; // Place queen

            // Recurse for next row
            res = solveNQueens(board, row + 1) || res;

            // Backtrack
            board[row][col] = 0;
        }
    }
    return res;
}

int main() {
    int board[N][N] = {0};

    if (!solveNQueens(board, 0))
        printf("No solution exists\n");

    return 0;
}
