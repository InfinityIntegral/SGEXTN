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

#include <SGEXTN/SeerattraNum/WeibullDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>

SGEXTN::SeerattraNum::WeibullDistribution::WeibullDistribution(bool useGlobal, float failureBehaviour, float characteristicLifespan) : private_characteristicLifespan(characteristicLifespan), private_failureBehaviour(failureBehaviour), private_rng(nullptr), private_ownsRng(useGlobal == false), private_reciprocalA(1.0f / failureBehaviour){
    if(failureBehaviour <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution constructor crashed because requested failure behaviour indicator is nonpositive");}
    if(characteristicLifespan <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution constructor crashed because requested characteristic lifespan is nonpositive");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
}

SGEXTN::SeerattraNum::WeibullDistribution::~WeibullDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::WeibullDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

float SGEXTN::SeerattraNum::WeibullDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    return (private_characteristicLifespan * SGEXTN::Math::FloatMath<float>::powerOf(-1.0f * SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - (*private_rng).randomFloat32()), private_reciprocalA));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeibullDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::WeibullDistribution::getFailureBehaviour() const {
    return private_failureBehaviour;
}

float SGEXTN::SeerattraNum::WeibullDistribution::getCharacteristicLifespan() const {
    return private_characteristicLifespan;
}

void SGEXTN::SeerattraNum::WeibullDistribution::setFailureBehaviour(float failureBehaviour){
    if(failureBehaviour <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::setFailureBehaviour crashed because requested failure behaviour indicator is nonpositive");}
    private_failureBehaviour = failureBehaviour;
    private_reciprocalA = 1.0f / failureBehaviour;
}

void SGEXTN::SeerattraNum::WeibullDistribution::setCharacteristicLifespan(float characteristicLifespan){
    if(characteristicLifespan <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::setCharacteristicLifespan crashed because requested characteristic lifespan is nonpositive");}
    private_characteristicLifespan = characteristicLifespan;
}
