#pragma once
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>

namespace SGEXTN {
namespace Utilities {
class Identifier;

class BUILDLAH_DLL_SGEXTN_Utilities IdentifierRegistry{
public:
    IdentifierRegistry() = default;
    SGEXTN::Containers::UnorderedSet<unsigned int, SGEXTN::Containers::EqualTo<unsigned int>, SGEXTN::Containers::Hash<unsigned int>> private_contents;
    [[nodiscard]] SGEXTN::Utilities::Identifier generateAndRegisterIdentifier();
    [[nodiscard]] SGEXTN::Utilities::Identifier parseAndRegisterIdentifier(unsigned int data, bool* isValid);
    bool unregister(SGEXTN::Utilities::Identifier id);
    [[nodiscard]] bool contains(SGEXTN::Utilities::Identifier id) const;
};
}
}