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

#include <SGEXTN/SeerattraNum/BernoulliDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::BernoulliDistribution::BernoulliDistribution() : SGEXTN::SeerattraNum::BernoulliDistribution(true, 0.5f){}

SGEXTN::SeerattraNum::BernoulliDistribution::BernoulliDistribution(bool useGlobal, float chanceOfTrue) : private_chanceOfTrue(chanceOfTrue), private_rngLocator(useGlobal){
    if(chanceOfTrue < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution constructor crashed because the requested probability is higher than 1");}
}

bool SGEXTN::SeerattraNum::BernoulliDistribution::sendOut(const SGEXTN::SeerattraNum::BernoulliDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendOut(x.private_rngLocator, x.private_chanceOfTrue, data);
}

bool SGEXTN::SeerattraNum::BernoulliDistribution::sendIn(SGEXTN::SeerattraNum::BernoulliDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float probability = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendIn(rngLocator, probability, data);
    if(isValid == false || probability < 0.0f || probability > 1.0f){return false;}
    x = SGEXTN::SeerattraNum::BernoulliDistribution(true, probability);
    x.private_rngLocator = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::BernoulliDistribution::size(){
    return 41;
}

void SGEXTN::SeerattraNum::BernoulliDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

bool SGEXTN::SeerattraNum::BernoulliDistribution::randomValue(){
    return ((*private_rngLocator).randomFloat32() < private_chanceOfTrue);
}

SGEXTN::Containers::Array<bool> SGEXTN::SeerattraNum::BernoulliDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<bool> outputArray(count, false);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::BernoulliDistribution::getChanceOfTrue() const {
    return private_chanceOfTrue;
}

void SGEXTN::SeerattraNum::BernoulliDistribution::setChanceOfTrue(float chanceOfTrue){
    if(chanceOfTrue < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::setChanceOfTrue crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    private_chanceOfTrue = chanceOfTrue;
}
