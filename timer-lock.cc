#include <iostream>
#include <thread>
#include <mutex>
#include <csignal>
#include <unistd.h>

std::mutex innermost_lock;
std::mutex shared_itimer_lock;

void signal_handler(int signal) {
    std::lock_guard<std::mutex> lock1(shared_itimer_lock);
    std::lock_guard<std::mutex> lock2(innermost_lock); // Potential rank order violation
}

void thread_func() {
    while (true) {
        std::lock_guard<std::mutex> lock1(innermost_lock);
        std::lock_guard<std::mutex> lock2(shared_itimer_lock); // Acquire in the reverse order
        // Do some work
        sleep(1);
    }
}

int main() {
    signal(SIGALRM, signal_handler);
    std::thread t1(thread_func);
    std::thread t2(thread_func);

    // Trigger an alarm
    alarm(1);

    t1.join();
    t2.join();
    return 0;
}
