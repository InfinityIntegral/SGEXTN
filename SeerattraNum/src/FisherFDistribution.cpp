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

#include <SGEXTN/SeerattraNum/FisherFDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/Serialise.h>

SGEXTN::SeerattraNum::FisherFDistribution::FisherFDistribution() : private_numeratorDegreesOfFreedom(1.0f), private_denominatorDegreesOfFreedom(1.0f), private_rngLocator(true), private_numeratorDistribution(true, 1.0f), private_denominatorDistribution(true, 1.0f){}

SGEXTN::SeerattraNum::FisherFDistribution::FisherFDistribution(bool useGlobal, float numeratorDegreesOfFreedom, float denominatorDegreesOfFreedom) : private_numeratorDegreesOfFreedom(numeratorDegreesOfFreedom), private_denominatorDegreesOfFreedom(denominatorDegreesOfFreedom), private_rngLocator(useGlobal), private_numeratorDistribution(true, 1.0f), private_denominatorDistribution(true, 1.0f){
    if(numeratorDegreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution constructor crashed because requested number of degrees of freedom in the numerator is nonpositive");}
    if(denominatorDegreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution constructor crashed because requested number of degrees of freedom in the denominator is nonpositive");}
    private_numeratorDistribution.setDegreesOfFreedom(numeratorDegreesOfFreedom);
    private_denominatorDistribution.setDegreesOfFreedom(denominatorDegreesOfFreedom);
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::FisherFDistribution::serialise(const SGEXTN::SeerattraNum::FisherFDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::serialiseTogether(x.private_rngLocator, x.private_numeratorDegreesOfFreedom, x.private_denominatorDegreesOfFreedom);
}

SGEXTN::SeerattraNum::FisherFDistribution SGEXTN::SeerattraNum::FisherFDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 45){
        success = false;
        return SGEXTN::SeerattraNum::FisherFDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::FisherFDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float numerator = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || numerator <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::FisherFDistribution();
    }
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float denominator = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || denominator <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::FisherFDistribution();
    }
    SGEXTN::SeerattraNum::FisherFDistribution output(true, numerator, denominator);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::FisherFDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::FisherFDistribution& x){
    return 45;
}

void SGEXTN::SeerattraNum::FisherFDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::FisherFDistribution::randomValue(){
    return ((private_denominatorDegreesOfFreedom * private_numeratorDistribution.private_randomValue(private_rngLocator)) / (private_numeratorDegreesOfFreedom * private_denominatorDistribution.private_randomValue(private_rngLocator)));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::FisherFDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::FisherFDistribution::getNumeratorDegreesOfFreedom() const {
    return private_numeratorDegreesOfFreedom;
}

float SGEXTN::SeerattraNum::FisherFDistribution::getDenominatorDegreesOfFreedom() const {
    return private_denominatorDegreesOfFreedom;
}

void SGEXTN::SeerattraNum::FisherFDistribution::setNumeratorDegreesOfFreedom(float numeratorDegreesOfFreedom){
    if(numeratorDegreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::setNumeratorDegreesOfFreedom crashed because requested number of degrees of freedom in the numerator is nonpositive");}
    private_numeratorDegreesOfFreedom = numeratorDegreesOfFreedom;
    private_numeratorDistribution.setDegreesOfFreedom(numeratorDegreesOfFreedom);
}

void SGEXTN::SeerattraNum::FisherFDistribution::setDenominatorDegreesOfFreedom(float denominatorDegreesOfFreedom){
    if(denominatorDegreesOfFreedom <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::setDenominatorDegreesOfFreedom crashed because requested number of degrees of freedom in the denominator is nonpositive");}
    private_denominatorDegreesOfFreedom = denominatorDegreesOfFreedom;
    private_denominatorDistribution.setDegreesOfFreedom(denominatorDegreesOfFreedom);
}
