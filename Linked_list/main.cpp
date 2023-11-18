#include "list.h"
#include <iostream>

int main() {
    try {
        list<int> myLinkedList;

        myLinkedList.push_back(1);
        myLinkedList.push_back(2);
        myLinkedList.push_back(3);
        myLinkedList.push_front(0);
		
	myLinkedList.print();
     
        myLinkedList.insert(4, 2);
	myLinkedList.print();
            
        myLinkedList.pop_back();
        myLinkedList.pop_front();
	myLinkedList.print();
		      
        myLinkedList.remove(1);
		        
        std::cout << "Linked List after removal: ";
        myLinkedList.print();
        std::cout << "Size: " << myLinkedList.size() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
