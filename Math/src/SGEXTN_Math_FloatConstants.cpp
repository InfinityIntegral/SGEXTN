#include <SGEXTN_Math_FloatConstants.h>
#include <numbers>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <type_traits>

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumber(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumberLog2(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::log2e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumberLog10(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::log10e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::pi(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::pi_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::naturalLog2(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::ln2_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::naturalLog10(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::ln10_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::squareRoot2(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::sqrt2_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::squareRoot3(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::sqrt3_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::goldenRatio(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numbers::phi_v<T>;
}

template class SGEXTN::Math::FloatConstants<float>;
template class SGEXTN::Math::FloatConstants<double>;
template class SGEXTN::Math::FloatConstants<long double>;
