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
#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Array;
}

namespace SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum UniformDistributionInteger {
public:
    SGEXTN::SeerattraNum::DirectRandomInstanceLocator private_rngLocator;
    int private_inclusiveMin;
    int private_inclusiveMax;
    UniformDistributionInteger();
    UniformDistributionInteger(bool useGlobal, int inclusiveMin, int inclusiveMax);
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(const UniformDistributionInteger& x);
    [[nodiscard]] static UniformDistributionInteger unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success);
    [[nodiscard]] static int lengthof(const UniformDistributionInteger& x);
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] int randomValue();
    [[nodiscard]] int private_randomValue(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& externalLocator) const;
    [[nodiscard]] SGEXTN::Containers::Array<int> randomValueArray(int count);
    [[nodiscard]] int getInclusiveMin() const;
    [[nodiscard]] int getInclusiveMax() const;
    void setRange(int inclusiveMin, int inclusiveMax);
};
}
}
