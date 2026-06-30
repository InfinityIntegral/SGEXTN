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

#include <SGEXTN/SeerattraNum/PerlinNoise.h>
#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SmoothingFunction.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Containers/Span.h>
#include <SGEXTN/Containers/private_api/HashAlgorithm.h>
#include <SGEXTN/Math/IntegerLimits.h>
#include <SGEXTN/Math/FloatConstants.h>
#include <SGEXTN/Math/FloatLimits.h>

namespace {
int powerOf2(int n){
    return (1 << n);
}
}

SGEXTN::SeerattraNum::PerlinNoise::PerlinNoise(int dimension, SGEXTN::SeerattraNum::SmoothingFunction smoothingFunction) : private_dimension(dimension), private_seed(SGEXTN::SeerattraNum::TrueRandom::randomInt32()), private_smoothingFunction(smoothingFunction){
    if(dimension <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise constructor crashed because the number of dimensions is nonpositive");}
}

void SGEXTN::SeerattraNum::PerlinNoise::seed(int seed){
    private_seed = seed;
}

float SGEXTN::SeerattraNum::PerlinNoise::getHeight(const SGEXTN::Containers::Array<float>& point) const {
    if(point.length() != private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise::getHeight crashed because the number of dimensions in the point does not match that of the noise generator");}
    SGEXTN::Containers::Array<float> cornerContribution(powerOf2(private_dimension));
    SGEXTN::Containers::Array<int> flooredCorner(private_dimension);
    for(int i=0; i<private_dimension; i++){
        flooredCorner.at(i) = SGEXTN::Math::FloatMath<float>::floorToInt(point.at(i));
    }
    SGEXTN::Containers::Array<int> spanArray(private_dimension + 2);
    spanArray.at(private_dimension) = private_seed;
    const SGEXTN::Containers::Span<const unsigned char> span(reinterpret_cast<const unsigned char*>(&spanArray.at(0)), (private_dimension + 2) *static_cast<int>(sizeof(int)));
    const double maximum = static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) + 1.0;
    int normalVarCount = private_dimension;
    if(private_dimension % 2 == 1){normalVarCount++;}
    SGEXTN::Containers::Array<float> normalDistributedVars(normalVarCount);
    for(int i=0; i<powerOf2(private_dimension); i++){
        for(int j=0; j<private_dimension; j++){
            if((i & powerOf2(j)) == 0){spanArray.at(j) = flooredCorner.at(j);}
            else{spanArray.at(j) = flooredCorner.at(j) + 1;}
        }
        for(int j=0; j<normalVarCount; j++){
            spanArray.at(private_dimension + 1) = j;
            unsigned int rngUnsigned = static_cast<unsigned int>(SGEXTN::Containers::HashAlgorithm::wyHash32(span));
            if(rngUnsigned == 0){rngUnsigned = 1;}
            normalDistributedVars.at(j) =  static_cast<float>(static_cast<double>(rngUnsigned) / maximum);
        }
        for(int j=0; j<normalVarCount/2; j++){
            const float squareRootFirst = SGEXTN::Math::FloatMath<float>::squareRoot(-2.0f * SGEXTN::Math::FloatMath<float>::naturalLog(normalDistributedVars.at(2 * j)));
            const float scaledSecond = 2 * SGEXTN::Math::FloatConstants<float>::pi() * normalDistributedVars.at(2 * j + 1);
            normalDistributedVars.at(2 * j) = squareRootFirst * SGEXTN::Math::FloatMath<float>::cosine(scaledSecond);
            normalDistributedVars.at(2 * j + 1) = squareRootFirst * SGEXTN::Math::FloatMath<float>::sine(scaledSecond);
        }
        float generatedMagnitude = 0.0f;
        for(int j=0; j<private_dimension; j++){
            generatedMagnitude += normalDistributedVars.at(j) * normalDistributedVars.at(j);
        }
        generatedMagnitude = SGEXTN::Math::FloatMath<float>::squareRoot(generatedMagnitude);
        if(generatedMagnitude >= SGEXTN::Math::FloatLimits<float>::minimumPositive()){
            for(int j=0; j<private_dimension; j++){
                normalDistributedVars.at(j) = normalDistributedVars.at(j) / generatedMagnitude;
            }
        }
        else{
            normalDistributedVars.at(0) = 1.0f;
            for(int j=1; j<private_dimension; j++){
                normalDistributedVars.at(j) = 0.0f;
            }
        }
        float dotProduct = 0.0f;
        for(int j=0; j<private_dimension; j++){
            dotProduct += normalDistributedVars.at(j) * (point.at(j) - static_cast<float>(spanArray.at(j)));
        }
        cornerContribution.at(i) = dotProduct;
    }
    for(int i=private_dimension-1; i>=0; i--){
        float dist = point.at(i) - static_cast<float>(flooredCorner.at(i));
        dist = private_smoothingFunction.private_function(dist);
        for(int j=0; j<powerOf2(i); j++){
            cornerContribution.at(j) = (1.0f - dist) * cornerContribution.at(j) + dist * cornerContribution.at(j + powerOf2(i));
        }
    }
    return cornerContribution.at(0) * 2.0f / SGEXTN::Math::FloatMath<float>::squareRoot(static_cast<float>(private_dimension));
}
