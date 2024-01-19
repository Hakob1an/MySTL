#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <bitset>

template<typename T, std::size_t N>
class array
{
public:
    array();
    T front() const;
    T back() const;
    void traverse(void (*)(T)) const;
    std::size_t size() const;
    bool empty() const;
    T& operator[](std::size_t);
    void set(std::size_t, T);

private:
    T m_elems[N];
    std::size_t m_size;
};

//specialization for bool
template<std::size_t N>
class array<bool, N>
{
public:
    array();
    bool front() const;
    bool back() const;
    void traverse(void (*)(bool)) const;
    std::size_t size() const;
    bool empty() const;
    bool operator[](std::size_t);
    void set(std::size_t, bool);

private:
    std::bitset<N> m_elems;
    std::size_t m_size;
};

#include "array.tpp"

#endif //ARRAY_HPP
