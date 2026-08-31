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
template <typename T> class Span;
}

namespace SGEXTN::SeerattraNum {
class DirectRandom;

class BuildLah_SGEXTN_SeerattraNum DirectRandomInstanceLocator {
private:
    bool ownsRng_;
    SGEXTN::SeerattraNum::DirectRandom* rng_;
public:
    explicit DirectRandomInstanceLocator(bool useGlobal);
    explicit DirectRandomInstanceLocator(const SGEXTN::SeerattraNum::DirectRandom& rng);
    DirectRandomInstanceLocator(const DirectRandomInstanceLocator& x);
    DirectRandomInstanceLocator& operator=(const DirectRandomInstanceLocator& x);
    DirectRandomInstanceLocator(DirectRandomInstanceLocator&& x) noexcept;
    DirectRandomInstanceLocator& operator=(DirectRandomInstanceLocator&& x) noexcept;
    ~DirectRandomInstanceLocator();
    [[nodiscard]] static bool sendOut(const DirectRandomInstanceLocator& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(DirectRandomInstanceLocator& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
    [[nodiscard]] SGEXTN::SeerattraNum::DirectRandom& operator*();
    [[nodiscard]] const SGEXTN::SeerattraNum::DirectRandom& operator*() const;
    [[nodiscard]] bool isUsingGlobal() const;
};
}
