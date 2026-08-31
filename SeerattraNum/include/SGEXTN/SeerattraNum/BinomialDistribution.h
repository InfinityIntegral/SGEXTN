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
#include <SGEXTN/SeerattraNum/GeometricDistribution.h>
#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>

namespace SGEXTN::Containers {
template <typename T> class Array;
template <typename T> class Span;
}

namespace SGEXTN::SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum BinomialDistribution {
private:
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator_;
    float chanceOfTrue_;
    int attemptCount_;
    SGEXTN::SeerattraNum::GeometricDistribution geometricDistribution_;
    float precompConstantL_;
    float precompConstantC_;
    float precompConstantM_;
    float exponentialFactorLeft_;
    float exponentialFactorRight_;
    float negativeReciprocalExponentialFactorLeft_;
    float reciprocalExponentialFactorRight_;
    float boundaryFarLeft_;
    float boundaryCenterLeft_;
    float boundaryCenterRight_;
    float boundaryFarRight_;
    float weightLeftTail_;
    float weightBothTails_;
    float weightAllExceptCenter_;
    float comparisonMultiplier_;
    float comparisonConstant_;
    void redoPrecompute();
public:
    explicit BinomialDistribution();
    explicit BinomialDistribution(bool useGlobal, float chanceOfTrue, int attemptCount);
    [[nodiscard]] static bool sendOut(const BinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(BinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] int randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<int> randomValueArray(int count);
    [[nodiscard]] float getChanceOfTrue() const;
    [[nodiscard]] int getAttemptCount() const;
    void setChanceOfTrue(float chanceOfTrue);
    void setAttemptCount(int attemptCount);
};
}
