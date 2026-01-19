#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T1, typename T2, typename T3> class Tuple3 {
public:
    T1 first;
    T2 second;
    T3 third;
    Tuple3() = default;
    Tuple3(T1 first, T2 second, T3 third);
    [[nodiscard]] bool operator==(const Tuple3& x) const;
    [[nodiscard]] bool operator!=(const Tuple3& x) const;
    [[nodiscard]] bool operator<(const Tuple3& x) const;
    [[nodiscard]] bool operator>(const Tuple3& x) const;
    [[nodiscard]] int hash() const;
};
}
}

#include <private_api/SGEXTN_Containers_Tuple3_impl.h>
