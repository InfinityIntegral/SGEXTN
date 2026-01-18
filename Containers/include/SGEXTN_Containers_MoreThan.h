#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class MoreThan {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> class MoreThan<T*> {
public:
    [[nodiscard]] bool operator()(T* const& a, T* const& b) const;
};
}
}

#include <private_api/SGEXTN_Containers_MoreThan_impl.h>
