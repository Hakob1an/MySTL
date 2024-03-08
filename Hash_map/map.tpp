#ifndef HASH_MAP_TPP
#define HASH_MAP_TPP


template<typename Key, typename Value>
hash_map<Key, Value>::hash_map()
    : _size{0}
{
    _bucket.resize(_bucket_size, nullptr);
}

template<typename Key, typename Value>
hash_map<Key, Value>::hash_map(const hash_map& other)
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

template<typename Key, typename Value>
hash_map<Key, Value>::hash_map(hash_map&& other) noexcept
    : _size{other._size}
{
    for (size_type i = 0; i < _bucket_size; ++i) {
        _bucket[i] = other._bucket[i];
        other._bucket[i] = nullptr;
    }
    other._size = 0;
    other.clear();
}

template<typename Key, typename Value>
hash_map<Key, Value>::~hash_map()
{
    clear();
}

template<typename Key, typename Value>
hash_map<Key, Value>& hash_map<Key, Value>::operator=(const hash_map& rhs)
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

template<typename Key, typename Value>
hash_map<Key, Value>& hash_map<Key, Value>::operator=(hash_map&& rhs) noexcept
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

template<typename Key, typename Value>
Value& hash_map<Key, Value>::operator[](const key_type& key)
{
    size_type pos = hash(key);
    
    if (_bucket[pos] == nullptr) {
        insert(key, Value());
    } else {
        node_type* current = _bucket[pos];
        while (current != nullptr) {
            if (current->_key == key) {
                return current->_value;
            }
            current = current->_next;
        }

        if (current == nullptr) {
            insert(key, Value());
        }
    }

    node_type* current = _bucket[pos];
    while (current != nullptr && current->_key != key) {
        current = current->_next;
    }

    return current->_value;
}

template<typename Key, typename Value>
const Value& hash_map<Key, Value>::operator[](const key_type& key) const 
{
    size_type pos = hash(key);
    if (_bucket[pos] == nullptr) {
        throw std::invalid_argument("The key is not present!");
    }
    node_type* current = _bucket[pos];
    while (current != nullptr && key != current->_key) {
        current = current->_next;
    }
    if (current == nullptr) {
        throw std::invalid_argument("The key is not present!");
    }

    return current->_value;
}

template<typename Key, typename Value>
bool hash_map<Key, Value>::empty() const
{
    return _size == 0;
}

template<typename Key, typename Value>
std::size_t hash_map<Key, Value>::size() const
{
    return _size;
}

template<typename Key, typename Value>
std::size_t hash_map<Key, Value>::max_size() const
{
    return _bucket_size * _bucket_size;
}

template<typename Key, typename Value>
void hash_map<Key, Value>::clear() noexcept
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

template<typename Key, typename Value>
std::pair<node<Key, Value>*, bool> hash_map<Key, Value>::insert(const key_type& key, const value_type& value)
{
    size_type position = hash(key);

    node_type* newNode = new node_type(key, value);
    
    if (_bucket[position] == nullptr) {
        _bucket[position] = newNode;
    } else {
        node_type* current = _bucket[position];
        while (current != nullptr) {
            if (current->_key == key) {
                current->_value = value;
                break;
            }
            current = current->_next;
        }
        if (current == nullptr) {
            //inserting at the front of linked list for maximizing the speed
            newNode->_next = _bucket[position];
            _bucket[position] = newNode;
        }
    }

    ++_size;
    checkRehash();

    return std::pair<node_type*, bool>(newNode, true);
}

template<typename Key, typename Value>
node<Key, Value>* hash_map<Key, Value>::erase(node_type* pos)
{
    if (pos == nullptr) {
        return pos;
    }
    
    size_type bucket_pos = hash(pos->_key);
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

template<typename Key, typename Value>
double hash_map<Key, Value>::load_factor() const
{
    return static_cast<double>(_size) / _bucket_size;
}

template<typename Key, typename Value>
node<Key, Value>* hash_map<Key, Value>::find(const key_type& key) 
{
    size_type pos = hash(key);
    if (_bucket[pos] == nullptr) {
        return nullptr;
    }
    node_type* current = _bucket[pos];
    while (current != nullptr) {
        if (current->_key == key) {
            return current;
        }
        current = current->_next;
    }

    return nullptr;
} 

template<typename Key, typename Value>
std::size_t hash_map<Key, Value>::count(const key_type& key)
{
    size_type pos = hash(key);

    if (_bucket[pos] == nullptr) {
        return 0;
    }

    node_type* current = _bucket[pos];
    while (current != nullptr) {
        if (current->_key == key) {
            return 1;
        }
        current = current->_next;
    }

    return 0;
}

template<typename Key, typename Value>
Value& hash_map<Key, Value>::at(const key_type& key)
{
    return const_cast<hash_map*>(std::as_const(*this)[key]);
}

template<typename Key, typename Value>
const Value& hash_map<Key, Value>::at(const key_type& key) const 
{
    size_type pos = hash(key);
    if (_bucket[pos] == nullptr) {
        throw std::out_of_range("Key doesn't exist!");
    }

    node_type* current = _bucket[pos];
    while (current != nullptr && key != current->_key) {
        current = current->_next;
    }

    if (current == nullptr) {
        throw std::out_of_range("Key doesn't exist!");
    } 

    return current->_value;
}

template<typename Key, typename Value>
template<typename U>
std::size_t hash_map<Key, Value>::hash(const U& key) 
{
    size_type k = 2166136261u;
    size_type p = 16777619u;

    return ((key * k) ^ p) % _bucket_size;
}

template<typename Key, typename Value>
std::size_t hash_map<Key, Value>::hash(const std::string& key)
{
    size_type k = 2166136261u;
    size_type p = 16777619u;

    for (size_type i = 0; i < key.size(); ++i) {
        k ^= key[i];
        k *= p;
    }
    return k % _bucket_size;
}

template<typename Key, typename Value>
void hash_map<Key, Value>::rehash(size_type count)
{
    std::vector<node_type*> new_set(count);

    size_type oldSize = _bucket_size;
    _bucket_size = count;
    for (size_type i = 0; i < oldSize; ++i) {
        node_type* current = _bucket[i];
        while (current != nullptr) {
            size_type pos = hash(current->_key);
            add(new_set[pos], current->_key, current->_value);
            current = current->_next;
        }
    }
    _bucket = std::move(new_set);
}

template<typename Key, typename Value>
void hash_map<Key, Value>::checkRehash()
{
    if (load_factor() >= _max_load_factor) {
        rehash(_bucket_size * 1.5);
    }
}

template<typename Key, typename Value>
void hash_map<Key, Value>::print() const
{
    for (size_type i = 0; i < _bucket_size; ++i) {
        std::cout << "bucket " << i << ": ";
        node_type* current = _bucket[i];
        while (current != nullptr) {
            std::cout << current->_key << ":" << current->_value << ", "; 
            current = current->_next;
        }
        std::cout << std::endl;
    }
}

template<typename Key, typename Value>
void hash_map<Key, Value>::add(node_type*& n, const key_type& key, const value_type& val)
{
    node_type* newNode = new node_type(key, val);
    if (n == nullptr) {
        n = newNode;
    } else {
        newNode->_next = n;
        n = newNode;
    }
}

#endif //HASH_MAP_TPP