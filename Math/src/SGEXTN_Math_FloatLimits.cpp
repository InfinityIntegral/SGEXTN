/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#include <SGEXTN_Math_FloatLimits.h>
#include <limits>
#include <cmath>

template <typename T> T SGEXTN::Math::FloatLimits<T>::minimumPositive(){
    return std::numeric_limits<T>::min();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::maximumNegative(){
    return -std::numeric_limits<T>::min();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::maximumFinite(){
    return std::numeric_limits<T>::max();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::minimumFinite(){
    return -std::numeric_limits<T>::max();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::denormalisedMinimumPositive(){
    return std::numeric_limits<T>::denorm_min();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::denormalisedMaximumNegative(){
    return -std::numeric_limits<T>::denorm_min();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::relativeIncrementGap(){
    return std::numeric_limits<T>::epsilon();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::positiveInfinity(){
    return std::numeric_limits<T>::infinity();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::negativeInfinity(){
    return -std::numeric_limits<T>::infinity();
}

template <typename T> T SGEXTN::Math::FloatLimits<T>::notANumber(){
    return std::numeric_limits<T>::quiet_NaN();
}

template <typename T> bool SGEXTN::Math::FloatLimits<T>::isInfinite(T x){
    return std::isinf(x);
}

template <typename T> bool SGEXTN::Math::FloatLimits<T>::isNotANumber(T x){
    return std::isnan(x);
}

template class SGEXTN::Math::FloatLimits<float>;
template class SGEXTN::Math::FloatLimits<double>;
