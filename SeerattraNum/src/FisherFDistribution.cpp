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

#include <SGEXTN/SeerattraNum/FisherFDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::FisherFDistribution(bool useGlobal, FloatingPoint numeratorDegreesOfFreedom, FloatingPoint denominatorDegreesOfFreedom) : private_numeratorDegreesOfFreedom(numeratorDegreesOfFreedom), private_denominatorDegreesOfFreedom(denominatorDegreesOfFreedom), private_stlRandomEngine(SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal)), private_stlDistribution(SGEXTN::SeerattraNum::UnsafeCasts<std::fisher_f_distribution<FloatingPoint>>::eraseType(new std::fisher_f_distribution<FloatingPoint>(numeratorDegreesOfFreedom, denominatorDegreesOfFreedom))){}

template <typename FloatingPoint> SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::~FisherFDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::fisher_f_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::fisher_f_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::getNumeratorDegreesOfFreedom() const {
    return private_numeratorDegreesOfFreedom;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::getDenominatorDegreesOfFreedom() const {
    return private_denominatorDegreesOfFreedom;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::setNumeratorDegreesOfFreedom(FloatingPoint numeratorDegreesOfFreedom){
    if(numeratorDegreesOfFreedom < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::setNumeratorDegreesOfFreedom crashed because requested number of degrees of freedom in the numerator is negative");}
    private_numeratorDegreesOfFreedom = numeratorDegreesOfFreedom;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::fisher_f_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).param(typename std::fisher_f_distribution<FloatingPoint>::param_type(private_numeratorDegreesOfFreedom, private_denominatorDegreesOfFreedom));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::fisher_f_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).reset();
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::FisherFDistribution<FloatingPoint>::setDenominatorDegreesOfFreedom(FloatingPoint denominatorDegreesOfFreedom){
    if(denominatorDegreesOfFreedom < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::setDenominatorDegreesOfFreedom crashed because requested number of degrees of freedom in the denominator is negative");}
    private_denominatorDegreesOfFreedom = denominatorDegreesOfFreedom;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::fisher_f_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).param(typename std::fisher_f_distribution<FloatingPoint>::param_type(private_numeratorDegreesOfFreedom, private_denominatorDegreesOfFreedom));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::fisher_f_distribution<FloatingPoint>>::uneraseType(private_stlDistribution)).reset();
}

template class SGEXTN::SeerattraNum::FisherFDistribution<float>;
template class SGEXTN::SeerattraNum::FisherFDistribution<double>;
