#include <SGEXTN_ApplicationBase_OldChar.h>
#include <QChar>
#include <SGEXTN_Containers_Hash.h>
#include <private_api/SGEXTN_Containers_Crash.h>

SGEXTN::ApplicationBase::OldChar::OldChar(){
    (*this).private_data = static_cast<unsigned short>(0);
}

SGEXTN::ApplicationBase::OldChar::OldChar(char c){
    (*this).private_data = static_cast<unsigned short>(static_cast<unsigned char>(c));
}

SGEXTN::ApplicationBase::OldChar::OldChar(unsigned short data){
    (*this).private_data = data;
}

SGEXTN::ApplicationBase::OldChar::OldChar(int unicode){
    if(unicode < 0 || unicode > 65535){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar constructor crashed because unicode value used is not between 0 and 65535 inclusive");}
    (*this).private_data = static_cast<unsigned short>(unicode);
}

char SGEXTN::ApplicationBase::OldChar::toChar() const {
    return static_cast<char>(private_data);
}

signed char SGEXTN::ApplicationBase::OldChar::toSignedChar() const {
    return static_cast<signed char>(private_data);
}

unsigned char SGEXTN::ApplicationBase::OldChar::toUnsignedChar() const {
    return static_cast<unsigned char>(private_data);
}

bool SGEXTN::ApplicationBase::OldChar::operator==(SGEXTN::ApplicationBase::OldChar x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::ApplicationBase::OldChar::operator!=(SGEXTN::ApplicationBase::OldChar x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::ApplicationBase::OldChar::operator<(SGEXTN::ApplicationBase::OldChar x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::ApplicationBase::OldChar::operator>(SGEXTN::ApplicationBase::OldChar x) const {
    return (private_data > x.private_data);
}

bool SGEXTN::ApplicationBase::OldChar::operator<=(SGEXTN::ApplicationBase::OldChar x) const {
    return (private_data <= x.private_data);
}

bool SGEXTN::ApplicationBase::OldChar::operator>=(SGEXTN::ApplicationBase::OldChar x) const {
    return (private_data >= x.private_data);
}

int SGEXTN::ApplicationBase::OldChar::hash() const {
    return SGEXTN::Containers::Hash<unsigned short>()(private_data);
}

bool SGEXTN::ApplicationBase::OldChar::isDigit() const {
    return ((*this) >= '0' && (*this) <= '9');
}

bool SGEXTN::ApplicationBase::OldChar::isDigitBase16() const {
    return (((*this) >= '0' && (*this) <= '9') || ((*this) >= 'a' && (*this) <= 'f') || ((*this) >= 'A' && (*this) <= 'F'));
}

bool SGEXTN::ApplicationBase::OldChar::isEnglishLowercase() const {
    return ((*this) >= 'a' && (*this) <= 'z');
}

bool SGEXTN::ApplicationBase::OldChar::isEnglishUppercase() const {
    return ((*this) >= 'A' && (*this) <= 'Z');
}

bool SGEXTN::ApplicationBase::OldChar::isEnglishLetter() const {
    return (((*this) >= 'a' && (*this) <= 'z') || ((*this) >= 'A' && (*this) <= 'Z'));
}

bool SGEXTN::ApplicationBase::OldChar::isEnglishAlphanumeric() const {
    return (((*this) >= '0' && (*this) <= '9') || ((*this) >= 'a' && (*this) <= 'z') || ((*this) >= 'A' && (*this) <= 'Z'));
}

bool SGEXTN::ApplicationBase::OldChar::isASCII() const {
    return (private_data < static_cast<unsigned short>(128u));
}

bool SGEXTN::ApplicationBase::OldChar::isWhitespace() const {
    return (QChar(private_data).isSpace());
}

int SGEXTN::ApplicationBase::OldChar::getUnicode() const {
    return static_cast<int>(private_data);
}

SGEXTN::ApplicationBase::OldChar SGEXTN::ApplicationBase::OldChar::uppercaseLanguageAware() const {
    return SGEXTN::ApplicationBase::OldChar(static_cast<unsigned short>(QChar(private_data).toUpper().unicode()));
}

SGEXTN::ApplicationBase::OldChar SGEXTN::ApplicationBase::OldChar::lowercaseLanguageAware() const {
    return SGEXTN::ApplicationBase::OldChar(static_cast<unsigned short>(QChar(private_data).toLower().unicode()));
}
