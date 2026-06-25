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

namespace SGEXTN {
namespace SeerattraNum {
template <typename ProbabilityType, typename Integer> class BuildLah_SGEXTN_SeerattraNum BinomialDistribution {
public:
    void* private_stlRandomEngine;
    void* private_stlDistribution;
    ProbabilityType private_chanceOfTrue;
    Integer private_attemptCount;
    BinomialDistribution(bool useGlobal, ProbabilityType chanceOfTrue, Integer attemptCount);
    BinomialDistribution(const BinomialDistribution&) = delete;
    BinomialDistribution& operator=(const BinomialDistribution&) = delete;
    BinomialDistribution(BinomialDistribution&&) = delete;
    BinomialDistribution& operator=(BinomialDistribution&&) = delete;
    ~BinomialDistribution();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] Integer randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<Integer> randomValueArray(int count);
    [[nodiscard]] ProbabilityType getChanceOfTrue() const;
    [[nodiscard]] Integer getAttemptCount() const;
    void setChanceOfTrue(ProbabilityType chanceOfTrue);
    void setAttemptCount(Integer attemptCount);
};
}
}
