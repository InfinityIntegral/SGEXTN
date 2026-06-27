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
template <typename WeightType> class BuildLah_SGEXTN_SeerattraNum WeightedIndexSelectionDistribution {
public:
    void* private_stlRandomEngine;
    void* private_stlDistribution;
    SGEXTN::Containers::Array<WeightType> private_weights;
    WeightedIndexSelectionDistribution(bool useGlobal, const SGEXTN::Containers::Array<WeightType>& weights);
    WeightedIndexSelectionDistribution(const WeightedIndexSelectionDistribution&) = delete;
    WeightedIndexSelectionDistribution& operator=(const WeightedIndexSelectionDistribution&) = delete;
    WeightedIndexSelectionDistribution(WeightedIndexSelectionDistribution&&) = delete;
    WeightedIndexSelectionDistribution& operator=(WeightedIndexSelectionDistribution&&) = delete;
    ~WeightedIndexSelectionDistribution();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] int randomIndex();
    [[nodiscard]] SGEXTN::Containers::Array<int> randomIndexArray(int count);
    [[nodiscard]] SGEXTN::Containers::Array<WeightType> getWeights() const;
    void setWeights(const SGEXTN::Containers::Array<WeightType>& weights);
};
}
}
