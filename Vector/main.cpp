#include "vector.hpp"
#include <iostream>

void print(vector<int>& vec) 
{
	for (auto& a : vec) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
}

int main() {
    try {
        vector<int> intVector;

        intVector.push_back(1);
        intVector.push_back(2);
        intVector.push_back(3);

        std::cout << "Size: " << intVector.size() << ", Capacity: " << intVector.capacity() << std::endl;

        std::cout << "Element at index 1: " << intVector[1] << std::endl;

        std::cout << "Vector contents: ";
        print(intVector);

        intVector.pop_back();
        std::cout << "After pop_back, size: " << intVector.size() << std::endl;

        intVector.reserve(10);
        std::cout << "After reserving capacity 10, Capacity: " << intVector.capacity() << std::endl;

        intVector.insert(4, 1);
        std::cout << "After inserting 4 at index 1: ";
        print(intVector);

        intVector.erase(1);
        std::cout << "After removing element at index 1: ";
        print(intVector);

        vector<int> anotherVector;
        anotherVector.push_back(5);
        anotherVector.push_back(6);
        
        intVector += anotherVector;
        std::cout << "After += operation: ";
        print(intVector);

        vector<int> copyVector(intVector);
        std::cout << "Copy vector: ";
        print(copyVector);

        vector<int> moveVector(std::move(intVector));
        std::cout << "Move vector: ";
        print(moveVector);

        vector<int> assignedVector;
        assignedVector = copyVector;
        std::cout << "After assignment: ";
        print(assignedVector);

        vector<int> movedVector;
        movedVector = std::move(copyVector);
        std::cout << "After move assignment: ";
        print(moveVector);
        
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
		
		//Using iterators
        vector<int> intVector2; 
        intVector2.push_back(1);
        intVector2.push_back(2);
        intVector2.push_back(3);
        std::cout << intVector2.capacity() << std::endl;
        vector<int>::iterator it = intVector2.begin();
        for (; it != intVector2.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        it = intVector2.begin();
        for (int i = 0; i < intVector2.size(); ++i) {
            std::cout << it[i] << " ";
        }
        std::cout << std::endl;
        
        //Inserting a static array
        int arr[5] = {1, 2, 3, 4, 5};
        vector<int> vec {1, 2, 3};
        vec.insert(arr, 5, 2);
        print(vec);

    } catch (const std::exception& e) {
        std::cerr << "Caught unexpected exception: " << e.what() << std::endl;
    }
    
    return 0;
}
