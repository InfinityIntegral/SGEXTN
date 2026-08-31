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
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

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

SGEXTN::SeerattraNum::SobolSequence::SobolSequence() : SGEXTN::SeerattraNum::SobolSequence(1){}

SGEXTN::SeerattraNum::SobolSequence::SobolSequence(int dimension) : lastPosition_(-1), dimensions_(dimension){
    if(dimension <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence constructor crashed because the number of dimensions is nonpositive");}
    if(dimension > 21200){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence constructor crashed because the number of dimensions exceeds 21200 which is where the lookup tables for direction numbers end");}
    hashedSeed_ = SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32Array(dimension);
    directionNumberCache_ = SGEXTN::Containers::Array<SGEXTN::Containers::Array<unsigned int>>(dimension, SGEXTN::Containers::Array<unsigned int>(32, 0u));
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
            directionNumberCache_.at(i).at(j) = directionNumber;
        }
    }
}

bool SGEXTN::SeerattraNum::SobolSequence::sendOut(const SGEXTN::SeerattraNum::SobolSequence& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<int, int, SGEXTN::Containers::Array<unsigned int>>::sendOut(x.dimensions_, x.lastPosition_, x.hashedSeed_, data);
}

bool SGEXTN::SeerattraNum::SobolSequence::sendIn(SGEXTN::SeerattraNum::SobolSequence& x, SGEXTN::Containers::Span<unsigned char> data){
    int dimensions = 0;
    int lastPosition = -1;
    SGEXTN::Containers::Array<unsigned int> hashedSeed;
    const bool isValid = SGEXTN::Containers::Serialise<int, int, SGEXTN::Containers::Array<unsigned int>>::sendIn(dimensions, lastPosition, hashedSeed, data);
    if(isValid == false || dimensions <= 0 || dimensions > 21200 || lastPosition == 0 || lastPosition < -1 || hashedSeed.length() != dimensions){return false;}
    x = SGEXTN::SeerattraNum::SobolSequence(dimensions);
    x.hashedSeed_ = hashedSeed;
    if(lastPosition != -1){(void)(x.requestTerm(lastPosition));}
    return true;
}

int SGEXTN::SeerattraNum::SobolSequence::sizeOut(const SGEXTN::SeerattraNum::SobolSequence& x){
    return SGEXTN::Containers::Serialise<int, int, SGEXTN::Containers::Array<unsigned int>>::sizeOut(x.dimensions_, x.lastPosition_, x.hashedSeed_);
}

int SGEXTN::SeerattraNum::SobolSequence::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<int, int, SGEXTN::Containers::Array<unsigned int>>::sizeIn(data);
}

void SGEXTN::SeerattraNum::SobolSequence::seed(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    lastPosition_ = -1;
    lastPositionResult_ = SGEXTN::Containers::Array<unsigned int>();
    SGEXTN::SeerattraNum::DirectRandom rng;
    rng.seed(seedArray);
    hashedSeed_ = rng.randomUnsignedInt32Array(dimensions_);
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::SobolSequence::nextTerm(){
    if(lastPosition_ == -1){return requestTerm(1);}
    const int changedBit = getTrailingZeroCount(static_cast<unsigned int>(lastPosition_));
    lastPosition_++;
    for(int i=0; i<dimensions_; i++){
        lastPositionResult_.at(i) = lastPositionResult_.at(i) ^ directionNumberCache_.at(i).at(changedBit);
    }
    SGEXTN::Containers::Array<unsigned int> integerResult(lastPositionResult_);
    for(int i=0; i<dimensions_; i++){
        integerResult.at(i) = integerResult.at(i) ^ hashedSeed_.at(i);
    }
    SGEXTN::Containers::Array<float> floatingPointResult(dimensions_, 0.0f);
    const float scaleFactor = 1.0f / static_cast<float>(static_cast<unsigned int>(1) << 24);
    for(int i=0; i<dimensions_; i++){
        floatingPointResult.at(i) = static_cast<float>(integerResult.at(i) >> 8) * scaleFactor;
    }
    return floatingPointResult;
}

SGEXTN::Containers::Array<float> SGEXTN::SeerattraNum::SobolSequence::requestTerm(int startingPoint){
    if(startingPoint <= 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence::requestTerm crashed because starting point is nonpositive, note that zero is not supported because its number of trailing zeroes is not well defined");}
    lastPosition_ = startingPoint;
    unsigned int grayCode = startingPoint;
    grayCode = grayCode ^ (grayCode >> 1);
    SGEXTN::Containers::Array<unsigned int> integerResult(dimensions_, 0u);
    for(int i=0; i<32; i++){
        if((grayCode & (1 << i)) != 0){
            for(int j=0; j<dimensions_; j++){
                integerResult.at(j) = integerResult.at(j) ^ directionNumberCache_.at(j).at(i);
            }
        }
    }
    lastPositionResult_ = integerResult;
    for(int i=0; i<dimensions_; i++){
        integerResult.at(i) = integerResult.at(i) ^ hashedSeed_.at(i);
    }
    SGEXTN::Containers::Array<float> floatingPointResult(dimensions_, 0.0f);
    const float scaleFactor = 1.0f / static_cast<float>(static_cast<unsigned int>(1) << 24);
    for(int i=0; i<dimensions_; i++){
        floatingPointResult.at(i) = static_cast<float>(integerResult.at(i) >> 8) * scaleFactor;
    }
    return floatingPointResult;
}
