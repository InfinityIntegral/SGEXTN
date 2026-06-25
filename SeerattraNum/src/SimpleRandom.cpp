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

#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <random>

namespace {
void initialiseRng(){
    SGEXTN::Containers::Array<unsigned int> seedArray = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(8);
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + 8);
    SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937 = SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::eraseType(new std::mt19937_64(seedSequence));
}

unsigned long long getRandomNumber(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937 == nullptr){initialiseRng();}
    return (*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937))();
}
}

void* SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937 = nullptr;

int SGEXTN::SeerattraNum::SimpleRandom::randomInt32(){
    return static_cast<int>(getRandomNumber());
}

long long SGEXTN::SeerattraNum::SimpleRandom::randomInt64(){
    return static_cast<long long>(getRandomNumber());
}

unsigned int SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32(){
    return static_cast<unsigned int>(getRandomNumber());
}

unsigned long long SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64(){
    return getRandomNumber();
}

float SGEXTN::SeerattraNum::SimpleRandom::randomFloat32(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937 == nullptr){initialiseRng();}
    if(SGEXTN::SeerattraNum::TrueRandom::private_stlDistributionFloat == nullptr){SGEXTN::SeerattraNum::TrueRandom::private_stlDistributionFloat = SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<float>>::eraseType(new std::uniform_real_distribution<float>(0.0f, 1.0f));}
    return (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<float>>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::private_stlDistributionFloat))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937));
}

double SGEXTN::SeerattraNum::SimpleRandom::randomFloat64(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937 == nullptr){initialiseRng();}
    if(SGEXTN::SeerattraNum::TrueRandom::private_stlDistributionDouble == nullptr){SGEXTN::SeerattraNum::TrueRandom::private_stlDistributionDouble = SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<double>>::eraseType(new std::uniform_real_distribution<double>(0.0, 1.0));}
    return (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<double>>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::private_stlDistributionDouble))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937));
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::SimpleRandom::randomInt32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom::randomInt32Array crashed as count is negative");}
    SGEXTN::Containers::Array<int> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::SimpleRandom::randomInt32();
    }
    return output;
}

SGEXTN::Containers::Array<long long> SGEXTN::SeerattraNum::SimpleRandom::randomInt64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom::randomInt64Array crashed as count is negative");}
    SGEXTN::Containers::Array<long long> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::SimpleRandom::randomInt64();
    }
    return output;
}

SGEXTN::Containers::Array<unsigned int> SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32Array crashed as count is negative");}
    SGEXTN::Containers::Array<unsigned int> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32();
    }
    return output;
}

SGEXTN::Containers::Array<unsigned long long> SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64Array crashed as count is negative");}
    SGEXTN::Containers::Array<unsigned long long> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64();
    }
    return output;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::SimpleRandom::randomFloat32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom::randomFloat32Array crashed as count is negative");}
    SGEXTN::Containers::Array<float> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::SimpleRandom::randomFloat32();
    }
    return output;
}

SGEXTN::Containers::Array<double> SGEXTN::SeerattraNum::SimpleRandom::randomFloat64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom::randomFloat64Array crashed as count is negative");}
    SGEXTN::Containers::Array<double> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::SimpleRandom::randomFloat64();
    }
    return output;
}

void* SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937 == nullptr){initialiseRng();}
    return SGEXTN::SeerattraNum::SimpleRandom::private_stlMersenneTwister19937;
}

void* SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(bool useGlobal){
    if(useGlobal == true){return nullptr;}
    SGEXTN::Containers::Array<unsigned int> seedArray = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(8);
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + 8);
    return SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::eraseType(new std::mt19937_64(seedSequence));
}

void SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(void* randomEngine, const SGEXTN::Containers::Array<unsigned int>& seedArray){
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + seedArray.length());
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)).seed(seedSequence);
}
