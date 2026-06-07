#include <SGEXTN_Math_FloatMath.h>
#include <cmath>

template <typename T> T SGEXTN::Math::FloatMath<T>::absoluteValue(T x){
    return std::fabs(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::modulo(T a, T b){
    return std::fmod(a, b);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::maximum(T a, T b){
    return std::fmax(a, b);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::minimum(T a, T b){
    return std::fmin(a, b);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::powerOfE(T x){
    return std::exp(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::powerOf2(T x){
    return std::exp2(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::naturalLog(T x){
    return std::log(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::logBase2(T x){
    return std::log2(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::logBase10(T x){
    return std::log10(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::powerOf(T a, T b){
    return std::pow(a, b);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::squareRoot(T x){
    return std::sqrt(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::cubeRoot(T x){
    return std::cbrt(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::sine(T x){
    return std::sin(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::cosine(T x){
    return std::cos(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::tangent(T x){
    return std::tan(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::arcsine(T x){
    return std::asin(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::arccosine(T x){
    return std::acos(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::arctangent(T x){
    return std::atan(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::arctangentQuadrantAware(T y, T x){
    return std::atan2(y, x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::extendedFactorial(T x){
    return std::tgamma(x + static_cast<T>(1.0f));
}

template <typename T> T SGEXTN::Math::FloatMath<T>::errorFunction(T x){
    return std::erf(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::complementaryErrorFunction(T x){
    return std::erfc(x);
}

template <typename T> T SGEXTN::Math::FloatMath<T>::ceiling(T x){
    return std::ceil(x);
}

template <typename T> int SGEXTN::Math::FloatMath<T>::ceilingToInt(T x){
    return static_cast<int>(std::ceil(x));
}

template <typename T> T SGEXTN::Math::FloatMath<T>::floor(T x){
    return std::floor(x);
}

template <typename T> int SGEXTN::Math::FloatMath<T>::floorToInt(T x){
    return static_cast<int>(std::floor(x));
}

template <typename T> T SGEXTN::Math::FloatMath<T>::round(T x){
    return std::round(x);
}

template <typename T> int SGEXTN::Math::FloatMath<T>::roundToInt(T x){
    return static_cast<int>(std::round(x));
}

template class SGEXTN::Math::FloatMath<float>;
template class SGEXTN::Math::FloatMath<double>;