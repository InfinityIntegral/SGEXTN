#ifndef SGLHASH_H
#define SGLHASH_H

#include "sglspan.h"
#include "sglprimitivetypechecker.h"

template <typename T> class SGLHash {
public:
    static_assert(SGLPrimitiveTypeChecker<T>::x, "Using SGLHash on structs with padding would break your data structures, so it has been disabled for everything except primitive types. Pls declare unsigned int YourStruct::hash() const; and SGLHashMerge::merge the SGLHash results of component properties inside that function, then use SGLHashCustom instead. For SGEXTN builtin primitives, use SGLHashCustom directly without defining the function.");
    [[nodiscard]] unsigned int operator()(const T& x) const;
};

template <typename T> class SGLHashCustom {
public:
    [[nodiscard]] unsigned int operator()(const T& x) const;
};

class SGLHashMerge {
public:
    static unsigned int merge(unsigned int hash1, unsigned int hash2);
};

template <typename T> unsigned int SGLHash<T>::operator()(const T& x) const {
    const SGLSpan<const unsigned char> span(reinterpret_cast<const unsigned char*>(&x), sizeof(T));
    const unsigned int num0 = 0xA0761D65;
    const unsigned int num1 = 0xE7037ED1;
    const unsigned int num2 = 0x8EBC6AF1;
    const unsigned int num3 = 0x589965CC;
    int i = 0;
    const int sizeOfT = static_cast<int>(sizeof(T));
    unsigned int hash = num0;
    while(sizeOfT - i >= 4){
        unsigned int k = 0u;
        k = k | (span.at(i));
        k = k | (span.at(i + 1) << 8);
        k = k | (span.at(i + 2) << 16);
        k = k | (span.at(i + 3) << 24);
        hash = num1 * (hash ^ k);
        hash = (hash << 13) | (hash >> 19);
        i += 4;
    }
    if(i < sizeOfT){
        unsigned int k = 0u;
        for(int j=0; j<sizeOfT-i; j++){
            k = k | (span.at(i + j) << (8 * j));
        }
        hash = num1 * (hash ^ k);
        hash = (hash << 13) | (hash >> 19);
    }
    hash = num2 * (hash ^ (hash >> 16));
    hash = num3 * (hash ^ (hash >> 13));
    hash = hash ^ (hash >> 16);
    return hash;
}

template <typename T> unsigned int SGLHashCustom<T>::operator()(const T& x) const {
    return x.hash();
}

inline unsigned int SGLHashMerge::merge(unsigned int hash1, unsigned int hash2){
    const unsigned long long x = (static_cast<unsigned long long>(hash1) << 32) | static_cast<unsigned long long>(hash2);
    const SGLHash<unsigned long long> h;
    return h(x);
}

#endif // SGLHASH_H
