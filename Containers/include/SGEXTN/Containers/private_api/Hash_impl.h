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

#pragma once
#include <SGEXTN/Containers/Span.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/ForceCrash.h>

template <typename T> int SGEXTN::Containers::Hash<T>::operator()(const T& x) const {
    const int bufferLength = SGEXTN::Containers::Serialise<T>::sizeOut(x);
    SGEXTN::Containers::Array<unsigned char> bufferArray(bufferLength);
    const SGEXTN::Containers::Span<unsigned char> span(bufferArray);
    const bool isValid = SGEXTN::Containers::Serialise<T>::sendOut(x, span);
    if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Container::Hash crashed because the object could not be serialised");}
    return SGEXTN::Containers::HashAlgorithm::wyHash32(span);
}
