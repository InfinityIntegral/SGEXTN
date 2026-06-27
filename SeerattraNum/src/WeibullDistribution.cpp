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

#include <SGEXTN/SeerattraNum/WeibullDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename FloatingPoint> SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::WeibullDistribution(bool useGlobal, FloatingPoint failureBehaviour, FloatingPoint characteristicLifespan){
    if(failureBehaviour <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution constructor crashed because requested failure behaviour indicator is nonpositive");}
    if(characteristicLifespan <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution constructor crashed because requested characteristic lifespan is nonpositive");}
    private_failureBehaviour = failureBehaviour;
    private_characteristicLifespan = characteristicLifespan;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::weibull_distribution<FloatingPoint>>::eraseType(new std::weibull_distribution<FloatingPoint>(failureBehaviour, characteristicLifespan));
}

template <typename FloatingPoint> SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::~WeibullDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::weibull_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::weibull_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::getFailureBehaviour() const {
    return private_failureBehaviour;
}

template <typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::getCharacteristicLifespan() const {
    return private_characteristicLifespan;
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::setFailureBehaviour(FloatingPoint failureBehaviour){
    if(failureBehaviour <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::setFailureBehaviour crashed because requested failure behaviour indicator is nonpositive");}
    private_failureBehaviour = failureBehaviour;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::weibull_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::weibull_distribution<FloatingPoint>>::eraseType(new std::weibull_distribution<FloatingPoint>(failureBehaviour, private_characteristicLifespan));
}

template <typename FloatingPoint> void SGEXTN::SeerattraNum::WeibullDistribution<FloatingPoint>::setCharacteristicLifespan(FloatingPoint characteristicLifespan){
    if(characteristicLifespan <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::setCharacteristicLifespan crashed because requested characteristic lifespan is nonpositive");}
    private_characteristicLifespan = characteristicLifespan;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::weibull_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::weibull_distribution<FloatingPoint>>::eraseType(new std::weibull_distribution<FloatingPoint>(private_failureBehaviour, characteristicLifespan));
}

template class SGEXTN::SeerattraNum::WeibullDistribution<float>;
template class SGEXTN::SeerattraNum::WeibullDistribution<double>;
