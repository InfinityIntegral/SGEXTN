#pragma once

namespace SGEXTN {
namespace ApplicationBase {
class String;
}

namespace Structs {
class IdentifierRegistry;
class BUILDLAH_DLL_SGEXTN_Structs Identifier {
public:
    unsigned int private_data;
    Identifier();
    [[nodiscard]] static Identifier nullIdentifier();
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