#pragma once
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>

namespace SGEXTN {
namespace Structs {
class Identifier;

class BUILDLAH_DLL_SGEXTN_Structs IdentifierRegistry{
public:
    IdentifierRegistry() = default;
    SGEXTN::Containers::UnorderedSet<unsigned int, SGEXTN::Containers::EqualTo<unsigned int>, SGEXTN::Containers::Hash<unsigned int>> private_contents;
    [[nodiscard]] SGEXTN::Structs::Identifier generateAndRegisterIdentifier();
    [[nodiscard]] SGEXTN::Structs::Identifier parseAndRegisterIdentifier(unsigned int data, bool* isValid);
    bool unregister(SGEXTN::Structs::Identifier id);
    [[nodiscard]] bool contains(SGEXTN::Structs::Identifier id) const;
};
}
}