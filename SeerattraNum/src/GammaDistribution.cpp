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

SGEXTN::SeerattraNum::GammaDistribution::GammaDistribution() : SGEXTN::SeerattraNum::GammaDistribution(true, 1.0f, 1.0f){}

SGEXTN::SeerattraNum::GammaDistribution::GammaDistribution(bool useGlobal, float variableCount, float variableMean) : private_variableCount(variableCount), private_variableMean(variableMean), private_rngLocator(useGlobal), private_standardNormalDistribution(true, 0.0f, 1.0f), private_precompConstantC(0.0f), private_precompConstantD(0.0f), private_reciprocalVariableCount(0.0f){
    if(variableCount <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution constructor crashed because requested number of exponentially distributed variables to sum is nonpositive");}
    if(variableMean <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution constructor crashed because requested mean of each exponentially distributed variable is nonpositive");}
    private_redoPrecompute();
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::GammaDistribution::serialise(const SGEXTN::SeerattraNum::GammaDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::serialiseTogether(x.private_rngLocator, x.private_variableCount, x.private_variableMean);
}

SGEXTN::SeerattraNum::GammaDistribution SGEXTN::SeerattraNum::GammaDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 45){
        success = false;
        return SGEXTN::SeerattraNum::GammaDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::GammaDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float variableCount = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || variableCount <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::GammaDistribution();
    }
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float variableMean = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || variableMean < 0){
        success = false;
        return SGEXTN::SeerattraNum::GammaDistribution();
    }
    SGEXTN::SeerattraNum::GammaDistribution output(true, variableCount, variableMean);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::GammaDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::GammaDistribution& x){
    return 45;
}

void SGEXTN::SeerattraNum::GammaDistribution::private_redoPrecompute(){
    float correctedVariableCount = private_variableCount;
    if(correctedVariableCount < 1.0f){correctedVariableCount = private_variableCount + 1.0f;}
    private_reciprocalVariableCount = 1.0f / private_variableCount;
    private_precompConstantD = correctedVariableCount - 1.0f / 3.0f;
    private_precompConstantC = 1.0f / 3.0f / SGEXTN::Math::FloatMath<float>::squareRoot(private_precompConstantD);
}

void SGEXTN::SeerattraNum::GammaDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::GammaDistribution::private_randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const {
    float effectiveVariableCount = private_variableCount;
    bool shouldAdjust = false;
    if(effectiveVariableCount < 1){
        effectiveVariableCount = private_variableCount + 1.0f;
        shouldAdjust = true;
    }
    float result = 0.0f;
    while(true){
        const float normalVar = private_standardNormalDistribution.private_randomValue(externalLocator);
        const float uniformVar = (*externalLocator).randomFloat32();
        float v = 1.0f + private_precompConstantC * normalVar;
        v = v * v * v;
        if(v <= 0.0f){continue;}
        float normalVar4th = normalVar * normalVar;
        normalVar4th = normalVar4th * normalVar4th;
        if(uniformVar < 1.0f - 0.0331f * normalVar4th){
            result = private_precompConstantD * v;
            break;
        }
        if(SGEXTN::Math::FloatMath<float>::naturalLog(uniformVar) < 0.5f * normalVar * normalVar + private_precompConstantD * (1.0f - v + SGEXTN::Math::FloatMath<float>::naturalLog(v))){
            result = private_precompConstantD * v;
            break;
        }
    }
    if(shouldAdjust == true){result *= SGEXTN::Math::FloatMath<float>::powerOf((*externalLocator).randomFloat32(), private_reciprocalVariableCount);}
    return (result * private_variableMean);
}

float SGEXTN::SeerattraNum::GammaDistribution::randomValue(){
    return private_randomValue(private_rngLocator);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::GammaDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::GammaDistribution::getVariableCount() const {
    return private_variableCount;
}

float SGEXTN::SeerattraNum::GammaDistribution::getVariableMean() const {
    return private_variableMean;
}

void SGEXTN::SeerattraNum::GammaDistribution::setVariableCount(float variableCount){
    if(variableCount <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::setVariableCount crashed because requested number of exponentially distributed variables to sum is nonpositive");}
    private_variableCount = variableCount;
    private_redoPrecompute();
}

void SGEXTN::SeerattraNum::GammaDistribution::setVariableMean(float variableMean){
    if(variableMean <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution::setVariableMean crashed because requested mean of each exponentially distributed variable is nonpositive");}
    private_variableMean = variableMean;
    private_redoPrecompute();
}
