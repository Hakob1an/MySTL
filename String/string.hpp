#ifndef STRING_HPP
#define STRING_HPP

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <utility>

struct string_iterator
{
	using value_type = char;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using pointer = value_type*;
    using const_pointer = const pointer;
    using category = std::random_access_iterator_tag;
	
	string_iterator(pointer p) : _ptr{p} 
	{}
	
	reference operator*() { return *_ptr; }
    pointer operator->() { return _ptr; }
    string_iterator& operator++() { ++_ptr; return *this; }
    string_iterator operator++(int) { string_iterator tmp{*this}; ++_ptr; return tmp; } 
    string_iterator& operator--() { --_ptr; return *this; }
    string_iterator operator--(int) { string_iterator tmp{*this}; --_ptr; return tmp; }
    string_iterator operator+(difference_type n) { return string_iterator(_ptr + n); }
    string_iterator operator-(difference_type n) { return string_iterator(_ptr - n); }
    difference_type operator-(string_iterator& ob){ return _ptr - ob._ptr; }
    string_iterator operator+=(difference_type n) { _ptr += n; return *this; }
    string_iterator operator-=(difference_type n) { _ptr -= n; return *this; }
    reference operator[](difference_type n) { return _ptr[n]; }

    friend bool operator==(const string_iterator& iter1, const string_iterator& iter2) { return iter1._ptr == iter2._ptr; }
    friend bool operator!=(const string_iterator& iter1, const string_iterator& iter2) { return iter1._ptr != iter2._ptr; }
    friend bool operator>(const string_iterator& iter1, const string_iterator& iter2) { return iter1._ptr > iter2._ptr; }
    friend bool operator>=(const string_iterator& iter1, const string_iterator& iter2) { return iter1._ptr >= iter2._ptr; }
    friend bool operator<(const string_iterator& iter1, const string_iterator& iter2) { return iter1._ptr < iter2._ptr; }
    friend bool operator<=(const string_iterator& iter1, const string_iterator& iter2) { return iter1._ptr <= iter2._ptr; }
	
	pointer _ptr;
};

class string
{
public:
    using value_type = char;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = string_iterator;
    using const_iterator = const iterator;

public:
    string();
    explicit string(const_pointer);
    string(const string&);
    string(string&&) noexcept;
    string(const std::string&);
    ~string();

public:
    string& operator=(const string&);
    string& operator=(string&&) noexcept;
    string& operator=(const_pointer);
    
    string& operator+=(const string&);
    string& operator+=(const_pointer);
    string operator+(const string&) const;
    friend string operator+(const string&, const_pointer);
    friend string operator+(const_pointer, const string&);
    
    reference operator[](size_type);
    const_reference operator[](size_type) const;

    bool operator==(const string&) const;
    bool operator==(const_pointer) const;
    friend bool operator==(const_pointer, const string&);
    bool operator!=(const string&) const;
    bool operator!=(const_pointer) const;
    friend bool operator!=(const_pointer, const string&);
    bool operator<(const string&) const;
    bool operator<(const_pointer) const;
    friend bool operator<(const_pointer, const string&);
    bool operator<=(const string&) const;
    bool operator<=(const_pointer) const;
    friend bool operator<=(const_pointer, const string&);
    bool operator>(const string&) const;
    bool operator>(const_pointer) const;
    friend bool operator>(const_pointer, const string&);
    bool operator>=(const string&) const;
    bool operator>=(const_pointer) const;
    friend bool operator>=(const_pointer, const string&);

    friend std::ostream& operator<<(std::ostream&, const string&);
    friend std::istream& operator>>(std::istream&, string&);
    
    friend string to_string(int);
    friend string to_string(double);
    friend int stoi(const string&);
    friend double stod(const string&);
    
    size_type size() const;
    size_type length() const;
    size_t capacity() const;
    bool empty() const;
    const_pointer c_str() const;
    pointer data() const;
    value_type front() const;
    value_type back() const;
    void append(const_pointer);
    void append(const string&);
    string& insert(size_type, const_pointer);
    string substr(size_type, size_type);
    reference at(size_type);
    const_reference at(size_type) const;
    void clear() noexcept;
    
    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

private:
    inline static constexpr size_type _maxSize = 20;
    bool _isOnHeap;
    size_type _size;
    union {
        pointer _onheap;
        value_type _onstack[_maxSize];
    };
    void copyFrom(const string&);
};

string operator""_ms(string::const_pointer, string::size_type);

#endif //STRING_HPP
