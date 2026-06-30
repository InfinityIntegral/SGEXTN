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
#include <SGEXTN/Containers/private_api/HashAlgorithm.h>
#include <SGEXTN/Math/IntegerLimits.h>
#include <SGEXTN/Math/FloatConstants.h>
#include <SGEXTN/Containers/Array.h>

namespace {
SGEXTN::Containers::Array<float> getFeaturePoint(int seed, const SGEXTN::Containers::Array<int>& center){
    const int dimensions = center.length();
    SGEXTN::Containers::Array<int> spanArray(dimensions + 2);
    for(int i=0; i<dimensions; i++){
        spanArray.at(i) = center.at(i);
    }
    spanArray.at(dimensions) = seed;
    const SGEXTN::Containers::Span<const unsigned char> span(reinterpret_cast<const unsigned char*>(&spanArray.at(0)), (dimensions + 2) * static_cast<int>(sizeof(int)));
    int normalVarCount = dimensions;
    if(dimensions % 2 == 1){normalVarCount++;}
    SGEXTN::Containers::Array<float> normalDistributedVars(normalVarCount);
    const double maximum = static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) + 1.0;
    for(int i=0; i<normalVarCount; i++){
        spanArray.at(dimensions + 1) = i;
        const unsigned int rngUnsigned = static_cast<unsigned int>(SGEXTN::Containers::HashAlgorithm::wyHash32(span));
        normalDistributedVars.at(i) = static_cast<float>(static_cast<double>(rngUnsigned) / maximum);
    }
    for(int i=0; i<normalVarCount/2; i++){
        const float squareRootFirst = SGEXTN::Math::FloatMath<float>::squareRoot(-2.0f * SGEXTN::Math::FloatMath<float>::naturalLog(normalDistributedVars.at(2 * i)));
        const float scaledSecond = 2 * SGEXTN::Math::FloatConstants<float>::pi() * normalDistributedVars.at(2 * i + 1);
        normalDistributedVars.at(2 * i) = squareRootFirst * SGEXTN::Math::FloatMath<float>::cosine(scaledSecond);
        normalDistributedVars.at(2 * i + 1) = squareRootFirst * SGEXTN::Math::FloatMath<float>::sine(scaledSecond);
    }
    float generatedMagnitude = 0.0f;
    for(int i=0; i<dimensions; i++){
        generatedMagnitude += normalDistributedVars.at(i) * normalDistributedVars.at(i);
    }
    generatedMagnitude = SGEXTN::Math::FloatMath<float>::squareRoot(generatedMagnitude);
    float magnitude = 0.0f;
    {
        spanArray.at(dimensions + 1) = dimensions + 2;
        const unsigned int rngSigned = static_cast<unsigned int>(SGEXTN::Containers::HashAlgorithm::wyHash32(span));
        magnitude = 0.5f * static_cast<float>(static_cast<double>(rngSigned) / maximum);
    }
    SGEXTN::Containers::Array<float> outputPoint(dimensions);
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

SGEXTN::SeerattraNum::VoronoiNoise::VoronoiNoise(int dimension) : private_dimension(dimension), private_seed(SGEXTN::SeerattraNum::TrueRandom::randomInt32()){
    if(dimension <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise constructor crashed because the number of dimensions is nonpositive");}
}

void SGEXTN::SeerattraNum::VoronoiNoise::seed(int seed){
    private_seed = seed;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::VoronoiNoise::getPosition(int nthNearest, const SGEXTN::Containers::Array<float>& point) const {
    if(nthNearest < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getPosition crashed because point index is negative");}
    if(nthNearest > 2 * private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getPosition crashed because only querying the nearest 2n + 1 points, where n is the number of dimensions, is supported");}
    if(point.length() != private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getPosition crashed because the number of dimensions in the point does not match that of the noise generator");}
    SGEXTN::Containers::Array<float> distancesSquared(nthNearest + 1, SGEXTN::Math::FloatLimits<float>::positiveInfinity());
    SGEXTN::Containers::Array<SGEXTN::Containers::Array<float>> points(nthNearest + 1, SGEXTN::Containers::Array<float>(0));
    SGEXTN::Containers::Array<int> nearestCenter(private_dimension);
    for(int i=0; i<private_dimension; i++){
        nearestCenter.at(i) = SGEXTN::Math::FloatMath<float>::roundToInt(point.at(i));
    }
    int powerOf3 = 1;
    for(int i=0; i<private_dimension; i++){
        powerOf3 *= 3;
    }
    SGEXTN::Containers::Array<int> currentVertex(private_dimension);
    for(int i=0; i<powerOf3; i++){
        int thisNumber = i;
        for(int j=0; j<private_dimension; j++){
            currentVertex.at(private_dimension - 1 - j) = thisNumber % 3 - 1 + nearestCenter.at(private_dimension - 1 - j);
            thisNumber /= 3;
        }
        SGEXTN::Containers::Array<float> featurePoint = getFeaturePoint(private_seed, currentVertex);
        float distanceSquared = 0.0f;
        for(int j=0; j<private_dimension; j++){
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
    if(nthNearest > 2 * private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getVectorFrom crashed because only querying the nearest 2n + 1 points, where n is the number of dimensions, is supported");}
    if(point.length() != private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getVectorFrom crashed because the number of dimensions in the point does not match that of the noise generator");}
    SGEXTN::Containers::Array<float> referencePoint = getPosition(nthNearest, point);
    SGEXTN::Containers::Array<float> output(private_dimension);
    for(int i=0; i<private_dimension; i++){
        output.at(i) = point.at(i) - referencePoint.at(i);
    }
    return output;
}

float SGEXTN::SeerattraNum::VoronoiNoise::getDistanceTo(int nthNearest, const SGEXTN::Containers::Array<float>& point) const {
    if(nthNearest < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getDistanceTo crashed because point index is negative");}
    if(nthNearest > 2 * private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getDistanceTo crashed because only querying the nearest 2n + 1 points, where n is the number of dimensions, is supported");}
    if(point.length() != private_dimension){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise::getDistanceTo crashed because the number of dimensions in the point does not match that of the noise generator");}
    float distanceSquared = 0.0f;
    SGEXTN::Containers::Array<float> difference = getVectorFrom(nthNearest, point);
    for(int i=0; i<private_dimension; i++){
        distanceSquared += difference.at(i) * difference.at(i);
    }
    return SGEXTN::Math::FloatMath<float>::squareRoot(distanceSquared);
}
