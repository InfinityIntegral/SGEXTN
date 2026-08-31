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
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/CoreText/String.h>
#include <SGEXTN/CoreText/UnicodeQuery.h>
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Containers/ArrayVectorMove.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

namespace {
int getCharacterDigitValue(const SGEXTN::CoreText::Character& c){
    if(c.isDigit() == true){return (static_cast<int>(c.byteAt(0)) - static_cast<int>('0'));}
    if(c.isEnglishLowercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('a'));}
    if(c.isEnglishUppercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('A'));}
    return -1;
}
}

SGEXTN::CoreText::Character::Character(){
    data_ = SGEXTN::CoreText::String::stringFromUnicode(0x1f496);
}

SGEXTN::CoreText::Character::Character(unsigned char c){
    if(c > 0x7f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String constructor crashed because the given unsigned char does not represent a valid ASCII character");}
    data_ += c;
}

SGEXTN::CoreText::Character::Character(const char* s){
    const SGEXTN::CoreText::String validityTest(s);
    if(validityTest.characterLength() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character constructor crashed as passed string literal does not represent a single character");}
    data_ += s;
}

SGEXTN::CoreText::Character::Character(int unicode){
    if(unicode < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character constructor crashed because unicode is negative");}
    else if(unicode > 0x10ffff){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character constructor crashed because unicode exceeds the largest possible code point");}
    data_ = SGEXTN::CoreText::String::stringFromUnicode(unicode);
}

bool SGEXTN::CoreText::Character::operator==(const SGEXTN::CoreText::Character& x) const {
    return (data_ == x.data_);
}

bool SGEXTN::CoreText::Character::operator!=(const SGEXTN::CoreText::Character& x) const {
    return (data_ != x.data_);
}

bool SGEXTN::CoreText::Character::operator<(const SGEXTN::CoreText::Character& x) const {
    return (data_ < x.data_);
}

bool SGEXTN::CoreText::Character::operator>(const SGEXTN::CoreText::Character& x) const {
    return (data_ > x.data_);
}

bool SGEXTN::CoreText::Character::operator<=(const SGEXTN::CoreText::Character& x) const {
    return (data_ <= x.data_);
}

bool SGEXTN::CoreText::Character::operator>=(const SGEXTN::CoreText::Character& x) const {
    return (data_ >= x.data_);
}

bool SGEXTN::CoreText::Character::sendOut(const SGEXTN::CoreText::Character& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::CoreText::String>::sendOut(x.data_, data);
}

bool SGEXTN::CoreText::Character::sendIn(SGEXTN::CoreText::Character& x, SGEXTN::Containers::Span<unsigned char> data){
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::CoreText::String>::sendIn(x.data_, data);
    if(isValid == false || x.data_.characterLength() != 1){return false;}
    return true;
}

int SGEXTN::CoreText::Character::sizeOut(const SGEXTN::CoreText::Character& x){
    return SGEXTN::Containers::Serialise<SGEXTN::CoreText::String>::sizeOut(x.data_);
}

int SGEXTN::CoreText::Character::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::CoreText::String>::sizeIn(data);
}

int SGEXTN::CoreText::Character::byteLength() const {
    return data_.byteLength();
}

unsigned char& SGEXTN::CoreText::Character::byteAt(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::byteAt crashed because the index points beyond the end of the character");}
    return data_.byteAt(i);
}

const unsigned char& SGEXTN::CoreText::Character::byteAt(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::byteAt crashed because the index points beyond the end of the character");}
    return data_.byteAt(i);
}

unsigned char SGEXTN::CoreText::Character::baseToAsciiChar() const {
    if(data_.byteAt(0) > 0x7f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character::baseToAsciiChar crashed because the first unsigned char in the grapheme cluster does not represent a valid ASCII character");}
    return data_.byteAt(0);
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
    return data_.getUnicode();
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
    output.data_ = "";
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        output.data_ += SGEXTN::CoreText::String::stringFromUnicode(SGEXTN::CoreText::UnicodeQuery::getUppercase(unicode.at(i)));
    }
    return output;
}

SGEXTN::CoreText::Character SGEXTN::CoreText::Character::getLowercase() const {
    if(byteLength() == 1){return SGEXTN::CoreText::Character(SGEXTN::CoreText::UnicodeQuery::getLowercase(static_cast<int>(byteAt(0))));}
    SGEXTN::CoreText::Character output;
    output.data_ = "";
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        output.data_ += SGEXTN::CoreText::String::stringFromUnicode(SGEXTN::CoreText::UnicodeQuery::getLowercase(unicode.at(i)));
    }
    return output;
}

SGEXTN::CoreText::Character SGEXTN::CoreText::Character::getTitlecase() const {
    if(byteLength() == 1){return SGEXTN::CoreText::Character(SGEXTN::CoreText::UnicodeQuery::getTitlecase(static_cast<int>(byteAt(0))));}
    SGEXTN::CoreText::Character output;
    output.data_ = "";
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        output.data_ += SGEXTN::CoreText::String::stringFromUnicode(SGEXTN::CoreText::UnicodeQuery::getTitlecase(unicode.at(i)));
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
