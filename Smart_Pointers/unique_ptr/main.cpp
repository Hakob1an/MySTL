#include "unique.h"

#include <iostream>

class A
{
public:
    void get() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int main()
{
    unique_ptr<int> up1(10);
    unique_ptr<int> up2(new int(100));
    unique_ptr<A> up3(new A);
    up3->get();
    std::cout << *up1 << std::endl;
    std::cout << *up2 << std::endl;
    return 0;
}
