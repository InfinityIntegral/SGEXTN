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

#include <SGEXTN/SeerattraNum/LogNormalDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::LogNormalDistribution(bool useGlobal, FloatingPoint meanOfLn, FloatingPoint standardDeviationOfLn){
    if(standardDeviationOfLn <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution constructor crashed because requested standard deviation is nonpositive");}
    private_meanOfLn = meanOfLn;
    private_standardDeviationOfLn = standardDeviationOfLn;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::lognormal_distribution<FloatingPoint>>::eraseType(new std::lognormal_distribution<FloatingPoint>(meanOfLn, standardDeviationOfLn));
}

template <typename FloatingPoint> SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::~LogNormalDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::lognormal_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::lognormal_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::getMeanOfLn() const {
    return private_meanOfLn;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::getStandardDeviationOfLn() const {
    return private_standardDeviationOfLn;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::setMeanOfLn(FloatingPoint meanOfLn){
    private_meanOfLn = meanOfLn;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::lognormal_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::lognormal_distribution<FloatingPoint>>::eraseType(new std::lognormal_distribution<FloatingPoint>(meanOfLn, private_standardDeviationOfLn));
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::LogNormalDistribution<FloatingPoint>::setStandardDeviationOfLn(FloatingPoint standardDeviationOfLn){
    if(standardDeviationOfLn <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution::setStandardDeviationOfLn crashed because requested standard deviation is nonpositive");}
    private_standardDeviationOfLn = standardDeviationOfLn;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::lognormal_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::lognormal_distribution<FloatingPoint>>::eraseType(new std::lognormal_distribution<FloatingPoint>(private_meanOfLn, standardDeviationOfLn));
}

template class SGEXTN::SeerattraNum::LogNormalDistribution<float>;
template class SGEXTN::SeerattraNum::LogNormalDistribution<double>;
