/*
 *   Copyright 2026 05524F.sg
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
// BuildLah license check: SGEXTN 7.0.0

#include <SGEXTN_SeerattraNum_UniformDistributionFloatingPoint.h>
#include <private_api/SGEXTN_SeerattraNum_UnsafeCasts.h>
#include <SGEXTN_SeerattraNum_TrueRandom.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_SeerattraNum_SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::UniformDistributionFloatingPoint(bool useGlobal, FloatingPoint minimum, FloatingPoint maximum) : private_minimum(minimum), private_maximum(maximum), private_stlRandomEngine(nullptr), private_stlDistribution(SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<FloatingPoint>>::eraseType(new std::uniform_real_distribution<FloatingPoint>(minimum, maximum))){
    if(useGlobal == false){
        SGEXTN::Containers::Array<unsigned int> seedArray = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(8);
        std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + 8);
        private_stlRandomEngine = SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::eraseType(new std::mt19937_64(seedSequence));
    }
}

template <typename FloatingPoint> SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::~UniformDistributionFloatingPoint(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::seed crashed because cannot seed global rng");}
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + seedArray.length());
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine)).seed(seedSequence);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::getMinimum() const {
    return private_minimum;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::getMaximum() const {
    return private_maximum;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::setMinimum(FloatingPoint minimum){
    if(minimum > private_maximum){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::setMinimum crashed because minimum is higher than maximum");}
    private_minimum = minimum;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).param(typename std::uniform_real_distribution<FloatingPoint>::param_type(private_minimum, private_maximum));
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<FloatingPoint>::setMaximum(FloatingPoint maximum){
    if(maximum < private_minimum){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::setMaximum crashed because maximum is lower than minimum");}
    private_maximum = maximum;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::uniform_real_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).param(typename std::uniform_real_distribution<FloatingPoint>::param_type(private_minimum, private_maximum));
}

template class SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<float>;
template class SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<double>;
