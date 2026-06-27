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

#include <SGEXTN/SeerattraNum/BernoulliDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename ProbabilityType> SGEXTN::SeerattraNum::BernoulliDistribution<ProbabilityType>::BernoulliDistribution(bool useGlobal, ProbabilityType chanceOfTrue){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution constructor crashed because the requested probability is higher than 1");}
    private_chanceOfTrue = chanceOfTrue;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::bernoulli_distribution>::eraseType(new std::bernoulli_distribution(chanceOfTrue));
}

template <typename ProbabilityType> SGEXTN::SeerattraNum::BernoulliDistribution<ProbabilityType>::~BernoulliDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::bernoulli_distribution>::uneraseType(private_stlDistribution);
}

template <typename ProbabilityType> void SGEXTN::SeerattraNum::BernoulliDistribution<ProbabilityType>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename ProbabilityType> bool SGEXTN::SeerattraNum::BernoulliDistribution<ProbabilityType>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::bernoulli_distribution>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename ProbabilityType> SGEXTN::Containers::Array<bool> SGEXTN::SeerattraNum::BernoulliDistribution<ProbabilityType>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<bool> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename ProbabilityType> ProbabilityType SGEXTN::SeerattraNum::BernoulliDistribution<ProbabilityType>::getChanceOfTrue() const {
    return private_chanceOfTrue;
}

template <typename ProbabilityType> void SGEXTN::SeerattraNum::BernoulliDistribution<ProbabilityType>::setChanceOfTrue(ProbabilityType chanceOfTrue){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::setChanceOfTrue crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    private_chanceOfTrue = chanceOfTrue;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::bernoulli_distribution>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::bernoulli_distribution>::eraseType(new std::bernoulli_distribution(chanceOfTrue));
}

template class SGEXTN::SeerattraNum::BernoulliDistribution<float>;
template class SGEXTN::SeerattraNum::BernoulliDistribution<double>;
