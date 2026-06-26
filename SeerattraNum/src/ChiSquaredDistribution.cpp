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

#include <SGEXTN/SeerattraNum/ChiSquaredDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::ChiSquaredDistribution<FloatingPoint>::ChiSquaredDistribution(bool useGlobal, FloatingPoint degreesOfFreedom) : private_degreesOfFreedom(degreesOfFreedom), private_stlRandomEngine(SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal)), private_stlDistribution(SGEXTN::SeerattraNum::UnsafeCasts<std::chi_squared_distribution<FloatingPoint>>::eraseType(new std::chi_squared_distribution<FloatingPoint>(degreesOfFreedom))){}

template <typename FloatingPoint> SGEXTN::SeerattraNum::ChiSquaredDistribution<FloatingPoint>::~ChiSquaredDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::chi_squared_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::ChiSquaredDistribution<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::ChiSquaredDistribution<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::chi_squared_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::ChiSquaredDistribution<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::ChiSquaredDistribution<FloatingPoint>::getDegreesOfFreedom() const {
    return private_degreesOfFreedom;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::ChiSquaredDistribution<FloatingPoint>::setDegreesOfFreedom(FloatingPoint degreesOfFreedom){
    if(degreesOfFreedom < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::setDegreesOfFreedom crashed because requested number of degrees of freedom is negative");}
    private_degreesOfFreedom = degreesOfFreedom;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::chi_squared_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).param(typename std::chi_squared_distribution<FloatingPoint>::param_type(private_degreesOfFreedom));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::chi_squared_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).reset();
}

template class SGEXTN::SeerattraNum::ChiSquaredDistribution<float>;
template class SGEXTN::SeerattraNum::ChiSquaredDistribution<double>;
