#include "ObjPool.hpp"

template <typename T>
ObjectPool<T>::ObjectPool(size_t size) {
    pool.resize(size);
    for (auto& obj : pool) {
        available.push_back(&obj);
    }
}

template <typename T>
T* ObjectPool<T>::Get() {
    if (available.empty()) return nullptr;
    T* obj = available.back();
    available.pop_back();
    return obj;
}

template <typename T>
void ObjectPool<T>::Return(T* object) {
    object->Deactivate();
    available.push_back(object);
}