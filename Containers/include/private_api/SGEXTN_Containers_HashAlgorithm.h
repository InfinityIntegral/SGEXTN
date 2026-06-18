#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class Span;

class BuildLah_SGEXTN_Containers HashAlgorithm {
public:
    [[nodiscard]] static int wyHash32(const SGEXTN::Containers::Span<const unsigned char>& span);
};
}
}
