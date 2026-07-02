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

SGEXTN::SeerattraNum::RandomPermutation::RandomPermutation(bool useGlobal) : private_ownsRng(useGlobal == false), private_rng(SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal)), private_uniformDistribution(new SGEXTN::SeerattraNum::UniformDistributionInteger(true, 0, 0)){
    (*private_uniformDistribution).private_rng = private_rng;
}

void SGEXTN::SeerattraNum::RandomPermutation::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

SGEXTN::Containers::Array<int> SGEXTN::SeerattraNum::RandomPermutation::randomPermutation(int n){
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation::randomPermutation crashed because the number of numbers in the requested permutation is negative");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    SGEXTN::Containers::Array<int> outputArray(n);
    for(int i=0; i<n; i++){
        outputArray.at(i) = i;
    }
    for(int i=n-1; i>0; i--){
        (*private_uniformDistribution).setRange(0, i);
        const int index = (*private_uniformDistribution).randomValue();
        const int tempVar = outputArray.at(index);
        outputArray.at(index) = outputArray.at(i);
        outputArray.at(i) = tempVar;
    }
    return outputArray;
}
