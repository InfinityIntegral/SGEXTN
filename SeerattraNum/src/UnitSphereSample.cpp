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

#include <SGEXTN/SeerattraNum/UnitSphereSample.h>
#include <SGEXTN/SeerattraNum/NormalDistribution.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>

SGEXTN::SeerattraNum::UnitSphereSample::UnitSphereSample(bool useGlobal) : private_ownsRng(useGlobal == false), private_rng(SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal)), private_normalDistribution(true, 0.0f, 1.0f){
    private_normalDistribution.private_rng = private_rng;
}

SGEXTN::SeerattraNum::UnitSphereSample::~UnitSphereSample(){
    if(private_ownsRng == true){delete private_rng;}
}

void SGEXTN::SeerattraNum::UnitSphereSample::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    if(private_ownsRng == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UnitSphereSample::seed crashed because cannot seed global rng");}
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    (*private_rng).seed(seedArray);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::UnitSphereSample::randomPoint(int dimensions){
    if(dimensions <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UnitSphereSample::randomPoint crashed because the requested number of dimensions is nonpositive");}
    SGEXTN::Containers::Array<float> outputArray = private_normalDistribution.randomValueArray(dimensions);
    float sumOfSquares = 0.0f;
    for(int i=0; i<dimensions; i++){
        sumOfSquares += (outputArray.at(i) * outputArray.at(i));
    }
    sumOfSquares = SGEXTN::Math::FloatMath<float>::squareRoot(sumOfSquares);
    if(sumOfSquares < SGEXTN::Math::FloatLimits<float>::minimumPositive()){
        outputArray.at(0) = 1.0f;
        for(int i=1; i<dimensions; i++){
            outputArray.at(i) = 0.0f;
        }
    }
    else{
        for(int i=0; i<dimensions; i++){
            outputArray.at(i) /= sumOfSquares;
        }
    }
    return outputArray;
}
