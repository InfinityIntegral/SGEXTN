#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class Span;

class HashAlgorithm {
public:
    [[nodiscard]] static int wyHash32(const SGEXTN::Containers::Span<const unsigned char>& span);
};
}
}

#include <private_api/SGEXTN_Containers_HashAlgorithm_impl.h>
