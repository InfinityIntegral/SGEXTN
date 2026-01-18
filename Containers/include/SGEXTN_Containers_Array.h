#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class Array {
public:
    Array(int count);
    Array(int count, const T& defaultValue);
    Array(const Array& x);
    Array& operator=(const Array& x);
    Array(Array&& x) noexcept;
    Array& operator=(Array&& x) noexcept;
    template <typename... Ts> Array(Ts... data);
    ~Array();
    void fill(const T& defaultValue);
    [[nodiscard]] int length() const;
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] T* pointerToData(int n);
    [[nodiscard]] const T* pointerToData(int n) const;
    T* private_data;
    int private_length;
};
}
}

#include <private_api/SGEXTN_Containers_Array_impl.h>
