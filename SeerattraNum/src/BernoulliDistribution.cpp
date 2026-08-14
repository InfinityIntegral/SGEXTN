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

SGEXTN::SeerattraNum::BernoulliDistribution::BernoulliDistribution() : SGEXTN::SeerattraNum::BernoulliDistribution(true, 0.5f){}

SGEXTN::SeerattraNum::BernoulliDistribution::BernoulliDistribution(bool useGlobal, float chanceOfTrue) : private_chanceOfTrue(chanceOfTrue), private_rngLocator(useGlobal){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution constructor crashed because the requested probability is higher than 1");}
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::BernoulliDistribution::serialise(const SGEXTN::SeerattraNum::BernoulliDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::serialiseTogether(x.private_rngLocator, x.private_chanceOfTrue);
}

SGEXTN::SeerattraNum::BernoulliDistribution SGEXTN::SeerattraNum::BernoulliDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 41){
        success = false;
        return SGEXTN::SeerattraNum::BernoulliDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::BernoulliDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float probability = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || probability < 0.0f || probability > 1.0f){
        success = false;
        return SGEXTN::SeerattraNum::BernoulliDistribution();
    }
    SGEXTN::SeerattraNum::BernoulliDistribution output(true, probability);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::BernoulliDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::BernoulliDistribution& x){
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
