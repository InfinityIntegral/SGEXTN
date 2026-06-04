#pragma once
#include <private_api/SGEXTN_Containers_RingBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T, typename Comparator> class PriorityQueue {
public:
    PriorityQueue();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] int length() const;
    void push(const T& x);
    void pop();
    void reserve(int newMemoryLength);
    void clear();
    SGEXTN::Containers::RingBuffer<T> private_ringBuffer;
    Comparator private_comparatorInstance;
    void private_swap(int a, int b);
    bool private_compare(int a, int b);
};
}
}

#include <private_api/SGEXTN_Containers_PriorityQueue_impl.h>
