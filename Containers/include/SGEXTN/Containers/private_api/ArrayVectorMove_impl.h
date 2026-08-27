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
#include <SGEXTN/Containers/private_api/RingBuffer.h>
#include <SGEXTN/Containers/Array.h>

template <typename T> SGEXTN::Containers::Vector<T> SGEXTN::Containers::ArrayVectorMove<T>::convertToVectorAndDestroyArray(SGEXTN::Containers::Array<T>& arr){
    if(arr.length() == 0){return SGEXTN::Containers::Vector<T>();}
    SGEXTN::Containers::Vector<T> vec;
    vec.private_ringBuffer.private_data = new SGEXTN::Containers::RingBufferSlot<T>[arr.length()];
    vec.private_ringBuffer.private_start = 0;
    vec.private_ringBuffer.private_length = arr.length();
    vec.private_ringBuffer.private_memoryLength = arr.length();
    for(int i=0; i<arr.length(); i++){
        new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&((*(vec.private_ringBuffer.private_data + i)).object))) T(static_cast<T&&>(arr.at(i)));
        arr.at(i).~T();
    }
    if(arr.isUsingHeap() == true){::operator delete(static_cast<void*>(arr.heap.data));}
    arr.stack.length = SGEXTN::Containers::ArrayStackStorage<T>::stackFlag;
    return vec;
}

template <typename T> SGEXTN::Containers::Array<T> SGEXTN::Containers::ArrayVectorMove<T>::convertToArrayAndDestroyVector(SGEXTN::Containers::Vector<T>& vec){
    if(vec.length() == 0){return SGEXTN::Containers::Array<T>();}
    SGEXTN::Containers::Array<T> arr;
    const int count = vec.private_ringBuffer.private_length;
    if(count <= SGEXTN::Containers::ArrayStackStorage<T>::maxElements){
        arr.stack.length = (SGEXTN::Containers::ArrayStackStorage<T>::stackFlag | static_cast<unsigned int>(count));
        for(int i=0; i<count; i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(arr.getStackSlot(i))) T(static_cast<T&&>(vec.at(i)));
        }
    }
    else{
        arr.heap.length = count;
        arr.heap.data = static_cast<T*>(::operator new(count * sizeof(T)));
        for(int i=0; i<count; i++){
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(arr.heap.data + i)) T(static_cast<T&&>(vec.at(i)));
        }
    }
    for(int i=0; i<count; i++){
        vec.at(i).~T();
    }
    delete[] vec.private_ringBuffer.private_data;
    vec.private_ringBuffer.private_data = nullptr;
    vec.private_ringBuffer.private_start = 0;
    vec.private_ringBuffer.private_length = 0;
    vec.private_ringBuffer.private_memoryLength = 0;
    return arr;
}
