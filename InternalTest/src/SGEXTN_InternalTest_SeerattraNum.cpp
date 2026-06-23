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

#include <private_api/SGEXTN_InternalTest_SeerattraNumTest.h>
#include <SGEXTN_SeerattraNum_TrueRandom.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_SeerattraNum_SimpleRandom.h>
#include <SGEXTN_SeerattraNum_DirectInteger.h>
#include <SGEXTN_SeerattraNum_DirectFloatingPoint.h>
#include <SGEXTN_SeerattraNum_UniformDistributionInteger.h>
#include <SGEXTN_SeerattraNum_UniformDistributionFloatingPoint.h>

namespace {
bool isCloseEnough(float a, float b){
    if(a > b - 0.001f && a < b + 0.001f){return true;}
    return false;
}
}

void SGEXTN::InternalTest::SeerattraNumTest::testTrueRandom(){
    SGEXTN::Containers::UnorderedSet<int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> randomInts32;
    while(randomInts32.length() < 100){
        randomInts32.insert(SGEXTN::SeerattraNum::TrueRandom::randomInt32());
    }
    SGEXTN::Containers::UnorderedSet<long long, SGEXTN::Containers::EqualTo<long long>, SGEXTN::Containers::Hash<long long>> randomInts64;
    while(randomInts64.length() < 100){
        randomInts64.insert(SGEXTN::SeerattraNum::TrueRandom::randomInt64());
    }
    SGEXTN::Containers::UnorderedSet<unsigned int, SGEXTN::Containers::EqualTo<unsigned int>, SGEXTN::Containers::Hash<unsigned int>> randomUnsignedInts32;
    while(randomUnsignedInts32.length() < 100){
        randomUnsignedInts32.insert(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32());
    }
    SGEXTN::Containers::UnorderedSet<unsigned long long, SGEXTN::Containers::EqualTo<unsigned long long>, SGEXTN::Containers::Hash<unsigned long long>> randomUnsignedInts64;
    while(randomUnsignedInts64.length() < 100){
        randomUnsignedInts64.insert(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64());
    }
    SGEXTN::Containers::UnorderedSet<float, SGEXTN::Containers::EqualTo<float>, SGEXTN::Containers::Hash<float>> randomFloats32;
    while(randomFloats32.length() < 100){
        randomFloats32.insert(SGEXTN::SeerattraNum::TrueRandom::randomFloat32());
    }
    SGEXTN::Containers::UnorderedSet<double, SGEXTN::Containers::EqualTo<double>, SGEXTN::Containers::Hash<double>> randomFloats64;
    while(randomFloats64.length() < 100){
        randomFloats64.insert(SGEXTN::SeerattraNum::TrueRandom::randomFloat64());
    }
    if(SGEXTN::SeerattraNum::TrueRandom::randomInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 32 bit integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 64 bit integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 32 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 64 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomFloat32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 32 bit floating point number fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomFloat64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 64 bit floating point number fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testSimpleRandom(){
    SGEXTN::Containers::UnorderedSet<int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> randomInts32;
    while(randomInts32.length() < 100){
        randomInts32.insert(SGEXTN::SeerattraNum::SimpleRandom::randomInt32());
    }
    SGEXTN::Containers::UnorderedSet<long long, SGEXTN::Containers::EqualTo<long long>, SGEXTN::Containers::Hash<long long>> randomInts64;
    while(randomInts64.length() < 100){
        randomInts64.insert(SGEXTN::SeerattraNum::SimpleRandom::randomInt64());
    }
    SGEXTN::Containers::UnorderedSet<unsigned int, SGEXTN::Containers::EqualTo<unsigned int>, SGEXTN::Containers::Hash<unsigned int>> randomUnsignedInts32;
    while(randomUnsignedInts32.length() < 100){
        randomUnsignedInts32.insert(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32());
    }
    SGEXTN::Containers::UnorderedSet<unsigned long long, SGEXTN::Containers::EqualTo<unsigned long long>, SGEXTN::Containers::Hash<unsigned long long>> randomUnsignedInts64;
    while(randomUnsignedInts64.length() < 100){
        randomUnsignedInts64.insert(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64());
    }
    SGEXTN::Containers::UnorderedSet<float, SGEXTN::Containers::EqualTo<float>, SGEXTN::Containers::Hash<float>> randomFloats32;
    while(randomFloats32.length() < 100){
        randomFloats32.insert(SGEXTN::SeerattraNum::SimpleRandom::randomFloat32());
    }
    SGEXTN::Containers::UnorderedSet<double, SGEXTN::Containers::EqualTo<double>, SGEXTN::Containers::Hash<double>> randomFloats64;
    while(randomFloats64.length() < 100){
        randomFloats64.insert(SGEXTN::SeerattraNum::SimpleRandom::randomFloat64());
    }
    if(SGEXTN::SeerattraNum::SimpleRandom::randomInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 32 bit integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 64 bit integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 32 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 64 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomFloat32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 32 bit floating point number fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomFloat64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 64 bit floating point number fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testDirectInteger(){
    SGEXTN::SeerattraNum::DirectInteger<int> generator(false);
    generator.seed(SGEXTN::Containers::Array<unsigned int>(1u, 2u, 3u, 4u, 5u));
    if(generator.randomInteger() != 689864061){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger generate integer first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomIntegerArray(2);
    if(randomArray.at(0) != -2116458956 || randomArray.at(1) != -249517681){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger generate integer array first seed fail");}
    generator.seed(SGEXTN::Containers::Array<unsigned int>(6u, 7u, 8u, 9u, 10u));
    if(generator.randomInteger() != 986110788){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger generate integer second seed fail");}
    randomArray = generator.randomIntegerArray(2);
    if(randomArray.at(0) != 1930272640 || randomArray.at(1) != -10058938){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger generate integer array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testDirectFloatingPoint(){
    SGEXTN::SeerattraNum::DirectFloatingPoint<float> generator(false);
    generator.seed(SGEXTN::Containers::Array<unsigned int>(1u, 2u, 3u, 4u, 5u));
    if(isCloseEnough(generator.randomFloatingPoint(), 0.33353f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectFloatingPoint generate floating point first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomFloatingPointArray(2);
    if(isCloseEnough(randomArray.at(0), 0.10711f) == false || isCloseEnough(randomArray.at(1), 0.53777f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectFloatingPoint generate floating point array first seed fail");}
    generator.seed(SGEXTN::Containers::Array<unsigned int>(6u, 7u, 8u, 9u, 10u));
    if(isCloseEnough(generator.randomFloatingPoint(), 0.52355f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectFloatingPoint generate floating point second seed fail");}
    randomArray = generator.randomFloatingPointArray(2);
    if(isCloseEnough(randomArray.at(0), 0.70912f) == false || isCloseEnough(randomArray.at(1), 0.92607f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectFloatingPoint generate floating point array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionInteger(){
    SGEXTN::SeerattraNum::UniformDistributionInteger<int> generator(false, 1, 6);
    generator.seed(SGEXTN::Containers::Array<unsigned int>(1u, 2u, 3u, 4u, 5u));
    if(generator.randomValue() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger generate number first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != 1 || randomArray.at(1) != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger generate array first seed fail");}
    if(generator.getInclusiveMin() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger get minimum boundary fail");}
    if(generator.getInclusiveMax() != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger get maximum boundary fail");}
    generator.setInclusiveMin(-5);
    generator.setInclusiveMax(-1);
    generator.seed(SGEXTN::Containers::Array<unsigned int>(6u, 7u, 8u, 9u, 10u));
    if(generator.randomValue() != -3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger generate number second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != -2 || randomArray.at(1) != -1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionFloatingPoint(){
    SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<float> generator(false, 1.0f, 2.0f);
    generator.seed(SGEXTN::Containers::Array<unsigned int>(1u, 2u, 3u, 4u, 5u));
    if(isCloseEnough(generator.randomValue(), 1.3335f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint generate number first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(isCloseEnough(randomArray.at(0), 1.1071f) == false || isCloseEnough(randomArray.at(1), 1.5378f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint generate array first seed fail");}
    if(generator.getMinimum() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint get minimum boundary fail");}
    if(generator.getMaximum() != 2.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint get maximum boundary fail");}
    generator.setMinimum(-2.0f);
    generator.setMaximum(-1.0f);
    generator.seed(SGEXTN::Containers::Array<unsigned int>(6u, 7u, 8u, 9u, 10u));
    if(isCloseEnough(generator.randomValue(), -1.4765f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint generate number second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(isCloseEnough(randomArray.at(0), -1.2909f) == false || isCloseEnough(randomArray.at(1), -1.0739f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testAll(){
    SGEXTN::InternalTest::SeerattraNumTest::testTrueRandom();
    SGEXTN::InternalTest::SeerattraNumTest::testSimpleRandom();
    SGEXTN::InternalTest::SeerattraNumTest::testDirectInteger();
    SGEXTN::InternalTest::SeerattraNumTest::testDirectFloatingPoint();
    SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionInteger();
    SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionFloatingPoint();
}
