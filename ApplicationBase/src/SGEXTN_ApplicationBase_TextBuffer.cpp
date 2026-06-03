#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>
#include <SGEXTN_Containers_Vector.h>
#include <cstring>
#include <SGEXTN_Containers_HashAlgorithm.h>
#include <SGEXTN_Containers_Span.h>
#include <SGEXTN_Containers_PlacementNew.h>

namespace {
void memoryCopy(const unsigned char* source, unsigned char* target, int length){
    std::memcpy(target, source, length);
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
    return (*(private_stackAllocData + 23));
}

const unsigned char& SGEXTN::ApplicationBase::TextBuffer::private_lengthByte() const {
    return (*(private_stackAllocData + 23));
}

SGEXTN::ApplicationBase::TextBuffer::TextBuffer(){
    private_isHeapAlloc = false;
    private_lengthByte() = 0;
}

SGEXTN::ApplicationBase::TextBuffer::TextBuffer(const SGEXTN::ApplicationBase::TextBuffer& x){
    private_isHeapAlloc = x.private_isHeapAlloc;
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::Containers::Vector<unsigned char>(x.private_heapAllocData);}
}

SGEXTN::ApplicationBase::TextBuffer& SGEXTN::ApplicationBase::TextBuffer::operator=(const SGEXTN::ApplicationBase::TextBuffer& x){
    if(this == &x){return (*this);}
    if(private_isHeapAlloc == true){private_heapAllocData.~Vector<unsigned char>();}
    private_isHeapAlloc = x.private_isHeapAlloc;
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.length();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::Containers::Vector<unsigned char>(x.private_heapAllocData);}
    return (*this);
}

SGEXTN::ApplicationBase::TextBuffer::TextBuffer(SGEXTN::ApplicationBase::TextBuffer&& x) noexcept {
    private_isHeapAlloc = x.private_isHeapAlloc;
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::Containers::Vector<unsigned char>((SGEXTN::Containers::Vector<unsigned char>&&)(x.private_heapAllocData));}
}

SGEXTN::ApplicationBase::TextBuffer& SGEXTN::ApplicationBase::TextBuffer::operator=(SGEXTN::ApplicationBase::TextBuffer&& x) noexcept {
    if(private_isHeapAlloc == true){private_heapAllocData.~Vector<unsigned char>();}
    private_isHeapAlloc = x.private_isHeapAlloc;
    if(private_isHeapAlloc == false){
        private_lengthByte() = x.private_lengthByte();
        memoryCopy(x.private_stackAllocData, private_stackAllocData, private_lengthByte());
    }
    else{new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::Containers::Vector<unsigned char>((SGEXTN::Containers::Vector<unsigned char>&&)(x.private_heapAllocData));}
    return (*this);
}

SGEXTN::ApplicationBase::TextBuffer::~TextBuffer(){
    if(private_isHeapAlloc == true){private_heapAllocData.~Vector<unsigned char>();}
}

unsigned char& SGEXTN::ApplicationBase::TextBuffer::byteAt(int i){
    if(private_isHeapAlloc == false){return (*(private_stackAllocData + i));}
    return (*private_heapAllocData.pointerToData(i));
}

const unsigned char& SGEXTN::ApplicationBase::TextBuffer::byteAt(int i) const {
    if(private_isHeapAlloc == false){return (*(private_stackAllocData + i));}
    return (*private_heapAllocData.pointerToData(i));
}

int SGEXTN::ApplicationBase::TextBuffer::length() const {
    if(private_isHeapAlloc == false){return private_lengthByte();}
    return private_heapAllocData.length();
}

void SGEXTN::ApplicationBase::TextBuffer::private_moveToHeap(){
    SGEXTN::Containers::Vector<unsigned char> heapContainer;
    heapContainer.reserve(private_lengthByte());
    heapContainer.private_ringBuffer.private_length = private_lengthByte();
    memoryCopy(private_stackAllocData, heapContainer.pointerToData(0), private_lengthByte());
    private_isHeapAlloc = true;
    new(SGEXTN::Containers::PlacementNew::placeholder, &private_heapAllocData) SGEXTN::Containers::Vector<unsigned char>((SGEXTN::Containers::Vector<unsigned char>&&)(heapContainer));
}

void SGEXTN::ApplicationBase::TextBuffer::pushBack(char c){
    const int newLength = length() + 1;
    if(newLength < 24){
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
    if(newLength < 24){
        private_lengthByte() = newLength;
        for(int i=0; i<sLength; i++){
            (*(private_stackAllocData + oldLength + i)) = static_cast<unsigned char>(*(s + i));
        }
    }
    else{
        if(private_isHeapAlloc == false){private_moveToHeap();}
        if(private_heapAllocData.private_ringBuffer.private_memoryLength < newLength){private_heapAllocData.reserve(3 * newLength / 2);}
        private_heapAllocData.private_ringBuffer.private_length = newLength;
        for(int i=0; i<sLength; i++){
            (*private_heapAllocData.pointerToData(oldLength + i)) = static_cast<unsigned char>(*(s + i));
        }
    }
}

void SGEXTN::ApplicationBase::TextBuffer::pushBack(const TextBuffer& data, int start, int length){
    const int oldLength = (*this).length();
    const int newLength = oldLength + length;
    if(newLength < 24){
        private_lengthByte() = newLength;
        if(data.private_isHeapAlloc == false){memoryCopy(data.private_stackAllocData + start, private_stackAllocData + oldLength, length);}
        else{memoryCopy(data.private_heapAllocData.pointerToData(start), private_stackAllocData + oldLength, length);}
    }
    else{
        if(private_isHeapAlloc == false){private_moveToHeap();}
        if(private_heapAllocData.private_ringBuffer.private_memoryLength < newLength){private_heapAllocData.reserve(3 * newLength / 2);}
        private_heapAllocData.private_ringBuffer.private_length = newLength;
        if(data.private_isHeapAlloc == false){memoryCopy(data.private_stackAllocData + start, private_heapAllocData.pointerToData(oldLength), length);}
        else{memoryCopy(data.private_heapAllocData.pointerToData(start), private_heapAllocData.pointerToData(oldLength), length);}
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