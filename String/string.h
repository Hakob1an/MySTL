#ifndef STRING_H
#define STRING_H

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstring>

class string
{
public:
    string();
    explicit string(const char* str);
    string(const string& src);
    string(string&& src) noexcept;
    string(const std::string& str);
    ~string();

public:
    string& operator=(const string&);
    string& operator=(string&&) noexcept;
    string& operator=(const char*);
    
    string& operator+=(const string&);
    string& operator+=(const char*);
    string operator+(const string&) const;
    friend string operator+(const string&, const char*);
    friend string operator+(const char*, const string&);
    
    bool operator==(const string&) const;
    bool operator==(const char*) const;
    friend bool operator==(const char*, const string&);
    bool operator!=(const string&) const;
    bool operator!=(const char*) const;
    friend bool operator!=(const char*, const string&);
    bool operator<(const string&) const;
    bool operator<(const char*) const;
    friend bool operator<(const char*, const string&);
    bool operator<=(const string&) const;
    bool operator<=(const char*) const;
    friend bool operator<=(const char*, const string&);
    bool operator>(const string&) const;
    bool operator>(const char*) const;
    friend bool operator>(const char*, const string&);
    bool operator>=(const string&) const;
    bool operator>=(const char*) const;
    friend bool operator>=(const char*, const string&);

    friend std::ostream& operator<<(std::ostream&, const string&);
    friend std::istream& operator>>(std::istream&, string&);
    
    friend string to_string(int);
    friend string to_string(double);
    friend int stoi(const string&);
    friend double stod(const string&);
    
    std::size_t size() const;
    const char* c_str() const;
    void append(const char* str);
    string substr(std::size_t, size_t);

private:
    inline static constexpr std::size_t m_maxSize = 16;
    bool m_onHeap;
    struct dyn_str
    {
        std::size_t size;
        char* str;
    };
    union {
        dyn_str m_onheap;
        char m_onstack[m_maxSize];
    };
    void copyFrom(const string&);
};

#endif //STRING_H
