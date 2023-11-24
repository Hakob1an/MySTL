#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

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

public:	
	struct node;
    class iterator;

public:
    iterator begin() const;
    iterator end() const;

private:
    std::shared_ptr<node> _head;
    std::shared_ptr<node> _tail;
    std::size_t _size;
};

template<typename T>
struct list<T>::node
{
    node(T);
    node(const node&);
    node(node&&) noexcept;

    node& operator=(const node&);
    node& operator=(node&&) noexcept;

    std::shared_ptr<node> _next;
    std::weak_ptr<node> _prev;
    T _data;
};

template<typename T>
class list<T>::iterator
{
public:
    iterator();
    iterator(std::shared_ptr<typename list<T>::node>);

    iterator& operator++();
    iterator operator++(int);
    T& operator*() const;
    bool operator==(const iterator&) const;
    bool operator!=(const iterator&) const;

private:
    std::shared_ptr<typename list<T>::node> _current;
};

#include "list.tpp"

#endif //LINKED_LIST_HPP
