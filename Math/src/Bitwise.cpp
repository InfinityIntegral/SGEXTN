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

#include <SGEXTN/Math/Bitwise.h>
#include <bit>

template <typename T> bool SGEXTN::Math::Bitwise<T>::isPowerOf2(T x){
    return std::has_single_bit(x);
}

template <typename T> T SGEXTN::Math::Bitwise<T>::ceilingToPowerOf2(T x){
    return std::bit_ceil(x);
}

template <typename T> T SGEXTN::Math::Bitwise<T>::floorToPowerOf2(T x){
    return std::bit_floor(x);
}

template <typename T> int SGEXTN::Math::Bitwise<T>::requiredStorageBits(T x){
    return std::bit_width(x);
}

template <typename T> T SGEXTN::Math::Bitwise<T>::leftRotate(T x, int amount){
    return std::rotl(x, amount);
}

template <typename T> T SGEXTN::Math::Bitwise<T>::rightRotate(T x, int amount){
    return std::rotr(x, amount);
}

template <typename T> int SGEXTN::Math::Bitwise<T>::leftCountConsecutiveZero(T x){
    return std::countl_zero(x);
}

template <typename T> int SGEXTN::Math::Bitwise<T>::rightCountConsecutiveZero(T x){
    return std::countr_zero(x);
}

template <typename T> int SGEXTN::Math::Bitwise<T>::leftCountConsecutiveOne(T x){
    return std::countl_one(x);
}

template <typename T> int SGEXTN::Math::Bitwise<T>::rightCountConsecutiveOne(T x){
    return std::countr_one(x);
}

template <typename T> int SGEXTN::Math::Bitwise<T>::countNumberOfOne(T x){
    return std::popcount(x);
}

template <typename T> int SGEXTN::Math::Bitwise<T>::countNumberOfZero(T x){
    return (8 * sizeof(x) - std::popcount(x));
}

template class SGEXTN::Math::Bitwise<unsigned short>;
template class SGEXTN::Math::Bitwise<unsigned int>;
template class SGEXTN::Math::Bitwise<unsigned long long>;
