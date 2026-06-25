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

#include <SGEXTN/SeerattraNum/DirectInteger.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename Integer> SGEXTN::SeerattraNum::DirectInteger<Integer>::DirectInteger(bool useGlobal) : private_stlRandomEngine(SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal)){}

template <typename Integer> SGEXTN::SeerattraNum::DirectInteger<Integer>::~DirectInteger(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
}

template <typename Integer> void SGEXTN::SeerattraNum::DirectInteger<Integer>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename Integer> Integer SGEXTN::SeerattraNum::DirectInteger<Integer>::randomInteger(){
    if(private_stlRandomEngine == nullptr){return static_cast<Integer>(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64());}
    return static_cast<Integer>((*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine))());
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
