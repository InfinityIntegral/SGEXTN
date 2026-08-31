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

#include <SGEXTN/SeerattraNum/GammaDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/SeerattraNum/NormalDistribution.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::GammaDistribution::GammaDistribution() : SGEXTN::SeerattraNum::GammaDistribution(true, 1.0f, 1.0f){}

SGEXTN::SeerattraNum::GammaDistribution::GammaDistribution(bool useGlobal, float variableCount, float variableMean) : variableCount_(variableCount), variableMean_(variableMean), rngLocator_(useGlobal), standardNormalDistribution_(true, 0.0f, 1.0f), precompConstantC_(0.0f), precompConstantD_(0.0f), reciprocalVariableCount_(0.0f){
    if(variableCount <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution constructor crashed because requested number of exponentially distributed variables to sum is nonpositive");}
    if(variableMean <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution constructor crashed because requested mean of each exponentially distributed variable is nonpositive");}
    redoPrecompute();
}

bool SGEXTN::SeerattraNum::GammaDistribution::sendOut(const SGEXTN::SeerattraNum::GammaDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendOut(x.rngLocator_, x.variableCount_, x.variableMean_, data);
}

bool SGEXTN::SeerattraNum::GammaDistribution::sendIn(SGEXTN::SeerattraNum::GammaDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float variableCount = 0.0f;
    float variableMean = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::sendIn(rngLocator, variableCount, variableMean, data);
    if(isValid == false || variableCount <= 0.0f || variableMean <= 0.0f){return false;}
    x = SGEXTN::SeerattraNum::GammaDistribution(true, variableCount, variableMean);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::GammaDistribution::size(){
    return 45;
}

void SGEXTN::SeerattraNum::GammaDistribution::redoPrecompute(){
    float correctedVariableCount = variableCount_;
    if(correctedVariableCount < 1.0f){correctedVariableCount = variableCount_ + 1.0f;}
    reciprocalVariableCount_ = 1.0f / variableCount_;
    precompConstantD_ = correctedVariableCount - 1.0f / 3.0f;
    precompConstantC_ = 1.0f / 3.0f / SGEXTN::Math::FloatMath<float>::squareRoot(precompConstantD_);
}

void SGEXTN::SeerattraNum::GammaDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

float SGEXTN::SeerattraNum::GammaDistribution::randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    float effectiveVariableCount = variableCount_;
    bool shouldAdjust = false;
    if(effectiveVariableCount < 1){
        effectiveVariableCount = variableCount_ + 1.0f;
        shouldAdjust = true;
    }
    float result = 0.0f;
    while(true){
        const float normalVar = standardNormalDistribution_.randomValue(externalLocator);
        const float uniformVar = (*externalLocator).randomFloat32();
        float v = 1.0f + precompConstantC_ * normalVar;
        v = v * v * v;
        if(v <= 0.0f){continue;}
        float normalVar4th = normalVar * normalVar;
        normalVar4th = normalVar4th * normalVar4th;
        if(uniformVar < 1.0f - 0.0331f * normalVar4th){
            result = precompConstantD_ * v;
            break;
        }
        if(SGEXTN::Math::FloatMath<float>::naturalLog(uniformVar) < 0.5f * normalVar * normalVar + precompConstantD_ * (1.0f - v + SGEXTN::Math::FloatMath<float>::naturalLog(v))){
            result = precompConstantD_ * v;
            break;
        }
    }
    if(shouldAdjust == true){result *= SGEXTN::Math::FloatMath<float>::powerOf((*externalLocator).randomFloat32(), reciprocalVariableCount_);}
    return (result * variableMean_);
}

float SGEXTN::SeerattraNum::GammaDistribution::randomValue(){
    return randomValue(rngLocator_);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::GammaDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count, 0.0f);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::GammaDistribution::getVariableCount() const {
    return variableCount_;
}

float SGEXTN::SeerattraNum::GammaDistribution::getVariableMean() const {
    return variableMean_;
}

void SGEXTN::SeerattraNum::GammaDistribution::setVariableCount(float variableCount){
    if(variableCount <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::setVariableCount crashed because requested number of exponentially distributed variables to sum is nonpositive");}
    variableCount_ = variableCount;
    redoPrecompute();
}

void SGEXTN::SeerattraNum::GammaDistribution::setVariableMean(float variableMean){
    if(variableMean <= 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::setVariableMean crashed because requested mean of each exponentially distributed variable is nonpositive");}
    variableMean_ = variableMean;
    redoPrecompute();
}
