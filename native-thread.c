#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NUM_THREADS 653

// Function to be run by each thread
void* thread_func(void* arg) {
    while (1) {
        sleep(1);  // Simulate some work
    }
    return NULL;
}

// Signal handler for SIGSEGV
void signal_handler(int signum) {
    printf("Received signal %d\n", signum);
}

int main() {
    signal(SIGSEGV, signal_handler);  // Install signal handler

    pthread_t threads[NUM_THREADS];

    // Create a large number of threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    printf("Application running with %d threads\n", NUM_THREADS);

    // Keep running indefinitely
    while (1) {
        sleep(1);
    }

    return 0;
}
