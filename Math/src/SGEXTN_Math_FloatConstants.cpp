#include <SGEXTN_Math_FloatConstants.h>
#include <numbers>

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumber(){
    return std::numbers::e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumberLog2(){
    return std::numbers::log2e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumberLog10(){
    return std::numbers::log10e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::pi(){
    return std::numbers::pi_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::naturalLog2(){
    return std::numbers::ln2_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::naturalLog10(){
    return std::numbers::ln10_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::squareRoot2(){
    return std::numbers::sqrt2_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::squareRoot3(){
    return std::numbers::sqrt3_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::goldenRatio(){
    return std::numbers::phi_v<T>;
}

template class SGEXTN::Math::FloatConstants<float>;
template class SGEXTN::Math::FloatConstants<double>;
