#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class Span {
public:
    Span(T* data, int length);
    [[nodiscard]] int length() const;
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] Span subspan(int start, int length) const;
    [[nodiscard]] Span subspanLeft(int length) const;
    [[nodiscard]] Span subspanRight(int length) const;
    [[nodiscard]] T* pointerToData(int n);
    [[nodiscard]] const T* pointerToData(int n) const;
    T* private_data;
    int private_length;
};
}
}

#include <private_api/SGEXTN_Containers_Span_impl.h>
