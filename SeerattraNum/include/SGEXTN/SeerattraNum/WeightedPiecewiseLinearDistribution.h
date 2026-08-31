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
#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>

namespace SGEXTN::Containers {
template <typename T> class Span;
}

namespace SGEXTN::SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum WeightedPiecewiseLinearDistribution {
private:
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator rngLocator_;
    SGEXTN::Containers::Array<float> weights_;
    SGEXTN::Containers::Array<float> boundaries_;
    SGEXTN::Containers::Array<float> prefixSums_;
    void updatePrefixSums();
public:
    explicit WeightedPiecewiseLinearDistribution();
    explicit WeightedPiecewiseLinearDistribution(bool useGlobal, const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries);
    [[nodiscard]] static bool sendOut(const WeightedPiecewiseLinearDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(WeightedPiecewiseLinearDistribution& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(const WeightedPiecewiseLinearDistribution& x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] float randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<float> randomValueArray(int count);
    [[nodiscard]] SGEXTN::Containers::Array<float> getWeights() const;
    [[nodiscard]] SGEXTN::Containers::Array<float> getBoundaries() const;
    void setWeightsAndBoundaries(const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries);
};
}
