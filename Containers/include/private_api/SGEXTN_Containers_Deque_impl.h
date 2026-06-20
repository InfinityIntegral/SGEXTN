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
