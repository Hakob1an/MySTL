#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

class Reader 
{
public:
   Reader(const std::string& name);
   int getId() const;
   std::string getName() const;
   std::vector<int> getIssuedBooks() const;
   void issueBook(int id);
   void returnBook(int id);

private:
   static int ID;
   int reader_id;
   std::string m_name;
   std::vector<int> m_issuedBooks; 
};

#endif //READER_H
