#pragma once
#include <private_api/SGEXTN_Containers_RingBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Vector {
public:
    Vector();
    Vector(int count);
    Vector(int count, const T& defaultValue);
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] int length() const;
    void fill(const T& defaultValue);
    void reserve(int newMemoryLength);
    void pushBack(const T& x);
    void popBack();
    [[nodiscard]] T* pointerToData(int n);
    [[nodiscard]] const T* pointerToData(int n) const;
    SGEXTN::Containers::RingBuffer<T> private_ringBuffer;
};
}
}

#include <private_api/SGEXTN_Containers_Vector_impl.h>
