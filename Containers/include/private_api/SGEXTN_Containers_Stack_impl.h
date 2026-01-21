#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T> SGEXTN::Containers::Stack<T>::Stack(){
    private_ringBuffer = SGEXTN::Containers::RingBuffer<T>();
}

template <typename T> T& SGEXTN::Containers::Stack<T>::top(){
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Stack::top crashed as the stack is empty");}
    return private_ringBuffer.back();
}

template <typename T> const T& SGEXTN::Containers::Stack<T>::top() const {
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Stack::top crashed as the stack is empty");}
    return private_ringBuffer.back();
}

template <typename T> int SGEXTN::Containers::Stack<T>::length() const {
    return private_ringBuffer.length();
}

template <typename T> void SGEXTN::Containers::Stack<T>::push(const T& x){
    private_ringBuffer.pushBack(x);
}

template <typename T> void SGEXTN::Containers::Stack<T>::pop(){
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Stack::pop crashed as the stack is empty");}
    private_ringBuffer.popBack();
}

template <typename T> void SGEXTN::Containers::Stack<T>::reserve(int newMemoryLength){
    private_ringBuffer.reserve(newMemoryLength);
}
