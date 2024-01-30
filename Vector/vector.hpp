#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <initializer_list>

template<typename T>
struct viterator
{
    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
    using category = std::random_access_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    viterator(pointer val) : _ptr{val} {}

    reference operator*() { return *_ptr; }
    pointer operator->() { return _ptr; }
    viterator& operator++() { ++_ptr; return *this; }
    viterator operator++(int) { viterator tmp{*this}; ++_ptr; return tmp; } 
    viterator& operator--() { --_ptr; return *this; }
    viterator operator--(int) { viterator tmp{*this}; --_ptr; return tmp; }
    viterator operator+(difference_type n) { return viterator(_ptr + n); }
    viterator operator-(difference_type n) { return viterator(_ptr - n); }
    difference_type operator-(viterator& ob){ return _ptr - ob._ptr; }
    viterator operator+=(difference_type n) { _ptr += n; return *this; }
    viterator operator-=(difference_type n) { _ptr -= n; *this; }
    reference operator[](difference_type n) { return _ptr[n]; }

    friend bool operator==(const viterator& iter1, const viterator& iter2) { return iter1._ptr == iter2._ptr; }
    friend bool operator!=(const viterator& iter1, const viterator& iter2) { return iter1._ptr != iter2._ptr; }
    friend bool operator>(const viterator& iter1, const viterator& iter2) { return iter1._ptr > iter2._ptr; }
    friend bool operator>=(const viterator& iter1, const viterator& iter2) { return iter1._ptr >= iter2._ptr; }
    friend bool operator<(const viterator& iter1, const viterator& iter2) { return iter1._ptr < iter2._ptr; }
    friend bool operator<=(const viterator& iter1, const viterator& iter2) { return iter1._ptr <= iter2._ptr; }

private:
    pointer _ptr;
};


template<typename T>
class vector
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = viterator<T>;
    using const_iterator = const iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
    constexpr vector();
    explicit vector(size_type size);
    explicit vector(size_type size, T init_value);
    constexpr vector(std::initializer_list<T> list);
    constexpr vector(const vector& src);
    constexpr vector(vector&& src) noexcept;
    ~vector();

public:
    constexpr vector& operator=(const vector& rhs);
    constexpr vector& operator=(vector&& rhs) noexcept;
    constexpr vector& operator=(std::initializer_list<T> list);
    reference operator[](size_type ipos);
    const_reference operator[](size_type ipos) const;
    vector& operator+=(const vector& vec);
    template<typename U>
    friend vector<U> operator+(const vector<U>& vec1, const vector<U>& vec2);

public:
    constexpr void push_back(const T& value);
    constexpr void pop_back();
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    constexpr void reserve(size_type capacity);
    constexpr void insert(T value, size_type pos);
    constexpr iterator insert(iterator pos, const T& value);
    void insert(T arr[], size_type size, size_type pos);
    constexpr void erase(size_type pos);
    constexpr iterator erase(iterator pos);
    constexpr iterator erase(iterator first, iterator last);
    constexpr void clear() noexcept;
    constexpr size_type size() const;
    constexpr size_type capacity() const;
    constexpr bool empty() const;
    void resize(size_type capacity);

public:
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

private:
    void moveFrom(vector& other);
    void swap(vector& src);
    
private: 
   size_type _size;
   size_type _capacity;
   T* _vec;
};

#include "vector.tpp"

#endif //VECTOR_HPP
