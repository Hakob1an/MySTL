#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP

#include "shared.h"

template<typename T>
weak_ptr<T>::weak_ptr()
    : _controlBlock{nullptr}
{}
template<typename T>
weak_ptr<T>::weak_ptr(const shared_ptr<T>& sharedPtr) 
    : _controlBlock{sharedPtr._controlBlock}
{
    _controlBlock->incrementWeakRefCount();
}
template<typename T>
weak_ptr<T>::~weak_ptr()
{
    if (_controlBlock) {
        _controlBlock->decrementWeakRefCount();
        if (_controlBlock->getWeakCount() == 0 && _controlBlock->getSharedCount() == 0) {
            delete _controlBlock;
        }
    }
}
template<typename T>
shared_ptr<T> weak_ptr<T>::lock() const
{
    if (_controlBlock && _controlBlock->getSharedCount() > 0) {
        return shared_ptr<T>(_controlBlock);
    } else {
        return shared_ptr<T>();
    }
}

#endif //WEAK_PTR_HPP