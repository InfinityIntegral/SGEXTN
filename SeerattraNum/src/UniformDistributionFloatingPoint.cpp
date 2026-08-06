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

#include <SGEXTN/SeerattraNum/UniformDistributionFloatingPoint.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>

SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::UniformDistributionFloatingPoint(bool useGlobal, float minimum, float maximum) : private_minimum(minimum), private_maximum(maximum), private_rngLocator(useGlobal){
    if(minimum >= maximum){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint constructor crashed because minimum is higher than or equal to maximum");}
}

void SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

float SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::randomValue(){
    return (private_minimum + (private_maximum - private_minimum) * (*private_rngLocator).randomFloat32());
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::randomValueArray(int count){
    if(count < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::randomValueArray crashed because a negative number of outputs is requested");}
    SGEXTN::Containers::Array<float> outputArray(count);
    for(int i=0; i<count; i++){
        outputArray.at(i) = randomValue();
    }
    return outputArray;
}

float SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::getMinimum() const {
    return private_minimum;
}

float SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::getMaximum() const {
    return private_maximum;
}

void SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::setRange(float minimum, float maximum){
    if(minimum >= maximum){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint::setRange crashed because minimum is higher than or equal to maximum");}
    private_minimum = minimum;
    private_maximum = maximum;
}
