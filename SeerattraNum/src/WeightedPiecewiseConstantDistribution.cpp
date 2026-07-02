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

#include <SGEXTN/SeerattraNum/WeightedPiecewiseConstantDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>

SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::WeightedPiecewiseConstantDistribution(bool useGlobal, const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries) : private_weights(weights), private_boundaries(boundaries), private_prefixSums(0), private_rng(nullptr), private_ownsRng(useGlobal == false){
    if(weights.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because the array of weights is empty");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because all of the weights are zero");}
    if(boundaries.length() != weights.length() + 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because the length of the boudaries array is not one more than the length of the weights array");}
    for(int i=0; i<boundaries.length()-1; i++){
        if(boundaries.at(i) >= boundaries.at(i + 1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because the boundaries array is not strictly increasing");}
    }
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
    private_updatePrefixSums();
}

SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::~WeightedPiecewiseConstantDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::private_updatePrefixSums(){
    private_prefixSums = SGEXTN::Containers::Array<float>(private_weights.length() + 1);
    private_prefixSums.at(0) = 0.0f;
    for(int i=0; i<private_weights.length(); i++){
        private_prefixSums.at(i + 1) = private_prefixSums.at(i) + private_weights.at(i) * (private_boundaries.at(i + 1) - private_boundaries.at(i));
    }
    for(int i=0; i<private_prefixSums.length(); i++){
        private_prefixSums.at(i) /= private_prefixSums.at(private_weights.length());
    }
}

void SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

float SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    float rng = (*private_rng).randomFloat32();
    int low = 0;
    int high = private_weights.length();
    while(high - low > 1){
        int middle = low + (high - low) / 2;
        if(private_prefixSums.at(middle) >= rng){high = middle;}
        else{low = middle;}
    }
    rng = (rng - private_prefixSums.at(low)) / (private_prefixSums.at(low + 1) - private_prefixSums.at(low));
    return private_boundaries.at(low) + rng * (private_boundaries.at(low + 1) - private_boundaries.at(low));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::getWeights() const {
    return private_weights;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::getBoundaries() const {
    return private_boundaries;
}

void SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries(const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries){
    if(weights.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because the array of weights is empty");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because all of the weights are zero");}
    if(boundaries.length() != weights.length() + 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because the length of the boudaries array is not one more than the length of the weights array");}
    for(int i=0; i<boundaries.length()-1; i++){
        if(boundaries.at(i) >= boundaries.at(i + 1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because the boundaries array is not strictly increasing");}
    }
    private_weights = weights;
    private_boundaries = boundaries;
    private_updatePrefixSums();
}
