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
#include <SGEXTN/Containers/PlacementNew.h>

template <typename T> SGEXTN::Containers::RingBufferSlot<T>::RingBufferSlot() : constructorRemover('\0') {}

template <typename T> SGEXTN::Containers::RingBufferSlot<T>::~RingBufferSlot(){}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer() : private_data(nullptr), private_start(0), private_length(0), private_memoryLength(0) {}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(int count, const T& defaultValue) : private_data(nullptr), private_start(0), private_length(count), private_memoryLength(count) {
    if(count > 0){private_data = new RingBufferSlot<T>[count];}
    for(int i=0; i<count; i++){
        new(SGEXTN::Containers::PlacementNew::placeholder, &(*(private_data + i)).object) T(defaultValue);
    }
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(const RingBuffer& x) : private_data(nullptr), private_start(0), private_length(x.length()), private_memoryLength(x.length()) {
    if(x.length() > 0){private_data = new RingBufferSlot<T>[x.length()];}
    for(int i=0; i<x.length(); i++){
        new(SGEXTN::Containers::PlacementNew::placeholder, &(*(private_data + i)).object) T(x.at(i));
    }
}

template <typename T> SGEXTN::Containers::RingBuffer<T>& SGEXTN::Containers::RingBuffer<T>::operator=(const RingBuffer& x){
    if(this == &x){return (*this);}
    for(int i=0; i<private_length; i++){
        at(i).~T();
    }
    delete[] private_data;
    private_data = new RingBufferSlot<T>[x.length()];
    private_start = 0;
    private_length = x.length();
    private_memoryLength = x.length();
    for(int i=0; i<x.length(); i++){
        new(SGEXTN::Containers::PlacementNew::placeholder, &(*(private_data + i)).object) T(x.at(i));
    }
    return (*this);
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(RingBuffer&& x) noexcept : private_data(x.private_data), private_start(x.private_start), private_length(x.private_length), private_memoryLength(x.private_memoryLength) {
    x.private_data = nullptr;
    x.private_start = 0;
    x.private_length = 0;
    x.private_memoryLength = 0;
}

template <typename T> SGEXTN::Containers::RingBuffer<T>& SGEXTN::Containers::RingBuffer<T>::operator=(RingBuffer&& x) noexcept {
    for(int i=0; i<private_length; i++){
        at(i).~T();
    }
    delete[] private_data;
    private_data = x.private_data;
    private_start = x.private_start;
    private_length = x.private_length;
    private_memoryLength = x.private_memoryLength;
    x.private_data = nullptr;
    x.private_start = 0;
    x.private_length = 0;
    x.private_memoryLength = 0;
    return (*this);
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::~RingBuffer(){
    for(int i=0; i<private_length; i++){
        at(i).~T();
    }
    delete[] private_data;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::fill(const T& defaultValue){
    for(int i=0; i<length(); i++){
        at(i) = defaultValue;
    }
}

template <typename T> int SGEXTN::Containers::RingBuffer<T>::private_getMemoryIndex(int i) const {
    if(private_start == 0){return i;}
    const int idx = i + private_start;
    if(idx < private_memoryLength){return idx;}
    return (idx - private_memoryLength);
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::at(int i){
    return (*(private_data + private_getMemoryIndex(i))).object;
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::at(int i) const {
    return (*(private_data + private_getMemoryIndex(i))).object;
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::front(){
    return at(0);
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::front() const {
    return at(0);
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::back(){
    return at(private_length - 1);
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::back() const {
    return at(private_length - 1);
}

template <typename T> int SGEXTN::Containers::RingBuffer<T>::length() const {
    return private_length;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::pushBack(const T& x){
    if(private_length == private_memoryLength){reserve(3 * private_memoryLength / 2 + 1);}
    private_length++;
    new(SGEXTN::Containers::PlacementNew::placeholder, &(*(private_data + private_getMemoryIndex(private_length - 1))).object) T(x);
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::popBack(){
    at(private_length - 1).~T();
    private_length--;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::pushFront(const T& x){
    if(private_length == private_memoryLength){reserve(3 * private_memoryLength / 2 + 1);}
    private_length++;
    private_start--;
    if(private_start < 0){private_start += private_memoryLength;}
    new(SGEXTN::Containers::PlacementNew::placeholder, &(*(private_data + private_getMemoryIndex(0))).object) T(x);
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::popFront(){
    at(0).~T();
    private_length--;
    private_start++;
    if(private_start >= private_memoryLength){private_start -= private_memoryLength;}
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::reserve(int newMemoryLength){
    if(newMemoryLength <= private_memoryLength){return;}
    RingBufferSlot<T>* newPointer = new RingBufferSlot<T>[newMemoryLength];
    for(int i=0; i<private_length; i++){
        new(SGEXTN::Containers::PlacementNew::placeholder, &(*(newPointer + i)).object) T(static_cast<T&&>(at(i)));
        at(i).~T();
    }
    delete[] private_data;
    private_data = newPointer;
    private_start = 0;
    private_memoryLength = newMemoryLength;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::clear(){
    for(int i=0; i<private_length; i++){
        at(i).~T();
    }
    private_start = 0;
    private_length = 0;
}
