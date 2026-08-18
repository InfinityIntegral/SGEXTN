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
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::UniformDistributionInteger::UniformDistributionInteger() : SGEXTN::SeerattraNum::UniformDistributionInteger(true, 0, 0){}

SGEXTN::SeerattraNum::UniformDistributionInteger::UniformDistributionInteger(bool useGlobal, int inclusiveMin, int inclusiveMax) : private_inclusiveMax(inclusiveMax), private_inclusiveMin(inclusiveMin), private_rngLocator(useGlobal){
    if(inclusiveMin > inclusiveMax){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger constructor crashed because minimum is higher than maximum");}
}

bool SGEXTN::SeerattraNum::UniformDistributionInteger::sendOut(const SGEXTN::SeerattraNum::UniformDistributionInteger& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, int, int>::sendOut(x.private_rngLocator, x.private_inclusiveMin, x.private_inclusiveMax, data);
}

bool SGEXTN::SeerattraNum::UniformDistributionInteger::sendIn(SGEXTN::SeerattraNum::UniformDistributionInteger& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    int min = 0;
    int max = 0;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, int, int>::sendIn(rngLocator, min, max, data);
    if(isValid == false || max < min){return false;}
    x = SGEXTN::SeerattraNum::UniformDistributionInteger(true, min, max);
    x.private_rngLocator = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::UniformDistributionInteger::size(){
    return 45;
}

void SGEXTN::SeerattraNum::UniformDistributionInteger::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

int SGEXTN::SeerattraNum::UniformDistributionInteger::private_randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    while(true){
        const unsigned int rngValue = (*externalLocator).randomUnsignedInt32();
        const unsigned int elementCount = static_cast<unsigned int>(private_inclusiveMax - private_inclusiveMin + 1);
        if(rngValue >= elementCount * (SGEXTN::Math::IntegerLimits<unsigned int>::maximum() / elementCount)){continue;}
        return (static_cast<int>(rngValue % elementCount) + private_inclusiveMin);
    }
}

int SGEXTN::SeerattraNum::UniformDistributionInteger::randomValue(){
    return private_randomValue(private_rngLocator);
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
