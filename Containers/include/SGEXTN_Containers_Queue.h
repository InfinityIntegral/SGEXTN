#pragma once
#include <private_api/SGEXTN_Containers_RingBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Queue {
public:
    Queue();
    [[nodiscard]] T& front();
    [[nodiscard]] const T& front() const;
    [[nodiscard]] T& back();
    [[nodiscard]] const T& back() const;
    [[nodiscard]] int length() const;
    void push(const T& x);
    void pop();
    void reserve(int newMemoryLength);
    SGEXTN::Containers::RingBuffer<T> private_ringBuffer;
};
}
}

#include <private_api/SGEXTN_Containers_Queue_impl.h>
