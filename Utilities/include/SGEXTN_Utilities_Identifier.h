#pragma once

namespace SGEXTN {
namespace CoreText {
class String;
}

namespace Utilities {
class IdentifierRegistry;
class BuildLah_SGEXTN_Utilities Identifier {
public:
    unsigned int private_data;
    Identifier();
    [[nodiscard]] static Identifier nullIdentifier();
    [[nodiscard]] bool operator==(Identifier x) const;
    [[nodiscard]] bool operator!=(Identifier x) const;
    [[nodiscard]] bool operator<(Identifier x) const;
    [[nodiscard]] bool operator>(Identifier x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGEXTN::CoreText::String getStringForPrinting() const;
    [[nodiscard]] SGEXTN::CoreText::String debugPrint() const;
};
}
}
