#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NUM_THREADS 653
#define RUN_DURATION 10  // Run for 10 seconds

// Function to be run by each thread
void* thread_func(void* arg) {
    while (1) {
        sleep(1);  // Simulate some work
    }
    return NULL;
}

// Signal handler for SIGTERM or SIGALRM to terminate the program
void signal_handler(int signum) {
    printf("Received signal %d, terminating application.\n", signum);
    exit(0);  // Exit the application, triggering DynamoRIO detachment
}

int main() {
    signal(SIGSEGV, signal_handler);   // Handle segmentation fault signals
    signal(SIGALRM, signal_handler);   // Handle alarm signals
    signal(SIGTERM, signal_handler);   // Handle termination signals

    pthread_t threads[NUM_THREADS];

    // Create a large number of threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    printf("Application running with %d threads\n", NUM_THREADS);

    // Set an alarm to terminate the program after RUN_DURATION seconds
    alarm(RUN_DURATION);

    // Keep running indefinitely until the signal handler terminates the app
    while (1) {
        sleep(1);
    }

    return 0;
}
