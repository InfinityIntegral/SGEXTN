#include <SGEXTN_Math_FloatMath.h>
#include <cmath>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <type_traits>

template <typename T> T SGEXTN::Math::FloatMath<T>::absoluteValue(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::fabs(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::modulo(T a, T b){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::fmod(a, b);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::maximum(T a, T b){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::fmax(a, b);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::minimum(T a, T b){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::fmin(a, b);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::powerOfE(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::exp(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::powerOf2(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::exp2(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::naturalLog(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::log(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::logBase2(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::log2(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::logBase10(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::log10(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::powerOf(T a, T b){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::pow(a, b);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::squareRoot(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::sqrt(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::cubeRoot(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::cbrt(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::sine(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::sin(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::cosine(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::cos(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::tangent(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::tan(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::arcsine(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::asin(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::arccosine(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::acos(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::arctangent(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::atan(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::arctangentQuadrantAware(T y, T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::atan2(y, x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::extendedFactorial(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::tgamma(x + static_cast<T>(1.0f));
}

template <typename T> T SGEXTN::Math::FloatMath<T>::errorFunction(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::erf(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::complementaryErrorFunction(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::erfc(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::ceiling(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::ceil(x);
}

template <typename T> int SGEXTN::Math::FloatMath<T>::ceilingToInt(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return static_cast<int>(std::ceil(x));
}

template <typename T> T SGEXTN::Math::FloatMath<T>::floor(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::floor(x);
}

template <typename T> int SGEXTN::Math::FloatMath<T>::floorToInt(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return static_cast<int>(std::floor(x));
}

template <typename T> T SGEXTN::Math::FloatMath<T>::round(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return std::round(x);
}

template <typename T> int SGEXTN::Math::FloatMath<T>::roundToInt(T x){
    if(std::is_same_v<T, long double> == true){SGEXTN::Containers::Crash::warn("avoid using long double due to inconsistent precision on different platforms, use double instead");}
    return static_cast<int>(std::round(x));
}

template class SGEXTN::Math::FloatMath<float>;
template class SGEXTN::Math::FloatMath<double>;
template class SGEXTN::Math::FloatMath<long double>;
