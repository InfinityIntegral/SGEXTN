#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>
#include <cstring>
#include <SGEXTN_Containers_PlacementNew.h>
#include <SGEXTN_Containers_HashAlgorithm.h>
#include <SGEXTN_Containers_Span.h>

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

unsigned char& SGEXTN::ApplicationBase::TextBuffer::private_lengthByte(){
    return (*(private_stackAllocData + 15));
}

const unsigned char& SGEXTN::ApplicationBase::TextBuffer::private_lengthByte() const {
    return (*(private_stackAllocData + 15));
}

SGEXTN::ApplicationBase::TextBuffer::TextBuffer() : private_isHeapAlloc(false), private_stackAllocData() {
    memoryFill(private_stackAllocData, 12, static_cast<unsigned char>(0));
}

SGEXTN::ApplicationBase::TextBuffer::TextBuffer(const SGEXTN::ApplicationBase::TextBuffer& x) : private_isHeapAlloc(x.private_isHeapAlloc) {
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::ApplicationBase::ByteVector(x.private_heapAllocData);}
}

SGEXTN::ApplicationBase::TextBuffer& SGEXTN::ApplicationBase::TextBuffer::operator=(const SGEXTN::ApplicationBase::TextBuffer& x){
    if(this == &x){return (*this);}
    if(private_isHeapAlloc == true){private_heapAllocData.~ByteVector();}
    private_isHeapAlloc = x.private_isHeapAlloc;
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.length();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::ApplicationBase::ByteVector(x.private_heapAllocData);}
    return (*this);
}

SGEXTN::ApplicationBase::TextBuffer::TextBuffer(SGEXTN::ApplicationBase::TextBuffer&& x) noexcept : private_isHeapAlloc(x.private_isHeapAlloc) {
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::ApplicationBase::ByteVector(static_cast<SGEXTN::ApplicationBase::ByteVector&&>(x.private_heapAllocData));}
}

SGEXTN::ApplicationBase::TextBuffer& SGEXTN::ApplicationBase::TextBuffer::operator=(SGEXTN::ApplicationBase::TextBuffer&& x) noexcept {
    if(private_isHeapAlloc == true){private_heapAllocData.~ByteVector();}
    private_isHeapAlloc = x.private_isHeapAlloc;
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::ApplicationBase::ByteVector(static_cast<SGEXTN::ApplicationBase::ByteVector&&>(x.private_heapAllocData));}
    return (*this);
}

SGEXTN::ApplicationBase::TextBuffer::~TextBuffer(){
    if(private_isHeapAlloc == true){private_heapAllocData.~ByteVector();}
}

unsigned char& SGEXTN::ApplicationBase::TextBuffer::byteAt(int i){
    if(private_isHeapAlloc == false){return (*(private_stackAllocData + i));}
    return private_heapAllocData.at(i);
}

const unsigned char& SGEXTN::ApplicationBase::TextBuffer::byteAt(int i) const {
    if(private_isHeapAlloc == false){return (*(private_stackAllocData + i));}
    return private_heapAllocData.at(i);
}

int SGEXTN::ApplicationBase::TextBuffer::length() const {
    if(private_isHeapAlloc == false){return private_lengthByte();}
    return private_heapAllocData.length();
}

void SGEXTN::ApplicationBase::TextBuffer::private_moveToHeap(){
    SGEXTN::ApplicationBase::ByteVector heapContainer;
    heapContainer.pushBack(private_stackAllocData, private_lengthByte());
    private_isHeapAlloc = true;
    new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::ApplicationBase::ByteVector(static_cast<SGEXTN::ApplicationBase::ByteVector&&>(heapContainer));
}

void SGEXTN::ApplicationBase::TextBuffer::pushBack(char c){
    const int newLength = length() + 1;
    if(newLength < 16){
        (*(private_stackAllocData + newLength - 1)) = static_cast<unsigned char>(c);
        private_lengthByte() = newLength;
    }
    else{
        if(private_isHeapAlloc == false){private_moveToHeap();}
        private_heapAllocData.pushBack(static_cast<unsigned char>(c));
    }
}

void SGEXTN::ApplicationBase::TextBuffer::pushBack(const char* s){
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

void SGEXTN::ApplicationBase::TextBuffer::pushBack(const TextBuffer& data, int start, int length){
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

bool SGEXTN::ApplicationBase::TextBuffer::operator==(const SGEXTN::ApplicationBase::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) == 0);
}

bool SGEXTN::ApplicationBase::TextBuffer::operator!=(const SGEXTN::ApplicationBase::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) != 0);
}

bool SGEXTN::ApplicationBase::TextBuffer::operator<(const SGEXTN::ApplicationBase::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) < 0);
}

bool SGEXTN::ApplicationBase::TextBuffer::operator>(const SGEXTN::ApplicationBase::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) > 0);
}

bool SGEXTN::ApplicationBase::TextBuffer::operator<=(const SGEXTN::ApplicationBase::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) <= 0);
}

bool SGEXTN::ApplicationBase::TextBuffer::operator>=(const SGEXTN::ApplicationBase::TextBuffer& x) const {
    return (memoryCompare(&byteAt(0), length(), &x.byteAt(0), x.length()) >= 0);
}

int SGEXTN::ApplicationBase::TextBuffer::hash() const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(&byteAt(0), length()));
}

SGEXTN::ApplicationBase::TextBuffer SGEXTN::ApplicationBase::TextBuffer::substring(int start, int length) const {
    SGEXTN::ApplicationBase::TextBuffer output;
    output.pushBack((*this), start, length);
    return output;
}

SGEXTN::ApplicationBase::TextBuffer SGEXTN::ApplicationBase::TextBuffer::substringLeft(int length) const {
    return substring(0, length);
}

SGEXTN::ApplicationBase::TextBuffer SGEXTN::ApplicationBase::TextBuffer::substringRight(int length) const {
    return substring((*this).length() - length, length);
}