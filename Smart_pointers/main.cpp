#include <iostream>
#include "memory.h"

class A
{
public:
    void get() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

struct B
{
    B(int a, double b) {}
};

int main() {
    unique_ptr<int> up1(10);
    unique_ptr<int> up2(new int(100));
    unique_ptr<A> up3(new A);
    up3->get();
    std::cout << *up1 << std::endl;
    std::cout << *up2 << std::endl;

    shared_ptr<int> shared1(new int(42));
    weak_ptr<int> weak1(shared1);

    shared_ptr<int> shared2 = weak1.lock();

    if (shared2) {
        std::cout << "Shared2: " << *shared2 << std::endl;
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    *shared1 = 100;

    if (shared2) {
        std::cout << "Shared2 after modification: " << *shared2 << std::endl;
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    shared1.reset(new int(200));

    weak_ptr<int> weak2(shared1);

    shared_ptr<int> shared3 = weak2.lock();

    if (shared3) {
        std::cout << "Shared3: " << *shared3 << std::endl;
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    shared_ptr<int> shared4{};
  
    weak_ptr<int> weak3(shared4);

    shared_ptr<int> shared5 = weak3.lock();

    if (shared5) {
        std::cout << "Shared5: " << *shared5 << std::endl; 
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    auto k = make_shared<int>(43);
    std::cout << *k << std::endl;

    auto u = make_unique<double>(3.14);
    std::cout << *u << std::endl;

    auto s1 = make_shared<B>(4, 5.5);
    auto s2 = make_unique<B>(12, 3.14);

    return 0;
}
