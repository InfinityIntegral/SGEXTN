#pragma once

namespace SGEXTN {
namespace Math {
template <typename T> class BUILDLAH_DLL_SGEXTN_Math FloatMath {
public:
    [[nodiscard]] static T absoluteValue(T x);
    [[nodiscard]] static T modulo(T a, T b);
    [[nodiscard]] static T maximum(T a, T b);
    [[nodiscard]] static T minimum(T a, T b);
    [[nodiscard]] static T powerOfE(T x);
    [[nodiscard]] static T powerOf2(T x);
    [[nodiscard]] static T naturalLog(T x);
    [[nodiscard]] static T logBase2(T x);
    [[nodiscard]] static T logBase10(T x);
    [[nodiscard]] static T powerOf(T a, T b);
    [[nodiscard]] static T squareRoot(T x);
    [[nodiscard]] static T cubeRoot(T x);
    [[nodiscard]] static T sine(T x);
    [[nodiscard]] static T cosine(T x);
    [[nodiscard]] static T tangent(T x);
    [[nodiscard]] static T arcsine(T x);
    [[nodiscard]] static T arccosine(T x);
    [[nodiscard]] static T arctangent(T x);
    [[nodiscard]] static T arctangentQuadrantAware(T y, T x);
    [[nodiscard]] static T extendedFactorial(T x);
    [[nodiscard]] static T errorFunction(T x);
    [[nodiscard]] static T complementaryErrorFunction(T x);
    [[nodiscard]] static T ceiling(T x);
    [[nodiscard]] static int ceilingToInt(T x);
    [[nodiscard]] static T floor(T x);
    [[nodiscard]] static int floorToInt(T x);
    [[nodiscard]] static T round(T x);
    [[nodiscard]] static int roundToInt(T x);
};
}
}
