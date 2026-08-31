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

#include <SGEXTN/CoreText/private_api/ByteVector.h>
#include <cstring>

namespace {
void memoryCopy(const unsigned char* source, unsigned char* destination, int length){
    std::memcpy(destination, source, length);
}
}

SGEXTN::CoreText::ByteVector::ByteVector() : data_(nullptr), length_(0), memoryLength_(0){}

SGEXTN::CoreText::ByteVector::ByteVector(int count) : data_(new unsigned char[count]), length_(count), memoryLength_(count){}

SGEXTN::CoreText::ByteVector::ByteVector(const SGEXTN::CoreText::ByteVector& x) : data_(nullptr), length_(x.length_), memoryLength_(x.length_) {
    if(x.length_ > 0){
        data_ = new unsigned char[x.length_];
        memoryCopy(x.data_, data_, x.length_);
    }
}

SGEXTN::CoreText::ByteVector& SGEXTN::CoreText::ByteVector::operator=(const SGEXTN::CoreText::ByteVector& x){
    if(this == &x){return (*this);}
    delete[] data_;
    length_ = x.length_;
    memoryLength_ = x.length_;
    if(x.length_ == 0){data_ = nullptr;}
    else{
        data_ = new unsigned char[x.length_];
        memoryCopy(x.data_, data_, x.length_);
    }
    return (*this);
}

SGEXTN::CoreText::ByteVector::ByteVector(SGEXTN::CoreText::ByteVector&& x) noexcept : data_(x.data_), length_(x.length_), memoryLength_(x.memoryLength_) {
    x.data_ = nullptr;
    x.length_ = 0;
    x.memoryLength_ = 0;
}

SGEXTN::CoreText::ByteVector& SGEXTN::CoreText::ByteVector::operator=(SGEXTN::CoreText::ByteVector&& x) noexcept {
    if(this == &x){return (*this);}
    delete[] data_;
    data_ = x.data_;
    length_ = x.length_;
    memoryLength_ = x.memoryLength_;
    x.data_ = nullptr;
    x.length_ = 0;
    x.memoryLength_ = 0;
    return (*this);
}

SGEXTN::CoreText::ByteVector::~ByteVector(){
    delete[] data_;
}

unsigned char& SGEXTN::CoreText::ByteVector::at(int i){
    unsigned char* data0 = data_;
    data_ = data0;
    return (*(data_ + i));
}

const unsigned char& SGEXTN::CoreText::ByteVector::at(int i) const {
    return (*(data_ + i));
}

int SGEXTN::CoreText::ByteVector::length() const {
    return length_;
}

void SGEXTN::CoreText::ByteVector::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLength_){return;}
    const unsigned char* oldPointer = data_;
    memoryLength_ = newMemoryLength;
    data_ = new unsigned char[newMemoryLength];
    if(oldPointer != nullptr){memoryCopy(oldPointer, data_, length_);}
    delete[] oldPointer;
}

void SGEXTN::CoreText::ByteVector::pushBack(unsigned char c){
    if(length_ + 1 > memoryLength_){reserve(3 * (length_ + 1) / 2 + 1);}
    length_++;
    (*(data_ + length_ - 1)) = c;
}

void SGEXTN::CoreText::ByteVector::pushBack(const unsigned char* start, int length){
    if(length_ + length > memoryLength_){reserve(3 * (length_ + length) / 2 + 1);}
    length_ += length;
    memoryCopy(start, data_ + length_ - length, length);
}

unsigned char* SGEXTN::CoreText::ByteVector::getRawPointer(){
    return data_;
}

const unsigned char* SGEXTN::CoreText::ByteVector::getRawPointer() const {
    return data_;
}
