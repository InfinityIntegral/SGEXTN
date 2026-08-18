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

#include <SGEXTN/SeerattraNum/RandomPermutation.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/SeerattraNum/UniformDistributionInteger.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::RandomPermutation::RandomPermutation() : SGEXTN::SeerattraNum::RandomPermutation(true){}

SGEXTN::SeerattraNum::RandomPermutation::RandomPermutation(bool useGlobal) : private_rngLocator(useGlobal), private_uniformDistribution(true, 0, 0){}

bool SGEXTN::SeerattraNum::RandomPermutation::sendOut(const SGEXTN::SeerattraNum::RandomPermutation& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::sendOut(x.private_rngLocator, data);
}

bool SGEXTN::SeerattraNum::RandomPermutation::sendIn(SGEXTN::SeerattraNum::RandomPermutation& x, SGEXTN::Containers::Span<unsigned char> data){
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator(true);
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::sendIn(rngLocator, data);
    if(isValid == false){return false;}
    x = SGEXTN::SeerattraNum::RandomPermutation(true);
    x.private_rngLocator = rngLocator;
    return true;
}

int SGEXTN::SeerattraNum::RandomPermutation::size(){
    return 37;
}

void SGEXTN::SeerattraNum::RandomPermutation::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_rngLocator.private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation::seed crashed because cannot seed global rng");}
    (*private_rngLocator).seed(seedArray);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::RandomPermutation::randomPermutation(int n){
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation::randomPermutation crashed because the number of numbers in the requested permutation is negative");}
    SGEXTN::Containers::Array<int> outputArray(n);
    for(int i=0; i<n; i++){
        outputArray.at(i) = i;
    }
    for(int i=n-1; i>0; i--){
        private_uniformDistribution.setRange(0, i);
        const int index = private_uniformDistribution.private_randomValue(private_rngLocator);
        const int tempVar = outputArray.at(index);
        outputArray.at(index) = outputArray.at(i);
        outputArray.at(i) = tempVar;
    }
    return outputArray;
}
