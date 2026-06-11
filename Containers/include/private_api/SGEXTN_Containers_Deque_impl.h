#pragma once
#include <SGEXTN_Containers_ForceCrash.h>

template <typename T> SGEXTN::Containers::Deque<T>::Deque() : private_ringBuffer() {}

template <typename T> void SGEXTN::Containers::Deque<T>::fill(const T& defaultValue){
    private_ringBuffer.fill(defaultValue);
}

template <typename T> T& SGEXTN::Containers::Deque<T>::at(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::at crashed because index is negative");}
    if(i >= private_ringBuffer.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::at crashed because index points beyond the end of the data structure");}
    return private_ringBuffer.at(i);
}

template <typename T> const T& SGEXTN::Containers::Deque<T>::at(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::at crashed because index is negative");}
    if(i >= private_ringBuffer.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::at crashed because index points beyond the end of the data structure");}
    return private_ringBuffer.at(i);
}

template <typename T> T& SGEXTN::Containers::Deque<T>::front(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::front crashed because the data structure is empty");}
    return private_ringBuffer.front();
}

template <typename T> const T& SGEXTN::Containers::Deque<T>::front() const {
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::front crashed because the data structure is empty");}
    return private_ringBuffer.front();
}

template <typename T> T& SGEXTN::Containers::Deque<T>::back(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::back crashed because the data structure is empty");}
    return private_ringBuffer.back();
}

template <typename T> const T& SGEXTN::Containers::Deque<T>::back() const {
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::back crashed because the data structure is empty");}
    return private_ringBuffer.back();
}

template <typename T> int SGEXTN::Containers::Deque<T>::length() const {
    return private_ringBuffer.length();
}

template <typename T> void SGEXTN::Containers::Deque<T>::pushBack(const T& x){
    private_ringBuffer.pushBack(x);
}

template <typename T> void SGEXTN::Containers::Deque<T>::popBack(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::popBack crashed because the data structure is empty");}
    private_ringBuffer.popBack();
}

template <typename T> void SGEXTN::Containers::Deque<T>::pushFront(const T& x){
    private_ringBuffer.pushFront(x);
}

template <typename T> void SGEXTN::Containers::Deque<T>::popFront(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque::popFront crashed because the data structure is empty");}
    private_ringBuffer.popFront();
}

template <typename T> void SGEXTN::Containers::Deque<T>::reserve(int newMemoryLength){
    private_ringBuffer.reserve(newMemoryLength);
}

template <typename T> void SGEXTN::Containers::Deque<T>::clear(){
    private_ringBuffer.clear();
}