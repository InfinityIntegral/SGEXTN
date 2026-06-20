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
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>

namespace SGEXTN {
namespace Utilities {
class Identifier;

class BuildLah_SGEXTN_Utilities IdentifierRegistry{
public:
    IdentifierRegistry() = default;
    SGEXTN::Containers::UnorderedSet<unsigned int, SGEXTN::Containers::EqualTo<unsigned int>, SGEXTN::Containers::Hash<unsigned int>> private_contents;
    [[nodiscard]] SGEXTN::Utilities::Identifier generateAndRegisterIdentifier();
    [[nodiscard]] SGEXTN::Utilities::Identifier parseAndRegisterIdentifier(unsigned int data, bool* isValid);
    bool unregister(SGEXTN::Utilities::Identifier id);
    [[nodiscard]] bool contains(SGEXTN::Utilities::Identifier id) const;
    [[nodiscard]] int length() const;
};
}
}
