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

#include <SGEXTN/SeerattraNum/WeightedIndexSelectionDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename WeightType> SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<WeightType>::WeightedIndexSelectionDistribution(bool useGlobal, const SGEXTN::Containers::Array<WeightType>& weights){
    if(weights.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightIndexSelectionDistribution constructor crashed because the array of weights is empty");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution constructor crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightIndexSelectionDistribution constructor crashed because all of the weights are zero");}
    private_weights = weights;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::discrete_distribution<int>>::eraseType(new std::discrete_distribution<int>(&weights.at(0), &weights.at(0) + weights.length()));
}

template <typename WeightType> SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<WeightType>::~WeightedIndexSelectionDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::discrete_distribution<int>>::uneraseType(private_stlDistribution);
}

template <typename WeightType> void SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<WeightType>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename WeightType> int SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<WeightType>::randomIndex(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::discrete_distribution<int>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename WeightType> SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<WeightType>::randomIndexArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::randomIndexArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomIndex();
    }
    return outputArray;
}

template <typename WeightType> SGEXTN::Containers::Array<WeightType> SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<WeightType>::getWeights() const {
    return private_weights;
}

template <typename WeightType> void SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<WeightType>::setWeights(const SGEXTN::Containers::Array<WeightType>& weights){
    if(weights.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightIndexSelectionDistribution::setWeights crashed because the array of weights is empty");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::setWeights crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightIndexSelectionDistribution::setWeights crashed because all of the weights are zero");}
    private_weights = weights;
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::discrete_distribution<int>>::uneraseType(private_stlDistribution)).param(typename std::discrete_distribution<int>::param_type(&weights.at(0), &weights.at(0) + weights.length()));
    (*SGEXTN::SeerattraNum::UnsafeCasts<std::discrete_distribution<int>>::uneraseType(private_stlDistribution)).reset();
}

template class SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<float>;
template class SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<double>;
