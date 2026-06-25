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

#include <SGEXTN/Math/FloatConstants.h>
#include <numbers>

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumber(){
    return std::numbers::e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumberLog2(){
    return std::numbers::log2e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::eulerNumberLog10(){
    return std::numbers::log10e_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::pi(){
    return std::numbers::pi_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::naturalLog2(){
    return std::numbers::ln2_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::naturalLog10(){
    return std::numbers::ln10_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::squareRoot2(){
    return std::numbers::sqrt2_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::squareRoot3(){
    return std::numbers::sqrt3_v<T>;
}

template <typename T> T SGEXTN::Math::FloatConstants<T>::goldenRatio(){
    return std::numbers::phi_v<T>;
}

template class SGEXTN::Math::FloatConstants<float>;
template class SGEXTN::Math::FloatConstants<double>;
