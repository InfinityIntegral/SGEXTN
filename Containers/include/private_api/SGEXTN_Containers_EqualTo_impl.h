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
#include <SGEXTN_Containers_Span.h>

template <typename T> bool SGEXTN::Containers::EqualTo<T>::operator()(const T& a, const T& b) const {
    return (a == b);
}

template <typename T> bool SGEXTN::Containers::EqualTo<T*>::operator()(const T* a, const T* b) const {
    const int typeMemoryLength = sizeof(T*);
    SGEXTN::Containers::Span<const unsigned char> aSpan(reinterpret_cast<const unsigned char*>(&a), typeMemoryLength);
    SGEXTN::Containers::Span<const unsigned char> bSpan(reinterpret_cast<const unsigned char*>(&b), typeMemoryLength);
    for(int i=0; i<typeMemoryLength; i++){
        if(aSpan.at(i) != bSpan.at(i)){return false;}
    }
    return true;
}

template <typename ReturnType, typename... ArgTypes> bool SGEXTN::Containers::EqualTo<ReturnType (*)(ArgTypes...)>::operator()(ReturnType (*a)(ArgTypes...), ReturnType (*b)(ArgTypes...)) const {
    const int typeMemoryLength = sizeof(ReturnType (*)(ArgTypes...));
    SGEXTN::Containers::Span<const unsigned char> aSpan(reinterpret_cast<const unsigned char*>(&a), typeMemoryLength);
    SGEXTN::Containers::Span<const unsigned char> bSpan(reinterpret_cast<const unsigned char*>(&b), typeMemoryLength);
    for(int i=0; i<typeMemoryLength; i++){
        if(aSpan.at(i) != bSpan.at(i)){return false;}
    }
    return true;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> bool SGEXTN::Containers::EqualTo<ReturnType (ClassName::*)(ArgTypes...)>::operator()(ReturnType (ClassName::*a)(ArgTypes...), ReturnType (ClassName::*b)(ArgTypes...)) const {
    const int typeMemoryLength = sizeof(ReturnType (ClassName::*)(ArgTypes...));
    SGEXTN::Containers::Span<const unsigned char> aSpan(reinterpret_cast<const unsigned char*>(&a), typeMemoryLength);
    SGEXTN::Containers::Span<const unsigned char> bSpan(reinterpret_cast<const unsigned char*>(&b), typeMemoryLength);
    for(int i=0; i<typeMemoryLength; i++){
        if(aSpan.at(i) != bSpan.at(i)){return false;}
    }
    return true;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> bool SGEXTN::Containers::EqualTo<ReturnType (ClassName::*)(ArgTypes...) const>::operator()(ReturnType (ClassName::*a)(ArgTypes...) const, ReturnType (ClassName::*b)(ArgTypes...) const) const {
    const int typeMemoryLength = sizeof(ReturnType (ClassName::*)(ArgTypes...) const);
    SGEXTN::Containers::Span<const unsigned char> aSpan(reinterpret_cast<const unsigned char*>(&a), typeMemoryLength);
    SGEXTN::Containers::Span<const unsigned char> bSpan(reinterpret_cast<const unsigned char*>(&b), typeMemoryLength);
    for(int i=0; i<typeMemoryLength; i++){
        if(aSpan.at(i) != bSpan.at(i)){return false;}
    }
    return true;
}
