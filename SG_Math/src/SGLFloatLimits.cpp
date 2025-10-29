#include <SGLFloatLimits.h>
#include <limits>
#include <cmath>

float SGLFloatLimits::minimumPositive(){
    return std::numeric_limits<float>::min();
}

float SGLFloatLimits::maximumNegative(){
    return ((-1.0f) * std::numeric_limits<float>::min());
}

float SGLFloatLimits::maximumFinite(){
    return std::numeric_limits<float>::max();
}

float SGLFloatLimits::mimimumFinite(){
    return ((-1.0f) * std::numeric_limits<float>::max());
}

float SGLFloatLimits::denormalisedMinimumPositive(){
    return std::numeric_limits<float>::denorm_min();
}

float SGLFloatLimits::denormalisedMaximumNegative(){
    return ((-1.0f) * std::numeric_limits<float>::denorm_min());
}

float SGLFloatLimits::relativeIncrementGap(){
    return std::numeric_limits<float>::epsilon();
}

float SGLFloatLimits::positiveInfinity(){
    return std::numeric_limits<float>::infinity();
}

float SGLFloatLimits::negativeInfinity(){
    return ((-1.0f) * std::numeric_limits<float>::infinity());
}

float SGLFloatLimits::notANumber(){
    return std::numeric_limits<float>::quiet_NaN();
}

bool SGLFloatLimits::isInfinite(float x){
    return std::isinf(x);
}

bool SGLFloatLimits::isNotANumber(float x){
    return std::isnan(x);
}
