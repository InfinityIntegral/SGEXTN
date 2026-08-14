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

namespace SGEXTN {
namespace SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum WeightedPiecewiseLinearDistribution {
public:
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator private_rngLocator;
    SGEXTN::Containers::Array<float> private_weights;
    SGEXTN::Containers::Array<float> private_boundaries;
    SGEXTN::Containers::Array<float> private_prefixSums;
    void private_updatePrefixSums();
    WeightedPiecewiseLinearDistribution();
    WeightedPiecewiseLinearDistribution(bool useGlobal, const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries);
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(const WeightedPiecewiseLinearDistribution& x);
    [[nodiscard]] static WeightedPiecewiseLinearDistribution unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success);
    [[nodiscard]] static int lengthof(const WeightedPiecewiseLinearDistribution& x);
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] float randomValue();
    [[nodiscard]] SGEXTN::Containers::Array<float> randomValueArray(int count);
    [[nodiscard]] SGEXTN::Containers::Array<float> getWeights() const;
    [[nodiscard]] SGEXTN::Containers::Array<float> getBoundaries() const;
    void setWeightsAndBoundaries(const SGEXTN::Containers::Array<float>& weights, const SGEXTN::Containers::Array<float>& boundaries);
};
}
}
