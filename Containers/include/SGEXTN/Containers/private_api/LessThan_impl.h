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

template <typename T> SGEXTN::Containers::LessThan<T>::LessThan() : lengthA_(0), lengthB_(0){}

template <typename T> SGEXTN::Containers::LessThan<T>::LessThan([[maybe_unused]] const SGEXTN::Containers::LessThan<T>& x) : lengthA_(0), lengthB_(0){}

template <typename T> SGEXTN::Containers::LessThan<T>& SGEXTN::Containers::LessThan<T>::operator=([[maybe_unused]] const SGEXTN::Containers::LessThan<T>& x){
    return (*this);
}

template <typename T> SGEXTN::Containers::LessThan<T>::LessThan(SGEXTN::Containers::LessThan<T>&& x) noexcept : lengthA_(x.lengthA_), lengthB_(x.lengthB_), bufferA_(static_cast<SGEXTN::Containers::Array<unsigned char>&&>(x.bufferA_)), bufferB_(static_cast<SGEXTN::Containers::Array<unsigned char>&&>(x.bufferB_)){
    x.lengthA_ = 0;
    x.lengthB_ = 0;
}

template <typename T> SGEXTN::Containers::LessThan<T>& SGEXTN::Containers::LessThan<T>::operator=(SGEXTN::Containers::LessThan<T>&& x) noexcept {
    lengthA_ = x.lengthA_;
    lengthB_ = x.lengthB_;
    bufferA_ = static_cast<SGEXTN::Containers::Array<unsigned char>&&>(x.bufferA_);
    bufferB_ = static_cast<SGEXTN::Containers::Array<unsigned char>&&>(x.bufferB_);
    x.lengthA_ = 0;
    x.lengthB_ = 0;
    return (*this);
}

template <typename T> SGEXTN::Containers::LessThan<T>::~LessThan(){}

template <typename T> bool SGEXTN::Containers::LessThan<T>::operator()(const T& a, const T& b) const {
    if constexpr(requires{SGEXTN::Containers::IsPointer<T>::isPointer;} == false){
        if constexpr(requires{a < b;} == true){return (a < b);}
    }
    const int bufferALength = SGEXTN::Containers::Serialise<T>::sizeOut(a);
    const int bufferBLength = SGEXTN::Containers::Serialise<T>::sizeOut(b);
    if(bufferALength < bufferBLength){return true;}
    if(bufferALength > bufferBLength){return false;}
    if(bufferALength != lengthA_){
        lengthA_ = bufferALength;
        bufferA_ = SGEXTN::Containers::Array<unsigned char>(lengthA_, static_cast<unsigned char>(0));
    }
    if(bufferBLength != lengthB_){
        lengthB_ = bufferBLength;
        bufferB_ = SGEXTN::Containers::Array<unsigned char>(lengthB_, static_cast<unsigned char>(0));
    }
    const bool aIsOk = SGEXTN::Containers::Serialise<T>::sendOut(a, SGEXTN::Containers::Span<unsigned char>(bufferA_));
    const bool bIsOk = SGEXTN::Containers::Serialise<T>::sendOut(b, SGEXTN::Containers::Span<unsigned char>(bufferB_));
    if(aIsOk == false || bIsOk == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::LessThan crashed because the object could not be serialised");}
    for(int i=0; i<bufferALength; i++){
        if(bufferA_.at(i) < bufferB_.at(i)){return true;}
        if(bufferA_.at(i) > bufferB_.at(i)){return false;}
    }
    return false;
}
