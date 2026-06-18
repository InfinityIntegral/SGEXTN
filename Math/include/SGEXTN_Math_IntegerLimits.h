#pragma once

namespace SGEXTN {
namespace Math {
template <typename T> class BuildLah_SGEXTN_Math IntegerLimits {
public:
    [[nodiscard]] static T maximum();
    [[nodiscard]] static T minimum();
};
}
}
