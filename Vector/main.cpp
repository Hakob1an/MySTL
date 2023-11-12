#include "vector.h"

#include <iostream>

int main() {
    try {
        vector<int> intVector;

        intVector.push_back(1);
        intVector.push_back(2);
        intVector.push_back(3);

        std::cout << "Size: " << intVector.size() << ", Capacity: " << intVector.capacity() << std::endl;

        std::cout << "Element at index 1: " << intVector[1] << std::endl;

        std::cout << "Vector contents: " << intVector << std::endl;

        intVector.pop_back();
        std::cout << "After pop_back, size: " << intVector.size() << std::endl;

        intVector.reserve(10);
        std::cout << "After reserving capacity 10, Capacity: " << intVector.capacity() << std::endl;

        intVector.insert(4, 1);
        std::cout << "After inserting 4 at index 1: " << intVector << std::endl;

        intVector.remove(1);
        std::cout << "After removing element at index 1: " << intVector << std::endl;

        vector<int> anotherVector;
        anotherVector.push_back(5);
        anotherVector.push_back(6);
        intVector += anotherVector;
        std::cout << "After += operation: " << intVector << std::endl;

        vector<int> copyVector(intVector);
        std::cout << "Copy vector: " << copyVector << std::endl;

        vector<int> moveVector(std::move(intVector));
        std::cout << "Move vector: " << moveVector << std::endl;

        vector<int> assignedVector;
        assignedVector = copyVector;
        std::cout << "After assignment: " << assignedVector << std::endl;

        vector<int> movedVector;
        movedVector = std::move(copyVector);
        std::cout << "After move assignment: " << movedVector << std::endl;
        
        std::cout << std::endl;

        vector<double> doubleVector;
        try {
            int value = doubleVector[5]; // This should throw an exception
        } catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }
        try {
            doubleVector.pop_back(); // This should throw an exception
        } catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }
        try {
            int value = doubleVector.at(5); // This should throw an exception
        } catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }
        try {
            doubleVector.insert(42, 10); // This should throw an exception
        } catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }

        vector<int> intVector2{1, 2, 3, 4};
        vector<int>::iterator it = intVector2.begin();
        for (; it != intVector2.end(); ++it) {
            std::cout << *it << " ";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Caught unexpected exception: " << e.what() << std::endl;
    }

    return 0;
}
