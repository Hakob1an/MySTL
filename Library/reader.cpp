#include "reader.h"

#include <string>
#include <vector>
#include <algorithm>

int Reader::ID = 0;

Reader::Reader(const std::string& name) 
    : reader_id{++ID} // Increment and assign a unique ID to each reader
    , m_name{name} 
{}
int Reader::getId() const 
{
    return reader_id;
}
std::string Reader::getName() const 
{
    return m_name;
}
std::vector<int> Reader::getIssuedBooks() const 
{
    return m_issuedBooks;
}
void Reader::issueBook(int id) 
{
    m_issuedBooks.push_back(id);
}
// Method to return a book, removing it from the list of issued books
void Reader::returnBook(int id) 
{
    m_issuedBooks.erase(std::remove(m_issuedBooks.begin(), m_issuedBooks.end(), id), m_issuedBooks.end());
}
