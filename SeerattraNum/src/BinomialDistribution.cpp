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

#include <SGEXTN/SeerattraNum/BinomialDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename ProbabilityType, typename Integer> SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::BinomialDistribution(bool useGlobal, ProbabilityType chanceOfTrue, Integer attemptCount){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested probability is higher than 1");}
    if(attemptCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested number of attempts is negative");}
    private_chanceOfTrue = chanceOfTrue;
    private_attemptCount = attemptCount;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::eraseType(new std::binomial_distribution<Integer>(attemptCount, chanceOfTrue));
}

template <typename ProbabilityType, typename Integer> SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::~BinomialDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution);
}

template <typename ProbabilityType, typename Integer> void SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
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
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::eraseType(new std::binomial_distribution<Integer>(private_attemptCount, chanceOfTrue));
}

template <typename ProbabilityType, typename Integer> void SGEXTN::SeerattraNum::BinomialDistribution<ProbabilityType, Integer>::setAttemptCount(Integer attemptCount){
    if(attemptCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setAttemptCount crashed because the requested number of attempts is negative");}
    private_attemptCount = attemptCount;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::binomial_distribution<Integer>>::eraseType(new std::binomial_distribution<Integer>(attemptCount, private_chanceOfTrue));
}

template class SGEXTN::SeerattraNum::BinomialDistribution<float, int>;
template class SGEXTN::SeerattraNum::BinomialDistribution<float, long long>;
template class SGEXTN::SeerattraNum::BinomialDistribution<float, unsigned int>;
template class SGEXTN::SeerattraNum::BinomialDistribution<float, unsigned long long>;
template class SGEXTN::SeerattraNum::BinomialDistribution<double, int>;
template class SGEXTN::SeerattraNum::BinomialDistribution<double, long long>;
template class SGEXTN::SeerattraNum::BinomialDistribution<double, unsigned int>;
template class SGEXTN::SeerattraNum::BinomialDistribution<double, unsigned long long>;
