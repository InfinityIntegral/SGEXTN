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

#include <SGEXTN/SeerattraNum/WeightedPiecewiseLinearDistribution.h>
#include <SGEXTN/SeerattraNum/private_api/UnsafeCasts.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <random>

template <typename WeightType, typename FloatingPoint> SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<WeightType, FloatingPoint>::WeightedPiecewiseLinearDistribution(bool useGlobal, const SGEXTN::Containers::Array<WeightType>& weights, const SGEXTN::Containers::Array<FloatingPoint>& boundaries){
    if(boundaries.length() < 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution constructor crashed because listed boundaries do not form at least 1 valid interval");}
    if(boundaries.length() != weights.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution constructor crashed because the length of the boudaries array is not equal to the length of the weights array");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution constructor crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution constructor crashed because all of the weights are zero");}
    for(int i=0; i<boundaries.length()-1; i++){
        if(boundaries.at(i) >= boundaries.at(i + 1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution constructor crashed because the boundaries array is not strictly increasing");}
    }
    private_weights = weights;
    private_boundaries = boundaries;
    private_stlRandomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_createRandomEngine(useGlobal);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::piecewise_linear_distribution<FloatingPoint>>::eraseType(new std::piecewise_linear_distribution<FloatingPoint>(&boundaries.at(0), &boundaries.at(0) + boundaries.length(), &weights.at(0)));
}

template <typename WeightType, typename FloatingPoint> SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<WeightType, FloatingPoint>::~WeightedPiecewiseLinearDistribution(){
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(private_stlRandomEngine);
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::piecewise_linear_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
}

template <typename WeightType, typename FloatingPoint> void SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<WeightType, FloatingPoint>::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_stlRandomEngine == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::SimpleRandom::private_seedRandomEngine(private_stlRandomEngine, seedArray);
}

template <typename WeightType, typename FloatingPoint> FloatingPoint SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<WeightType, FloatingPoint>::randomValue(){
    void* randomEngine = private_stlRandomEngine;
    if(randomEngine == nullptr){randomEngine = SGEXTN::SeerattraNum::SimpleRandom::private_getRandomEngine();}
    return ((*SGEXTN::SeerattraNum::UnsafeCasts<std::piecewise_linear_distribution<FloatingPoint>>::uneraseType(private_stlDistribution))(*SGEXTN::SeerattraNum::UnsafeCasts<std::mt19937_64>::uneraseType(randomEngine)));
}

template <typename WeightType, typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<WeightType, FloatingPoint>::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::randomIndexArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<FloatingPoint> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

template <typename WeightType, typename FloatingPoint> SGEXTN::Containers::Array<WeightType> SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<WeightType, FloatingPoint>::getWeights() const {
    return private_weights;
}

template <typename WeightType, typename FloatingPoint> SGEXTN::Containers::Array<FloatingPoint> SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<WeightType, FloatingPoint>::getBoundaries() const {
    return private_boundaries;
}

template <typename WeightType, typename FloatingPoint> void SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<WeightType, FloatingPoint>::setWeightsAndBoundaries(const SGEXTN::Containers::Array<WeightType>& weights, const SGEXTN::Containers::Array<FloatingPoint>& boundaries){
    if(boundaries.length() < 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::setWeightsAndBoundaries crashed because listed boundaries do not form at least 1 valid interval");}
    if(boundaries.length() != weights.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::setWeightsAndBoundaries crashed because the length of the boudaries array is not equal to the length of the weights array");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::setWeightsAndBoundaries crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::setWeightsAndBoundaries crashed because all of the weights are zero");}
    for(int i=0; i<boundaries.length()-1; i++){
        if(boundaries.at(i) >= boundaries.at(i + 1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::setWeightsAndBoundaries crashed because the boundaries array is not strictly increasing");}
    }
    private_weights = weights;
    private_boundaries = boundaries;
    delete SGEXTN::SeerattraNum::UnsafeCasts<std::piecewise_linear_distribution<FloatingPoint>>::uneraseType(private_stlDistribution);
    private_stlDistribution = SGEXTN::SeerattraNum::UnsafeCasts<std::piecewise_linear_distribution<FloatingPoint>>::eraseType(new std::piecewise_linear_distribution<FloatingPoint>(&boundaries.at(0), &boundaries.at(0) + boundaries.length(), &weights.at(0)));
}

template class SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<float, float>;
template class SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<float, double>;
template class SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<double, float>;
template class SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<double, double>;
