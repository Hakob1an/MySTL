#include <iostream>
#include "shared.h"

int main() {
    // Creating shared_ptr and weak_ptr with an integer value
    shared_ptr<int> shared1(new int(42));
    weak_ptr<int> weak1(shared1);

    // Lock the weak_ptr to create a new shared_ptr
    shared_ptr<int> shared2 = weak1.lock();

    // Print the value using the new shared_ptr
    if (shared2) {
        std::cout << "Shared2: " << *shared2 << std::endl;
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    // Modify the value through one of the shared_ptrs
    *shared1 = 100;

    // Print the modified value through the other shared_ptr
    if (shared2) {
        std::cout << "Shared2 after modification: " << *shared2 << std::endl;
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    // Reset shared1 to a new value
    shared1.reset(new int(200));

    // Create a weak_ptr from the updated shared_ptr
    weak_ptr<int> weak2(shared1);

    // Lock the weak_ptr to create another shared_ptr
    shared_ptr<int> shared3 = weak2.lock();

    // Print the value using the new shared_ptr
    if (shared3) {
        std::cout << "Shared3: " << *shared3 << std::endl;
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    // Create shared_ptr with a null pointer
    shared_ptr<int> shared4{};

    // Create weak_ptr from shared_ptr with a null pointer
    weak_ptr<int> weak3(shared4);

    // Lock the weak_ptr with a null shared_ptr
    shared_ptr<int> shared5 = weak3.lock();

    // Print the value using the new shared_ptr
    if (shared5) {
        std::cout << "Shared5: " << *shared5 << std::endl; // This should not be reached
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    return 0;
}
