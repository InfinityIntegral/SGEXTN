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

#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Containers/Hash.h>
#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

namespace {
unsigned long long rotation(unsigned long long x, int k){
    return ((x << k) | (x >> (64 - k)));
}

int tempHash(unsigned int a, int b){
    SGEXTN::Containers::Array<unsigned char> bufferArray(8, static_cast<unsigned char>(0));
    static_cast<void>(SGEXTN::Containers::Serialise<unsigned int>::sendOut(SGEXTN::Containers::Hash<unsigned int>()(a), SGEXTN::Containers::Span<unsigned char>(bufferArray, 0, 4)));
    static_cast<void>(SGEXTN::Containers::Serialise<int>::sendOut(SGEXTN::Containers::Hash<int>()(b), SGEXTN::Containers::Span<unsigned char>(bufferArray, 4, 4)));
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<unsigned char>(bufferArray, 0, 8));
}
}

SGEXTN::SeerattraNum::DirectRandom::DirectRandom() : cache_(0u), cacheActive_(false), firstNum_(0u), secondNum_(0u), thirdNum_(0u), fourthNum_(0u){
    seed(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(8));
}

bool SGEXTN::SeerattraNum::DirectRandom::sendOut(const SGEXTN::SeerattraNum::DirectRandom& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<unsigned long long, unsigned long long, unsigned long long, unsigned long long, bool, unsigned int>::sendOut(x.firstNum_, x.secondNum_, x.thirdNum_, x.fourthNum_, x.cacheActive_, x.cache_, data);
}

bool SGEXTN::SeerattraNum::DirectRandom::sendIn(SGEXTN::SeerattraNum::DirectRandom& x, SGEXTN::Containers::Span<unsigned char> data){
    unsigned long long n1 = 0;
    unsigned long long n2 = 0;
    unsigned long long n3 = 0;
    unsigned long long n4 = 0;
    bool cacheActive = false;
    unsigned int cache = 0;
    const bool isValid = SGEXTN::Containers::Serialise<unsigned long long, unsigned long long, unsigned long long, unsigned long long, bool, unsigned int>::sendIn(n1, n2, n3, n4, cacheActive, cache, data);
    if(isValid == false){return false;}
    x.firstNum_ = n1;
    x.secondNum_ = n2;
    x.thirdNum_ = n3;
    x.fourthNum_ = n4;
    x.cacheActive_ = cacheActive;
    x.cache_ = cache;
    return true;
}

int SGEXTN::SeerattraNum::DirectRandom::size(){
    return 37;
}

void SGEXTN::SeerattraNum::DirectRandom::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    SGEXTN::Containers::Array<unsigned int> improvedSeed({0x19650809u, 1965u, 65u, 26u, 726u, 5900691u, 61u, 744u});
    if(seedArray.length() == 0){
        for(int i=0; i<8; i++){
            improvedSeed.at(i) = tempHash(improvedSeed.at(i), i);
        }
    }
    else{
        for(int i=0; i<8; i++){
            improvedSeed.at(i) = tempHash(seedArray.at(i % seedArray.length()), i);
        }
    }
    for(int i=0; i<8; i++){
        if(improvedSeed.at(i) == 0){improvedSeed.at(i) = 0x19650809u + i;}
    }
    firstNum_ = static_cast<unsigned long long>(improvedSeed.at(0)) | (static_cast<unsigned long long>(improvedSeed.at(1)) << 32);
    secondNum_ = static_cast<unsigned long long>(improvedSeed.at(2)) | (static_cast<unsigned long long>(improvedSeed.at(3)) << 32);
    thirdNum_ = static_cast<unsigned long long>(improvedSeed.at(4)) | (static_cast<unsigned long long>(improvedSeed.at(5)) << 32);
    fourthNum_ = static_cast<unsigned long long>(improvedSeed.at(6)) | (static_cast<unsigned long long>(improvedSeed.at(7)) << 32);
    cacheActive_ = false;
    cache_ = 0u;
}

int SGEXTN::SeerattraNum::DirectRandom::randomInt32(){
    if(cacheActive_ == true){
        cacheActive_ = false;
        return static_cast<int>(cache_);
    }
    const unsigned long long rng = randomUnsignedInt64();
    cacheActive_ = true;
    cache_ = static_cast<unsigned int>(rng >> 32);
    return static_cast<int>(rng & 0xffffffff);
}

unsigned int SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt32(){
    return static_cast<unsigned int>(randomInt32());
}

long long SGEXTN::SeerattraNum::DirectRandom::randomInt64(){
    return static_cast<long long>(randomUnsignedInt64());
}

unsigned long long SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt64(){
    const unsigned long long output = rotation(secondNum_ * 5, 7) * 9;
    const unsigned long long t = secondNum_ << 17;
    thirdNum_ = thirdNum_ ^ firstNum_;
    fourthNum_ = fourthNum_ ^ secondNum_;
    secondNum_ = secondNum_ ^ thirdNum_;
    firstNum_ = firstNum_ ^ fourthNum_;
    thirdNum_ = thirdNum_ ^ t;
    fourthNum_ = rotation(fourthNum_, 45);
    return output;
}

float SGEXTN::SeerattraNum::DirectRandom::randomFloat32(){
    const float scaleFactor = 1.0f / static_cast<float>(static_cast<unsigned int>(1) << 24);
    return (static_cast<float>(randomUnsignedInt32() >> 8) * scaleFactor);
}

double SGEXTN::SeerattraNum::DirectRandom::randomFloat64(){
    const double scaleFactor = static_cast<double>(1.0f) / static_cast<double>(static_cast<unsigned long long>(1) << 53);
    return (static_cast<double>(randomUnsignedInt64() >> 11) * scaleFactor);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::DirectRandom::randomInt32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomInt32Array crashed as count is negative");}
    SGEXTN::Containers::Array<int> output(count, 0);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomInt32();
    }
    return output;
}

SGEXTN::Containers::Array<long long> SGEXTN::SeerattraNum::DirectRandom::randomInt64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomInt64Array crashed as count is negative");}
    SGEXTN::Containers::Array<long long> output(count, 0);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomInt64();
    }
    return output;
}

SGEXTN::Containers::Array<unsigned int> SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt32Array crashed as count is negative");}
    SGEXTN::Containers::Array<unsigned int> output(count, 0);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt32();
    }
    return output;
}

SGEXTN::Containers::Array<unsigned long long> SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt64Array crashed as count is negative");}
    SGEXTN::Containers::Array<unsigned long long> output(count, 0);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt64();
    }
    return output;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::DirectRandom::randomFloat32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomFloat32Array crashed as count is negative");}
    SGEXTN::Containers::Array<float> output(count, 0.0f);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomFloat32();
    }
    return output;
}

SGEXTN::Containers::Array<double> SGEXTN::SeerattraNum::DirectRandom::randomFloat64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomFloat64Array crashed as count is negative");}
    SGEXTN::Containers::Array<double> output(count, 0.0f);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomFloat64();
    }
    return output;
}

SGEXTN::SeerattraNum::DirectRandom* SGEXTN::SeerattraNum::DirectRandom::createRng(bool useGlobal){
    if(useGlobal == true){
        if(SGEXTN::SeerattraNum::SimpleRandom::globalInstance == nullptr){SGEXTN::SeerattraNum::SimpleRandom::globalInstance = new SGEXTN::SeerattraNum::DirectRandom();}
        return SGEXTN::SeerattraNum::SimpleRandom::globalInstance;
    }
    return new SGEXTN::SeerattraNum::DirectRandom();
}
