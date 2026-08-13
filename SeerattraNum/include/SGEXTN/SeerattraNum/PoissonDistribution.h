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
    PoissonDistribution();
    PoissonDistribution(bool useGlobal, float mean);
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(const PoissonDistribution& x);
    [[nodiscard]] static PoissonDistribution unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success);
    [[nodiscard]] static int lengthof(const PoissonDistribution& x);
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
