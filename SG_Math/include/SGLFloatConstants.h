#ifndef SGLFLOATCONSTANTS_H
#define SGLFLOATCONSTANTS_H

#include <private_api_Math/SG_Build_Math.h>

class SG_MATH_DLL SGLFloatConstants
{
public:
    SGLFloatConstants() = delete;
    static float eulerNumber();
    static float log2OfEulerNumber();
    static float log10OfEulerNumber();
    static float pi();
    static float naturalLogarithmOf2();
    static float naturalLogarithmOf10();
    static float squareRootOf2();
    static float squareRootOf3();
    static float goldenRatio();
};

#endif // SGLFLOATCONSTANTS_H
