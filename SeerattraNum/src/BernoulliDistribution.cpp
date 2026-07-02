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

SGEXTN::SeerattraNum::BernoulliDistribution::BernoulliDistribution(bool useGlobal, float chanceOfTrue) : private_chanceOfTrue(chanceOfTrue), private_rng(nullptr), private_ownsRng(useGlobal == false){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution constructor crashed because the requested probability is higher than 1");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
}

SGEXTN::SeerattraNum::BernoulliDistribution::~BernoulliDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::BernoulliDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

bool SGEXTN::SeerattraNum::BernoulliDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    return ((*private_rng).randomFloat32() < private_chanceOfTrue);
}

SGEXTN::Containers::Array<bool> SGEXTN::SeerattraNum::BernoulliDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<bool> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::BernoulliDistribution::getChanceOfTrue() const {
    return private_chanceOfTrue;
}

void SGEXTN::SeerattraNum::BernoulliDistribution::setChanceOfTrue(float chanceOfTrue){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::setChanceOfTrue crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    private_chanceOfTrue = chanceOfTrue;
}
