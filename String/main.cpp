#include "string.hpp"

#include <iostream>
#include <utility>
#include <typeinfo>

int main() {
    string s1 {"Hello"};
    string s2 {"World"};
    string s3 = s1 + s2;
    std::cout << s3 << std::endl;

    string input;
    std::cout << "Enter a string: ";
    std::cin >> input;
    std::cout << "You entered: " << input << std::endl;
    string s4 = std::move(input);
    std::cout << s4 << std::endl;
    s4.append("123456");
    std::cout << s4 << std::endl;
    std::cout << s4.substr(12, 6) << std::endl;
    s4 = "bye";
    std::cout << s4 << std::endl;
    std::cout << s4.size() << std::endl;
    
    s4.insert(1, "may");
    std::cout << s4 << std::endl;
    
    std::cout << (typeid(s4) == typeid("hi"_ms));
    
    auto it = s4.begin();
    std::cout << *it << std::endl;
    
    return 0;
}
