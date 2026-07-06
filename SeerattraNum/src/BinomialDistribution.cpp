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

SGEXTN::SeerattraNum::BinomialDistribution::BinomialDistribution(bool useGlobal, float chanceOfTrue, int attemptCount) :private_chanceOfTrue(chanceOfTrue), private_attemptCount(attemptCount), private_rng(nullptr), private_ownsRng(useGlobal == false), private_geometricDistribution(true, 0.5f), private_standardExponentialDistribution(true, 1.0f), private_precompConstantL(0.0f), private_precompConstantC(0.0f), private_precompConstantM(0.0f), private_exponentialFactorLeft(0.0f), private_exponentialFactorRight(0.0f), private_negativeReciprocalExponentialFactorLeft(0.0f), private_reciprocalExponentialFactorRight(0.0f), private_boundaryFarLeft(0.0f), private_boundaryCenterLeft(0.0f), private_boundaryCenterRight(0.0f), private_boundaryFarRight(0.0f), private_weightLeftTail(0.0f), private_weightBothTails(0.0f), private_weightAllExceptCenter(0.0f), private_comparisonMultiplier(0.0f), private_comparisonConstant(0.0f){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested probability is higher than 1");}
    if(attemptCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution constructor crashed because the requested number of attempts is negative");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
    private_redoPrecompute();
    private_geometricDistribution.private_rng = private_rng;
    private_geometricDistribution.private_bernoulliDistribution.private_rng = private_rng;
    private_standardExponentialDistribution.private_rng = private_rng;
    private_geometricDistribution.setChanceOfTrue(chanceOfTrue);
}

SGEXTN::SeerattraNum::BinomialDistribution::~BinomialDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::BinomialDistribution::private_redoPrecompute(){
    float probability = private_chanceOfTrue;
    const float attempts = static_cast<float>(private_attemptCount);
    if(probability > 0.5f){probability = 1.0f - probability;}
    private_precompConstantL = 0.5f + SGEXTN::Math::FloatMath<float>::floor(2.195f * SGEXTN::Math::FloatMath<float>::squareRoot(attempts * probability * (1.0f - probability)) - 4.6f * (1.0f - probability));
    private_precompConstantM = SGEXTN::Math::FloatMath<float>::floor(attempts * probability + probability);
    private_precompConstantC = 0.134f + 20.5f / (15.3f + private_precompConstantM);
    const float exponentialInternalLeft = (attempts * probability + probability - (private_precompConstantM - private_precompConstantL)) / (attempts * probability + probability - probability * (private_precompConstantM - private_precompConstantL));
    private_exponentialFactorLeft = exponentialInternalLeft * (1.0f + 0.5f * exponentialInternalLeft);
    const float exponentialInternalRight = (private_precompConstantM + private_precompConstantL + 1.0f - attempts * probability - probability) / ((private_precompConstantM + private_precompConstantL + 1.0f) * (1.0f - probability));
    private_exponentialFactorRight = exponentialInternalRight * (1.0f + 0.5f * exponentialInternalRight);
    private_negativeReciprocalExponentialFactorLeft = -1.0f / private_exponentialFactorLeft;
    private_reciprocalExponentialFactorRight = 1.0f / private_exponentialFactorRight;
    private_boundaryFarLeft = private_precompConstantM - private_precompConstantL + 0.5f;
    private_boundaryCenterLeft = private_precompConstantM - private_precompConstantC * private_precompConstantL + 0.5f;
    private_boundaryCenterRight = private_precompConstantM + private_precompConstantC * private_precompConstantL + 0.5f;
    private_boundaryFarRight = private_precompConstantM + private_precompConstantL + 0.5f;
    const float w1 = private_precompConstantC / private_exponentialFactorLeft;
    const float w2 = 0.5f * private_precompConstantL * (1.0f - private_precompConstantC * private_precompConstantC);
    const float w3 = 2.0f * private_precompConstantC * private_precompConstantL;
    const float w4 = 0.5f * private_precompConstantL * (1.0f - private_precompConstantC * private_precompConstantC);
    const float w5 = private_precompConstantC / private_exponentialFactorRight;
    const float weightSum = w1 + w2 + w3 + w4 + w5;
    private_weightLeftTail = w1 / weightSum;
    private_weightBothTails = (w1 + w5) / weightSum;
    private_weightAllExceptCenter = 1.0f - w3 / weightSum;
    private_comparisonMultiplier = SGEXTN::Math::FloatMath<float>::naturalLog(probability) - SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - probability);
    private_comparisonConstant = SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(private_precompConstantM) + SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(attempts - private_precompConstantM) - private_precompConstantM * private_comparisonMultiplier;
    private_geometricDistribution.setChanceOfTrue(probability);
}

void SGEXTN::SeerattraNum::BinomialDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

int SGEXTN::SeerattraNum::BinomialDistribution::randomValue(){
    if(private_chanceOfTrue == 0.0f){return 0;}
    if(private_chanceOfTrue == 1.0f){return private_attemptCount;}
    if(private_attemptCount == 0){return 0;}
    bool useNegative = false;
    float probability = private_chanceOfTrue;
    int result = 0;
    if(probability > 0.5f){
        probability = 1.0f - probability;
        useNegative = true;
    }
    if(static_cast<float>(private_attemptCount) * probability < 30.0f){
        int count = 0;
        int sum = 0;
        while(sum <= private_attemptCount){
            sum += (private_geometricDistribution.randomValue() + 1);
            count++;
        }
        result = count - 1;
    }
    else{
        while(true){
            float rng = (*private_rng).randomFloat32();
            float xCoord = 0.0f;
            float yCoord = 0.0f;
            if(rng < private_weightLeftTail){
                private_standardExponentialDistribution.private_samplePointStandard(xCoord, yCoord);
                xCoord = private_negativeReciprocalExponentialFactorLeft * xCoord + private_boundaryFarLeft;
                yCoord = private_precompConstantC * yCoord;
            }
            else if(rng < private_weightBothTails){
                private_standardExponentialDistribution.private_samplePointStandard(xCoord, yCoord);
                xCoord = private_reciprocalExponentialFactorRight * xCoord + private_boundaryFarRight;
                yCoord = private_precompConstantC * yCoord;
            }
            else if(rng < private_weightAllExceptCenter){
                rng = (rng - private_weightBothTails) / (private_weightAllExceptCenter - private_weightBothTails);
                xCoord = private_boundaryFarLeft + rng * (private_boundaryCenterLeft - private_boundaryFarLeft);
                yCoord = (*private_rng).randomFloat32() * (1.0f + private_precompConstantC);
                if(yCoord > private_precompConstantC + rng * (1.0f - private_precompConstantC)){
                    xCoord = private_boundaryCenterRight + xCoord - private_boundaryFarLeft;
                    yCoord = 1.0f + private_precompConstantC - yCoord;
                }
            }
            else{
                rng = (rng - private_weightAllExceptCenter) / (1.0f - private_weightAllExceptCenter);
                xCoord = private_boundaryCenterLeft + rng * (private_boundaryCenterRight - private_boundaryCenterLeft);
                yCoord = (*private_rng).randomFloat32();
            }
            const float flooredX = SGEXTN::Math::FloatMath<float>::floor(xCoord);
            if(static_cast<int>(flooredX) < 0 || static_cast<int>(flooredX) > private_attemptCount){continue;}
            if(private_precompConstantL * yCoord <= private_precompConstantL - SGEXTN::Math::FloatMath<float>::absoluteValue(private_precompConstantM - xCoord + 0.5f)){
                result = static_cast<int>(flooredX);
                break;
            }
            if(SGEXTN::Math::FloatMath<float>::naturalLog(yCoord) + SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(flooredX) + SGEXTN::Math::FloatMath<float>::lnExtendedFactorial(static_cast<float>(private_attemptCount) - flooredX) <= flooredX * private_comparisonMultiplier + private_comparisonConstant){
                result = static_cast<int>(flooredX);
                break;
            }
        }
    }
    if(useNegative == false){return result;}
    return (private_attemptCount - result);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::BinomialDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::BinomialDistribution::getChanceOfTrue() const {
    return private_chanceOfTrue;
}

int SGEXTN::SeerattraNum::BinomialDistribution::getAttemptCount() const {
    return private_attemptCount;
}

void SGEXTN::SeerattraNum::BinomialDistribution::setChanceOfTrue(float chanceOfTrue){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setChanceOfTrue crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    private_chanceOfTrue = chanceOfTrue;
    private_redoPrecompute();
}

void SGEXTN::SeerattraNum::BinomialDistribution::setAttemptCount(int attemptCount){
    if(attemptCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution::setAttemptCount crashed because the requested number of attempts is negative");}
    private_attemptCount = attemptCount;
    private_redoPrecompute();
}
