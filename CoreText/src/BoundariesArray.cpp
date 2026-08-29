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

#include <SGEXTN/CoreText/private_api/BoundariesArray.h>

SGEXTN::CoreText::BoundariesArray::BoundariesArray() : length_(0), freeSpace_(0), data_(nullptr){}

SGEXTN::CoreText::BoundariesArray::BoundariesArray(int count) : length_(count), freeSpace_(0), data_(new unsigned int[count](0)){}

SGEXTN::CoreText::BoundariesArray::BoundariesArray(SGEXTN::CoreText::BoundariesArray&& x) noexcept : data_(x.data_), freeSpace_(x.freeSpace_), length_(x.length_){
    x.data_ = nullptr;
    x.length_ = 0;
    x.freeSpace_ = 0;
}

SGEXTN::CoreText::BoundariesArray& SGEXTN::CoreText::BoundariesArray::operator=(SGEXTN::CoreText::BoundariesArray&& x) noexcept {
    if(this == &x){return (*this);}
    delete[] data_;
    data_ = x.data_;
    length_ = x.length_;
    freeSpace_ = x.freeSpace_;
    x.data_ = nullptr;
    x.length_ = 0;
    x.freeSpace_ = 0;
    return (*this);
}

SGEXTN::CoreText::BoundariesArray::~BoundariesArray(){
    delete[] data_;
}

int SGEXTN::CoreText::BoundariesArray::length() const {
    return length_;
}

unsigned int& SGEXTN::CoreText::BoundariesArray::at(int i){
    unsigned int* temp = data_;
    data_ = temp;
    return (*(data_ + i));
}

int& SGEXTN::CoreText::BoundariesArray::emptySpace(){
    const int temp = freeSpace_;
    freeSpace_ = temp;
    return freeSpace_;
}
