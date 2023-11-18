#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <type_traits>
#include "control_block.hpp"
#include "weak.hpp"

template<typename T>
class weak_ptr;

template<typename T>
class shared_ptr
{
public:
    shared_ptr(T value);
    shared_ptr(T* ptr = nullptr);
    shared_ptr(const shared_ptr&);
    ~shared_ptr();

    shared_ptr& operator=(const shared_ptr&);
    shared_ptr(shared_ptr&& src) noexcept;
    shared_ptr& operator=(shared_ptr&& src) noexcept;

public:
    void reset(T* ptr = nullptr);
    T* get();
    const T* get() const;
    int use_count() const;
    operator bool() const;
    T& operator*();
    const T& operator*() const;
    template<typename U = T, typename = std::enable_if_t<!std::is_fundamental_v<U>>>
    T* operator->();
    template<typename U = T, typename = std::enable_if_t<!std::is_fundamental_v<U>>>
    const T* operator->() const;
    
    friend class weak_ptr<T>;

private:
    shared_ptr(ControlBlock<T>*);

private:
    ControlBlock<T>* _controlBlock;    
};

#include "shared.tpp"

#endif //SHARED_PTR_HPP





