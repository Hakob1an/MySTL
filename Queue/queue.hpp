#ifndef QUEUE_WITH_LIST_HPP
#define QUEUE_QITH_LIST_HPP

#include <cstddef>

template<typename T>
struct Node
{
    Node(T value) 
        : data{value}
        , next{nullptr}
    {}
    
    T data;
    Node* next;
};

template<typename T>
class queue
{
public:
    queue();
    queue(const queue&);
    queue(T);
    queue& operator=(const queue&);
    ~queue();

public:
    T front() const;
    T back() const;
    bool empty() const;
    std::size_t size() const;
    void push(T);
    void pop();
    bool operator==(const queue&) const;
    bool operator!=(const queue&) const;
    bool operator>(const queue&) const;
    bool operator>=(const queue&) const;
    bool operator<(const queue&) const;
    bool operator<=(const queue&) const;

private:
    Node<T>* _head;
    Node<T>* _tail;
    std::size_t _size;
};

#include "q.tpp"

#endif //QUEUE_WITH_LSIT_HPP
