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

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer() : data_(nullptr), start_(0), length_(0), memoryLength_(0) {}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(int count, const T& defaultValue) : data_(nullptr), start_(0), length_(count), memoryLength_(count) {
    if(count > 0){data_ = new RingBufferSlot<T>[count];}
    for(int i=0; i<count; i++){
        new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&(*(data_ + i)).object)) T(defaultValue);
    }
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(const RingBuffer& x) : data_(nullptr), start_(0), length_(x.length()), memoryLength_(x.length()) {
    if(x.length() > 0){data_ = new RingBufferSlot<T>[x.length()];}
    for(int i=0; i<x.length(); i++){
        new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&(*(data_ + i)).object)) T(x.at(i));
    }
}

template <typename T> SGEXTN::Containers::RingBuffer<T>& SGEXTN::Containers::RingBuffer<T>::operator=(const RingBuffer& x){
    if(this == &x){return (*this);}
    for(int i=0; i<length_; i++){
        at(i).~T();
    }
    delete[] data_;
    data_ = new RingBufferSlot<T>[x.length()];
    start_ = 0;
    length_ = x.length();
    memoryLength_ = x.length();
    for(int i=0; i<x.length(); i++){
        new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&(*(data_ + i)).object)) T(x.at(i));
    }
    return (*this);
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(RingBuffer&& x) noexcept : data_(x.data_), start_(x.start_), length_(x.length_), memoryLength_(x.memoryLength_) {
    x.data_ = nullptr;
    x.start_ = 0;
    x.length_ = 0;
    x.memoryLength_ = 0;
}

template <typename T> SGEXTN::Containers::RingBuffer<T>& SGEXTN::Containers::RingBuffer<T>::operator=(RingBuffer&& x) noexcept {
    if(this == &x){return (*this);}
    for(int i=0; i<length_; i++){
        at(i).~T();
    }
    delete[] data_;
    data_ = x.data_;
    start_ = x.start_;
    length_ = x.length_;
    memoryLength_ = x.memoryLength_;
    x.data_ = nullptr;
    x.start_ = 0;
    x.length_ = 0;
    x.memoryLength_ = 0;
    return (*this);
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::~RingBuffer(){
    for(int i=0; i<length_; i++){
        at(i).~T();
    }
    delete[] data_;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::fill(const T& defaultValue){
    for(int i=0; i<length(); i++){
        at(i) = defaultValue;
    }
}

template <typename T> int SGEXTN::Containers::RingBuffer<T>::getMemoryIndex(int i) const {
    if(start_ == 0){return i;}
    const int idx = i + start_;
    if(idx < memoryLength_){return idx;}
    return (idx - memoryLength_);
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::at(int i){
    return (*(data_ + getMemoryIndex(i))).object;
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::at(int i) const {
    return (*(data_ + getMemoryIndex(i))).object;
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::front(){
    return at(0);
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::front() const {
    return at(0);
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::back(){
    return at(length_ - 1);
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::back() const {
    return at(length_ - 1);
}

template <typename T> int SGEXTN::Containers::RingBuffer<T>::length() const {
    return length_;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::pushBack(const T& x){
    if(length_ == memoryLength_){reserve(3 * memoryLength_ / 2 + 1);}
    length_++;
    new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&(*(data_ + getMemoryIndex(length_ - 1))).object)) T(x);
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::popBack(){
    at(length_ - 1).~T();
    length_--;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::pushFront(const T& x){
    if(length_ == memoryLength_){reserve(3 * memoryLength_ / 2 + 1);}
    length_++;
    start_--;
    if(start_ < 0){start_ += memoryLength_;}
    new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&(*(data_ + getMemoryIndex(0))).object)) T(x);
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::popFront(){
    at(0).~T();
    length_--;
    start_++;
    if(start_ >= memoryLength_){start_ -= memoryLength_;}
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLength_){return;}
    RingBufferSlot<T>* newPointer = new RingBufferSlot<T>[newMemoryLength];
    for(int i=0; i<length_; i++){
        new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&(*(newPointer + i)).object)) T(static_cast<T&&>(at(i)));
        at(i).~T();
    }
    delete[] data_;
    data_ = newPointer;
    start_ = 0;
    memoryLength_ = newMemoryLength;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::clear(){
    for(int i=0; i<length_; i++){
        at(i).~T();
    }
    start_ = 0;
    length_ = 0;
}
