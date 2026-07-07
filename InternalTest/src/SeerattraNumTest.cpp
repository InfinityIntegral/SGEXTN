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
#include <random>
#include <SGEXTN/CoreText/Debug.h>
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
    SG(maximumDifference);
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
    SG(maximumDifference);
    return (maximumDifference < 608);
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
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedIndexSelectionDistribution(){
    const SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    const SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generator(false, firstWeights);
    generator.seed(firstSeed);
    if(generator.randomIndex() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomIndexArray(2);
    if(randomArray.at(0) != 4 || randomArray.at(1) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generate index first seed fail");}
    SGEXTN::Containers::Array<float> firstWeightsReturned = generator.getWeights();
    bool isSame = true;
    if(firstWeights.length() != firstWeightsReturned.length()){isSame = false;}
    for(int i=0; i<firstWeights.length(); i++){
        if(firstWeights.at(i) != firstWeightsReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution get weights fail");}
    generator.setWeights(secondWeights);
    generator.seed(secondSeed);
    if(generator.randomIndex() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generate index second seed fail");}
    randomArray = generator.randomIndexArray(2);
    if(randomArray.at(0) != 2 || randomArray.at(1) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedPiecewiseConstantDistribution(){
    const SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    const SGEXTN::Containers::Array<float> firstBoundaries(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
    const SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    const SGEXTN::Containers::Array<float> secondBoundaries(-4.0f, -3.0f, -2.0f, -1.0f);
    SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generator(false, firstWeights, firstBoundaries);
    generator.seed(firstSeed);
    if(isCloseEnough(generator.randomValue(), 1.1600f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(isCloseEnough(randomArray.at(0), 5.5369f) == false || isCloseEnough(randomArray.at(1), 2.2637f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generate array first seed fail");}
    SGEXTN::Containers::Array<float> firstWeightsReturned = generator.getWeights();
    bool isSame = true;
    if(firstWeights.length() != firstWeightsReturned.length()){isSame = false;}
    for(int i=0; i<firstWeights.length(); i++){
        if(firstWeights.at(i) != firstWeightsReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution get weights fail");}
    SGEXTN::Containers::Array<float> firstBoundariesReturned = generator.getBoundaries();
    isSame = true;
    if(firstBoundaries.length() != firstBoundariesReturned.length()){isSame = false;}
    for(int i=0; i<firstBoundaries.length(); i++){
        if(firstBoundaries.at(i) != firstBoundariesReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution get boundaries fail");}
    generator.setWeightsAndBoundaries(secondWeights, secondBoundaries);
    generator.seed(secondSeed);
    if(isCloseEnough(generator.randomValue(), -3.5631f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(isCloseEnough(randomArray.at(0), -1.1783f) == false || isCloseEnough(randomArray.at(1), -1.6591f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedPiecewiseLinearDistribution(){
    const SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    const SGEXTN::Containers::Array<float> firstBoundaries(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    const SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    const SGEXTN::Containers::Array<float> secondBoundaries(-3.0f, -2.0f, -1.0f);
    SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generator(false, firstWeights, firstBoundaries);
    generator.seed(firstSeed);
    if(isCloseEnough(generator.randomValue(), 1.9147f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(isCloseEnough(randomArray.at(0), 1.8146f) == false || isCloseEnough(randomArray.at(1), 3.9966f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generate array first seed fail");}
    SGEXTN::Containers::Array<float> firstWeightsReturned = generator.getWeights();
    bool isSame = true;
    if(firstWeights.length() != firstWeightsReturned.length()){isSame = false;}
    for(int i=0; i<firstWeights.length(); i++){
        if(firstWeights.at(i) != firstWeightsReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution get weights fail");}
    SGEXTN::Containers::Array<float> firstBoundariesReturned = generator.getBoundaries();
    isSame = true;
    if(firstBoundaries.length() != firstBoundariesReturned.length()){isSame = false;}
    for(int i=0; i<firstBoundaries.length(); i++){
        if(firstBoundaries.at(i) != firstBoundariesReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution get boundaries fail");}
    generator.setWeightsAndBoundaries(secondWeights, secondBoundaries);
    generator.seed(secondSeed);
    if(isCloseEnough(generator.randomValue(), -2.3781f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(isCloseEnough(randomArray.at(0), -1.3481f) == false || isCloseEnough(randomArray.at(1), -1.0087f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testRandomPermutation(){
    SGEXTN::SeerattraNum::RandomPermutation generator(false);
    generator.seed(firstSeed);
    SGEXTN::Containers::Array<int> firstPermutation = generator.randomPermutation(5);
    if(firstPermutation.length() != 5 || firstPermutation.at(0) != 1 || firstPermutation.at(1) != 4 || firstPermutation.at(2) != 3 || firstPermutation.at(3) != 0 || firstPermutation.at(4) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation generate permutation first seed fail");}
    generator.seed(secondSeed);
    SGEXTN::Containers::Array<int> secondPermutation = generator.randomPermutation(4);
    if(secondPermutation.length() != 4 || secondPermutation.at(0) != 0 || secondPermutation.at(1) != 1 || secondPermutation.at(2) != 2 || secondPermutation.at(3) != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation generate permutation second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testUnitSphereSample(){
    SGEXTN::SeerattraNum::UnitSphereSample generator(false);
    generator.seed(firstSeed);
    SGEXTN::Containers::Array<float> firstPoint = generator.randomPoint(2);
    if(firstPoint.length() != 2 || isCloseEnough(firstPoint.at(0), -0.87714f) == false || isCloseEnough(firstPoint.at(1), 0.48023f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UnitSphereSample generate first point fail");}
    generator.seed(secondSeed);
    SGEXTN::Containers::Array<float> secondPoint = generator.randomPoint(3);
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), -0.053906f) == false || isCloseEnough(secondPoint.at(1), -0.72207f) == false || isCloseEnough(secondPoint.at(2), 0.68972f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UnitSphereSample generate second point fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testSobolSequence(){
    SGEXTN::SeerattraNum::SobolSequence generator(3);
    generator.seed(726);
    SGEXTN::Containers::Array<float> firstPoint = generator.nextTerm();
    if(firstPoint.length() != 3 || isCloseEnough(firstPoint.at(0), 0.036170f) == false || isCloseEnough(firstPoint.at(1), 0.015295f) == false || isCloseEnough(firstPoint.at(2), 0.38167f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence generate first point first seed fail");}
    SGEXTN::Containers::Array<float> secondPoint = generator.nextTerm();
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.53617f) == false || isCloseEnough(secondPoint.at(1), 0.51530f) == false || isCloseEnough(secondPoint.at(2), 0.88167f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence generate second point first seed fail");}
    generator.seed(1965);
    firstPoint = generator.nextTerm();
    if(firstPoint.length() != 3 || isCloseEnough(firstPoint.at(0), 0.28590f) == false || isCloseEnough(firstPoint.at(1), 0.81898f) == false || isCloseEnough(firstPoint.at(2), 0.092364f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence generate first point second seed fail");}
    secondPoint = generator.nextTerm();
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.78590f) == false || isCloseEnough(secondPoint.at(1), 1.31898f - 1.0f) == false || isCloseEnough(secondPoint.at(2), 0.59236) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::SobolSequence generate second point second seed fail");}
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
