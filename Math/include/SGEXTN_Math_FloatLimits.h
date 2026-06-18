#pragma once

namespace SGEXTN {
namespace Math {
template <typename T> class BuildLah_SGEXTN_Math FloatLimits {
public:
    [[nodiscard]] static T minimumPositive();
    [[nodiscard]] static T maximumNegative();
    [[nodiscard]] static T maximumFinite();
    [[nodiscard]] static T minimumFinite();
    [[nodiscard]] static T denormalisedMinimumPositive();
    [[nodiscard]] static T denormalisedMaximumNegative();
    [[nodiscard]] static T relativeIncrementGap();
    [[nodiscard]] static T positiveInfinity();
    [[nodiscard]] static T negativeInfinity();
    [[nodiscard]] static T notANumber();
    [[nodiscard]] static bool isInfinite(T x);
    [[nodiscard]] static bool isNotANumber(T x);
};
}
}
