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

#include <SGEXTN/SeerattraNum/NormalDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/SeerattraNum/private_api/ZigguratTables.h>
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Math/FloatConstants.h>
#include <cmath>

namespace {
float unpackInteger(unsigned int data){
    const unsigned int sign = static_cast<int>((data & 0x80000000) >> 31);
    const unsigned int exponent = (data & 0x7f800000) >> 23;
    const unsigned int mantissa = data & 0x007fffff;
    if(exponent == 0xff){
        if(mantissa != 0){return SGEXTN::Math::FloatLimits<float>::notANumber();}
        if(sign == 1){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
        return SGEXTN::Math::FloatLimits<float>::positiveInfinity();
    }
    if(exponent == 0){
        if(mantissa == 0){
            if(sign == 1){return -0.0f;}
            return 0.0f;
        }
        if(sign == 1){return (-1.0f * std::scalbn(static_cast<float>(mantissa), -149));}
        return std::scalbn(static_cast<float>(mantissa), -149);
    }
    if(sign == 1){return (-1.0f * std::scalbn(1.0f + std::scalbn(static_cast<float>(mantissa), -23), static_cast<int>(exponent) - 127));}
    return std::scalbn(1.0f + std::scalbn(static_cast<float>(mantissa), -23), static_cast<int>(exponent) - 127);
}

float getHwidth(int i){
    const unsigned char firstByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::normalDistributionHalfWidths + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i)));
    const unsigned char secondByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::normalDistributionHalfWidths + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 1)));
    const unsigned char thirdByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::normalDistributionHalfWidths + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 2)));
    const unsigned char fourthByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::normalDistributionHalfWidths + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 3)));
    const unsigned int packedInt = (static_cast<unsigned int>(firstByte) << 24) | (static_cast<unsigned int>(secondByte) << 16) | (static_cast<unsigned int>(thirdByte) << 8) | static_cast<unsigned int>(fourthByte);
    return unpackInteger(packedInt);
}

float getFloor(int i){
    const unsigned char firstByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::normalDistributionFloors + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i)));
    const unsigned char secondByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::normalDistributionFloors + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 1)));
    const unsigned char thirdByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::normalDistributionFloors + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 2)));
    const unsigned char fourthByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::normalDistributionFloors + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 3)));
    const unsigned int packedInt = (static_cast<unsigned int>(firstByte) << 24) | (static_cast<unsigned int>(secondByte) << 16) | (static_cast<unsigned int>(thirdByte) << 8) | static_cast<unsigned int>(fourthByte);
    return unpackInteger(packedInt);
}

void parseTables(){
    SGEXTN::SeerattraNum::NormalDistribution::hwidthTables = new SGEXTN::Containers::Array<float>(256);
    SGEXTN::SeerattraNum::NormalDistribution::floorTables = new SGEXTN::Containers::Array<float>(256);
    for(int i=0; i<256; i++){
        (*SGEXTN::SeerattraNum::NormalDistribution::hwidthTables).at(i) = getHwidth(i);
        (*SGEXTN::SeerattraNum::NormalDistribution::floorTables).at(i) = getFloor(i);
    }
}
}

SGEXTN::Containers::Array<float>* SGEXTN::SeerattraNum::NormalDistribution::hwidthTables = nullptr;
SGEXTN::Containers::Array<float>* SGEXTN::SeerattraNum::NormalDistribution::floorTables = nullptr;
SGEXTN::SeerattraNum::NormalDistribution::NormalDistribution(bool useGlobal, float mean, float standardDeviation) : private_mean(mean), private_standardDeviation(standardDeviation), private_rng(nullptr), private_ownsRng(useGlobal == false){
    if(standardDeviation <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution constructor crashed because requested standard deviation is nonpositive");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
}

SGEXTN::SeerattraNum::NormalDistribution::~NormalDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::NormalDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

float SGEXTN::SeerattraNum::NormalDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    if(SGEXTN::SeerattraNum::NormalDistribution::floorTables == nullptr){parseTables();}
    float result = 0;
    int sign = 1;
    while(true){
        const unsigned int rng = (*private_rng).randomUnsignedInt32();
        const int layer = static_cast<int>((rng & 0xff000000) >> 24);
        if((rng & 0x800000) != 0){sign = -1;}
        else{sign = 1;}
        const float scaleFactor = 1.0f / static_cast<float>(1u << 23);
        float xCoord = static_cast<float>(rng & 0x7fffff) * scaleFactor;
        if(layer == 0){
            const float rectangleProportion = (*SGEXTN::SeerattraNum::NormalDistribution::floorTables).at(0);
            if(xCoord < rectangleProportion){
                xCoord /= rectangleProportion;
                result = (xCoord * (*SGEXTN::SeerattraNum::NormalDistribution::hwidthTables).at(1));
                break;
            }
            const float rectangleBoundary = (*SGEXTN::SeerattraNum::NormalDistribution::hwidthTables).at(1);
            const float v1 = -1.0f * SGEXTN::Math::FloatMath<float>::naturalLog((*private_rng).randomFloat32()) / rectangleBoundary;
            const float v2 = -1.0f * SGEXTN::Math::FloatMath<float>::naturalLog((*private_rng).randomFloat32());
            if(v1 * v1 < v2 + v2){
                result = rectangleBoundary + v1;
                break;
            }
            continue;
        }
        const float thisLayerHwidth = (*SGEXTN::SeerattraNum::NormalDistribution::hwidthTables).at(layer);
        float layerAboveHwidth = 0.0f;
        const float thisLayerFloor = (*SGEXTN::SeerattraNum::NormalDistribution::floorTables).at(layer);
        float layerAboveFloor = 0.3989422804f;
        if(layer != 255){
            layerAboveHwidth = (*SGEXTN::SeerattraNum::NormalDistribution::hwidthTables).at(layer + 1);
            layerAboveFloor = (*SGEXTN::SeerattraNum::NormalDistribution::floorTables).at(layer + 1);
        }
        xCoord *= thisLayerHwidth;
        if(xCoord < layerAboveHwidth){
            result = xCoord;
            break;
        }
        const float yCoord = thisLayerFloor + (layerAboveFloor - thisLayerFloor) * (*private_rng).randomFloat32();
        if(SGEXTN::Math::FloatMath<float>::naturalLog(yCoord) < -0.5f * xCoord * xCoord){
            result = xCoord;
            break;
        }
    }
    return (private_mean + result * static_cast<float>(sign) * private_standardDeviation);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::NormalDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::NormalDistribution::getMean() const {
    return private_mean;
}

float SGEXTN::SeerattraNum::NormalDistribution::getStandardDeviation() const {
    return private_standardDeviation;
}

void SGEXTN::SeerattraNum::NormalDistribution::setMean(float mean){
    private_mean = mean;
}

void SGEXTN::SeerattraNum::NormalDistribution::setStandardDeviation(float standardDeviation){
    if(standardDeviation <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::setStandardDeviation crashed because requested standard deviation is nonpositive");}
    private_standardDeviation = standardDeviation;
}

float SGEXTN::SeerattraNum::NormalDistribution::private_fastTransform(float x){
    x = 2.0f * x - 1.0f;
    if(x == -1.0f || x == 1.0f){x = 0.0f;}
    if(x == 0.0f){return 0.0f;}
    const float sign = x / SGEXTN::Math::FloatMath<float>::absoluteValue(x);
    const float lnOneMinusXSquared = SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - x * x);
    const float a = 0.140012288687f;
    const float reciprocalA = 7.14223022408f;
    const float twoOverPiA = 4.54688497945f;
    const float sum = twoOverPiA + 0.5f * lnOneMinusXSquared;
    const float innerSqrtInside = sum * sum - lnOneMinusXSquared * reciprocalA;
    const float outerSqrtInside = SGEXTN::Math::FloatMath<float>::squareRoot(innerSqrtInside) - sum;
    return (SGEXTN::Math::FloatConstants<float>::squareRoot2() * sign * SGEXTN::Math::FloatMath<float>::squareRoot(outerSqrtInside));
}
