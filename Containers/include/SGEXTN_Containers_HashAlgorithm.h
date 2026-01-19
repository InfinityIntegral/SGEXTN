#pragma once
#include <SGEXTN_Containers_Span.h>

namespace SGEXTN {
namespace Containers {
class HashAlgorithm {
public:
    static int wyHash32(const SGEXTN::Containers::Span<const unsigned char>& span);
};
}
}

#include <private_api/SGEXTN_Containers_HashAlgorithm_impl.h>
