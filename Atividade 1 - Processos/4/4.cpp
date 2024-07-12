#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>

std::mutex mtx;
std::condition_variable cv;
bool ready_to_allocate = false;
bool ready_to_display = false;
int size;
std::vector<int> vet;

void threadA() {
    std::cout << "Enter the size of the vector: ";
    std::cin >> size;

    // Notify threadB that it can allocate the vector
    std::unique_lock<std::mutex> lock(mtx);
    ready_to_allocate = true;
    cv.notify_all();
}

void threadB() {
    // Wait until threadA has read the size
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready_to_allocate; });

    // Allocate and populate the vector
    vet.resize(size);
    for (int i = 0; i < size; ++i) {
        vet[i] = i * 10; // Example values, can be replaced with actual logic
    }

    // Notify threadC that it can display the vector
    ready_to_display = true;
    cv.notify_all();
}

void threadC() {
    // Wait until threadB has populated the vector
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready_to_display; });

    // Display the vector
    std::cout << "Vector elements: ";
    for (int val : vet) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::thread tA(threadA);
    std::thread tB(threadB);
    std::thread tC(threadC);

    tA.join();
    tB.join();
    tC.join();

    return 0;
}
