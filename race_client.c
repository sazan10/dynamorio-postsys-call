#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define NUM_THREADS 5

volatile int stop = 0;

void* thread_func(void* arg) {
    int id = *((int*)arg);
    while (!stop) {
        // Simulate work
        printf("Thread %d is working...\n", id);
        usleep(100000); // 100 ms
    }
    printf("Thread %d exiting...\n", id);
    return NULL;
}

void* terminator_thread(void* arg) {
    usleep(300000);  // Sleep for 300 ms
    printf("Terminator thread: terminating process.\n");
    stop = 1;
    exit(0);  // Terminate the process
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_t terminator;
    int thread_ids[NUM_THREADS];

    // Create worker threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Create a terminator thread
    if (pthread_create(&terminator, NULL, terminator_thread, NULL) != 0) {
        perror("Failed to create terminator thread");
        return 1;
    }

    // Wait for all threads (should not reach here due to process termination)
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_join(terminator, NULL);

    return 0;
}
