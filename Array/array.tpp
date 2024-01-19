template<typename T, std::size_t N>
array<T, N>::array()
    : m_size{}
{}

template<typename T, std::size_t N>
void array<T, N>::set(std::size_t pos, T value) 
{
    if (pos >= N) {
        throw std::out_of_range("The array is full.");
    }
    m_elems[pos] = value;
    if (pos >= m_size) {
        m_size = pos + 1;
    }
}

template<typename T, std::size_t N>
T array<T, N>::front() const
{
    if (m_size == 0) {
        throw std::out_of_range("There are no elements in array.");
    }
    return m_elems[0];
}

template<typename T, std::size_t N>
T array<T, N>::back() const
{
    if (m_size == 0) {
        throw std::out_of_range("There are no elements in array.");
    }
    return m_elems[m_size - 1];
}

template<typename T, std::size_t N>
void array<T, N>::traverse(void(*fp)(T)) const
{
    for (std::size_t i{0}; i < m_size; ++i) {
        fp(m_elems[i]);
    }
    std::cout << std::endl;
}

template<typename T, std::size_t N>
std::size_t array<T, N>::size() const
{
    return m_size;
}

template<typename T, std::size_t N>
bool array<T, N>::empty() const
{
    return m_size == 0;
}

template<typename T, std::size_t N>
T& array<T, N>::operator[](std::size_t pos)
{
    if (pos >= N) {
        throw std::out_of_range("Invalid index.");
    }
    if (pos >= m_size) {
        m_size = pos + 1;
    }
    return m_elems[pos];
}

template<typename T>
void print(T elem) 
{
    std::cout << elem << " ";
}


//specialization for bool

template<std::size_t N>
array<bool, N>::array()
    : m_size{0}
{}

template<std::size_t N>
void array<bool, N>::set(std::size_t pos, bool value) 
{
    if (pos >= N) {
        throw std::out_of_range("The array is full.");
    }
    m_elems[pos] = value;
    if (pos >= m_size) {
        m_size = pos + 1;
    }
}

template<std::size_t N>
bool array<bool, N>::front() const
{
    if (empty()) {
        throw std::out_of_range("The array is empty.");
    }
    return m_elems.test(0);
}

template<std::size_t N>
bool array<bool, N>::back() const
{
    if (empty()) {
        throw std::out_of_range("The array is empty.");
    }
    return m_elems.test(m_size - 1);
}

template<std::size_t N>
void array<bool, N>::traverse(void(*fp)(bool)) const
{
    for (std::size_t i{0}; i < m_size; ++i) {
        fp(m_elems[i]);
    }
    std::cout << std::endl;
}

template<std::size_t N>
std::size_t array<bool, N>::size() const
{
    return m_size;
}

template<std::size_t N>
bool array<bool, N>::empty() const
{
    return m_size == 0;
}

template<std::size_t N>
bool array<bool, N>::operator[](std::size_t pos)
{
    if (pos >= N) {
        throw std::out_of_range("The array is full.");
    }
    ++m_size;
    return m_elems.test(pos);
}

template<>
void print(bool elem) 
{
    std::cout << std::boolalpha << elem << " ";
}
