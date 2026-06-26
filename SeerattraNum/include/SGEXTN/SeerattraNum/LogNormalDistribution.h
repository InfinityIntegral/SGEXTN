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
template <typename FloatingPoint> class BuildLah_SGEXTN_SeerattraNum LogNormalDistribution {
public:
    void* private_stlRandomEngine;
    void* private_stlDistribution;
    FloatingPoint private_meanOfLn;
    FloatingPoint private_standardDeviationOfLn;
    LogNormalDistribution(bool useGlobal, FloatingPoint meanOfLn, FloatingPoint standardDeviationOfLn);
    LogNormalDistribution(const LogNormalDistribution&) = delete;
    LogNormalDistribution& operator=(const LogNormalDistribution&) = delete;
    LogNormalDistribution(LogNormalDistribution&&) = delete;
    LogNormalDistribution& operator=(LogNormalDistribution&&) = delete;
    ~LogNormalDistribution();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] FloatingPoint randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<FloatingPoint> randomValueArray(int count);
    [[nodiscard]] FloatingPoint getMeanOfLn() const;
    [[nodiscard]] FloatingPoint getStandardDeviationOfLn() const;
    void setMeanOfLn(FloatingPoint meanOfLn);
    void setStandardDeviationOfLn(FloatingPoint standardDeviationOfLn);
};
}
}
