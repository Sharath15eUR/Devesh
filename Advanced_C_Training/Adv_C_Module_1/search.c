#include <stdio.h>

int searchMatrix(int **mat, int n, int key) {
    int row = 0, col = n - 1;

    while (row < n && col >= 0) {
        if (mat[row][col] == key)
            return 1; // Found
        else if (mat[row][col] > key)
            col--;
        else
            row++;
    }

    return 0; // Not found
}

// Example usage with static matrix for demo:
int main() {
    int mat[4][4] = {
        {1, 4, 7, 11},
        {2, 5, 8, 12},
        {3, 6, 9, 16},
        {10, 13, 14, 17}
    };
    int key;
    printf("\nEnter Key: ");
    scanf("%d",&key);

    // Convert to int** pointer
    int *ptrs[4];
    for (int i = 0; i < 4; i++)
        ptrs[i] = mat[i];

    if (searchMatrix(ptrs, 4, key))
        printf("Found\n");
    else
        printf("Not found\n");

    return 0;
}
