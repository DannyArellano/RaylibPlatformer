#ifndef OBJPOOL_HPP
#define OBJPOOL_HPP

#include <vector>
#include <cstddef> // Include this header for size_t

#include "raymath.h"

template <typename T>
class ObjectPool {
public:
    ObjectPool(size_t size);
    T* Get();
    void Return(T* object);

private:
    std::vector<T> pool;
    std::vector<T*> available;
};

#include "ObjPool.inl"

#endif // OBJPOOL_HPP