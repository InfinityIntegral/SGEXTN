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

SGEXTN::SeerattraNum::GumbelDistribution::GumbelDistribution() : private_mode(0.0f), private_spread(1.0f), private_rngLocator(true){}

SGEXTN::SeerattraNum::GumbelDistribution::GumbelDistribution(bool useGlobal, float mode, float spread) : private_mode(mode), private_spread(spread), private_rngLocator(useGlobal){
    if(spread <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution constructor crashed because requested spread is nonpositive");}
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::GumbelDistribution::serialise(const SGEXTN::SeerattraNum::GumbelDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::serialiseTogether(x.private_rngLocator, x.private_mode, x.private_spread);
}

SGEXTN::SeerattraNum::GumbelDistribution SGEXTN::SeerattraNum::GumbelDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 45){
        success = false;
        return SGEXTN::SeerattraNum::GumbelDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::GumbelDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float mode = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::GumbelDistribution();}
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float spread = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || spread <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::GumbelDistribution();
    }
    SGEXTN::SeerattraNum::GumbelDistribution output(true, mode, spread);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::GumbelDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::GumbelDistribution& x){
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
