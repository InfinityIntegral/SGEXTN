#include "sgxchar.h"
#include <QChar>

SGXChar::SGXChar(char c){
    (*this).data = static_cast<unsigned short>(c);
}

SGXChar::SGXChar(unsigned short data){
    (*this).data = data;
}

SGXChar::SGXChar(int unicode){
    (*this).data = static_cast<unsigned short>(unicode);
}

SGXChar::operator char() const {
    return static_cast<char>(data);
}

bool SGXChar::operator==(SGXChar x) const {
    return (data == x.data);
}

bool SGXChar::operator==(char x) const {
    return (data == static_cast<unsigned short>(x));
}

bool SGXChar::operator!=(SGXChar x) const {
    return (data != x.data);
}

bool SGXChar::operator!=(char x) const {
    return (data != static_cast<unsigned short>(x));
}

bool SGXChar::operator<(SGXChar x) const {
    return (data < x.data);
}

bool SGXChar::operator<(char x) const {
    return (data < static_cast<unsigned short>(x));
}

bool SGXChar::operator>(SGXChar x) const {
    return (data > x.data);
}

bool SGXChar::operator>(char x) const {
    return (data > static_cast<unsigned short>(x));
}

bool SGXChar::operator<=(SGXChar x) const {
    return (data <= x.data);
}

bool SGXChar::operator<=(char x) const {
    return (data <= static_cast<unsigned short>(x));
}

bool SGXChar::operator>=(SGXChar x) const {
    return (data >= x.data);
}

bool SGXChar::operator>=(char x) const {
    return (data >= static_cast<unsigned short>(x));
}

bool SGXChar::isDigit() const {
    return ((*this) >= '0' && (*this) <= '9');
}

bool SGXChar::isDigitBase16() const {
    return (((*this) >= '0' && (*this) <= '9') || ((*this) >= 'a' && (*this) <= 'f') || ((*this) >= 'A' && (*this) <= 'F'));
}

bool SGXChar::isEnglishLowercase() const {
    return ((*this) >= 'a' && (*this) <= 'z');
}

bool SGXChar::isEnglishUppercase() const {
    return ((*this) >= 'A' && (*this) <= 'Z');
}

bool SGXChar::isEnglishLetter() const {
    return (((*this) >= 'a' && (*this) <= 'z') || ((*this) >= 'A' && (*this) <= 'Z'));
}

bool SGXChar::isEnglishAlphanumeric() const {
    return (((*this) >= '0' && (*this) <= '9') || ((*this) >= 'a' && (*this) <= 'z') || ((*this) >= 'A' && (*this) <= 'Z'));
}

bool SGXChar::isASCII() const {
    return (data < static_cast<unsigned short>(256));
}

bool SGXChar::isWhitespace() const {
    return (QChar(data).isSpace());
}

int SGXChar::getUnicode() const {
    return static_cast<int>(data);
}

SGXChar SGXChar::getUpperLanguageAware() const {
    return static_cast<unsigned short>(QChar(data).toUpper().unicode());
}

SGXChar SGXChar::getLowerLanguageAware() const {
    return static_cast<unsigned short>(QChar(data).toLower().unicode());
}

void SGXChar::toUpperLanguageAware(){
    data = static_cast<unsigned short>(QChar(data).toUpper().unicode());
}

void SGXChar::toLowerLanguageAware(){
    data = static_cast<unsigned short>(QChar(data).toLower().unicode());
}
