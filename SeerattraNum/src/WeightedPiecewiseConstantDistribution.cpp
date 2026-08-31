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
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::WeightedPiecewiseConstantDistribution() : SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution(true, SGEXTN::Containers::Array<float>(1, 1.0f), SGEXTN::Containers::Array<float>({0.0f, 1.0f})){}

SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::WeightedPiecewiseConstantDistribution(bool useGlobal, const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries) : weights_(weights), boundaries_(boundaries), rngLocator_(useGlobal){
    if(weights.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because the array of weights is empty");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0f){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because all of the weights are zero");}
    if(boundaries.length() != weights.length() + 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because the length of the boudaries array is not one more than the length of the weights array");}
    for(int i=0; i<boundaries.length()-1; i++){
        if(boundaries.at(i) >= boundaries.at(i + 1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution constructor crashed because the boundaries array is not strictly increasing");}
    }
    updatePrefixSums();
}

bool SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::sendOut(const SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>, SGEXTN::Containers::Array<float>>::sendOut(x.rngLocator_, x.weights_, x.boundaries_, data);
}

bool SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::sendIn(SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    SGEXTN::Containers::Array<float> weights;
    SGEXTN::Containers::Array<float> boundaries;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>, SGEXTN::Containers::Array<float>>::sendIn(rngLocator, weights, boundaries, data);
    if(isValid == false || weights.length() == 0 || boundaries.length() != weights.length() + 1){return false;}
    bool allZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0f){return false;}
        if(weights.at(i) > 0.0f){allZero = false;}
    }
    if(allZero == true){return false;}
    for(int i=0; i<boundaries.length()-1; i++){
        if(boundaries.at(i) >= boundaries.at(i + 1)){return false;}
    }
    x = SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution(true, weights, boundaries);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::sizeOut(const SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>, SGEXTN::Containers::Array<float>>::sizeOut(x.rngLocator_, x.weights_, x.boundaries_);
}

int SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>, SGEXTN::Containers::Array<float>>::sizeIn(data);
}

void SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::updatePrefixSums(){
    prefixSums_ = SGEXTN::Containers::Array<float>(weights_.length() + 1, 0.0f);
    prefixSums_.at(0) = 0.0f;
    for(int i=0; i<weights_.length(); i++){
        prefixSums_.at(i + 1) = prefixSums_.at(i) + weights_.at(i) * (boundaries_.at(i + 1) - boundaries_.at(i));
    }
    for(int i=0; i<prefixSums_.length(); i++){
        prefixSums_.at(i) /= prefixSums_.at(weights_.length());
    }
}

void SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

float SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::randomValue(){
    float rng = (*rngLocator_).randomFloat32();
    int low = 0;
    int high = weights_.length();
    while(high - low > 1){
        const int middle = low + (high - low) / 2;
        if(prefixSums_.at(middle) >= rng){high = middle;}
        else{low = middle;}
    }
    rng = (rng - prefixSums_.at(low)) / (prefixSums_.at(low + 1) - prefixSums_.at(low));
    return boundaries_.at(low) + rng * (boundaries_.at(low + 1) - boundaries_.at(low));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count, 0.0f);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::getWeights() const {
    return weights_;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::getBoundaries() const {
    return boundaries_;
}

void SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries(const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries){
    if(weights.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because the array of weights is empty");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0f){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because all of the weights are zero");}
    if(boundaries.length() != weights.length() + 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because the length of the boudaries array is not one more than the length of the weights array");}
    for(int i=0; i<boundaries.length()-1; i++){
        if(boundaries.at(i) >= boundaries.at(i + 1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::setWeightsAndBoundaries crashed because the boundaries array is not strictly increasing");}
    }
    weights_ = weights;
    boundaries_ = boundaries;
    updatePrefixSums();
}
