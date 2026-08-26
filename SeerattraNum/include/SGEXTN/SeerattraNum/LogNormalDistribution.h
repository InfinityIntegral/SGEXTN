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
#include <SGEXTN/SeerattraNum/NormalDistribution.h>
#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>

namespace SGEXTN::Containers {
template <typename T> class Array;
}

namespace SGEXTN::SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum LogNormalDistribution {
public:
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator private_rngLocator;
    float private_meanOfLn;
    float private_standardDeviationOfLn;
    SGEXTN::SeerattraNum::NormalDistribution private_normalDistribution;
    explicit LogNormalDistribution();
    explicit LogNormalDistribution(bool useGlobal, float meanOfLn, float standardDeviationOfLn);
    [[nodiscard]] static bool sendOut(const LogNormalDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(LogNormalDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] float randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<float> randomValueArray(int count);
    [[nodiscard]] float getMeanOfLn() const;
    [[nodiscard]] float getStandardDeviationOfLn() const;
    void setMeanOfLn(float meanOfLn);
    void setStandardDeviationOfLn(float standardDeviationOfLn);
};
}
