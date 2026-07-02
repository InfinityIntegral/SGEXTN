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

#include <SGEXTN/SeerattraNum/ValueNoise.h>
#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Containers/Span.h>
#include <SGEXTN/Containers/private_api/HashAlgorithm.h>
#include <SGEXTN/SeerattraNum/SmoothingFunction.h>
#include <SGEXTN/Containers/Array.h>

namespace {
int powerOf2(int n){
    return (1 << n);
}
}

SGEXTN::SeerattraNum::ValueNoise::ValueNoise(int dimension, SGEXTN::SeerattraNum::SmoothingFunction smoothingFunction) : private_dimension(dimension), private_seed(SGEXTN::SeerattraNum::TrueRandom::randomInt32()), private_smoothingFunction(smoothingFunction){
    if(dimension <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise constructor crashed because the number of dimensions is nonpositive");}
}

void SGEXTN::SeerattraNum::ValueNoise::seed(int seed){
    private_seed = seed;
}

float SGEXTN::SeerattraNum::ValueNoise::getHeight(const SGEXTN::Containers::Array<float>& point) const {
    if(point.length() != private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise::getHeight crashed because the number of dimensions in the point does not match that of the noise generator");}
    SGEXTN::Containers::Array<float> cornerHeights(powerOf2(private_dimension));
    SGEXTN::Containers::Array<int> flooredCorner(private_dimension);
    for(int i=0; i<private_dimension; i++){
        flooredCorner.at(i) = SGEXTN::Math::FloatMath<float>::floorToInt(point.at(i));
    }
    SGEXTN::Containers::Array<int> spanArray(private_dimension + 1);
    spanArray.at(private_dimension) = private_seed;
    const SGEXTN::Containers::Span<const unsigned char> span(reinterpret_cast<const unsigned char*>(&spanArray.at(0)), (private_dimension + 1) *static_cast<int>(sizeof(int)));
    const float scaleFactor = 1.0f / static_cast<float>(static_cast<unsigned int>(1) << 24) * 2.0f;
    for(int i=0; i<powerOf2(private_dimension); i++){
        for(int j=0; j<private_dimension; j++){
            if((i & powerOf2(j)) == 0){spanArray.at(j) = flooredCorner.at(j);}
            else{spanArray.at(j) = flooredCorner.at(j) + 1;}
        }
        const unsigned int rngUnsigned = static_cast<unsigned int>(SGEXTN::Containers::HashAlgorithm::wyHash32(span));
        cornerHeights.at(i) = static_cast<float>(rngUnsigned >> 8) * scaleFactor - 1.0f;
    }
    for(int i=private_dimension-1; i>=0; i--){
        float dist = point.at(i) - static_cast<float>(flooredCorner.at(i));
        dist = private_smoothingFunction.private_function(dist);
        for(int j=0; j<powerOf2(i); j++){
            cornerHeights.at(j) = (1.0f - dist) * cornerHeights.at(j) + dist * cornerHeights.at(j + powerOf2(i));
        }
    }
    return cornerHeights.at(0);
}
