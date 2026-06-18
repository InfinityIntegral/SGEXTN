#pragma once

namespace SGEXTN {
namespace Math {
template <typename T> class BuildLah_SGEXTN_Math IntegerMath {
public:
    [[nodiscard]] static T absoluteValue(T x);
    [[nodiscard]] static T minimum(T a, T b);
    [[nodiscard]] static T maximum(T a, T b);
    [[nodiscard]] static T highestCommonFactor(T a, T b);
    [[nodiscard]] static T lowestCommonMultiple(T a, T b);
};
}
}
