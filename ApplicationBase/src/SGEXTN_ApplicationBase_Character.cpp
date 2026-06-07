#include <SGEXTN_ApplicationBase_Character.h>
#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_ApplicationBase_UnicodeQuery.h>
#include <SGEXTN_Containers_Vector.h>
#include <SGEXTN_Math_FloatLimits.h>
#include <SGEXTN_Containers_ArrayVectorMove.h>

namespace {
void appendUnicode(int unicode, SGEXTN::ApplicationBase::Character& c){
    if(unicode < 0x80){c.private_data.pushBack(static_cast<unsigned char>(unicode));}
    else if(unicode < 0x800){
        c.private_data.pushBack(static_cast<unsigned char>(0xc0 + (unicode >> 6)));
        c.private_data.pushBack(static_cast<unsigned char>(0x80 + (unicode & 0x3f)));
    }
    else if(unicode < 0x10000){
        c.private_data.pushBack(static_cast<unsigned char>(0xe0 + (unicode >> 12)));
        c.private_data.pushBack(static_cast<unsigned char>(0x80 + ((unicode >> 6) & 0x3f)));
        c.private_data.pushBack(static_cast<unsigned char>(0x80 + (unicode & 0x3f)));
    }
    else if(unicode < 0x110000){
        c.private_data.pushBack(static_cast<unsigned char>(0xf0 + (unicode >> 18)));
        c.private_data.pushBack(static_cast<unsigned char>(0x80 + ((unicode >> 12) & 0x3f)));
        c.private_data.pushBack(static_cast<unsigned char>(0x80 + ((unicode >> 6) & 0x3f)));
        c.private_data.pushBack(static_cast<unsigned char>(0x80 + (unicode & 0x3f)));
    }
}

int getCharacterDigitValue(const SGEXTN::ApplicationBase::Character& c){
    if(c.isDigit() == true){return (static_cast<int>(c.byteAt(0)) - static_cast<int>('0'));}
    if(c.isEnglishLowercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('a'));}
    if(c.isEnglishUppercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('A'));}
    return -1;
}
}

SGEXTN::ApplicationBase::Character::Character(){
    private_data.pushBack(static_cast<unsigned char>(0xE2));
    private_data.pushBack(static_cast<unsigned char>(0x99));
    private_data.pushBack(static_cast<unsigned char>(0xA5));
}

SGEXTN::ApplicationBase::Character::Character(unsigned char c){
    if(c > 0x7f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String constructor crashed because the given unsigned char does not represent a valid ASCII character");}
    private_data.pushBack(c);
}

SGEXTN::ApplicationBase::Character::Character(const char* s){
    const SGEXTN::ApplicationBase::String validityTest(s);
    if(validityTest.characterLength() != 1){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor crashed as passed string literal does not represent a single character");}
    private_data.pushBack(s);
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

unsigned char SGEXTN::ApplicationBase::Character::baseToAsciiChar() const {
    if(private_data.byteAt(0) > 0x7f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::baseToAsciiChar crashed because the first unsigned char in the grapheme cluster does not represent a valid ASCII character");}
    return private_data.byteAt(0);
}

bool SGEXTN::ApplicationBase::Character::isDigit() const {
    if(byteLength() != 1){return false;}
    if((*this) >= '0' && (*this) <= '9'){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isDigit(int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::isDigit crashed because base is not within 2 to 36 inclusive");}
    if(byteLength() != 1){return false;}
    const int d = getCharacterDigitValue(*this);
    if(d >= 0 && d < base){return true;}
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
    if(byteLength() == 1){return SGEXTN::ApplicationBase::UnicodeQuery::isWhitespace(static_cast<int>(byteAt(0)));}
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() != 1){return false;}
    return SGEXTN::ApplicationBase::UnicodeQuery::isWhitespace(codePoints.at(0));
}

int SGEXTN::ApplicationBase::Character::getBaseUnicode() const {
    if((byteAt(0) & 0x80) == 0){return static_cast<int>(byteAt(0));}
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() == 1){return codePoints.at(0);}
    for(int i=0; i<codePoints.length(); i++){
        const SGEXTN::ApplicationBase::GraphemeSegmentationType graphemeCategory = SGEXTN::ApplicationBase::UnicodeQuery::getGraphemeSegmentationType(codePoints.at(i));
        if(graphemeCategory == SGEXTN::ApplicationBase::GraphemeSegmentationType::Other || graphemeCategory == SGEXTN::ApplicationBase::GraphemeSegmentationType::RegionalIndicator || graphemeCategory == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeading || graphemeCategory == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulVowel || graphemeCategory == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulTrailing || graphemeCategory == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeadingAndVowel || graphemeCategory == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing){return codePoints.at(i);}
    }
    return codePoints.at(0);
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
            if(i + 1 >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to incomplete 2 byte character");}
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x1f) << 6);
            if((byteAt(i + 1) & 0xC0) != 0x80){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to invalid continuation byte in 2 byte character");}
            unicode += static_cast<int>(byteAt(i + 1) & 0x3f);
            if(unicode < 0x80){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to 2 byte overlong character");}
            output.pushBack(unicode);
            i += 2;
        }
        else if((byteAt(i) & 0xF0) == 0xE0){
            if(i + 2 >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to incomplete 3 byte character");}
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x0f) << 12);
            if((byteAt(i + 1) & 0xC0) != 0x80){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to invalid first continuation byte in 3 byte character");}
            unicode += (static_cast<int>(byteAt(i + 1) & 0x3f) << 6);
            if((byteAt(i + 2) & 0xC0) != 0x80){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to invalid second continuation byte in 3 byte character");}
            unicode += static_cast<int>(byteAt(i + 2) & 0x3f);
            if(unicode < 0x800){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to 3 byte overlong character");}
            output.pushBack(unicode);
            i += 3;
        }
        else if((byteAt(i) & 0xF8) == 0xF0){
            if(i + 3 >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to incomplete 4 byte character");}
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x07) << 18);
            if((byteAt(i + 1) & 0xC0) != 0x80){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to invalid first continuation byte in 4 byte character");}
            unicode += (static_cast<int>(byteAt(i + 1) & 0x3f) << 12);
            if((byteAt(i + 2) & 0xC0) != 0x80){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to invalid second continuation byte in 4 byte character");}
            unicode += (static_cast<int>(byteAt(i + 2) & 0x3f) << 6);
            if((byteAt(i + 3) & 0xC0) != 0x80){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to invalid third continuation byte in 4 byte character");}
            unicode += static_cast<int>(byteAt(i + 3) & 0x3f);
            if(unicode < 0x10000){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to 4 byte overlong character");}
            if(unicode > 0x10ffff){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to 4 byte invalid character");}
            output.pushBack(unicode);
            i += 4;
        }
        else{SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::getUnicode crashed due to invalid character");}
    }
    return SGEXTN::Containers::ArrayVectorMove<int>::convertToArrayAndDestroyVector(output);
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
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() > 1){return -1;}
    return SGEXTN::ApplicationBase::UnicodeQuery::getDecimalDigitValue(codePoints.at(0));
}

float SGEXTN::ApplicationBase::Character::getNumericalValue() const {
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() > 1){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    return SGEXTN::ApplicationBase::UnicodeQuery::getNumericalValue(codePoints.at(0));
}