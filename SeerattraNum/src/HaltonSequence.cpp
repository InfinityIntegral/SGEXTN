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

#include <SGEXTN/SeerattraNum/HaltonSequence.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/RandomPermutation.h>
#include <SGEXTN/Containers/Vector.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::HaltonSequence::HaltonSequence() : SGEXTN::SeerattraNum::HaltonSequence(1){}

SGEXTN::SeerattraNum::HaltonSequence::HaltonSequence(int dimensions) : dimensions_(dimensions), lastPosition_(-1){
    if(dimensions <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence constructor crashed as the number of dimensions is nonpositive");}
    permutations_ = SGEXTN::Containers::Array<SGEXTN::Containers::Array<int>>(dimensions, SGEXTN::Containers::Array<int>());
    primeNumbers_ = SGEXTN::Containers::Array<int>(dimensions, 0);
    int primesFound = 1;
    primeNumbers_.at(0) = 2;
    int nextPossiblePrime = 3;
    while(primesFound < dimensions){
        bool isPrime = true;
        for(int i=0; i<primesFound; i++){
            if(nextPossiblePrime % primeNumbers_.at(i) == 0){isPrime = false;}
        }
        if(isPrime == true){
            primesFound++;
            primeNumbers_.at(primesFound - 1) = nextPossiblePrime;
        }
        nextPossiblePrime++;
    }
    SGEXTN::SeerattraNum::RandomPermutation permutationGenerator(true);
    for(int i=0; i<dimensions; i++){
        permutations_.at(i) = permutationGenerator.randomPermutation(primeNumbers_.at(i));
    }
    for(int i=0; i<dimensions; i++){
        for(int j=0; j<primeNumbers_.at(i); j++){
            if(permutations_.at(i).at(j) == 0){
                permutations_.at(i).at(j) = permutations_.at(i).at(0);
                permutations_.at(i).at(0) = 0;
            }
        }
    }
}

bool SGEXTN::SeerattraNum::HaltonSequence::sendOut(const SGEXTN::SeerattraNum::HaltonSequence& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<int, int, SGEXTN::Containers::Array<SGEXTN::Containers::Array<int>>>::sendOut(x.dimensions_, x.lastPosition_, x.permutations_, data);
}

bool SGEXTN::SeerattraNum::HaltonSequence::sendIn(SGEXTN::SeerattraNum::HaltonSequence& x, SGEXTN::Containers::Span<unsigned char> data){
    int dimensions = 0;
    int lastPosition = -1;
    SGEXTN::Containers::Array<SGEXTN::Containers::Array<int>> permutations(0, SGEXTN::Containers::Array<int>());
    const bool isValid = SGEXTN::Containers::Serialise<int, int, SGEXTN::Containers::Array<SGEXTN::Containers::Array<int>>>::sendIn(dimensions, lastPosition, permutations, data);
    if(isValid == false || dimensions <= 0 || lastPosition == 0 || lastPosition < -1 || permutations.length() != dimensions){return false;}
    SGEXTN::Containers::Array<int> primeNumbers(dimensions, 0);
    int primesFound = 1;
    primeNumbers.at(0) = 2;
    int nextPossiblePrime = 3;
    while(primesFound < dimensions){
        bool isPrime = true;
        for(int i=0; i<primesFound; i++){
            if(nextPossiblePrime % primeNumbers.at(i) == 0){isPrime = false;}
        }
        if(isPrime == true){
            primesFound++;
            primeNumbers.at(primesFound - 1) = nextPossiblePrime;
        }
        nextPossiblePrime++;
    }
    for(int i=0; i<dimensions; i++){
        if(permutations.at(i).length() != primeNumbers.at(i) || permutations.at(i).at(0) != 0){return false;}
        SGEXTN::Containers::Array<int> occurences(primeNumbers.at(i), 0);
        for(int j=0; j<primeNumbers.at(i); j++){
            if(permutations.at(i).at(j) < 0 || permutations.at(i).at(j) >= primeNumbers.at(i)){return false;}
            occurences.at(permutations.at(i).at(j))++;
        }
        for(int j=0; j<primeNumbers.at(i); j++){
            if(occurences.at(j) != 1){return false;}
        }
    }
    x = SGEXTN::SeerattraNum::HaltonSequence(dimensions);
    x.permutations_ = permutations;
    if(lastPosition != -1){(void)(x.requestTerm(lastPosition));}
    return true;
}

int SGEXTN::SeerattraNum::HaltonSequence::sizeOut(const SGEXTN::SeerattraNum::HaltonSequence& x){
    return SGEXTN::Containers::Serialise<int, int, SGEXTN::Containers::Array<SGEXTN::Containers::Array<int>>>::sizeOut(x.dimensions_, x.lastPosition_, x.permutations_);
}

int SGEXTN::SeerattraNum::HaltonSequence::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<int, int, SGEXTN::Containers::Array<SGEXTN::Containers::Array<int>>>::sizeIn(data);
}

void SGEXTN::SeerattraNum::HaltonSequence::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    SGEXTN::SeerattraNum::RandomPermutation permutationGenerator(false);
    permutationGenerator.seed(seedArray);
    for(int i=0; i<dimensions_; i++){
        permutations_.at(i) = permutationGenerator.randomPermutation(primeNumbers_.at(i));
    }
    for(int i=0; i<dimensions_; i++){
        for(int j=0; j<primeNumbers_.at(i); j++){
            if(permutations_.at(i).at(j) == 0){
                permutations_.at(i).at(j) = permutations_.at(i).at(0);
                permutations_.at(i).at(0) = 0;
            }
        }
    }
    lastPosition_ = -1;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::HaltonSequence::nextTerm(){
    if(lastPosition_ == -1){return requestTerm(1);}
    lastPosition_++;
    return requestTerm(lastPosition_);
}

SGEXTN::Containers::Array<float>SGEXTN::SeerattraNum::HaltonSequence::requestTerm(int startingPoint){
    if(startingPoint <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence::requestTerm crashed because starting point is nonpositive, note that zero is not supported for consistency with Sobol Sequence");}
    lastPosition_ = startingPoint;
    SGEXTN::Containers::Array<double> doubleArray(dimensions_, static_cast<double>(0.0f));
    for(int i=0; i<dimensions_; i++){
        SGEXTN::Containers::Vector<int> primeBaseDigitsReversed;
        int current = startingPoint;
        while(current != 0){
            primeBaseDigitsReversed.pushBack(current % primeNumbers_.at(i));
            current /= primeNumbers_.at(i);
        }
        for(int j=0; j<primeBaseDigitsReversed.length(); j++){
            primeBaseDigitsReversed.at(j) = permutations_.at(i).at(primeBaseDigitsReversed.at(j));
        }
        for(int j=primeBaseDigitsReversed.length()-1; j>=0; j--){
            doubleArray.at(i) += static_cast<double>(primeBaseDigitsReversed.at(j));
            doubleArray.at(i) /= static_cast<double>(primeNumbers_.at(i));
        }
    }
    SGEXTN::Containers::Array<float> outputArray(dimensions_, 0.0f);
    for(int i=0; i<dimensions_; i++){
        outputArray.at(i) = static_cast<float>(doubleArray.at(i));
    }
    return outputArray;
}
