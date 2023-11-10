#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include "reader.h"

#include <string>
#include <vector>
#include <utility>

class Library 
{
public:
   void addReader(const Reader& reader);
   void addBook(const Book& book, int count);
   void issueBook(int book_id, int reader_id);
   void returnBook(int book_id, int reader_id);
   void changeBookCount(int book_id);
   Book getBook(int index) const;
   Reader getReader(int index) const;

private: 
   std::vector<std::pair<Book, int>> m_books;
   std::vector<Reader> m_readers;
};

#endif //LIBRARY_H
