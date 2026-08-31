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

#include <SGEXTN/SeerattraNum/VoronoiNoise.h>
#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Containers/Span.h>
#include <SGEXTN/Containers/Hash.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/SeerattraNum/NormalDistribution.h>
#include <SGEXTN/Containers/Serialise.h>

namespace {
SGEXTN::Containers::Array<float> getFeaturePoint(int seed, const SGEXTN::Containers::Array<int>& center){
    const int dimensions = center.length();
    SGEXTN::Containers::Array<unsigned char> serialiseBuffer(4 * dimensions + 8, static_cast<unsigned char>(0));
    bool isValid = false;
    for(int i=0; i<dimensions; i++){
        isValid = SGEXTN::Containers::Serialise<int>::sendOut(center.at(i), SGEXTN::Containers::Span<unsigned char>(serialiseBuffer, 4 * i, 4));
        if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise failed to generate feature point due to serialisation issues");}
    }
    isValid = SGEXTN::Containers::Serialise<int>::sendOut(seed, SGEXTN::Containers::Span<unsigned char>(serialiseBuffer, 4 * dimensions, 4));
    if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise failed to generate feature point due to serialisation issues");}
    SGEXTN::Containers::Array<float> normalDistributedVars(dimensions, 0.0f);
    const float scaleFactor = 1.0f / static_cast<float>(static_cast<unsigned int>(1) << 24);
    for(int i=0; i<dimensions; i++){
        isValid = SGEXTN::Containers::Serialise<int>::sendOut(i, SGEXTN::Containers::Span<unsigned char>(serialiseBuffer, 4 * dimensions + 4, 4));
        if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise failed to generate feature point due to serialisation issues");}
        const unsigned int rngUnsigned = static_cast<unsigned int>(SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<unsigned char>(serialiseBuffer)));
        normalDistributedVars.at(i) = static_cast<float>(rngUnsigned >> 8) * scaleFactor;
        normalDistributedVars.at(i) = SGEXTN::SeerattraNum::NormalDistribution::fastTransform(normalDistributedVars.at(i));
    }
    float generatedMagnitude = 0.0f;
    for(int i=0; i<dimensions; i++){
        generatedMagnitude += normalDistributedVars.at(i) * normalDistributedVars.at(i);
    }
    generatedMagnitude = SGEXTN::Math::FloatMath<float>::squareRoot(generatedMagnitude);
    float magnitude = 0.0f;
    {
        isValid = SGEXTN::Containers::Serialise<int>::sendOut(dimensions + 2, SGEXTN::Containers::Span<unsigned char>(serialiseBuffer, 4 * dimensions + 4, 4));
        if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise failed to generate feature point due to serialisation issues");}
        const unsigned int rngUnsigned = static_cast<unsigned int>(SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<unsigned char>(serialiseBuffer)));
        magnitude = 0.5f * static_cast<float>(rngUnsigned >> 8) * scaleFactor;
    }
    SGEXTN::Containers::Array<float> outputPoint(dimensions, 0.0f);
    if(generatedMagnitude >= SGEXTN::Math::FloatLimits<float>::minimumPositive()){
        for(int i=0; i<dimensions; i++){
            outputPoint.at(i) = (normalDistributedVars.at(i) / generatedMagnitude * magnitude) + static_cast<float>(center.at(i));
        }
    }
    else{
        for(int i=0; i<dimensions; i++){
            outputPoint.at(i) = static_cast<float>(center.at(i));
        }
    }
    return outputPoint;
}
}

SGEXTN::SeerattraNum::VoronoiNoise::VoronoiNoise() : SGEXTN::SeerattraNum::VoronoiNoise(1){}

SGEXTN::SeerattraNum::VoronoiNoise::VoronoiNoise(int dimension) : dimension_(dimension), seed_(SGEXTN::SeerattraNum::TrueRandom::randomInt32()){
    if(dimension <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise constructor crashed because the number of dimensions is nonpositive");}
}

bool SGEXTN::SeerattraNum::VoronoiNoise::sendOut(const SGEXTN::SeerattraNum::VoronoiNoise& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<int, int>::sendOut(x.dimension_, x.seed_, data);
}

bool SGEXTN::SeerattraNum::VoronoiNoise::sendIn(SGEXTN::SeerattraNum::VoronoiNoise& x, SGEXTN::Containers::Span<unsigned char> data){
    int dimensions = 0;
    int seed = 0;
    const bool isValid = SGEXTN::Containers::Serialise<int, int>::sendIn(dimensions, seed, data);
    if(isValid == false || dimensions <= 0){return false;}
    x = SGEXTN::SeerattraNum::VoronoiNoise(dimensions);
    x.seed(seed);
    return true;
}

int SGEXTN::SeerattraNum::VoronoiNoise::size(){
    return 8;
}

void SGEXTN::SeerattraNum::VoronoiNoise::seed(int seed){
    seed_ = seed;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::VoronoiNoise::getPosition(int nthNearest, const SGEXTN::Containers::Array<float>& point) const {
    if(nthNearest < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getPosition crashed because point index is negative");}
    if(nthNearest > 2 * dimension_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getPosition crashed because only querying the nearest 2n + 1 points, where n is the number of dimensions, is supported");}
    if(point.length() != dimension_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getPosition crashed because the number of dimensions in the point does not match that of the noise generator");}
    SGEXTN::Containers::Array<float> distancesSquared(nthNearest + 1, SGEXTN::Math::FloatLimits<float>::positiveInfinity());
    SGEXTN::Containers::Array<SGEXTN::Containers::Array<float>> points(nthNearest + 1, SGEXTN::Containers::Array<float>());
    SGEXTN::Containers::Array<int> nearestCenter(dimension_, 0);
    for(int i=0; i<dimension_; i++){
        nearestCenter.at(i) = SGEXTN::Math::FloatMath<float>::roundToInt(point.at(i));
    }
    int powerOf3 = 1;
    for(int i=0; i<dimension_; i++){
        powerOf3 *= 3;
    }
    SGEXTN::Containers::Array<int> currentVertex(dimension_, 0);
    for(int i=0; i<powerOf3; i++){
        int thisNumber = i;
        for(int j=0; j<dimension_; j++){
            currentVertex.at(dimension_ - 1 - j) = thisNumber % 3 - 1 + nearestCenter.at(dimension_ - 1 - j);
            thisNumber /= 3;
        }
        SGEXTN::Containers::Array<float> featurePoint = getFeaturePoint(seed_, currentVertex);
        float distanceSquared = 0.0f;
        for(int j=0; j<dimension_; j++){
            distanceSquared += (point.at(j) - featurePoint.at(j)) * (point.at(j) - featurePoint.at(j));
        }
        for(int j=0; j<=nthNearest; j++){
            if(distanceSquared < distancesSquared.at(j)){
                for(int k=nthNearest-1; k>=j; k--){
                    distancesSquared.at(k + 1) = distancesSquared.at(k);
                    points.at(k + 1) = static_cast<SGEXTN::Containers::Array<float>&&>(points.at(k));
                }
                distancesSquared.at(j) = distanceSquared;
                points.at(j) = static_cast<SGEXTN::Containers::Array<float>&&>(featurePoint);
                break;
            }
        }
    }
    return points.at(nthNearest);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::VoronoiNoise::getVectorFrom(int nthNearest, const SGEXTN::Containers::Array<float>& point) const {
    if(nthNearest < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getVectorFrom crashed because point index is negative");}
    if(nthNearest > 2 * dimension_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getVectorFrom crashed because only querying the nearest 2n + 1 points, where n is the number of dimensions, is supported");}
    if(point.length() != dimension_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getVectorFrom crashed because the number of dimensions in the point does not match that of the noise generator");}
    SGEXTN::Containers::Array<float> referencePoint = getPosition(nthNearest, point);
    SGEXTN::Containers::Array<float> output(dimension_, 0.0f);
    for(int i=0; i<dimension_; i++){
        output.at(i) = point.at(i) - referencePoint.at(i);
    }
    return output;
}

float SGEXTN::SeerattraNum::VoronoiNoise::getDistanceTo(int nthNearest, const SGEXTN::Containers::Array<float>& point) const {
    if(nthNearest < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getDistanceTo crashed because point index is negative");}
    if(nthNearest > 2 * dimension_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getDistanceTo crashed because only querying the nearest 2n + 1 points, where n is the number of dimensions, is supported");}
    if(point.length() != dimension_){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getDistanceTo crashed because the number of dimensions in the point does not match that of the noise generator");}
    float distanceSquared = 0.0f;
    SGEXTN::Containers::Array<float> difference = getVectorFrom(nthNearest, point);
    for(int i=0; i<dimension_; i++){
        distanceSquared += difference.at(i) * difference.at(i);
    }
    return SGEXTN::Math::FloatMath<float>::squareRoot(distanceSquared);
}
