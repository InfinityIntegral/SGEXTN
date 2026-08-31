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
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

void SGEXTN::SeerattraNum::ExponentialDistribution::parseTables(){
    SGEXTN::SeerattraNum::ExponentialDistribution::widthTables = new SGEXTN::Containers::Array<float>(256, 0.0f);
    SGEXTN::SeerattraNum::ExponentialDistribution::floorTables = new SGEXTN::Containers::Array<float>(256, 0.0f);
    SGEXTN::Containers::Array<double> widthArray(256, 0.0f);
    SGEXTN::Containers::Array<double> floorArray(256, 0.0f);
    const double rightBound = 7.69711747013104972;
    const double rectangleArea = 0.003949653420019919;
    const double expNegativeRightBound = SGEXTN::Math::FloatMath<double>::powerOfE(static_cast<double>(-1.0f) *rightBound);
    widthArray.at(0) = SGEXTN::Math::FloatLimits<double>::positiveInfinity();
    floorArray.at(0) = (rectangleArea - expNegativeRightBound) / rectangleArea;
    widthArray.at(1) = rightBound;
    floorArray.at(1) = expNegativeRightBound;
    for(int i=2; i<256; i++){
        floorArray.at(i) = floorArray.at(i - 1) + rectangleArea / widthArray.at(i - 1);
        widthArray.at(i) = static_cast<double>(-1.0f) * SGEXTN::Math::FloatMath<double>::naturalLog(floorArray.at(i));
    }
    for(int i=0; i<256; i++){
        (*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(i) = static_cast<float>(widthArray.at(i));
        (*SGEXTN::SeerattraNum::ExponentialDistribution::floorTables).at(i) = static_cast<float>(floorArray.at(i));
    }
    SGEXTN::SeerattraNum::ExponentialDistribution::expRightBoundary = SGEXTN::Math::FloatMath<float>::powerOfE((*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(1));
}

SGEXTN::Containers::Array<float>* SGEXTN::SeerattraNum::ExponentialDistribution::widthTables = nullptr;
SGEXTN::Containers::Array<float>* SGEXTN::SeerattraNum::ExponentialDistribution::floorTables = nullptr;
float SGEXTN::SeerattraNum::ExponentialDistribution::expRightBoundary = 0.0f;

SGEXTN::SeerattraNum::ExponentialDistribution::ExponentialDistribution() : SGEXTN::SeerattraNum::ExponentialDistribution(true, 1.0f){}

SGEXTN::SeerattraNum::ExponentialDistribution::ExponentialDistribution(bool useGlobal, float meanEventsPerTime) : meanEventsPerTime_(meanEventsPerTime), reciprocalRate_(1.0f / meanEventsPerTime), rngLocator_(useGlobal){
    if(meanEventsPerTime <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution constructor crashed because requested number of events occurring in each unit time is nonpositive");}
}

bool SGEXTN::SeerattraNum::ExponentialDistribution::sendOut(const SGEXTN::SeerattraNum::ExponentialDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendOut(x.rngLocator_, x.meanEventsPerTime_, data);
}

bool SGEXTN::SeerattraNum::ExponentialDistribution::sendIn(SGEXTN::SeerattraNum::ExponentialDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float rate = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float>::sendIn(rngLocator, rate, data);
    if(isValid == false || rate <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::ExponentialDistribution(true, rate);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::ExponentialDistribution::size(){
    return 41;
}

void SGEXTN::SeerattraNum::ExponentialDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

float SGEXTN::SeerattraNum::ExponentialDistribution::randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    if(SGEXTN::SeerattraNum::ExponentialDistribution::floorTables == nullptr){SGEXTN::SeerattraNum::ExponentialDistribution::parseTables();}
    float result = 0;
    while(true){
        const unsigned int rng = (*externalLocator).randomUnsignedInt32();
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
            result = ((*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(1) - SGEXTN::Math::FloatMath<float>::naturalLog((*externalLocator).randomFloat32()));
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
        const float yCoord = thisLayerFloor + (layerAboveFloor - thisLayerFloor) * (*externalLocator).randomFloat32();
        if(SGEXTN::Math::FloatMath<float>::naturalLog(yCoord) < -1.0f * xCoord){
            result = xCoord;
            break;
        }
    }
    return (result * reciprocalRate_);
}

float SGEXTN::SeerattraNum::ExponentialDistribution::randomValue(){
    return randomValue(rngLocator_);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::ExponentialDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count, 0.0f);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::ExponentialDistribution::getMeanEventsPerTime() const {
    return meanEventsPerTime_;
}

void SGEXTN::SeerattraNum::ExponentialDistribution::setMeanEventsPerTime(float meanEventsPerTime){
    if(meanEventsPerTime <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::setMeanEventsPerTime crashed because requested number of events occurring in each unit time is nonpositive");}
    meanEventsPerTime_ = meanEventsPerTime;
    reciprocalRate_ = 1.0f / meanEventsPerTime;
}

void SGEXTN::SeerattraNum::ExponentialDistribution::samplePointStandard(float& x, float& y, SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator){
    if(SGEXTN::SeerattraNum::ExponentialDistribution::floorTables == nullptr){SGEXTN::SeerattraNum::ExponentialDistribution::parseTables();}
    while(true){
        const unsigned int rng = (*externalLocator).randomUnsignedInt32();
        const int layer = static_cast<int>((rng & 0xff000000) >> 24);
        const float scaleFactor = 1.0f / static_cast<float>(1u << 24);
        float xCoord = static_cast<float>(rng & 0xffffff) * scaleFactor;
        if(layer == 0){
            const float rectangleProportion = (*SGEXTN::SeerattraNum::ExponentialDistribution::floorTables).at(0);
            if(xCoord < rectangleProportion){
                xCoord /= rectangleProportion;
                x = (xCoord * (*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(1));
                y = (*SGEXTN::SeerattraNum::ExponentialDistribution::floorTables).at(1) * (*externalLocator).randomFloat32();
                return;
            }
            const float newRng = (*externalLocator).randomFloat32();
            x = ((*SGEXTN::SeerattraNum::ExponentialDistribution::widthTables).at(1) - SGEXTN::Math::FloatMath<float>::naturalLog(newRng));
            y = newRng / SGEXTN::SeerattraNum::ExponentialDistribution::expRightBoundary;
            return;
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
        const float yCoord = thisLayerFloor + (layerAboveFloor - thisLayerFloor) * (*externalLocator).randomFloat32();
        if(xCoord < layerAboveWidth){
            x = xCoord;
            y = yCoord;
            return;
        }
        if(SGEXTN::Math::FloatMath<float>::naturalLog(yCoord) < -1.0f * xCoord){
            x = xCoord;
            y = yCoord;
            return;
        }
    }
}
