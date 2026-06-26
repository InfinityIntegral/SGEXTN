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

#include <SGEXTN/SeerattraNum/CauchyDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::CauchyDistribution(bool useGlobal, FloatingPoint median, FloatingPoint halfWidth){
    if(halfWidth <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution constructor crashed because requested half width is nonpositive");}
    private_median = median;
    private_halfWidth = halfWidth;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::cauchy_distribution<FloatingPoint>>::eraseType(new std::cauchy_distribution<FloatingPoint>(median, halfWidth));
}

template <typename FloatingPoint> SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::~CauchyDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::cauchy_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::cauchy_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::getMedian() const {
    return private_median;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::getHalfWidth() const {
    return private_halfWidth;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::setMedian(FloatingPoint median){
    private_median = median;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::cauchy_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).param(typename std::cauchy_distribution<FloatingPoint>::param_type(private_median, private_halfWidth));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::cauchy_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).reset();
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::CauchyDistribution<FloatingPoint>::setHalfWidth(FloatingPoint halfWidth){
    if(halfWidth <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution::setHalfWidth crashed because requested half width is nonpositive");}
    private_halfWidth = halfWidth;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::cauchy_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).param(typename std::cauchy_distribution<FloatingPoint>::param_type(private_median, private_halfWidth));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::cauchy_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).reset();
}

template class SGEXTN::SeerattraNum::CauchyDistribution<float>;
template class SGEXTN::SeerattraNum::CauchyDistribution<double>;
