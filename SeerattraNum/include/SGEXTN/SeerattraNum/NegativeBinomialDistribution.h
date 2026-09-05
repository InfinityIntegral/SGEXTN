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
#include <SGEXTN/SeerattraNum/GammaDistribution.h>
#include <SGEXTN/SeerattraNum/PoissonDistribution.h>
#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>

namespace SGEXTN::Containers {
template <typename T> class Array;
template <typename T> class Span;
}

namespace SGEXTN::SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum NegativeBinomialDistribution {
private:
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator_;
    float chanceOfTrue_;
    int successCount_;
    SGEXTN::SeerattraNum::GammaDistribution gammaDistribution_;
    SGEXTN::SeerattraNum::PoissonDistribution poissonDistribution_;
public:
    NegativeBinomialDistribution();
    explicit NegativeBinomialDistribution(bool useGlobal, float chanceOfTrue, int successCount);
    [[nodiscard]] static bool sendOut(const NegativeBinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(NegativeBinomialDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] int randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<int> randomValueArray(int count);
    [[nodiscard]] float getChanceOfTrue() const;
    [[nodiscard]] int getSuccessCount() const;
    void setChanceOfTrue(float chanceOfTrue);
    void setSuccessCount(int successCount);
};
}
