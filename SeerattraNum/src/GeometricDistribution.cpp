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

SGEXTN::SeerattraNum::GeometricDistribution::GeometricDistribution() : SGEXTN::SeerattraNum::GeometricDistribution(true, 0.5f){}

SGEXTN::SeerattraNum::GeometricDistribution::GeometricDistribution(bool useGlobal, float chanceOfTrue) : private_chanceOfTrue(chanceOfTrue), private_cacheReciprocalOfLnChanceOfFalse(1.0f / SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - chanceOfTrue)), private_rngLocator(useGlobal){
    if(chanceOfTrue <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution constructor crashed because the requested probability is nonpositive");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution constructor crashed because the requested probability is higher than 1");}
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::GeometricDistribution::serialise(const SGEXTN::SeerattraNum::GeometricDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::serialiseTogether(x.private_rngLocator, x.private_chanceOfTrue);
}

SGEXTN::SeerattraNum::GeometricDistribution SGEXTN::SeerattraNum::GeometricDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 41){
        success = false;
        return SGEXTN::SeerattraNum::GeometricDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::GeometricDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float probability = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || probability <= 0.0f || probability > 1.0f){
        success = false;
        return SGEXTN::SeerattraNum::GeometricDistribution();
    }
    SGEXTN::SeerattraNum::GeometricDistribution output(true, probability);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::GeometricDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::GeometricDistribution& x){
    return 41;
}

void SGEXTN::SeerattraNum::GeometricDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

int SGEXTN::SeerattraNum::GeometricDistribution::private_randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    if(private_chanceOfTrue < 0.15f){
        const float rng = (*externalLocator).randomFloat32();
        return SGEXTN::Math::FloatMath<float>::floorToInt(SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - rng) * private_cacheReciprocalOfLnChanceOfFalse);
    }
    int failCount = 0;
    while((*externalLocator).randomFloat32() > private_chanceOfTrue){
        failCount++;
    }
    return failCount;
}

int SGEXTN::SeerattraNum::GeometricDistribution::randomValue(){
    return private_randomValue(private_rngLocator);
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
}
