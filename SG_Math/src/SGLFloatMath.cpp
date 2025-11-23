#include <SGLFloatMath.h>
#include <cmath>

float SGLFloatMath::absoluteValue(float x){
    return std::fabs(x);
}

float SGLFloatMath::modulo(float a, float b){
    return std::fmod(a, b);
}

float SGLFloatMath::maximum(float a, float b){
    return std::fmaxf(a, b);
}

float SGLFloatMath::minimum(float a, float b){
    return std::fminf(a, b);
}

float SGLFloatMath::eToThePowerOfThis(float x){
    return std::exp(x);
}

float SGLFloatMath::twoToThePowerOfThis(float x){
    return std::exp2(x);
}

float SGLFloatMath::naturalLogarithm(float x){
    return std::log(x);
}

float SGLFloatMath::logarithmBase2(float x){
    return std::log2(x);
}

float SGLFloatMath::logarithmBase10(float x){
    return std::log10(x);
}

float SGLFloatMath::aToThePowerOfB(float a, float b){
    return std::pow(a, b);
}

float SGLFloatMath::squareRoot(float x){
    return std::sqrt(x);
}

float SGLFloatMath::cubeRoot(float x){
    return std::cbrt(x);
}

float SGLFloatMath::sine(float x){
    return std::sin(x);
}

float SGLFloatMath::cosine(float x){
    return std::cos(x);
}

float SGLFloatMath::tangent(float x){
    return std::tan(x);
}

float SGLFloatMath::arcsine(float x){
    return std::asin(x);
}

float SGLFloatMath::arccosine(float x){
    return std::acos(x);
}

float SGLFloatMath::arctangent(float x){
    return std::atan(x);
}

float SGLFloatMath::arctangentQuadrantAware(float y, float x){
    return std::atan2(y, x);
}

float SGLFloatMath::cosecant(float x){
    return (1.0f / std::sin(x));
}

float SGLFloatMath::secant(float x){
    return (1.0f / std::cos(x));
}

float SGLFloatMath::cotangent(float x){
    return (1.0f / std::tan(x));
}

float SGLFloatMath::extendedFactorial(float x){
    return std::tgamma(x);
}

float SGLFloatMath::integralOfNormalDistributionFromLeft(float x){
    return std::erf(x);
}

float SGLFloatMath::integralOfNormalDistributionFromRight(float x){
    return std::erfc(x);
}

float SGLFloatMath::ceiling(float x){
    return std::ceil(x);
}

float SGLFloatMath::floor(float x){
    return std::floor(x);
}

float SGLFloatMath::round(float x){
    return std::round(x);
}

int SGLFloatMath::ceilingToInt(float x){
    return static_cast<int>(std::ceil(x));
}

int SGLFloatMath::floorToInt(float x){
    return static_cast<int>(std::floor(x));
}

int SGLFloatMath::roundToInt(float x){
    return static_cast<int>(std::round(x));
}

long long SGLFloatMath::ceilingToLongLong(float x){
    return static_cast<long long>(std::ceil(x));
}

long long SGLFloatMath::floorToLongLong(float x){
    return static_cast<long long>(std::floor(x));
}

long long SGLFloatMath::roundToLongLong(float x){
    return static_cast<long long>(std::round(x));
}
