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
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::WeightedIndexSelectionDistribution() : SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution(true, SGEXTN::Containers::Array<float>(1, 1.0f)){}

SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::WeightedIndexSelectionDistribution(bool useGlobal, const SGEXTN::Containers::Array<float>& weights) : private_weights(weights), private_rngLocator(useGlobal){
    if(weights.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightIndexSelectionDistribution constructor crashed because the array of weights is empty");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution constructor crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0f){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightIndexSelectionDistribution constructor crashed because all of the weights are zero");}
    private_updatePrefixSums();
}

bool SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::sendOut(const SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>>::sendOut(x.private_rngLocator, x.private_weights, data);
}

bool SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::sendIn(SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    SGEXTN::Containers::Array<float> weights;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>>::sendIn(rngLocator, weights, data);
    if(isValid == false || weights.length() == 0){return false;}
    bool allZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0f){return false;}
        if(weights.at(i) > 0.0f){allZero = false;}
    }
    if(allZero == true){return false;}
    x = SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution(true, weights);
    x.private_rngLocator = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::sizeOut(const SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>>::sizeOut(x.private_rngLocator, x.private_weights);
}

int SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, SGEXTN::Containers::Array<float>>::sizeIn(data);
}

void SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::private_updatePrefixSums(){
    private_prefixSums = SGEXTN::Containers::Array<float>(private_weights.length() + 1, 0.0f);
    private_prefixSums.at(0) = 0.0f;
    for(int i=0; i<private_weights.length(); i++){
        private_prefixSums.at(i + 1) = private_prefixSums.at(i) + private_weights.at(i);
    }
    for(int i=0; i<private_prefixSums.length(); i++){
        private_prefixSums.at(i) /= private_prefixSums.at(private_weights.length());
    }
}

void SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

int SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::randomIndex(){
    const float rng = (*private_rngLocator).randomFloat32();
    int low = 0;
    int high = private_weights.length();
    while(high - low > 1){
        const int middle = low + (high - low) / 2;
        if(private_prefixSums.at(middle) >= rng){high = middle;}
        else{low = middle;}
    }
    return low;
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::randomIndexArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::randomIndexArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count, 0);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomIndex();
    }
    return outputArray;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::getWeights() const {
    return private_weights;
}

void SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::setWeights(const SGEXTN::Containers::Array<float>& weights){
    if(weights.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightIndexSelectionDistribution::setWeights crashed because the array of weights is empty");}
    bool isAllZero = true;
    for(int i=0; i<weights.length(); i++){
        if(weights.at(i) < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution::setWeights crashed because at least 1 weight is negative");}
        if(weights.at(i) > 0.0f){isAllZero = false;}
    }
    if(isAllZero == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightIndexSelectionDistribution::setWeights crashed because all of the weights are zero");}
    private_weights = weights;
    private_updatePrefixSums();
}
