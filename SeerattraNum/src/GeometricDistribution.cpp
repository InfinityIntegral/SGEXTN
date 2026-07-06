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
#include <SGEXTN/SeerattraNum/BernoulliDistribution.h>

SGEXTN::SeerattraNum::GeometricDistribution::GeometricDistribution(bool useGlobal, float chanceOfTrue) : private_chanceOfTrue(chanceOfTrue), private_cacheReciprocalOfLnChanceOfFalse(1.0f / SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - chanceOfTrue)), private_rng(nullptr), private_ownsRng(useGlobal == false), private_bernoulliDistribution(true, 0.5f){
    if(chanceOfTrue <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution constructor crashed because the requested probability is nonpositive");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution constructor crashed because the requested probability is higher than 1");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
    private_bernoulliDistribution.private_rng = private_rng;
    private_bernoulliDistribution.setChanceOfTrue(chanceOfTrue);
}

SGEXTN::SeerattraNum::GeometricDistribution::~GeometricDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::GeometricDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

int SGEXTN::SeerattraNum::GeometricDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    if(private_chanceOfTrue < 0.15f){
        const float rng = (*private_rng).randomFloat32();
        return SGEXTN::Math::FloatMath<float>::floorToInt(SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - rng) * private_cacheReciprocalOfLnChanceOfFalse);
    }
    int failCount = 0;
    while(private_bernoulliDistribution.randomValue() == false){
        failCount++;
    }
    return failCount;
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::GeometricDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::GeometricDistribution::getChanceOfTrue() const {
    return private_chanceOfTrue;
}

void SGEXTN::SeerattraNum::GeometricDistribution::setChanceOfTrue(float chanceOfTrue){
    if(chanceOfTrue <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::setChanceOfTrue crashed because the requested probability is nonpositive");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    private_chanceOfTrue = chanceOfTrue;
    private_cacheReciprocalOfLnChanceOfFalse = 1.0f / SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - chanceOfTrue);
    private_bernoulliDistribution.setChanceOfTrue(chanceOfTrue);
}
