#include <SGEXTN_Utilities_Identifier.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_ApplicationBase_String.h>

SGEXTN::Utilities::Identifier::Identifier() : private_data(0) {}

SGEXTN::Utilities::Identifier SGEXTN::Utilities::Identifier::nullIdentifier(){
    SGEXTN::Utilities::Identifier x;
    x.private_data = 0u;
    return x;
}

bool SGEXTN::Utilities::Identifier::operator==(SGEXTN::Utilities::Identifier x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::Utilities::Identifier::operator!=(SGEXTN::Utilities::Identifier x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::Utilities::Identifier::operator<(SGEXTN::Utilities::Identifier x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::Utilities::Identifier::operator>(SGEXTN::Utilities::Identifier x) const {
    return (private_data > x.private_data);
}

int SGEXTN::Utilities::Identifier::hash() const {
    return SGEXTN::Containers::Hash<unsigned int>()(private_data);
}

SGEXTN::ApplicationBase::String SGEXTN::Utilities::Identifier::getStringForPrinting() const {
    return SGEXTN::ApplicationBase::String::stringFromUnsignedInt(private_data, 16).fillLeftToByteLength(8, '0');
}

SGEXTN::ApplicationBase::String SGEXTN::Utilities::Identifier::debugLog() const {
    return getStringForPrinting();
}