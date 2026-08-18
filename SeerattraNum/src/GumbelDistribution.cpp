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

#include <SGEXTN/SeerattraNum/GumbelDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::GumbelDistribution::GumbelDistribution() : SGEXTN::SeerattraNum::GumbelDistribution(true, 0.0f, 1.0f){}

SGEXTN::SeerattraNum::GumbelDistribution::GumbelDistribution(bool useGlobal, float mode, float spread) : private_mode(mode), private_spread(spread), private_rngLocator(useGlobal){
    if(spread <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution constructor crashed because requested spread is nonpositive");}
}

bool SGEXTN::SeerattraNum::GumbelDistribution::sendOut(const SGEXTN::SeerattraNum::GumbelDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendOut(x.private_rngLocator, x.private_mode, x.private_spread, data);
}

bool SGEXTN::SeerattraNum::GumbelDistribution::sendIn(SGEXTN::SeerattraNum::GumbelDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float mode = 0.0f;
    float spread = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendIn(rngLocator, mode, spread, data);
    if(isValid == false || spread <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::GumbelDistribution(true, mode, spread);
    x.private_rngLocator = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::GumbelDistribution::size(){
    return 45;
}

void SGEXTN::SeerattraNum::GumbelDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::GumbelDistribution::randomValue(){
    const unsigned int integerRng = (*private_rngLocator).randomUnsignedInt32();
    const float scaleFactor = 1.0f / (static_cast<float>(static_cast<unsigned int>(1) << 24) + 1.0f);
    const float rng = (1.0f + (static_cast<float>(integerRng >> 8))) * scaleFactor;
    return (private_mode - private_spread * SGEXTN::Math::FloatMath<float>::naturalLog(-1.0f * SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - rng)));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::GumbelDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::GumbelDistribution::getMode() const {
    return private_mode;
}

float SGEXTN::SeerattraNum::GumbelDistribution::getSpread() const {
    return private_spread;
}

void SGEXTN::SeerattraNum::GumbelDistribution::setMode(float mode){
    private_mode = mode;
}

void SGEXTN::SeerattraNum::GumbelDistribution::setSpread(float spread){
    if(spread <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution::setSpread crashed because requested spread is nonpositive");}
    private_spread = spread;
}
