#include <SGEXTN_Math_IntegerMath.h>
#include <numeric>

template <typename T> T SGEXTN::Math::IntegerMath<T>::absoluteValue(T x){
    if(x < 0){return (-x);}
    return x;
}

template <typename T> T SGEXTN::Math::IntegerMath<T>::minimum(T a, T b){
    if(a <= b){return a;}
    return b;
}

template <typename T> T SGEXTN::Math::IntegerMath<T>::maximum(T a, T b){
    if(a >= b){return a;}
    return b;
}

template <typename T> T SGEXTN::Math::IntegerMath<T>::highestCommonFactor(T a, T b){
    return std::gcd(a, b);
}

template <typename T> T SGEXTN::Math::IntegerMath<T>::lowestCommonMultiple(T a, T b){
    return std::lcm(a, b);
}

template class SGEXTN::Math::IntegerMath<short>;
template class SGEXTN::Math::IntegerMath<unsigned short>;
template class SGEXTN::Math::IntegerMath<int>;
template class SGEXTN::Math::IntegerMath<unsigned int>;
template class SGEXTN::Math::IntegerMath<long long>;
template class SGEXTN::Math::IntegerMath<unsigned long long>;
