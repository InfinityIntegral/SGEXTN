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

SGEXTN::SeerattraNum::UniformDistributionInteger::UniformDistributionInteger() : private_inclusiveMax(0), private_inclusiveMin(0), private_rngLocator(true){}

SGEXTN::SeerattraNum::UniformDistributionInteger::UniformDistributionInteger(bool useGlobal, int inclusiveMin, int inclusiveMax) : private_inclusiveMax(inclusiveMax), private_inclusiveMin(inclusiveMin), private_rngLocator(useGlobal){
    if(inclusiveMin > inclusiveMax){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger constructor crashed because minimum is higher than maximum");}
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::UniformDistributionInteger::serialise(const SGEXTN::SeerattraNum::UniformDistributionInteger& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandom, int, int>::serialiseTogether((*x.private_rngLocator), x.private_inclusiveMin, x.private_inclusiveMax);
}

SGEXTN::SeerattraNum::UniformDistributionInteger SGEXTN::SeerattraNum::UniformDistributionInteger::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 45){
        success = false;
        return SGEXTN::SeerattraNum::UniformDistributionInteger();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::UniformDistributionInteger();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const int min = SGEXTN::Containers::Serialise<int>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::UniformDistributionInteger();}
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const int max = SGEXTN::Containers::Serialise<int>::unserialise(tempArray, &success);
    if(success == false || max < min){
        success = false;
        return SGEXTN::SeerattraNum::UniformDistributionInteger();
    }
    SGEXTN::SeerattraNum::UniformDistributionInteger output(true, min, max);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::UniformDistributionInteger::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::UniformDistributionInteger& x){
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
