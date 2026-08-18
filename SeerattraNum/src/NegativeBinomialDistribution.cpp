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
#include <SGEXTN/Containers/Serialisation.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::NegativeBinomialDistribution::NegativeBinomialDistribution() : SGEXTN::SeerattraNum::NegativeBinomialDistribution(true, 0.5f, 1){}

SGEXTN::SeerattraNum::NegativeBinomialDistribution::NegativeBinomialDistribution(bool useGlobal, float chanceOfTrue, int successCount) : private_chanceOfTrue(chanceOfTrue), private_successCount(successCount), private_rngLocator(useGlobal), private_gammaDistribution(true, 1.0f, 1.0f), private_poissonDistribution(true, 1.0f){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested probability is higher than 1");}
    if(successCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested number of successful attempts is negative");}
    private_gammaDistribution.setVariableCount(static_cast<float>(successCount));
    private_gammaDistribution.setVariableMean((1.0f - chanceOfTrue) / chanceOfTrue);
}

bool SGEXTN::SeerattraNum::NegativeBinomialDistribution::sendOut(const SGEXTN::SeerattraNum::NegativeBinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialisation<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, int>::sendOut(x.private_rngLocator, x.private_chanceOfTrue, x.private_successCount, data);
}

bool SGEXTN::SeerattraNum::NegativeBinomialDistribution::sendIn(SGEXTN::SeerattraNum::NegativeBinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    float probability = 0.0f;
    int successes = 0;
    const bool isValid = SGEXTN::Containers::Serialisation<SGEXTN::SeerattraNum::DirectRandomInstanceLocator, float, int>::sendIn(rngLocator, probability, successes, data);
    if(isValid == false || probability < 0.0f || probability > 1.0f || successes < 0){return false;}
    x = SGEXTN::SeerattraNum::NegativeBinomialDistribution(true, probability, successes);
    x.private_rngLocator = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::NegativeBinomialDistribution::size(){
    return 45;
}

void SGEXTN::SeerattraNum::NegativeBinomialDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

int SGEXTN::SeerattraNum::NegativeBinomialDistribution::randomValue(){
    private_poissonDistribution.setMean(private_gammaDistribution.private_randomValue(private_rngLocator));
    return private_poissonDistribution.private_randomValue(private_rngLocator);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::NegativeBinomialDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<int> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::NegativeBinomialDistribution::getChanceOfTrue() const {
    return private_chanceOfTrue;
}

int SGEXTN::SeerattraNum::NegativeBinomialDistribution::getSuccessCount() const {
    return private_successCount;
}

void SGEXTN::SeerattraNum::NegativeBinomialDistribution::setChanceOfTrue(float chanceOfTrue){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::setChanceOfTrue crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::setChanceOfTrue crashed because the requested probability is higher than 1");}
    private_chanceOfTrue = chanceOfTrue;
    private_gammaDistribution.setVariableMean((1.0f - chanceOfTrue) / chanceOfTrue);
}

void SGEXTN::SeerattraNum::NegativeBinomialDistribution::setSuccessCount(int successCount){
    if(successCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::setSuccessCount crashed because the requested number of successful attempts is negative");}
    private_successCount = successCount;
    private_gammaDistribution.setVariableCount(static_cast<float>(successCount));
}
