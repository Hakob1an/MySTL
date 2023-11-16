#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <type_traits>
#include "control_block.hpp"

template<typename T>
class weak_ptr;

template<typename T>
class shared_ptr
{
public:
    shared_ptr(T value);
    shared_ptr(T* ptr = nullptr);
    shared_ptr(const shared_ptr&);
    shared_ptr(ControlBlock<T>*);
    shared_ptr& operator=(const shared_ptr&);
    shared_ptr(shared_ptr&& src) noexcept;
    shared_ptr& operator=(shared_ptr&& src) noexcept;
    ~shared_ptr();
    void free();

public:
    void reset(T* ptr = nullptr);
    T* get() const;
    T& operator*();
    template<typename U = T, typename = std::enable_if_t<!std::is_fundamental_v<U>>>
    T* operator->();
    int use_count() const;
    operator bool();
    
    friend class weak_ptr<T>;

private:
    ControlBlock<T>* _controlBlock;    
};

#include "shared.hpp"

#endif //SHARED_PTR_H

#ifndef WEAK_PTR_H
#define WEAK_PTR_H

#include "shared.h"
#include "control_block.hpp"

template<typename T>
class weak_ptr
{
public:
    weak_ptr();
    weak_ptr(const shared_ptr<T>&);
    ~weak_ptr();
    shared_ptr<T> lock()const;

    friend class shared_ptr<T>;

private:
    ControlBlock<T>* _controlBlock;
};

#include "weak.hpp"

#endif //WEAK_PTR_HPP





