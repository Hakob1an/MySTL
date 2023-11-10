#include "book.h"
#include "reader.h"
#include "library.h"

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

void Library::addReader(const Reader& reader) 
{
    // Check if the reader ID already exists
    if (std::find_if(m_readers.begin(), m_readers.end(), [&](const Reader& r) { return r.getId() == reader.getId(); }) != m_readers.end()) {
        std::cout << "The reader ID already exists." << std::endl;
        return;
    }
    
    m_readers.push_back(reader);
}
void Library::addBook(const Book& book, int count) 
{
    // Check if the book already exists in the library
    auto book_it = std::find_if(m_books.begin(), m_books.end(), [&](const std::pair<Book, int>& b) { return b.first.getId() == book.getId(); });
    if (book_it != m_books.end()) {
        book_it->second += count;
    } else {
        m_books.push_back({book, count});
    }
}
void Library::issueBook(int book_id, int reader_id) 
{
    // Find the book in the library
    auto book_it = std::find_if(m_books.begin(), m_books.end(), [&](const std::pair<Book, int>& b) { return b.first.getId() == book_id; });

    if (book_it != m_books.end() && book_it->first.getAvailability() && book_it->second >= 1) {
    	// Find the reader in the library
        auto reader_it = std::find_if(m_readers.begin(), m_readers.end(), [&](const Reader& r) { return r.getId() == reader_id; });
        if (reader_it != m_readers.end()) {
            // Issue the book to the reader
            reader_it->issueBook(book_id);
            book_it->first.setAvailability(false);
            book_it->second--;  // Decrease the count
        } else {
            std::cout << "Reader not found." << std::endl;
        }
    } else {
        std::cout << "Book not available or not found." << std::endl;
    }
}
void Library::returnBook(int book_id, int reader_id) 
{
    // Find the book in the library
    auto book_it = std::find_if(m_books.begin(), m_books.end(), [&](const std::pair<Book, int>& b) { return b.first.getId() == book_id; });

    if (book_it != m_books.end() && !book_it->first.getAvailability()) {
        // Find the reader in the library
        auto reader_it = std::find_if(m_readers.begin(), m_readers.end(), [&](const Reader& r) { return r.getId() == reader_id; });
        if (reader_it != m_readers.end()) {
            // Return the book and update its availability
            reader_it->returnBook(book_id);
            book_it->first.setAvailability(true);
            book_it->second++;  // Increase the count
        } else {
            std::cout << "Reader not found." << std::endl;
        }
    } else {
        std::cout << "Book not issued or not found." << std::endl;
    }
}
Book Library::getBook(int id) const 
{
    auto book_it = std::find_if(m_books.begin(), m_books.end(), [&](const std::pair<Book, int>& b) { return b.first.getId() == id; });
    if (book_it != m_books.end()) {
        return book_it->first;
    } 
    
    throw std::runtime_error("The book is not found."); 
}
Reader Library::getReader(int id) const 
{
    auto reader_it = std::find_if(m_readers.begin(), m_readers.end(), [&](const Reader& r) { return r.getId() == id; });
    if (reader_it != m_readers.end()) {
        return *reader_it;
    }
    
    throw std::runtime_error("The reader is not found.");
}

