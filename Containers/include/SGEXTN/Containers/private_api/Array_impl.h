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

template <typename T> SGEXTN::Containers::Array<T>::Array(int count) : private_data(nullptr), private_length(count) {
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array constructor crashed because count cannot be negative");}
    if(count > 0){private_data = new T[count]();}
}

template <typename T> SGEXTN::Containers::Array<T>::Array(int count, const T& defaultValue) : private_data(nullptr), private_length(count) {
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array constructor crashed because count cannot be negative");}
    if(count > 0){private_data = new T[count];}
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = defaultValue;
    }
}

template <typename T> template <typename... Ts> SGEXTN::Containers::Array<T>::Array(Ts... data) : private_data(nullptr), private_length(sizeof...(Ts)){
    if((sizeof...(Ts)) > 0){private_data = new T[private_length]{data...};}
}

template <typename T> SGEXTN::Containers::Array<T>::Array(const Array& x) : private_data(nullptr), private_length(x.private_length) {
    if(x.private_length > 0){private_data = new T[x.private_length];}
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = (*(x.private_data + i));
    }
}

template <typename T> SGEXTN::Containers::Array<T>& SGEXTN::Containers::Array<T>::operator=(const Array& x){
    if(this == &x){return (*this);}
    delete[] private_data;
    if(x.private_length == 0){private_data = nullptr;}
    else{private_data = new T[x.private_length];}
    private_length = x.private_length;
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = (*(x.private_data + i));
    }
    return (*this);
}

template <typename T> SGEXTN::Containers::Array<T>::Array(Array&& x) noexcept : private_data(x.private_data), private_length(x.private_length) {
    x.private_data = nullptr;
    x.private_length = 0;
}

template <typename T> SGEXTN::Containers::Array<T>& SGEXTN::Containers::Array<T>::operator=(Array&& x) noexcept {
    delete[] private_data;
    private_data = x.private_data;
    private_length = x.private_length;
    x.private_data = nullptr;
    x.private_length = 0;
    return (*this);
}

template <typename T> SGEXTN::Containers::Array<T>::~Array(){
    delete[] private_data;
}

template <typename T> void SGEXTN::Containers::Array<T>::fill(const T& defaultValue){
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = defaultValue;
    }
}

template <typename T> int SGEXTN::Containers::Array<T>::length() const {
    return private_length;
}

template <typename T> T& SGEXTN::Containers::Array<T>::at(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::at crashed because index is negative");}
    if(i >= private_length){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::at crashed because index points beyond the end of the array");}
    return (*(private_data + i));
}

template <typename T> const T& SGEXTN::Containers::Array<T>::at(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::at crashed because index is negative");}
    if(i >= private_length){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::at crashed because index points beyond the end of the array");}
    return (*(private_data + i));
}

template <typename T> template <typename Comparator> void SGEXTN::Containers::Array<T>::sort(int start, int length){
    if(start < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::sort crashed because start of range is negative");}
    if(start + length > (*this).length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array::sort crashed because end of range points beyond the end of the array");}
    SGEXTN::Containers::Sort<T, Comparator>::private_sort(private_data + start, length);
}
