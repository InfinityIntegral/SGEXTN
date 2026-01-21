#pragma once
#include <private_api/SGEXTN_Containers_RingBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Deque {
public:
    Deque();
    Deque(int count);
    Deque(int count, const T& defaultValue);
    void fill(const T& defaultValue);
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] T& front();
    [[nodiscard]] const T& front() const;
    [[nodiscard]] T& back();
    [[nodiscard]] const T& back() const;
    [[nodiscard]] int length() const;
    void pushBack(const T& x);
    void popBack();
    void pushFront(const T& x);
    void popFront();
    void reserve(int newMemoryLength);
    [[nodiscard]] T* pointerToData(int n);
    [[nodiscard]] const T* pointerToData(int n) const;
    SGEXTN::Containers::RingBuffer<T> private_ringBuffer;
};
}
}

#include <private_api/SGEXTN_Containers_Deque_impl.h>
