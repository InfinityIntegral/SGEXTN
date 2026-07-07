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

class BuildLah_SGEXTN_SeerattraNum GumbelDistribution {
public:
    SGEXTN::SeerattraNum::DirectRandom* private_rng;
    bool private_ownsRng;
    float private_mode;
    float private_spread;
    GumbelDistribution(bool useGlobal, float mode, float spread);
    GumbelDistribution(const GumbelDistribution&) = delete;
    GumbelDistribution& operator=(const GumbelDistribution&) = delete;
    GumbelDistribution(GumbelDistribution&&) = delete;
    GumbelDistribution& operator=(GumbelDistribution&&) = delete;
    ~GumbelDistribution();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] float randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<float> randomValueArray(int count);
    [[nodiscard]] float getMode() const;
    [[nodiscard]] float getSpread() const;
    void setMode(float mode);
    void setSpread(float spread);
};
}
}
