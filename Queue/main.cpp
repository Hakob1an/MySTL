#include "lqueue.hpp"
#include <iostream>

int main() {
    try {
        queue<int> intQueue;

        intQueue.push(1);
        intQueue.push(2);
        intQueue.push(3);

        std::cout << "Front of intQueue: " << intQueue.front() << std::endl;
        std::cout << "Back of intQueue: " << intQueue.back() << std::endl;
        std::cout << "Size of intQueue: " << intQueue.size() << std::endl;

        intQueue.pop();
        std::cout << "After dequeue, Front of intQueue: " << intQueue.front() << std::endl;

        queue<std::string> stringQueue;

        stringQueue.push("One");
        stringQueue.push("Two");
        stringQueue.push("Three");

        std::cout << "Front of stringQueue: " << stringQueue.front() << std::endl;
        std::cout << "Back of stringQueue: " << stringQueue.back() << std::endl;
        std::cout << "Size of stringQueue: " << stringQueue.size() << std::endl;

        queue<int> copiedIntQueue(intQueue);
        std::cout << "Copied intQueue is equal: " << (copiedIntQueue == intQueue) << std::endl;

        queue<int> smallerQueue;
        smallerQueue.push(1);
        smallerQueue.push(2);

        std::cout << "Comparison: intQueue > smallerQueue: " << (intQueue > smallerQueue) << std::endl;
        std::cout << "Comparison: intQueue < smallerQueue: " << (intQueue < smallerQueue) << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
