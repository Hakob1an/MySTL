#ifndef VECTOR_TPP
#define VECTOR_TPP

template<typename T>
constexpr vector<T>::vector()
    : _size{0}
    , _capacity{0}
    , _vec{nullptr}
{}
template<typename T>
vector<T>::vector(size_type size)
    : _size{0}
    , _capacity{size}
    , _vec{new T[size]{}}
{}
template<typename T>
vector<T>::vector(size_type size, value_type init_value)
    : _size{size}
    , _capacity{size}
    , _vec{new T[size]{}}
{
    for (size_type i = 0; i < size; ++i) {
        _vec[i] = init_value;
    }
}
template<typename T>
constexpr vector<T>::vector(std::initializer_list<T> list)
    : _size{list.size()}
    , _capacity{_size}
    , _vec{new T[_size]}
{
    auto it = list.begin();
    for (size_type i = 0; i < _size; ++i) {
    	_vec[i] = *it++;
    }
}
template<typename T>
constexpr vector<T>::vector(const vector<T>& src)
    : _size{src._size}
    , _capacity{src._capacity}
    , _vec{new T[_size]}
{
    for (size_type i{0}; i < _size; ++i) {
        _vec[i] = src._vec[i];
    }
}
template<typename T>
constexpr vector<T>::vector(vector<T>&& src) noexcept
    : _size{src._size}
    , _capacity{src._capacity}
    , _vec{src._vec}
{
    src._size = src._capacity = 0;
    src._vec = nullptr;
}
template<typename T>
vector<T>::~vector()
{
    if (_vec) {
        delete[] _vec;
    }
}
template<typename T>
constexpr vector<T>& vector<T>::operator=(const vector<T>& rhs)
{
    vector<T> tmp{rhs};
    swap(tmp);
    return *this;
}
template<typename T>
constexpr vector<T>& vector<T>::operator=(vector<T>&& rhs) noexcept
{
    moveFrom(rhs);
    return *this;
}
template<typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type ipos) const
{
    if (_vec == nullptr) {
    	throw std::out_of_range("The vector is empty!");
    }
    return _vec[ipos];
}
template<typename T>
typename vector<T>::reference vector<T>::operator[](size_type ipos)
{
	if (_vec == nullptr) {
    	throw std::out_of_range("The vector is empty!");
    }
    return _vec[ipos];
}
template<typename T>
vector<T>& vector<T>::operator+=(const vector& vec)
{
    if (_size + vec._size > _capacity) {
        resize(_size + vec._size);
    }
    for (size_type i{0}; i < vec._size; ++i) {
        _vec[_size + i] = vec._vec[i];
    }
    _size += vec._size;
    return *this;
}
template<typename T>
vector<T> operator+(const vector<T>& vec1, const vector<T>& vec2)
{
    vector<T> res{vec1};
    res += vec2;
    return res;
}
template<typename T>
constexpr void vector<T>::push_back(const value_type& value)
{
    if (_size == _capacity) {
        resize(_capacity * 2);
    }
    _vec[_size] = value;
    ++_size;
}
template<typename T>
constexpr void vector<T>::pop_back()
{
    if (empty()) {
        throw std::out_of_range("The vector is empty.");
    }
    --_size;
    if (_size == _capacity / 2) {
        resize(_capacity / 2);
    }
}
template<typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const
{
    if (pos >= _size) {
        throw std::out_of_range("Invalid index.");
    }
    return _vec[pos];
}
template<typename T>
typename vector<T>::reference vector<T>::at(size_type pos)
{
    return const_cast<reference>(std::as_const(*this)[pos]);
}
template<typename T>
constexpr void vector<T>::reserve(size_type capacity)
{
    resize(capacity);
}
template<typename T>
constexpr void vector<T>::insert(value_type value, size_type pos)
{
    if (pos >= _size) {
        throw std::out_of_range("Invalid index.");
    }
    if (empty() || pos == _size - 1) {
        push_back(value);
        return;
    }
    ++_size;
    if (_size == _capacity) {
        resize(_capacity * 2);
    }
    for (size_type i{_size - 1}; i > pos; --i) {
        _vec[i] = _vec[i - 1];
    }
    _vec[pos] = value;
}
template<typename T>
constexpr typename vector<T>::iterator vector<T>::insert(iterator pos, const T& value)
{ 
    if (pos == end()) {
        throw std::out_of_range("Invalid index.");
    }
    if (empty() || pos == --end()) {
        push_back(value);
        return pos;
    }
    ++_size;
    if (_size == _capacity) {
        resize(_capacity * 2);
    }
    auto it = --end();
    while (it != pos) {
        *it = *(it - 1);
        --it;
    }
    *pos = value;
    return pos;
}
template<typename T>
void vector<T>::insert(T arr[], size_type size, size_type pos)
{
    if (pos >= _size) {
    	throw std::out_of_range("Invalid index.");
    }
    if (!arr) {
    	throw std::runtime_error("The static array is empty!");
    }
    size_type newSize = _size + size;
    if (newSize > _capacity) {
        resize(_size + size + 1);
    }
    
    for (size_type i = _size - 1; i >= pos; --i) {
        _vec[i + size] = _vec[i];
    }
    for (size_type i = 0; i < size; ++i) {
        _vec[i + pos] = arr[i];
    }
    _size = newSize;
}
template<typename T>
constexpr void vector<T>::erase(size_type pos)
{
    if (empty()) {
        throw std::runtime_error("Vector is empty.");
    }
    if (pos >= _size) {
        throw std::out_of_range("Invalid index.");
    }
    --_size;
    for (std::size_t i{pos}; i < _size; ++i) {
        _vec[i] = _vec[i + 1];
    }
    if (_size <= _capacity / 2) {
        resize(_capacity / 2);
    }
}
template<typename T>
constexpr typename vector<T>::iterator vector<T>::erase(iterator pos)
{
    if (empty()) {
        throw std::runtime_error("Vector is empty.");
    }
    if (pos == end()) {
        throw std::out_of_range("Invalid index.");
    }
    --_size;
    auto it = pos;
    while (it != end()) {
        *it = *(it + 1);
        ++it;
    }
    if (_size <= _capacity / 2) {
        resize(_capacity / 2);
    }
    return it;
}
template<typename T>
constexpr typename vector<T>::iterator vector<T>::erase(iterator first, iterator last)
{
    size_type numOfElems = static_cast<size_type>(std::distance(first, last));
    if (first == end() || last == end() || first == last) {
        throw std::out_of_range("Invalid iterator range.");
    }
    auto it = first;
    while (it + numOfElems != end()) {
        *it = *(it + numOfElems);
        ++it;
    }
    _size -= numOfElems;
    return first;
}
template<typename T>
constexpr void vector<T>::clear() noexcept
{
    _size = _capacity = 0;
    delete[] _vec;
    _vec = nullptr;
}
template<typename T>
constexpr typename vector<T>::size_type vector<T>::size() const
{
    return _size;
}
template<typename T>
constexpr typename vector<T>::size_type vector<T>::capacity() const
{
    return _capacity;
}
template<typename T>
constexpr bool vector<T>::empty() const
{
    return _size == 0;
}
template<typename T>
typename vector<T>::iterator vector<T>::begin()
{
    return iterator{_vec};
}
template<typename T>
typename vector<T>::iterator vector<T>::end()
{
    return iterator{_vec + _size};
}
template<typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const
{
    return const_iterator{_vec};
}
template<typename T>
typename vector<T>::const_iterator vector<T>::cend() const
{
    return const_iterator{_vec + _size};
}
template<typename T>
typename vector<T>::reverse_iterator vector<T>::rbegin()
{
    return reverse_iterator{_vec};
}
template<typename T>
typename vector<T>::reverse_iterator vector<T>::rend()
{
    return reverse_iterator{_vec + _size};
}
template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::crbegin() const
{
    return const_reverse_iterator{_vec};
}
template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::crend() const
{
    return const_reverse_iterator{_vec + _size};
}
template<typename T>
void vector<T>::resize(size_type capacity)
{
    if (capacity == 0) {
        capacity = 1;
    }
    T* tmp = nullptr;
    try {
    	tmp = new T[capacity];
    	for (size_type i{0}; i < _size; ++i) {
        	tmp[i] = _vec[i];
    	}
    }
    catch (const std::bad_alloc& e) {
    	std::cerr << "Memory allocation failed: " << e.what() << std::endl;
    	throw std::runtime_error("Memory allocation failed");
    }
    
    delete[] _vec;
    _vec = tmp;
    _capacity = capacity;
}
template<typename T>
void vector<T>::moveFrom(vector& vec)
{
    _size = std::exchange(vec._size, 0);
    _capacity = std::exchange(vec._capacity, 0);
    _vec = std::exchange(vec._vec, nullptr);
}
template<typename T>
void vector<T>::swap(vector& vec)
{
    std::swap(_size, vec._size);
    std::swap(_capacity, vec._capacity);
    std::swap(_vec, vec._vec);
}

#endif //VECTOR_TPP
