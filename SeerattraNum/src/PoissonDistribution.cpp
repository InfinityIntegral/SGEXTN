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

#include <SGEXTN/SeerattraNum/PoissonDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::PoissonDistribution::PoissonDistribution() : SGEXTN::SeerattraNum::PoissonDistribution(true, 1.0f){}

SGEXTN::SeerattraNum::PoissonDistribution::PoissonDistribution(bool useGlobal, float mean) : mean_(mean), rngLocator_(useGlobal), smallMeanProductThreshold_(0.0f), precompConstantA_(0.0f), precompConstantB_(0.0f), squeezeBoundU_(0.0f), squeezeBoundV_(0.0f), lnMean_(0.0f), lnAcceptRate_(0.0f){
    if(mean <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution constructor crashed because requested mean is nonpositive");}
    redoPrecompute();
}

bool SGEXTN::SeerattraNum::PoissonDistribution::sendOut(const SGEXTN::SeerattraNum::PoissonDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendOut(x.rngLocator_, x.mean_, data);
}

bool SGEXTN::SeerattraNum::PoissonDistribution::sendIn(SGEXTN::SeerattraNum::PoissonDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float mean = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendIn(rngLocator, mean, data);
    if(isValid == false || mean <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::PoissonDistribution(true, mean);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::PoissonDistribution::size(){
    return 41;
}

void SGEXTN::SeerattraNum::PoissonDistribution::redoPrecompute(){
    smallMeanProductThreshold_ = SGEXTN::Math::FloatMath<float>::powerOfE(-1.0f * mean_);
    precompConstantB_ = 0.931f + 2.53f * SGEXTN::Math::FloatMath<float>::squareRoot(mean_);
    precompConstantA_ = -0.059f + 0.02483f * precompConstantB_;
    lnMean_ = SGEXTN::Math::FloatMath<float>::naturalLog(mean_);
    lnAcceptRate_ = SGEXTN::Math::FloatMath<float>::naturalLog(1.0f / (1.1239f + 1.1328f / (precompConstantB_ - 1.4f)));
    squeezeBoundU_ = 0.43f;
    squeezeBoundV_ = 0.9277f - 3.6224f / (precompConstantB_ - 2.0f);
}

void SGEXTN::SeerattraNum::PoissonDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

int SGEXTN::SeerattraNum::PoissonDistribution::randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    if(mean_ <= 20.0f){
        float product = 1.0f;
        int count = 0;
        while(product >= smallMeanProductThreshold_){
            product *= (*externalLocator).randomFloat32();
            count++;
        }
        return (count - 1);
    }
    int result = 0;
    while(true){
        const float v1 = (*externalLocator).randomFloat32() - 0.5f;
        const float v2 = (*externalLocator).randomFloat32();
        const int g0OfV1 = SGEXTN::Math::FloatMath<float>::floorToInt(0.445f + mean_ + v1 * (precompConstantB_ + 2.0f * precompConstantA_ / (0.5f - SGEXTN::Math::FloatMath<float>::absoluteValue(v1))));
        if(g0OfV1 < 0){continue;}
        if(v1 >= -1.0f * squeezeBoundU_ && v1 <= squeezeBoundU_ && v2 <= squeezeBoundV_){
            result = g0OfV1;
            break;
        }
        const float g1OfV1 = precompConstantB_ + precompConstantA_ / (0.5f - SGEXTN::Math::FloatMath<float>::absoluteValue(v1)) / (0.5f - SGEXTN::Math::FloatMath<float>::absoluteValue(v1));
        const float leftSide = SGEXTN::Math::FloatMath<float>::naturalLog(v2 / g1OfV1);
        const float rightSide = lnAcceptRate_ - mean_ + static_cast<float>(g0OfV1) * lnMean_ - SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(static_cast<float>(g0OfV1));
        if(leftSide <= rightSide){
            result = g0OfV1;
            break;
        }
    }
    return result;
}

int SGEXTN::SeerattraNum::PoissonDistribution::randomValue(){
    return randomValue(rngLocator_);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::PoissonDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count, 0);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::PoissonDistribution::getMean() const {
    return mean_;
}

void SGEXTN::SeerattraNum::PoissonDistribution::setMean(float mean){
    if(mean <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::setMean crashed because requested mean is nonpositive");}
    mean_ = mean;
    redoPrecompute();
}
