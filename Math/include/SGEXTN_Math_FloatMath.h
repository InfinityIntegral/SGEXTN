#pragma once

namespace SGEXTN {
namespace Math {
template <typename T> class BUILDLAH_DLL_SGEXTN_Math FloatMath {
public:
    static T absoluteValue(T x);
    static T modulo(T a, T b);
    static T maximum(T a, T b);
    static T minimum(T a, T b);
    static T powerOfE(T x);
    static T powerOf2(T x);
    static T naturalLog(T x);
    static T logBase2(T x);
    static T logBase10(T x);
    static T powerOf(T a, T b);
    static T squareRoot(T x);
    static T cubeRoot(T x);
    static T sine(T x);
    static T cosine(T x);
    static T tangent(T x);
    static T arcsine(T x);
    static T arccosine(T x);
    static T arctangent(T x);
    static T arctangentQuadrantAware(T y, T x);
    static T extendedFactorial(T x);
    static T errorFunction(T x);
    static T complementaryErrorFunction(T x);
    static T ceiling(T x);
    static int ceilingToInt(T x);
    static T floor(T x);
    static int floorToInt(T x);
    static T round(T x);
    static int roundToInt(T x);
};
}
}
