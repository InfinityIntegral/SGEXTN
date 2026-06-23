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

#include <SGEXTN_SeerattraNum_TrueRandom.h>
#include <private_api/SGEXTN_SeerattraNum_UnsafeCasts.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_Containers_Array.h>
#include <chrono>
#include <random>

namespace {
long long getCurrentTime(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
}

void* SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice = nullptr;
void* SGEXTN::SeerattraNum::TrueRandom::stlDistributionFloat = nullptr;
void* SGEXTN::SeerattraNum::TrueRandom::stlDistributionDouble = nullptr;

int SGEXTN::SeerattraNum::TrueRandom::randomInt32(){
    if(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice == nullptr){SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice = SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::eraseType(new std::random_device());}
    const unsigned int randomValue = (*SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice))();
    return (static_cast<int>(randomValue) ^ static_cast<int>(getCurrentTime()));
}

long long SGEXTN::SeerattraNum::TrueRandom::randomInt64(){
    if(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice == nullptr){SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice = SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::eraseType(new std::random_device());}
    const unsigned int randomValue1 = (*SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice))();
    const unsigned int randomValue2 = (*SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice))();
    const unsigned long long randomValue = (static_cast<unsigned long long>(randomValue1) << 32) + static_cast<unsigned long long>(randomValue2);
    return (static_cast<long long>(randomValue) ^ getCurrentTime());
}

unsigned int SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32(){
    return static_cast<unsigned int>(SGEXTN::SeerattraNum::TrueRandom::randomInt32());
}

unsigned long long SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64(){
    return static_cast<unsigned long long>(SGEXTN::SeerattraNum::TrueRandom::randomInt64());
}

float SGEXTN::SeerattraNum::TrueRandom::randomFloat32(){
    if(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice == nullptr){SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice = SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::eraseType(new std::random_device());}
    if(SGEXTN::SeerattraNum::TrueRandom::stlDistributionFloat == nullptr){SGEXTN::SeerattraNum::TrueRandom::stlDistributionFloat = SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<float>>::eraseType(new std::uniform_real_distribution<float>(0.0f, 1.0f));}
    return (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<float>>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::stlDistributionFloat))(*SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice));
}

double SGEXTN::SeerattraNum::TrueRandom::randomFloat64(){
    if(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice == nullptr){SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice = SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::eraseType(new std::random_device());}
    if(SGEXTN::SeerattraNum::TrueRandom::stlDistributionDouble == nullptr){SGEXTN::SeerattraNum::TrueRandom::stlDistributionDouble = SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<double>>::eraseType(new std::uniform_real_distribution<double>(0.0, 1.0));}
    return (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<double>>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::stlDistributionDouble))(*SGEXTN::SeerattraNum::UnsafeCasts<std::random_device>::uneraseType(SGEXTN::SeerattraNum::TrueRandom::stlRandomDevice));
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::TrueRandom::randomInt32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom::randomInt32Array crashed as count is negative");}
    SGEXTN::Containers::Array<int> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::TrueRandom::randomInt32();
    }
    return output;
}

SGEXTN::Containers::Array<long long> SGEXTN::SeerattraNum::TrueRandom::randomInt64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom::randomInt64Array crashed as count is negative");}
    SGEXTN::Containers::Array<long long> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::TrueRandom::randomInt64();
    }
    return output;
}

SGEXTN::Containers::Array<unsigned int> SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array crashed as count is negative");}
    SGEXTN::Containers::Array<unsigned int> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32();
    }
    return output;
}

SGEXTN::Containers::Array<unsigned long long> SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64Array crashed as count is negative");}
    SGEXTN::Containers::Array<unsigned long long> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64();
    }
    return output;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::TrueRandom::randomFloat32Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom::randomFloat32Array crashed as count is negative");}
    SGEXTN::Containers::Array<float> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::TrueRandom::randomFloat32();
    }
    return output;
}

SGEXTN::Containers::Array<double> SGEXTN::SeerattraNum::TrueRandom::randomFloat64Array(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom::randomFloat64Array crashed as count is negative");}
    SGEXTN::Containers::Array<double> output(count);
    for(int i=0; i<count; i++){
        output.at(i) = SGEXTN::SeerattraNum::TrueRandom::randomFloat64();
    }
    return output;
}
