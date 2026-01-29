#include <SGEXTN_Math_FloatLimits.h>
#include <limits>
#include <cmath>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <type_traits>

template <typename T> T SGEXTN::Math::FloatLimits<T>::minimumPositive(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numeric_limits<T>::min();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::maximumNegative(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return -std::numeric_limits<T>::min();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::maximumFinite(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numeric_limits<T>::max();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::minimumFinite(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return -std::numeric_limits<T>::max();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::denormalisedMinimumPositive(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numeric_limits<T>::denorm_min();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::denormalisedMaximumNegative(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return -std::numeric_limits<T>::denorm_min();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::relativeIncrementGap(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numeric_limits<T>::epsilon();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::positiveInfinity(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numeric_limits<T>::infinity();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::negativeInfinity(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return -std::numeric_limits<T>::infinity();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::notANumber(){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::numeric_limits<T>::quiet_NaN();
}

template <typename T> bool SGEXTN::Math::FloatLimits<T>::isInfinite(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::isinf(x);
}

template <typename T> bool SGEXTN::Math::FloatLimits<T>::isNotANumber(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::isnan(x);
}

template class SGEXTN::Math::FloatLimits<float>;
template class SGEXTN::Math::FloatLimits<double>;
template class SGEXTN::Math::FloatLimits<long double>;
