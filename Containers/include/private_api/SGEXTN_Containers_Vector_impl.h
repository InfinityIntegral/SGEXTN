#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T> SGEXTN::Containers::Vector<T>::Vector() : private_ringBuffer() {}

template <typename T> SGEXTN::Containers::Vector<T>::Vector(int count) : private_ringBuffer() {
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector constructor crashed because count is negative");}
    private_ringBuffer = SGEXTN::Containers::RingBuffer<T>(count, T());
}

template <typename T> SGEXTN::Containers::Vector<T>::Vector(int count, const T& defaultValue) : private_ringBuffer() {
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
    private_ringBuffer.popBack();
}

template <typename T> void SGEXTN::Containers::Vector<T>::clear(){
    private_ringBuffer.clear();
}

template <typename T> T* SGEXTN::Containers::Vector<T>::pointerToData(int n){
    return private_ringBuffer.pointerToData(n);
}

template <typename T> const T* SGEXTN::Containers::Vector<T>::pointerToData(int n) const {
    return private_ringBuffer.pointerToData(n);
}

template <typename T> SGEXTN::Containers::Vector<T> SGEXTN::Containers::Vector<T>::convertToVectorAndDestroyArray(SGEXTN::Containers::Array<T>& arr){
    SGEXTN::Containers::Vector<T> vec;
    vec.private_ringBuffer.private_data = new SGEXTN::Containers::RingBufferSlot<T>[arr.private_length];
    for(int i=0; i<arr.private_length; i++){
        new(SGEXTN::Containers::PlacementNew::placeholder, &((*(vec.private_ringBuffer.private_data + i)).object)) T(static_cast<T&&>(arr.at(i)));
    }
    vec.private_ringBuffer.private_start = 0;
    vec.private_ringBuffer.private_length = arr.private_length;
    vec.private_ringBuffer.private_memoryLength = arr.private_length;
    delete[] arr.private_data;
    arr.private_data = nullptr;
    arr.private_length = 0;
    return vec;
}

template <typename T> SGEXTN::Containers::Array<T> SGEXTN::Containers::Vector<T>::convertToArrayAndDestroyVector(SGEXTN::Containers::Vector<T>& vec){
    SGEXTN::Containers::Array<T> arr(0);
    arr.private_data = new T[vec.private_ringBuffer.private_length];
    arr.private_length = vec.private_ringBuffer.private_length;
    for(int i=0; i<arr.private_length; i++){
        arr.at(i) = static_cast<T&&>(vec.at(i));
        vec.at(i).~T();
    }
    delete[] vec.private_ringBuffer.private_data;
    vec.private_ringBuffer.private_data = nullptr;
    vec.private_ringBuffer.private_start = 0;
    vec.private_ringBuffer.private_length = 0;
    vec.private_ringBuffer.private_memoryLength = 0;
    return arr;
}