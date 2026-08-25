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
#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Array;
template <typename T> class Span;
}

namespace SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum PoissonDistribution {
public:
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator private_rngLocator;
    float private_mean;
    float private_smallMeanProductThreshold;
    float private_precompConstantA;
    float private_precompConstantB;
    float private_squeezeBoundU;
    float private_squeezeBoundV;
    float private_lnMean;
    float private_lnAcceptRate;
    explicit PoissonDistribution();
    explicit PoissonDistribution(bool useGlobal, float mean);
    [[nodiscard]] static bool sendOut(const PoissonDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(PoissonDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] int randomValue();
    [[nodiscard]] int private_randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const;
    [[nodiscard]] SGEXTN::Containers::Array<int> randomValueArray(int count);
    [[nodiscard]] float getMean() const;
    void setMean(float mean);
    void private_redoPrecompute();
};
}
}
