#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <iostream>
#include <type_traits>

template<typename T>
class unique_ptr
{
public:
    unique_ptr(T value);
    unique_ptr(T* ptr = nullptr);
    unique_ptr(unique_ptr&& src) noexcept;
    unique_ptr& operator=(unique_ptr&& src) noexcept;
    ~unique_ptr();

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

public:
    void reset(T* ptr = nullptr);
    T* get() const;
    T& operator*();
    template<typename U = T, typename = std::enable_if_t<!std::is_fundamental_v<U>>>
    T* operator->();
    T* release();

private:
    T* _ptr;
};

#include "unique.hpp"

#endif //UNIQUE_PTR_H