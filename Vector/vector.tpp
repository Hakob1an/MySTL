#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "vector.hpp"

template<typename T>
vector<T>::vector()
    : _size{0}
    , _capacity{0}
    , _vec{nullptr}
{}
template<typename T>
vector<T>::vector(std::size_t size)
    : _size{0}
    , _capacity{size}
    , _vec{new T[size]{}}
{}
template<typename T>
vector<T>::vector(std::size_t size, T init_value)
    : _size{size}
    , _capacity{size}
    , _vec{new T[size]{}}
{
    for (std::size_t i = 0; i < size; ++i) {
        _vec[i] = init_value;
    }
}
template<typename T>
vector<T>::vector(std::initializer_list<T> list)
{
    for (const auto& i : list) {
        push_back(i);
    }
}
template<typename T>
vector<T>::vector(const vector<T>& src)
    : _size{src._size}
    , _capacity{src._capacity}
    , _vec{new T[_size]}
{
    for (std::size_t i{0}; i < _size; ++i) {
        _vec[i] = src._vec[i];
    }
}
template<typename T>
vector<T>::vector(vector<T>&& src) noexcept
    : _size{src._size}
    , _capacity{src._capacity}
    , _vec{src._vec}
{
    src._size = src._capacity = 0;
    src._vec = nullptr;
}
template<typename T>
vector<T>::~vector()
{
    delete[] _vec;
}
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& rhs)
{
    vector<T> tmp{rhs};
    swap(tmp);
    return *this;
}
template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& rhs) noexcept
{
    moveFrom(rhs);
    return *this;
}
template<typename T>
T const& vector<T>::operator[](std::size_t ipos) const
{
    if (ipos >= _size) {
        throw std::out_of_range("Invalid index.");
    }
    return _vec[ipos];
}
template<typename T>
T& vector<T>::operator[](std::size_t ipos)
{
    return const_cast<T&>(static_cast<vector<T> const&>(*this)[ipos]);
}
template<typename T>
vector<T>& vector<T>::operator+=(const vector& vec)
{
    if (_size + vec._size > _capacity) {
        realloc(_size + vec._size);
    }
    for (std::size_t i{0}; i < vec._size; ++i) {
        _vec[_size + i] = vec._vec[i];
    }
    _size += vec._size;
    return *this;
}
template<typename T>
vector<T> operator+(const vector<T>& vec1, const vector<T>& vec2)
{
    vector<T> res{vec1};
    res += vec2;
    return res;
}
template<typename T>
std::ostream& operator<<(std::ostream& out, vector<T>& vec)
{
    for (std::size_t i{0}; i < vec._size; ++i) {
        out << vec._vec[i] << " ";
    }
    return out;
}
template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    T val;
    while (in >> val) {
        vec.push_back(val);
    }
    return in;
}
template<typename T>
void vector<T>::push_back(T value)
{
    if (_size == _capacity) {
        realloc(_capacity * 2);
    }
    _vec[_size] = value;
    ++_size;
}
template<typename T>
void vector<T>::pop_back()
{
    if (empty()) {
        throw std::out_of_range("The vector is empty.");
    }
    --_size;
    if (_size == _capacity / 2) {
        realloc(_capacity / 2);
    }
}
template<typename T>
T& vector<T>::at(std::size_t pos) 
{
    if (pos >= _capacity) {
        throw std::out_of_range("Invalid index.");
    }
    return _vec[pos];
}
template<typename T>
void vector<T>::reserve(std::size_t capacity)
{
    realloc(capacity);
}
template<typename T>
void vector<T>::insert(T value, std::size_t pos)
{
    if (pos >= _size) {
        throw std::out_of_range("Invalid index.");
    }
    if (empty() || pos == _size - 1) {
        push_back(value);
        return;
    }
    ++_size;
    if (_size == _capacity) {
        realloc(_capacity * 2);
    }
    for (std::size_t i{_size - 1}; i > pos; --i) {
        _vec[i] = _vec[i - 1];
    }
    _vec[pos] = value;
}
template<typename T>
void vector<T>::remove(std::size_t pos)
{
    if (empty()) {
        throw std::runtime_error("Vector is empty.");
    }
    if (pos >= _size) {
        throw std::out_of_range("Invalid index.");
    }
    --_size;
    for (std::size_t i{pos}; i < _size; ++i) {
        _vec[i] = _vec[i + 1];
    }
    if (_size <= _capacity / 2) {
        realloc(_capacity / 2);
    }
}
template<typename T>
void vector<T>::erase()
{
    _size = _capacity = 0;
    delete[] _vec;
    _vec = nullptr;
}
template<typename T>
std::size_t vector<T>::size() const
{
    return _size;
}
template<typename T>
std::size_t vector<T>::capacity() const
{
    return _capacity;
}
template<typename T>
bool vector<T>::empty() const
{
    return _size == 0;
}
template<typename T>
typename vector<T>::iterator vector<T>::begin()
{
    return iterator{_vec};
}
template<typename T>
typename vector<T>::iterator vector<T>::end()
{
    return iterator{_vec + _size};
}
template<typename T>
void vector<T>::moveFrom(vector& vec)
{
    _size = std::exchange(vec._size, 0);
    _capacity = std::exchange(vec._capacity, 0);
    _vec = std::exchange(vec._vec, nullptr);
}
template<typename T>
void vector<T>::swap(vector& vec)
{
    std::swap(_size, vec._size);
    std::swap(_capacity, vec._capacity);
    std::swap(_vec, vec._vec);
}
template<typename T>
void vector<T>::realloc(std::size_t capacity)
{
    if (capacity == 0) {
        capacity = 1;
    }
    T* tmp = new T[capacity];
    for (std::size_t i{0}; i < _size; ++i) {
        tmp[i] = _vec[i];
    }
    delete[] _vec;
    _vec = tmp;
    _capacity = capacity;
}

#endif //VECTOR_TPP
