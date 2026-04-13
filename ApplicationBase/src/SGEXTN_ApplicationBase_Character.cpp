#include <SGEXTN_ApplicationBase_Character.h>
#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Containers_Hash.h>

SGEXTN::ApplicationBase::Character::Character(){
    private_data.pushBack(0xE2);
    private_data.pushBack(0x99);
    private_data.pushBack(0xA5);
}

SGEXTN::ApplicationBase::Character::Character(char c){
    private_data.pushBack(c);
}

SGEXTN::ApplicationBase::Character::Character(int unicode){
    if(unicode < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor crashed because unicode is negative");}
    else if(unicode < 0x80){private_data.pushBack(static_cast<char>(unicode));}
    else if(unicode < 0x800){
        private_data.pushBack(static_cast<char>(0xc0 + (unicode >> 6)));
        private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
    else if(unicode < 0x10000){
        private_data.pushBack(static_cast<char>(0xe0 + (unicode >> 12)));
        private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 6) & 0x3f)));
        private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
    else if(unicode < 0x110000){
        private_data.pushBack(static_cast<char>(0xf0 + (unicode >> 18)));
        private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 12) & 0x3f)));
        private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 6) & 0x3f)));
        private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
    else{SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor crashed because unicode exceeds the largest possible code point");}
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
    //return (getBaseSimplifiedType() == SGEXTN::ApplicationBase::SimplifiedCharacterType::Whitespace);
}

int SGEXTN::ApplicationBase::Character::getUnicode() const {
    int unicode = 0;
    if(byteLength() == 1){unicode += static_cast<int>(byteAt(0));}
    else if(byteLength() == 2){
        unicode += (static_cast<int>(byteAt(0) & 0x1f) << 6);
        unicode += static_cast<int>(byteAt(1) & 0x3f);
    }
    else if(byteLength() == 3){
        unicode += (static_cast<int>(byteAt(0) & 0x0f) << 12);
        unicode += (static_cast<int>(byteAt(1) & 0x3f) << 6);
        unicode += static_cast<int>(byteAt(2) & 0x3f);
    }
    else{
        unicode += (static_cast<int>(byteAt(0) & 0x07) << 18);
        unicode += (static_cast<int>(byteAt(1) & 0x3f) << 12);
        unicode += (static_cast<int>(byteAt(2) & 0x3f) << 6);
        unicode += static_cast<int>(byteAt(3) & 0x3f);
    }
    return unicode;
}

bool SGEXTN::ApplicationBase::Character::isUppercase() const {
    //return (getBaseFullType() == SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter);
}

bool SGEXTN::ApplicationBase::Character::isLowercase() const {
    //return (getBaseFullType() == SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter);
}

bool SGEXTN::ApplicationBase::Character::isTitlecase() const {
    //return (getBaseFullType() == SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter);
}

bool SGEXTN::ApplicationBase::Character::isNormalised() const {
    //return ((*this) == getNormalised());
}
