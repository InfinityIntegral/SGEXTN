#include <SGEXTN_ApplicationBase_Character.h>
#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_ApplicationBase_UnicodeQuery.h>
#include <SGEXTN_Containers_Vector.h>

namespace {
void appendUnicode(int unicode, SGEXTN::ApplicationBase::Character& c){
    if(unicode < 0x80){c.private_data.pushBack(static_cast<char>(unicode));}
    else if(unicode < 0x800){
        c.private_data.pushBack(static_cast<char>(0xc0 + (unicode >> 6)));
        c.private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
    else if(unicode < 0x10000){
        c.private_data.pushBack(static_cast<char>(0xe0 + (unicode >> 12)));
        c.private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 6) & 0x3f)));
        c.private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
    else if(unicode < 0x110000){
        c.private_data.pushBack(static_cast<char>(0xf0 + (unicode >> 18)));
        c.private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 12) & 0x3f)));
        c.private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 6) & 0x3f)));
        c.private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
}
}

SGEXTN::ApplicationBase::Character::Character(){
    private_data.pushBack(static_cast<char>(0xE2));
    private_data.pushBack(static_cast<char>(0x99));
    private_data.pushBack(static_cast<char>(0xA5));
}

SGEXTN::ApplicationBase::Character::Character(char c){
    private_data.pushBack(c);
}

SGEXTN::ApplicationBase::Character::Character(int unicode){
    if(unicode < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor crashed because unicode is negative");}
    else if(unicode > 0x10ffff){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor crashed because unicode exceeds the largest possible code point");}
    appendUnicode(unicode, (*this));
}

bool SGEXTN::ApplicationBase::Character::operator==(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator!=(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator<(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator>(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data > x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator<=(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data <= x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator>=(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data >= x.private_data);
}

int SGEXTN::ApplicationBase::Character::hash() const {
    return SGEXTN::Containers::Hash<SGEXTN::ApplicationBase::TextBuffer>()(private_data);
}

int SGEXTN::ApplicationBase::Character::byteLength() const {
    return private_data.length();
}

unsigned char& SGEXTN::ApplicationBase::Character::byteAt(int i){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::byteAt crashed because the index points beyond the end of the character");}
    return private_data.byteAt(i);
}

const unsigned char& SGEXTN::ApplicationBase::Character::byteAt(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::byteAt crashed because the index points beyond the end of the character");}
    return private_data.byteAt(i);
}

char SGEXTN::ApplicationBase::Character::baseToChar() const {
    return static_cast<char>(private_data.byteAt(0));
}

bool SGEXTN::ApplicationBase::Character::isDigit() const {
    if(byteLength() != 1){return false;}
    if((*this) >= '0' && (*this) <= '9'){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isEnglishLowercase() const {
    if(byteLength() != 1){return false;}
    if((*this) >= 'a' && (*this) <= 'z'){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isEnglishUppercase() const {
    if(byteLength() != 1){return false;}
    if((*this) >= 'A' && (*this) <= 'Z'){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isEnglishLetter() const {
    return (isEnglishUppercase() || isEnglishLowercase());
}

bool SGEXTN::ApplicationBase::Character::isEnglishAlphanumeric() const {
    return (isEnglishLetter() || isDigit());
}

bool SGEXTN::ApplicationBase::Character::isASCII() const {
    if(byteLength() != 1){return false;}
    if(byteAt(0) < 128){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isWhitespace() const {
    return (SGEXTN::ApplicationBase::UnicodeQuery::getSimplifiedType(getBaseUnicode()) == SGEXTN::ApplicationBase::SimplifiedCharacterType::Whitespace);
}

int SGEXTN::ApplicationBase::Character::getBaseUnicode() const {
    if((byteAt(0) & 0x80) == 0){return static_cast<int>(byteAt(0));}
    if((byteAt(0) & 0xE0) == 0xC0){
        int unicode = 0;
        unicode += (static_cast<int>(byteAt(0) & 0x1f) << 6);
        unicode += static_cast<int>(byteAt(1) & 0x3f);
        return unicode;
    }
    if((byteAt(0) & 0xF0) == 0xE0){
        int unicode = 0;
        unicode += (static_cast<int>(byteAt(0) & 0x0f) << 12);
        unicode += (static_cast<int>(byteAt(1) & 0x3f) << 6);
        unicode += static_cast<int>(byteAt(2) & 0x3f);
        return unicode;
    }
    {
        int unicode = 0;
        unicode += (static_cast<int>(byteAt(0) & 0x07) << 18);
        unicode += (static_cast<int>(byteAt(1) & 0x3f) << 12);
        unicode += (static_cast<int>(byteAt(2) & 0x3f) << 6);
        unicode += static_cast<int>(byteAt(3) & 0x3f);
        return unicode;
    }
}

SGEXTN::Containers::Array<int> SGEXTN::ApplicationBase::Character::getUnicode() const {
    SGEXTN::Containers::Vector<int> output;
    int i = 0;
    while(i < byteLength()){
        if((byteAt(i) & 0x80) == 0){
            output.pushBack(static_cast<int>(byteAt(i)));
            i++;
        }
        else if((byteAt(i) & 0xE0) == 0xC0){
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x1f) << 6);
            unicode += static_cast<int>(byteAt(i + 1) & 0x3f);
            output.pushBack(unicode);
            i += 2;
        }
        else if((byteAt(i) & 0xF0) == 0xE0){
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x0f) << 12);
            unicode += (static_cast<int>(byteAt(i + 1) & 0x3f) << 6);
            unicode += static_cast<int>(byteAt(i + 2) & 0x3f);
            output.pushBack(unicode);
            i += 3;
        }
        else{
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x07) << 18);
            unicode += (static_cast<int>(byteAt(i + 1) & 0x3f) << 12);
            unicode += (static_cast<int>(byteAt(i + 2) & 0x3f) << 6);
            unicode += static_cast<int>(byteAt(i + 3) & 0x3f);
            output.pushBack(unicode);
            i += 4;
        }
    }
    SGEXTN::Containers::Array<int> outputArray(output.length());
    for(int j=0; j<output.length(); j++){
        outputArray.at(j) = output.at(j);
    }
    return outputArray;
}

bool SGEXTN::ApplicationBase::Character::isUppercase() const {
    return (SGEXTN::ApplicationBase::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter);
}

bool SGEXTN::ApplicationBase::Character::isLowercase() const {
    return (SGEXTN::ApplicationBase::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter);
}

bool SGEXTN::ApplicationBase::Character::isTitlecase() const {
    return (SGEXTN::ApplicationBase::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter);
}

SGEXTN::ApplicationBase::Character SGEXTN::ApplicationBase::Character::getUppercase() const {
    if(byteLength() == 1){return SGEXTN::ApplicationBase::Character(SGEXTN::ApplicationBase::UnicodeQuery::getUppercase(static_cast<int>(byteAt(0))));}
    SGEXTN::ApplicationBase::Character output;
    output.private_data = SGEXTN::ApplicationBase::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(SGEXTN::ApplicationBase::UnicodeQuery::getUppercase(unicode.at(i)), output);
    }
    return output;
}

SGEXTN::ApplicationBase::Character SGEXTN::ApplicationBase::Character::getLowercase() const {
    if(byteLength() == 1){return SGEXTN::ApplicationBase::Character(SGEXTN::ApplicationBase::UnicodeQuery::getLowercase(static_cast<int>(byteAt(0))));}
    SGEXTN::ApplicationBase::Character output;
    output.private_data = SGEXTN::ApplicationBase::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(SGEXTN::ApplicationBase::UnicodeQuery::getLowercase(unicode.at(i)), output);
    }
    return output;
}

SGEXTN::ApplicationBase::Character SGEXTN::ApplicationBase::Character::getTitlecase() const {
    if(byteLength() == 1){return SGEXTN::ApplicationBase::Character(SGEXTN::ApplicationBase::UnicodeQuery::getTitlecase(static_cast<int>(byteAt(0))));}
    SGEXTN::ApplicationBase::Character output;
    output.private_data = SGEXTN::ApplicationBase::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(SGEXTN::ApplicationBase::UnicodeQuery::getTitlecase(unicode.at(i)), output);
    }
    return output;
}

int SGEXTN::ApplicationBase::Character::getDecimalDigitValue() const {
    return SGEXTN::ApplicationBase::UnicodeQuery::getDecimalDigitValue(getBaseUnicode());
}

float SGEXTN::ApplicationBase::Character::getNumericalValue() const {
    return SGEXTN::ApplicationBase::UnicodeQuery::getNumericalValue(getBaseUnicode());
}