#ifndef SGLFLOATLIMITS_H
#define SGLFLOATLIMITS_H

#include <private_api_Math/SG_Build_Math.h>

class SG_MATH_DLL SGLFloatLimits
{
public:
    SGLFloatLimits() = delete;
    static float minimumPositive();
    static float maximumNegative();
    static float maximumFinite();
    static float mimimumFinite();
    static float denormalisedMinimumPositive();
    static float denormalisedMaximumNegative();
    static float relativeIncrementGap();
    static float positiveInfinity();
    static float negativeInfinity();
    static float notANumber();
    static bool isInfinite(float x);
    static bool isNotANumber(float x);
};

#endif // SGLFLOATLIMITS_H
