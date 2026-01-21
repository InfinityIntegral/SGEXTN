#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class RingBuffer {
public:
    RingBuffer();
    RingBuffer(int count);
    RingBuffer(int count, const T& defaultValue);
    RingBuffer(const RingBuffer& x);
    RingBuffer& operator=(const RingBuffer& x);
    RingBuffer(RingBuffer&& x) noexcept;
    RingBuffer& operator=(RingBuffer&& x) noexcept;
    ~RingBuffer();
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
    T* private_data;
    int private_start;
    int private_length;
    int private_memoryLength;
    [[nodiscard]] int private_getMemoryIndex(int i) const;
};
}
}

#include <private_api/SGEXTN_Containers_RingBuffer_impl.h>
