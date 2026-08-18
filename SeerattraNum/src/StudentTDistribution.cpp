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
#include <SGEXTN/Containers/Serialisation.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::StudentTDistribution::StudentTDistribution() : SGEXTN::SeerattraNum::StudentTDistribution(true, 1.0f){}

SGEXTN::SeerattraNum::StudentTDistribution::StudentTDistribution(bool useGlobal, float degreesOfFreedom) : private_degreesOfFreedom(degreesOfFreedom), private_rngLocator(useGlobal), private_chiSquaredDistribution(true, 1.0f), private_standardNormalDistribution(true, 0.0f, 1.0f){
    if(degreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution constructor crashed because requested number of degrees of freedom is nonpositive");}
    private_chiSquaredDistribution.setDegreesOfFreedom(degreesOfFreedom);
}

bool SGEXTN::SeerattraNum::StudentTDistribution::sendOut(const SGEXTN::SeerattraNum::StudentTDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialisation<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendOut(x.private_rngLocator, x.private_degreesOfFreedom, data);
}

bool SGEXTN::SeerattraNum::StudentTDistribution::sendIn(SGEXTN::SeerattraNum::StudentTDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float degree = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialisation<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendIn(rngLocator, degree, data);
    if(isValid == false || degree <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::StudentTDistribution(true, degree);
    x.private_rngLocator = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::StudentTDistribution::size(){
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
