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

template <typename... Ts> SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<Ts...>::serialiseTogether(Ts... xs){
    SGEXTN::Containers::Array<unsigned char> outputArray((0 + ... + SGEXTN::Containers::Serialise<Ts>::lengthof(xs)));
    int offset = 0;
    (SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<Ts>::serialise(xs)), ...);
    return outputArray;
}

template <typename T> SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<T>::serialise(const T& x){
    return T::serialise(x);
}

template <typename T> T SGEXTN::Containers::Serialise<T>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    bool isSuccessful = false;
    T output = T::unserialise(data, isSuccessful);
    if(success != nullptr){(*success) = isSuccessful;}
    return output;
}

template <typename T> int SGEXTN::Containers::Serialise<T>::lengthof(const T& x){
    return T::lengthof(x);
}

template <typename T> SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::serialise(const SGEXTN::Containers::Array<T>& x){
    if(x.length() == 0){
        SGEXTN::Containers::Array<unsigned char> output(9);
        int offset = 0;
        SGEXTN::Containers::MemoryCopySerialise::copySection(output, offset, SGEXTN::Containers::Serialise<int>::serialise(9));
        SGEXTN::Containers::MemoryCopySerialise::copySection(output, offset, SGEXTN::Containers::Serialise<bool>::serialise(false));
        SGEXTN::Containers::MemoryCopySerialise::copySection(output, offset, SGEXTN::Containers::Serialise<int>::serialise(0));
        return output;
    }
    bool lengthVaries = false;
    int firstLength = SGEXTN::Containers::Serialise<T>::lengthof(x.at(0));
    for(int i=1; i<x.length(); i++){
        if(SGEXTN::Containers::Serialise<T>::lengthof(x.at(i)) != firstLength){
            lengthVaries = true;
            break;
        }
    }
    if(lengthVaries == false){
        SGEXTN::Containers::Array<unsigned char> outputArray(13 + x.length() * firstLength);
        int offset = 0;
        SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<int>::serialise(13 + x.length() * firstLength));
        SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<bool>::serialise(false));
        SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<int>::serialise(x.length()));
        SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<int>::serialise(firstLength));
        for(int i=0; i<x.length(); i++){
            SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<T>::serialise(x.at(i)));
        }
        return outputArray;
    }
    {
        int totalLength = 9;
        for(int i=0; i<x.length(); i++){
            totalLength += (4 + SGEXTN::Containers::Serialise<T>::lengthof(x.at(i)));
        }
        SGEXTN::Containers::Array<unsigned char> outputArray(totalLength);
        int offset = 0;
        SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<int>::serialise(totalLength));
        SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<bool>::serialise(true));
        SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<int>::serialise(x.length()));
        for(int i=0; i<x.length(); i++){
            SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<int>::serialise(SGEXTN::Containers::Serialise<T>::lengthof(x.at(i))));
            SGEXTN::Containers::MemoryCopySerialise::copySection(outputArray, offset, SGEXTN::Containers::Serialise<T>::serialise(x.at(i)));
        }
        return outputArray;
    }
}

template <typename T> SGEXTN::Containers::Array<T> SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    bool isSuccessful = false;
    if(data.length() < 9){
        if(success != nullptr){(*success) = false;}
        return SGEXTN::Containers::Array<T>(0);
    }
    int offset = 0;
    SGEXTN::Containers::Array<unsigned char> tempArray(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const int reportedDataSize = SGEXTN::Containers::Serialise<int>::unserialise(tempArray, &isSuccessful);
    if(isSuccessful == false || reportedDataSize != data.length()){
        if(success != nullptr){(*success) = false;}
        return SGEXTN::Containers::Array<T>(0);
    }
    tempArray = SGEXTN::Containers::Array<unsigned char>(1);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const bool isVariableSized = SGEXTN::Containers::Serialise<bool>::unserialise(tempArray, &isSuccessful);
    if(isSuccessful == false){
        if(success != nullptr){(*success) = false;}
        return SGEXTN::Containers::Array<T>(0);
    }
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    int arrayLength = SGEXTN::Containers::Serialise<int>::unserialise(tempArray, &isSuccessful);
    if(isSuccessful == false || arrayLength < 0){
        if(success != nullptr){(*success) = false;}
        return SGEXTN::Containers::Array<T>(0);
    }
    SGEXTN::Containers::Array<T> output(arrayLength);
    if(arrayLength == 0){
        if(data.length() != 9){
            if(success != nullptr){(*success) = false;}
        }
        else{
            if(success != nullptr){(*success) = true;}
        }
        return SGEXTN::Containers::Array<T>(0);
    }
    if(isVariableSized == false){
        if(data.length() < 13){
            if(success != nullptr){(*success) = false;}
            return SGEXTN::Containers::Array<T>(0);
        }
        SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
        const int elementLength = SGEXTN::Containers::Serialise<int>::unserialise(tempArray, &isSuccessful);
        if(isSuccessful == false || elementLength <= 0 || data.length() != 13 + arrayLength * elementLength){
            if(success != nullptr){(*success) = false;}
            return SGEXTN::Containers::Array<T>(0);
        }
        tempArray = SGEXTN::Containers::Array<unsigned char>(elementLength);
        for(int i=0; i<arrayLength; i++){
            SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
            T obj = SGEXTN::Containers::Serialise<T>::unserialise(tempArray, &isSuccessful);
            if(isSuccessful == false){
                if(success != nullptr){(*success) = false;}
                return SGEXTN::Containers::Array<T>(0);
            }
            output.at(i) = obj;
        }
        if(success != nullptr){(*success) = true;}
        return output;
    }
    SGEXTN::Containers::Array<unsigned char> objArray(0);
    for(int i=0; i<arrayLength; i++){
        if(data.length() - offset < 4){
            if(success != nullptr){(*success) = false;}
            return SGEXTN::Containers::Array<T>(0);
        }
        SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
        const int objLength = SGEXTN::Containers::Serialise<int>::unserialise(tempArray, &isSuccessful);
        if(isSuccessful == false || objLength <= 0){
            if(success != nullptr){(*success) = false;}
            return SGEXTN::Containers::Array<T>(0);
        }
        objArray = SGEXTN::Containers::Array<unsigned char>(objLength);
        if(data.length() - offset < objLength){
            if(success != nullptr){(*success) = false;}
            return SGEXTN::Containers::Array<T>(0);
        }
        SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, objArray);
        T obj = SGEXTN::Containers::Serialise<T>::unserialise(objArray, &isSuccessful);
        if(isSuccessful == false){
            if(success != nullptr){(*success) = false;}
            return SGEXTN::Containers::Array<T>(0);
        }
        output.at(i) = obj;
    }
    if(offset != data.length()){
        if(success != nullptr){(*success) = false;}
        return SGEXTN::Containers::Array<T>(0);
    }
    if(success != nullptr){(*success) = true;}
    return output;
}

template <typename T> int SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<T>>::lengthof(const SGEXTN::Containers::Array<T>& x){
    if(x.length() == 0){return 9;}
    bool lengthVaries = false;
    int firstLength = SGEXTN::Containers::Serialise<T>::lengthof(x.at(0));
    for(int i=1; i<x.length(); i++){
        if(SGEXTN::Containers::Serialise<T>::lengthof(x.at(i)) != firstLength){
            lengthVaries = true;
            break;
        }
    }
    if(lengthVaries == false){return (13 + x.length() * firstLength);}
    int totalLength = 9;
    for(int i=0; i<x.length(); i++){
        totalLength += (4 + SGEXTN::Containers::Serialise<T>::lengthof(x.at(i)));
    }
    return totalLength;
}

template <typename T> SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<T*>::serialise(const T* x){
    SGEXTN::Containers::Array<unsigned char> outputArray(SGEXTN::Containers::Serialise<T*>::lengthof(x));
    const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
    for(int i=0; i<outputArray.length(); i++){
        outputArray.at(i) = (*(memoryLocation + i));
    }
    return outputArray;
}

template <typename T> int SGEXTN::Containers::Serialise<T*>::lengthof(const T* x){
    return sizeof(x);
}

template <typename ReturnType, typename... ArgTypes> SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<ReturnType (*)(ArgTypes...)>::serialise(ReturnType (*x)(ArgTypes...)){
    SGEXTN::Containers::Array<unsigned char> outputArray(SGEXTN::Containers::Serialise<ReturnType (*)(ArgTypes...)>::lengthof(x));
    const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
    for(int i=0; i<outputArray.length(); i++){
        outputArray.at(i) = (*(memoryLocation + i));
    }
    return outputArray;
}

template <typename ReturnType, typename... ArgTypes> int SGEXTN::Containers::Serialise<ReturnType (*)(ArgTypes...)>::lengthof(ReturnType (*x)(ArgTypes...)){
    return sizeof(x);
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<ReturnType (ClassName::*)(ArgTypes...)>::serialise(ReturnType (ClassName::*x)(ArgTypes...)){
    SGEXTN::Containers::Array<unsigned char> outputArray(SGEXTN::Containers::Serialise<ReturnType (ClassName::*)(ArgTypes...)>::lengthof(x));
    const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
    for(int i=0; i<outputArray.length(); i++){
        outputArray.at(i) = (*(memoryLocation + i));
    }
    return outputArray;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> int SGEXTN::Containers::Serialise<ReturnType (ClassName::*)(ArgTypes...)>::lengthof(ReturnType (ClassName::*x)(ArgTypes...)){
    return sizeof(x);
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<ReturnType (ClassName::*)(ArgTypes...) const>::serialise(ReturnType (ClassName::*x)(ArgTypes...) const){
    SGEXTN::Containers::Array<unsigned char> outputArray(SGEXTN::Containers::Serialise<ReturnType (ClassName::*)(ArgTypes...) const>::lengthof(x));
    const unsigned char* memoryLocation = reinterpret_cast<const unsigned char*>(&x);
    for(int i=0; i<outputArray.length(); i++){
        outputArray.at(i) = (*(memoryLocation + i));
    }
    return outputArray;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> int SGEXTN::Containers::Serialise<ReturnType (ClassName::*)(ArgTypes...) const>::lengthof(ReturnType (ClassName::*x)(ArgTypes...) const){
    return sizeof(x);
}
