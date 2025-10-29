#ifndef SGLFLOATMATH_H
#define SGLFLOATMATH_H

#include <private_api_Math/SG_Build_Math.h>

class SG_MATH_DLL SGLFloatMath
{
public:
    SGLFloatMath() = delete;
    static float absoluteValue(float x);
    static float modulo(float a, float b);
    static float maximum(float a, float b);
    static float minimum(float a, float b);
    static float eToThePowerOfThis(float x);
    static float twoToThePowerOfThis(float x);
    static float naturalLogarithm(float x);
    static float logarithmBase2(float x);
    static float logarithmBase10(float x);
    static float aToThePowerOfB(float a, float b);
    static float squareRoot(float x);
    static float cubeRoot(float x);
    static float sine(float x);
    static float cosine(float x);
    static float tangent(float x);
    static float arcsine(float x);
    static float arccosine(float x);
    static float arctangent(float x);
    static float arctangentQuadrantAware(float y, float x);
    static float cosecant(float x);
    static float secant(float x);
    static float cotangent(float x);
    static float extendedFactorial(float x);
    static float integralOfNormalDistributionFromLeft(float x);
    static float integralOfNormalDistributionFromRight(float x);
    static float ceiling(float x);
    static float floor(float x);
    static float round(float x);
    static int ceilingToInt(float x);
    static int floorToInt(float x);
    static int roundToInt(float x);
    static long long ceilingToLongLong(float x);
    static long long floorToLongLong(float x);
    static long long roundToLongLong(float x);
};

#endif // SGLFLOATMATH_H
