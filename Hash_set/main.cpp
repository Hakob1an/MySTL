#include "set.hpp"
#include <iostream>


void print(const hash_set<int>& mySet)
{
    std::cout << "Size: " << mySet.size()
              << "\nLoad Factor: " << mySet.load_factor()
              << "\nEmpty: " << mySet.empty() << std::endl;

    mySet.print();
    std::cout << std::endl;
}


int main()
{
    hash_set<int> mySet;
    mySet.insert(2);
    auto [ptr1, b1] = mySet.insert(3);
    mySet.insert(4);
    auto [ptr, b] = mySet.insert(12);
    
    //std::cout << ptr->_value << std::endl;
    
    mySet.erase(ptr);
    //print(mySet);

    std::cout << std::endl;

    mySet.erase(ptr1);
    //print(mySet);

    auto ptr2 = mySet.find(2);
    //std::cout << ptr2->_value << std::endl;
    
    hash_set<int> mySet2;
    mySet2 = mySet;
    //print(mySet2);

    hash_set<int> mySet3({1, 2, 3, 4, 5}, 10);
    //print(mySet3);

    hash_set<int> mySet4({1, 2, 3, 4, 5, 12, 22, 25, 32, 42, 52, 56}, 10);
    print(mySet4);
    
    return 0;
}
