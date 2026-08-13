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

#include <SGEXTN/SeerattraNum/LogNormalDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Containers/Serialise.h>

SGEXTN::SeerattraNum::LogNormalDistribution::LogNormalDistribution() : private_meanOfLn(0.0f), private_standardDeviationOfLn(1.0f), private_rngLocator(true), private_normalDistribution(true, 0.0f, 1.0f){}

SGEXTN::SeerattraNum::LogNormalDistribution::LogNormalDistribution(bool useGlobal, float meanOfLn, float standardDeviationOfLn) : private_meanOfLn(meanOfLn), private_standardDeviationOfLn(standardDeviationOfLn), private_rngLocator(useGlobal), private_normalDistribution(true, 0.0f, 1.0f){
    if(standardDeviationOfLn <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution constructor crashed because requested standard deviation is nonpositive");}
    private_normalDistribution.setMean(meanOfLn);
    private_normalDistribution.setStandardDeviation(standardDeviationOfLn);
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::LogNormalDistribution::serialise(const SGEXTN::SeerattraNum::LogNormalDistribution& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, float>::serialiseTogether(x.private_rngLocator, x.private_meanOfLn, x.private_standardDeviationOfLn);
}

SGEXTN::SeerattraNum::LogNormalDistribution SGEXTN::SeerattraNum::LogNormalDistribution::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 45){
        success = false;
        return SGEXTN::SeerattraNum::LogNormalDistribution();
    }
    SGEXTN::Containers::Array<unsigned char> tempArray(37);
    int offset = 0;
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::LogNormalDistribution();}
    tempArray = SGEXTN::Containers::Array<unsigned char>(4);
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float meanLn = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false){return SGEXTN::SeerattraNum::LogNormalDistribution();}
    SGEXTN::Containers::MemoryCopySerialise::copyOutSection(data, offset, tempArray);
    const float standardDeviationLn = SGEXTN::Containers::Serialise<float>::unserialise(tempArray, &success);
    if(success == false || standardDeviationLn <= 0.0f){
        success = false;
        return SGEXTN::SeerattraNum::LogNormalDistribution();
    }
    SGEXTN::SeerattraNum::LogNormalDistribution output(true, meanLn, standardDeviationLn);
    output.private_rngLocator = rngLocator;
    return output;
}

int SGEXTN::SeerattraNum::LogNormalDistribution::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::LogNormalDistribution& x){
    return 45;
}

void SGEXTN::SeerattraNum::LogNormalDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::LogNormalDistribution::randomValue(){
    return SGEXTN::Math::FloatMath<float>::powerOfE(private_normalDistribution.private_randomValue(private_rngLocator));
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::LogNormalDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::LogNormalDistribution::getMeanOfLn() const {
    return private_meanOfLn;
}

float SGEXTN::SeerattraNum::LogNormalDistribution::getStandardDeviationOfLn() const {
    return private_standardDeviationOfLn;
}

void SGEXTN::SeerattraNum::LogNormalDistribution::setMeanOfLn(float meanOfLn){
    private_meanOfLn = meanOfLn;
    private_normalDistribution.setMean(meanOfLn);
}

void SGEXTN::SeerattraNum::LogNormalDistribution::setStandardDeviationOfLn(float standardDeviationOfLn){
    if(standardDeviationOfLn <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution::setStandardDeviationOfLn crashed because requested standard deviation is nonpositive");}
    private_standardDeviationOfLn = standardDeviationOfLn;
    private_normalDistribution.setStandardDeviation(standardDeviationOfLn);
}
