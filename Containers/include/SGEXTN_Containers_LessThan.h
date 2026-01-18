#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class LessThan {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> class LessThan<T*> {
public:
    [[nodiscard]] bool operator()(T* const& a, T* const& b) const;
};
}
}

#include <private_api/SGEXTN_Containers_LessThan_impl.h>
