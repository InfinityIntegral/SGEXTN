#pragma once

namespace SGEXTN {
namespace Math {
template <typename T> class BUILDLAH_DLL_SGEXTN_Math IntegerMath {
public:
    static T absoluteValue(T x);
    static T minimum(T a, T b);
    static T maximum(T a, T b);
    static T highestCommonFactor(T a, T b);
    static T lowestCommonMultiple(T a, T b);
};
}
}
