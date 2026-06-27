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

#include <SGEXTN/SeerattraNum/NormalDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::NormalDistribution(bool useGlobal, FloatingPoint mean, FloatingPoint standardDeviation){
    if(standardDeviation <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution constructor crashed because requested standard deviation is nonpositive");}
    private_mean = mean;
    private_standardDeviation = standardDeviation;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::normal_distribution<FloatingPoint>>::eraseType(new std::normal_distribution<FloatingPoint>(mean, standardDeviation));
}

template <typename FloatingPoint> SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::~NormalDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::normal_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::normal_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::getMean() const {
    return private_mean;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::getStandardDeviation() const {
    return private_standardDeviation;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::setMean(FloatingPoint mean){
    private_mean = mean;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::normal_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::normal_distribution<FloatingPoint>>::eraseType(new std::normal_distribution<FloatingPoint>(mean, private_standardDeviation));
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::NormalDistribution<FloatingPoint>::setStandardDeviation(FloatingPoint standardDeviation){
    if(standardDeviation <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::setStandardDeviation crashed because requested standard deviation is nonpositive");}
    private_standardDeviation = standardDeviation;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::normal_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::normal_distribution<FloatingPoint>>::eraseType(new std::normal_distribution<FloatingPoint>(private_mean, standardDeviation));
}

template class SGEXTN::SeerattraNum::NormalDistribution<float>;
template class SGEXTN::SeerattraNum::NormalDistribution<double>;
