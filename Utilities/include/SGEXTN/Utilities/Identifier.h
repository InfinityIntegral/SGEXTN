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

namespace SGEXTN::SingText {
class String;
}

namespace SGEXTN::Utilities {
class IdentifierRegistry;

class BuildLah_SGEXTN_Utilities Identifier {
private:
    friend class SGEXTN::Utilities::IdentifierRegistry;
    unsigned int data_;
public:
    explicit Identifier();
    [[nodiscard]] static Identifier nullIdentifier();
    [[nodiscard]] bool operator==(Identifier x) const;
    [[nodiscard]] bool operator!=(Identifier x) const;
    [[nodiscard]] SGEXTN::SingText::String getStringForPrinting() const;
    [[nodiscard]] SGEXTN::SingText::String debugPrint() const;
    [[nodiscard]] static bool sendOut(Identifier x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(Identifier& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
};
}
