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
class DirectRandom;

class BuildLah_SGEXTN_SeerattraNum CauchyDistribution {
public:
    SGEXTN::SeerattraNum::DirectRandom* private_rng;
    bool private_ownsRng;
    float private_median;
    float private_halfWidth;
    CauchyDistribution(bool useGlobal, float median, float halfWidth);
    CauchyDistribution(const CauchyDistribution&) = delete;
    CauchyDistribution& operator=(const CauchyDistribution&) = delete;
    CauchyDistribution(CauchyDistribution&&) = delete;
    CauchyDistribution& operator=(CauchyDistribution&&) = delete;
    ~CauchyDistribution();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] float randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<float> randomValueArray(int count);
    [[nodiscard]] float getMedian() const;
    [[nodiscard]] float getHalfWidth() const;
    void setMedian(float median);
    void setHalfWidth(float halfWidth);
};
}
}
