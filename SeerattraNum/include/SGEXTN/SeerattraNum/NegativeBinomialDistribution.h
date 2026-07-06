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
#include <SGEXTN/SeerattraNum/GammaDistribution.h>
#include <SGEXTN/SeerattraNum/PoissonDistribution.h>

namespace SGEXTN {
namespace SeerattraNum {
class DirectRandom;

class BuildLah_SGEXTN_SeerattraNum NegativeBinomialDistribution {
public:
    SGEXTN::SeerattraNum::DirectRandom* private_rng;
    bool private_ownsRng;
    float private_chanceOfTrue;
    int private_successCount;
    SGEXTN::SeerattraNum::GammaDistribution private_gammaDistribution;
    SGEXTN::SeerattraNum::PoissonDistribution private_poissonDistribution;
    NegativeBinomialDistribution(bool useGlobal, float chanceOfTrue, int successCount);
    NegativeBinomialDistribution(const NegativeBinomialDistribution&) = delete;
    NegativeBinomialDistribution& operator=(const NegativeBinomialDistribution&) = delete;
    NegativeBinomialDistribution(NegativeBinomialDistribution&&) = delete;
    NegativeBinomialDistribution& operator=(NegativeBinomialDistribution&&) = delete;
    ~NegativeBinomialDistribution();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] int randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<int> randomValueArray(int count);
    [[nodiscard]] float getChanceOfTrue() const;
    [[nodiscard]] int getSuccessCount() const;
    void setChanceOfTrue(float chanceOfTrue);
    void setSuccessCount(int successCount);
};
}
}
