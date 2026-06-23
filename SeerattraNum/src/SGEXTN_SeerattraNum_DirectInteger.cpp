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

#include <SGEXTN_SeerattraNum_DirectInteger.h>
#include <private_api/SGEXTN_SeerattraNum_UnsafeCasts.h>
#include <SGEXTN_SeerattraNum_TrueRandom.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_SeerattraNum_SimpleRandom.h>
#include <random>

template <typename Integer> SGEXTN::SeerattraNum::DirectInteger<Integer>::DirectInteger(bool useGlobal) : stlRandomEngine(nullptr){
    if(useGlobal == false){
        SGEXTN::Containers::Array<unsigned int> seedArray = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(8);
        std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + 8);
        stlRandomEngine = SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::eraseType(new std::mt19937_64(seedSequence));
    }
}

template <typename Integer> SGEXTN::SeerattraNum::DirectInteger<Integer>::~DirectInteger(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(stlRandomEngine);
}

template <typename Integer> void SGEXTN::SeerattraNum::DirectInteger<Integer>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger::seed crashed because cannot seed global rng");}
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + seedArray.length());
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(stlRandomEngine)).seed(seedSequence);
}

template <typename Integer> Integer SGEXTN::SeerattraNum::DirectInteger<Integer>::randomInteger(){
    if(stlRandomEngine == nullptr){return static_cast<Integer>(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64());}
    return static_cast<Integer>((*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(stlRandomEngine))());
}

template <typename Integer> SGEXTN::Containers::Array<Integer> SGEXTN::SeerattraNum::DirectInteger<Integer>::randomIntegerArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger::randomIntegerArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<Integer> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomInteger();
    }
    return outputArray;
}

template class SGEXTN::SeerattraNum::DirectInteger<int>;
template class SGEXTN::SeerattraNum::DirectInteger<long long>;
template class SGEXTN::SeerattraNum::DirectInteger<unsigned int>;
template class SGEXTN::SeerattraNum::DirectInteger<unsigned long long>;
