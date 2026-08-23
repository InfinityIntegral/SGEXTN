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
#include <SGEXTN/Containers/private_api/TypeTraits.h>
#include <SGEXTN/Containers/Serialise.h>

template <typename T> SGEXTN::Containers::EqualTo<T>::EqualTo() : lengthA(0), lengthB(0), bufferA(0), bufferB(0){}

template <typename T> bool SGEXTN::Containers::EqualTo<T>::operator()(const T& a, const T& b){
    if constexpr(requires{SGEXTN::Containers::IsPointer<T>::isPointer;} == false){
        if constexpr(requires{a == b;} == true){return (a == b);}
    }
    const int bufferALength = SGEXTN::Containers::Serialise<T>::sizeOut(a);
    const int bufferBLength = SGEXTN::Containers::Serialise<T>::sizeOut(b);
    if(bufferALength != bufferBLength){return false;}
    if(bufferALength != lengthA){
        lengthA = bufferALength;
        bufferA = SGEXTN::Containers::Array<unsigned char>(lengthA);
    }
    if(bufferBLength != lengthB){
        lengthB = bufferBLength;
        bufferB = SGEXTN::Containers::Array<unsigned char>(lengthB);
    }
    const bool aIsOk = SGEXTN::Containers::Serialise<T>::sendOut(a, SGEXTN::Containers::Span<unsigned char>(bufferA));
    const bool bIsOk = SGEXTN::Containers::Serialise<T>::sendOut(b, SGEXTN::Containers::Span<unsigned char>(bufferB));
    if(aIsOk == false || bIsOk == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::EqualTo crashed because the object could not be serialised");}
    for(int i=0; i<bufferALength; i++){
        if(bufferA.at(i) != bufferB.at(i)){return false;}
    }
    return true;
}
