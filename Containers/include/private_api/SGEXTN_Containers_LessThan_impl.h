#pragma once
#include <SGEXTN_Containers_Span.h>

template <typename T> bool SGEXTN::Containers::LessThan<T>::operator()(const T& a, const T& b) const {
    return (a < b);
}

template <typename T> bool SGEXTN::Containers::LessThan<T*>::operator()(const T* a, const T* b) const {
    int typeMemoryLength = sizeof(T*);
    SGEXTN::Containers::Span<const unsigned char> aSpan(reinterpret_cast<const unsigned char*>(&a), typeMemoryLength);
    SGEXTN::Containers::Span<const unsigned char> bSpan(reinterpret_cast<const unsigned char*>(&b), typeMemoryLength);
    for(int i=0; i<typeMemoryLength; i++){
        if(aSpan.at(i) < bSpan.at(i)){return true;}
        if(bSpan.at(i) < aSpan.at(i)){return false;}
    }
    return false;
}

template <typename ReturnType, typename... ArgTypes> bool SGEXTN::Containers::LessThan<ReturnType (*)(ArgTypes...)>::operator()(ReturnType (*a)(ArgTypes...), ReturnType (*b)(ArgTypes...)) const {
    int typeMemoryLength = sizeof(ReturnType (*)(ArgTypes...));
    SGEXTN::Containers::Span<const unsigned char> aSpan(reinterpret_cast<const unsigned char*>(&a), typeMemoryLength);
    SGEXTN::Containers::Span<const unsigned char> bSpan(reinterpret_cast<const unsigned char*>(&b), typeMemoryLength);
    for(int i=0; i<typeMemoryLength; i++){
        if(aSpan.at(i) < bSpan.at(i)){return true;}
        if(bSpan.at(i) < aSpan.at(i)){return false;}
    }
    return false;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> bool SGEXTN::Containers::LessThan<ReturnType (ClassName::*)(ArgTypes...)>::operator()(ReturnType (ClassName::*a)(ArgTypes...), ReturnType (ClassName::*b)(ArgTypes...)) const {
    int typeMemoryLength = sizeof(ReturnType (ClassName::*)(ArgTypes...));
    SGEXTN::Containers::Span<const unsigned char> aSpan(reinterpret_cast<const unsigned char*>(&a), typeMemoryLength);
    SGEXTN::Containers::Span<const unsigned char> bSpan(reinterpret_cast<const unsigned char*>(&b), typeMemoryLength);
    for(int i=0; i<typeMemoryLength; i++){
        if(aSpan.at(i) < bSpan.at(i)){return true;}
        if(bSpan.at(i) < aSpan.at(i)){return false;}
    }
    return false;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> bool SGEXTN::Containers::LessThan<ReturnType (ClassName::*)(ArgTypes...) const>::operator()(ReturnType (ClassName::*a)(ArgTypes...) const, ReturnType (ClassName::*b)(ArgTypes...) const) const {
    int typeMemoryLength = sizeof(ReturnType (ClassName::*)(ArgTypes...) const);
    SGEXTN::Containers::Span<const unsigned char> aSpan(reinterpret_cast<const unsigned char*>(&a), typeMemoryLength);
    SGEXTN::Containers::Span<const unsigned char> bSpan(reinterpret_cast<const unsigned char*>(&b), typeMemoryLength);
    for(int i=0; i<typeMemoryLength; i++){
        if(aSpan.at(i) < bSpan.at(i)){return true;}
        if(bSpan.at(i) < aSpan.at(i)){return false;}
    }
    return false;
}