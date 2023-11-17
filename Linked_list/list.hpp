#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "list.h"
#include <stdexcept>
#include <iostream>

template<typename T>
list<T>::list()
    : _head{nullptr}
    , _tail{nullptr}
    , _size{0}
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
        auto current = _head;
        for (std::size_t i{0}; i < ind - 1; ++i) {
            current = current->_next;
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
        --_size;
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
        auto current = _head;
        for (std::size_t i{0}; i < ind; ++i) {
            current = current->_next;
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
list<T>::node::node(T value)
	: _data{value}
{}

#endif //LINKED_LIST_HPP
