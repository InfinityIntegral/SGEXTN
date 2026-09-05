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

namespace SGEXTN::Containers {
template <typename T> class Array;
template <typename T> class Span;
}

namespace SGEXTN::SeerattraNum {
class DirectRandomInstanceLocator;

class BuildLah_SGEXTN_SeerattraNum DirectRandom {
private:
    friend class SGEXTN::SeerattraNum::DirectRandomInstanceLocator;
    unsigned long long firstNum_;
    unsigned long long secondNum_;
    unsigned long long thirdNum_;
    unsigned long long fourthNum_;
    unsigned int cache_;
    bool cacheActive_;
    [[nodiscard]] static DirectRandom* createRng(bool useGlobal);
public:
    DirectRandom();
    [[nodiscard]] static bool sendOut(const DirectRandom& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(DirectRandom& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
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
