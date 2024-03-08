#include <iostream>
#include "map.hpp"  // Replace with the actual header file name

int main() {
    using KeyType = int;  // Change this based on your key type
    using ValueType = std::string;  // Change this based on your value type
    using HashMapType = hash_map<KeyType, ValueType>;

    // Create a hash map
    HashMapType myHashMap;

    // Insert some key-value pairs
    myHashMap.insert(1, "One");
    myHashMap.insert(2, "Two");
    myHashMap.insert(3, "Three");
    myHashMap.insert(4, "Four");
    myHashMap.insert(5, "Five");

    // Print the contents of the hash map
    myHashMap.print();

    // Find and print a value
    int keyToFind = 3;
    auto foundNode = myHashMap.find(keyToFind);
    if (foundNode) {
        std::cout << "Value for key " << keyToFind << ": " << foundNode->_value << std::endl;
    } else {
        std::cout << "Key " << keyToFind << " not found." << std::endl;
    }

    std::cout << "Value for key 2: " << myHashMap[2] << std::endl;

    // Modify elements using operator[]
    myHashMap[2] = "New Two";

    // Access non-existing element using operator[]
    std::cout << "Value for key 5: " << myHashMap[5] << std::endl;

    // Check if a key exists using count
    int keyToCheck = 3;
    if (myHashMap.count(keyToCheck)) {
        std::cout << "Key " << keyToCheck << " exists!" << std::endl;
    } else {
        std::cout << "Key " << keyToCheck << " does not exist!" << std::endl;
    }

    // Print the contents of the hash_map
    myHashMap.print();

    return 0;
}
