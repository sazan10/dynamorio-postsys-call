#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 100

void* thread_func(void* arg) {
    printf("Thread %ld is running\n", (long)arg);
    // Simulate some work with a sleep
    sleep(1);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create threads
    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, (void*)i)) {
            fprintf(stderr, "Error creating thread %ld\n", i);
            return 1;
        }
    }

    // Wait for threads to finish
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}
