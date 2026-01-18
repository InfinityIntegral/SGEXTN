#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class EqualTo {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};
}
}

#include <private_api/SGEXTN_Containers_EqualTo_impl.h>
