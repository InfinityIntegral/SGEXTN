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

template <typename T> SGEXTN::Containers::Queue<T>::Queue() : ringBuffer_() {}

template <typename T> T& SGEXTN::Containers::Queue<T>::front(){
    if(ringBuffer_.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::front crashed because the queue is empty");}
    return ringBuffer_.front();
}

template <typename T> const T& SGEXTN::Containers::Queue<T>::front() const {
    if(ringBuffer_.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::front crashed because the queue is empty");}
    return ringBuffer_.front();
}

template <typename T> T& SGEXTN::Containers::Queue<T>::back(){
    if(ringBuffer_.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::back crashed because the queue is empty");}
    return ringBuffer_.back();
}

template <typename T> const T& SGEXTN::Containers::Queue<T>::back() const {
    if(ringBuffer_.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::back crashed because the queue is empty");}
    return ringBuffer_.back();
}

template <typename T> int SGEXTN::Containers::Queue<T>::length() const {
    return ringBuffer_.length();
}

template <typename T> void SGEXTN::Containers::Queue<T>::push(const T& x){
    ringBuffer_.pushBack(x);
}

template <typename T> void SGEXTN::Containers::Queue<T>::pop(){
    if(ringBuffer_.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue::pop crashed because the queue is empty");}
    ringBuffer_.popFront();
}

template <typename T> void SGEXTN::Containers::Queue<T>::clear(){
    ringBuffer_.clear();
}

template <typename T> void SGEXTN::Containers::Queue<T>::reserve(int newMemoryLength){
    ringBuffer_.reserve(newMemoryLength);
}
