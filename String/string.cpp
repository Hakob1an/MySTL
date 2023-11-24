#include "string.h"


string::string() : m_onHeap{false} 
{
    m_onstack[0] = '\0';
}
string::string(const char* str) 
{
    std::size_t size = std::strlen(str);
    if (size < m_maxSize) {
        m_onHeap = false;
        std::strcpy(m_onstack, str);
    }
    else {
        m_onHeap = true;
        m_onheap.size = size;
        m_onheap.str = new char[size + 1];
        std::strcpy(m_onheap.str, str);
    }
}
string ::string(const std::string& str) : string(str.c_str())
{}
string::string(const string& src)
{
    copyFrom(src);
}
string::string(string&& src) noexcept 
{
    m_onHeap = src.m_onHeap;
    if (m_onHeap) {
        m_onheap.size = src.m_onheap.size;
        m_onheap.str = src.m_onheap.str;
    }
    else { 
        std::strcpy(m_onstack, src.m_onstack);
    }
    src.m_onHeap = false;
    src.m_onstack[0] = '\0';
}
string::~string()
{
    if (m_onHeap) {
        delete[] m_onheap.str;
    }
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
        m_onHeap = rhs.m_onHeap;
        if (m_onHeap) {
            m_onheap.size = rhs.m_onheap.size;
            m_onheap.str = rhs.m_onheap.str;
        }
        else {
            std::strcpy(m_onstack, rhs.m_onstack);
        }
        rhs.m_onHeap = false;
        rhs.m_onstack[0] = '\0';
    }
    
    return *this;
}
string& string::operator=(const char* str)
{
    std::size_t len = std::strlen(str);
	
	if (m_onHeap) {
		delete[] m_onheap.str;
		m_onHeap = false;
	}
	if (len > m_maxSize) {
    	m_onHeap = true;
    	m_onheap.size = len;
    	m_onheap.str = new char[m_onheap.size + 1];
        std::strcpy(m_onheap.str, str);
    }
    else {
   		std::strcpy(m_onstack, str);
   	}
	
    return *this;
}
string& string::operator+=(const string& s)
{
    this->append(s.c_str());
    
    return *this;
}
string& string::operator+=(const char* s)
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
string operator+(const string& s1, const char* s2)
{
    string tmp{s1};
    tmp += s2;
    
    return tmp;
}
string operator+(const char* s1, const string& s2)
{
    string tmp{s1};
    tmp += s2;
    
    return tmp;
}
bool string::operator==(const string& other) const
{
    return (size() == other.size()) && (std::strcmp(c_str(), other.c_str()) == 0);
}
bool string::operator==(const char* str) const
{
	return (size() == std::strlen(str)) && (std::strcmp(c_str(), str) == 0);
}
bool operator==(const char* str, const string& other) 
{
	return (std::strlen(str) == other.size()) && (std::strcmp(str, other.c_str()) == 0);
}
bool string::operator!=(const string& other) const
{
	return !(*this == other);
}
bool string::operator!=(const char* str) const
{
	return !(*this == str);
}
bool operator!=(const char* str, const string& other) 
{
	return !(str == other);
}
bool string::operator<(const string& other) const
{
	return (size() == other.size()) && (std::strcmp(c_str(), other.c_str()) < 0);
}
bool string::operator<(const char* str) const
{
	return (size() == std::strlen(str)) && (std::strcmp(c_str(), str) < 0);
}
bool operator<(const char* str, const string& other) 
{
	return (std::strlen(str) == other.size()) && (std::strcmp(str, other.c_str()) < 0);
}
bool string::operator<=(const string& other) const
{
	return (*this == other) && (*this < other);
}
bool string::operator<=(const char* str) const
{
	return (*this == str) && (*this < str);
}
bool operator<=(const char* str, const string& other)
{
	return (str == other) && (str < other);
}
bool string::operator>(const string& other) const
{
	return !(*this <= other);
}
bool string::operator>(const char* str) const
{
	return !(*this <= str);
}
bool operator>(const char* str, const string& other) 
{
	return !(str <= other);
}
bool string::operator>=(const string& other) const
{
	return !(*this < other);
}
bool string::operator>=(const char* str) const
{
	return !(*this < str);
}
bool operator>=(const char* str, const string& other) 
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
    constexpr std::size_t bufferSize = 1024;
    
    char buffer[bufferSize];
    in.getline(buffer, bufferSize);
    str = string(buffer);

    return in;
}
string to_string(int num) 
{
	constexpr std::size_t bufferSize = 32;
	char buffer[bufferSize];
	std::snprintf(buffer, bufferSize, "%d", num);
	return string(buffer);
}
string to_string(double num) 
{
	constexpr std::size_t bufferSize = 32;
	char buffer[bufferSize];
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
std::size_t string::size() const
{
	if (m_onHeap) {
		return m_onheap.size;
	}
	return std::strlen(m_onstack);
}
const char* string::c_str() const
{
    return m_onHeap ? m_onheap.str : m_onstack;
}
void string::append(const char* str) 
{
    std::size_t len = std::strlen(str);
    std::size_t currentLen = size();
   
    if (!m_onHeap) {
        if (currentLen + len + 1 < m_maxSize) {
            std::strcat(m_onstack, str);
        }
        else {
            m_onHeap = true;
            std::size_t size =  len + currentLen;
            char* tmp = new char[size + 1];
            std::strcpy(tmp, m_onstack);
            std::strcat(tmp, str);
            m_onheap.size = size;
            m_onheap.str = tmp;
        }
    }
    else {
        std::size_t size = len + currentLen;
        char* tmp = new char[size + 1];
        std::strcpy(tmp, m_onheap.str);
        std::strcat(tmp, str);
        m_onheap.size = size;
        m_onheap.str = tmp;
    }
}
string string::substr(std::size_t pos, std::size_t len)
{
	std::size_t length = size();
	
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
void string::copyFrom(const string& src) {
    m_onHeap = src.m_onHeap;
    if (m_onHeap) {
        m_onheap.size = src.m_onheap.size;
        m_onheap.str = new char[m_onheap.size + 1];
        std::strcpy(m_onheap.str, src.m_onheap.str);
    } else {
        std::strcpy(m_onstack, src.m_onstack);
    }
}
