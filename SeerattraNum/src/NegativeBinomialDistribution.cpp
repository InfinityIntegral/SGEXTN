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

#include <SGEXTN/SeerattraNum/NegativeBinomialDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/SeerattraNum/GammaDistribution.h>
#include <SGEXTN/SeerattraNum/PoissonDistribution.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::NegativeBinomialDistribution::NegativeBinomialDistribution() : SGEXTN::SeerattraNum::NegativeBinomialDistribution(true, 0.5f, 1){}

SGEXTN::SeerattraNum::NegativeBinomialDistribution::NegativeBinomialDistribution(bool useGlobal, float chanceOfTrue, int successCount) : chanceOfTrue_(chanceOfTrue), successCount_(successCount), rngLocator_(useGlobal), gammaDistribution_(true, 1.0f, 1.0f), poissonDistribution_(true, 1.0f){
    if(chanceOfTrue < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested probability is higher than 1");}
    if(successCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested number of successful attempts is negative");}
    gammaDistribution_.setVariableCount(static_cast<float>(successCount));
    gammaDistribution_.setVariableMean((1.0f - chanceOfTrue) / chanceOfTrue);
}

bool SGEXTN::SeerattraNum::NegativeBinomialDistribution::sendOut(const SGEXTN::SeerattraNum::NegativeBinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, int>::sendOut(x.rngLocator_, x.chanceOfTrue_, x.successCount_, data);
}

bool SGEXTN::SeerattraNum::NegativeBinomialDistribution::sendIn(SGEXTN::SeerattraNum::NegativeBinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float probability = 0.0f;
    int successes = 0;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, int>::sendIn(rngLocator, probability, successes, data);
    if(isValid == false || probability < 0.0f || probability > 1.0f || successes < 0){return false;}
    x = SGEXTN::SeerattraNum::NegativeBinomialDistribution(true, probability, successes);
    x.rngLocator_ = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::NegativeBinomialDistribution::size(){
    return 45;
}

void SGEXTN::SeerattraNum::NegativeBinomialDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(rngLocator_.isUsingGlobal() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::seed crashed because cannot seed global rng");}
    (*rngLocator_).seed(seedArray);
}

int SGEXTN::SeerattraNum::NegativeBinomialDistribution::randomValue(){
    poissonDistribution_.setMean(gammaDistribution_.randomValue(rngLocator_));
    return poissonDistribution_.randomValue(rngLocator_);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::NegativeBinomialDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count, 0);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::NegativeBinomialDistribution::getChanceOfTrue() const {
    return chanceOfTrue_;
}

int SGEXTN::SeerattraNum::NegativeBinomialDistribution::getSuccessCount() const {
    return successCount_;
}

void SGEXTN::SeerattraNum::NegativeBinomialDistribution::setChanceOfTrue(float chanceOfTrue){
    if(chanceOfTrue < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::setChanceOfTrue crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    chanceOfTrue_ = chanceOfTrue;
    gammaDistribution_.setVariableMean((1.0f - chanceOfTrue) / chanceOfTrue);
}

void SGEXTN::SeerattraNum::NegativeBinomialDistribution::setSuccessCount(int successCount){
    if(successCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::setSuccessCount crashed because the requested number of successful attempts is negative");}
    successCount_ = successCount;
    gammaDistribution_.setVariableCount(static_cast<float>(successCount));
}
