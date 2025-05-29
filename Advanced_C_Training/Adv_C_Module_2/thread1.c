#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

// Thread A: Computes sum of first N primes
void* threadA(void* arg) {
    int N = *((int*)arg);
    int count = 0, num = 2, sum = 0;

    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    printf("[Thread A] Sum of first %d prime numbers is: %d\n", N, sum);
    return NULL;
}

// Thread B: Prints every 2 seconds
void* threadB(void* arg) {
    time_t start = time(NULL);
    while (difftime(time(NULL), start) <= 100) {
        printf("[Thread 1] Thread 1 running\n");
        sleep(2);
    }
    return NULL;
}

// Thread C: Prints every 3 seconds
void* threadC(void* arg) {
    time_t start = time(NULL);
    while (difftime(time(NULL), start) <= 100) {
        printf("[Thread 2] Thread 2 running\n");
        sleep(3);
    }
    return NULL;
}

int main() {
    int N;
    printf("Enter N (number of primes to sum): ");
    scanf("%d", &N);

    pthread_t tA, tB, tC;

    // Create threads
    pthread_create(&tA, NULL, threadA, &N);
    pthread_create(&tB, NULL, threadB, NULL);
    pthread_create(&tC, NULL, threadC, NULL);

    // Wait for all threads to complete
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    printf("All threads completed.\n");
    return 0;
}
