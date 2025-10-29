#ifndef SGLINTLIMITS_H
#define SGLINTLIMITS_H

#include <private_api_Math/SG_Build_Math.h>

class SG_MATH_DLL SGLIntLimits
{
public:
    SGLIntLimits() = delete;
    static int maximum();
    static int minimum();
};

#endif // SGLINTLIMITS_H
