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

#include <SGEXTN/SeerattraNum/BinomialDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/SeerattraNum/GeometricDistribution.h>
#include <SGEXTN/SeerattraNum/ExponentialDistribution.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::BinomialDistribution::BinomialDistribution() : SGEXTN::SeerattraNum::BinomialDistribution(true, 0.5f, 1){}

SGEXTN::SeerattraNum::BinomialDistribution::BinomialDistribution(bool useGlobal, float chanceOfTrue, int attemptCount) : chanceOfTrue_(chanceOfTrue), attemptCount_(attemptCount), rngLocator_(useGlobal), geometricDistribution_(true, 0.5f), precompConstantL_(0.0f), precompConstantC_(0.0f), precompConstantM_(0.0f), exponentialFactorLeft_(0.0f), exponentialFactorRight_(0.0f), negativeReciprocalExponentialFactorLeft_(0.0f), reciprocalExponentialFactorRight_(0.0f), boundaryFarLeft_(0.0f), boundaryCenterLeft_(0.0f), boundaryCenterRight_(0.0f), boundaryFarRight_(0.0f), weightLeftTail_(0.0f), weightBothTails_(0.0f), weightAllExceptCenter_(0.0f), comparisonMultiplier_(0.0f), comparisonConstant_(0.0f){
    if(chanceOfTrue < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested probability is higher than 1");}
    if(attemptCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested number of attempts is negative");}
    redoPrecompute();
    geometricDistribution_.setChanceOfTrue(chanceOfTrue);
}

bool SGEXTN::SeerattraNum::BinomialDistribution::sendOut(const SGEXTN::SeerattraNum::BinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, int>::sendOut(x.rngLocator_, x.chanceOfTrue_, x.attemptCount_, data);
}

bool SGEXTN::SeerattraNum::BinomialDistribution::sendIn(SGEXTN::SeerattraNum::BinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float probability = 0.0f;
    int attempts = 0;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, int>::sendIn(rngLocator, probability, attempts, data);
    if(isValid == false || probability < 0.0f || probability > 1.0f || attempts < 0){return false;}
    x = SGEXTN::SeerattraNum::BinomialDistribution(true, probability, attempts);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::BinomialDistribution::size(){
    return 45;
}

void SGEXTN::SeerattraNum::BinomialDistribution::redoPrecompute(){
    float probability = chanceOfTrue_;
    const float attempts = static_cast<float>(attemptCount_);
    if(probability > 0.5f){probability = 1.0f - probability;}
    precompConstantL_ = 0.5f + SGEXTN::Math::FloatMath<float>::floor(2.195f * SGEXTN::Math::FloatMath<float>::squareRoot(attempts * probability * (1.0f - probability)) - 4.6f * (1.0f - probability));
    precompConstantM_ = SGEXTN::Math::FloatMath<float>::floor(attempts * probability + probability);
    precompConstantC_ = 0.134f + 20.5f / (15.3f + precompConstantM_);
    const float exponentialInternalLeft = (attempts * probability + probability - (precompConstantM_ - precompConstantL_)) / (attempts * probability + probability - probability * (precompConstantM_ - precompConstantL_));
    exponentialFactorLeft_ = exponentialInternalLeft * (1.0f + 0.5f * exponentialInternalLeft);
    const float exponentialInternalRight = (precompConstantM_ + precompConstantL_ + 1.0f - attempts * probability - probability) / ((precompConstantM_ + precompConstantL_ + 1.0f) * (1.0f - probability));
    exponentialFactorRight_ = exponentialInternalRight * (1.0f + 0.5f * exponentialInternalRight);
    negativeReciprocalExponentialFactorLeft_ = -1.0f / exponentialFactorLeft_;
    reciprocalExponentialFactorRight_ = 1.0f / exponentialFactorRight_;
    boundaryFarLeft_ = precompConstantM_ - precompConstantL_ + 0.5f;
    boundaryCenterLeft_ = precompConstantM_ - precompConstantC_ * precompConstantL_ + 0.5f;
    boundaryCenterRight_ = precompConstantM_ + precompConstantC_ * precompConstantL_ + 0.5f;
    boundaryFarRight_ = precompConstantM_ + precompConstantL_ + 0.5f;
    const float w1 = precompConstantC_ / exponentialFactorLeft_;
    const float w2 = 0.5f * precompConstantL_ * (1.0f - precompConstantC_ * precompConstantC_);
    const float w3 = 2.0f * precompConstantC_ * precompConstantL_;
    const float w4 = 0.5f * precompConstantL_ * (1.0f - precompConstantC_ * precompConstantC_);
    const float w5 = precompConstantC_ / exponentialFactorRight_;
    const float weightSum = w1 + w2 + w3 + w4 + w5;
    weightLeftTail_ = w1 / weightSum;
    weightBothTails_ = (w1 + w5) / weightSum;
    weightAllExceptCenter_ = 1.0f - w3 / weightSum;
    comparisonMultiplier_ = SGEXTN::Math::FloatMath<float>::naturalLog(probability) - SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - probability);
    comparisonConstant_ = SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(precompConstantM_) + SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(attempts - precompConstantM_) - precompConstantM_ * comparisonMultiplier_;
    geometricDistribution_.setChanceOfTrue(probability);
}

void SGEXTN::SeerattraNum::BinomialDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

int SGEXTN::SeerattraNum::BinomialDistribution::randomValue(){
    if(chanceOfTrue_ == 0.0f){return 0;}
    if(chanceOfTrue_ == 1.0f){return attemptCount_;}
    if(attemptCount_ == 0){return 0;}
    bool useNegative = false;
    float probability = chanceOfTrue_;
    int result = 0;
    if(probability > 0.5f){
        probability = 1.0f - probability;
        useNegative = true;
    }
    if(static_cast<float>(attemptCount_) * probability < 30.0f){
        int count = 0;
        int sum = 0;
        while(sum <= attemptCount_){
            sum += (geometricDistribution_.randomValue(rngLocator_) + 1);
            count++;
        }
        result = count - 1;
    }
    else{
        while(true){
            float rng = (*rngLocator_).randomFloat32();
            float xCoord = 0.0f;
            float yCoord = 0.0f;
            if(rng < weightLeftTail_){
                SGEXTN::SeerattraNum::ExponentialDistribution::samplePointStandard(xCoord, yCoord, rngLocator_);
                xCoord = negativeReciprocalExponentialFactorLeft_ * xCoord + boundaryFarLeft_;
                yCoord = precompConstantC_ * yCoord;
            }
            else if(rng < weightBothTails_){
                SGEXTN::SeerattraNum::ExponentialDistribution::samplePointStandard(xCoord, yCoord, rngLocator_);
                xCoord = reciprocalExponentialFactorRight_ * xCoord + boundaryFarRight_;
                yCoord = precompConstantC_ * yCoord;
            }
            else if(rng < weightAllExceptCenter_){
                rng = (rng - weightBothTails_) / (weightAllExceptCenter_ - weightBothTails_);
                xCoord = boundaryFarLeft_ + rng * (boundaryCenterLeft_ - boundaryFarLeft_);
                yCoord = (*rngLocator_).randomFloat32() * (1.0f + precompConstantC_);
                if(yCoord > precompConstantC_ + rng * (1.0f - precompConstantC_)){
                    xCoord = boundaryCenterRight_ + xCoord - boundaryFarLeft_;
                    yCoord = 1.0f + precompConstantC_ - yCoord;
                }
            }
            else{
                rng = (rng - weightAllExceptCenter_) / (1.0f - weightAllExceptCenter_);
                xCoord = boundaryCenterLeft_ + rng * (boundaryCenterRight_ - boundaryCenterLeft_);
                yCoord = (*rngLocator_).randomFloat32();
            }
            const float flooredX = SGEXTN::Math::FloatMath<float>::floor(xCoord);
            if(static_cast<int>(flooredX) < 0 || static_cast<int>(flooredX) > attemptCount_){continue;}
            if(precompConstantL_ * yCoord <= precompConstantL_ - SGEXTN::Math::FloatMath<float>::absoluteValue(precompConstantM_ - xCoord + 0.5f)){
                result = static_cast<int>(flooredX);
                break;
            }
            if(SGEXTN::Math::FloatMath<float>::naturalLog(yCoord) + SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(flooredX) + SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(static_cast<float>(attemptCount_) - flooredX) <= flooredX * comparisonMultiplier_ + comparisonConstant_){
                result = static_cast<int>(flooredX);
                break;
            }
        }
    }
    if(useNegative == false){return result;}
    return (attemptCount_ - result);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::BinomialDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count, 0);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::BinomialDistribution::getChanceOfTrue() const {
    return chanceOfTrue_;
}

int SGEXTN::SeerattraNum::BinomialDistribution::getAttemptCount() const {
    return attemptCount_;
}

void SGEXTN::SeerattraNum::BinomialDistribution::setChanceOfTrue(float chanceOfTrue){
    if(chanceOfTrue < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setChanceOfTrue crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    chanceOfTrue_ = chanceOfTrue;
    redoPrecompute();
}

void SGEXTN::SeerattraNum::BinomialDistribution::setAttemptCount(int attemptCount){
    if(attemptCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setAttemptCount crashed because the requested number of attempts is negative");}
    attemptCount_ = attemptCount;
    redoPrecompute();
}
