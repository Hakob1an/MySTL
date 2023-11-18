#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP

#include "control_block.hpp"

template<typename T>
class shared_ptr;

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

#include "weak.tpp"

#endif //WEAK_PTR_HPP