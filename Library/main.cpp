#include <iostream>
#include <string>
#include <vector>
#include "library.h"
#include "book.h"
#include "reader.h"


int main() {
    Library lib;
    Reader r1{"Aram"};
    Reader r2{"Ani"};
    Book b1{"OOAD", "Grady Booch"};
    Book b2{"Effective c++", "Scott Meyers"};

    lib.addReader(r1);
    lib.addReader(r2);

    std::cout << "Reader id: " << r1.getId() << ", name: " << r1.getName() << std::endl;

    lib.addBook(b1, 1);
    std::cout << "Book id: " << b1.getId() << ", author: " << b1.getAuthor() << ", title: " << b1.getTitle()<< std::endl;

    lib.addBook(b2, 1);
    lib.issueBook(b1.getId(), r1.getId()); // Issue the book using IDs
    lib.returnBook(b1.getId(), r1.getId()); // Return the book using IDs
    lib.issueBook(4, 5); // This will print "Book not available or not found."

    return 0;
}

