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

template <typename T> SGEXTN::Containers::Span<T>::Span(T* data, int length) : data_(data), length_(length){
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span constructor crashed because the length is negative");}
    if(data == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span constructor crashed because the data pointer is nullptr");}
}

template <typename T> SGEXTN::Containers::Span<T>::Span(SGEXTN::Containers::Array<T>& array) : data_(array.getRawPointer()), length_(array.length()){}

template <typename T> SGEXTN::Containers::Span<T>::Span(SGEXTN::Containers::Array<T>& array, int start, int length) : data_(array.getRawPointer() + start), length_(length){
    if(start < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span constructor crashed because starting point of span is negative");}
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span constructor crashed because length of span is negative");}
    if(start + length > array.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span constructor crashed because end of span points beyond end of the array");}
}

template <typename T> int SGEXTN::Containers::Span<T>::length() const {
    return length_;
}

template <typename T> T& SGEXTN::Containers::Span<T>::at(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::at crashed because the index is negative");}
    if(i >= length_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::at crashed because the index points beyond the end of the span");}
    return (*(data_ + i));
}

template <typename T> const T& SGEXTN::Containers::Span<T>::at(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::at crashed because the index is negative");}
    if(i >= length_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::at crashed because the index points beyond the end of the span");}
    return (*(data_ + i));
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspan(int start, int length) const {
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspan crashed because the length is negative");}
    if(start < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspan crashed because the starting point is negative");}
    if(start + length > length_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspan crashed because the ending point, which is start + length - 1, will point beyond the end of the span");}
    return SGEXTN::Containers::Span(data_ + start, length);
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspanLeft(int length) const {
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspanLeft crashed because the length of the subspan is negative");}
    if(length > length_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspanLeft crashed because the length of the subspan exceeds the length of the original span");}
    return SGEXTN::Containers::Span(data_, length);
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspanRight(int length) const {
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspanRight crashed because the length of the subspan is negative");}
    if(length > length_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspanRight crashed because the length of the subspan exceeds the length of the original span");}
    return SGEXTN::Containers::Span(data_ + length_ - length, length);
}

template <typename T> template <typename Comparator> void SGEXTN::Containers::Span<T>::sort(int start, int length){
    if(start < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::sort crashed because start of range is negative");}
    if(start + length > (*this).length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::sort crashed because end of range points beyond the end of the span");}
    SGEXTN::Containers::Sort<T, Comparator>::sort(data_ + start, length);
}

template <typename T> T* SGEXTN::Containers::Span<T>::getRawPointer(){
    return data_;
}

template <typename T> const T* SGEXTN::Containers::Span<T>::getRawPointer() const {
    return data_;
}
