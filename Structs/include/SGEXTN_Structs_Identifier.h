#pragma once
#include <SGEXTN_ApplicationBase_String.h>

namespace SGEXTN {
namespace Structs {
class IdentifierRegistry;
class BUILDLAH_DLL_SGEXTN_Structs Identifier {
public:
    unsigned int private_data;
    Identifier() = default;
    static Identifier nullIdentifier();
    [[nodiscard]] bool operator==(Identifier x) const;
    [[nodiscard]] bool operator!=(Identifier x) const;
    [[nodiscard]] bool operator<(Identifier x) const;
    [[nodiscard]] bool operator>(Identifier x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String getStringForPrinting() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String debugLog() const;
};
}
}