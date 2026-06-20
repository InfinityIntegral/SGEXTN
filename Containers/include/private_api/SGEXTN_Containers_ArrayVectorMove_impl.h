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

template <typename T> SGEXTN::Containers::Vector<T> SGEXTN::Containers::ArrayVectorMove<T>::convertToVectorAndDestroyArray(SGEXTN::Containers::Array<T>& arr){
    SGEXTN::Containers::Vector<T> vec;
    vec.private_ringBuffer.private_data = new SGEXTN::Containers::RingBufferSlot<T>[arr.private_length];
    for(int i=0; i<arr.private_length; i++){
        new(SGEXTN::Containers::PlacementNew::placeholder, &((*(vec.private_ringBuffer.private_data + i)).object)) T(static_cast<T&&>(arr.at(i)));
    }
    vec.private_ringBuffer.private_start = 0;
    vec.private_ringBuffer.private_length = arr.private_length;
    vec.private_ringBuffer.private_memoryLength = arr.private_length;
    delete[] arr.private_data;
    arr.private_data = nullptr;
    arr.private_length = 0;
    return vec;
}

template <typename T> SGEXTN::Containers::Array<T> SGEXTN::Containers::ArrayVectorMove<T>::convertToArrayAndDestroyVector(SGEXTN::Containers::Vector<T>& vec){
    SGEXTN::Containers::Array<T> arr(0);
    arr.private_length = vec.private_ringBuffer.private_length;
    arr.private_data = new T[arr.private_length];
    for(int i=0; i<arr.private_length; i++){
        arr.at(i) = static_cast<T&&>(vec.at(i));
        vec.at(i).~T();
    }
    delete[] vec.private_ringBuffer.private_data;
    vec.private_ringBuffer.private_data = nullptr;
    vec.private_ringBuffer.private_start = 0;
    vec.private_ringBuffer.private_length = 0;
    vec.private_ringBuffer.private_memoryLength = 0;
    return arr;
}
