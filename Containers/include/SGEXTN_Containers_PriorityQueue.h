#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T, typename Comparator> class PriorityQueue {
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue& x);
    PriorityQueue& operator=(const PriorityQueue& x);
    PriorityQueue(PriorityQueue&& x) noexcept;
    PriorityQueue& operator=(PriorityQueue&& x) noexcept;
    ~PriorityQueue();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] int length() const;
    void push(const T& x);
    void pop();
    void reserve(int newMemoryLength);
    T* private_data;
    int private_length;
    int private_memoryLength;
    Comparator private_comparatorInstance;
    void private_swap(int a, int b);
    bool private_compare(int a, int b);
};
}
}

#include <private_api/SGEXTN_Containers_PriorityQueue_impl.h>
