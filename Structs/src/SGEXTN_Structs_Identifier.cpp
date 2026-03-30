#include <SGEXTN_Structs_Identifier.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_ApplicationBase_String.h>

SGEXTN::Structs::Identifier::Identifier(){
    private_data = 0u;
}

SGEXTN::Structs::Identifier SGEXTN::Structs::Identifier::nullIdentifier(){
    SGEXTN::Structs::Identifier x;
    x.private_data = 0u;
    return x;
}

bool SGEXTN::Structs::Identifier::operator==(SGEXTN::Structs::Identifier x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::Structs::Identifier::operator!=(SGEXTN::Structs::Identifier x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::Structs::Identifier::operator<(SGEXTN::Structs::Identifier x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::Structs::Identifier::operator>(SGEXTN::Structs::Identifier x) const {
    return (private_data > x.private_data);
}

int SGEXTN::Structs::Identifier::hash() const {
    return SGEXTN::Containers::Hash<unsigned int>()(private_data);
}

SGEXTN::ApplicationBase::String SGEXTN::Structs::Identifier::getStringForPrinting() const {
    return SGEXTN::ApplicationBase::String::stringFromUnsignedInt(private_data, 16).fillLeftToLength(8, '0');
}

SGEXTN::ApplicationBase::String SGEXTN::Structs::Identifier::debugLog() const {
    return getStringForPrinting();
}