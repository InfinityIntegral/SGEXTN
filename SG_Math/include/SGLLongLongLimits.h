#ifndef SGLLONGLONGLIMITS_H
#define SGLLONGLONGLIMITS_H

#include <private_api_Math/SG_Build_Math.h>

class SG_MATH_DLL SGLLongLongLimits
{
public:
    SGLLongLongLimits() = delete;
    static long long maximum();
    static long long minimum();
};

#endif // SGLLONGLONGLIMITS_H
