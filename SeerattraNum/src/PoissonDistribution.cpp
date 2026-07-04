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

SGEXTN::SeerattraNum::PoissonDistribution::PoissonDistribution(bool useGlobal, float mean) : private_mean(mean), private_rng(nullptr), private_ownsRng(useGlobal == false), private_smallMeanProductThreshold(0.0f), private_precompConstantA(0.0f), private_precompConstantB(0.0f), private_squeezeBoundU(0.0f), private_squeezeBoundV(0.0f), private_lnMean(0.0f), private_lnAcceptRate(0.0f){
    if(mean <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution constructor crashed because requested mean is nonpositive");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
    private_redoPrecompute();
}

SGEXTN::SeerattraNum::PoissonDistribution::~PoissonDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::PoissonDistribution::private_redoPrecompute(){
    private_smallMeanProductThreshold = SGEXTN::Math::FloatMath<float>::powerOfE(-1.0f * private_mean);
    private_precompConstantB = 0.931f + 2.53f * SGEXTN::Math::FloatMath<float>::squareRoot(private_mean);
    private_precompConstantA = -0.059f + 0.02483f * private_precompConstantB;
    private_lnMean = SGEXTN::Math::FloatMath<float>::naturalLog(private_mean);
    private_lnAcceptRate = SGEXTN::Math::FloatMath<float>::naturalLog(1.0f / (1.1239f + 1.1328f / (private_precompConstantB - 1.4f)));
    private_squeezeBoundU = 0.43f;
    private_squeezeBoundV = 0.9277f - 3.6224f / (private_precompConstantB - 2.0f);
}

void SGEXTN::SeerattraNum::PoissonDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

int SGEXTN::SeerattraNum::PoissonDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    if(private_mean <= 20.0f){
        float product = 1.0f;
        int count = 0;
        while(product >= private_smallMeanProductThreshold){
            product *= (*private_rng).randomFloat32();
            count++;
        }
        return (count - 1);
    }
    int result = 0;
    while(true){
        const float v1 = (*private_rng).randomFloat32() - 0.5f;
        const float v2 = (*private_rng).randomFloat32();
        const int g0OfV1 = SGEXTN::Math::FloatMath<float>::floorToInt(0.445f + private_mean + v1 * (private_precompConstantB + 2.0f * private_precompConstantA / (0.5f - SGEXTN::Math::FloatMath<float>::absoluteValue(v1))));
        if(g0OfV1 < 0){continue;}
        if(v1 >= -1.0f * private_squeezeBoundU && v1 <= private_squeezeBoundU && v2 <= private_squeezeBoundV){
            result = g0OfV1;
            break;
        }
        const float g1OfV1 = private_precompConstantB + private_precompConstantA / (0.5f - SGEXTN::Math::FloatMath<float>::absoluteValue(v1)) / (0.5f - SGEXTN::Math::FloatMath<float>::absoluteValue(v1));
        const float leftSide = SGEXTN::Math::FloatMath<float>::naturalLog(v2 / g1OfV1);
        const float rightSide = private_lnAcceptRate - private_mean + static_cast<float>(g0OfV1) * private_lnMean - SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(static_cast<float>(g0OfV1));
        if(leftSide <= rightSide){
            result = g0OfV1;
            break;
        }
    }
    return result;
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::PoissonDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::PoissonDistribution::getMean() const {
    return private_mean;
}

void SGEXTN::SeerattraNum::PoissonDistribution::setMean(float mean){
    if(mean <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution::setMean crashed because requested mean is nonpositive");}
    private_mean = mean;
    private_redoPrecompute();
}
