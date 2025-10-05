#include "sglfloatmath.h"
#include <cmath>

float SGLFloatMath::absoluteValue(float x){
    return std::fabsf(x);
}

float SGLFloatMath::modulo(float a, float b){
    return std::fmodf(a, b);
}

float SGLFloatMath::maximum(float a, float b){
    return std::fmaxf(a, b);
}

float SGLFloatMath::minimum(float a, float b){
    return std::fminf(a, b);
}

float SGLFloatMath::eToThePowerOfThis(float x){
    return std::expf(x);
}

float SGLFloatMath::twoToThePowerOfThis(float x){
    return std::exp2f(x);
}

float SGLFloatMath::naturalLogarithm(float x){
    return std::logf(x);
}

float SGLFloatMath::logarithmBase2(float x){
    return std::log2f(x);
}

float SGLFloatMath::logarithmBase10(float x){
    return std::log10f(x);
}

float SGLFloatMath::aToThePowerOfB(float a, float b){
    return std::powf(a, b);
}

float SGLFloatMath::squareRoot(float x){
    return std::sqrtf(x);
}

float SGLFloatMath::cubeRoot(float x){
    return std::cbrtf(x);
}

float SGLFloatMath::sine(float x){
    return std::sinf(x);
}

float SGLFloatMath::cosine(float x){
    return std::cosf(x);
}

float SGLFloatMath::tangent(float x){
    return std::tanf(x);
}

float SGLFloatMath::arcsine(float x){
    return std::asinf(x);
}

float SGLFloatMath::arccosine(float x){
    return std::acosf(x);
}

float SGLFloatMath::arctangent(float x){
    return std::atanf(x);
}

float SGLFloatMath::arctangentQuadrantAware(float y, float x){
    return std::atan2f(y, x);
}

float SGLFloatMath::cosecant(float x){
    return (1.0f / std::sinf(x));
}

float SGLFloatMath::secant(float x){
    return (1.0f / std::cosf(x));
}

float SGLFloatMath::cotangent(float x){
    return (1.0f / std::tanf(x));
}

float SGLFloatMath::extendedFactorial(float x){
    return std::tgammaf(x);
}

float SGLFloatMath::integralOfNormalDistributionFromLeft(float x){
    return std::erff(x);
}

float SGLFloatMath::integralOfNormalDistributionFromRight(float x){
    return std::erfcf(x);
}

float SGLFloatMath::ceiling(float x){
    return std::ceilf(x);
}

float SGLFloatMath::floor(float x){
    return std::floorf(x);
}

float SGLFloatMath::round(float x){
    return std::roundf(x);
}

int SGLFloatMath::ceilingToInt(float x){
    return static_cast<int>(std::ceilf(x));
}

int SGLFloatMath::floorToInt(float x){
    return static_cast<int>(std::floorf(x));
}

int SGLFloatMath::roundToInt(float x){
    return static_cast<int>(std::roundf(x));
}

long long SGLFloatMath::ceilingToLongLong(float x){
    return static_cast<long long>(std::ceilf(x));
}

long long SGLFloatMath::floorToLongLong(float x){
    return static_cast<long long>(std::floorf(x));
}

long long SGLFloatMath::roundToLongLong(float x){
    return static_cast<long long>(std::roundf(x));
}
