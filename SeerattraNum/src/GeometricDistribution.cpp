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

#include <SGEXTN/SeerattraNum/GeometricDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::GeometricDistribution::GeometricDistribution() : SGEXTN::SeerattraNum::GeometricDistribution(true, 0.5f){}

SGEXTN::SeerattraNum::GeometricDistribution::GeometricDistribution(bool useGlobal, float chanceOfTrue) : chanceOfTrue_(chanceOfTrue), cacheReciprocalOfLnChanceOfFalse_(1.0f / SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - chanceOfTrue)), rngLocator_(useGlobal){
    if(chanceOfTrue <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution constructor crashed because the requested probability is nonpositive");}
    if(chanceOfTrue > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution constructor crashed because the requested probability is higher than 1");}
}

bool SGEXTN::SeerattraNum::GeometricDistribution::sendOut(const SGEXTN::SeerattraNum::GeometricDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendOut(x.rngLocator_, x.chanceOfTrue_, data);
}

bool SGEXTN::SeerattraNum::GeometricDistribution::sendIn(SGEXTN::SeerattraNum::GeometricDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float probability = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendIn(rngLocator, probability, data);
    if(isValid == false || probability < 0.0f || probability > 1.0f){return false;}
    x = SGEXTN::SeerattraNum::GeometricDistribution(true, probability);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::GeometricDistribution::size(){
    return 41;
}

void SGEXTN::SeerattraNum::GeometricDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

int SGEXTN::SeerattraNum::GeometricDistribution::randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    if(chanceOfTrue_ < 0.15f){
        const float rng = (*externalLocator).randomFloat32();
        return SGEXTN::Math::FloatMath<float>::floorToInt(SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - rng) * cacheReciprocalOfLnChanceOfFalse_);
    }
    int failCount = 0;
    while((*externalLocator).randomFloat32() > chanceOfTrue_){
        failCount++;
    }
    return failCount;
}

int SGEXTN::SeerattraNum::GeometricDistribution::randomValue(){
    return randomValue(rngLocator_);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::GeometricDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count, 0);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::GeometricDistribution::getChanceOfTrue() const {
    return chanceOfTrue_;
}

void SGEXTN::SeerattraNum::GeometricDistribution::setChanceOfTrue(float chanceOfTrue){
    if(chanceOfTrue <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::setChanceOfTrue crashed because the requested probability is nonpositive");}
    if(chanceOfTrue > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    chanceOfTrue_ = chanceOfTrue;
    cacheReciprocalOfLnChanceOfFalse_ = 1.0f / SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - chanceOfTrue);
}
