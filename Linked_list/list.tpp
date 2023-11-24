#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "list.hpp"
#include <stdexcept>
#include <iostream>

template<typename T>
list<T>::list() 
    : _size{0}
{}
template<typename T>
void list<T>::push_back(T value)
{
    auto newNode = std::make_shared<list<T>::node>(value);
    if (_head == nullptr) {
        _head = _tail = newNode;
    } 
    else {
        _tail->_next = newNode;
        newNode->_prev = _tail;
        _tail = newNode;
    }
    ++_size;
}
template<typename T>
void list<T>::push_front(T value)
{
    auto newNode = std::make_shared<list<T>::node>(value);
    if (_head == nullptr) {
        _head = _tail = newNode;
    } 
    else {
        _head->_prev = newNode;
        newNode->_next = _head;
        _head = newNode;
    }
    ++_size;
}
template<typename T>
void list<T>::insert(T value, std::size_t ind) 
{
    if (ind == 0) {
        push_front(value);
    } 
    else if (ind == _size) {
        push_back(value);    
    }
    else if (ind < _size) {
        auto newNode = std::make_shared<list<T>::node>(value);
        bool isLowerMid = (ind < _size / 2);

        auto current = isLowerMid ? _head : _tail;
        std::size_t position = isLowerMid ? ind - 1 : _size - ind;
        
        for (std::size_t i{0}; i < position; ++i) {
            current = isLowerMid ? current->_next : current->_prev.lock();
        }

        newNode->_next = current->_next;
        newNode->_prev = current;
        current->_next->_prev = newNode;
        current->_next = newNode;
        
        ++_size;
    }
    else {
    	throw std::out_of_range("Invalid index.");
    }
}
template<typename T>
void list<T>::pop_back()
{
    if (_size == 0) {
        throw std::runtime_error("The list is empty.");
    }
    if (_size == 1) {
        _head = _tail = nullptr;
    }
    else {
    	_tail = _tail->_prev.lock();
    	_tail->_next = nullptr;
    }
    --_size;
}
template<typename T>
void list<T>::pop_front()
{
    if (_size == 0) {
        throw std::runtime_error("The list is empty.");
    }
    if (_size == 1) {
        _head = _tail = nullptr;
    }
    else {
    	_head = _head->_next;
    	_head->_prev.lock() = nullptr;
    }
    --_size;
}
template<typename T>
void list<T>::remove(std::size_t ind) 
{
    if (ind == 0) {
        pop_front();
    }    
    else if (ind == _size - 1) {
        pop_back();
    }
    else if (ind < _size) {
        bool isLowerMid = (ind < _size / 2);

        auto current = isLowerMid ? _head : _tail;
        std::size_t position = isLowerMid ? ind : _size - ind - 1;
        
        for (std::size_t i{0}; i < position; ++i) {
            current = isLowerMid ? current->_next : current->_prev.lock();
        }

        auto prevNode = current->_prev.lock();
        auto nextNode = current->_next;

        if (prevNode) {
            prevNode->_next = nextNode;
        }

        if (nextNode) {
            nextNode->_prev = prevNode;
        }
        
        --_size;
    }
    else {
    	throw std::out_of_range("Invalid index.");
	}
}
template<typename T>
std::size_t list<T>::size() const
{
    return _size;
}
template<typename T>
void list<T>::print() const
{
    auto current = _head;
    while (current != nullptr) {
        std::cout << current->_data << " ";
        current = current->_next;
    }
    std::cout << std::endl;
}
template<typename T>
typename list<T>::iterator list<T>::begin() const
{
    return iterator{_head};
}
template<typename T>
typename list<T>::iterator list<T>::end() const
{
    return iterator{nullptr};
}
template<typename T>
list<T>::node::node(T value)
	: _data{value}
{}
template<typename T>
list<T>::node::node(const list<T>::node& src)
    : _data{src._data}
{}
template<typename T>
list<T>::node::node(list<T>::node&& src) noexcept
    : _next{std::move(src._next)}
    , _prev{std::move(src._prev)}
    , _data{std::move(src._data)}
{}
template<typename T>
typename list<T>::node& list<T>::node::operator=(const list<T>::node& rhs)
{
    if (this != &rhs) {
        _data = rhs._data;
    }
    return *this;
}
template<typename T>
typename list<T>::node& list<T>::node::operator=(list<T>::node&& rhs) noexcept
{
    if (this != &rhs) {
        _next = std::move(rhs._next);
        _prev = std::move(rhs._prev);
        _data = std::move(rhs._data);
    }
    return *this;
}
template<typename T>
list<T>::iterator::iterator() 
    : _current{nullptr}
{}
template<typename T>
list<T>::iterator::iterator(std::shared_ptr<typename list<T>::node> ptr)
    : _current{ptr}
{}
template<typename T>
typename list<T>::iterator& list<T>::iterator::operator++()
{
    if (_current) {
        _current = _current->_next;
    }
    return *this;
}
template<typename T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
    typename list<T>::iterator tmp{*this};
    ++(*this);
    return tmp;
}
template<typename T>
T& list<T>::iterator::operator*() const
{
    return _current->_data;
}
template<typename T>
bool list<T>::iterator::operator==(const list<T>::iterator& other) const
{
    return _current == other._current;
}
template<typename T>
bool list<T>::iterator::operator!=(const list<T>::iterator& other) const
{
    return _current != other._current;
}

#endif //LINKED_LIST_TPP
