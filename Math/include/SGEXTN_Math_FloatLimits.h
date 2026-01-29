#pragma once

namespace SGEXTN {
namespace Math {
template <typename T> class BUILDLAH_DLL_SGEXTN_Math FloatLimits {
public:
    static T minimumPositive();
    static T maximumNegative();
    static T maximumFinite();
    static T minimumFinite();
    static T denormalisedMinimumPositive();
    static T denormalisedMaximumNegative();
    static T relativeIncrementGap();
    static T positiveInfinity();
    static T negativeInfinity();
    static T notANumber();
    static bool isInfinite(T x);
    static bool isNotANumber(T x);
};
}
}
