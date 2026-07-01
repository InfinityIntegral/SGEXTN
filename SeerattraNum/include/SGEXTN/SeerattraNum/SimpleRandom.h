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

class BuildLah_SGEXTN_SeerattraNum SimpleRandom{
public:
    static DirectRandom* private_globalInstance;
    [[nodiscard]] static int randomInt32();
    [[nodiscard]] static long long randomInt64();
    [[nodiscard]] static unsigned int randomUnsignedInt32();
    [[nodiscard]] static unsigned long long randomUnsignedInt64();
    [[nodiscard]] static float randomFloat32();
    [[nodiscard]] static double randomFloat64();
    [[nodiscard]] static SGEXTN::Containers::Array<int> randomInt32Array(int count);
    [[nodiscard]] static SGEXTN::Containers::Array<long long> randomInt64Array(int count);
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned int> randomUnsignedInt32Array(int count);
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned long long> randomUnsignedInt64Array(int count);
    [[nodiscard]] static SGEXTN::Containers::Array<float> randomFloat32Array(int count);
    [[nodiscard]] static SGEXTN::Containers::Array<double> randomFloat64Array(int count);
    [[nodiscard]] static void* private_getRandomEngine();
    [[nodiscard]] static void* private_createRandomEngine(bool useGlobal);
    static void private_seedRandomEngine(void* randomEngine, const SGEXTN::Containers::Array<unsigned int>& seedArray);
};
}
}
