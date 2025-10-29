#ifndef SGLLONGLONGMATH_H
#define SGLLONGLONGMATH_H

#include <private_api_Math/SG_Build_Math.h>

class SG_MATH_DLL SGLLongLongMath
{
public:
    SGLLongLongMath() = delete;
    static long long absoluteValue(long long x);
    static long long minimum(long long a, long long b);
    static long long maximum(long long a, long long b);
    static long long highestCommonFactor(long long a, long long b);
    static long long lowestCommonMultiple(long long a, long long b);
};

#endif // SGLLONGLONGMATH_H
