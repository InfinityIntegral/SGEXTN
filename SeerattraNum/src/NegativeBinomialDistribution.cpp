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

SGEXTN::SeerattraNum::NegativeBinomialDistribution::NegativeBinomialDistribution(bool useGlobal, float chanceOfTrue, int successCount) : private_chanceOfTrue(chanceOfTrue), private_successCount(successCount), private_rng(nullptr), private_ownsRng(useGlobal == false), private_gammaDistribution(true, 1.0f, 1.0f), private_poissonDistribution(true, 1.0f){
    if(chanceOfTrue < 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested probability is negative");}
    if(chanceOfTrue > 1.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested probability is higher than 1");}
    if(successCount < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution constructor crashed because the requested number of successful attempts is negative");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
    private_gammaDistribution.private_rng = private_rng;
    private_gammaDistribution.private_standardNormalDistribution.private_rng = private_rng;
    private_poissonDistribution.private_rng = private_rng;
    private_gammaDistribution.setVariableCount(static_cast<float>(successCount));
    private_gammaDistribution.setVariableMean((1.0f - chanceOfTrue) / chanceOfTrue);
}

SGEXTN::SeerattraNum::NegativeBinomialDistribution::~NegativeBinomialDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::NegativeBinomialDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

int SGEXTN::SeerattraNum::NegativeBinomialDistribution::randomValue(){
    private_poissonDistribution.setMean(private_gammaDistribution.randomValue());
    return private_poissonDistribution.randomValue();
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
