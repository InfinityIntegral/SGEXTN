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
#include <random>

namespace {
std::mt19937_64 stlRandomEngine;
SGEXTN::Containers::Array<unsigned int> firstSeed(1u, 2u, 3u, 4u, 5u);
SGEXTN::Containers::Array<unsigned int> secondSeed(6u, 7u, 8u, 9u, 10u);

void seedRandomEngine(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + seedArray.length());
    stlRandomEngine.seed(seedSequence);
}

bool isCloseEnough(float a, float b){
    return (a > b - 0.001f && a < b + 0.001f);
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
#include <SGEXTN/CoreText/Debug.h>
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
    std::uniform_int_distribution<int> stlRandomDistribution(1, 6);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::UniformDistributionInteger<int> generator(false, 1, 6);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger generate number first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger generate array first seed fail");}
    if(generator.getInclusiveMin() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger get minimum boundary fail");}
    if(generator.getInclusiveMax() != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger get maximum boundary fail");}
    stlRandomDistribution = std::uniform_int_distribution<int>(-5, -1);
    seedRandomEngine(secondSeed);
    generator.setRange(-5, -1);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger generate number second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionInteger generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testUniformDistributionFloatingPoint(){
    std::uniform_real_distribution<float> stlRandomDistribution(1.0f, 2.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::UniformDistributionFloatingPoint<float> generator(false, 1.0f, 2.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint generate number first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint generate array first seed fail");}
    if(generator.getMinimum() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint get minimum boundary fail");}
    if(generator.getMaximum() != 2.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint get maximum boundary fail");}
    stlRandomDistribution = std::uniform_real_distribution<float>(-2.0f, -1.0f);
    seedRandomEngine(secondSeed);
    generator.setRange(-2.0f, -1.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint generate number second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UniformDistributionFloatingPoint generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testBernoulliDistribution(){
    std::bernoulli_distribution stlRandomDistribution(0.25f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::BernoulliDistribution<float> generator(false, 0.25f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<bool> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution generate array first seed fail");}
    if(generator.getChanceOfTrue() != 0.25f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution get probability fail");}
    stlRandomDistribution = std::bernoulli_distribution(0.75f);
    seedRandomEngine(secondSeed);
    generator.setChanceOfTrue(0.75f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BernoulliDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testBinomialDistribution(){
    std::binomial_distribution<int> stlRandomDistribution(100, 0.25f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::BinomialDistribution<float, int> generator(false, 0.25f, 100);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution generate array first seed fail");}
    if(generator.getChanceOfTrue() != 0.25f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution get probability fail");}
    if(generator.getAttemptCount() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution get number of attempts fail");}
    stlRandomDistribution = std::binomial_distribution<int>(1000, 0.75f);
    seedRandomEngine(secondSeed);
    generator.setChanceOfTrue(0.75f);
    generator.setAttemptCount(1000);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::BinomialDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testNegativeBinomialDistribution(){
    std::negative_binomial_distribution<int> stlRandomDistribution(100, 0.25f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::NegativeBinomialDistribution<float, int> generator(false, 0.25f, 100);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution generate array first seed fail");}
    if(generator.getChanceOfTrue() != 0.25f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution get probability fail");}
    if(generator.getSuccessCount() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution get number of successful attempts fail");}
    stlRandomDistribution = std::negative_binomial_distribution<int>(1000, 0.75f);
    seedRandomEngine(secondSeed);
    generator.setChanceOfTrue(0.75f);
    generator.setSuccessCount(1000);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NegativeBinomialDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testGeometricDistribution(){
    std::geometric_distribution<int> stlRandomDistribution(0.25f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::GeometricDistribution<float, int> generator(false, 0.25f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution generate array first seed fail");}
    if(generator.getChanceOfTrue() != 0.25f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution get probability fail");}
    stlRandomDistribution = std::geometric_distribution<int>(0.75f);
    seedRandomEngine(secondSeed);
    generator.setChanceOfTrue(0.75f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GeometricDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testPoissonDistribution(){
    std::poisson_distribution<int> stlRandomDistribution(100.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::PoissonDistribution<float, int> generator(false, 100.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution generate array first seed fail");}
    if(generator.getMean() != 100.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution get mean fail");}
    stlRandomDistribution = std::poisson_distribution<int>(10.0f);
    seedRandomEngine(secondSeed);
    generator.setMean(10.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PoissonDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testExponentialDistribution(){
    std::exponential_distribution<float> stlRandomDistribution(1.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::ExponentialDistribution<float> generator(false, 1.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution generate array first seed fail");}
    if(generator.getMeanEventsPerTime() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution get mean number of events occurring per unit time fail");}
    stlRandomDistribution = std::exponential_distribution<float>(10.0f);
    seedRandomEngine(secondSeed);
    generator.setMeanEventsPerTime(10.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ExponentialDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testGammaDistribution(){
    std::gamma_distribution<float> stlRandomDistribution(2.0f, 5.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::GammaDistribution<float> generator(false, 2.0f, 5.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution generate array first seed fail");}
    if(generator.getVariableCount() != 2.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution get number of exponentially distributed variables being summed fail");}
    if(generator.getVariableMean() != 5.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution get mean of each exponentially distributed variable fail");}
    stlRandomDistribution = std::gamma_distribution<float>(10.0f, 20.0f);
    seedRandomEngine(secondSeed);
    generator.setVariableCount(10.0f);
    generator.setVariableMean(20.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GammaDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeibullDistribution(){
    std::weibull_distribution<float> stlRandomDistribution(0.5f, 10.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::WeibullDistribution<float> generator(false, 0.5f, 10.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution generate array first seed fail");}
    if(generator.getFailureBehaviour() != 0.5f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution get failure behaviour fail");}
    if(generator.getCharacteristicLifespan() != 10.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution get characteristic lifespan fail");}
    stlRandomDistribution = std::weibull_distribution<float>(2.0f, 100.0f);
    seedRandomEngine(secondSeed);
    generator.setFailureBehaviour(2.0f);
    generator.setCharacteristicLifespan(100.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeibullDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testGumbelDistribution(){
    std::extreme_value_distribution<float> stlRandomDistribution(-1.0f, 1.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::GumbelDistribution<float> generator(false, -1.0f, 1.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution generate array first seed fail");}
    if(generator.getMode() != -1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution get mode fail");}
    if(generator.getSpread() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution get spread fail");}
    stlRandomDistribution = std::extreme_value_distribution<float>(100.0f, 5.0f);
    seedRandomEngine(secondSeed);
    generator.setMode(100.0f);
    generator.setSpread(5.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testNormalDistribution(){
    std::normal_distribution<float> stlRandomDistribution(-1.0f, 1.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::NormalDistribution<float> generator(false, -1.0f, 1.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution generate array first seed fail");}
    if(generator.getMean() != -1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution get mean fail");}
    if(generator.getStandardDeviation() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution get standard deviation fail");}
    stlRandomDistribution = std::normal_distribution<float>(100.0f, 5.0f);
    seedRandomEngine(secondSeed);
    generator.setMean(100.0f);
    generator.setStandardDeviation(5.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::NormalDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testLogNormalDistribution(){
    std::lognormal_distribution<float> stlRandomDistribution(-1.0f, 1.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::LogNormalDistribution<float> generator(false, -1.0f, 1.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution generate array first seed fail");}
    if(generator.getMeanOfLn() != -1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution get mean of ln of data fail");}
    if(generator.getStandardDeviationOfLn() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution get standard deviation of ln of data fail");}
    stlRandomDistribution = std::lognormal_distribution<float>(1.0f, 0.125f);
    seedRandomEngine(secondSeed);
    generator.setMeanOfLn(1.0f);
    generator.setStandardDeviationOfLn(0.125f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::LogNormalDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testCauchyDistribution(){
    std::cauchy_distribution<float> stlRandomDistribution(-1.0f, 1.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::CauchyDistribution<float> generator(false, -1.0f, 1.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution generate array first seed fail");}
    if(generator.getMedian() != -1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution get median fail");}
    if(generator.getHalfWidth() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution get half width fail");}
    stlRandomDistribution = std::cauchy_distribution<float>(100.0f, 5.0f);
    seedRandomEngine(secondSeed);
    generator.setMedian(100.0f);
    generator.setHalfWidth(5.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::CauchyDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testChiSquaredDistribution(){
    std::chi_squared_distribution<float> stlRandomDistribution(5.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::ChiSquaredDistribution<float> generator(false, 5.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution generate array first seed fail");}
    if(generator.getDegreesOfFreedom() != 5.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution get number of degrees of freedom fail");}
    stlRandomDistribution = std::chi_squared_distribution<float>(100.0f);
    seedRandomEngine(secondSeed);
    generator.setDegreesOfFreedom(100.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::ChiSquaredDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testFisherFDistribution(){
    std::fisher_f_distribution<float> stlRandomDistribution(5.0f, 10.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::FisherFDistribution<float> generator(false, 5.0f, 10.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution generate array first seed fail");}
    if(generator.getNumeratorDegreesOfFreedom() != 5.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution get number of degrees of freedom in numerator fail");}
    if(generator.getDenominatorDegreesOfFreedom() != 10.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution get number of degrees of freedom in denominator fail");}
    stlRandomDistribution = std::fisher_f_distribution<float>(14.0f, 7.0f);
    seedRandomEngine(secondSeed);
    generator.setNumeratorDegreesOfFreedom(14.0f);
    generator.setDenominatorDegreesOfFreedom(7.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::FisherFDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testStudentTDistribution(){
    std::student_t_distribution<float> stlRandomDistribution(5.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::StudentTDistribution<float> generator(false, 5.0f);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution generate array first seed fail");}
    if(generator.getDegreesOfFreedom() != 5.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution get number of degrees of freedom fail");}
    stlRandomDistribution = std::student_t_distribution<float>(100.0f);
    seedRandomEngine(secondSeed);
    generator.setDegreesOfFreedom(100.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::StudentTDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedIndexSelectionDistribution(){
    SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    std::discrete_distribution<int> stlRandomDistribution(&firstWeights.at(0), &firstWeights.at(0) + firstWeights.length());
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution<float> generator(false, firstWeights);
    generator.seed(firstSeed);
    if(generator.randomIndex() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomIndexArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generate index first seed fail");}
    SGEXTN::Containers::Array<float> firstWeightsReturned = generator.getWeights();
    bool isSame = true;
    if(firstWeights.length() != firstWeightsReturned.length()){isSame = false;}
    for(int i=0; i<firstWeights.length(); i++){
        if(firstWeights.at(i) != firstWeightsReturned.at(i)){isSame = false;}
    }
    if(isSame == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution get weights fail");}
    stlRandomDistribution = std::discrete_distribution<int>(&secondWeights.at(0), &secondWeights.at(0) + secondWeights.length());
    seedRandomEngine(secondSeed);
    generator.setWeights(secondWeights);
    generator.seed(secondSeed);
    if(generator.randomIndex() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generate index second seed fail");}
    randomArray = generator.randomIndexArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedIndexSelectionDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedPiecewiseConstantDistribution(){
    SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    SGEXTN::Containers::Array<float> firstBoundaries(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
    SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    SGEXTN::Containers::Array<float> secondBoundaries(-4.0f, -3.0f, -2.0f, -1.0f);
    std::piecewise_constant_distribution<float> stlRandomDistribution(&firstBoundaries.at(0), &firstBoundaries.at(0) + firstBoundaries.length(), &firstWeights.at(0));
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution<float, float> generator(false, firstWeights, firstBoundaries);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generate array first seed fail");}
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
    stlRandomDistribution = std::piecewise_constant_distribution<float>(&secondBoundaries.at(0), &secondBoundaries.at(0) + secondBoundaries.length(), &secondWeights.at(0));
    seedRandomEngine(secondSeed);
    generator.setWeightsAndBoundaries(secondWeights, secondBoundaries);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseConstantDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testWeightedPiecewiseLinearDistribution(){
    SGEXTN::Containers::Array<float> firstWeights(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    SGEXTN::Containers::Array<float> firstBoundaries(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    SGEXTN::Containers::Array<float> secondWeights(0.5f, 0.1f, 2.0f);
    SGEXTN::Containers::Array<float> secondBoundaries(-3.0f, -2.0f, -1.0f);
    std::piecewise_linear_distribution<float> stlRandomDistribution(&firstBoundaries.at(0), &firstBoundaries.at(0) + firstBoundaries.length(), &firstWeights.at(0));
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution<float, float> generator(false, firstWeights, firstBoundaries);
    generator.seed(firstSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generate value first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generate array first seed fail");}
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
    stlRandomDistribution = std::piecewise_linear_distribution<float>(&secondBoundaries.at(0), &secondBoundaries.at(0) + secondBoundaries.length(), &secondWeights.at(0));
    seedRandomEngine(secondSeed);
    generator.setWeightsAndBoundaries(secondWeights, secondBoundaries);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::WeightedPiecewiseLinearDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testRandomPermutation(){
    SGEXTN::SeerattraNum::RandomPermutation generator(false);
    generator.seed(firstSeed);
    SGEXTN::Containers::Array<int> firstPermutation = generator.randomPermutation(5);
    if(firstPermutation.length() != 5 || firstPermutation.at(0) != 2 || firstPermutation.at(1) != 3 || firstPermutation.at(2) != 4 || firstPermutation.at(3) != 0 || firstPermutation.at(4) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation generate permutation first seed fail");}
    generator.seed(secondSeed);
    SGEXTN::Containers::Array<int> secondPermutation = generator.randomPermutation(4);
    if(secondPermutation.length() != 4 || secondPermutation.at(0) != 0 || secondPermutation.at(1) != 1 || secondPermutation.at(2) != 3 || secondPermutation.at(3) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::RandomPermutation generate permutation second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testUnitSphereSample(){
    SGEXTN::SeerattraNum::UnitSphereSample generator(false);
    generator.seed(firstSeed);
    SGEXTN::Containers::Array<float> firstPoint = generator.randomPoint(2);
    if(firstPoint.length() != 2 || isCloseEnough(firstPoint.at(0), -0.92076f) == false || isCloseEnough(firstPoint.at(1), -0.39013) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UnitSphereSample generate first point fail");}
    generator.seed(secondSeed);
    SGEXTN::Containers::Array<float> secondPoint = generator.randomPoint(3);
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.94004f) == false || isCloseEnough(secondPoint.at(1), 0.10584f) == false || isCloseEnough(secondPoint.at(2), 0.32422f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::UnitSphereSample generate second point fail");}
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
    generator.seed(726);
    SGEXTN::Containers::Array<float> firstPoint = generator.nextTerm();
    if(firstPoint.length() != 3 || isCloseEnough(firstPoint.at(0), 0.5f) == false || isCloseEnough(firstPoint.at(1), 2.0f / 3.0f) == false || isCloseEnough(firstPoint.at(2), 0.8f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence generate first point first seed fail");}
    SGEXTN::Containers::Array<float> secondPoint = generator.nextTerm();
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.25f) == false || isCloseEnough(secondPoint.at(1), 1.0f / 3.0f) == false || isCloseEnough(secondPoint.at(2), 0.2f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence generate second point first seed fail");}
    generator.seed(1965);
    firstPoint = generator.nextTerm();
    if(firstPoint.length() != 3 || isCloseEnough(firstPoint.at(0), 0.5f) == false || isCloseEnough(firstPoint.at(1), 2.0f / 3.0f) == false || isCloseEnough(firstPoint.at(2), 0.4f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence generate first point second seed fail");}
    secondPoint = generator.nextTerm();
    if(secondPoint.length() != 3 || isCloseEnough(secondPoint.at(0), 0.25f) == false || isCloseEnough(secondPoint.at(1), 1.0f / 3.0f) == false || isCloseEnough(secondPoint.at(2), 0.8f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::HaltonSequence generate second point second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testVoronoiNoise(){
    SGEXTN::SeerattraNum::VoronoiNoise noiseMap(3);
    noiseMap.seed(726);
    const SGEXTN::Containers::Array<float> testPoint1(0.0f, 0.0f, 0.0f);
    const SGEXTN::Containers::Array<float> testPoint2(0.35f, 0.35f, 0.35f);
    SGEXTN::Containers::Array<float> outputPoint = noiseMap.getPosition(0, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.017993f) == false || isCloseEnough(outputPoint.at(1), 0.11588f) == false || isCloseEnough(outputPoint.at(2), 0.13573f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise first seed get closest point to first test point fail");}
    outputPoint = noiseMap.getVectorFrom(0, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.017993f) == false || isCloseEnough(outputPoint.at(1), -0.11588f) == false || isCloseEnough(outputPoint.at(2), -0.13573f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise get vector fail");}
    if(isCloseEnough(noiseMap.getDistanceTo(0, testPoint1), 0.17938f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise get distance fail");}
    outputPoint = noiseMap.getPosition(1, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.84598f) == false || isCloseEnough(outputPoint.at(1), -0.021936f) == false || isCloseEnough(outputPoint.at(2), 0.22727f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise first seed get second closest point to first test point fail");}
    outputPoint = noiseMap.getPosition(0, testPoint2);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.017993f) == false || isCloseEnough(outputPoint.at(1), 0.11588f) == false || isCloseEnough(outputPoint.at(2), 0.13573f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise first seed get closest point to second test point fail");}
    outputPoint = noiseMap.getPosition(1, testPoint2);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), 0.15600f) == false || isCloseEnough(outputPoint.at(1), -0.093905f) == false || isCloseEnough(outputPoint.at(2), 0.95159f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise first seed get second closest point to second test point fail");}
    noiseMap.seed(1965);
    outputPoint = noiseMap.getPosition(0, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.11358f) == false || isCloseEnough(outputPoint.at(1), 0.30637f) == false || isCloseEnough(outputPoint.at(2), -0.13487f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise second seed get closest point to first test point fail");}
    outputPoint = noiseMap.getPosition(1, testPoint1);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.016363f) == false || isCloseEnough(outputPoint.at(1), 0.0033550f) == false || isCloseEnough(outputPoint.at(2), -0.86490f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise second seed get second closest point to first test point fail");}
    outputPoint = noiseMap.getPosition(0, testPoint2);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.11358f) == false || isCloseEnough(outputPoint.at(1), 0.30637f) == false || isCloseEnough(outputPoint.at(2), -0.13487f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise second seed get closest point to second test point fail");}
    outputPoint = noiseMap.getPosition(1, testPoint2);
    if(outputPoint.length() != 3 || isCloseEnough(outputPoint.at(0), -0.27972f) == false || isCloseEnough(outputPoint.at(1), 0.16646f) == false || isCloseEnough(outputPoint.at(2), 0.97845f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::VoronoiNoise second seed get second closest point to second test point fail");}
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
    if(isCloseEnough(noiseMap.getHeight(firstPoint), 0.27678f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise get first point first seed fail");}
    if(isCloseEnough(noiseMap.getHeight(secondPoint), -0.29634f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise get second point first seed fail");}
    noiseMap.seed(1965);
    if(isCloseEnough(noiseMap.getHeight(firstPoint), -0.10025f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise get first point second seed fail");}
    if(isCloseEnough(noiseMap.getHeight(secondPoint), -0.0084291f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::PerlinNoise get second point second seed fail");}
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
