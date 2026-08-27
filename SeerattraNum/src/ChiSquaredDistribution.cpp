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

#include <SGEXTN/SeerattraNum/ChiSquaredDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::ChiSquaredDistribution::ChiSquaredDistribution() : SGEXTN::SeerattraNum::ChiSquaredDistribution(true, 1.0f){}

SGEXTN::SeerattraNum::ChiSquaredDistribution::ChiSquaredDistribution(bool useGlobal, float degreesOfFreedom) : private_degreesOfFreedom(degreesOfFreedom), private_rngLocator(useGlobal), private_gammaDistribution(true, 1.0f, 2.0f){
    if(degreesOfFreedom <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution constructor crashed because requested number of degrees of freedom is nonpositive");}
    private_gammaDistribution.setVariableCount(0.5f * degreesOfFreedom);
}

bool SGEXTN::SeerattraNum::ChiSquaredDistribution::sendOut(const SGEXTN::SeerattraNum::ChiSquaredDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendOut(x.private_rngLocator, x.private_degreesOfFreedom, data);
}

bool SGEXTN::SeerattraNum::ChiSquaredDistribution::sendIn(SGEXTN::SeerattraNum::ChiSquaredDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float degree = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendIn(rngLocator, degree, data);
    if(isValid == false || degree <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::ChiSquaredDistribution(true, degree);
    x.private_rngLocator = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::ChiSquaredDistribution::size(){
    return 41;
}

void SGEXTN::SeerattraNum::ChiSquaredDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::ChiSquaredDistribution::private_randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    return private_gammaDistribution.private_randomValue(externalLocator);
}

float SGEXTN::SeerattraNum::ChiSquaredDistribution::randomValue(){
    return private_randomValue(private_rngLocator);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::ChiSquaredDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count, 0.0f);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::ChiSquaredDistribution::getDegreesOfFreedom() const {
    return private_degreesOfFreedom;
}

void SGEXTN::SeerattraNum::ChiSquaredDistribution::setDegreesOfFreedom(float degreesOfFreedom){
    if(degreesOfFreedom <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::setDegreesOfFreedom crashed because requested number of degrees of freedom is nonpositive");}
    private_degreesOfFreedom = degreesOfFreedom;
    private_gammaDistribution.setVariableCount(0.5f * degreesOfFreedom);
}
