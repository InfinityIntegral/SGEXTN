#pragma once
#include <private_api/SGEXTN_Containers_RingBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Stack {
public:
    Stack();
    [[nodiscard]] T& top();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] int length() const;
    void push(const T& x);
    void pop();
    void reserve(int newMemoryLength);
    SGEXTN::Containers::RingBuffer<T> private_ringBuffer;
};
}
}

#include <private_api/SGEXTN_Containers_Stack_impl.h>
