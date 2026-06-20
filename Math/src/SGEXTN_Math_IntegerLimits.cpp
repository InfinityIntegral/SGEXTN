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
