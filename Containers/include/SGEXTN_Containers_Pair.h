#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T1, typename T2> class Pair {
public:
    T1 first;
    T2 second;
    Pair() = default;
    Pair(T1 first, T2 second);
    [[nodiscard]] bool operator==(const Pair& x) const;
    [[nodiscard]] bool operator!=(const Pair& x) const;
    [[nodiscard]] bool operator<(const Pair& x) const;
    [[nodiscard]] bool operator>(const Pair& x) const;
    [[nodiscard]] int hash() const;
};
}
}

#include <private_api/SGEXTN_Containers_Pair_impl.h>
