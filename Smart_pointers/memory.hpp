#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "shared.hpp"
#include "weak.hpp"
#include "unique.hpp"

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args)
{
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //MEMORY_HPP
