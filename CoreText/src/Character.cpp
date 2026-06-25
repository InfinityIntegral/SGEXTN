/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#include <SGEXTN/CoreText/Character.h>
#include <SGEXTN/CoreText/private_api/TextBuffer.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Containers/Hash.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/CoreText/String.h>
#include <SGEXTN/CoreText/UnicodeQuery.h>
#include <SGEXTN/Containers/Vector.h>
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Containers/ArrayVectorMove.h>

namespace {
void appendUnicode(int unicode, SGEXTN::CoreText::Character& c){
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

int getCharacterDigitValue(const SGEXTN::CoreText::Character& c){
    if(c.isDigit() == true){return (static_cast<int>(c.byteAt(0)) - static_cast<int>('0'));}
    if(c.isEnglishLowercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('a'));}
    if(c.isEnglishUppercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('A'));}
    return -1;
}
}

SGEXTN::CoreText::Character::Character(){
    appendUnicode(0x1f496, (*this));
}

SGEXTN::CoreText::Character::Character(unsigned char c){
    if(c > 0x7f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String constructor crashed because the given unsigned char does not represent a valid ASCII character");}
    private_data.pushBack(c);
}

SGEXTN::CoreText::Character::Character(const char* s){
    const SGEXTN::CoreText::String validityTest(s);
    if(validityTest.characterLength() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character constructor crashed as passed string literal does not represent a single character");}
    private_data.pushBack(s);
}

SGEXTN::CoreText::Character::Character(int unicode){
    if(unicode < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character constructor crashed because unicode is negative");}
    else if(unicode > 0x10ffff){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character constructor crashed because unicode exceeds the largest possible code point");}
    appendUnicode(unicode, (*this));
}

bool SGEXTN::CoreText::Character::operator==(const SGEXTN::CoreText::Character& x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::CoreText::Character::operator!=(const SGEXTN::CoreText::Character& x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::CoreText::Character::operator<(const SGEXTN::CoreText::Character& x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::CoreText::Character::operator>(const SGEXTN::CoreText::Character& x) const {
    return (private_data > x.private_data);
}

bool SGEXTN::CoreText::Character::operator<=(const SGEXTN::CoreText::Character& x) const {
    return (private_data <= x.private_data);
}

bool SGEXTN::CoreText::Character::operator>=(const SGEXTN::CoreText::Character& x) const {
    return (private_data >= x.private_data);
}

int SGEXTN::CoreText::Character::hash() const {
    return SGEXTN::Containers::Hash<SGEXTN::CoreText::TextBuffer>()(private_data);
}

int SGEXTN::CoreText::Character::byteLength() const {
    return private_data.length();
}

unsigned char& SGEXTN::CoreText::Character::byteAt(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::byteAt crashed because the index points beyond the end of the character");}
    return private_data.byteAt(i);
}

const unsigned char& SGEXTN::CoreText::Character::byteAt(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::byteAt crashed because the index points beyond the end of the character");}
    return private_data.byteAt(i);
}

unsigned char SGEXTN::CoreText::Character::baseToAsciiChar() const {
    if(private_data.byteAt(0) > 0x7f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::baseToAsciiChar crashed because the first unsigned char in the grapheme cluster does not represent a valid ASCII character");}
    return private_data.byteAt(0);
}

bool SGEXTN::CoreText::Character::isDigit() const {
    if(byteLength() != 1){return false;}
    if((*this) >= '0' && (*this) <= '9'){return true;}
    return false;
}

bool SGEXTN::CoreText::Character::isDigit(int base) const {
    if(base < 2 || base > 36){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::isDigit crashed because base is not within 2 to 36 inclusive");}
    if(byteLength() != 1){return false;}
    const int d = getCharacterDigitValue(*this);
    if(d >= 0 && d < base){return true;}
    return false;
}

bool SGEXTN::CoreText::Character::isEnglishLowercase() const {
    if(byteLength() != 1){return false;}
    if((*this) >= 'a' && (*this) <= 'z'){return true;}
    return false;
}

bool SGEXTN::CoreText::Character::isEnglishUppercase() const {
    if(byteLength() != 1){return false;}
    if((*this) >= 'A' && (*this) <= 'Z'){return true;}
    return false;
}

bool SGEXTN::CoreText::Character::isEnglishLetter() const {
    return (isEnglishUppercase() || isEnglishLowercase());
}

bool SGEXTN::CoreText::Character::isEnglishAlphanumeric() const {
    return (isEnglishLetter() || isDigit());
}

bool SGEXTN::CoreText::Character::isASCII() const {
    if(byteLength() != 1){return false;}
    if(byteAt(0) < 128){return true;}
    return false;
}

bool SGEXTN::CoreText::Character::isWhitespace() const {
    if(byteLength() == 1){return SGEXTN::CoreText::UnicodeQuery::isWhitespace(static_cast<int>(byteAt(0)));}
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() != 1){return false;}
    return SGEXTN::CoreText::UnicodeQuery::isWhitespace(codePoints.at(0));
}

int SGEXTN::CoreText::Character::getBaseUnicode() const {
    if((byteAt(0) & 0x80) == 0){return static_cast<int>(byteAt(0));}
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() == 1){return codePoints.at(0);}
    for(int i=0; i<codePoints.length(); i++){
        const SGEXTN::CoreText::GraphemeSegmentationType graphemeCategory = SGEXTN::CoreText::UnicodeQuery::getGraphemeSegmentationType(codePoints.at(i));
        if(graphemeCategory == SGEXTN::CoreText::GraphemeSegmentationType::Other || graphemeCategory == SGEXTN::CoreText::GraphemeSegmentationType::RegionalIndicator || graphemeCategory == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeading || graphemeCategory == SGEXTN::CoreText::GraphemeSegmentationType::HangulVowel || graphemeCategory == SGEXTN::CoreText::GraphemeSegmentationType::HangulTrailing || graphemeCategory == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowel || graphemeCategory == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing){return codePoints.at(i);}
    }
    return codePoints.at(0);
}

SGEXTN::Containers::Array<int> SGEXTN::CoreText::Character::getUnicode() const {
    SGEXTN::Containers::Vector<int> output;
    int i = 0;
    while(i < byteLength()){
        if((byteAt(i) & 0x80) == 0){
            output.pushBack(static_cast<int>(byteAt(i)));
            i++;
        }
        else if((byteAt(i) & 0xE0) == 0xC0){
            if(i + 1 >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to incomplete 2 byte character");}
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x1f) << 6);
            if((byteAt(i + 1) & 0xC0) != 0x80){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to invalid continuation byte in 2 byte character");}
            unicode += static_cast<int>(byteAt(i + 1) & 0x3f);
            if(unicode < 0x80){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to 2 byte overlong character");}
            output.pushBack(unicode);
            i += 2;
        }
        else if((byteAt(i) & 0xF0) == 0xE0){
            if(i + 2 >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to incomplete 3 byte character");}
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x0f) << 12);
            if((byteAt(i + 1) & 0xC0) != 0x80){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to invalid first continuation byte in 3 byte character");}
            unicode += (static_cast<int>(byteAt(i + 1) & 0x3f) << 6);
            if((byteAt(i + 2) & 0xC0) != 0x80){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to invalid second continuation byte in 3 byte character");}
            unicode += static_cast<int>(byteAt(i + 2) & 0x3f);
            if(unicode < 0x800){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to 3 byte overlong character");}
            output.pushBack(unicode);
            i += 3;
        }
        else if((byteAt(i) & 0xF8) == 0xF0){
            if(i + 3 >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to incomplete 4 byte character");}
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x07) << 18);
            if((byteAt(i + 1) & 0xC0) != 0x80){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to invalid first continuation byte in 4 byte character");}
            unicode += (static_cast<int>(byteAt(i + 1) & 0x3f) << 12);
            if((byteAt(i + 2) & 0xC0) != 0x80){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to invalid second continuation byte in 4 byte character");}
            unicode += (static_cast<int>(byteAt(i + 2) & 0x3f) << 6);
            if((byteAt(i + 3) & 0xC0) != 0x80){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to invalid third continuation byte in 4 byte character");}
            unicode += static_cast<int>(byteAt(i + 3) & 0x3f);
            if(unicode < 0x10000){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to 4 byte overlong character");}
            if(unicode > 0x10ffff){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to 4 byte invalid character");}
            output.pushBack(unicode);
            i += 4;
        }
        else{SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::getUnicode crashed due to invalid character");}
    }
    return SGEXTN::Containers::ArrayVectorMove<int>::convertToArrayAndDestroyVector(output);
}

bool SGEXTN::CoreText::Character::isUppercase() const {
    return (SGEXTN::CoreText::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::CoreText::FullCharacterType::UppercaseLetter);
}

bool SGEXTN::CoreText::Character::isLowercase() const {
    return (SGEXTN::CoreText::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::CoreText::FullCharacterType::LowercaseLetter);
}

bool SGEXTN::CoreText::Character::isTitlecase() const {
    return (SGEXTN::CoreText::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::CoreText::FullCharacterType::TitlecaseLetter);
}

SGEXTN::CoreText::Character SGEXTN::CoreText::Character::getUppercase() const {
    if(byteLength() == 1){return SGEXTN::CoreText::Character(SGEXTN::CoreText::UnicodeQuery::getUppercase(static_cast<int>(byteAt(0))));}
    SGEXTN::CoreText::Character output;
    output.private_data = SGEXTN::CoreText::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(SGEXTN::CoreText::UnicodeQuery::getUppercase(unicode.at(i)), output);
    }
    return output;
}

SGEXTN::CoreText::Character SGEXTN::CoreText::Character::getLowercase() const {
    if(byteLength() == 1){return SGEXTN::CoreText::Character(SGEXTN::CoreText::UnicodeQuery::getLowercase(static_cast<int>(byteAt(0))));}
    SGEXTN::CoreText::Character output;
    output.private_data = SGEXTN::CoreText::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(SGEXTN::CoreText::UnicodeQuery::getLowercase(unicode.at(i)), output);
    }
    return output;
}

SGEXTN::CoreText::Character SGEXTN::CoreText::Character::getTitlecase() const {
    if(byteLength() == 1){return SGEXTN::CoreText::Character(SGEXTN::CoreText::UnicodeQuery::getTitlecase(static_cast<int>(byteAt(0))));}
    SGEXTN::CoreText::Character output;
    output.private_data = SGEXTN::CoreText::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(SGEXTN::CoreText::UnicodeQuery::getTitlecase(unicode.at(i)), output);
    }
    return output;
}

int SGEXTN::CoreText::Character::getDecimalDigitValue() const {
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() > 1){return -1;}
    return SGEXTN::CoreText::UnicodeQuery::getDecimalDigitValue(codePoints.at(0));
}

float SGEXTN::CoreText::Character::getNumericalValue() const {
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() > 1){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    return SGEXTN::CoreText::UnicodeQuery::getNumericalValue(codePoints.at(0));
}
