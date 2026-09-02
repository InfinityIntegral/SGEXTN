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

#include <SGEXTN/SingText/Character.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/SingText/String.h>
#include <SGEXTN/SingText/UnicodeQuery.h>
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Containers/ArrayVectorMove.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

namespace {
int getCharacterDigitValue(const SGEXTN::SingText::Character& c){
    if(c.isDigit() == true){return (static_cast<int>(c.byteAt(0)) - static_cast<int>('0'));}
    if(c.isEnglishLowercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('a'));}
    if(c.isEnglishUppercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('A'));}
    return -1;
}
}

SGEXTN::SingText::Character::Character(){
    data_ = SGEXTN::SingText::String::stringFromUnicode(0x1f496);
}

SGEXTN::SingText::Character::Character(unsigned char c){
    if(c > 0x7f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String constructor crashed because the given unsigned char does not represent a valid ASCII character");}
    data_ += c;
}

SGEXTN::SingText::Character::Character(const char* s){
    const SGEXTN::SingText::String validityTest(s);
    if(validityTest.characterLength() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character constructor crashed as passed string literal does not represent a single character");}
    data_ += s;
}

SGEXTN::SingText::Character::Character(int unicode){
    if(unicode < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character constructor crashed because unicode is negative");}
    else if(unicode > 0x10ffff){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character constructor crashed because unicode exceeds the largest possible code point");}
    data_ = SGEXTN::SingText::String::stringFromUnicode(unicode);
}

bool SGEXTN::SingText::Character::operator==(const SGEXTN::SingText::Character& x) const {
    return (data_ == x.data_);
}

bool SGEXTN::SingText::Character::operator!=(const SGEXTN::SingText::Character& x) const {
    return (data_ != x.data_);
}

bool SGEXTN::SingText::Character::operator<(const SGEXTN::SingText::Character& x) const {
    return (data_ < x.data_);
}

bool SGEXTN::SingText::Character::operator>(const SGEXTN::SingText::Character& x) const {
    return (data_ > x.data_);
}

bool SGEXTN::SingText::Character::operator<=(const SGEXTN::SingText::Character& x) const {
    return (data_ <= x.data_);
}

bool SGEXTN::SingText::Character::operator>=(const SGEXTN::SingText::Character& x) const {
    return (data_ >= x.data_);
}

bool SGEXTN::SingText::Character::sendOut(const SGEXTN::SingText::Character& x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SingText::String>::sendOut(x.data_, data);
}

bool SGEXTN::SingText::Character::sendIn(SGEXTN::SingText::Character& x, SGEXTN::Containers::Span<unsigned char> data){
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SingText::String>::sendIn(x.data_, data);
    if(isValid == false || x.data_.characterLength() != 1){return false;}
    return true;
}

int SGEXTN::SingText::Character::sizeOut(const SGEXTN::SingText::Character& x){
    return SGEXTN::Containers::Serialise<SGEXTN::SingText::String>::sizeOut(x.data_);
}

int SGEXTN::SingText::Character::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<SGEXTN::SingText::String>::sizeIn(data);
}

int SGEXTN::SingText::Character::byteLength() const {
    return data_.byteLength();
}

unsigned char& SGEXTN::SingText::Character::byteAt(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character::byteAt crashed because the index points beyond the end of the character");}
    return data_.byteAt(i);
}

const unsigned char& SGEXTN::SingText::Character::byteAt(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character::byteAt crashed because the index points beyond the end of the character");}
    return data_.byteAt(i);
}

unsigned char SGEXTN::SingText::Character::baseToAsciiChar() const {
    if(data_.byteAt(0) > 0x7f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character::baseToAsciiChar crashed because the first unsigned char in the grapheme cluster does not represent a valid ASCII character");}
    return data_.byteAt(0);
}

bool SGEXTN::SingText::Character::isDigit() const {
    if(byteLength() != 1){return false;}
    if((*this) >= '0' && (*this) <= '9'){return true;}
    return false;
}

bool SGEXTN::SingText::Character::isDigit(int base) const {
    if(base < 2 || base > 36){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character::isDigit crashed because base is not within 2 to 36 inclusive");}
    if(byteLength() != 1){return false;}
    const int d = getCharacterDigitValue(*this);
    if(d >= 0 && d < base){return true;}
    return false;
}

bool SGEXTN::SingText::Character::isEnglishLowercase() const {
    if(byteLength() != 1){return false;}
    if((*this) >= 'a' && (*this) <= 'z'){return true;}
    return false;
}

bool SGEXTN::SingText::Character::isEnglishUppercase() const {
    if(byteLength() != 1){return false;}
    if((*this) >= 'A' && (*this) <= 'Z'){return true;}
    return false;
}

bool SGEXTN::SingText::Character::isEnglishLetter() const {
    return (isEnglishUppercase() || isEnglishLowercase());
}

bool SGEXTN::SingText::Character::isEnglishAlphanumeric() const {
    return (isEnglishLetter() || isDigit());
}

bool SGEXTN::SingText::Character::isASCII() const {
    if(byteLength() != 1){return false;}
    if(byteAt(0) < 128){return true;}
    return false;
}

bool SGEXTN::SingText::Character::isWhitespace() const {
    if(byteLength() == 1){return SGEXTN::SingText::UnicodeQuery::isWhitespace(static_cast<int>(byteAt(0)));}
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() != 1){return false;}
    return SGEXTN::SingText::UnicodeQuery::isWhitespace(codePoints.at(0));
}

int SGEXTN::SingText::Character::getBaseUnicode() const {
    if((byteAt(0) & 0x80) == 0){return static_cast<int>(byteAt(0));}
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() == 1){return codePoints.at(0);}
    for(int i=0; i<codePoints.length(); i++){
        const SGEXTN::SingText::GraphemeSegmentationType graphemeCategory = SGEXTN::SingText::UnicodeQuery::getGraphemeSegmentationType(codePoints.at(i));
        if(graphemeCategory == SGEXTN::SingText::GraphemeSegmentationType::Other || graphemeCategory == SGEXTN::SingText::GraphemeSegmentationType::RegionalIndicator || graphemeCategory == SGEXTN::SingText::GraphemeSegmentationType::HangulLeading || graphemeCategory == SGEXTN::SingText::GraphemeSegmentationType::HangulVowel || graphemeCategory == SGEXTN::SingText::GraphemeSegmentationType::HangulTrailing || graphemeCategory == SGEXTN::SingText::GraphemeSegmentationType::HangulLeadingAndVowel || graphemeCategory == SGEXTN::SingText::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing){return codePoints.at(i);}
    }
    return codePoints.at(0);
}

SGEXTN::Containers::Array<int> SGEXTN::SingText::Character::getUnicode() const {
    return data_.getUnicode();
}

bool SGEXTN::SingText::Character::isUppercase() const {
    return (SGEXTN::SingText::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::SingText::FullCharacterType::UppercaseLetter);
}

bool SGEXTN::SingText::Character::isLowercase() const {
    return (SGEXTN::SingText::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::SingText::FullCharacterType::LowercaseLetter);
}

bool SGEXTN::SingText::Character::isTitlecase() const {
    return (SGEXTN::SingText::UnicodeQuery::getFullType(getBaseUnicode()) == SGEXTN::SingText::FullCharacterType::TitlecaseLetter);
}

SGEXTN::SingText::Character SGEXTN::SingText::Character::getUppercase() const {
    if(byteLength() == 1){return SGEXTN::SingText::Character(SGEXTN::SingText::UnicodeQuery::getUppercase(static_cast<int>(byteAt(0))));}
    SGEXTN::SingText::Character output;
    output.data_ = "";
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        output.data_ += SGEXTN::SingText::String::stringFromUnicode(SGEXTN::SingText::UnicodeQuery::getUppercase(unicode.at(i)));
    }
    return output;
}

SGEXTN::SingText::Character SGEXTN::SingText::Character::getLowercase() const {
    if(byteLength() == 1){return SGEXTN::SingText::Character(SGEXTN::SingText::UnicodeQuery::getLowercase(static_cast<int>(byteAt(0))));}
    SGEXTN::SingText::Character output;
    output.data_ = "";
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        output.data_ += SGEXTN::SingText::String::stringFromUnicode(SGEXTN::SingText::UnicodeQuery::getLowercase(unicode.at(i)));
    }
    return output;
}

SGEXTN::SingText::Character SGEXTN::SingText::Character::getTitlecase() const {
    if(byteLength() == 1){return SGEXTN::SingText::Character(SGEXTN::SingText::UnicodeQuery::getTitlecase(static_cast<int>(byteAt(0))));}
    SGEXTN::SingText::Character output;
    output.data_ = "";
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        output.data_ += SGEXTN::SingText::String::stringFromUnicode(SGEXTN::SingText::UnicodeQuery::getTitlecase(unicode.at(i)));
    }
    return output;
}

int SGEXTN::SingText::Character::getDecimalDigitValue() const {
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() > 1){return -1;}
    return SGEXTN::SingText::UnicodeQuery::getDecimalDigitValue(codePoints.at(0));
}

float SGEXTN::SingText::Character::getNumericalValue() const {
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(codePoints.length() > 1){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    return SGEXTN::SingText::UnicodeQuery::getNumericalValue(codePoints.at(0));
}
