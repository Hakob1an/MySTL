#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>
#include <cstddef>


template<typename T>
class list
{
public:
    list();

public:
    void push_back(T);
    void push_front(T);
    void insert(T, std::size_t);
    void pop_back();
    void pop_front();
    void remove(std::size_t);
    std::size_t size() const;
    void print() const;

private:
    struct node 
    {
        node(T);

        std::shared_ptr<node> _next;
        std::weak_ptr<node> _prev;
        T _data;
    };
    std::shared_ptr<node> _head;
    std::shared_ptr<node> _tail;
    std::size_t _size;
};

#include "list.hpp"

#endif //LINKED_LIST_H
