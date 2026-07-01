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
#include <SGEXTN/Math/IntegerLimits.h>

namespace {
unsigned long long rotation(unsigned long long x, int k){
    return ((x << k) | (x >> (64 - k)));
}
}

SGEXTN::SeerattraNum::DirectRandom::DirectRandom() : private_cache(0u), private_cacheActive(false), private_firstNum(0u), private_secondNum(0u), private_thirdNum(0u), private_fourthNum(0u){
    seed(SGEXTN::Containers::Array<unsigned int>(0x19650809u, 1965u, 65u, 26u, 726u, 5900691u, 61u, 744u));
}

void SGEXTN::SeerattraNum::DirectRandom::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    SGEXTN::Containers::Array<unsigned int> improvedSeed(8);
    if(seedArray.length() == 0){
        SGEXTN::Containers::Array<unsigned int> defaultSeedArray(0x19650809u, 1965u, 65u, 26u, 726u, 5900691u, 61u, 744u);
        for(int i=0; i<8; i++){
            improvedSeed.at(i) = SGEXTN::Containers::Hash<unsigned int, int>()(defaultSeedArray.at(i), i);
        }
    }
    else{
        for(int i=0; i<8; i++){
            improvedSeed.at(i) = SGEXTN::Containers::Hash<unsigned int, int>()(seedArray.at(i % seedArray.length()), i);
        }
    }
    for(int i=0; i<8; i++){
        if(improvedSeed.at(i) == 0){improvedSeed.at(i) = 0x19650809u + i;}
    }
    private_firstNum = static_cast<unsigned long long>(improvedSeed.at(0)) | (static_cast<unsigned long long>(improvedSeed.at(1)) << 32);
    private_secondNum = static_cast<unsigned long long>(improvedSeed.at(2)) | (static_cast<unsigned long long>(improvedSeed.at(3)) << 32);
    private_thirdNum = static_cast<unsigned long long>(improvedSeed.at(4)) | (static_cast<unsigned long long>(improvedSeed.at(5)) << 32);
    private_fourthNum = static_cast<unsigned long long>(improvedSeed.at(6)) | (static_cast<unsigned long long>(improvedSeed.at(7)) << 32);
    private_cacheActive = false;
    private_cache = 0u;
}

int SGEXTN::SeerattraNum::DirectRandom::randomInt32(){
    if(private_cacheActive == true){
        private_cacheActive = false;
        return static_cast<int>(private_cache);
    }
    const unsigned long long rng = randomUnsignedInt64();
    private_cacheActive = true;
    private_cache = static_cast<unsigned int>(rng >> 32);
    return static_cast<int>(rng & 0xffffffff);
}

unsigned int SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt32(){
    return static_cast<unsigned int>(randomInt32());
}

long long SGEXTN::SeerattraNum::DirectRandom::randomInt64(){
    return static_cast<long long>(randomUnsignedInt64());
}

unsigned long long SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt64(){
    const unsigned long long output = rotation(private_secondNum * 5, 7) * 9;
    const unsigned long long t = private_secondNum << 17;
    private_thirdNum = private_thirdNum ^ private_firstNum;
    private_fourthNum = private_fourthNum ^ private_secondNum;
    private_secondNum = private_secondNum ^ private_thirdNum;
    private_firstNum = private_firstNum ^ private_fourthNum;
    private_thirdNum = private_thirdNum ^ t;
    private_fourthNum = rotation(private_fourthNum, 45);
    return output;
}

float SGEXTN::SeerattraNum::DirectRandom::randomFloat32(){
    const double maximum = static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) + 1.0;
    return static_cast<float>(static_cast<double>(randomUnsignedInt32()) / maximum);
}

double SGEXTN::SeerattraNum::DirectRandom::randomFloat64(){
    const double maximum = static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) + 1.0;
    return (static_cast<double>(randomUnsignedInt32()) / maximum);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::DirectRandom::randomInt32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomInt32Array crashed as count is negative");}
    SGEXTN::Containers::Array<int> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomInt32();
    }
    return output;
}

SGEXTN::Containers::Array<long long> SGEXTN::SeerattraNum::DirectRandom::randomInt64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomInt64Array crashed as count is negative");}
    SGEXTN::Containers::Array<long long> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomInt64();
    }
    return output;
}

SGEXTN::Containers::Array<unsigned int> SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt32Array crashed as count is negative");}
    SGEXTN::Containers::Array<unsigned int> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt32();
    }
    return output;
}

SGEXTN::Containers::Array<unsigned long long> SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt64Array crashed as count is negative");}
    SGEXTN::Containers::Array<unsigned long long> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomUnsignedInt64();
    }
    return output;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::DirectRandom::randomFloat32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomFloat32Array crashed as count is negative");}
    SGEXTN::Containers::Array<float> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomFloat32();
    }
    return output;
}

SGEXTN::Containers::Array<double> SGEXTN::SeerattraNum::DirectRandom::randomFloat64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom::randomFloat64Array crashed as count is negative");}
    SGEXTN::Containers::Array<double> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::DirectRandom::randomFloat64();
    }
    return output;
}
