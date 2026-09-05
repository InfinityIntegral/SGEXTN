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

namespace SGEXTN::Containers {
template <typename T> class Span;
}

namespace SGEXTN::SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum SobolSequence {
private:
    int lastPosition_;
    SGEXTN::Containers::Array<unsigned int> lastPositionResult_;
    int dimensions_;
    SGEXTN::Containers::Array<unsigned int> hashedSeed_;
    SGEXTN::Containers::Array<SGEXTN::Containers::Array<unsigned int>> directionNumberCache_;
public:
    SobolSequence();
    explicit SobolSequence(int dimension);
    [[nodiscard]] static bool sendOut(const SobolSequence& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(SobolSequence& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(const SobolSequence& x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
    void seed(const SGEXTN::Containers::Array<unsigned int>& seedArray);
    [[nodiscard]] SGEXTN::Containers::Array<float> nextTerm();
    [[nodiscard]] SGEXTN::Containers::Array<float> requestTerm(int startingPoint);
};
}
