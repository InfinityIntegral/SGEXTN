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
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::WeibullDistribution::WeibullDistribution() : SGEXTN::SeerattraNum::WeibullDistribution(true, 1.0f, 1.0f){}

SGEXTN::SeerattraNum::WeibullDistribution::WeibullDistribution(bool useGlobal, float failureBehaviour, float characteristicLifespan) : characteristicLifespan_(characteristicLifespan), failureBehaviour_(failureBehaviour), rngLocator_(useGlobal), reciprocalA_(1.0f / failureBehaviour){
    if(failureBehaviour <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution constructor crashed because requested failure behaviour indicator is nonpositive");}
    if(characteristicLifespan <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution constructor crashed because requested characteristic lifespan is nonpositive");}
}

bool SGEXTN::SeerattraNum::WeibullDistribution::sendOut(const SGEXTN::SeerattraNum::WeibullDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendOut(x.rngLocator_, x.failureBehaviour_, x.characteristicLifespan_, data);
}

bool SGEXTN::SeerattraNum::WeibullDistribution::sendIn(SGEXTN::SeerattraNum::WeibullDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float failureBehaviour = 0.0f;
    float characteristicLifespan = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendIn(rngLocator, failureBehaviour, characteristicLifespan, data);
    if(isValid == false || failureBehaviour <= 0.0f || characteristicLifespan <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::WeibullDistribution(true, failureBehaviour, characteristicLifespan);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::WeibullDistribution::size(){
    return 45;
}

void SGEXTN::SeerattraNum::WeibullDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

float SGEXTN::SeerattraNum::WeibullDistribution::randomValue(){
    return (characteristicLifespan_ * SGEXTN::Math::FloatMath<float>::powerOf(-1.0f * SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - (*rngLocator_).randomFloat32()), reciprocalA_));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::WeibullDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count, 0.0f);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::WeibullDistribution::getFailureBehaviour() const {
    return failureBehaviour_;
}

float SGEXTN::SeerattraNum::WeibullDistribution::getCharacteristicLifespan() const {
    return characteristicLifespan_;
}

void SGEXTN::SeerattraNum::WeibullDistribution::setFailureBehaviour(float failureBehaviour){
    if(failureBehaviour <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::setFailureBehaviour crashed because requested failure behaviour indicator is nonpositive");}
    failureBehaviour_ = failureBehaviour;
    reciprocalA_ = 1.0f / failureBehaviour;
}

void SGEXTN::SeerattraNum::WeibullDistribution::setCharacteristicLifespan(float characteristicLifespan){
    if(characteristicLifespan <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::setCharacteristicLifespan crashed because requested characteristic lifespan is nonpositive");}
    characteristicLifespan_ = characteristicLifespan;
}
