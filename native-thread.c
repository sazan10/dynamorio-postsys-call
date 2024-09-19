#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 653

// Thread function simulating work
void* thread_func(void* arg) {
    // Simulate thread work
    while (1) {
        sleep(1);
    }
    return NULL;
}

// Signal handler for SIGSEGV
void signal_handler(int signum) {
    printf("SIGSEGV received: %d\n", signum);
    // Simulate segmentation fault by dereferencing a null pointer
    int* null_ptr = NULL;
    *null_ptr = 42;
}

int main() {
    signal(SIGSEGV, signal_handler);  // Install signal handler

    pthread_t threads[NUM_THREADS];

    // Create a large number of threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    printf("Attached to %d threads\n", NUM_THREADS);

    // Simulate detaching from threads (where the crash occurs)
    printf("Detaching from threads...\n");
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_cancel(threads[i]);
        pthread_join(threads[i], NULL);
    }

    printf("Detached from all threads.\n");
    return 0;
}
