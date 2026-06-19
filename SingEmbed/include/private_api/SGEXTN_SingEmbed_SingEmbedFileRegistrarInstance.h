#pragma once
#include <private_api/SGEXTN_SingEmbed_EmbeddedFile.h>

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
