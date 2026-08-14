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

SGEXTN::SeerattraNum::WeibullDistribution::WeibullDistribution() : SGEXTN::SeerattraNum::WeibullDistribution(true, 1.0f, 1.0f){}

SGEXTN::SeerattraNum::WeibullDistribution::WeibullDistribution(bool useGlobal, float failureBehaviour, float characteristicLifespan) : private_characteristicLifespan(characteristicLifespan), private_failureBehaviour(failureBehaviour), private_rngLocator(useGlobal), private_reciprocalA(1.0f / failureBehaviour){
    if(failureBehaviour <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution constructor crashed because requested failure behaviour indicator is nonpositive");}
    if(characteristicLifespan <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution constructor crashed because requested characteristic lifespan is nonpositive");}
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::WeibullDistribution::serialise(const SGEXTN::SeerattraNum::WeibullDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::serialiseTogether(x.private_rngLocator, x.private_failureBehaviour, x.private_characteristicLifespan);
}

SGEXTN::SeerattraNum::WeibullDistribution SGEXTN::SeerattraNum::WeibullDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 45){
        success = false;
        return SGEXTN::SeerattraNum::WeibullDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::WeibullDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float failureMode = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || failureMode <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::WeibullDistribution();
    }
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float characteristicLife = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || characteristicLife <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::WeibullDistribution();
    }
    SGEXTN::SeerattraNum::WeibullDistribution output(true, failureMode, characteristicLife);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::WeibullDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::WeibullDistribution& x){
    return 45;
}

void SGEXTN::SeerattraNum::WeibullDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::WeibullDistribution::randomValue(){
    return (private_characteristicLifespan * SGEXTN::Math::FloatMath<float>::powerOf(-1.0f * SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - (*private_rngLocator).randomFloat32()), private_reciprocalA));
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
