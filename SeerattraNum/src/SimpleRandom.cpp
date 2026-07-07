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
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>

SGEXTN::SeerattraNum::DirectRandom* SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance = nullptr;

int SGEXTN::SeerattraNum::SimpleRandom::randomInt32(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance == nullptr){SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance = new SGEXTN::SeerattraNum::DirectRandom();}
    return (*SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance).randomInt32();
}

long long SGEXTN::SeerattraNum::SimpleRandom::randomInt64(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance == nullptr){SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance = new SGEXTN::SeerattraNum::DirectRandom();}
    return (*SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance).randomInt64();
}

unsigned int SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance == nullptr){SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance = new SGEXTN::SeerattraNum::DirectRandom();}
    return (*SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance).randomUnsignedInt32();
}

unsigned long long SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance == nullptr){SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance = new SGEXTN::SeerattraNum::DirectRandom();}
    return (*SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance).randomUnsignedInt64();
}

float SGEXTN::SeerattraNum::SimpleRandom::randomFloat32(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance == nullptr){SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance = new SGEXTN::SeerattraNum::DirectRandom();}
    return (*SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance).randomFloat32();
}

double SGEXTN::SeerattraNum::SimpleRandom::randomFloat64(){
    if(SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance == nullptr){SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance = new SGEXTN::SeerattraNum::DirectRandom();}
    return (*SGEXTN::SeerattraNum::SimpleRandom::private_globalInstance).randomFloat64();
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
