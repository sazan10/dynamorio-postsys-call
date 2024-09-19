#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
volatile int ready = 0;

void alarm_handler(int signum) {
    // Simulate holding the lock when an alarm is received
    pthread_mutex_lock(&lock);
    printf("Alarm received. Holding lock.\n");
    sleep(1); // Simulate holding the lock for a while
    pthread_mutex_unlock(&lock);
}

void* thread_func(void* arg) {
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    pthread_mutex_lock(&lock);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    // Simulate thread blocking at a safe spot
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);

    pthread_mutex_lock(&lock);
    while (!ready) {
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);

    // Send alarm signal to trigger the race condition
    alarm(1);

    // Detach thread, simulating the SUSPEND_SIGNAL
    pthread_join(tid, NULL);

    return 0;
}
