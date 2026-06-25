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

#include <SGEXTN/SeerattraNum/UniformDistributionInteger.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename Integer> SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::UniformDistributionInteger(bool useGlobal, Integer inclusiveMin, Integer inclusiveMax) : private_inclusiveMin(inclusiveMin), private_inclusiveMax(inclusiveMax), private_stlRandomEngine(nullptr), private_stlDistribution(SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_int_distribution<Integer>>::eraseType(new std::uniform_int_distribution<Integer>(inclusiveMin, inclusiveMax))){
    if(useGlobal == false){
        SGEXTN::Containers::Array<unsigned int> seedArray = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(8);
        std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + 8);
        private_stlRandomEngine = SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::eraseType(new std::mt19937_64(seedSequence));
    }
}

template <typename Integer> SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::~UniformDistributionInteger(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_int_distribution<Integer>>::uneraseType(private_stlDistribution);
}

template <typename Integer> void SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::seed crashed because cannot seed global rng");}
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + seedArray.length());
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine)).seed(seedSequence);
}

template <typename Integer> Integer SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_int_distribution<Integer>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename Integer> SGEXTN::Containers::Array<Integer> SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<Integer> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename Integer> Integer SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::getInclusiveMin() const {
    return private_inclusiveMin;
}

template <typename Integer> Integer SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::getInclusiveMax() const {
    return private_inclusiveMax;
}

template <typename Integer> void SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::setInclusiveMin(Integer inclusiveMin){
    if(inclusiveMin > private_inclusiveMax){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::setInclusiveMin crashed because minimum is higher than maximum");}
    private_inclusiveMin = inclusiveMin;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_int_distribution<Integer>>::uneraseType(private_stlDistribution)).param(typename std::uniform_int_distribution<Integer>::param_type(private_inclusiveMin, private_inclusiveMax));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_int_distribution<Integer>>::uneraseType(private_stlDistribution)).reset();
}

template <typename Integer> void SGEXTN::SeerattraNum::UniformDistributionInteger<Integer>::setInclusiveMax(Integer inclusiveMax){
    if(inclusiveMax < private_inclusiveMin){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::setInclusiveMax crashed because maximum is lower than minimum");}
    private_inclusiveMax = inclusiveMax;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_int_distribution<Integer>>::uneraseType(private_stlDistribution)).param(typename std::uniform_int_distribution<Integer>::param_type(private_inclusiveMin, private_inclusiveMax));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_int_distribution<Integer>>::uneraseType(private_stlDistribution)).reset();
}

template class SGEXTN::SeerattraNum::UniformDistributionInteger<int>;
template class SGEXTN::SeerattraNum::UniformDistributionInteger<long long>;
template class SGEXTN::SeerattraNum::UniformDistributionInteger<unsigned int>;
template class SGEXTN::SeerattraNum::UniformDistributionInteger<unsigned long long>;
