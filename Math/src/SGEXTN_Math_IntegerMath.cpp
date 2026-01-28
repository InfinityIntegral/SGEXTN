#include <SGEXTN_Math_IntegerMath.h>
#include <numeric>
#include <type_traits>
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T> T SGEXTN::Math::IntegerMath<T>::absoluteValue(T x){
    if(std::is_same_v<T, char> == true){SGEXTN::Containers::Crash::warn("avoid using char as a integer type, use signed char or unsigned char instead");}
    if(x < 0){return (-x);}
    return x;
}

template <typename T> T SGEXTN::Math::IntegerMath<T>::minimum(T a, T b){
    if(std::is_same_v<T, char> == true){SGEXTN::Containers::Crash::warn("avoid using char as a integer type, use signed char or unsigned char instead");}
    if(a <= b){return a;}
    return b;
}

template <typename T> T SGEXTN::Math::IntegerMath<T>::maximum(T a, T b){
    if(std::is_same_v<T, char> == true){SGEXTN::Containers::Crash::warn("avoid using char as a integer type, use signed char or unsigned char instead");}
    if(a >= b){return a;}
    return b;
}

template <typename T> T SGEXTN::Math::IntegerMath<T>::highestCommonFactor(T a, T b){
    if(std::is_same_v<T, char> == true){SGEXTN::Containers::Crash::warn("avoid using char as a integer type, use signed char or unsigned char instead");}
    return std::gcd(a, b);
}

template <typename T> T SGEXTN::Math::IntegerMath<T>::lowestCommonMultiple(T a, T b){
    if(std::is_same_v<T, char> == true){SGEXTN::Containers::Crash::warn("avoid using char as a integer type, use signed char or unsigned char instead");}
    return std::lcm(a, b);
}

template class SGEXTN::Math::IntegerMath<char>;
template class SGEXTN::Math::IntegerMath<signed char>;
template class SGEXTN::Math::IntegerMath<unsigned char>;
template class SGEXTN::Math::IntegerMath<short>;
template class SGEXTN::Math::IntegerMath<unsigned short>;
template class SGEXTN::Math::IntegerMath<int>;
template class SGEXTN::Math::IntegerMath<unsigned int>;
template class SGEXTN::Math::IntegerMath<long long>;
template class SGEXTN::Math::IntegerMath<unsigned long long>;
