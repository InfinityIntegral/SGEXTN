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
#include <SGEXTN/Containers/ForceCrash.h>

template <typename T> SGEXTN::Containers::Vector<T>::Vector() : ringBuffer_() {}

template <typename T> SGEXTN::Containers::Vector<T>::Vector(int count, const T& defaultValue) : ringBuffer_() {
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector constructor crashed because count is negative");}
    ringBuffer_ = SGEXTN::Containers::RingBuffer<T>(count, defaultValue);
}

template <typename T> T& SGEXTN::Containers::Vector<T>::at(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::at crashed because the index is negative");}
    if(i >= ringBuffer_.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::at crashed because the index points beyond the end of the vector");}
    return ringBuffer_.at(i);
}

template <typename T> const T& SGEXTN::Containers::Vector<T>::at(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::at crashed because the index is negative");}
    if(i >= ringBuffer_.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::at crashed because the index points beyond the end of the vector");}
    return ringBuffer_.at(i);
}

template <typename T> int SGEXTN::Containers::Vector<T>::length() const {
    return ringBuffer_.length();
}

template <typename T> void SGEXTN::Containers::Vector<T>::fill(const T& defaultValue){
    ringBuffer_.fill(defaultValue);
}

template <typename T> void SGEXTN::Containers::Vector<T>::reserve(int newMemoryLength){
    ringBuffer_.reserve(newMemoryLength);
}

template <typename T> void SGEXTN::Containers::Vector<T>::pushBack(const T& x){
    ringBuffer_.pushBack(x);
}

template <typename T> void SGEXTN::Containers::Vector<T>::popBack(){
    if(ringBuffer_.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector::popBack crashed because the vector is empty");}
    ringBuffer_.popBack();
}

template <typename T> void SGEXTN::Containers::Vector<T>::clear(){
    ringBuffer_.clear();
}
