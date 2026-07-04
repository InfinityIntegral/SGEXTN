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
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>

SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::WeightedPiecewiseLinearDistribution(bool useGlobal, const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries) : private_weights(weights), private_boundaries(boundaries), private_prefixSums(0), private_rng(nullptr), private_ownsRng(useGlobal == false){
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
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
    private_updatePrefixSums();
}

SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::~WeightedPiecewiseLinearDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::private_updatePrefixSums(){
    private_prefixSums = SGEXTN::Containers::Array<float>(private_weights.length());
    private_prefixSums.at(0) = 0.0f;
    for(int i=1; i<private_weights.length(); i++){
        private_prefixSums.at(i) = private_prefixSums.at(i - 1) + (private_boundaries.at(i) - private_boundaries.at(i - 1)) * (private_weights.at(i - 1) + private_weights.at(i)) / 2;
    }
    for(int i=0; i<private_prefixSums.length(); i++){
        private_prefixSums.at(i) /= private_prefixSums.at(private_weights.length() - 1);
    }
}

void SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

float SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    float rng = (*private_rng).randomFloat32();
    int low = 0;
    int high = private_weights.length() - 1;
    while(high - low > 1){
        const int middle = low + (high - low) / 2;
        if(private_prefixSums.at(middle) >= rng){high = middle;}
        else{low = middle;}
    }
    rng = (rng - private_prefixSums.at(low)) / (private_prefixSums.at(low + 1) - private_prefixSums.at(low));
    const float k1 = private_weights.at(low);
    const float k2 = private_weights.at(low + 1);
    const float y = (*private_rng).randomFloat32() * (k1 + k2);
    const float boundary = k1 + rng * (k2 - k1);
    if(y <= boundary){return (private_boundaries.at(low) + rng * (private_boundaries.at(low + 1) - private_boundaries.at(low)));}
    return (private_boundaries.at(low + 1) + rng * (private_boundaries.at(low) - private_boundaries.at(low + 1)));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::getWeights() const {
    return private_weights;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::getBoundaries() const {
    return private_boundaries;
}

void SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution::setWeightsAndBoundaries(const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries){
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
    private_updatePrefixSums();
}
