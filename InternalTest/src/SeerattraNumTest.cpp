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
#include <SGEXTN/SeerattraNum/DirectInteger.h>
#include <SGEXTN/SeerattraNum/DirectFloatingPoint.h>
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
#include <random>

namespace {
std::mt19937_64 stlRandomEngine;
SGEXTN::Containers::Array<unsigned int> firstSeed(1u, 2u, 3u, 4u, 5u);
SGEXTN::Containers::Array<unsigned int> secondSeed(6u, 7u, 8u, 9u, 10u);

void seedRandomEngine(const SGEXTN::Containers::Array<unsigned int>& seedArray){
    std::seed_seq seedSequence(&seedArray.at(0), &seedArray.at(0) + seedArray.length());
    stlRandomEngine.seed(seedSequence);
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
    generator.seed(firstSeed);
    if(generator.randomInteger() != 689864061){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger generate integer first seed fail");}
    SGEXTN::Containers::Array<int> randomArray = generator.randomIntegerArray(2);
    if(randomArray.at(0) != -2116458956 || randomArray.at(1) != -249517681){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger generate integer array first seed fail");}
    generator.seed(secondSeed);
    if(generator.randomInteger() != 986110788){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger generate integer second seed fail");}
    randomArray = generator.randomIntegerArray(2);
    if(randomArray.at(0) != 1930272640 || randomArray.at(1) != -10058938){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectInteger generate integer array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testDirectFloatingPoint(){
    std::uniform_real_distribution<float> stlRandomDistribution(0.0f, 1.0f);
    seedRandomEngine(firstSeed);
    SGEXTN::SeerattraNum::DirectFloatingPoint<float> generator(false);
    generator.seed(firstSeed);
    if(generator.randomFloatingPoint() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectFloatingPoint generate floating point first seed fail");}
    SGEXTN::Containers::Array<float> randomArray = generator.randomFloatingPointArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectFloatingPoint generate floating point array first seed fail");}
    seedRandomEngine(secondSeed);
    generator.seed(secondSeed);
    if(generator.randomFloatingPoint() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectFloatingPoint generate floating point second seed fail");}
    randomArray = generator.randomFloatingPointArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::DirectFloatingPoint generate floating point array second seed fail");}
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
    stlRandomDistribution.param(std::uniform_int_distribution<int>::param_type(-5, -1));
    stlRandomDistribution.reset();
    seedRandomEngine(secondSeed);
    generator.setInclusiveMin(-5);
    generator.setInclusiveMax(-1);
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
    stlRandomDistribution.param(std::uniform_real_distribution<float>::param_type(-2.0f, -1.0f));
    stlRandomDistribution.reset();
    seedRandomEngine(secondSeed);
    generator.setMinimum(-2.0f);
    generator.setMaximum(-1.0f);
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
    stlRandomDistribution.param(std::bernoulli_distribution::param_type(0.75f));
    stlRandomDistribution.reset();
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
    stlRandomDistribution.param(std::binomial_distribution<int>::param_type(1000, 0.75f));
    stlRandomDistribution.reset();
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
    stlRandomDistribution.param(std::negative_binomial_distribution<int>::param_type(1000, 0.75f));
    stlRandomDistribution.reset();
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
    stlRandomDistribution.param(std::geometric_distribution<int>::param_type(0.75f));
    stlRandomDistribution.reset();
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
    stlRandomDistribution.param(std::poisson_distribution<int>::param_type(10.0f));
    stlRandomDistribution.reset();
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
    stlRandomDistribution.param(std::exponential_distribution<float>::param_type(10.0f));
    stlRandomDistribution.reset();
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
    stlRandomDistribution.param(std::gamma_distribution<float>::param_type(10.0f, 20.0f));
    stlRandomDistribution.reset();
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
    stlRandomDistribution.param(std::weibull_distribution<float>::param_type(2.0f, 100.0f));
    stlRandomDistribution.reset();
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
    stlRandomDistribution.param(std::extreme_value_distribution<float>::param_type(100.0f, 5.0f));
    stlRandomDistribution.reset();
    seedRandomEngine(secondSeed);
    generator.setMode(100.0f);
    generator.setSpread(5.0f);
    generator.seed(secondSeed);
    if(generator.randomValue() != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution generate value second seed fail");}
    randomArray = generator.randomValueArray(2);
    if(randomArray.at(0) != stlRandomDistribution(stlRandomEngine) || randomArray.at(1) != stlRandomDistribution(stlRandomEngine)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SeerattraNum::GumbelDistribution generate array second seed fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testAll(){
    SGEXTN::InternalTest::SeerattraNumTest::testTrueRandom();
    SGEXTN::InternalTest::SeerattraNumTest::testSimpleRandom();
    SGEXTN::InternalTest::SeerattraNumTest::testDirectInteger();
    SGEXTN::InternalTest::SeerattraNumTest::testDirectFloatingPoint();
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
}
