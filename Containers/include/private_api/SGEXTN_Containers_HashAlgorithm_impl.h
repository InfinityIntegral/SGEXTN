#pragma once
#include <SGEXTN_Containers_Span.h>

int SGEXTN::Containers::HashAlgorithm::wyHash32(const SGEXTN::Containers::Span<const unsigned char> &span){
    const unsigned int num0 = 0xA0761D65;
    const unsigned int num1 = 0xE7037ED1;
    const unsigned int num2 = 0x8EBC6AF1;
    const unsigned int num3 = 0x589965CC;
    int i = 0;
    const int sizeOfT = span.length();
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
    return static_cast<int>(hash);
}
