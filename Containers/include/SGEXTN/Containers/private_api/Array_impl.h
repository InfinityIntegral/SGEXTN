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
#include <SGEXTN/Containers/private_api/Sort.h>
#include <SGEXTN/Containers/PlacementNew.h>

template <typename T> SGEXTN::Containers::Array<T>::Array(){
    stack.length = SGEXTN::Containers::ArrayStackStorage<T>::stackFlag;
}

template <typename T> T* SGEXTN::Containers::Array<T>::getStackSlot(int i){
    return (reinterpret_cast<T*>(stack.data) + i);
}

template <typename T> const T* SGEXTN::Containers::Array<T>::getStackSlot(int i) const {
    return (reinterpret_cast<const T*>(stack.data) + i);
}

template <typename T> SGEXTN::Containers::Array<T>::Array(int count, const T& defaultValue){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array constructor crashed because count cannot be negative");}
    if(count <= SGEXTN::Containers::ArrayStackStorage<T>::maxElements){
        stack.length = (SGEXTN::Containers::ArrayStackStorage<T>::stackFlag | static_cast<unsigned int>(count));
        for(int i=0; i<count; i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(getStackSlot(i))) T(defaultValue);
        }
    }
    else{
        heap.length = count;
        heap.data = static_cast<T*>(::operator new(count * sizeof(T)));
        for(int i=0; i<count; i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(heap.data + i)) T(defaultValue);
        }
    }
}

template <typename T> template <int N> SGEXTN::Containers::Array<T>::Array(const T(&xs)[N]){
    if(N <= SGEXTN::Containers::ArrayStackStorage<T>::maxElements){
        stack.length = (SGEXTN::Containers::ArrayStackStorage<T>::stackFlag | static_cast<unsigned int>(N));
        for(int i=0; i<N; i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(getStackSlot(i))) T(*(xs + i));
        }
    }
    else{
        heap.length = N;
        heap.data = static_cast<T*>(::operator new(N * sizeof(T)));
        for(int i=0; i<N; i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(heap.data + i)) T(*(xs + i));
        }
    }
}

template <typename T> bool SGEXTN::Containers::Array<T>::isUsingHeap() const {
    return ((stack.length & SGEXTN::Containers::ArrayStackStorage<T>::stackFlag) == 0);
}

template <typename T> SGEXTN::Containers::Array<T>::Array(const Array& x){
    if(x.isUsingHeap() == false){
        stack.length = x.stack.length;
        for(int i=0; i<x.length(); i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(getStackSlot(i))) T(x.at(i));
        }
    }
    else{
        heap.length = x.length();
        heap.data = static_cast<T*>(::operator new(heap.length * sizeof(T)));
        for(int i=0; i<x.length(); i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(heap.data + i)) T(x.at(i));
        }
    }
}

template <typename T> SGEXTN::Containers::Array<T>& SGEXTN::Containers::Array<T>::operator=(const Array& x){
    if(this == &x){return (*this);}
    for(int i=0; i<length(); i++){
        at(i).~T();
    }
    if(isUsingHeap() == true){::operator delete(static_cast<void*>(heap.data));}
    if(x.isUsingHeap() == false){
        stack.length = x.stack.length;
        for(int i=0; i<x.length(); i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(getStackSlot(i))) T(x.at(i));
        }
    }
    else{
        heap.length = x.length();
        heap.data = static_cast<T*>(::operator new(heap.length * sizeof(T)));
        for(int i=0; i<x.length(); i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(heap.data + i)) T(x.at(i));
        }
    }
    return (*this);
}

template <typename T> SGEXTN::Containers::Array<T>::Array(Array&& x) noexcept {
    if(x.isUsingHeap() == false){
        stack.length = x.stack.length;
        for(int i=0; i<x.length(); i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(getStackSlot(i))) T(static_cast<T&&>(x.at(i)));
            x.at(i).~T();
        }
    }
    else{
        heap.length = x.length();
        heap.data = x.heap.data;
    }
    x.stack.length = SGEXTN::Containers::ArrayStackStorage<T>::stackFlag;
}

template <typename T> SGEXTN::Containers::Array<T>& SGEXTN::Containers::Array<T>::operator=(Array&& x) noexcept {
    if(this == &x){return (*this);}
    for(int i=0; i<length(); i++){
        at(i).~T();
    }
    if(isUsingHeap() == true){::operator delete(static_cast<void*>(heap.data));}
    if(x.isUsingHeap() == false){
        stack.length = x.stack.length;
        for(int i=0; i<x.length(); i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(getStackSlot(i))) T(static_cast<T&&>(x.at(i)));
            x.at(i).~T();
        }
    }
    else{
        heap.length = x.length();
        heap.data = x.heap.data;
    }
    x.stack.length = SGEXTN::Containers::ArrayStackStorage<T>::stackFlag;
    return (*this);
}

template <typename T> SGEXTN::Containers::Array<T>::~Array(){
    for(int i=0; i<length(); i++){
        at(i).~T();
    }
    if(isUsingHeap() == true){::operator delete(static_cast<void*>(heap.data));}
}

template <typename T> void SGEXTN::Containers::Array<T>::fill(const T& defaultValue){
    for(int i=0; i<length(); i++){
        at(i) = defaultValue;
    }
}

template <typename T> int SGEXTN::Containers::Array<T>::length() const {
    if(isUsingHeap() == false){return static_cast<int>(stack.length & 0x7fffffff);}
    return heap.length;
}

template <typename T> T& SGEXTN::Containers::Array<T>::at(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::at crashed because index is negative");}
    if(i >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::at crashed because index points beyond the end of the array");}
    if(isUsingHeap() == false){return (*(getStackSlot(i)));}
    return (*(heap.data + i));
}

template <typename T> const T& SGEXTN::Containers::Array<T>::at(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::at crashed because index is negative");}
    if(i >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::at crashed because index points beyond the end of the array");}
    if(isUsingHeap() == false){return (*(getStackSlot(i)));}
    return (*(heap.data + i));
}

template <typename T> template <typename Comparator> void SGEXTN::Containers::Array<T>::sort(int start, int length){
    if(start < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::sort crashed because start of range is negative");}
    if(start + length > (*this).length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::sort crashed because end of range points beyond the end of the array");}
    if((*this).length() == 0){return;}
    SGEXTN::Containers::Sort<T, Comparator>::private_sort(&(*this).at(0) + start, length);
}

template <typename T> T* SGEXTN::Containers::Array<T>::getRawPointer(){
    if(length() == 0){return nullptr;}
    return &at(0);
}

template <typename T> const T* SGEXTN::Containers::Array<T>::getRawPointer() const {
    if(length() == 0){return nullptr;}
    return &at(0);
}
