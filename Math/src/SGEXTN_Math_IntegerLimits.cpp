#include <SGEXTN_Math_IntegerLimits.h>
#include <limits>

template <typename T> T SGEXTN::Math::IntegerLimits<T>::maximum(){
    return std::numeric_limits<T>::max();
}

template <typename T> T SGEXTN::Math::IntegerLimits<T>::minimum(){
    return std::numeric_limits<T>::min();
}

template class SGEXTN::Math::IntegerLimits<short>;
template class SGEXTN::Math::IntegerLimits<unsigned short>;
template class SGEXTN::Math::IntegerLimits<int>;
template class SGEXTN::Math::IntegerLimits<unsigned int>;
template class SGEXTN::Math::IntegerLimits<long long>;
template class SGEXTN::Math::IntegerLimits<unsigned long long>;
