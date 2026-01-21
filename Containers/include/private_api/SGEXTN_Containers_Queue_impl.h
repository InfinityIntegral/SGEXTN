#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T> SGEXTN::Containers::Queue<T>::Queue(){
    private_ringBuffer = SGEXTN::Containers::RingBuffer<T>();
}

template <typename T> T& SGEXTN::Containers::Queue<T>::front(){
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue::front crashed because the queue is empty");}
    return private_ringBuffer.front();
}

template <typename T> const T& SGEXTN::Containers::Queue<T>::front() const {
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue::front crashed because the queue is empty");}
    return private_ringBuffer.front();
}

template <typename T> T& SGEXTN::Containers::Queue<T>::back(){
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue::back crashed because the queue is empty");}
    return private_ringBuffer.back();
}

template <typename T> const T& SGEXTN::Containers::Queue<T>::back() const {
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue::back crashed because the queue is empty");}
    return private_ringBuffer.back();
}

template <typename T> int SGEXTN::Containers::Queue<T>::length() const {
    return private_ringBuffer.length();
}

template <typename T> void SGEXTN::Containers::Queue<T>::push(const T& x){
    private_ringBuffer.pushBack(x);
}

template <typename T> void SGEXTN::Containers::Queue<T>::pop(){
    if(private_ringBuffer.length() == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue::pop crashed because the queue is empty");}
    private_ringBuffer.popFront();
}

template <typename T> void SGEXTN::Containers::Queue<T>::reserve(int newMemoryLength){
    private_ringBuffer.reserve(newMemoryLength);
}
