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

#include <SGEXTN/SeerattraNum/UniformDistributionInteger.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/IntegerLimits.h>

SGEXTN::SeerattraNum::UniformDistributionInteger::UniformDistributionInteger(bool useGlobal, int inclusiveMin, int inclusiveMax) : private_inclusiveMax(inclusiveMax), private_inclusiveMin(inclusiveMin), private_rng(nullptr), private_ownsRng(useGlobal == false){
    if(inclusiveMin > inclusiveMax){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger constructor crashed because minimum is higher than maximum");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
}

SGEXTN::SeerattraNum::UniformDistributionInteger::~UniformDistributionInteger(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::UniformDistributionInteger::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

int SGEXTN::SeerattraNum::UniformDistributionInteger::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    while(true){
        const unsigned int rngValue = (*private_rng).randomUnsignedInt32();
        const unsigned int elementCount = static_cast<unsigned int>(private_inclusiveMax - private_inclusiveMin + 1);
        if(rngValue >= elementCount * (SGEXTN::Math::IntegerLimits<unsigned int>::maximum() / elementCount)){continue;}
        return (static_cast<int>(rngValue % elementCount) + private_inclusiveMin);
    }
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::UniformDistributionInteger::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

int SGEXTN::SeerattraNum::UniformDistributionInteger::getInclusiveMin() const {
    return private_inclusiveMin;
}

int SGEXTN::SeerattraNum::UniformDistributionInteger::getInclusiveMax() const {
    return private_inclusiveMax;
}

void SGEXTN::SeerattraNum::UniformDistributionInteger::setRange(int inclusiveMin, int inclusiveMax){
    if(inclusiveMin > inclusiveMax){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::setRange crashed because minimum is higher than maximum");}
    private_inclusiveMin = inclusiveMin;
    private_inclusiveMax = inclusiveMax;
}
