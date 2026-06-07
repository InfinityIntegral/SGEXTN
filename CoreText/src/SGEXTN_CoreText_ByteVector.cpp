#include <private_api/SGEXTN_CoreText_ByteVector.h>
#include <cstring>

namespace {
void memoryCopy(const unsigned char* source, unsigned char* destination, int length){
    std::memcpy(destination, source, length);
}
}

SGEXTN::CoreText::ByteVector::ByteVector() : private_data(nullptr), private_length(0), private_memoryLength(0) {}

SGEXTN::CoreText::ByteVector::ByteVector(const SGEXTN::CoreText::ByteVector& x) : private_data(nullptr), private_length(x.private_length), private_memoryLength(x.private_length) {
    if(x.private_length > 0){
        private_data = new unsigned char[x.private_length];
        memoryCopy(x.private_data, private_data, x.private_length);
    }
}

SGEXTN::CoreText::ByteVector& SGEXTN::CoreText::ByteVector::operator=(const SGEXTN::CoreText::ByteVector& x){
    if(&x == this){return (*this);}
    delete[] private_data;
    private_length = x.private_length;
    private_memoryLength = x.private_length;
    if(x.private_length == 0){private_data = nullptr;}
    else{
        private_data = new unsigned char[x.private_length];
        memoryCopy(x.private_data, private_data, x.private_length);
    }
    return (*this);
}

SGEXTN::CoreText::ByteVector::ByteVector(SGEXTN::CoreText::ByteVector&& x) noexcept : private_data(x.private_data), private_length(x.private_length), private_memoryLength(x.private_memoryLength) {
    x.private_data = nullptr;
    x.private_length = 0;
    x.private_memoryLength = 0;
}

SGEXTN::CoreText::ByteVector& SGEXTN::CoreText::ByteVector::operator=(SGEXTN::CoreText::ByteVector&& x) noexcept {
    delete[] private_data;
    private_data = x.private_data;
    private_length = x.private_length;
    private_memoryLength = x.private_memoryLength;
    x.private_data = nullptr;
    x.private_length = 0;
    x.private_memoryLength = 0;
    return (*this);
}

SGEXTN::CoreText::ByteVector::~ByteVector(){
    delete[] private_data;
}

// NOLINTNEXTLINE(readability-make-member-function-const)
unsigned char& SGEXTN::CoreText::ByteVector::at(int i){
    return (*(private_data + i));
}

const unsigned char& SGEXTN::CoreText::ByteVector::at(int i) const {
    return (*(private_data + i));
}

int SGEXTN::CoreText::ByteVector::length() const {
    return private_length;
}

void SGEXTN::CoreText::ByteVector::reserve(int newMemoryLength){
    if(newMemoryLength <= private_memoryLength){return;}
    const unsigned char* oldPointer = private_data;
    private_memoryLength = newMemoryLength;
    private_data = new unsigned char[newMemoryLength];
    if(oldPointer != nullptr){memoryCopy(oldPointer, private_data, private_length);}
    delete[] oldPointer;
}

void SGEXTN::CoreText::ByteVector::pushBack(unsigned char c){
    if(private_length + 1 > private_memoryLength){reserve(3 * (private_length + 1) / 2 + 1);}
    private_length++;
    (*(private_data + private_length - 1)) = c;
}

void SGEXTN::CoreText::ByteVector::pushBack(const unsigned char* start, int length){
    if(private_length + length > private_memoryLength){reserve(3 * (private_length + length) / 2 + 1);}
    private_length += length;
    memoryCopy(start, private_data + private_length - length, length);
}