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

#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Math/IntegerLimits.h>
#include <chrono>
#include <random>

namespace {
std::random_device randomDevice;

long long getCurrentTime(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
}

int SGEXTN::SeerattraNum::TrueRandom::randomInt32(){
    const unsigned int randomValue = randomDevice();
    return static_cast<int>(randomValue ^ static_cast<unsigned int>(getCurrentTime()));
}

long long SGEXTN::SeerattraNum::TrueRandom::randomInt64(){
    const unsigned int randomValue1 = randomDevice();
    const unsigned int randomValue2 = randomDevice();
    const unsigned long long randomValue = (static_cast<unsigned long long>(randomValue1) << 32) + static_cast<unsigned long long>(randomValue2);
    return static_cast<long long>(randomValue ^ static_cast<unsigned long long>(getCurrentTime()));
}

unsigned int SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32(){
    const unsigned int randomValue = randomDevice();
    return (randomValue ^ static_cast<unsigned int>(getCurrentTime()));
}

unsigned long long SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64(){
    const unsigned int randomValue1 = randomDevice();
    const unsigned int randomValue2 = randomDevice();
    const unsigned long long randomValue = (static_cast<unsigned long long>(randomValue1) << 32) + static_cast<unsigned long long>(randomValue2);
    return (randomValue ^ static_cast<unsigned long long>(getCurrentTime()));
}

float SGEXTN::SeerattraNum::TrueRandom::randomFloat32(){
    const double maximum = static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) + 1.0;
    return static_cast<float>(static_cast<double>(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32()) /maximum);
}

double SGEXTN::SeerattraNum::TrueRandom::randomFloat64(){
    const double maximum = static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) + 1.0;
    return (static_cast<double>(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32()) /maximum);
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
