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

#pragma once
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/SeerattraNum/GeometricDistribution.h>
#include <SGEXTN/SeerattraNum/ExponentialDistribution.h>

namespace SGEXTN {
namespace SeerattraNum {
class DirectRandom;

class BuildLah_SGEXTN_SeerattraNum BinomialDistribution {
public:
    SGEXTN::SeerattraNum::DirectRandom* private_rng;
    bool private_ownsRng;
    float private_chanceOfTrue;
    int private_attemptCount;
    SGEXTN::SeerattraNum::GeometricDistribution private_geometricDistribution;
    SGEXTN::SeerattraNum::ExponentialDistribution private_standardExponentialDistribution;
    float private_precompConstantL;
    float private_precompConstantC;
    float private_precompConstantM;
    float private_exponentialFactorLeft;
    float private_exponentialFactorRight;
    float private_negativeReciprocalExponentialFactorLeft;
    float private_reciprocalExponentialFactorRight;
    float private_boundaryFarLeft;
    float private_boundaryCenterLeft;
    float private_boundaryCenterRight;
    float private_boundaryFarRight;
    float private_weightLeftTail;
    float private_weightBothTails;
    float private_weightAllExceptCenter;
    float private_comparisonMultiplier;
    float private_comparisonConstant;
    BinomialDistribution(bool useGlobal, float chanceOfTrue, int attemptCount);
    BinomialDistribution(const BinomialDistribution&) = delete;
    BinomialDistribution& operator=(const BinomialDistribution&) = delete;
    BinomialDistribution(BinomialDistribution&&) = delete;
    BinomialDistribution& operator=(BinomialDistribution&&) = delete;
    ~BinomialDistribution();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] int randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<int> randomValueArray(int count);
    [[nodiscard]] float getChanceOfTrue() const;
    [[nodiscard]] int getAttemptCount() const;
    void setChanceOfTrue(float chanceOfTrue);
    void setAttemptCount(int attemptCount);
    void private_redoPrecompute();
};
}
}
