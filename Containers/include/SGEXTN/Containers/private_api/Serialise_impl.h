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
#include <SGEXTN/Containers/private_api/TypeTraits.h>

template <typename... Ts> bool SGEXTN::Containers::Serialise<Ts...>::sendOut(const Ts&... xs, SGEXTN::Containers::Span<unsigned char> data){
    const int requiredLength = SGEXTN::Containers::Serialise<Ts...>::sizeOut(xs...);
    if(data.length() != requiredLength){return false;}
    int offset = 0;
    int nextLength = 0;
    bool isValid = true;
    bool nextValid = true;
    const bool finalResult = ((nextLength = SGEXTN::Containers::Serialise<Ts>::sizeOut(xs), nextValid = SGEXTN::Containers::Serialise<Ts>::sendOut(xs, data.subspan(offset, nextLength)), isValid = (isValid && nextValid), offset += nextLength, isValid == true) && ...);
    return finalResult;
}

template <typename... Ts> bool SGEXTN::Containers::Serialise<Ts...>::sendIn(Ts&... xs, SGEXTN::Containers::Span<unsigned char> data){
    const int requiredLength = SGEXTN::Containers::Serialise<Ts...>::sizeIn(data);
    if(data.length() != requiredLength){return false;}
    int offset = 0;
    int nextLength = 0;
    bool nextValid = false;
    bool isValid = true;
    const bool finalResult = ((nextLength = SGEXTN::Containers::Serialise<Ts>::sizeIn(data.subspanRight(data.length() - offset)), nextValid = SGEXTN::Containers::Serialise<Ts>::sendIn(xs, data.subspan(offset, nextLength)), offset += nextLength, isValid = (isValid && nextValid), isValid == true) && ...);
    return finalResult;
}

template <typename... Ts> int SGEXTN::Containers::Serialise<Ts...>::sizeOut(const Ts&... xs){
    return (0 + ... + SGEXTN::Containers::Serialise<Ts>::sizeOut(xs));
}

template <typename... Ts> int SGEXTN::Containers::Serialise<Ts...>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    int nextLength = 0;
    int offset = 0;
    bool isOk = true;
    const bool finalResult = ((nextLength = SGEXTN::Containers::Serialise<Ts>::sizeIn(data.subspanRight(data.length() - offset)), isOk = isOk && (nextLength != -1), offset += nextLength, isOk = isOk && (data.length() >= offset), isOk == true) && ...);
    if(finalResult == true){return offset;}
    return -1;
}

template <typename T> bool SGEXTN::Containers::Serialise<T>::sendOut(const T& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialise<T>::sizeOut(x)){return false;}
    if constexpr (requires{SGEXTN::Containers::IsPointer<T>::isPointer;} == true){
        const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
        for(int i=0; i<data.length(); i++){
            data.at(i) = (*(memoryLocation + i));
        }
        return true;
    }
    if constexpr (requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = x;} == false && requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = static_cast<unsigned char>(x);} == true && requires{SGEXTN::Containers::IsTrue<bool, sizeof(T) == 1>::isTrue;} == true){return SGEXTN::Containers::Serialise<unsigned char>::sendOut(static_cast<unsigned char>(x), data);}
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::sendOut(x, data)), bool>::same;} == true){return T::sendOut(x, data);}
    SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise::sendOut requires custom type T to have bool T::sendOut(const T& x, SGEXTN::Containers::Span<unsigned char>& data); properly defined to work");
}

template <typename T> bool SGEXTN::Containers::Serialise<T>::sendIn(T& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialise<T>::sizeIn(data)){return false;}
    if constexpr (requires{SGEXTN::Containers::IsPointer<T>::isPointer;} == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise::sendIn forbids use with pointers because the addresses of pointers always change between runs");}
    if constexpr (requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = x;} == false && requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = static_cast<unsigned char>(x);} == true && requires{SGEXTN::Containers::IsTrue<bool, sizeof(T) == 1>::isTrue;} == true){
        unsigned char c = static_cast<unsigned char>(0);
        const bool isValid = SGEXTN::Containers::Serialise<unsigned char>::sendIn(c, data);
        x = static_cast<T>(c);
        return isValid;
    }
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::sendIn(x, data)), bool>::same;} == true){return T::sendIn(x, data);}
    SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise::sendIn requires custom type T to have bool T::sendIn(T& x, SGEXTN::Containers::Span<unsigned char> data); properly defined to work");
}

template <typename T> int SGEXTN::Containers::Serialise<T>::sizeOut(const T& x){
    if constexpr (requires{SGEXTN::Containers::IsPointer<T>::isPointer;} == true){return sizeof(x);}
    if constexpr (requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = x;} == false && requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = static_cast<unsigned char>(x);} == true && requires{SGEXTN::Containers::IsTrue<bool, sizeof(T) == 1>::isTrue;} == true){return 1;}
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::size()), int>::same;} == true){return T::size();}
    if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::sizeOut(x)), int>::same;} == true){return T::sizeOut(x);}
    SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise::sizeOut requires custom type T to have int T::sizeOut(const T& x); properly defined if T has variable size or int T::size(); properly defined if T has constant size to work");
}

template <typename T> int SGEXTN::Containers::Serialise<T>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    int requiredLength = 0;
    if constexpr (requires{SGEXTN::Containers::IsPointer<T>::isPointer;} == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise::sizeIn forbids use with pointers because the addresses of pointers always change between runs");}
    else if constexpr (requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = SGEXTN::Containers::CreateInstance<T>::getInstance();} == false && requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = static_cast<unsigned char>(SGEXTN::Containers::CreateInstance<T>::getInstance());} == true && requires{SGEXTN::Containers::IsTrue<bool, sizeof(T) == 1>::isTrue;} == true){requiredLength = 1;}
    else if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::size()), int>::same;} == true){requiredLength = T::size();}
    else if constexpr (requires{SGEXTN::Containers::IsSameType<decltype(T::sizeIn(data)), int>::same;} == true){requiredLength = T::sizeIn(data);}
    else{SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise::sizeIn requires custom type T to have int T::sizeIn(SGEXTN::Containers::Span<unsigned char> data); properly defined if T has variable size or int T::size(); properly defined if T has constant size to work");}
    if(requiredLength > data.length()){return -1;}
    return requiredLength;
}

template <typename T> bool SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::sendOut(const SGEXTN::Containers::Array<T>& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::sizeOut(x)){return false;}
    if(x.length() == 0){return SGEXTN::Containers::Serialise<bool, int>::sendOut(false, 0, data);}
    bool lengthVaries = false;
    const int firstLength = SGEXTN::Containers::Serialise<T>::sizeOut(x.at(0));
    for(int i=1; i<x.length(); i++){
        if(SGEXTN::Containers::Serialise<T>::sizeOut(x.at(i)) != firstLength){
            lengthVaries = true;
            break;
        }
    }
    if(lengthVaries == false){
        bool success = SGEXTN::Containers::Serialise<bool, int, int>::sendOut(false, x.length(), firstLength, data.subspanLeft(9));
        if(success == false){return false;}
        for(int i=0; i<x.length(); i++){
            success = SGEXTN::Containers::Serialise<T>::sendOut(x.at(i), data.subspan(9 + i * firstLength, firstLength));
            if(success == false){return false;}
        }
        return true;
    }
    {
        const int totalLength = 5;
        bool success = SGEXTN::Containers::Serialise<bool, int>::sendOut(true, x.length(), data.subspanLeft(5));
        if(success == false){return false;}
        int offset = 5;
        for(int i=0; i<x.length(); i++){
            const int thisLength = SGEXTN::Containers::Serialise<T>::sizeOut(x.at(i));
            success = SGEXTN::Containers::Serialise<int, T>::sendOut(thisLength, x.at(i), data.subspan(offset, 4 + thisLength));
            if(success == false){return false;}
            offset += (4 + thisLength);
        }
    }
    return true;
}

template <typename T> bool SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::sendIn(SGEXTN::Containers::Array<T>& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::sizeIn(data)){return false;}
    bool success = false;
    bool variableSize = false;
    int arrayLength = 0;
    success = SGEXTN::Containers::Serialise<bool, int>::sendIn(variableSize, arrayLength, data.subspan(0, 5));
    if(success == false || arrayLength < 0){return false;}
    if(arrayLength == 0){
        x = SGEXTN::Containers::Array<T>(0);
        return true;
    }
    if(variableSize == false){
        int elementLength = 0;
        success = SGEXTN::Containers::Serialise<int>::sendIn(elementLength, data.subspan(5, 4));
        if(success == false || elementLength <= 0){return false;}
        x = SGEXTN::Containers::Array<T>(arrayLength);
        for(int i=0; i<arrayLength; i++){
            success = SGEXTN::Containers::Serialise<T>::sendIn(x.at(i), data.subspan(9 + i * elementLength, elementLength));
            if(success == false){return false;}
        }
        return true;
    }
    {
        int offset = 5;
        x = SGEXTN::Containers::Array<T>(arrayLength);
        for(int i=0; i<arrayLength; i++){
            int objLength = 0;
            success = SGEXTN::Containers::Serialise<int>::sendIn(objLength, data.subspan(offset, 4));
            if(success == false || objLength <= 0){return false;}
            success = SGEXTN::Containers::Serialise<T>::sendIn(x.at(i), data.subspan(offset + 4, objLength));
            if(success == false){return false;}
            offset += (4 + objLength);
        }
    }
    return true;
}

template <typename T> int SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::sizeOut(const SGEXTN::Containers::Array<T>& x){
    if(x.length() == 0){return 5;}
    bool variableLength = false;
    const int firstLength = SGEXTN::Containers::Serialise<T>::sizeOut(x.at(0));
    for(int i=1; i<x.length(); i++){
        if(SGEXTN::Containers::Serialise<T>::sizeOut(x.at(i)) != firstLength){
            variableLength = true;
            break;
        }
    }
    if(variableLength == false){return (9 + x.length() * firstLength);}
    int totalLength = 5;
    for(int i=0; i<x.length(); i++){
        totalLength += (4 + SGEXTN::Containers::Serialise<T>::sizeOut(x.at(i)));
    }
    return totalLength;
}

template <typename T> int SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 5){return -1;}
    bool variableSize = false;
    int arrayLength = 0;
    bool success = SGEXTN::Containers::Serialise<bool, int>::sendIn(variableSize, arrayLength, data.subspanLeft(5));
    if(success == false || arrayLength < 0){return -1;}
    if(arrayLength == 0){return 5;}
    if(variableSize == false){
        if(data.length() < 9){return -1;}
        int elementLength = 0;
        success = SGEXTN::Containers::Serialise<int>::sendIn(elementLength, data.subspan(5, 4));
        if(success == false || elementLength <= 0 || data.length() < 9 + arrayLength * elementLength){return -1;}
        return (9 + arrayLength * elementLength);
    }
    int offset = 5;
    for(int i=0; i<arrayLength; i++){
        if(data.length() < offset + 4){return -1;}
        int objLength = 0;
        success = SGEXTN::Containers::Serialise<int>::sendIn(objLength, data.subspan(offset, 4));
        offset += (4 + objLength);
        if(success == false || objLength <= 0 || data.length() < offset){return -1;}
    }
    return offset;
}
