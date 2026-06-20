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
#include <SGEXTN_Containers_ForceCrash.h>

template <typename T> SGEXTN::Containers::Queue<T>::Queue() : private_ringBuffer() {}

template <typename T> T& SGEXTN::Containers::Queue<T>::front(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::front crashed because the queue is empty");}
    return private_ringBuffer.front();
}

template <typename T> const T& SGEXTN::Containers::Queue<T>::front() const {
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::front crashed because the queue is empty");}
    return private_ringBuffer.front();
}

template <typename T> T& SGEXTN::Containers::Queue<T>::back(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::back crashed because the queue is empty");}
    return private_ringBuffer.back();
}

template <typename T> const T& SGEXTN::Containers::Queue<T>::back() const {
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::back crashed because the queue is empty");}
    return private_ringBuffer.back();
}

template <typename T> int SGEXTN::Containers::Queue<T>::length() const {
    return private_ringBuffer.length();
}

template <typename T> void SGEXTN::Containers::Queue<T>::push(const T& x){
    private_ringBuffer.pushBack(x);
}

template <typename T> void SGEXTN::Containers::Queue<T>::pop(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::pop crashed because the queue is empty");}
    private_ringBuffer.popFront();
}

template <typename T> void SGEXTN::Containers::Queue<T>::clear(){
    private_ringBuffer.clear();
}

template <typename T> void SGEXTN::Containers::Queue<T>::reserve(int newMemoryLength){
    private_ringBuffer.reserve(newMemoryLength);
}
