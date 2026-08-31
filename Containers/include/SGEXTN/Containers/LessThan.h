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
template <typename T> class LessThan {
private:
    mutable int lengthA_;
    mutable int lengthB_;
    mutable SGEXTN::Containers::Array<unsigned char> bufferA_;
    mutable SGEXTN::Containers::Array<unsigned char> bufferB_;
public:
    explicit LessThan();
    LessThan(const LessThan& x);
    LessThan& operator=(const LessThan& x);
    LessThan(LessThan&& x) noexcept;
    LessThan& operator=(LessThan&& x) noexcept;
    ~LessThan();
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};
}

#include <SGEXTN/Containers/private_api/LessThan_impl.h>
