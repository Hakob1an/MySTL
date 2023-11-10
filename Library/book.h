#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book 
{
public:
   Book(const std::string& title, const std::string& author);

public:
   int getId() const;
   std::string getAuthor() const;
   std::string getTitle() const;
   bool getAvailability() const;
   void setAvailability(bool available);

private:
   static int ID;
   int m_id;
   std::string m_title;
   std::string m_author;
   bool m_isAvailable;
};

#endif //BOOK_H
