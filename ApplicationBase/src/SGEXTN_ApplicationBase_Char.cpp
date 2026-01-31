#include <SGEXTN_ApplicationBase_Char.h>
#include <QChar>
#include <SGEXTN_Containers_Hash.h>
#include <private_api/SGEXTN_Containers_Crash.h>

SGEXTN::ApplicationBase::Char::Char(char c){
    (*this).private_data = static_cast<unsigned short>(c);
}

SGEXTN::ApplicationBase::Char::Char(unsigned short data){
    (*this).private_data = data;
}

SGEXTN::ApplicationBase::Char::Char(int unicode){
    if(unicode < 0 || unicode > 65535){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char constructor crashed because unicode value used is not between 0 and 65535 inclusive");}
    (*this).private_data = static_cast<unsigned short>(unicode);
}

char SGEXTN::ApplicationBase::Char::toChar() const {
    return static_cast<char>(private_data);
}

signed char SGEXTN::ApplicationBase::Char::toSignedChar() const {
    return static_cast<signed char>(private_data);
}

unsigned char SGEXTN::ApplicationBase::Char::toUnsignedChar() const {
    return static_cast<unsigned char>(private_data);
}

bool SGEXTN::ApplicationBase::Char::operator==(SGEXTN::ApplicationBase::Char x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::ApplicationBase::Char::operator!=(SGEXTN::ApplicationBase::Char x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::ApplicationBase::Char::operator<(SGEXTN::ApplicationBase::Char x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::ApplicationBase::Char::operator>(SGEXTN::ApplicationBase::Char x) const {
    return (private_data > x.private_data);
}

bool SGEXTN::ApplicationBase::Char::operator<=(SGEXTN::ApplicationBase::Char x) const {
    return (private_data <= x.private_data);
}

bool SGEXTN::ApplicationBase::Char::operator>=(SGEXTN::ApplicationBase::Char x) const {
    return (private_data >= x.private_data);
}

int SGEXTN::ApplicationBase::Char::hash() const {
    return SGEXTN::Containers::Hash<unsigned short>()(private_data);
}

bool SGEXTN::ApplicationBase::Char::isDigit() const {
    return ((*this) >= '0' && (*this) <= '9');
}

bool SGEXTN::ApplicationBase::Char::isDigitBase16() const {
    return (((*this) >= '0' && (*this) <= '9') || ((*this) >= 'a' && (*this) <= 'f') || ((*this) >= 'A' && (*this) <= 'F'));
}

bool SGEXTN::ApplicationBase::Char::isEnglishLowercase() const {
    return ((*this) >= 'a' && (*this) <= 'z');
}

bool SGEXTN::ApplicationBase::Char::isEnglishUppercase() const {
    return ((*this) >= 'A' && (*this) <= 'Z');
}

bool SGEXTN::ApplicationBase::Char::isEnglishLetter() const {
    return (((*this) >= 'a' && (*this) <= 'z') || ((*this) >= 'A' && (*this) <= 'Z'));
}

bool SGEXTN::ApplicationBase::Char::isEnglishAlphanumeric() const {
    return (((*this) >= '0' && (*this) <= '9') || ((*this) >= 'a' && (*this) <= 'z') || ((*this) >= 'A' && (*this) <= 'Z'));
}

bool SGEXTN::ApplicationBase::Char::isASCII() const {
    return (private_data < static_cast<unsigned short>(128u));
}

bool SGEXTN::ApplicationBase::Char::isWhitespace() const {
    return (QChar(private_data).isSpace());
}

int SGEXTN::ApplicationBase::Char::getUnicode() const {
    return static_cast<int>(private_data);
}

SGEXTN::ApplicationBase::Char SGEXTN::ApplicationBase::Char::uppercaseLanguageAware() const {
    return SGEXTN::ApplicationBase::Char(static_cast<unsigned short>(QChar(private_data).toUpper().unicode()));
}

SGEXTN::ApplicationBase::Char SGEXTN::ApplicationBase::Char::lowercaseLanguageAware() const {
    return SGEXTN::ApplicationBase::Char(static_cast<unsigned short>(QChar(private_data).toLower().unicode()));
}
