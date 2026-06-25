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

#include <SGEXTN/Math/IntegerMath.h>
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
