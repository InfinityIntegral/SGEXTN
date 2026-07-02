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

SGEXTN::SeerattraNum::ExponentialDistribution::ExponentialDistribution(bool useGlobal, float meanEventsPerTime) : private_meanEventsPerTime(meanEventsPerTime), private_rng(nullptr), private_ownsRng(useGlobal == false){
    if(meanEventsPerTime <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution constructor crashed because requested number of events occurring in each unit time is nonpositive");}
    private_rng = SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal);
}

SGEXTN::SeerattraNum::ExponentialDistribution::~ExponentialDistribution(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::ExponentialDistribution::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

float SGEXTN::SeerattraNum::ExponentialDistribution::randomValue(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    const float rng = (*private_rng).randomFloat32();
    return (-1.0f * SGEXTN::Math::FloatMath<float>::naturalLog(1.0f - rng) / private_meanEventsPerTime);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::ExponentialDistribution::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::ExponentialDistribution::getMeanEventsPerTime() const {
    return private_meanEventsPerTime;
}

void SGEXTN::SeerattraNum::ExponentialDistribution::setMeanEventsPerTime(float meanEventsPerTime){
    if(meanEventsPerTime <= 0.0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution::setMeanEventsPerTime crashed because requested number of events occurring in each unit time is nonpositive");}
    private_meanEventsPerTime = meanEventsPerTime;
}
