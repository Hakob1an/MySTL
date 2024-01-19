#ifndef QUEUE_WITH_LIST_TPP
#define QUEUE_WITH_LIST_TPP

#include <stdexcept>

template<typename T>
queue<T>::queue()
	: _head{nullptr}
	, _tail{nullptr}
	, _size{0}
{}
template<typename T>
queue<T>::queue(T value)
    : _head{new Node<T>(value)}
    , _tail{_head}
{}
template<typename T>
queue<T>::queue(const queue<T>& src)
	: queue()
{
    Node<T>* current{src._head};
    while (current) {
        push(current->data);
        current = current->next;
    }
}
template<typename T>
queue<T>& queue<T>::operator=(const queue<T>& rhs)
{
    if (this == & rhs) {
    	return *this;
    }
    while (_head) {
        Node<T>* current = _head;
        _head = _head->next;
        delete current;
    }
    Node<T>* current = rhs.front;
    while (current) {
        enqueue(current->data);
        current = current->next;
    }
    return *this;
}
template<typename T>
queue<T>::~queue()
{
    while (_head) {
        Node<T>* current = _head;
        _head = _head->next;
        delete current;
    }
}
template<typename T>
T queue<T>::front() const
{
    if (!_head) {
        throw std::runtime_error("front(): Queue is empty.");
    }
    return _head->data;
}
template<typename T>
T queue<T>::back() const
{
    if (!_head) {
        throw std::runtime_error("back(): Queue is empty.");
    }
    return _tail->data;
}
template<typename T>
bool queue<T>::empty() const
{
    return _head == nullptr;
}
template<typename T>
std::size_t queue<T>::size() const
{
    return _size;
}
template<typename T>
void queue<T>::push(T value)
{
    Node<T>* newNode = new Node<T>(value);
    if (_head == nullptr) {
        _head = _tail = newNode;
    } else {
        _tail->next = newNode;
        _tail = _tail->next;
    }
    ++_size;
}
template<typename T>
void queue<T>::pop()
{
    if (_head == nullptr) {
        throw std::runtime_error("dequeue(): Queue is empty.");
    }
    Node<T>* nodeToDelete = _head;
    _head = _head->next;
    delete nodeToDelete;
    --_size;
}
template<typename T>
bool queue<T>::operator==(const queue<T>& rhs) const
{
    if (_size != rhs._size) {
        return false;
    }
    Node<T>* current1 = _head;
    Node<T>* current2 = rhs._head;
    while (current1 && current2) {
        if (current1->data != current2->data) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return true;
}
template<typename T>
bool queue<T>::operator!=(const queue<T>& rhs) const
{
    return !(*this == rhs);
}
template<typename T>
bool queue<T>::operator>(const queue<T>& rhs) const
{
    Node<T>* current1 = _head;
    Node<T>* current2 = rhs._head;
    while (current1 && current2) {
        if (current1->data <= current2->data) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return (current1 != nullptr && current2 == nullptr);
}
template<typename T>
bool queue<T>::operator>=(const queue<T>& rhs) const
{
    return (*this == rhs) || (*this > rhs);
}
template<typename T>
bool queue<T>::operator<(const queue<T>& rhs) const
{
    return !(*this >= rhs);
}
template<typename T>
bool queue<T>::operator<=(const queue<T>& rhs) const
{
    return !(*this > rhs);
}

#endif //QUEUE_WITH_LIST_TPP
