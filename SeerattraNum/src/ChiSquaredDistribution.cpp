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

SGEXTN::SeerattraNum::ChiSquaredDistribution::ChiSquaredDistribution(bool useGlobal, float degreesOfFreedom) : private_degreesOfFreedom(degreesOfFreedom), private_rng(nullptr), private_ownsRng(useGlobal == false), private_gammaDistribution(true, 1.0f, 2.0f){
    if(degreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution constructor crashed because requested number of degrees of freedom is nonpositive");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
    private_gammaDistribution.private_rng = private_rng;
    private_gammaDistribution.private_standardNormalDistribution.private_rng = private_rng;
    private_gammaDistribution.setVariableCount(0.5f * degreesOfFreedom);
}

SGEXTN::SeerattraNum::ChiSquaredDistribution::~ChiSquaredDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::ChiSquaredDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

float SGEXTN::SeerattraNum::ChiSquaredDistribution::randomValue(){
    return private_gammaDistribution.randomValue();
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::ChiSquaredDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::ChiSquaredDistribution::getDegreesOfFreedom() const {
    return private_degreesOfFreedom;
}

void SGEXTN::SeerattraNum::ChiSquaredDistribution::setDegreesOfFreedom(float degreesOfFreedom){
    if(degreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution::setDegreesOfFreedom crashed because requested number of degrees of freedom is nonpositive");}
    private_degreesOfFreedom = degreesOfFreedom;
    private_gammaDistribution.setVariableCount(0.5f * degreesOfFreedom);
}
