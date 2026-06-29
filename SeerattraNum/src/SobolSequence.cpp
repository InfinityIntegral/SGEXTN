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

#include <SGEXTN/SeerattraNum/SobolSequence.h>
#include <SGEXTN/SeerattraNum/private_api/SobolSequenceLookup.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/Hash.h>
#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/Math/IntegerLimits.h>
#include <SGEXTN/Containers/ForceCrash.h>

namespace {
int getTrailingZeroCount(unsigned int n){
    int count = 0;
    if((n & 0xffff) == 0){
        count += 16;
        n = n >> 16;
    }
    if((n & 0xff) == 0){
        count += 8;
        n = n >> 8;
    }
    if((n & 0xf) == 0){
        count += 4;
        n = n >> 4;
    }
    if((n & 3) == 0){
        count += 2;
        n = n >> 2;
    }
    if((n & 1) == 0){count++;}
    return count;
}
}

SGEXTN::SeerattraNum::SobolSequence::SobolSequence(int dimension) : private_lastPosition(-1), private_lastPositionResult(0), private_dimensions(dimension), private_hashedSeed(0), private_directionNumberCache(0){
    if(dimension <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence constructor crashed because the number of dimensions is nonpositive");}
    if(dimension > 21200){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence constructor crashed because the number of dimensions exceeds 21200 which is where the lookup tables for direction numbers end");}
    private_hashedSeed = SGEXTN::Containers::Array<unsigned int>(dimension);
    private_directionNumberCache = SGEXTN::Containers::Array<SGEXTN::Containers::Array<unsigned int>>(dimension, SGEXTN::Containers::Array<unsigned int>(32));
    for(int i=0; i<dimension; i++){
        for(int j=0; j<32; j++){
            unsigned int directionNumber = 0;
            const unsigned char firstByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::SobolSequenceLookup::data + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(128 * i + 4 * j)));
            const unsigned char secondByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::SobolSequenceLookup::data + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(128 * i + 4 * j + 1)));
            const unsigned char thirdByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::SobolSequenceLookup::data + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(128 * i + 4 * j + 2)));
            const unsigned char fourthByte = static_cast<unsigned char>(*(SGEXTN::SeerattraNum::SobolSequenceLookup::data + static_cast<decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr))>(128 * i + 4 * j + 3)));
            directionNumber = directionNumber | (static_cast<unsigned int>(firstByte) << 24);
            directionNumber = directionNumber | (static_cast<unsigned int>(secondByte) << 16);
            directionNumber = directionNumber | (static_cast<unsigned int>(thirdByte) << 8);
            directionNumber = directionNumber | static_cast<unsigned int>(fourthByte);
            private_directionNumberCache.at(i).at(j) = directionNumber;
        }
    }
    const unsigned int seed = SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32();
    for(int i=0; i<dimension; i++){
        private_hashedSeed.at(i) = SGEXTN::Containers::Hash<int, unsigned int>()(i, seed);
    }
}

void SGEXTN::SeerattraNum::SobolSequence::seed(int seed){
    for(int i=0; i<private_dimensions; i++){
        private_hashedSeed.at(i) = SGEXTN::Containers::Hash<int, int>()(i, seed);
    }
    private_lastPosition = -1;
    private_lastPositionResult = SGEXTN::Containers::Array<unsigned int>(0);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::SobolSequence::nextTerm(){
    if(private_lastPosition == -1){return requestTerm(1);}
    const int changedBit = getTrailingZeroCount(static_cast<unsigned int>(private_lastPosition));
    private_lastPosition++;
    for(int i=0; i<private_dimensions; i++){
        private_lastPositionResult.at(i) = private_lastPositionResult.at(i) ^ private_directionNumberCache.at(i).at(changedBit);
    }
    SGEXTN::Containers::Array<unsigned int> integerResult(private_lastPositionResult);
    for(int i=0; i<private_dimensions; i++){
        integerResult.at(i) = integerResult.at(i) ^ private_hashedSeed.at(i);
    }
    SGEXTN::Containers::Array<float> floatingPointResult(private_dimensions);
    const double maximumValue = static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) + 1.0;
    for(int i=0; i<private_dimensions; i++){
        floatingPointResult.at(i) = static_cast<float>(static_cast<double>(integerResult.at(i)) / maximumValue);
    }
    return floatingPointResult;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::SobolSequence::requestTerm(int startingPoint){
    if(startingPoint <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence::requestTerm crashed because starting point is nonpositive, note that zero is not supported because its number of trailing zeroes is not well defined");}
    private_lastPosition = startingPoint;
    unsigned int grayCode = startingPoint;
    grayCode = grayCode ^ (grayCode >> 1);
    SGEXTN::Containers::Array<unsigned int> integerResult(private_dimensions, 0u);
    for(int i=0; i<32; i++){
        if((grayCode & (1 << i)) != 0){
            for(int j=0; j<private_dimensions; j++){
                integerResult.at(j) = integerResult.at(j) ^ private_directionNumberCache.at(j).at(i);
            }
        }
    }
    private_lastPositionResult = integerResult;
    for(int i=0; i<private_dimensions; i++){
        integerResult.at(i) = integerResult.at(i) ^ private_hashedSeed.at(i);
    }
    SGEXTN::Containers::Array<float> floatingPointResult(private_dimensions);
    const double maximumValue = static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) + 1.0;
    for(int i=0; i<private_dimensions; i++){
        floatingPointResult.at(i) = static_cast<float>(static_cast<double>(integerResult.at(i)) / maximumValue);
    }
    return floatingPointResult;
}
