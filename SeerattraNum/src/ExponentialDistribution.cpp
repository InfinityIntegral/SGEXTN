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

#include <SGEXTN/SeerattraNum/ExponentialDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::ExponentialDistribution<FloatingPoint>::ExponentialDistribution(bool useGlobal, FloatingPoint meanEventsPerTime){
    if(meanEventsPerTime <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution constructor crashed because requested number of events occurring in each unit time is nonpositive");}
    private_meanEventsPerTime = meanEventsPerTime;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::exponential_distribution<FloatingPoint>>::eraseType(new std::exponential_distribution<FloatingPoint>(meanEventsPerTime));
}

template <typename FloatingPoint> SGEXTN::SeerattraNum::ExponentialDistribution<FloatingPoint>::~ExponentialDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::exponential_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::ExponentialDistribution<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::ExponentialDistribution<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::exponential_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::ExponentialDistribution<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::ExponentialDistribution<FloatingPoint>::getMeanEventsPerTime() const {
    return private_meanEventsPerTime;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::ExponentialDistribution<FloatingPoint>::setMeanEventsPerTime(FloatingPoint meanEventsPerTime){
    if(meanEventsPerTime <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::setMeanEventsPerTime crashed because requested number of events occurring in each unit time is nonpositive");}
    private_meanEventsPerTime = meanEventsPerTime;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::exponential_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).param(typename std::exponential_distribution<FloatingPoint>::param_type(private_meanEventsPerTime));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::exponential_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).reset();
}

template class SGEXTN::SeerattraNum::ExponentialDistribution<float>;
template class SGEXTN::SeerattraNum::ExponentialDistribution<double>;
