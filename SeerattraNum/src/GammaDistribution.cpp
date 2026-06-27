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

#include <SGEXTN/SeerattraNum/GammaDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::GammaDistribution(bool useGlobal, FloatingPoint variableCount, FloatingPoint variableMean){
    if(variableCount <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution constructor crashed because requested number of exponentially distributed variables to sum is nonpositive");}
    if(variableMean <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution constructor crashed because requested mean of each exponentially distributed variable is nonpositive");}
    private_variableCount = variableCount;
    private_variableMean = variableMean;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::gamma_distribution<FloatingPoint>>::eraseType(new std::gamma_distribution<FloatingPoint>(variableCount, variableMean));
}

template <typename FloatingPoint> SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::~GammaDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::gamma_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::gamma_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::getVariableCount() const {
    return private_variableCount;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::getVariableMean() const {
    return private_variableMean;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::setVariableCount(FloatingPoint variableCount){
    if(variableCount <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::setVariableCount crashed because requested number of exponentially distributed variables to sum is nonpositive");}
    private_variableCount = variableCount;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::gamma_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::gamma_distribution<FloatingPoint>>::eraseType(new std::gamma_distribution<FloatingPoint>(variableCount, private_variableMean));
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::GammaDistribution<FloatingPoint>::setVariableMean(FloatingPoint variableMean){
    if(variableMean <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::setVariableMean crashed because requested mean of each exponentially distributed variable is nonpositive");}
    private_variableMean = variableMean;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::gamma_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::gamma_distribution<FloatingPoint>>::eraseType(new std::gamma_distribution<FloatingPoint>(private_variableCount, variableMean));
}

template class SGEXTN::SeerattraNum::GammaDistribution<float>;
template class SGEXTN::SeerattraNum::GammaDistribution<double>;
