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

template <typename T> SGEXTN::Containers::Vector<T>::Vector() : private_ringBuffer() {}

template <typename T> SGEXTN::Containers::Vector<T>::Vector(int count, const T& defaultValue) : private_ringBuffer() {
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector constructor crashed because count is negative");}
    private_ringBuffer = SGEXTN::Containers::RingBuffer<T>(count, defaultValue);
}

template <typename T> T& SGEXTN::Containers::Vector<T>::at(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::at crashed because the index is negative");}
    if(i >= private_ringBuffer.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::at crashed because the index points beyond the end of the vector");}
    return private_ringBuffer.at(i);
}

template <typename T> const T& SGEXTN::Containers::Vector<T>::at(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::at crashed because the index is negative");}
    if(i >= private_ringBuffer.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::at crashed because the index points beyond the end of the vector");}
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
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::popBack crashed because the vector is empty");}
    private_ringBuffer.popBack();
}

template <typename T> void SGEXTN::Containers::Vector<T>::clear(){
    private_ringBuffer.clear();
}
