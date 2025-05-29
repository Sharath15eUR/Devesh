#include <stdio.h>
#include <stdlib.h>

void rearrangeEvenOdd(int *arr, int size) {
    int *temp = (int *)malloc(size * sizeof(int));
    int *ptr = arr;
    int *t = temp;

    // First pass: copy evens
    for (int i = 0; i < size; i++) {
        if (*(ptr + i) % 2 == 0) {
            *t = *(ptr + i);
            t++;
        }
    }

    // Second pass: copy odds
    for (int i = 0; i < size; i++) {
        if (*(ptr + i) % 2 != 0) {
            *t = *(ptr + i);
            t++;
        }
    }

    // Copy back to original array
    for (int i = 0; i < size; i++) {
        *(ptr + i) = *(temp + i);
    }

    free(temp);
}

// Sample usage
int main() {
    int arr[] = {1, 2, 4, 3, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    rearrangeEvenOdd(arr, size);

    for (int i = 0; i < size; i++)
        printf("%d ", *(arr + i));

    return 0;
}
