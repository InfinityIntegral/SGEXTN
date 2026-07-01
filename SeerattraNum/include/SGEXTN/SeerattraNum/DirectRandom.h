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
class BuildLah_SGEXTN_SeerattraNum DirectRandom{
public:
    unsigned long long private_firstNum;
    unsigned long long private_secondNum;
    unsigned long long private_thirdNum;
    unsigned long long private_fourthNum;
    unsigned int private_cache;
    bool private_cacheActive;
    DirectRandom();
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] int randomInt32();
    [[nodiscard]] long long randomInt64();
    [[nodiscard]] unsigned int randomUnsignedInt32();
    [[nodiscard]] unsigned long long randomUnsignedInt64();
    [[nodiscard]] float randomFloat32();
    [[nodiscard]] double randomFloat64();
    [[nodiscard]] SGEXTN::Containers::Array<int> randomInt32Array(int count);
    [[nodiscard]] SGEXTN::Containers::Array<long long> randomInt64Array(int count);
    [[nodiscard]] SGEXTN::Containers::Array<unsigned int> randomUnsignedInt32Array(int count);
    [[nodiscard]] SGEXTN::Containers::Array<unsigned long long> randomUnsignedInt64Array(int count);
    [[nodiscard]] SGEXTN::Containers::Array<float> randomFloat32Array(int count);
    [[nodiscard]] SGEXTN::Containers::Array<double> randomFloat64Array(int count);
};
}
}
