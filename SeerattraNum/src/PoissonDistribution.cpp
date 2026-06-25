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

#include <SGEXTN/SeerattraNum/PoissonDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename MeanType, typename Integer> SGEXTN::SeerattraNum::PoissonDistribution<MeanType, Integer>::PoissonDistribution(bool useGlobal, MeanType mean) : private_mean(mean), private_stlRandomEngine(SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal)), private_stlDistribution(SGEXTN::SeerattraNum::UnsafeCasts<std::poisson_distribution<Integer>>::eraseType(new std::poisson_distribution<Integer>(mean))){}

template <typename MeanType, typename Integer> SGEXTN::SeerattraNum::PoissonDistribution<MeanType, Integer>::~PoissonDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::poisson_distribution<Integer>>::uneraseType(private_stlDistribution);
}

template <typename MeanType, typename Integer> void SGEXTN::SeerattraNum::PoissonDistribution<MeanType, Integer>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename MeanType, typename Integer> Integer SGEXTN::SeerattraNum::PoissonDistribution<MeanType, Integer>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::poisson_distribution<Integer>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename MeanType, typename Integer> SGEXTN::Containers::Array<Integer> SGEXTN::SeerattraNum::PoissonDistribution<MeanType, Integer>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<Integer> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename MeanType, typename Integer> MeanType SGEXTN::SeerattraNum::PoissonDistribution<MeanType, Integer>::getMean() const {
    return private_mean;
}

template <typename MeanType, typename Integer> void SGEXTN::SeerattraNum::PoissonDistribution<MeanType, Integer>::setMean(MeanType mean){
    if(mean < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::setMean crashed because requested mean is negative");}
    private_mean = mean;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::poisson_distribution<Integer>>::uneraseType(private_stlDistribution)).param(typename std::poisson_distribution<Integer>::param_type(private_mean));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::poisson_distribution<Integer>>::uneraseType(private_stlDistribution)).reset();
}

template class SGEXTN::SeerattraNum::PoissonDistribution<float, int>;
template class SGEXTN::SeerattraNum::PoissonDistribution<float, long long>;
template class SGEXTN::SeerattraNum::PoissonDistribution<float, unsigned int>;
template class SGEXTN::SeerattraNum::PoissonDistribution<float, unsigned long long>;
template class SGEXTN::SeerattraNum::PoissonDistribution<double, int>;
template class SGEXTN::SeerattraNum::PoissonDistribution<double, long long>;
template class SGEXTN::SeerattraNum::PoissonDistribution<double, unsigned int>;
template class SGEXTN::SeerattraNum::PoissonDistribution<double, unsigned long long>;
