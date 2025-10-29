#include <SGLFloatConstants.h>
#include <numbers>

float SGLFloatConstants::eulerNumber(){
    return std::numbers::e_v<float>;
}

float SGLFloatConstants::log2OfEulerNumber(){
    return std::numbers::log2e_v<float>;
}

float SGLFloatConstants::log10OfEulerNumber(){
    return std::numbers::log10e_v<float>;
}

float SGLFloatConstants::pi(){
    return std::numbers::pi_v<float>;
}

float SGLFloatConstants::naturalLogarithmOf2(){
    return std::numbers::ln2_v<float>;
}

float SGLFloatConstants::naturalLogarithmOf10(){
    return std::numbers::ln10_v<float>;
}

float SGLFloatConstants::squareRootOf2(){
    return std::numbers::sqrt2_v<float>;
}

float SGLFloatConstants::squareRootOf3(){
    return std::numbers::sqrt3_v<float>;
}

float SGLFloatConstants::goldenRatio(){
    return std::numbers::phi_v<float>;
}
