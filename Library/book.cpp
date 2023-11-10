#include "book.h"

#include <string>

int Book::ID = 0;

Book::Book(const std::string& title, const std::string& author) 
: m_id{++ID}  // Increment and assign a unique ID to each book
, m_title{title}
, m_author{author}
, m_isAvailable{true} 
{}
int Book::getId() const 
{
    return m_id;
}
std::string Book::getTitle() const 
{
    return m_title;
}
std::string Book::getAuthor() const 
{
    return m_author;
}
bool Book::getAvailability() const 
{
    return m_isAvailable;
}
void Book::setAvailability(bool available) 
{
    m_isAvailable = available;
}
