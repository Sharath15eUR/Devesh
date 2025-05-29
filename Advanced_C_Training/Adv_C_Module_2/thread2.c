#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

// --- Signal Handler ---
void sig_handler(int sig) {
    printf("\n[Signal] Caught signal %d (e.g., Ctrl+C). Ignoring.\n", sig);
}

// --- Prime Checker ---
int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0) return 0;
    return 1;
}

// --- Thread A: Sum of N primes ---
void* threadA(void* arg) {
    int N = *((int*)arg);
    int count = 0, num = 2, sum = 0;

    printf("[Thread A] Started: Calculating sum of first %d primes...\n", N);

    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    printf("[Thread A] Finished: Sum = %d\n", sum);
    return NULL;
}

// --- Thread B: Prints every 2 sec ---
void* threadB(void* arg) {
    printf("[Thread B] Started: Printing every 2 seconds\n");
    time_t start = time(NULL);

    while (difftime(time(NULL), start) <= 100) {
        printf("[Thread B] Thread 1 running\n");
        sleep(2);
    }

    printf("[Thread B] Finished\n");
    return NULL;
}

// --- Thread C: Prints every 3 sec ---
void* threadC(void* arg) {
    printf("[Thread C] Started: Printing every 3 seconds\n");
    time_t start = time(NULL);

    while (difftime(time(NULL), start) <= 100) {
        printf("[Thread C] Thread 2 running\n");
        sleep(3);
    }

    printf("[Thread C] Finished\n");
    return NULL;
}

// --- Main Program ---
int main() {
    // Register signal handler
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);  // Handle Ctrl+C
    sigaction(SIGTERM, &sa, NULL); // Handle kill

    int N;
    printf("Enter N (number of primes to sum): ");
    scanf("%d", &N);

    pthread_t tA, tB, tC;
    clock_t start_time = clock();

    printf("[Main] Starting all threads...\n");

    pthread_create(&tA, NULL, threadA, &N);
    pthread_create(&tB, NULL, threadB, NULL);
    pthread_create(&tC, NULL, threadC, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("[Main] All threads completed.\n");
    printf("[Main] Total execution time: %.2f seconds\n", total_time);

    return 0;
}
