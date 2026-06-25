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

#include <SGEXTN/CoreText/private_api/TextBuffer.h>
#include <SGEXTN/Containers/PlacementNew.h>
#include <SGEXTN/Containers/private_api/HashAlgorithm.h>
#include <SGEXTN/Containers/Span.h>
#include <SGEXTN/CoreText/private_api/ByteVector.h>
#include <cstring>

namespace {
void memoryCopy(const unsigned char* source, unsigned char* destination, int length){
    std::memcpy(destination, source, length);
}

void memoryFill(unsigned char* start, int length, unsigned char byte){
    std::memset(start, byte, length);
}

int cStringLength(const char* s){
    return static_cast<int>(std::strlen(s));
}

int memoryCompare(const unsigned char* a, int aLength, const unsigned char* b, int bLength){
    const int lengthCompare = aLength - bLength;
    int shorterLength = 0;
    if(lengthCompare <= 0){shorterLength = aLength;}
    else{shorterLength = bLength;}
    const int equalLengthCompare = std::memcmp(a, b, shorterLength);
    if(equalLengthCompare < 0){return -1;}
    if(equalLengthCompare > 0){return 1;}
    if(lengthCompare < 0){return -1;}
    if(lengthCompare > 0){return 1;}
    return 0;
}
}

unsigned char& SGEXTN::CoreText::TextBuffer::private_lengthByte(){
    return (*(private_stackAllocData + 15));
}

const unsigned char& SGEXTN::CoreText::TextBuffer::private_lengthByte() const {
    return (*(private_stackAllocData + 15));
}

SGEXTN::CoreText::TextBuffer::TextBuffer() : private_isHeapAlloc(false), private_stackAllocData() {
    memoryFill(private_stackAllocData, 12, static_cast<unsigned char>(0));
}

SGEXTN::CoreText::TextBuffer::TextBuffer(const SGEXTN::CoreText::TextBuffer& x) : private_isHeapAlloc(x.private_isHeapAlloc), private_stackAllocData() {
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::CoreText::ByteVector(x.private_heapAllocData);}
}

SGEXTN::CoreText::TextBuffer& SGEXTN::CoreText::TextBuffer::operator=(const SGEXTN::CoreText::TextBuffer& x){
    if(this == &x){return (*this);}
    if(private_isHeapAlloc == true){private_heapAllocData.~ByteVector();}
    private_isHeapAlloc = x.private_isHeapAlloc;
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.length();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::CoreText::ByteVector(x.private_heapAllocData);}
    return (*this);
}

SGEXTN::CoreText::TextBuffer::TextBuffer(SGEXTN::CoreText::TextBuffer&& x) noexcept : private_isHeapAlloc(x.private_isHeapAlloc), private_stackAllocData() {
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::CoreText::ByteVector(static_cast<SGEXTN::CoreText::ByteVector&&>(x.private_heapAllocData));}
}

SGEXTN::CoreText::TextBuffer& SGEXTN::CoreText::TextBuffer::operator=(SGEXTN::CoreText::TextBuffer&& x) noexcept {
    if(private_isHeapAlloc == true){private_heapAllocData.~ByteVector();}
    private_isHeapAlloc = x.private_isHeapAlloc;
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::CoreText::ByteVector(static_cast<SGEXTN::CoreText::ByteVector&&>(x.private_heapAllocData));}
    return (*this);
}

SGEXTN::CoreText::TextBuffer::~TextBuffer(){
    if(private_isHeapAlloc == true){private_heapAllocData.~ByteVector();}
}

unsigned char& SGEXTN::CoreText::TextBuffer::byteAt(int i){
    if(private_isHeapAlloc == false){return (*(private_stackAllocData + i));}
    return private_heapAllocData.at(i);
}

const unsigned char& SGEXTN::CoreText::TextBuffer::byteAt(int i) const {
    if(private_isHeapAlloc == false){return (*(private_stackAllocData + i));}
    return private_heapAllocData.at(i);
}

int SGEXTN::CoreText::TextBuffer::length() const {
    if(private_isHeapAlloc == false){return private_lengthByte();}
    return private_heapAllocData.length();
}

void SGEXTN::CoreText::TextBuffer::private_moveToHeap(){
    SGEXTN::CoreText::ByteVector heapContainer;
    heapContainer.pushBack(private_stackAllocData, private_lengthByte());
    private_isHeapAlloc = true;
    new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::CoreText::ByteVector(static_cast<SGEXTN::CoreText::ByteVector&&>(heapContainer));
}

void SGEXTN::CoreText::TextBuffer::pushBack(unsigned char c){
    const int newLength = length() + 1;
    if(newLength < 16){
        (*(private_stackAllocData + newLength - 1)) = c;
        private_lengthByte() = newLength;
    }
    else{
        if(private_isHeapAlloc == false){private_moveToHeap();}
        private_heapAllocData.pushBack(c);
    }
}

void SGEXTN::CoreText::TextBuffer::pushBack(const char* s){
    const int sLength = cStringLength(s);
    const int oldLength = length();
    const int newLength = oldLength + sLength;
    const unsigned char* unsignedString = reinterpret_cast<const unsigned char*>(s);
    if(newLength < 16){
        private_lengthByte() = newLength;
        memoryCopy(unsignedString, private_stackAllocData + oldLength, sLength);
    }
    else{
        if(private_isHeapAlloc == false){private_moveToHeap();}
        private_heapAllocData.pushBack(unsignedString, sLength);
    }
}

void SGEXTN::CoreText::TextBuffer::pushBack(const TextBuffer& data, int start, int length){
    const int oldLength = (*this).length();
    const int newLength = oldLength + length;
    if(newLength < 16){
        private_lengthByte() = newLength;
        if(data.private_isHeapAlloc == false){memoryCopy(data.private_stackAllocData + start, private_stackAllocData + oldLength, length);}
        else{memoryCopy(&data.private_heapAllocData.at(start), private_stackAllocData + oldLength, length);}
    }
    else{
        if(private_isHeapAlloc == false){private_moveToHeap();}
        if(data.private_isHeapAlloc == false){private_heapAllocData.pushBack(data.private_stackAllocData + start, length);}
        else{private_heapAllocData.pushBack(&data.private_heapAllocData.at(start), length);}
    }
}

bool SGEXTN::CoreText::TextBuffer::operator==(const SGEXTN::CoreText::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) == 0);
}

bool SGEXTN::CoreText::TextBuffer::operator!=(const SGEXTN::CoreText::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) != 0);
}

bool SGEXTN::CoreText::TextBuffer::operator<(const SGEXTN::CoreText::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) < 0);
}

bool SGEXTN::CoreText::TextBuffer::operator>(const SGEXTN::CoreText::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) > 0);
}

bool SGEXTN::CoreText::TextBuffer::operator<=(const SGEXTN::CoreText::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) <= 0);
}

bool SGEXTN::CoreText::TextBuffer::operator>=(const SGEXTN::CoreText::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) >= 0);
}

int SGEXTN::CoreText::TextBuffer::hash() const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(&byteAt(0), length()));
}

SGEXTN::CoreText::TextBuffer SGEXTN::CoreText::TextBuffer::substring(int start, int length) const {
    SGEXTN::CoreText::TextBuffer output;
    output.pushBack((*this), start, length);
    return output;
}

SGEXTN::CoreText::TextBuffer SGEXTN::CoreText::TextBuffer::substringLeft(int length) const {
    return substring(0, length);
}

SGEXTN::CoreText::TextBuffer SGEXTN::CoreText::TextBuffer::substringRight(int length) const {
    return substring((*this).length() - length, length);
}
