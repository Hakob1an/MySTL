#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>
#include <iostream>
#include <stdexcept>

template<typename Key, typename Value>
struct node
{
    using key_type = Key;
    using value_type = Value;

    node(key_type key, value_type value) 
    : _key{key}, _value{value}, _next{nullptr}
    {}

    key_type _key;
    value_type _value;
    node* _next;
};

template<typename Key, typename Value>
class hash_map
{
public:
    using key_type = Key;
    using value_type = Value;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using node_type = node<key_type, value_type>;

public:
    hash_map();
    hash_map(const hash_map& other);
    hash_map(hash_map&& other) noexcept;
    ~hash_map();

    hash_map& operator=(const hash_map& rhs);
    hash_map& operator=(hash_map&& rhs) noexcept;
    reference operator[](const key_type& key);
    const_reference operator[](const key_type& key) const;

public:
    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    void clear() noexcept;
    std::pair<node_type*, bool> insert(const key_type& key, const value_type& value);
    node_type* erase(node_type* pos);
    double load_factor() const;
    node_type* find(const key_type& key);
    size_type count(const key_type& key);
    reference at(const Key& key);
    const_reference at(const Key& key) const;
    void print() const;

private:
    template<typename U = Key>
    size_type hash(const U& key);
    size_type hash(const std::string& key);
    void rehash(size_type count);
    void checkRehash();
    void add(node_type*& n, const key_type& key, const value_type& val);

private:
    size_type _size;
    inline constexpr static double _max_load_factor = 0.75;
    size_type _bucket_size = 10;
    std::vector<node_type*> _bucket;
};

#include "map.tpp"

#endif //HASH_MAP_HPP