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

SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::WeightedPiecewiseConstantDistribution() : SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution(true, SGEXTN::Containers::Array<float>(1, 1.0f), SGEXTN::Containers::Array<float>(0.0f, 1.0f)){}

SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::WeightedPiecewiseConstantDistribution(bool useGlobal, const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries) : private_weights(weights), private_boundaries(boundaries), private_prefixSums(0), private_rngLocator(useGlobal){
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
    private_updatePrefixSums();
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::serialise(const SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>, SGEXTN::Containers::Array<float>>::serialiseTogether(x.private_rngLocator, x.private_weights, x.private_boundaries);
}

SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() < 41){
        success = false;
        return SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution();}
    int readAhead = offset;
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, readAhead, tempArray);
    const int weightsArrayDataLength = SGEXTN::Containers::Serialise<int>::unserialise(tempArray, &success);
    if(success == false || weightsArrayDataLength < 0){
        success = false;
        return SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution();
    }
    tempArray = SGEXTN::Containers::Array<unsigned char>(weightsArrayDataLength);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::Containers::Array<float> weights = SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<float>>::unserialise(tempArray, &success);
    if(success == false || weights.length() == 0){
        success = false;
        return SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution();
    }
    bool allZero = true;
    bool hasNegative = false;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0f){
            hasNegative = true;
            break;
        }
        if(weights.at(i) > 0.0f){allZero = false;}
    }
    if(allZero == true || hasNegative == true){
        success = false;
        return SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution();
    }
    tempArray = SGEXTN::Containers::Array<unsigned char>(data.length() - 37 - weightsArrayDataLength);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::Containers::Array<float> boundaries = SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<float>>::unserialise(tempArray, &success);
    if(success == false || boundaries.length() != weights.length() + 1){
        success = false;
        return SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution();
    }
    for(int i=0; i<boundaries.length()-1; i++){
        if(boundaries.at(i) >= boundaries.at(i + 1)){
            success = false;
            return SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution();
        }
    }
    SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution output(true, weights, boundaries);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::lengthof(const SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution& x){
    return (37 + SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<float>>::lengthof(x.private_weights) + SGEXTN::Containers::Serialise<SGEXTN::Containers::Array<float>>::lengthof(x.private_boundaries));
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
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution::randomValue(){
    float rng = (*private_rngLocator).randomFloat32();
    int low = 0;
    int high = private_weights.length();
    while(high - low > 1){
        const int middle = low + (high - low) / 2;
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
