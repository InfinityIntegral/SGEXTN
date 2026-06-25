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

#include <SGEXTN_SeerattraNum_BinomialDistribution.h>
#include <private_api/SGEXTN_SeerattraNum_UnsafeCasts.h>
#include <SGEXTN_SeerattraNum_TrueRandom.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_SeerattraNum_SimpleRandom.h>
#include <random>

template <typename ProbabilityType, typename Integer> SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::BinomialDistribution(bool useGlobal, ProbabilityType chanceOfTrue, Integer attemptCount) : private_chanceOfTrue(chanceOfTrue), private_attemptCount(attemptCount), private_stlRandomEngine(nullptr), private_stlDistribution(SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::eraseType(new std::binomial_distribution<Integer>(attemptCount, chanceOfTrue))){
    if(useGlobal == false){
        SGEXTN::Containers::Array<unsigned int> seedArray = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(8);
        std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + 8);
        private_stlRandomEngine = SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::eraseType(new std::mt19937_64(seedSequence));
    }
}

template <typename ProbabilityType, typename Integer> SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::~BinomialDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution);
}

template <typename ProbabilityType, typename Integer> void SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::seed crashed because cannot seed global rng");}
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + seedArray.length());
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine)).seed(seedSequence);
}

template <typename ProbabilityType, typename Integer> Integer SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename ProbabilityType, typename Integer> SGEXTN::Containers::Array<Integer> SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<Integer> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename ProbabilityType, typename Integer> ProbabilityType SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::getChanceOfTrue() const {
    return private_chanceOfTrue;
}

template <typename ProbabilityType, typename Integer> Integer SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::getAttemptCount() const {
    return private_attemptCount;
}

template <typename ProbabilityType, typename Integer> void SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::setChanceOfTrue(ProbabilityType chanceOfTrue){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setChanceOfTrue crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    private_chanceOfTrue = chanceOfTrue;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution)).param(typename std::binomial_distribution<Integer>::param_type(private_attemptCount, private_chanceOfTrue));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution)).reset();
}

template <typename ProbabilityType, typename Integer> void SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::setAttemptCount(Integer attemptCount){
    if(attemptCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setAttemptCount crashed because the requested number of attempts is negative");}
    private_attemptCount = attemptCount;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution)).param(typename std::binomial_distribution<Integer>::param_type(private_attemptCount, private_chanceOfTrue));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution)).reset();
}

template class SGEXTN::SeerattraNum::BinomialDistribution<float, int>;
template class SGEXTN::SeerattraNum::BinomialDistribution<float, long long>;
template class SGEXTN::SeerattraNum::BinomialDistribution<float, unsigned int>;
template class SGEXTN::SeerattraNum::BinomialDistribution<float, unsigned long long>;
template class SGEXTN::SeerattraNum::BinomialDistribution<double, int>;
template class SGEXTN::SeerattraNum::BinomialDistribution<double, long long>;
template class SGEXTN::SeerattraNum::BinomialDistribution<double, unsigned int>;
template class SGEXTN::SeerattraNum::BinomialDistribution<double, unsigned long long>;
