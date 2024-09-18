#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<bool> done(false);

void thread_func() {
    // Sleep to simulate work and allow attach to start
    std::this_thread::sleep_for(std::chrono::seconds(1));
    done = true;
}

int main() {
    std::thread t1(thread_func);
    std::thread t2(thread_func);

    // Simulate attach process by sleeping
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Mark threads as done
    done = true;

    // Wait for threads to exit
    t1.join();
    t2.join();

    return 0;
}
