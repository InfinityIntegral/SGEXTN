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

#include <SGEXTN/SeerattraNum/ExponentialDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/SeerattraNum/private_api/ZigguratTables.h>
#include <SGEXTN/Math/FloatLimits.h>
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

float getWidth(int i){
    const unsigned char firstByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::exponentialDistributionWidths + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i)));
    const unsigned char secondByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::exponentialDistributionWidths + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 1)));
    const unsigned char thirdByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::exponentialDistributionWidths + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 2)));
    const unsigned char fourthByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::exponentialDistributionWidths + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 3)));
    const unsigned int packedInt = (static_cast<unsigned int>(firstByte) << 24) | (static_cast<unsigned int>(secondByte) << 16) | (static_cast<unsigned int>(thirdByte) << 8) | static_cast<unsigned int>(fourthByte);
    return unpackInteger(packedInt);
}

float getFloor(int i){
    const unsigned char firstByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::exponentialDistributionFloors + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i)));
    const unsigned char secondByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::exponentialDistributionFloors + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 1)));
    const unsigned char thirdByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::exponentialDistributionFloors + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 2)));
    const unsigned char fourthByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::ZigguratTables::exponentialDistributionFloors + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(4 * i + 3)));
    const unsigned int packedInt = (static_cast<unsigned int>(firstByte) << 24) | (static_cast<unsigned int>(secondByte) << 16) | (static_cast<unsigned int>(thirdByte) << 8) | static_cast<unsigned int>(fourthByte);
    return unpackInteger(packedInt);
}

void parseTables(){
    SGEXTN::SeerattraNum::ExponentialDistribution::widthTables = new SGEXTN::Containers::Array<float>(256);
    SGEXTN::SeerattraNum::ExponentialDistribution::floorTables = new SGEXTN::Containers::Array<float>(256);
    for(int i=0; i<256; i++){
        (*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(i) = getWidth(i);
        (*SGEXTN::SeerattraNum::ExponentialDistribution::floorTables).at(i) = getFloor(i);
    }
}
}

SGEXTN::Containers::Array<float>* SGEXTN::SeerattraNum::ExponentialDistribution::widthTables = nullptr;
SGEXTN::Containers::Array<float>* SGEXTN::SeerattraNum::ExponentialDistribution::floorTables = nullptr;

SGEXTN::SeerattraNum::ExponentialDistribution::ExponentialDistribution(bool useGlobal, float meanEventsPerTime) : private_meanEventsPerTime(meanEventsPerTime), private_reciprocalRate(1.0f / meanEventsPerTime), private_rng(nullptr), private_ownsRng(useGlobal == false){
    if(meanEventsPerTime <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution constructor crashed because requested number of events occurring in each unit time is nonpositive");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
}

SGEXTN::SeerattraNum::ExponentialDistribution::~ExponentialDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::ExponentialDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

float SGEXTN::SeerattraNum::ExponentialDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    if(SGEXTN::SeerattraNum::ExponentialDistribution::floorTables == nullptr){parseTables();}
    float result = 0;
    while(true){
        const unsigned int rng = (*private_rng).randomUnsignedInt32();
        const int layer = static_cast<int>((rng & 0xff000000) >> 24);
        const float scaleFactor = 1.0f / static_cast<float>(1u << 24);
        float xCoord = static_cast<float>(rng & 0xffffff) * scaleFactor;
        if(layer == 0){
            const float rectangleProportion = (*SGEXTN::SeerattraNum::ExponentialDistribution::floorTables).at(0);
            if(xCoord < rectangleProportion){
                xCoord /= rectangleProportion;
                result = (xCoord * (*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(1));
                break;
            }
            result = ((*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(1) - SGEXTN::Math::FloatMath<float>::naturalLog((*private_rng).randomFloat32()));
            break;
        }
        const float thisLayerWidth = (*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(layer);
        float layerAboveWidth = 0.0f;
        const float thisLayerFloor = (*SGEXTN::SeerattraNum::ExponentialDistribution::floorTables).at(layer);
        float layerAboveFloor = 1.0f;
        if(layer != 255){
            layerAboveWidth = (*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(layer + 1);
            layerAboveFloor = (*SGEXTN::SeerattraNum::ExponentialDistribution::floorTables).at(layer + 1);
        }
        xCoord *= thisLayerWidth;
        if(xCoord < layerAboveWidth){
            result = xCoord;
            break;
        }
        const float yCoord = thisLayerFloor + (layerAboveFloor - thisLayerFloor) * (*private_rng).randomFloat32();
        if(SGEXTN::Math::FloatMath<float>::naturalLog(yCoord) < -1.0f * xCoord){
            result = xCoord;
            break;
        }
    }
    return (result * private_reciprocalRate);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::ExponentialDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::ExponentialDistribution::getMeanEventsPerTime() const {
    return private_meanEventsPerTime;
}

void SGEXTN::SeerattraNum::ExponentialDistribution::setMeanEventsPerTime(float meanEventsPerTime){
    if(meanEventsPerTime <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::setMeanEventsPerTime crashed because requested number of events occurring in each unit time is nonpositive");}
    private_meanEventsPerTime = meanEventsPerTime;
    private_reciprocalRate = 1.0f / meanEventsPerTime;
}
