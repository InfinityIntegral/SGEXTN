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
#include <SGEXTN/Containers/Hash.h>
#include <SGEXTN/SeerattraNum/SmoothingFunction.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/Serialise.h>

namespace {
int powerOf2(int n){
    return (1 << n);
}
}

SGEXTN::SeerattraNum::ValueNoise::ValueNoise() : SGEXTN::SeerattraNum::ValueNoise(1, SGEXTN::SeerattraNum::SmoothingFunction::polynomial2){}

SGEXTN::SeerattraNum::ValueNoise::ValueNoise(int dimension, SGEXTN::SeerattraNum::SmoothingFunction smoothingFunction) : private_dimension(dimension), private_seed(SGEXTN::SeerattraNum::TrueRandom::randomInt32()), private_smoothingFunction(smoothingFunction){
    if(dimension <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise constructor crashed because the number of dimensions is nonpositive");}
}

bool SGEXTN::SeerattraNum::ValueNoise::sendOut(const SGEXTN::SeerattraNum::ValueNoise& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<int, int, SGEXTN::SeerattraNum::SmoothingFunction>::sendOut(x.private_dimension, x.private_seed, x.private_smoothingFunction, data);
}

bool SGEXTN::SeerattraNum::ValueNoise::sendIn(SGEXTN::SeerattraNum::ValueNoise& x, SGEXTN::Containers::Span<unsigned char> data){
    int dimensions = 0;
    int seed = 0;
    SGEXTN::SeerattraNum::SmoothingFunction func;
    const bool isValid = SGEXTN::Containers::Serialise<int, int, SGEXTN::SeerattraNum::SmoothingFunction>::sendIn(dimensions, seed, func, data);
    if(isValid == false || dimensions <= 0){return false;}
    x = SGEXTN::SeerattraNum::ValueNoise(dimensions, func);
    x.seed(seed);
    return true;
}

int SGEXTN::SeerattraNum::ValueNoise::size(){
    return 9;
}

void SGEXTN::SeerattraNum::ValueNoise::seed(int seed){
    private_seed = seed;
}

float SGEXTN::SeerattraNum::ValueNoise::getHeight(const SGEXTN::Containers::Array<float>& point) const {
    if(point.length() != private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise::getHeight crashed because the number of dimensions in the point does not match that of the noise generator");}
    SGEXTN::Containers::Array<float> cornerHeights(powerOf2(private_dimension), 0.0f);
    SGEXTN::Containers::Array<int> flooredCorner(private_dimension, 0);
    for(int i=0; i<private_dimension; i++){
        flooredCorner.at(i) = SGEXTN::Math::FloatMath<float>::floorToInt(point.at(i));
    }
    SGEXTN::Containers::Array<unsigned char> serialiseBuffer(4 * private_dimension + 4, static_cast<unsigned char>(0));
    bool isValid = false;
    isValid = SGEXTN::Containers::Serialise<int>::sendOut(private_seed, SGEXTN::Containers::Span<unsigned char>(serialiseBuffer, 4 * private_dimension, 4));
    if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise failed to generate height due to serialisation issues");}
    const float scaleFactor = 1.0f / static_cast<float>(static_cast<unsigned int>(1) << 24) * 2.0f;
    for(int i=0; i<powerOf2(private_dimension); i++){
        for(int j=0; j<private_dimension; j++){
            if((i & powerOf2(j)) == 0){
                isValid = SGEXTN::Containers::Serialise<int>::sendOut(flooredCorner.at(j), SGEXTN::Containers::Span<unsigned char>(serialiseBuffer, 4 * j, 4));
                if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise failed to generate height due to serialisation issues");}
            }
            else{
                isValid = SGEXTN::Containers::Serialise<int>::sendOut(flooredCorner.at(j) + 1, SGEXTN::Containers::Span<unsigned char>(serialiseBuffer, 4 * j, 4));
                if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise failed to generate height due to serialisation issues");}
            }
        }
        const unsigned int rngUnsigned = static_cast<unsigned int>(SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<unsigned char>(serialiseBuffer)));
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
