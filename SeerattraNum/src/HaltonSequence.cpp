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

SGEXTN::SeerattraNum::HaltonSequence::HaltonSequence(int dimensions) : private_dimensions(dimensions), private_lastPosition(-1), private_permutations(0), private_primeNumbers(0){
    if(dimensions <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence constructor crashed as the number of dimensions is nonpositive");}
    private_permutations = SGEXTN::Containers::Array<SGEXTN::Containers::Array<int>>(dimensions, SGEXTN::Containers::Array<int>(0));
    private_primeNumbers = SGEXTN::Containers::Array<int>(dimensions);
    int primesFound = 1;
    private_primeNumbers.at(0) = 2;
    int nextPossiblePrime = 3;
    while(primesFound < dimensions){
        bool isPrime = true;
        for(int i=0; i<primesFound; i++){
            if(nextPossiblePrime % private_primeNumbers.at(i) == 0){isPrime = false;}
        }
        if(isPrime == true){
            primesFound++;
            private_primeNumbers.at(primesFound - 1) = nextPossiblePrime;
        }
        nextPossiblePrime++;
    }
    SGEXTN::SeerattraNum::RandomPermutation permutationGenerator(true);
    for(int i=0; i<dimensions; i++){
        private_permutations.at(i) = permutationGenerator.randomPermutation(private_primeNumbers.at(i));
    }
    for(int i=0; i<dimensions; i++){
        for(int j=0; j<private_primeNumbers.at(i); j++){
            if(private_permutations.at(i).at(j) == 0){
                private_permutations.at(i).at(j) = private_permutations.at(i).at(0);
                private_permutations.at(i).at(0) = 0;
            }
        }
    }
}

void SGEXTN::SeerattraNum::HaltonSequence::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    SGEXTN::SeerattraNum::RandomPermutation permutationGenerator(false);
    permutationGenerator.seed(seedArray);
    for(int i=0; i<private_dimensions; i++){
        private_permutations.at(i) = permutationGenerator.randomPermutation(private_primeNumbers.at(i));
    }
    for(int i=0; i<private_dimensions; i++){
        for(int j=0; j<private_primeNumbers.at(i); j++){
            if(private_permutations.at(i).at(j) == 0){
                private_permutations.at(i).at(j) = private_permutations.at(i).at(0);
                private_permutations.at(i).at(0) = 0;
            }
        }
    }
    private_lastPosition = -1;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::HaltonSequence::nextTerm(){
    if(private_lastPosition == -1){return requestTerm(1);}
    private_lastPosition++;
    return requestTerm(private_lastPosition);
}

SGEXTN::Containers::Array<float>SGEXTN::SeerattraNum::HaltonSequence::requestTerm(int startingPoint){
    if(startingPoint <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence::requestTerm crashed because starting point is nonpositive, note that zero is not supported for consistency with Sobol Sequence");}
    private_lastPosition = startingPoint;
    SGEXTN::Containers::Array<double> doubleArray(private_dimensions, 0.0);
    for(int i=0; i<private_dimensions; i++){
        SGEXTN::Containers::Vector<int> primeBaseDigitsReversed;
        int current = startingPoint;
        while(current != 0){
            primeBaseDigitsReversed.pushBack(current % private_primeNumbers.at(i));
            current /= private_primeNumbers.at(i);
        }
        for(int j=0; j<primeBaseDigitsReversed.length(); j++){
            primeBaseDigitsReversed.at(j) = private_permutations.at(i).at(primeBaseDigitsReversed.at(j));
        }
        for(int j=primeBaseDigitsReversed.length()-1; j>=0; j--){
            doubleArray.at(i) += static_cast<double>(primeBaseDigitsReversed.at(j));
            doubleArray.at(i) /= static_cast<double>(private_primeNumbers.at(i));
        }
    }
    SGEXTN::Containers::Array<float> outputArray(private_dimensions);
    for(int i=0; i<private_dimensions; i++){
        outputArray.at(i) = static_cast<float>(doubleArray.at(i));
    }
    return outputArray;
}
