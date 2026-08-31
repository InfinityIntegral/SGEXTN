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
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::FisherFDistribution::FisherFDistribution() : SGEXTN::SeerattraNum::FisherFDistribution(true, 1.0f, 1.0f){}

SGEXTN::SeerattraNum::FisherFDistribution::FisherFDistribution(bool useGlobal, float numeratorDegreesOfFreedom, float denominatorDegreesOfFreedom) : numeratorDegreesOfFreedom_(numeratorDegreesOfFreedom), denominatorDegreesOfFreedom_(denominatorDegreesOfFreedom), rngLocator_(useGlobal), numeratorDistribution_(true, 1.0f), denominatorDistribution_(true, 1.0f){
    if(numeratorDegreesOfFreedom <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution constructor crashed because requested number of degrees of freedom in the numerator is nonpositive");}
    if(denominatorDegreesOfFreedom <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution constructor crashed because requested number of degrees of freedom in the denominator is nonpositive");}
    numeratorDistribution_.setDegreesOfFreedom(numeratorDegreesOfFreedom);
    denominatorDistribution_.setDegreesOfFreedom(denominatorDegreesOfFreedom);
}

bool SGEXTN::SeerattraNum::FisherFDistribution::sendOut(const SGEXTN::SeerattraNum::FisherFDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendOut(x.rngLocator_, x.numeratorDegreesOfFreedom_, x.denominatorDegreesOfFreedom_, data);
}

bool SGEXTN::SeerattraNum::FisherFDistribution::sendIn(SGEXTN::SeerattraNum::FisherFDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float top = 0.0f;
    float bottom = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendIn(rngLocator, top, bottom, data);
    if(isValid == false || top <= 0.0f || bottom <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::FisherFDistribution(true, top, bottom);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::FisherFDistribution::size(){
    return 45;
}

void SGEXTN::SeerattraNum::FisherFDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

float SGEXTN::SeerattraNum::FisherFDistribution::randomValue(){
    return ((denominatorDegreesOfFreedom_ * numeratorDistribution_.randomValue(rngLocator_)) / (numeratorDegreesOfFreedom_ * denominatorDistribution_.randomValue(rngLocator_)));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::FisherFDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count, 0.0f);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::FisherFDistribution::getNumeratorDegreesOfFreedom() const {
    return numeratorDegreesOfFreedom_;
}

float SGEXTN::SeerattraNum::FisherFDistribution::getDenominatorDegreesOfFreedom() const {
    return denominatorDegreesOfFreedom_;
}

void SGEXTN::SeerattraNum::FisherFDistribution::setNumeratorDegreesOfFreedom(float numeratorDegreesOfFreedom){
    if(numeratorDegreesOfFreedom <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::setNumeratorDegreesOfFreedom crashed because requested number of degrees of freedom in the numerator is nonpositive");}
    numeratorDegreesOfFreedom_ = numeratorDegreesOfFreedom;
    numeratorDistribution_.setDegreesOfFreedom(numeratorDegreesOfFreedom);
}

void SGEXTN::SeerattraNum::FisherFDistribution::setDenominatorDegreesOfFreedom(float denominatorDegreesOfFreedom){
    if(denominatorDegreesOfFreedom <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution::setDenominatorDegreesOfFreedom crashed because requested number of degrees of freedom in the denominator is nonpositive");}
    denominatorDegreesOfFreedom_ = denominatorDegreesOfFreedom;
    denominatorDistribution_.setDegreesOfFreedom(denominatorDegreesOfFreedom);
}
