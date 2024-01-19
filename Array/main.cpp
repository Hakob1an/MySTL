#include "array.hpp"

template<typename T, std::size_t N>
array<T, N> to_array(T (&arr)[N])
{
    array<T, N> res;
    for (std::size_t i{0}; i < N; ++i) {
        res[i] = arr[i];
    }
    return res;
}
int main()
{
    array<int, 5> intArray;
    intArray.set(0, 1);
    intArray.set(1, 2);
    intArray.set(2, 3);
    intArray.set(3, 4);
    intArray.set(4, 5);
    
    std::cout << "Elements: ";
    intArray.traverse(print<int>);
    std::cout << "Front element: " << intArray.front() << std::endl;
    std::cout << "Back element: " << intArray.back() << std::endl;
    std::cout << "Is Empty?: " << intArray.empty() << std::endl;
    std::cout << "Size: " << intArray.size() << std::endl;

    array<bool, 4> boolArray;
    boolArray.set(0, true); 
    boolArray.set(1, false);
    boolArray.set(2, true); 
    boolArray.set(3, true);
    
    std::cout << "Elements: ";
    boolArray.traverse(print<bool>);
    std::cout << "Front element: " << boolArray.front() << std::endl;
    std::cout << "Back element: " << boolArray.back() << std::endl;
    std::cout << "Is Empty?: " << boolArray.empty() << std::endl;
    std::cout << "Size: " << boolArray.size() << std::endl;
    
    int arr[4] = {1, 2, 3, 4};
    array<int, 4> tarr = to_array<int, 4>(arr);
    tarr.traverse(print<int>);
    return 0;
}
