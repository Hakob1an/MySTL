#ifndef CONTROL_BLOCK_HPP
#define CONTROL_BLOCK_HPP

#include <utility>

template<typename T>
class ControlBlock
{
public:
    ControlBlock(T* ptr)
        : _ptr{ptr}
        , _weakRefCount{new int{0}}
        , _sharedRefCount{new int{1}}
    {}
    ControlBlock(const ControlBlock& src)
    {
        _ptr = new T{*(src._ptr)};
        _weakRefCount = new int{*(src._weakRefCount)};
        _sharedRefCount = new int{*(src._sharedrefCount)};
    }
    ControlBlock(const ControlBlock&& src)
    {
        _ptr = std::exchange(src._ptr, nullptr);
        _weakRefCount = std::exchange(src._weakRefCount, nullptr);
        _sharedRefCount = std::exchange(src._sharedRefCount, nullptr);
    }
    void incrementSharedRefCount()
    {
        ++(*_sharedRefCount);
    }
    void decrementSharedRefCount()
    {
        --(*_sharedRefCount);
    }
    void incrementWeakRefCount()
    {
        ++(*_weakRefCount);
    }
    void decrementWeakRefCount()
    {
        --(*_weakRefCount);
    }
    T* get() const
    {
        return _ptr;
    }
    int getSharedCount() const
    {
        return *_sharedRefCount;
    }
    int getWeakCount() const
    {
        return *_weakRefCount;
    }
    void free()
    {
        if (_ptr) {
    	    --(*_sharedRefCount);
    	    if (*_sharedRefCount == 0) {
        	    delete _ptr;
        	    delete _sharedRefCount;
                delete _weakRefCount;
    	    }
        }
    }
private:
    T* _ptr;
    int* _weakRefCount;
    int* _sharedRefCount;
};

#endif //CONTROL_BLOCK_HPP
