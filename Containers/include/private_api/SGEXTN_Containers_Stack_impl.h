#pragma once
#include <SGEXTN_Containers_ForceCrash.h>

template <typename T> SGEXTN::Containers::Stack<T>::Stack() : private_ringBuffer() {}

template <typename T> T& SGEXTN::Containers::Stack<T>::top(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack::top crashed as the stack is empty");}
    return private_ringBuffer.back();
}

template <typename T> const T& SGEXTN::Containers::Stack<T>::top() const {
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack::top crashed as the stack is empty");}
    return private_ringBuffer.back();
}

template <typename T> int SGEXTN::Containers::Stack<T>::length() const {
    return private_ringBuffer.length();
}

template <typename T> void SGEXTN::Containers::Stack<T>::push(const T& x){
    private_ringBuffer.pushBack(x);
}

template <typename T> void SGEXTN::Containers::Stack<T>::pop(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack::pop crashed as the stack is empty");}
    private_ringBuffer.popBack();
}

template <typename T> void SGEXTN::Containers::Stack<T>::clear(){
    private_ringBuffer.clear();
}

template <typename T> void SGEXTN::Containers::Stack<T>::reserve(int newMemoryLength){
    private_ringBuffer.reserve(newMemoryLength);
}
