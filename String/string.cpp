#include "string.hpp"

string::string() 
    : _isOnHeap{false}
    , _size{0}
{
    _onstack[0] = '\0';
}

string::string(const_pointer str) 
{
    size_type size = std::strlen(str);
    if (size < _maxSize) {
        _isOnHeap = false;
        std::strcpy(_onstack, str);
    }
    else {
        _isOnHeap = true;
        _isOnHeap = new char[size + 1];
        std::strcpy(_onheap, str);
    }
    _size = size;
}

string ::string(const std::string& str) : string(str.c_str())
{}

string::string(const string& src)
{
    copyFrom(src);
}

string::string(string&& src) noexcept 
{
    _isOnHeap = src._isOnHeap;
    if (_isOnHeap) {
        _onheap = src._onheap;
    }
    else { 
        std::strcpy(_onstack, src._onstack);
    }
    _size = src._size;
    src._isOnHeap = false;
    src._onstack[0] = '\0';
}

string::~string()
{
    clear();
}

string& string::operator=(const string& rhs)
{
    if (this != & rhs) {
        copyFrom(rhs);
    }
    
    return *this;
}

string& string::operator=(string&& rhs) noexcept 
{
    if (this != &rhs) {
        _isOnHeap = rhs._isOnHeap;
        if (_isOnHeap) {
            delete[] _onheap;
            _onheap = rhs._onheap;
        }
        else {
            std::strcpy(_onstack, rhs._onstack);
        }
        _size = rhs._size;
        rhs._isOnHeap = false;
        rhs._onstack[0] = '\0';
    }
    return *this;
}

string& string::operator=(const_pointer str)
{
    size_type len = std::strlen(str);
	
	if (_isOnHeap) {
		delete[] _onheap;
		_isOnHeap = false;
	}
	if (len > _maxSize) {
    	_isOnHeap = true;
    	_onheap = new char[_size + 1];
        std::strcpy(_onheap, str);
    }
    else {
   		std::strcpy(_onstack, str);
   	}
    _size = len;
	
    return *this;
}

string& string::operator+=(const string& s)
{
    this->append(s.c_str());
    
    return *this;
}

string& string::operator+=(const_pointer s)
{
    this->append(s);
    
    return *this;
}

string string::operator+(const string& s) const
{
    string tmp{*this};
    tmp += s;
    
    return tmp;
}

string operator+(const string& s1, string::const_pointer s2)
{
    string tmp{s1};
    tmp += s2;
    
    return tmp;
}

string operator+(string::const_pointer s1, const string& s2)
{
    string tmp{s1};
    tmp += s2;
    
    return tmp;
}

string::const_reference string::operator[](size_type pos) const
{
    return _isOnHeap ? _onheap[pos] : _onstack[pos];
}

string::reference string::operator[](size_type pos)
{
    return const_cast<reference>(std::as_const(*this)[pos]);
}

bool string::operator==(const string& other) const
{
    return (size() == other.size()) && (std::strcmp(c_str(), other.c_str()) == 0);
}

bool string::operator==(const_pointer str) const
{
	return (size() == std::strlen(str)) && (std::strcmp(c_str(), str) == 0);
}

bool operator==(string::const_pointer str, const string& other) 
{
	return (std::strlen(str) == other.size()) && (std::strcmp(str, other.c_str()) == 0);
}

bool string::operator!=(const string& other) const
{
	return !(*this == other);
}

bool string::operator!=(const_pointer str) const
{
	return !(*this == str);
}

bool operator!=(string::const_pointer str, const string& other) 
{
	return !(str == other);
}

bool string::operator<(const string& other) const
{
	return (size() == other.size()) && (std::strcmp(c_str(), other.c_str()) < 0);
}

bool string::operator<(const_pointer str) const
{
	return (size() == std::strlen(str)) && (std::strcmp(c_str(), str) < 0);
}

bool operator<(string::const_pointer str, const string& other) 
{
	return (std::strlen(str) == other.size()) && (std::strcmp(str, other.c_str()) < 0);
}

bool string::operator<=(const string& other) const
{
	return (*this == other) && (*this < other);
}

bool string::operator<=(const_pointer str) const
{
	return (*this == str) && (*this < str);
}

bool operator<=(string::const_pointer str, const string& other)
{
	return (str == other) && (str < other);
}

bool string::operator>(const string& other) const
{
	return !(*this <= other);
}

bool string::operator>(const_pointer str) const
{
	return !(*this <= str);
}

bool operator>(string::const_pointer str, const string& other) 
{
	return !(str <= other);
}

bool string::operator>=(const string& other) const
{
	return !(*this < other);
}

bool string::operator>=(const_pointer str) const
{
	return !(*this < str);
}

bool operator>=(string::const_pointer str, const string& other) 
{
	return !(str < other);
}

std::ostream& operator<<(std::ostream& out, const string& str)
{
    out << str.c_str();
    
    return out;
}

std::istream& operator>>(std::istream& in, string& str) 
{
    constexpr string::size_type bufferSize = 1024;
    
    string::value_type buffer[bufferSize];
    in.getline(buffer, bufferSize);
    str = string(buffer);

    return in;
}

string to_string(int num) 
{
	constexpr string::size_type bufferSize = 32;
    string::value_type buffer[bufferSize];
	std::snprintf(buffer, bufferSize, "%d", num);
	return string(buffer);
}

string to_string(double num) 
{
	constexpr string::size_type bufferSize = 32;
    string::value_type buffer[bufferSize];
	std::snprintf(buffer, bufferSize, "%f", num);
	return string(buffer);
}

int stoi(const string& str)
{
	std::stringstream ss{str.c_str()};
	int value;
	ss >> value;
	if (ss.fail() || ss.bad()) {
		throw std::invalid_argument("stoi: Conversion failed.");
	}
	
	return value;
}

double stod(const string& str)
{
	std::stringstream ss{str.c_str()};
	double value;
	ss >> value;
	if (ss.fail() || ss.bad()) {
		throw std::invalid_argument("stod: Conversion failed.");
	}
	
	return value;
}

string::size_type string::size() const
{
	return _size;
}

string::size_type string::length() const
{
	return _size;
}

bool string::empty() const
{
    return _size == 0;
}

string::const_pointer string::c_str() const
{
    return _isOnHeap ? _onheap : _onstack;
}

string::pointer string::data() const
{
    return _isOnHeap ? _onheap : nullptr;
}

string::value_type string::front() const
{
    return _isOnHeap ? _onheap[0] : _onstack[0];
}

string::value_type string::back() const
{
    return _isOnHeap ? _onheap[_size - 1] : _onstack[_size - 1];
}

void string::append(const_pointer str) 
{
    size_type sz =  std::strlen(str) + size();
    if (!_isOnHeap) {
        if (sz + 1 < _maxSize) {
            std::strcat(_onstack, str);
        }
        else {
            _isOnHeap = true;
            char* tmp = new char[sz + 1];
            std::strcpy(tmp, _onstack);
            std::strcat(tmp, str);
            _onheap = tmp;
        }
    }
    else {
        char* tmp = new char[sz + 1];
        std::strcpy(tmp, _onheap);
        std::strcat(tmp, str);
        _onheap = tmp;
    }
    _size = sz;
}

void string::append(const string& str)
{
    append(str.c_str());
}

string& string::insert(size_type pos, const_pointer str)
{
    if (pos > _size) {
        throw std::out_of_range("Invalid index!");
    }
    if (pos == _size) {
        append(str);
    }
    string tmp;
    tmp.append(substr(0, pos));
    tmp.append(str);
    tmp.append(substr(pos, _size - pos));
    *this = tmp;
    return *this;
}

string string::substr(size_type pos, size_type len)
{
	size_type length = size();
	
	if (pos > length || len == 0) {
		return string();
	}
	
	if (pos + len > length) {
		len = length - pos;
	}
	char* st = new char[len + 1];
	std::strncpy(st, c_str() + pos, len);
	
	return string{st};
}

string::const_reference string::at(size_type pos) const {
    if (pos >= _size) {
        throw std::out_of_range("Invalid index!");
    }
    return _isOnHeap ? _onheap[pos] : _onstack[pos];
}

string::reference string::at(size_type pos)
{
    return const_cast<reference>(std::as_const(*this).at(pos));
}

void string::clear() noexcept
{
    if (_isOnHeap) {
        delete[] _onheap;
    }
    _onstack[0] = '\0';
    _size = 0;
    _isOnHeap = false;
}

string::iterator string::begin()
{
    pointer ptr = (char*)(_isOnHeap ? _onheap : _onstack);
    return iterator{ptr};
}

string::const_iterator string::cbegin() const
{
    pointer ptr = (char*)(_isOnHeap ? _onheap : _onstack);
    return const_iterator{ptr};
}

string::iterator string::end()
{
    pointer ptr = (char*)(_isOnHeap ? _onheap : _onstack);
    return iterator{ptr + _size};
}

string::const_iterator string::cend() const
{
    pointer ptr = (char*)(_isOnHeap ? _onheap : _onstack);
    return iterator{ptr + _size};
}

void string::copyFrom(const string& src) {
    _isOnHeap = src._isOnHeap;
    if (_isOnHeap) {
        _size = src._size;
        _onheap = new char[_size + 1];
        std::strcpy(_onheap, src._onheap);
    } else {
        std::strcpy(_onstack, src._onstack);
    }
}

string operator""_ms(string::const_pointer str, string::size_type)
{
    return string{str};
}
