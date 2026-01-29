#include <SGEXTN_Math_IntegerLimits.h>
#include <limits>
#include <type_traits>
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T> T SGEXTN::Math::IntegerLimits<T>::maximum(){
    if(std::is_same_v<T, char> == true){SGEXTN::Containers::Crash::warn("avoid using char as a integer type, use signed char or unsigned char instead");}
    if(std::is_same_v<T, long> == true || std::is_same_v<T, unsigned long> == true){SGEXTN::Containers::Crash::warn("avoid using long due to inconsistent precision on different platforms, use long long or int instead");}
    return std::numeric_limits<T>::max();
}

template <typename T> T SGEXTN::Math::IntegerLimits<T>::minimum(){
    if(std::is_same_v<T, char> == true){SGEXTN::Containers::Crash::warn("avoid using char as a integer type, use signed char or unsigned char instead");}
    if(std::is_same_v<T, long> == true || std::is_same_v<T, unsigned long> == true){SGEXTN::Containers::Crash::warn("avoid using long due to inconsistent precision on different platforms, use long long or int instead");}
    return std::numeric_limits<T>::min();
}

template class SGEXTN::Math::IntegerLimits<char>;
template class SGEXTN::Math::IntegerLimits<signed char>;
template class SGEXTN::Math::IntegerLimits<unsigned char>;
template class SGEXTN::Math::IntegerLimits<short>;
template class SGEXTN::Math::IntegerLimits<unsigned short>;
template class SGEXTN::Math::IntegerLimits<int>;
template class SGEXTN::Math::IntegerLimits<unsigned int>;
template class SGEXTN::Math::IntegerLimits<long>;
template class SGEXTN::Math::IntegerLimits<unsigned long>;
template class SGEXTN::Math::IntegerLimits<long long>;
template class SGEXTN::Math::IntegerLimits<unsigned long long>;
