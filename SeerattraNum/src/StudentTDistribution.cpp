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

#include <SGEXTN/SeerattraNum/StudentTDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Containers/Serialise.h>

SGEXTN::SeerattraNum::StudentTDistribution::StudentTDistribution() : private_degreesOfFreedom(1.0f), private_rngLocator(true), private_chiSquaredDistribution(true, 1.0f), private_standardNormalDistribution(true, 0.0f, 1.0f){}

SGEXTN::SeerattraNum::StudentTDistribution::StudentTDistribution(bool useGlobal, float degreesOfFreedom) : private_degreesOfFreedom(degreesOfFreedom), private_rngLocator(useGlobal), private_chiSquaredDistribution(true, 1.0f), private_standardNormalDistribution(true, 0.0f, 1.0f){
    if(degreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution constructor crashed because requested number of degrees of freedom is nonpositive");}
    private_chiSquaredDistribution.setDegreesOfFreedom(degreesOfFreedom);
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::StudentTDistribution::serialise(const SGEXTN::SeerattraNum::StudentTDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::serialiseTogether(x.private_rngLocator, x.private_degreesOfFreedom);
}

SGEXTN::SeerattraNum::StudentTDistribution SGEXTN::SeerattraNum::StudentTDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 41){
        success = false;
        return SGEXTN::SeerattraNum::StudentTDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::StudentTDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float degreesOfFreedom = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || degreesOfFreedom <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::StudentTDistribution();
    }
    SGEXTN::SeerattraNum::StudentTDistribution output(true, degreesOfFreedom);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::StudentTDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::StudentTDistribution& x){
    return 41;
}

void SGEXTN::SeerattraNum::StudentTDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::StudentTDistribution::randomValue(){
    return (private_standardNormalDistribution.private_randomValue(private_rngLocator) * SGEXTN::Math::FloatMath<float>::squareRoot(private_degreesOfFreedom / private_chiSquaredDistribution.private_randomValue(private_rngLocator)));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::StudentTDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::StudentTDistribution::getDegreesOfFreedom() const {
    return private_degreesOfFreedom;
}

void SGEXTN::SeerattraNum::StudentTDistribution::setDegreesOfFreedom(float degreesOfFreedom){
    if(degreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution::setDegreesOfFreedom crashed because requested number of degrees of freedom is nonpositive");}
    private_degreesOfFreedom = degreesOfFreedom;
    private_chiSquaredDistribution.setDegreesOfFreedom(degreesOfFreedom);
}
