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

#include <SGEXTN/InternalTest/private_api/SeerattraNumTest.h>
#include <SGEXTN/SeerattraNum/TrueRandom.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/UnorderedSet.h>
#include <SGEXTN/Containers/EqualTo.h>
#include <SGEXTN/Containers/Hash.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SeerattraNum/SimpleRandom.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/SeerattraNum/UniformDistributionInteger.h>
#include <SGEXTN/SeerattraNum/UniformDistributionFloatingPoint.h>
#include <SGEXTN/SeerattraNum/BernoulliDistribution.h>
#include <SGEXTN/SeerattraNum/BinomialDistribution.h>
#include <SGEXTN/SeerattraNum/NegativeBinomialDistribution.h>
#include <SGEXTN/SeerattraNum/GeometricDistribution.h>
#include <SGEXTN/SeerattraNum/PoissonDistribution.h>
#include <SGEXTN/SeerattraNum/ExponentialDistribution.h>
#include <SGEXTN/SeerattraNum/GammaDistribution.h>
#include <SGEXTN/SeerattraNum/WeibullDistribution.h>
#include <SGEXTN/SeerattraNum/GumbelDistribution.h>
#include <SGEXTN/SeerattraNum/NormalDistribution.h>
#include <SGEXTN/SeerattraNum/LogNormalDistribution.h>
#include <SGEXTN/SeerattraNum/CauchyDistribution.h>
#include <SGEXTN/SeerattraNum/ChiSquaredDistribution.h>
#include <SGEXTN/SeerattraNum/FisherFDistribution.h>
#include <SGEXTN/SeerattraNum/StudentTDistribution.h>
#include <SGEXTN/SeerattraNum/WeightedIndexSelectionDistribution.h>
#include <SGEXTN/SeerattraNum/WeightedPiecewiseConstantDistribution.h>
#include <SGEXTN/SeerattraNum/WeightedPiecewiseLinearDistribution.h>
#include <SGEXTN/SeerattraNum/RandomPermutation.h>
#include <SGEXTN/SeerattraNum/UnitSphereSample.h>
#include <SGEXTN/SeerattraNum/SobolSequence.h>
#include <SGEXTN/SeerattraNum/HaltonSequence.h>
#include <SGEXTN/SeerattraNum/VoronoiNoise.h>
#include <SGEXTN/SeerattraNum/ValueNoise.h>
#include <SGEXTN/SeerattraNum/SmoothingFunction.h>
#include <SGEXTN/SeerattraNum/PerlinNoise.h>
#include <SGEXTN/Containers/LessThan.h>
#include <SGEXTN/Containers/Map.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>
#include <random>

namespace {
SGEXTN::Containers::Array<unsigned int> firstSeed(1u, 2u, 3u, 4u, 5u);
SGEXTN::Containers::Array<unsigned int> secondSeed(6u, 7u, 8u, 9u, 10u);

std::mt19937 standardLibraryRng;

void seedStandardLibraryRng(const SGEXTN::Containers::Array<unsigned int>& seed){
    std::seed_seq seedSequence(&seed.at(0), &seed.at(0) + seed.length());
    standardLibraryRng.seed(seedSequence);
}

bool isCloseEnough(float a, float b){
    return (a > b - 0.001f && a < b + 0.001f);
}

bool testIfDistributionSameContinuous(SGEXTN::Containers::Array<float>& sampleData, SGEXTN::Containers::Array<float>& testData){
    if(sampleData.length() != 100000 || testData.length() != 100000){SGEXTN_IMMEDIATE_CRASH("sample size is wrong");}
    sampleData.sort<SGEXTN::Containers::LessThan<float>>(0, sampleData.length());
    testData.sort<SGEXTN::Containers::LessThan<float>>(0, testData.length());
    int maximumDifference = 0;
    int nextInSampleData = 0;
    int nextInTestData = 0;
    while(nextInSampleData < 100000 && nextInTestData < 100000){
        if(sampleData.at(nextInSampleData) < testData.at(nextInTestData)){nextInSampleData++;}
        else{nextInTestData++;}
        if(maximumDifference < nextInSampleData - nextInTestData){maximumDifference = nextInSampleData - nextInTestData;}
        else if(maximumDifference < nextInTestData - nextInSampleData){maximumDifference = nextInTestData - nextInSampleData;}
    }
    return (maximumDifference < 608);
}

bool testIfDistributionSameDiscrete(SGEXTN::Containers::Array<int>& sampleData, SGEXTN::Containers::Array<int>& testData){
    if(sampleData.length() != 100000 || testData.length() != 100000){SGEXTN_IMMEDIATE_CRASH("sample size is wrong");}
    SGEXTN::Containers::Map<int, int, SGEXTN::Containers::LessThan<int>> sampleDataDensityMap;
    SGEXTN::Containers::Map<int, int, SGEXTN::Containers::LessThan<int>> testDataDensityMap;
    for(int i=0; i<100000; i++){
        if(sampleDataDensityMap.contains(sampleData.at(i)) == false){sampleDataDensityMap.insert(sampleData.at(i), 1);}
        else{sampleDataDensityMap.at(sampleData.at(i))++;}
    }
    for(int i=0; i<100000; i++){
        if(testDataDensityMap.contains(testData.at(i)) == false){testDataDensityMap.insert(testData.at(i), 1);}
        else{testDataDensityMap.at(testData.at(i))++;}
    }
    int minimum = sampleDataDensityMap.keyAt(0);
    if(testDataDensityMap.keyAt(0) < minimum){minimum = testDataDensityMap.keyAt(0);}
    int maximum = sampleDataDensityMap.keyAt(sampleDataDensityMap.length() - 1);
    if(testDataDensityMap.keyAt(testDataDensityMap.length() - 1) > maximum){maximum = testDataDensityMap.keyAt(testDataDensityMap.length() - 1);}
    if(maximum - minimum > 100000){SGEXTN_IMMEDIATE_CRASH("range of data too wide");}
    int maximumDifference = 0;
    int nextInSampleData = 0;
    int nextInTestData = 0;
    for(int i=minimum; i<=maximum; i++){
        if(sampleDataDensityMap.contains(i) == true){nextInSampleData += sampleDataDensityMap.at(i);}
        if(testDataDensityMap.contains(i) == true){nextInTestData += testDataDensityMap.at(i);}
        if(maximumDifference < nextInSampleData - nextInTestData){maximumDifference = nextInSampleData - nextInTestData;}
        else if(maximumDifference < nextInTestData - nextInSampleData){maximumDifference = nextInTestData - nextInSampleData;}
    }
    return (maximumDifference < 608);
}

bool isBitwiseIdentical(const SGEXTN::Containers::Array<unsigned char>& a, const SGEXTN::Containers::Array<unsigned char>& b){
    if(a.length() != b.length()){return false;}
    for(int i=0; i<a.length(); i++){
        if(a.at(i) != b.at(i)){return false;}
    }
    return true;
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
    if(SGEXTN::SeerattraNum::TrueRandom::randomInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom generate array of 32 bit integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom generate array of 64 bit integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom generate array of 32 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom generate array of 64 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomFloat32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom generate array of 32 bit floating point number fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomFloat64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::TrueRandom generate array of 64 bit floating point number fail");}
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
    if(SGEXTN::SeerattraNum::SimpleRandom::randomInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom generate array of 32 bit integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom generate array of 64 bit integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom generate array of 32 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom generate array of 64 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomFloat32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom generate array of 32 bit floating point number fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomFloat64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SimpleRandom generate array of 64 bit floating point number fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testDirectRandom(){
    SGEXTN::SeerattraNum::DirectRandom generator;
    generator.seed(firstSeed);
    if(generator.randomInt32() != 45808322){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom generate first integer first seed fail");}
    if(generator.randomInt32() != -662986976){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom generate second integer first seed fail");}
    if(isCloseEnough(generator.randomFloat32(), 0.10182f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom generate first floating point first seed fail");}
    if(isCloseEnough(generator.randomFloat32(), 0.35892f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom generate second floating point first seed fail");}
    generator.seed(secondSeed);
    if(generator.randomInt32() != 360871459){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom generate first integer second seed fail");}
    if(generator.randomInt32() != -589113209){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom generate second integer second seed fail");}
    if(isCloseEnough(generator.randomFloat32(), 0.49299f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom generate first floating point second seed fail");}
    if(isCloseEnough(generator.randomFloat32(), 0.90498f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectRandom generate second floating point second seed fail");}
    SGEXTN::SeerattraNum::DirectRandom sampleRng;
    sampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    (void)sampleRng.randomInt32();
    SGEXTN::Containers::Array<unsigned char> serialiseArray(37);
    serialiseArray.at(0) = static_cast<unsigned char>(0x02);
    serialiseArray.at(1) = static_cast<unsigned char>(0x65);
    serialiseArray.at(2) = static_cast<unsigned char>(0xe2);
    serialiseArray.at(3) = static_cast<unsigned char>(0xf2);
    serialiseArray.at(4) = static_cast<unsigned char>(0x2e);
    serialiseArray.at(5) = static_cast<unsigned char>(0x64);
    serialiseArray.at(6) = static_cast<unsigned char>(0xb6);
    serialiseArray.at(7) = static_cast<unsigned char>(0xd4);
    serialiseArray.at(8) = static_cast<unsigned char>(0x22);
    serialiseArray.at(9) = static_cast<unsigned char>(0x93);
    serialiseArray.at(10) = static_cast<unsigned char>(0x9a);
    serialiseArray.at(11) = static_cast<unsigned char>(0x22);
    serialiseArray.at(12) = static_cast<unsigned char>(0xcc);
    serialiseArray.at(13) = static_cast<unsigned char>(0x46);
    serialiseArray.at(14) = static_cast<unsigned char>(0x5c);
    serialiseArray.at(15) = static_cast<unsigned char>(0xb5);
    serialiseArray.at(16) = static_cast<unsigned char>(0x71);
    serialiseArray.at(17) = static_cast<unsigned char>(0x55);
    serialiseArray.at(18) = static_cast<unsigned char>(0xd7);
    serialiseArray.at(19) = static_cast<unsigned char>(0xea);
    serialiseArray.at(20) = static_cast<unsigned char>(0x0c);
    serialiseArray.at(21) = static_cast<unsigned char>(0xd3);
    serialiseArray.at(22) = static_cast<unsigned char>(0x21);
    serialiseArray.at(23) = static_cast<unsigned char>(0xde);
    serialiseArray.at(24) = static_cast<unsigned char>(0xde);
    serialiseArray.at(25) = static_cast<unsigned char>(0x74);
    serialiseArray.at(26) = static_cast<unsigned char>(0x69);
    serialiseArray.at(27) = static_cast<unsigned char>(0xf6);
    serialiseArray.at(28) = static_cast<unsigned char>(0x15);
    serialiseArray.at(29) = static_cast<unsigned char>(0x02);
    serialiseArray.at(30) = static_cast<unsigned char>(0xb5);
    serialiseArray.at(31) = static_cast<unsigned char>(0x94);
    serialiseArray.at(32) = static_cast<unsigned char>(0x01);
    serialiseArray.at(33) = static_cast<unsigned char>(0x8e);
    serialiseArray.at(34) = static_cast<unsigned char>(0x0b);
    serialiseArray.at(35) = static_cast<unsigned char>(0xf8);
    serialiseArray.at(36) = static_cast<unsigned char>(0xcd);
    bool isValid = false;
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandom>::serialise(sampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::DirectRandom fail");}
    SGEXTN::SeerattraNum::DirectRandom unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandom>::unserialise(serialiseArray, &isValid);
    if(sampleRng.randomInt64() != unserialisedRng.randomInt64() || sampleRng.randomInt32() != unserialisedRng.randomInt32()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::DirectRandom fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandom>::lengthof(sampleRng) != 37){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::DirectRandom fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionInteger(){
    SGEXTN::SeerattraNum::UniformDistributionInteger testRng(false, 1, 6);
    testRng.seed(firstSeed);
    std::uniform_int_distribution sampleRng(1, 6);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<int> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<int> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger first test fail");}
    if(testRng.getInclusiveMin() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger get minimum boundary fail");}
    if(testRng.getInclusiveMax() != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger get maximum boundary fail");}
    testRng.setRange(-5, -1);
    testRng.seed(secondSeed);
    sampleRng = std::uniform_int_distribution(-5, -1);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::UniformDistributionInteger newSampleRng(false, 0, 100);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(0));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(100));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UniformDistributionInteger>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::UniformDistributionInteger fail");}
    SGEXTN::SeerattraNum::UniformDistributionInteger unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UniformDistributionInteger>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::UniformDistributionInteger fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UniformDistributionInteger>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::UniformDistributionInteger fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionFloatingPoint(){
    SGEXTN::SeerattraNum::UniformDistributionFloatingPoint testRng(false, 1.0f, 2.0f);
    testRng.seed(firstSeed);
    std::uniform_real_distribution sampleRng(1.0f, 2.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint first test fail");}
    if(testRng.getMinimum() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint get minimum boundary fail");}
    if(testRng.getMaximum() != 2.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint get maximum boundary fail");}
    testRng.setRange(-2.0f, -1.0f);
    testRng.seed(secondSeed);
    sampleRng = std::uniform_real_distribution(-2.0f, -1.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::UniformDistributionFloatingPoint newSampleRng(false, -0.5f, 0.5f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(-0.5f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.5f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UniformDistributionFloatingPoint>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::UniformDistributionFloatingPoint fail");}
    SGEXTN::SeerattraNum::UniformDistributionFloatingPoint unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UniformDistributionFloatingPoint>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::UniformDistributionFloatingPoint fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UniformDistributionFloatingPoint>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::UniformDistributionFloatingPoint fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testBernoulliDistribution(){
    SGEXTN::SeerattraNum::BernoulliDistribution testRng(false, 0.25f);
    testRng.seed(firstSeed);
    std::bernoulli_distribution sampleRng(0.25f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<int> testData(100000);
    SGEXTN::Containers::Array<int> sampleData(100000);
    for(int i=0; i<100000; i++){
        if(testRng.randomValue() == true){testData.at(i) = 1;}
        else{testData.at(i) = 0;}
        if(sampleRng(standardLibraryRng) == true){sampleData.at(i) = 1;}
        else{sampleData.at(i) = 0;}
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution first test fail");}
    if(testRng.getChanceOfTrue() != 0.25f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution get probability fail");}
    testRng.setChanceOfTrue(0.75f);
    testRng.seed(secondSeed);
    sampleRng = std::bernoulli_distribution(0.75f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        if(testRng.randomValue() == true){testData.at(i) = 1;}
        else{testData.at(i) = 0;}
        if(sampleRng(standardLibraryRng) == true){sampleData.at(i) = 1;}
        else{sampleData.at(i) = 0;}
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::BernoulliDistribution newSampleRng(false, 0.26f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(41);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.26f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::BernoulliDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::BernoulliDistribution fail");}
    SGEXTN::SeerattraNum::BernoulliDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::BernoulliDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::BernoulliDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::BernoulliDistribution>::lengthof(newSampleRng) != 41){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::BernoulliDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testBinomialDistribution(){
    SGEXTN::SeerattraNum::BinomialDistribution testRng(false, 0.25f, 100);
    testRng.seed(firstSeed);
    std::binomial_distribution sampleRng(100, 0.25f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<int> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<int> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution first test fail");}
    if(testRng.getChanceOfTrue() != 0.25f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution get probability fail");}
    if(testRng.getAttemptCount() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution get number of attempts fail");}
    testRng.setChanceOfTrue(0.75f);
    testRng.setAttemptCount(1000);
    testRng.seed(secondSeed);
    sampleRng = std::binomial_distribution(1000, 0.75f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::BinomialDistribution newSampleRng(false, 0.26f, 26);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.26f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(26));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::BinomialDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::BinomialDistribution fail");}
    SGEXTN::SeerattraNum::BinomialDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::BinomialDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::BinomialDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::BinomialDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::BinomialDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testNegativeBinomialDistribution(){
    SGEXTN::SeerattraNum::NegativeBinomialDistribution testRng(false, 0.25f, 100);
    testRng.seed(firstSeed);
    std::negative_binomial_distribution sampleRng(100, 0.25f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<int> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<int> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution first test fail");}
    if(testRng.getChanceOfTrue() != 0.25f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution get probability fail");}
    if(testRng.getSuccessCount() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution get number of successful attempts fail");}
    testRng.setChanceOfTrue(0.75f);
    testRng.setSuccessCount(1000);
    testRng.seed(secondSeed);
    sampleRng = std::negative_binomial_distribution(1000, 0.75f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::NegativeBinomialDistribution newSampleRng(false, 0.26f, 26);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.26f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(26));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::NegativeBinomialDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::NegativeBinomialDistribution fail");}
    SGEXTN::SeerattraNum::NegativeBinomialDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::NegativeBinomialDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::NegativeBinomialDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::NegativeBinomialDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::NegativeBinomialDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testGeometricDistribution(){
    SGEXTN::SeerattraNum::GeometricDistribution testRng(false, 0.25f);
    testRng.seed(firstSeed);
    std::geometric_distribution sampleRng(0.25f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<int> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<int> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution first test fail");}
    if(testRng.getChanceOfTrue() != 0.25f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution get probability fail");}
    testRng.setChanceOfTrue(0.05f);
    testRng.seed(secondSeed);
    sampleRng = std::geometric_distribution(0.05f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::GeometricDistribution newSampleRng(false, 0.26f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(41);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.26f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GeometricDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::GeometricDistribution fail");}
    SGEXTN::SeerattraNum::GeometricDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GeometricDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::GeometricDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GeometricDistribution>::lengthof(newSampleRng) != 41){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::GeometricDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testPoissonDistribution(){
    SGEXTN::SeerattraNum::PoissonDistribution testRng(false, 100.0f);
    testRng.seed(firstSeed);
    std::poisson_distribution sampleRng(100.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<int> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<int> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution first test fail");}
    if(testRng.getMean() != 100.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution get mean fail");}
    testRng.setMean(10.0f);
    testRng.seed(secondSeed);
    sampleRng = std::poisson_distribution(10.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::PoissonDistribution newSampleRng(false, 26.0f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(41);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(26.0f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::PoissonDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::PoissonDistribution fail");}
    SGEXTN::SeerattraNum::PoissonDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::PoissonDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::PoissonDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::PoissonDistribution>::lengthof(newSampleRng) != 41){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::PoissonDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testExponentialDistribution(){
    SGEXTN::SeerattraNum::ExponentialDistribution testRng(false, 1.0f);
    testRng.seed(firstSeed);
    std::exponential_distribution sampleRng(1.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution first test fail");}
    if(testRng.getMeanEventsPerTime() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution get mean number of events occurring per unit time fail");}
    testRng.setMeanEventsPerTime(10.0f);
    testRng.seed(secondSeed);
    sampleRng = std::exponential_distribution(10.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::ExponentialDistribution newSampleRng(false, 26.0f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(41);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(26.0f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::ExponentialDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::ExponentialDistribution fail");}
    SGEXTN::SeerattraNum::ExponentialDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::ExponentialDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::ExponentialDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::ExponentialDistribution>::lengthof(newSampleRng) != 41){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::ExponentialDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testGammaDistribution(){
    SGEXTN::SeerattraNum::GammaDistribution testRng(false, 2.0f, 5.0f);
    testRng.seed(firstSeed);
    std::gamma_distribution sampleRng(2.0f, 5.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution first test fail");}
    if(testRng.getVariableCount() != 2.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution get number of exponentially distributed variables being summed fail");}
    if(testRng.getVariableMean() != 5.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution get mean of each exponentially distributed variable fail");}
    testRng.setVariableCount(10.0f);
    testRng.setVariableMean(20.0f);
    testRng.seed(secondSeed);
    sampleRng = std::gamma_distribution(10.0f, 20.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::GammaDistribution newSampleRng(false, 26.0f, 0.26f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(26.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.26f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GammaDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::GammaDistribution fail");}
    SGEXTN::SeerattraNum::GammaDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GammaDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::GammaDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GammaDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::GammaDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeibullDistribution(){
    SGEXTN::SeerattraNum::WeibullDistribution testRng(false, 0.5f, 10.0f);
    testRng.seed(firstSeed);
    std::weibull_distribution sampleRng(0.5f, 10.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution first test fail");}
    if(testRng.getFailureBehaviour() != 0.5f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution get failure behaviour fail");}
    if(testRng.getCharacteristicLifespan() != 10.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution get characteristic lifespan fail");}
    testRng.setFailureBehaviour(2.0f);
    testRng.setCharacteristicLifespan(100.0f);
    testRng.seed(secondSeed);
    sampleRng = std::weibull_distribution(2.0f, 100.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::WeibullDistribution newSampleRng(false, 2.6f, 26.0f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.6f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(26.0f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeibullDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::WeibullDistribution fail");}
    SGEXTN::SeerattraNum::WeibullDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeibullDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::WeibullDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeibullDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::WeibullDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testGumbelDistribution(){
    SGEXTN::SeerattraNum::GumbelDistribution testRng(false, -1.0f, 1.0f);
    testRng.seed(firstSeed);
    std::extreme_value_distribution sampleRng(-1.0f, 1.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution first test fail");}
    if(testRng.getMode() != -1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution get mode fail");}
    if(testRng.getSpread() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution get spread fail");}
    testRng.setMode(100.0f);
    testRng.setSpread(5.0f);
    testRng.seed(secondSeed);
    sampleRng = std::extreme_value_distribution(100.0f, 5.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::GumbelDistribution newSampleRng(false, 26.0f, 2.6f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(26.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.6f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GumbelDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::GumbelDistribution fail");}
    SGEXTN::SeerattraNum::GumbelDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GumbelDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::GumbelDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::GumbelDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::GumbelDistribution");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testNormalDistribution(){
    SGEXTN::SeerattraNum::NormalDistribution testRng(false, -1.0f, 1.0f);
    testRng.seed(firstSeed);
    std::normal_distribution sampleRng(-1.0f, 1.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution first test fail");}
    if(testRng.getMean() != -1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution get mean fail");}
    if(testRng.getStandardDeviation() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution get standard deviation fail");}
    testRng.setMean(100.0f);
    testRng.setStandardDeviation(5.0f);
    testRng.seed(secondSeed);
    sampleRng = std::normal_distribution(100.0f, 5.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::NormalDistribution newSampleRng(false, 26.0f, 2.6f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(26.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.6f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::NormalDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::NormalDistribution fail");}
    SGEXTN::SeerattraNum::NormalDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::NormalDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::NormalDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::NormalDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::NormalDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testLogNormalDistribution(){
    SGEXTN::SeerattraNum::LogNormalDistribution testRng(false, -1.0f, 1.0f);
    testRng.seed(firstSeed);
    std::lognormal_distribution sampleRng(-1.0f, 1.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution first test fail");}
    if(testRng.getMeanOfLn() != -1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution get mean of ln of data fail");}
    if(testRng.getStandardDeviationOfLn() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution get standard deviation of ln of data fail");}
    testRng.setMeanOfLn(1.0f);
    testRng.setStandardDeviationOfLn(0.125f);
    testRng.seed(secondSeed);
    sampleRng = std::lognormal_distribution(1.0f, 0.125f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::LogNormalDistribution newSampleRng(false, 2.6f, 0.26f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.6f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.26f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::LogNormalDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::LogNormalDistribution fail");}
    SGEXTN::SeerattraNum::LogNormalDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::LogNormalDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::LogNormalDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::LogNormalDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::LogNormalDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testCauchyDistribution(){
    SGEXTN::SeerattraNum::CauchyDistribution testRng(false, -1.0f, 1.0f);
    testRng.seed(firstSeed);
    std::cauchy_distribution sampleRng(-1.0f, 1.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution first test fail");}
    if(testRng.getMedian() != -1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution get median fail");}
    if(testRng.getHalfWidth() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution get half width fail");}
    testRng.setMedian(20.0f);
    testRng.setHalfWidth(5.0f);
    testRng.seed(secondSeed);
    sampleRng = std::cauchy_distribution(20.0f, 5.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::CauchyDistribution newSampleRng(false, 26.0f, 2.6f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(26.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.6f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::CauchyDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::CauchyDistribution fail");}
    SGEXTN::SeerattraNum::CauchyDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::CauchyDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::CauchyDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::CauchyDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::CauchyDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testChiSquaredDistribution(){
    SGEXTN::SeerattraNum::ChiSquaredDistribution testRng(false, 5.0f);
    testRng.seed(firstSeed);
    std::chi_squared_distribution sampleRng(5.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution first test fail");}
    if(testRng.getDegreesOfFreedom() != 5.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution get number of degrees of freedom fail");}
    testRng.setDegreesOfFreedom(100.0f);
    testRng.seed(secondSeed);
    sampleRng = std::chi_squared_distribution(100.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::ChiSquaredDistribution newSampleRng(false, 2.6f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(41);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.6f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::ChiSquaredDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::ChiSquaredDistribution fail");}
    SGEXTN::SeerattraNum::ChiSquaredDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::ChiSquaredDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::ChiSquaredDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::ChiSquaredDistribution>::lengthof(newSampleRng) != 41){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::ChiSquaredDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testFisherFDistribution(){
    SGEXTN::SeerattraNum::FisherFDistribution testRng(false, 5.0f, 10.0f);
    testRng.seed(firstSeed);
    std::fisher_f_distribution sampleRng(5.0f, 10.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution first test fail");}
    if(testRng.getNumeratorDegreesOfFreedom() != 5.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution get number of degrees of freedom in numerator fail");}
    if(testRng.getDenominatorDegreesOfFreedom() != 10.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution get number of degrees of freedom in denominator fail");}
    testRng.setNumeratorDegreesOfFreedom(14.0f);
    testRng.setDenominatorDegreesOfFreedom(7.0f);
    testRng.seed(secondSeed);
    sampleRng = std::fisher_f_distribution(14.0f, 7.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::FisherFDistribution newSampleRng(false, 0.26f, 2.6f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(45);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.26f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.6f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::FisherFDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::FisherFDistribution fail");}
    SGEXTN::SeerattraNum::FisherFDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::FisherFDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::FisherFDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::FisherFDistribution>::lengthof(newSampleRng) != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::FisherFDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testStudentTDistribution(){
    SGEXTN::SeerattraNum::StudentTDistribution testRng(false, 5.0f);
    testRng.seed(firstSeed);
    std::student_t_distribution sampleRng(5.0f);
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution first test fail");}
    if(testRng.getDegreesOfFreedom() != 5.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution get number of degrees of freedom fail");}
    testRng.setDegreesOfFreedom(100.0f);
    testRng.seed(secondSeed);
    sampleRng = std::student_t_distribution(100.0f);
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::StudentTDistribution newSampleRng(false, 2.6f);
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(41);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.6f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::StudentTDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::StudentTDistribution fail");}
    SGEXTN::SeerattraNum::StudentTDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::StudentTDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::StudentTDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::StudentTDistribution>::lengthof(newSampleRng) != 41){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::StudentTDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedIndexSelectionDistribution(){
    const SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    const SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution testRng(false, firstWeights);
    testRng.seed(firstSeed);
    std::discrete_distribution sampleRng(&firstWeights.at(0), &firstWeights.at(0) + firstWeights.length());
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<int> testData = testRng.randomIndexArray(100000);
    SGEXTN::Containers::Array<int> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution first test fail");}
    SGEXTN::Containers::Array<float> firstWeightsReturned = testRng.getWeights();
    bool isSame = true;
    if(firstWeights.length() != firstWeightsReturned.length()){isSame = false;}
    for(int i=0; i<firstWeights.length(); i++){
        if(firstWeights.at(i) != firstWeightsReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution get weights fail");}
    testRng.setWeights(secondWeights);
    testRng.seed(secondSeed);
    sampleRng = std::discrete_distribution(&secondWeights.at(0), &secondWeights.at(0) + secondWeights.length());
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomIndex();
        sampleData.at(i) = sampleRng(standardLibraryRng);
    }
    if(testIfDistributionSameDiscrete(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution newSampleRng(false, SGEXTN::Containers::Array<float>(0.01f, 0.1f, 0.89f));
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(62);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(25));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<bool>::serialise(false));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(3));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(4));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.01f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.1f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.89f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution fail");}
    SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomIndex() != unserialisedRng.randomIndex()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution>::lengthof(newSampleRng) != 62){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedPiecewiseConstantDistribution(){
    const SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    const SGEXTN::Containers::Array<float> firstBoundaries(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
    const SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    const SGEXTN::Containers::Array<float> secondBoundaries(-4.0f, -3.0f, -2.0f, -1.0f);
    SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution testRng(false, firstWeights, firstBoundaries);
    testRng.seed(firstSeed);
    std::piecewise_constant_distribution sampleRng(&firstBoundaries.at(0), &firstBoundaries.at(0) + firstBoundaries.length(), &firstWeights.at(0));
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = static_cast<float>(sampleRng(standardLibraryRng));
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution first test fail");}
    SGEXTN::Containers::Array<float> firstWeightsReturned = testRng.getWeights();
    bool isSame = true;
    if(firstWeights.length() != firstWeightsReturned.length()){isSame = false;}
    for(int i=0; i<firstWeights.length(); i++){
        if(firstWeights.at(i) != firstWeightsReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution get weights fail");}
    SGEXTN::Containers::Array<float> firstBoundariesReturned = testRng.getBoundaries();
    isSame = true;
    if(firstBoundaries.length() != firstBoundariesReturned.length()){isSame = false;}
    for(int i=0; i<firstBoundaries.length(); i++){
        if(firstBoundaries.at(i) != firstBoundariesReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution get boundaries fail");}
    testRng.setWeightsAndBoundaries(secondWeights, secondBoundaries);
    testRng.seed(secondSeed);
    sampleRng = std::piecewise_constant_distribution(&secondBoundaries.at(0), &secondBoundaries.at(0) + secondBoundaries.length(), &secondWeights.at(0));
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = static_cast<float>(sampleRng(standardLibraryRng));
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution newSampleRng(false, SGEXTN::Containers::Array<float>(0.01f, 0.1f, 0.89f), SGEXTN::Containers::Array<float>(1.0f, 2.0f, 3.0f, 4.0f));
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(91);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(25));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<bool>::serialise(false));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(3));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(4));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.01f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.1f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.89f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(29));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<bool>::serialise(false));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(4));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(4));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(1.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(3.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(4.0f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution fail");}
    SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution>::lengthof(newSampleRng) != 91){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedPiecewiseLinearDistribution(){
    const SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    const SGEXTN::Containers::Array<float> firstBoundaries(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    const SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    const SGEXTN::Containers::Array<float> secondBoundaries(-3.0f, -2.0f, -1.0f);
    SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution testRng(false, firstWeights, firstBoundaries);
    testRng.seed(firstSeed);
    std::piecewise_linear_distribution sampleRng(&firstBoundaries.at(0), &firstBoundaries.at(0) + firstBoundaries.length(), &firstWeights.at(0));
    seedStandardLibraryRng(firstSeed);
    SGEXTN::Containers::Array<float> testData = testRng.randomValueArray(100000);
    SGEXTN::Containers::Array<float> sampleData(100000);
    for(int i=0; i<100000; i++){
        sampleData.at(i) = static_cast<float>(sampleRng(standardLibraryRng));
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution first test fail");}
    SGEXTN::Containers::Array<float> firstWeightsReturned = testRng.getWeights();
    bool isSame = true;
    if(firstWeights.length() != firstWeightsReturned.length()){isSame = false;}
    for(int i=0; i<firstWeights.length(); i++){
        if(firstWeights.at(i) != firstWeightsReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution get weights fail");}
    SGEXTN::Containers::Array<float> firstBoundariesReturned = testRng.getBoundaries();
    isSame = true;
    if(firstBoundaries.length() != firstBoundariesReturned.length()){isSame = false;}
    for(int i=0; i<firstBoundaries.length(); i++){
        if(firstBoundaries.at(i) != firstBoundariesReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution get boundaries fail");}
    testRng.setWeightsAndBoundaries(secondWeights, secondBoundaries);
    testRng.seed(secondSeed);
    sampleRng = std::piecewise_linear_distribution(&secondBoundaries.at(0), &secondBoundaries.at(0) + secondBoundaries.length(), &secondWeights.at(0));
    seedStandardLibraryRng(secondSeed);
    for(int i=0; i<100000; i++){
        testData.at(i) = testRng.randomValue();
        sampleData.at(i) = static_cast<float>(sampleRng(standardLibraryRng));
    }
    if(testIfDistributionSameContinuous(sampleData, testData) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution second test fail");}
    bool isValid = false;
    int offset = 0;
    SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution newSampleRng(false, SGEXTN::Containers::Array<float>(0.01f, 0.01f, 0.1f, 0.88f), SGEXTN::Containers::Array<float>(1.0f, 2.0f, 3.0f, 4.0f));
    newSampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    SGEXTN::Containers::Array<unsigned char> serialiseArray(95);
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(newSampleRng.private_rngLocator));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(29));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<bool>::serialise(false));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(4));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(4));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.01f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.01f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.1f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(0.88f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(29));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<bool>::serialise(false));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(4));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<int>::serialise(4));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(1.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(2.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(3.0f));
    SGEXTN::Containers::MemoryCopySerialise::copySection(serialiseArray, offset, SGEXTN::Containers::Serialise<float>::serialise(4.0f));
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution>::serialise(newSampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution fail");}
    SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution>::unserialise(serialiseArray, &isValid);
    if(isValid == false || newSampleRng.randomValue() != unserialisedRng.randomValue()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution>::lengthof(newSampleRng) != 95){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testRandomPermutation(){
    SGEXTN::SeerattraNum::RandomPermutation generator(false);
    generator.seed(firstSeed);
    SGEXTN::Containers::Array<int> firstPermutation = generator.randomPermutation(5);
    if(firstPermutation.length() != 5 || firstPermutation.at(0) != 1 || firstPermutation.at(1) != 4 || firstPermutation.at(2) != 3 || firstPermutation.at(3) != 0 || firstPermutation.at(4) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation generate permutation first seed fail");}
    generator.seed(secondSeed);
    SGEXTN::Containers::Array<int> secondPermutation = generator.randomPermutation(4);
    if(secondPermutation.length() != 4 || secondPermutation.at(0) != 0 || secondPermutation.at(1) != 1 || secondPermutation.at(2) != 2 || secondPermutation.at(3) != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation generate permutation second seed fail");}
    bool isValid = false;
    SGEXTN::SeerattraNum::RandomPermutation sampleRng(false);
    sampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    const SGEXTN::Containers::Array<unsigned char> serialiseArray = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(sampleRng.private_rngLocator);
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::RandomPermutation>::serialise(sampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::RandomPermutation fail");}
    SGEXTN::SeerattraNum::RandomPermutation unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::RandomPermutation>::unserialise(serialiseArray, &isValid);
    SGEXTN::Containers::Array<int> output1 = sampleRng.randomPermutation(100);
    SGEXTN::Containers::Array<int> output2 = unserialisedRng.randomPermutation(100);
    for(int i=0; i<100; i++){
        if(output1.at(i) != output2.at(i)){isValid = false;}
    }
    if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::RandomPermutation fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::RandomPermutation>::lengthof(sampleRng) != 37){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::RandomPermutation fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testUnitSphereSample(){
    SGEXTN::SeerattraNum::UnitSphereSample generator(false);
    generator.seed(secondSeed);
    SGEXTN::Containers::Array<SGEXTN::Containers::Array<float>> sample(10000, SGEXTN::Containers::Array<float>(0));
    for(int i=0; i<10000; i++){
        sample.at(i) = generator.randomPoint(3);
    }
    float rho = 0.3f;
    float measuredVariation = 0.0f;
    for(int i=1; i<10000; i++){
        for(int j=0; j<i; j++){
            float dotProduct = sample.at(i).at(0) * sample.at(j).at(0) + sample.at(i).at(1) * sample.at(j).at(1) + sample.at(i).at(2) * sample.at(j).at(2);
            dotProduct = (1.0f - rho * rho) * SGEXTN::Math::FloatMath<float>::powerOf(1.0f + rho * rho - 2.0f * rho * dotProduct, -1.5f) - 1.0f;
            measuredVariation += dotProduct;
        }
    }
    measuredVariation *= (2.0f / 10000.0f / 9999.0f);
    float expectedVariation = 2.0f / 10000.0f / 9999.0f * ((1.0f + rho * rho) / (1.0f - rho * rho) / (1.0f - rho * rho) - 1.0f);
    float measurementValue = measuredVariation / SGEXTN::Math::FloatMath<float>::squareRoot(expectedVariation);
    if(measurementValue >= 1.645f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UnitSphereSample uniformity first test fail");}
    rho = 0.7f;
    measuredVariation = 0.0f;
    for(int i=1; i<10000; i++){
        for(int j=0; j<i; j++){
            float dotProduct = sample.at(i).at(0) * sample.at(j).at(0) + sample.at(i).at(1) * sample.at(j).at(1) + sample.at(i).at(2) * sample.at(j).at(2);
            dotProduct = (1.0f - rho * rho) * SGEXTN::Math::FloatMath<float>::powerOf(1.0f + rho * rho - 2.0f * rho * dotProduct, -1.5f) - 1.0f;
            measuredVariation += dotProduct;
        }
    }
    measuredVariation *= (2.0f / 10000.0f / 9999.0f);
    expectedVariation = 2.0f / 10000.0f / 9999.0f * ((1.0f + rho * rho) / (1.0f - rho * rho) / (1.0f - rho * rho) - 1.0f);
    measurementValue = measuredVariation / SGEXTN::Math::FloatMath<float>::squareRoot(expectedVariation);
    if(measurementValue >= 1.645f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UnitSphereSample uniformity second test fail");}
    bool isValid = false;
    SGEXTN::SeerattraNum::UnitSphereSample sampleRng(false);
    sampleRng.seed(SGEXTN::Containers::Array<unsigned int>(1, 726u));
    const SGEXTN::Containers::Array<unsigned char> serialiseArray = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandomInstanceLocator>::serialise(sampleRng.private_rngLocator);
    if(isBitwiseIdentical(serialiseArray, SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UnitSphereSample>::serialise(sampleRng)) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise serialise SGEXTN::SeerattraNum::UnitSphereSample fail");}
    SGEXTN::SeerattraNum::UnitSphereSample unserialisedRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UnitSphereSample>::unserialise(serialiseArray, &isValid);
    SGEXTN::Containers::Array<float> output1 = sampleRng.randomPoint(4);
    SGEXTN::Containers::Array<float> output2 = unserialisedRng.randomPoint(4);
    for(int i=0; i<4; i++){
        if(output1.at(i) != output2.at(i)){isValid = false;}
    }
    if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise unserialise SGEXTN::SeerattraNum::UnitSphereSample fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::UnitSphereSample>::lengthof(sampleRng) != 37){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise lengthof SGEXTN::SeerattraNum::UnitSphereSample fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testSobolSequence(){
    SGEXTN::SeerattraNum::SobolSequence generator(3);
    generator.seed(firstSeed);
    SGEXTN::Containers::Array<float> firstPoint = generator.nextTerm();
    if(firstPoint.length() != 3 || isCloseEnough(firstPoint.at(0), 0.51067f) == false || isCloseEnough(firstPoint.at(1), 0.34564f) == false || isCloseEnough(firstPoint.at(2), 0.60182f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence generate first point first seed fail");}
    SGEXTN::Containers::Array<float> secondPoint = generator.nextTerm();
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.01067f) == false || isCloseEnough(secondPoint.at(1), 0.84564f) == false || isCloseEnough(secondPoint.at(2), 0.10182f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence generate second point first seed fail");}
    generator.seed(secondSeed);
    firstPoint = generator.nextTerm();
    if(firstPoint.length() != 3 || isCloseEnough(firstPoint.at(0), 0.58402f) == false || isCloseEnough(firstPoint.at(1), 0.36284f) == false || isCloseEnough(firstPoint.at(2), 0.99299f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence generate first point second seed fail");}
    secondPoint = generator.nextTerm();
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.08402f) == false || isCloseEnough(secondPoint.at(1), 0.86284f) == false || isCloseEnough(secondPoint.at(2), 0.49299f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence generate second point second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testHaltonSequence(){
    SGEXTN::SeerattraNum::HaltonSequence generator(3);
    generator.seed(firstSeed);
    SGEXTN::Containers::Array<float> firstPoint = generator.nextTerm();
    if(firstPoint.length() != 3 || isCloseEnough(firstPoint.at(0), 0.5f) == false || isCloseEnough(firstPoint.at(1), 1.0f / 3.0f) == false || isCloseEnough(firstPoint.at(2), 0.8f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence generate first point first seed fail");}
    SGEXTN::Containers::Array<float> secondPoint = generator.nextTerm();
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.25f) == false || isCloseEnough(secondPoint.at(1), 2.0f / 3.0f) == false || isCloseEnough(secondPoint.at(2), 0.2f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence generate second point first seed fail");}
    generator.seed(secondSeed);
    firstPoint = generator.nextTerm();
    if(firstPoint.length() != 3 || isCloseEnough(firstPoint.at(0), 0.5f) == false || isCloseEnough(firstPoint.at(1), 1.0f / 3.0f) == false || isCloseEnough(firstPoint.at(2), 0.2f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence generate first point second seed fail");}
    secondPoint = generator.nextTerm();
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.25f) == false || isCloseEnough(secondPoint.at(1), 2.0f / 3.0f) == false || isCloseEnough(secondPoint.at(2), 0.4f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence generate second point second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testVoronoiNoise(){
    SGEXTN::SeerattraNum::VoronoiNoise noiseMap(3);
    noiseMap.seed(726);
    const SGEXTN::Containers::Array<float> testPoint1(0.0f, 0.0f, 0.0f);
    const SGEXTN::Containers::Array<float> testPoint2(0.35f, 0.35f, 0.35f);
    SGEXTN::Containers::Array<float> outputPoint = noiseMap.getPosition(0, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.034563f) == false || isCloseEnough(outputPoint.at(1), -0.10254f) == false || isCloseEnough(outputPoint.at(2), -0.14306f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise first seed get closest point to first test point fail");}
    outputPoint = noiseMap.getVectorFrom(0, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.034563f) == false || isCloseEnough(outputPoint.at(1), 0.10254f) == false || isCloseEnough(outputPoint.at(2), 0.14306f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise get vector fail");}
    if(isCloseEnough(noiseMap.getDistanceTo(0, testPoint1), 0.17938f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise get distance fail");}
    outputPoint = noiseMap.getPosition(1, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.040457f) == false || isCloseEnough(outputPoint.at(1), -0.11818f) == false || isCloseEnough(outputPoint.at(2), -0.70033f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise first seed get second closest point to first test point fail");}
    outputPoint = noiseMap.getPosition(0, testPoint2);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.91800f) == false || isCloseEnough(outputPoint.at(1), 0.083622f) == false || isCloseEnough(outputPoint.at(2), 0.11147f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise first seed get closest point to second test point fail");}
    outputPoint = noiseMap.getPosition(1, testPoint2);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.034563f) == false || isCloseEnough(outputPoint.at(1), -0.10254f) == false || isCloseEnough(outputPoint.at(2), -0.14306f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise first seed get second closest point to second test point fail");}
    noiseMap.seed(1965);
    outputPoint = noiseMap.getPosition(0, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.29695f) == false || isCloseEnough(outputPoint.at(1), -0.097455f) == false || isCloseEnough(outputPoint.at(2), 0.16516f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise second seed get closest point to first test point fail");}
    outputPoint = noiseMap.getPosition(1, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.031908f) == false || isCloseEnough(outputPoint.at(1), 0.66805f) == false || isCloseEnough(outputPoint.at(2), 0.11509f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise second seed get second closest point to first test point fail");}
    outputPoint = noiseMap.getPosition(0, testPoint2);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.29695f) == false || isCloseEnough(outputPoint.at(1), -0.097455f) == false || isCloseEnough(outputPoint.at(2), 0.16516f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise second seed get closest point to second test point fail");}
    outputPoint = noiseMap.getPosition(1, testPoint2);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.031908f) == false || isCloseEnough(outputPoint.at(1), 0.66805f) == false || isCloseEnough(outputPoint.at(2), 0.11509f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise second seed get second closest point to second test point fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testValueNoise(){
    SGEXTN::SeerattraNum::ValueNoise noiseMap(3, SGEXTN::SeerattraNum::SmoothingFunction::polynomial2);
    const SGEXTN::Containers::Array<float> firstPoint(0.25f, 0.25f, 0.25f);
    const SGEXTN::Containers::Array<float> secondPoint(-0.25f, -0.25f, -0.25f);
    noiseMap.seed(726);
    if(isCloseEnough(noiseMap.getHeight(firstPoint), -0.42717f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise get first point first seed fail");}
    if(isCloseEnough(noiseMap.getHeight(secondPoint), -0.60357f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise get second point first seed fail");}
    noiseMap.seed(1965);
    if(isCloseEnough(noiseMap.getHeight(firstPoint), -0.52749f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise get first point second seed fail");}
    if(isCloseEnough(noiseMap.getHeight(secondPoint), -0.39768f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ValueNoise get second point second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testPerlinNoise(){
    SGEXTN::SeerattraNum::PerlinNoise noiseMap(3, SGEXTN::SeerattraNum::SmoothingFunction::polynomial2);
    const SGEXTN::Containers::Array<float> firstPoint(0.25f, 0.25f, 0.25f);
    const SGEXTN::Containers::Array<float> secondPoint(-0.25f, -0.25f, -0.25f);
    noiseMap.seed(726);
    if(isCloseEnough(noiseMap.getHeight(firstPoint), -0.33693f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise get first point first seed fail");}
    if(isCloseEnough(noiseMap.getHeight(secondPoint), 0.45495f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise get second point first seed fail");}
    noiseMap.seed(1965);
    if(isCloseEnough(noiseMap.getHeight(firstPoint), 0.31241f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise get first point second seed fail");}
    if(isCloseEnough(noiseMap.getHeight(secondPoint), -0.28643f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise get second point second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testAll(){
    SGEXTN::InternalTest::SeerattraNumTest::testTrueRandom();
    SGEXTN::InternalTest::SeerattraNumTest::testSimpleRandom();
    SGEXTN::InternalTest::SeerattraNumTest::testDirectRandom();
    SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionInteger();
    SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionFloatingPoint();
    SGEXTN::InternalTest::SeerattraNumTest::testBernoulliDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testBinomialDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testNegativeBinomialDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testGeometricDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testPoissonDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testExponentialDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testGammaDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testWeibullDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testGumbelDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testNormalDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testLogNormalDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testCauchyDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testChiSquaredDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testFisherFDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testStudentTDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testWeightedIndexSelectionDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testWeightedPiecewiseConstantDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testWeightedPiecewiseLinearDistribution();
    SGEXTN::InternalTest::SeerattraNumTest::testRandomPermutation();
    SGEXTN::InternalTest::SeerattraNumTest::testUnitSphereSample();
    SGEXTN::InternalTest::SeerattraNumTest::testSobolSequence();
    SGEXTN::InternalTest::SeerattraNumTest::testHaltonSequence();
    SGEXTN::InternalTest::SeerattraNumTest::testVoronoiNoise();
    SGEXTN::InternalTest::SeerattraNumTest::testValueNoise();
    SGEXTN::InternalTest::SeerattraNumTest::testPerlinNoise();
}
