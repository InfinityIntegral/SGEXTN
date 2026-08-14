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

#include <SGEXTN/SeerattraNum/CauchyDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Math/FloatConstants.h>
#include <SGEXTN/Containers/Serialise.h>

SGEXTN::SeerattraNum::CauchyDistribution::CauchyDistribution() : SGEXTN::SeerattraNum::CauchyDistribution(true, 0.0f, 1.0f){}

SGEXTN::SeerattraNum::CauchyDistribution::CauchyDistribution(bool useGlobal, float median, float halfWidth) : private_median(median), private_halfWidth(halfWidth), private_rngLocator(useGlobal){
    if(halfWidth <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution constructor crashed because requested half width is nonpositive");}
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::CauchyDistribution::serialise(const SGEXTN::SeerattraNum::CauchyDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::serialiseTogether(x.private_rngLocator, x.private_median, x.private_halfWidth);
}

SGEXTN::SeerattraNum::CauchyDistribution SGEXTN::SeerattraNum::CauchyDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 45){
        success = false;
        return SGEXTN::SeerattraNum::CauchyDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::CauchyDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float median = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::CauchyDistribution();}
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float halfWidth = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || halfWidth <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::CauchyDistribution();
    }
    SGEXTN::SeerattraNum::CauchyDistribution output(true, median, halfWidth);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::CauchyDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::CauchyDistribution& x){
    return 45;
}

void SGEXTN::SeerattraNum::CauchyDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::CauchyDistribution::randomValue(){
    const unsigned int integerRng = (*private_rngLocator).randomUnsignedInt32();
    const float scaleFactor = 1.0f / (static_cast<float>(static_cast<unsigned int>(1) << 24) + 1.0f);
    const float rng = (1.0f + (static_cast<float>(integerRng >> 8))) * scaleFactor;
    return (private_median + private_halfWidth * SGEXTN::Math::FloatMath<float>::tangent(SGEXTN::Math::FloatConstants<float>::pi() * (rng - 0.5f)));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::CauchyDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::CauchyDistribution::getMedian() const {
    return private_median;
}

float SGEXTN::SeerattraNum::CauchyDistribution::getHalfWidth() const {
    return private_halfWidth;
}

void SGEXTN::SeerattraNum::CauchyDistribution::setMedian(float median){
    private_median = median;
}

void SGEXTN::SeerattraNum::CauchyDistribution::setHalfWidth(float halfWidth){
    if(halfWidth <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution::setHalfWidth crashed because requested half width is nonpositive");}
    private_halfWidth = halfWidth;
}
