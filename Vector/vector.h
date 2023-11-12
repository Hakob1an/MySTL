#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class vector
{
public:
    vector();
    vector(std::size_t size);
    vector(std::size_t size, T init_value);
    vector(std::initializer_list<T> list);
    vector(const vector& src);
    vector(vector&& src) noexcept;
    ~vector();

public:
    vector& operator=(const vector& rhs);
    vector& operator=(vector&& rhs) noexcept;
    T& operator[](std::size_t ipos);
    T const& operator[](std::size_t ipos) const;
    vector& operator+=(const vector& vec);
    template<typename U>
    friend vector<U> operator+(const vector<U>& vec1, const vector<U>& vec2);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, vector<U>& vec);
    template<typename U>
    friend std::istream& operator>>(std::istream& in, vector<U>& vec);

public:
    void push_back(T value);
    void pop_back();
    T& at(std::size_t pos);
    void reserve(std::size_t capacity);
    void insert(T value, std::size_t pos);
    void remove(std::size_t pos);
    void erase();
    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;
public:
    struct iterator
    {
        using category = std::forward_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        iterator(pointer val) : _ptr{val} {}

        reference operator*() { return *_ptr; }
        pointer operator->() { return _ptr; }
        iterator& operator++() 
        { 
            ++_ptr; 
            return *this; 
        }
        iterator operator++(int) 
        { 
            iterator tmp{*this};
            ++_ptr;
            return tmp; 
        } 
        friend bool operator==(const iterator& iter1, const iterator& iter2) { return iter1._ptr == iter2._ptr; }
        friend bool operator!=(const iterator& iter1, const iterator& iter2) { return iter1._ptr != iter2._ptr; }

    private:
        pointer _ptr;
    };

    iterator begin();
    iterator end();

private:
    void moveFrom(vector& other);
    void swap(vector& src);
    void realloc(std::size_t capacity);

private: 
   std::size_t _size;
   std::size_t _capacity;
   T* _vec;
};

#include "vector.hpp"

#endif //VECTOR_H
