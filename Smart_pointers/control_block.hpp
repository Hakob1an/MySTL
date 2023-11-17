#ifndef CONTROL_BLOCK_HPP
#define CONTROL_BLOCK_HPP


template<typename T>
class ControlBlock
{
public:
    ControlBlock(T* ptr)
        : _ptr{ptr}
        , _weakRefCount{new int{1}}
        , _sharedRefCount{new int{1}}
    {}
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