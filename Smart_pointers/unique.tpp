#ifndef UNIQUE_PTR_TPP
#define UNIQUE_PTR_TPP

#include "unique.hpp"

template<typename T>
unique_ptr<T>::unique_ptr(T value)
    : _ptr{new int{value}}
{}
template<typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : _ptr{ptr}
{}
template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& src) noexcept
    : _ptr{src._ptr}
{
    src._ptr = nullptr;
}
template<typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& rhs) noexcept
{
    if (this != &rhs) {
        delete _ptr;
        _ptr = rhs._ptr;
        rhs._ptr = nullptr;
    }
    return *this;
}
template<typename T>
unique_ptr<T>::~unique_ptr()
{
    delete _ptr;
}
template<typename T>
void unique_ptr<T>::reset(T* ptr)
{
    delete _ptr;
    _ptr = ptr;
}
template<typename T>
T* unique_ptr<T>::get()
{
    return _ptr;
}
template<typename T>
const T* unique_ptr<T>::get() const
{
    return _ptr;
}
template<typename T>
T& unique_ptr<T>::operator*()
{
    return *_ptr;
}
template<typename T>
const T& unique_ptr<T>::operator*() const
{
    return *_ptr;
}
template<typename T>
template<typename U, typename>
T* unique_ptr<T>::operator->()
{
    return _ptr;
}
template<typename T>
template<typename U, typename>
const T* unique_ptr<T>::operator->() const
{
    return _ptr;
}

#endif //UNIQUE_PTR_TPP
