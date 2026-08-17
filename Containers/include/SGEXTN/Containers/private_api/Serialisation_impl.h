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
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/Span.h>
#include <SGEXTN/Containers/ForceCrash.h>

namespace SGEXTN { namespace Containers { template <typename T1, typename T2> class IsSameType {};
template <typename T> class IsSameType<T, T> {public: static bool same;}; template <typename T> bool IsSameType<T, T>::same = true;} }

template <typename... Ts> bool SGEXTN::Containers::Serialisation<Ts...>::sendOut(const Ts&... xs, SGEXTN::Containers::Span<unsigned char> data){
    const int requiredLength = SGEXTN::Containers::Serialisation<Ts...>::sizeOut(xs...);
    if(data.length() != requiredLength){return false;}
    int offset = 0;
    int nextLength = 0;
    bool isValid = true;
    bool nextValid = true;
    const bool finalResult = ((nextLength = SGEXTN::Containers::Serialisation<Ts>::sizeOut(xs), nextValid = SGEXTN::Containers::Serialisation<Ts>::sendOut(xs, data.subspan(offset, nextLength)), isValid = (isValid && nextValid), offset += nextLength, isValid == true) && ...);
    return finalResult;
}

template <typename... Ts> bool SGEXTN::Containers::Serialisation<Ts...>::sendIn(Ts&... xs, SGEXTN::Containers::Span<unsigned char> data){
    const int requiredLength = SGEXTN::Containers::Serialisation<Ts...>::sizeIn(data);
    if(data.length() != requiredLength){return false;}
    int offset = 0;
    int nextLength = 0;
    bool nextValid = false;
    bool isValid = true;
    const bool finalResult = ((nextLength = SGEXTN::Containers::Serialisation<Ts>::sizeIn(data.subspanRight(data.length() - offset)), nextValid = SGEXTN::Containers::Serialisation<Ts>::sendIn(xs, data.subspan(offset, nextLength)), offset += nextLength, isValid = (isValid && nextValid), isValid == true) && ...);
    return finalResult;
}

template <typename... Ts> int SGEXTN::Containers::Serialisation<Ts...>::sizeOut(const Ts&... xs){
    return (0 + ... + SGEXTN::Containers::Serialisation<Ts>::sizeOut(xs));
}

template <typename... Ts> int SGEXTN::Containers::Serialisation<Ts...>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    int nextLength = 0;
    int offset = 0;
    bool isOk = true;
    const bool finalResult = ((nextLength = SGEXTN::Containers::Serialisation<Ts>::sizeIn(data.subspanRight(data.length() - offset)), isOk = isOk && (nextLength != -1), offset += nextLength, isOk = isOk && (data.length() >= offset), isOk == true) && ...);
    if(finalResult == true){return offset;}
    return -1;
}

template <typename T> bool SGEXTN::Containers::Serialisation<T>::sendOut(const T& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialisation<T>::sizeOut(x)){return false;}
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::sendOut(x, data)), bool>::same;}){return T::sendOut(x, data);}
    SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialisation::sendOut requires custom type T to have bool T::sendOut(const T& x, SGEXTN::Containers::Span<unsigned char>& data); properly defined to work");
}

template <typename T> bool SGEXTN::Containers::Serialisation<T>::sendIn(T& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialisation<T>::sizeIn(data)){return false;}
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::sendIn(x, data)), bool>::same;}){return T::sendIn(x, data);}
    SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialisation::sendIn requires custom type T to have bool T::sendIn(T& x, SGEXTN::Containers::Span<unsigned char> data); properly defined to work");
}

template <typename T> int SGEXTN::Containers::Serialisation<T>::sizeOut(const T& x){
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::size()), int>::same;}){return T::size();}
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::sizeOut(x)), int>::same;}){return T::sizeOut(x);}
    SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialisation::sizeOut requires custom type T to have int T::sizeOut(const T& x); properly defined if T has variable size or int T::size(); properly defined if T has constant size to work");
}

template <typename T> int SGEXTN::Containers::Serialisation<T>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    int requiredLength = 0;
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::size()), int>::same;}){requiredLength = T::size();}
    else if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::sizeIn(data)), int>::same;}){requiredLength = T::sizeIn(data);}
    else{SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialisation::sizeIn requires custom type T to have int T::sizeIn(SGEXTN::Containers::Span<unsigned char> data); properly defined if T has variable size or int T::size(); properly defined if T has constant size to work");}
    if(requiredLength > data.length()){return -1;}
    return requiredLength;
}

template <typename T> bool SGEXTN::Containers::Serialisation<SGEXTN::Containers::Array<T>>::sendOut(const SGEXTN::Containers::Array<T>& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialisation<SGEXTN::Containers::Array<T>>::sizeOut(x)){return false;}
    if(x.length() == 0){return SGEXTN::Containers::Serialisation<bool, int>::sendOut(false, 0, data);}
    bool lengthVaries = false;
    const int firstLength = SGEXTN::Containers::Serialisation<T>::sizeOut(x.at(0));
    for(int i=1; i<x.length(); i++){
        if(SGEXTN::Containers::Serialisation<T>::sizeOut(x.at(i)) != firstLength){
            lengthVaries = true;
            break;
        }
    }
    if(lengthVaries == false){
        bool success = SGEXTN::Containers::Serialisation<bool, int, int>::sendOut(false, x.length(), firstLength, data.subspanLeft(9));
        if(success == false){return false;}
        for(int i=0; i<x.length(); i++){
            success = SGEXTN::Containers::Serialisation<T>::sendOut(x.at(i), data.subspan(9 + i * firstLength, firstLength));
            if(success == false){return false;}
        }
        return true;
    }
    {
        const int totalLength = 5;
        bool success = SGEXTN::Containers::Serialisation<bool, int>::sendOut(true, x.length(), data.subspanLeft(5));
        if(success == false){return false;}
        int offset = 5;
        for(int i=0; i<x.length(); i++){
            int thisLength = SGEXTN::Containers::Serialisation<T>::sizeOut(x.at(i));
            success = SGEXTN::Containers::Serialisation<int, T>::sendOut(thisLength, x.at(i), data.subspan(offset, 4 + thisLength));
            if(success == false){return false;}
            offset += (4 + thisLength);
        }
    }
    return true;
}

template <typename T> bool SGEXTN::Containers::Serialisation<SGEXTN::Containers::Array<T>>::sendIn(SGEXTN::Containers::Array<T>& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialisation<SGEXTN::Containers::Array<T>>::sizeIn(data)){return false;}
    bool success = false;
    bool variableSize = false;
    int arrayLength = 0;
    success = SGEXTN::Containers::Serialisation<bool, int>::sendIn(variableSize, arrayLength, data.subspan(0, 5));
    if(success == false || arrayLength < 0){return false;}
    if(arrayLength == 0){
        x = SGEXTN::Containers::Array<T>(0);
        return true;
    }
    if(variableSize == false){
        int elementLength = 0;
        success = SGEXTN::Containers::Serialisation<int>::sendIn(elementLength, data.subspan(5, 4));
        if(success == false || elementLength <= 0){return false;}
        x = SGEXTN::Containers::Array<T>(arrayLength);
        for(int i=0; i<arrayLength; i++){
            success = SGEXTN::Containers::Serialisation<T>::sendIn(x.at(i), data.subspan(9 + i * elementLength, elementLength));
            if(success == false){return false;}
        }
        return true;
    }
    {
        int offset = 5;
        x = SGEXTN::Containers::Array<T>(arrayLength);
        for(int i=0; i<arrayLength; i++){
            int objLength = 0;
            success = SGEXTN::Containers::Serialisation<int>::sendIn(objLength, data.subspan(offset, 4));
            if(success == false || objLength <= 0){return false;}
            success = SGEXTN::Containers::Serialisation<T>::sendIn(x.at(i), data.subspan(offset + 4, objLength));
            if(success == false){return false;}
            offset += (4 + objLength);
        }
    }
    return true;
}

template <typename T> int SGEXTN::Containers::Serialisation<SGEXTN::Containers::Array<T>>::sizeOut(const SGEXTN::Containers::Array<T>& x){
    if(x.length() == 0){return 5;}
    bool variableLength = false;
    int firstLength = SGEXTN::Containers::Serialisation<T>::sizeOut(x.at(0));
    for(int i=1; i<x.length(); i++){
        if(SGEXTN::Containers::Serialisation<T>::sizeOut(x.at(i)) != firstLength){
            variableLength = true;
            break;
        }
    }
    if(variableLength == false){return (9 + x.length() * firstLength);}
    int totalLength = 5;
    for(int i=0; i<x.length(); i++){
        totalLength += (4 + SGEXTN::Containers::Serialisation<T>::sizeOut(x.at(i)));
    }
    return totalLength;
}

template <typename T> int SGEXTN::Containers::Serialisation<SGEXTN::Containers::Array<T>>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 5){return -1;}
    bool variableSize = false;
    int arrayLength = 0;
    bool success = SGEXTN::Containers::Serialisation<bool, int>::sendIn(variableSize, arrayLength, data.subspanLeft(5));
    if(success == false || arrayLength < 0){return -1;}
    if(arrayLength == 0){return 5;}
    if(variableSize == false){
        if(data.length() < 9){return -1;}
        int elementLength = 0;
        success = SGEXTN::Containers::Serialisation<int>::sendIn(elementLength, data.subspan(5, 4));
        if(success == false || elementLength <= 0 || data.length() < 9 + arrayLength * elementLength){return -1;}
        return (9 + arrayLength * elementLength);
    }
    int offset = 5;
    for(int i=0; i<arrayLength; i++){
        if(data.length() < offset + 4){return -1;}
        int objLength = 0;
        success = SGEXTN::Containers::Serialisation<int>::sendIn(objLength, data.subspan(offset, 4));
        offset += (4 + objLength);
        if(success == false || objLength <= 0 || data.length() < offset){return -1;}
    }
    return offset;
}

template <typename T> bool SGEXTN::Containers::Serialisation<T*>::sendOut(const T* x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialisation<T*>::sizeOut(x)){return false;}
    const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
    for(int i=0; i<data.length(); i++){
        data.at(i) = (*(memoryLocation + i));
    }
    return true;
}

template <typename T> int SGEXTN::Containers::Serialisation<T*>::sizeOut(const T* x){
    return sizeof(x);
}

template <typename ReturnType, typename... ArgTypes> bool SGEXTN::Containers::Serialisation<ReturnType (*)(ArgTypes...)>::sendOut(ReturnType (*x)(ArgTypes...), SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialisation<ReturnType (*)(ArgTypes...)>::sizeOut(x)){return false;}
    const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
    for(int i=0; i<data.length(); i++){
        data.at(i) = (*(memoryLocation + i));
    }
    return true;
}

template <typename ReturnType, typename... ArgTypes> int SGEXTN::Containers::Serialisation<ReturnType (*)(ArgTypes...)>::sizeOut(ReturnType (*x)(ArgTypes...)){
    return sizeof(x);
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> bool SGEXTN::Containers::Serialisation<ReturnType (ClassName::*)(ArgTypes...)>::sendOut(ReturnType (ClassName::*x)(ArgTypes...), SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialisation<ReturnType (ClassName::*)(ArgTypes...)>::sizeOut(x)){return false;}
    const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
    for(int i=0; i<data.length(); i++){
        data.at(i) = (*(memoryLocation + i));
    }
    return true;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> int SGEXTN::Containers::Serialisation<ReturnType (ClassName::*)(ArgTypes...)>::sizeOut(ReturnType (ClassName::*x)(ArgTypes...)){
    return sizeof(x);
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> bool SGEXTN::Containers::Serialisation<ReturnType (ClassName::*)(ArgTypes...) const>::sendOut(ReturnType (ClassName::*x)(ArgTypes...) const, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialisation<ReturnType (ClassName::*)(ArgTypes...) const>::sizeOut(x)){return false;}
    const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
    for(int i=0; i<data.length(); i++){
        data.at(i) = (*(memoryLocation + i));
    }
    return true;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> int SGEXTN::Containers::Serialisation<ReturnType (ClassName::*)(ArgTypes...) const>::sizeOut(ReturnType (ClassName::*x)(ArgTypes...) const){
    return sizeof(x);
}
