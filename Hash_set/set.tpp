#ifndef HASH_SET_TPP
#define HASH_SET_TPP


template<typename Key>
hash_set<Key>::hash_set()
    : _size{0}
{
    _bucket.resize(_bucket_size);
    for (size_type i = 0; i < _bucket_size; ++i) {
        _bucket[i] = nullptr;
    }
}

template<typename Key>
hash_set<Key>::hash_set(const hash_set& other)
    : _size{other._size}
{
    _bucket.resize(_bucket_size, nullptr);
    for (size_type i = 0; i < _bucket_size; ++i) {
        node_type* current = other._bucket[i];
        while (current != nullptr) {
            insert(current->_value);
            current = current->_next;
        }
    }
}

template<typename Key>
hash_set<Key>::hash_set(hash_set&& other) noexcept
    : _size{other._size}
{
    for (size_type i = 0; i < _bucket_size; ++i) {
        _bucket[i] = other._bucket[i];
        other._bucket[i] = nullptr;
    }
    other._size = 0;
    other.clear();
}

template<typename Key>
hash_set<Key>::hash_set(std::initializer_list<value_type> ilist, size_type bucket_count) 
    : _size{0}
{
    _bucket.resize(bucket_count, nullptr);
    for (const auto& elem : ilist) {
        insert(elem);
    }
}

template<typename Key>
hash_set<Key>::~hash_set()
{
    clear();
}

template<typename Key>
hash_set<Key>& hash_set<Key>::operator=(const hash_set& rhs)
{
    if (this != &rhs) {
        clear();
        _size = rhs._size;
        for (size_type i = 0; i < _bucket_size; ++i) {
            node_type* current = rhs._bucket[i];
            while (current != nullptr) {
                insert(current->_value);
                current = current->_next;
            }
        }
    }
    return *this;
}

template<typename Key>
hash_set<Key>& hash_set<Key>::operator=(hash_set&& rhs) noexcept
{
    if (this != &rhs) {
        clear();
        for (size_type i = 0; i < _bucket_size; ++i) {
            _bucket[i] = rhs._bucket[i];
            rhs._bucket[i] = nullptr;
        }
        rhs._size = 0;
    }
    return *this;
}

template<typename Key>
hash_set<Key>& hash_set<Key>::operator=(std::initializer_list<value_type> ilist)
{
    clear();
    for (const auto& elem : ilist) {
        insert(elem);
    }
    return *this;
}

template<typename Key>
bool hash_set<Key>::empty() const
{
    return _size == 0;
}

template<typename Key>
std::size_t hash_set<Key>::size() const
{
    return _size;
}

template<typename Key>
std::size_t hash_set<Key>::max_size() const
{
    return _bucket_size * _bucket_size;
}

template<typename Key>
void hash_set<Key>::clear() noexcept
{
    for (size_type i = 0; i < _bucket_size; ++i) {
        node_type* current = _bucket[i];
        node_type* next = nullptr;
        while (current != nullptr) {
            next = current->_next;
            delete current;
            current = next;
        }
        _bucket[i] = nullptr;
    }
    _size = 0;
}

template<typename Key>
std::pair<node<Key>*, bool> hash_set<Key>::insert(const value_type& value)
{
    size_type position = hash(value);

    node_type* newNode = new node_type(value);
    
    if (_bucket[position] == nullptr) {
        _bucket[position] = newNode;
    } else {
        //inserting at the front of linked list for maximizing the speed
        newNode->_next = _bucket[position];
        _bucket[position] = newNode;
    }

    ++_size;
    checkRehash();

    return std::pair<node_type*, bool>(newNode, true);
}

template<typename Key>
node<Key>* hash_set<Key>::erase(node_type* pos)
{
    if (pos == nullptr) {
        return pos;
    }
    
    size_type bucket_pos = hash(pos->_value);
    node_type* current = _bucket[bucket_pos];
    
    if (pos == _bucket[bucket_pos]) {
        _bucket[bucket_pos] = _bucket[bucket_pos]->_next;
    } else {
        while (current != nullptr && current->_next != nullptr && current->_next != pos) {
            current = current->_next;
        }
        current->_next = current->_next->_next;
    }
    delete pos;
    
    --_size;

    return current->_next;
}

template<typename Key>
double hash_set<Key>::load_factor() const
{
    return static_cast<double>(_size) / _bucket_size;
}

template<typename Key>
node<Key>* hash_set<Key>::find(const key_type& key) 
{
    size_type pos = hash(key);
    if (_bucket[pos] == nullptr) {
        return nullptr;
    }
    node_type* current = _bucket[pos];
    while (current != nullptr) {
        if (current->_value == key) {
            return current;
        }
        current = current->_next;
    }

    return nullptr;
} 

template<typename Key>
template<typename U>
std::size_t hash_set<Key>::hash(const U& key) 
{
    size_type k = 2166136261u;
    size_type p = 16777619u;
    return ((key * k) % p) % _bucket_size;
}

template<typename Key>
std::size_t hash_set<Key>::hash(const std::string& key)
{
    size_type k = 2166136261zu;
    size_type p = 16777619zu;

    for (size_type i = 0; i < key.size(); ++i) {
        k ^= key[i];
        k *= p;
    }
    return k % _bucket_size;
}

template<typename Key>
void hash_set<Key>::rehash(size_type count)
{
    std::vector<node_type*> new_set(count);

    size_type oldSize = _bucket_size;
    _bucket_size = count;
    for (size_type i = 0; i < oldSize; ++i) {
        node_type* current = _bucket[i];
        while (current != nullptr) {
            size_type pos = hash(current->_value);
            add(new_set[pos], current->_value);
            current = current->_next;
        }
    }
    _bucket = std::move(new_set);
}

template<typename Key>
void hash_set<Key>::checkRehash()
{
    if (load_factor() >= _max_load_factor) {
        rehash(_bucket_size * 1.5);
    }
}

template<typename Key>
void hash_set<Key>::print() const
{
    for (size_type i = 0; i < _bucket_size; ++i) {
        std::cout << "bucket " << i << ": ";
        node_type* current = _bucket[i];
        while (current != nullptr) {
            std::cout << current->_value << " "; 
            current = current->_next;
        }
        std::cout << std::endl;
    }
}

template<typename Key>
void hash_set<Key>::add(node_type*& n, const value_type& val)
{
    node_type* newNode = new node_type(val);
    if (n == nullptr) {
        n = newNode;
    } else {
        newNode->_next = n;
        n = newNode;
    }
}

#endif //HASH_SET_TPP
