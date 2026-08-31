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
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Math/FloatConstants.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

void SGEXTN::SeerattraNum::NormalDistribution::parseTables(){
    SGEXTN::SeerattraNum::NormalDistribution::hwidthTables = new SGEXTN::Containers::Array<float>(256, 0.0f);
    SGEXTN::SeerattraNum::NormalDistribution::floorTables = new SGEXTN::Containers::Array<float>(256, 0.0f);
    SGEXTN::Containers::Array<double> hwidthArray(256, 0.0f);
    SGEXTN::Containers::Array<double> floorArray(256, 0.0f);
    const double rightBound = 3.6541528853610088;
    const double rectangleArea = 0.00492867323399;
    hwidthArray.at(0) = SGEXTN::Math::FloatLimits<double>::positiveInfinity();
    floorArray.at(0) = (rectangleArea - SGEXTN::Math::FloatMath<double>::squareRoot(static_cast<double>(0.5f) * SGEXTN::Math::FloatConstants<double>::pi()) * SGEXTN::Math::FloatMath<double>::complementaryErrorFunction(rightBound / SGEXTN::Math::FloatConstants<double>::squareRoot2())) / rectangleArea;
    hwidthArray.at(1) = rightBound;
    floorArray.at(1) = SGEXTN::Math::FloatMath<double>::powerOfE(static_cast<double>(-0.5f) * rightBound * rightBound);
    for(int i=2; i<256; i++){
        floorArray.at(i) = floorArray.at(i - 1) + rectangleArea / hwidthArray.at(i - 1);
        hwidthArray.at(i) = SGEXTN::Math::FloatMath<double>::squareRoot(static_cast<double>(-2.0f) * SGEXTN::Math::FloatMath<double>::naturalLog(floorArray.at(i)));
    }
    for(int i=0; i<256; i++){
        (*SGEXTN::SeerattraNum::NormalDistribution::hwidthTables).at(i) = static_cast<float>(hwidthArray.at(i));
        (*SGEXTN::SeerattraNum::NormalDistribution::floorTables).at(i) = static_cast<float>(floorArray.at(i));
    }
}

SGEXTN::Containers::Array<float>* SGEXTN::SeerattraNum::NormalDistribution::hwidthTables = nullptr;
SGEXTN::Containers::Array<float>* SGEXTN::SeerattraNum::NormalDistribution::floorTables = nullptr;

SGEXTN::SeerattraNum::NormalDistribution::NormalDistribution() : SGEXTN::SeerattraNum::NormalDistribution(true, 0.0f, 1.0f){}

SGEXTN::SeerattraNum::NormalDistribution::NormalDistribution(bool useGlobal, float mean, float standardDeviation) : mean_(mean), standardDeviation_(standardDeviation), rngLocator_(useGlobal){
    if(standardDeviation <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution constructor crashed because requested standard deviation is nonpositive");}
}

bool SGEXTN::SeerattraNum::NormalDistribution::sendOut(const SGEXTN::SeerattraNum::NormalDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendOut(x.rngLocator_, x.mean_, x.standardDeviation_, data);
}

bool SGEXTN::SeerattraNum::NormalDistribution::sendIn(SGEXTN::SeerattraNum::NormalDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float mean = 0.0f;
    float standardDeviation = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendIn(rngLocator, mean, standardDeviation, data);
    if(isValid == false || standardDeviation <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::NormalDistribution(true, mean, standardDeviation);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::NormalDistribution::size(){
    return 45;
}

void SGEXTN::SeerattraNum::NormalDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

float SGEXTN::SeerattraNum::NormalDistribution::randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    if(SGEXTN::SeerattraNum::NormalDistribution::floorTables == nullptr){SGEXTN::SeerattraNum::NormalDistribution::parseTables();}
    float result = 0;
    int sign = 1;
    while(true){
        const unsigned int rng = (*externalLocator).randomUnsignedInt32();
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
            const float v1 = -1.0f * SGEXTN::Math::FloatMath<float>::naturalLog((*externalLocator).randomFloat32()) / rectangleBoundary;
            const float v2 = -1.0f * SGEXTN::Math::FloatMath<float>::naturalLog((*externalLocator).randomFloat32());
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
        const float yCoord = thisLayerFloor + (layerAboveFloor - thisLayerFloor) * (*externalLocator).randomFloat32();
        if(SGEXTN::Math::FloatMath<float>::naturalLog(yCoord) < -0.5f * xCoord * xCoord){
            result = xCoord;
            break;
        }
    }
    return (mean_ + result * static_cast<float>(sign) * standardDeviation_);
}

float SGEXTN::SeerattraNum::NormalDistribution::randomValue(){
    return randomValue(rngLocator_);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::NormalDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count, 0.0f);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::NormalDistribution::getMean() const {
    return mean_;
}

float SGEXTN::SeerattraNum::NormalDistribution::getStandardDeviation() const {
    return standardDeviation_;
}

void SGEXTN::SeerattraNum::NormalDistribution::setMean(float mean){
    mean_ = mean;
}

void SGEXTN::SeerattraNum::NormalDistribution::setStandardDeviation(float standardDeviation){
    if(standardDeviation <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution::setStandardDeviation crashed because requested standard deviation is nonpositive");}
    standardDeviation_ = standardDeviation;
}

float SGEXTN::SeerattraNum::NormalDistribution::fastTransform(float x){
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
