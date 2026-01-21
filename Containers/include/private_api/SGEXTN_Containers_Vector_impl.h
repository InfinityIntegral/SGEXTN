#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T> SGEXTN::Containers::Vector<T>::Vector(){
    private_ringBuffer = SGEXTN::Containers::RingBuffer<T>();
}

template <typename T> SGEXTN::Containers::Vector<T>::Vector(int count){
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector constructor crashed because count is negative");}
    private_ringBuffer = SGEXTN::Containers::RingBuffer<T>(count);
}

template <typename T> SGEXTN::Containers::Vector<T>::Vector(int count, const T& defaultValue){
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector constructor crashed because count is negative");}
    private_ringBuffer = SGEXTN::Containers::RingBuffer<T>(count, defaultValue);
}

template <typename T> T& SGEXTN::Containers::Vector<T>::at(int i){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector::at crashed because the index is negative");}
    if(i >= private_ringBuffer.length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector::at crashed because the index points beyond the end of the vector");}
    return private_ringBuffer.at(i);
}

template <typename T> const T& SGEXTN::Containers::Vector<T>::at(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector::at crashed because the index is negative");}
    if(i >= private_ringBuffer.length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector::at crashed because the index points beyond the end of the vector");}
    return private_ringBuffer.at(i);
}

template <typename T> int SGEXTN::Containers::Vector<T>::length() const {
    return private_ringBuffer.length();
}

template <typename T> void SGEXTN::Containers::Vector<T>::fill(const T& defaultValue){
    private_ringBuffer.fill(defaultValue);
}

template <typename T> void SGEXTN::Containers::Vector<T>::reserve(int newMemoryLength){
    private_ringBuffer.reserve(newMemoryLength);
}

template <typename T> void SGEXTN::Containers::Vector<T>::pushBack(const T& x){
    private_ringBuffer.pushBack(x);
}

template <typename T> void SGEXTN::Containers::Vector<T>::popBack(){
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector::popBack crashed because the vector is empty");}
    private_ringBuffer.private_length--;
}

template <typename T> T* SGEXTN::Containers::Vector<T>::pointerToData(int n){
    return private_ringBuffer.pointerToData(n);
}

template <typename T> const T* SGEXTN::Containers::Vector<T>::pointerToData(int n) const {
    return private_ringBuffer.pointerToData(n);
}
