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
#include <SGEXTN/SingEmbed/private_api/EmbeddedFile.h>

namespace SGEXTN {
namespace CoreText {
class String;
}

namespace Containers {
template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMap;
template <typename T> class EqualTo;
template <typename... Ts> class Hash;
}

namespace SingEmbed {
class BuildLah_SGEXTN_SingEmbed SingEmbedFileRegistrarInstance {
public:
    static SGEXTN::Containers::UnorderedMap<SGEXTN::CoreText::String, SGEXTN::SingEmbed::EmbeddedFile, SGEXTN::Containers::EqualTo<SGEXTN::CoreText::String>, SGEXTN::Containers::Hash<SGEXTN::CoreText::String>>* registry;
    SingEmbedFileRegistrarInstance(const SGEXTN::CoreText::String& virtualPath, int fileSize, const char* data);
};
}
}
