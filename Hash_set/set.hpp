#ifndef HASH_SET_HPP
#define HASH_SET_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>
#include <iostream>

template<typename Key>
struct node
{
    using value_type = Key;

    node(value_type value) : _value{value}, _next{nullptr}
    {}

    value_type _value;
    node* _next;
};

template<typename Key>
class hash_set
{
public:
    using key_type = Key;
    using value_type = Key;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using node_type = node<value_type>;

public:
    hash_set();
    hash_set(const hash_set& other);
    hash_set(hash_set&& other) noexcept;
    hash_set(std::initializer_list<value_type> ilist, size_type bucket_count);
    ~hash_set();

    hash_set& operator=(const hash_set& rhs);
    hash_set& operator=(hash_set&& rhs) noexcept;
    hash_set& operator=(std::initializer_list<value_type> ilist);

public:
    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    void clear() noexcept;
    std::pair<node_type*, bool> insert(const value_type& value);
    node_type* erase(node_type* pos);
    double load_factor() const;
    node_type* find(const value_type& key);
    void print() const;

private:
    template<typename U = Key>
    size_type hash(const U& key);
    size_type hash(const std::string& key);
    void rehash(size_type count);
    void checkRehash();
    void add(node_type*& n, const value_type& val);

private:
    size_type _size;
    inline constexpr static double _max_load_factor = 0.75;
    size_type _bucket_size = 10;
    std::vector<node_type*> _bucket;
};

#include "set.tpp"

#endif //HASH_SET_HPP
