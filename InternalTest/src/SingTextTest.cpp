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

#include <SGEXTN/InternalTest/private_api/SingTextTest.h>
#include <SGEXTN/SingText/String.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/SingText/Character.h>
#include <SGEXTN/Math/FloatLimits.h>
#include <SGEXTN/Containers/Serialise.h>

namespace {
bool isBitwiseIdentical(const SGEXTN::Containers::Array<unsigned char>& a, const SGEXTN::Containers::Array<unsigned char>& b){
    if(a.length() != b.length()){return false;}
    for(int i=0; i<a.length(); i++){
        if(a.at(i) != b.at(i)){return false;}
    }
    return true;
}

bool isBitwiseIdentical(int length, const SGEXTN::Containers::Array<unsigned char>& a, const SGEXTN::Containers::Array<unsigned char>& b){
    for(int i=0; i<length; i++){
        if(a.at(i) != b.at(i)){return false;}
    }
    return true;
}

SGEXTN::Containers::Span<unsigned char> makeSpan(SGEXTN::Containers::Array<unsigned char>& array, int length){
    return SGEXTN::Containers::Span<unsigned char>(array, 0, length);
}

const char* utf8(const char8_t* x){
    return reinterpret_cast<const char*>(x);
}
}

void SGEXTN::InternalTest::SingTextTest::testAll(){
    SGEXTN::InternalTest::SingTextTest::testCharacter();
    SGEXTN::InternalTest::SingTextTest::testString();
}

void SGEXTN::InternalTest::SingTextTest::testCharacter(){
    if(SGEXTN::SingText::Character() != SGEXTN::SingText::Character(0x1f496)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character default value fail");}
    if(SGEXTN::SingText::Character('A') != SGEXTN::SingText::Character(65)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character constructor from unsigned char fail");}
    if(SGEXTN::SingText::Character(reinterpret_cast<const char*>(u8"\U0001f496")) != SGEXTN::SingText::Character()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character constructor from C string fail");}
    const SGEXTN::SingText::Character a('a');
    const SGEXTN::SingText::Character b('b');
    if(a == b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character equality check fail");}
    if(a != SGEXTN::SingText::Character(0x61)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character inequality check fail");}
    if(b < a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character less than operator fail");}
    if(a > b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character more than operator fail");}
    if(b <= a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character less than or equal to operator fail");}
    if(a >= b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character more than or equal to operator fail");}
    SGEXTN::SingText::Character c;
    if(c.byteLength() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character check byte length fail");}
    if(c.byteAt(3) != 0x96){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get byte at fail");}
    c.byteAt(3) = 0x97;
    if(c != SGEXTN::SingText::Character(0x1f497)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character set byte at fail");}
    if(a.baseToAsciiChar() != 'a'){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character convert to C++ unsigned char fail");}
    if(SGEXTN::SingText::Character('0').isDigit() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 10 fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isDigit() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 10 fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 10 fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 10 fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 10 fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 10 fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 10 fail for punctuation mark");}
    if(SGEXTN::SingText::Character('0').isDigit(2) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 2 fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 2 fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 2 fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 2 fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 2 fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 2 fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 2 fail for punctuation mark");}
    if(SGEXTN::SingText::Character('0').isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 16 fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 16 fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 16 fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 16 fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isDigit(16) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 16 fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isDigit(16) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 16 fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isDigit(16) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 16 fail for punctuation mark");}
    if(SGEXTN::SingText::Character('0').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 36 fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 36 fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 36 fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 36 fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 36 fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 36 fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isDigit(36) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is digit base 36 fail for punctuation mark");}
    if(SGEXTN::SingText::Character('0').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English lowercase fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English lowercase fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isEnglishLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English lowercase fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English lowercase fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isEnglishLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English lowercase fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English lowercase fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English lowercase fail for punctuation mark");}
    if(SGEXTN::SingText::Character('0').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English uppercase fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English uppercase fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English uppercase fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isEnglishUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English uppercase fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English uppercase fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isEnglishUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English uppercase fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English uppercase fail for punctuation mark");}
    if(SGEXTN::SingText::Character('0').isEnglishLetter() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English letter fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isEnglishLetter() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English letter fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English letter fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English letter fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English letter fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English letter fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isEnglishLetter() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English letter fail for punctuation mark");}
    if(SGEXTN::SingText::Character('0').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English alphanumeric fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English alphanumeric fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English alphanumeric fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English alphanumeric fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English alphanumeric fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English alphanumeric fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isEnglishAlphanumeric() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is English alphanumeric fail for punctuation mark");}
    if(SGEXTN::SingText::Character('0').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is ASCII fail for digit 0");}
    if(SGEXTN::SingText::Character('5').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is ASCII fail for digit 5");}
    if(SGEXTN::SingText::Character('a').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is ASCII fail for small letter a");}
    if(SGEXTN::SingText::Character('A').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is ASCII fail for capital letter A");}
    if(SGEXTN::SingText::Character('x').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is ASCII fail for small letter x");}
    if(SGEXTN::SingText::Character('X').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is ASCII fail for capital letter X");}
    if(SGEXTN::SingText::Character('/').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is ASCII fail for punctuation mark");}
    if(SGEXTN::SingText::Character().isASCII() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is ASCII fail for heart");}
    if(SGEXTN::SingText::Character().isWhitespace() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is whitespace fail for heart");}
    if(SGEXTN::SingText::Character("A").isWhitespace() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is whitespace fail for English letter");}
    if(SGEXTN::SingText::Character(" ").isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is whitespace fail for space");}
    if(SGEXTN::SingText::Character("\t").isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is whitespace fail for tab");}
    if(SGEXTN::SingText::Character("\n").isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is whitespace fail for newline");}
    if(SGEXTN::SingText::Character(0x2003).isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is whitespace fail for unicode space");}
    const SGEXTN::SingText::Character cWithTail(reinterpret_cast<const char*>(u8"\u0063\u0327"));
    if(cWithTail.getBaseUnicode() != 0x63){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get base unicode fail");}
    SGEXTN::Containers::Array<int> codePoints = cWithTail.getUnicode();
    if(codePoints.length() != 2 || codePoints.at(0) != 0x63 || codePoints.at(1) != 0x327){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get unicode fail");}
    if(SGEXTN::SingText::Character('a').isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is uppercase English lowercase fail");}
    if(SGEXTN::SingText::Character('A').isUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is uppercase English uppercase fail");}
    if(SGEXTN::SingText::Character(0x03b1).isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is uppercase Greek lowercase fail");}
    if(SGEXTN::SingText::Character(0x0391).isUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is uppercase Greek uppercase fail");}
    if(SGEXTN::SingText::Character(0x4e00).isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is uppercase Chinese letter fail");}
    if(SGEXTN::SingText::Character(0x01c5).isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is uppercase Dz fail");}
    if(SGEXTN::SingText::Character('a').isLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is lowercase English lowercase fail");}
    if(SGEXTN::SingText::Character('A').isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is lowercase English uppercase fail");}
    if(SGEXTN::SingText::Character(0x03b1).isLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is lowercase Greek lowercase fail");}
    if(SGEXTN::SingText::Character(0x0391).isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is lowercase Greek uppercase fail");}
    if(SGEXTN::SingText::Character(0x4e00).isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is lowercase Chinese letter fail");}
    if(SGEXTN::SingText::Character(0x01c5).isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is lowercase Dz fail");}
    if(SGEXTN::SingText::Character('a').isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is titlecase English lowercase fail");}
    if(SGEXTN::SingText::Character('A').isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is titlecase English uppercase fail");}
    if(SGEXTN::SingText::Character(0x03b1).isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is titlecase Greek lowercase fail");}
    if(SGEXTN::SingText::Character(0x0391).isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is titlecase Greek uppercase fail");}
    if(SGEXTN::SingText::Character(0x4e00).isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is titlecase Chinese letter fail");}
    if(SGEXTN::SingText::Character(0x01c5).isTitlecase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character is titlecase Dz fail");}
    if(SGEXTN::SingText::Character('a').getUppercase() != SGEXTN::SingText::Character('A')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get uppercase English lowercase fail");}
    if(SGEXTN::SingText::Character('A').getUppercase() != SGEXTN::SingText::Character('A')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get uppercase English uppercase fail");}
    if(SGEXTN::SingText::Character(0x03b1).getUppercase() != SGEXTN::SingText::Character(0x0391)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get uppercase Greek lowercase fail");}
    if(SGEXTN::SingText::Character(0x0391).getUppercase() != SGEXTN::SingText::Character(0x0391)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get uppercase Greek uppercase fail");}
    if(SGEXTN::SingText::Character(0x4e00).getUppercase() != SGEXTN::SingText::Character(0x4e00)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get uppercase Chinese letter fail");}
    if(SGEXTN::SingText::Character(0x01c5).getUppercase() != SGEXTN::SingText::Character(0x01c4)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get uppercase Dz fail");}
    if(SGEXTN::SingText::Character('a').getLowercase() != SGEXTN::SingText::Character('a')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get lowercase English lowercase fail");}
    if(SGEXTN::SingText::Character('A').getLowercase() != SGEXTN::SingText::Character('a')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get lowercase English uppercase fail");}
    if(SGEXTN::SingText::Character(0x03b1).getLowercase() != SGEXTN::SingText::Character(0x03b1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get lowercase Greek lowercase fail");}
    if(SGEXTN::SingText::Character(0x0391).getLowercase() != SGEXTN::SingText::Character(0x03b1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get lowercase Greek uppercase fail");}
    if(SGEXTN::SingText::Character(0x4e00).getLowercase() != SGEXTN::SingText::Character(0x4e00)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get lowercase Chinese letter fail");}
    if(SGEXTN::SingText::Character(0x01c5).getLowercase() != SGEXTN::SingText::Character(0x01c6)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get lowercase Dz fail");}
    if(SGEXTN::SingText::Character('a').getTitlecase() != SGEXTN::SingText::Character('A')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get titlecase English lowercase fail");}
    if(SGEXTN::SingText::Character('A').getTitlecase() != SGEXTN::SingText::Character('A')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get titlecase English uppercase fail");}
    if(SGEXTN::SingText::Character(0x03b1).getTitlecase() != SGEXTN::SingText::Character(0x0391)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get titlecase Greek lowercase fail");}
    if(SGEXTN::SingText::Character(0x0391).getTitlecase() != SGEXTN::SingText::Character(0x0391)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get titlecase Greek uppercase fail");}
    if(SGEXTN::SingText::Character(0x4e00).getTitlecase() != SGEXTN::SingText::Character(0x4e00)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get titlecase Chinese letter fail");}
    if(SGEXTN::SingText::Character(0x01c5).getTitlecase() != SGEXTN::SingText::Character(0x01c5)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get titlecase Dz fail");}
    if(SGEXTN::SingText::Character('0').getDecimalDigitValue() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get decimal digit value digit zero fail");}
    if(SGEXTN::SingText::Character(0x0be6).getDecimalDigitValue() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get decimal digit value Tamil digit zero fail");}
    if(SGEXTN::SingText::Character(' ').getDecimalDigitValue() != -1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get decimal digit value space fail");}
    if(SGEXTN::SingText::Character(0xbd).getDecimalDigitValue() != -1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get decimal digit value half fraction fail");}
    if(SGEXTN::SingText::Character('0').getNumericalValue() != 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get numerical value digit zero fail");}
    if(SGEXTN::SingText::Character(0x0be6).getNumericalValue() != 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get numerical value Tamil digit zero fail");}
    if(SGEXTN::SingText::Character(' ').getNumericalValue() != SGEXTN::Math::FloatLimits<float>::negativeInfinity()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get numerical value space fail");}
    if(SGEXTN::SingText::Character(0xbd).getNumericalValue() != 0.5f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::Character get numerical value half fraction fail");}
    SGEXTN::Containers::Array<unsigned char> serialiseArray(726, static_cast<unsigned char>(0));
    SGEXTN::Containers::Array<unsigned char> serialiseDestination(726, static_cast<unsigned char>(0));
    serialiseArray.at(0) = static_cast<unsigned char>(0x04);
    serialiseArray.at(1) = static_cast<unsigned char>(0x00);
    serialiseArray.at(2) = static_cast<unsigned char>(0x00);
    serialiseArray.at(3) = static_cast<unsigned char>(0x00);
    serialiseArray.at(4) = static_cast<unsigned char>(0xf0);
    serialiseArray.at(5) = static_cast<unsigned char>(0x9f);
    serialiseArray.at(6) = static_cast<unsigned char>(0x92);
    serialiseArray.at(7) = static_cast<unsigned char>(0x96);
    bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SingText::Character>::sendOut(SGEXTN::SingText::Character(), makeSpan(serialiseDestination, 8));
    if(isValid == false || isBitwiseIdentical(8, serialiseArray, serialiseDestination) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise sendOut SGEXTN::SingText::Character fail");}
    SGEXTN::SingText::Character unserialisedCharacter;
    isValid = SGEXTN::Containers::Serialise<SGEXTN::SingText::Character>::sendIn(unserialisedCharacter, makeSpan(serialiseArray, 8));
    if(isValid == false || unserialisedCharacter != SGEXTN::SingText::Character()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise sendIn SGEXTN::SingText::Character fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SingText::Character>::sizeOut(SGEXTN::SingText::Character()) != 8){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise sizeOut SGEXTN::SingText::Character fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SingText::Character>::sizeIn(makeSpan(serialiseArray, 100)) != 8){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise sizeIn SGEXTN::SingText::Character fail");}
}

void SGEXTN::InternalTest::SingTextTest::testString(){
    SGEXTN::SingText::String a('a');
    const SGEXTN::SingText::String b("b");
    if(b != SGEXTN::SingText::String('b')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String constructor from C++ unsigned char fail");}
    if(a != SGEXTN::SingText::String("a")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String constructor from C string fail");}
    if(a != SGEXTN::SingText::String(SGEXTN::SingText::Character('a'))){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String constructor from SGEXTN character fail");}
    if(a == b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String equality check fail");}
    if((a != b) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String inequality check fail");}
    if(b < a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String less than operator fail");}
    if(a > b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String more than operator fail");}
    if(b <= a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String less than or equal to operator fail");}
    if(a >= b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String more than or equal to operator fail");}
    if(a + b != "ab"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String string addition fail");}
    a += b;
    if(a != "ab"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String string addition assignment fail");}
    SGEXTN::SingText::String aAlphaSpaceEpsilonA = utf8(u8"\u0061\u03b1\u0301\u0020\u03c3\u0041");
    if(aAlphaSpaceEpsilonA.byteLength() != 9){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check  byte length fail");}
    if(aAlphaSpaceEpsilonA.characterLength() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check character length fail");}
    if(aAlphaSpaceEpsilonA.byteAt(8) != 'A'){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String get byte at fail");}
    aAlphaSpaceEpsilonA.byteAt(8) = 'B';
    if(aAlphaSpaceEpsilonA.byteAt(8) != 'B'){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String set byte at fail");}
    if(aAlphaSpaceEpsilonA.getCharacterAt(1) != SGEXTN::SingText::Character(utf8(u8"\u03b1\u0301"))){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String get character at fail");}
    aAlphaSpaceEpsilonA.setCharacterAt(1, SGEXTN::SingText::Character(utf8(u8"\u03b1\u0300")));
    if(aAlphaSpaceEpsilonA.getCharacterAt(1) != SGEXTN::SingText::Character(utf8(u8"\u03b1\u0300"))){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String set character same length fail");}
    aAlphaSpaceEpsilonA.setCharacterAt(4, SGEXTN::SingText::Character(utf8(u8"\uff21")));
    if(aAlphaSpaceEpsilonA.getCharacterAt(4) != SGEXTN::SingText::Character(0xff21)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String set character different length fail");}
    if(aAlphaSpaceEpsilonA.fillBytes('0') != "00000000000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill bytes fail");}
    if(aAlphaSpaceEpsilonA.fillCharacters(SGEXTN::SingText::Character(utf8(u8"\u03b1\u0301"))) != utf8(u8"\u03b1\u0301\u03b1\u0301\u03b1\u0301\u03b1\u0301\u03b1\u0301")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill characters fail");}
    SGEXTN::SingText::String bytesFindString = "__ab_aab_abb";
    if(bytesFindString.findFirstBytesFromLeft("ab") != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String find bytes from left fail");}
    if(bytesFindString.findFirstBytesFromRight("ab") != 9){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String find bytes from right fail");}
    if(bytesFindString.findFirstBytesFromLeftBounded(3, "ab") != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String find bytes from left bounded fail");}
    if(bytesFindString.findFirstBytesFromRightBounded(8, "ab") != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String find bytes from right bounded fail");}
    SGEXTN::SingText::String charactersFindString = utf8(u8"\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2");
    if(charactersFindString.findFirstCharactersFromLeft(utf8(u8"\u03b1\u0300\u03b2")) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String find characters from left fail");}
    if(charactersFindString.findFirstCharactersFromRight(utf8(u8"\u03b1\u0300\u03b2")) != 9){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String find characters from right fail");}
    if(charactersFindString.findFirstCharactersFromLeftBounded(3, utf8(u8"\u03b1\u0300\u03b2")) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String find characters from left bounded fail");}
    if(charactersFindString.findFirstCharactersFromRightBounded(8, utf8(u8"\u03b1\u0300\u03b2")) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String find characters from right bounded fail");}
    if(bytesFindString.substringBytes(5, 3) != "aab"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String substring bytes fail");}
    if(bytesFindString.substringBytesLeft(3) != "__a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String substring bytes left fail");}
    if(bytesFindString.substringBytesRight(3) != "abb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String substring bytes right fail");}
    if(charactersFindString.substringCharacters(5, 3) != utf8(u8"\u03b1\u0300\u03b1\u0300\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String substring characters fail");}
    if(charactersFindString.substringCharactersLeft(3) != utf8(u8"\u0020\u0020\u03b1\u0300")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String substring characters left fail");}
    if(charactersFindString.substringCharactersRight(3) != utf8(u8"\u03b1\u0300\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String substring characters right fail");}
    if(bytesFindString.replaceBytes("ab", 'c') != "__c_ac_cb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String replace bytes fail");}
    if(charactersFindString.replaceCharacters(utf8(u8"\u03b1\u0300\u03b2"), utf8(u8"\u03b3")) != utf8(u8"\u0020\u0020\u03b3\u0020\u03b1\u0300\u03b3\u0020\u03b3\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String replace characters fail");}
    if(bytesFindString.removeBytes("ab") != "___a_b"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String remove bytes fail");}
    if(charactersFindString.removeCharacters(utf8(u8"\u03b1\u0300\u03b2")) != utf8(u8"\u0020\u0020\u0020\u03b1\u0300\u0020\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String remove characters fail");}
    if(bytesFindString.insertAtByteIndex(0, "cc") != "cc__ab_aab_abb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String insert bytes at start fail");}
    if(bytesFindString.insertAtByteIndex(2, "cc") != "__ccab_aab_abb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String insert bytes at middle fail");}
    if(bytesFindString.insertAtByteIndex(12, "cc") != "__ab_aab_abbcc"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String insert bytes at end fail");}
    if(charactersFindString.insertAtCharacterIndex(0, utf8(u8"\u03b3\u03b3")) != utf8(u8"\u03b3\u03b3\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String insert characters at start fail");}
    if(charactersFindString.insertAtCharacterIndex(2, utf8(u8"\u03b3\u03b3")) != utf8(u8"\u0020\u0020\u03b3\u03b3\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String insert characters at middle fail");}
    if(charactersFindString.insertAtCharacterIndex(12, utf8(u8"\u03b3\u03b3")) != utf8(u8"\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2\u03b3\u03b3")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String insert characters at end fail");}
    if(bytesFindString.removeAtByteIndex(5, 3) != "__ab__abb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String remove bytes fail");}
    if(charactersFindString.removeAtCharacterIndex(5, 3) != utf8(u8"\u0020\u0020\u03b1\u0300\u03b2\u0020\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String remove characters fail");}
    if(bytesFindString.containsBytes("ab") == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check if contains existing bytes fail");}
    if(bytesFindString.containsBytes("bc") == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check if contains nonexistent bytes fail");}
    if(charactersFindString.containsCharacters(utf8(u8"\u03b1\u0300\u03b2")) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check if contains existing characters fail");}
    if(charactersFindString.containsCharacters(utf8(u8"\u0300\u03b2")) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check if contains nonexistent characters fail");}
    if(bytesFindString.startsWithBytes("__") == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check start bytes with matched prefix fail");}
    if(bytesFindString.startsWithBytes("_a") == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check start bytes with unmatched prefix fail");}
    if(charactersFindString.startsWithCharacters(utf8(u8"\u0020\u0020")) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check start characters with matched prefix fail");}
    if(charactersFindString.startsWithCharacters(utf8(u8"\u0020\u03b1\u0300")) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check start characters with unmatched prefix fail");}
    if(bytesFindString.endsWithBytes("bb") == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check end bytes with matched prefix fail");}
    if(bytesFindString.endsWithBytes("ab") == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check end bytes with unmatched prefix fail");}
    if(charactersFindString.endsWithCharacters(utf8(u8"\u03b2\u03b2")) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check end characters with matched prefix fail");}
    if(charactersFindString.endsWithCharacters(utf8(u8"\u03b1\u0300\u03b2")) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check end characters with unmatched prefix fail");}
    bytesFindString = SGEXTN::SingText::String::repeat("a", 7);
    charactersFindString = SGEXTN::SingText::String::repeat(utf8(u8"\u03b1\u0300"), 7);
    if(charactersFindString != utf8(u8"\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String repeat given string fail");}
    if(bytesFindString.countBytes("aaa") != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String count bytes no overlap fail");}
    if(charactersFindString.countCharacters(utf8(u8"\u03b1\u0300\u03b1\u0300\u03b1\u0300")) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String count characters no overlap fail");}
    if(bytesFindString.countBytesAllowOverlap("aaa") != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String count bytes allow overlap fail");}
    if(charactersFindString.countCharactersAllowOverlap(utf8(u8"\u03b1\u0300\u03b1\u0300\u03b1\u0300")) != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String count characters allow overlap fail");}
    if(bytesFindString.fillLeftToByteLength(5, 'b') != bytesFindString){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill left bytes sufficient length fail");}
    if(bytesFindString.fillLeftToByteLength(10, 'b') != "bbbaaaaaaa"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill left bytes insufficient length fail");}
    if(charactersFindString.fillLeftToCharacterLength(5, SGEXTN::SingText::Character(utf8(u8"\u03b2"))) != charactersFindString){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill left characters sufficient length fail");}
    if(charactersFindString.fillLeftToCharacterLength(10, SGEXTN::SingText::Character(utf8(u8"\u03b2"))) != utf8(u8"\u03b2\u03b2\u03b2\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill left characters insufficient length fail");}
    if(bytesFindString.fillRightToByteLength(5, 'b') != bytesFindString){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill right bytes sufficient length fail");}
    if(bytesFindString.fillRightToByteLength(10, 'b') != "aaaaaaabbb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill right bytes insufficient length fail");}
    if(charactersFindString.fillRightToCharacterLength(5, SGEXTN::SingText::Character(utf8(u8"\u03b2"))) != charactersFindString){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill right characters sufficient length fail");}
    if(charactersFindString.fillRightToCharacterLength(10, SGEXTN::SingText::Character(utf8(u8"\u03b2"))) != utf8(u8"\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b2\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String fill right characters insufficient length fail");}
    if(charactersFindString.byteIndexToCharacterIndex(1) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String convert byte index to character index fail");}
    if(charactersFindString.characterIndexToByteIndex(1) != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String convert character index to byte index fail");}
    SGEXTN::SingText::String positiveBase10Number = "26";
    SGEXTN::SingText::String negativeBase10Number = "-26";
    SGEXTN::SingText::String positiveBase16Number = "1a";
    SGEXTN::SingText::String negativeBase16Number = "-1A";
    SGEXTN::SingText::String positiveNonLatinNumber = utf8(u8"\u0be8\u0bec");
    SGEXTN::SingText::String negativeNonLatinNumber = utf8(u8"\u002d\u0be8\u0bec");
    SGEXTN::SingText::String invalidNumber = "2 6";
    bool isValid = false;
    if(positiveBase10Number.parseToShort(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 10 number to short fail");}
    isValid = false;
    if(negativeBase10Number.parseToShort(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 10 number to short fail");}
    isValid = false;
    if(positiveBase16Number.parseToShort(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 16 number to short fail");}
    isValid = false;
    if(negativeBase16Number.parseToShort(&isValid, 16) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 16 number to short fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToShort(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive non Latin number to short fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToShort(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative non Latin number to short fail");}
    isValid = true;
    if(invalidNumber.parseToShort(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to short fail");}
    if(invalidNumber.parseToShort(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to short no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedShort(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 10 number to unsigned short fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedShort(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 16 number to unsigned short fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedShort(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive non Latin number to unsigned short fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedShort(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to unsigned short fail");}
    if(invalidNumber.parseToUnsignedShort(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to unsigned short no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToInt(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 10 number to int fail");}
    isValid = false;
    if(negativeBase10Number.parseToInt(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 10 number to int fail");}
    isValid = false;
    if(positiveBase16Number.parseToInt(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 16 number to int fail");}
    isValid = false;
    if(negativeBase16Number.parseToInt(&isValid, 16) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 16 number to int fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToInt(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive non Latin number to int fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToInt(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative non Latin number to int fail");}
    isValid = true;
    if(invalidNumber.parseToInt(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to int fail");}
    if(invalidNumber.parseToInt(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to int no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedInt(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 10 number to unsigned int fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedInt(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 16 number to unsigned int fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedInt(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive non Latin number to unsigned int fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedInt(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to unsigned int fail");}
    if(invalidNumber.parseToUnsignedInt(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to unsigned int no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 10 number to long long fail");}
    isValid = false;
    if(negativeBase10Number.parseToLongLong(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 10 number to long long fail");}
    isValid = false;
    if(positiveBase16Number.parseToLongLong(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 16 number to long long fail");}
    isValid = false;
    if(negativeBase16Number.parseToLongLong(&isValid, 16) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 16 number to long long fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive non Latin number to long long fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToLongLong(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative non Latin number to long long fail");}
    isValid = true;
    if(invalidNumber.parseToLongLong(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to long long fail");}
    if(invalidNumber.parseToLongLong(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to long long no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 10 number to unsigned long long fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedLongLong(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 16 number to unsigned long long fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive non Latin number to unsigned long long fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedLongLong(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to unsigned long long fail");}
    if(invalidNumber.parseToUnsignedLongLong(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to unsigned long long no success flag fail");}
    positiveBase10Number = "10.5";
    negativeBase10Number = "-010.500";
    const SGEXTN::SingText::String positiveScientificNotation = "5^-1";
    const SGEXTN::SingText::String negativeScientificNotation = "-5.0^-01";
    positiveBase16Number = "a.8";
    negativeBase16Number = "-0a.80";
    positiveNonLatinNumber = utf8(u8"\u0be6\u002e\u0beb");
    negativeNonLatinNumber = utf8(u8"\u002d\u0be6\u0be6\u002e\u0beb\u0be6");
    invalidNumber = "-+0.5";
    isValid = false;
    if(positiveBase10Number.parseToFloat(&isValid, 10) != 10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 10 number to float fail");}
    isValid = false;
    if(negativeBase10Number.parseToFloat(&isValid, 10) != -10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 10 number to float fail");}
    isValid = false;
    if(positiveScientificNotation.parseToFloat(&isValid, 10) != 0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive scientific notation number to float fail");}
    isValid = false;
    if(negativeScientificNotation.parseToFloat(&isValid, 10) != -0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative scientific notation number to float fail");}
    isValid = false;
    if(positiveBase16Number.parseToFloat(&isValid, 16) != 10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 16 number to float fail");}
    isValid = false;
    if(negativeBase16Number.parseToFloat(&isValid, 16) != -10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 16 number to float fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToFloat(&isValid, 10) != 0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive non Latin number to float fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToFloat(&isValid, 10) != -0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative non Latin number to float fail");}
    isValid = true;
    if(invalidNumber.parseToFloat(&isValid, 10) != 0.0f || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to float fail");}
    if(invalidNumber.parseToFloat(nullptr, 10) != 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to float no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToDouble(&isValid, 10) != 10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 10 number to double fail");}
    isValid = false;
    if(negativeBase10Number.parseToDouble(&isValid, 10) != -10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 10 number to double fail");}
    isValid = false;
    if(positiveScientificNotation.parseToDouble(&isValid, 10) != 0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive scientific notation number to double fail");}
    isValid = false;
    if(negativeScientificNotation.parseToDouble(&isValid, 10) != -0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative scientific notation number to double fail");}
    isValid = false;
    if(positiveBase16Number.parseToDouble(&isValid, 16) != 10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive base 16 number to double fail");}
    isValid = false;
    if(negativeBase16Number.parseToDouble(&isValid, 16) != -10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative base 16 number to double fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToDouble(&isValid, 10) != 0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse positive non Latin number to double fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToDouble(&isValid, 10) != -0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse negative non Latin number to double fail");}
    isValid = true;
    if(invalidNumber.parseToDouble(&isValid, 10) != 0.0f || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to double fail");}
    if(invalidNumber.parseToDouble(nullptr, 10) != 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String parse invalid number to double no success flag fail");}
    if(SGEXTN::SingText::String::stringFromShort(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print short positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromShort(-26, 10) != "-26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print short negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromShort(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print short positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromShort(-26, 16) != "-1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print short negative base 16 fail");}
    if(SGEXTN::SingText::String::stringFromUnsignedShort(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print unsigned short positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromUnsignedShort(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print unsigned short positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromInt(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print int positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromInt(-26, 10) != "-26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print int negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromInt(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print int positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromInt(-26, 16) != "-1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print int negative base 16 fail");}
    if(SGEXTN::SingText::String::stringFromUnsignedInt(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print unsigned int positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromUnsignedInt(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print unsigned int positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromLongLong(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print long long positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromLongLong(-26, 10) != "-26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print long long negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromLongLong(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print long long positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromLongLong(-26, 16) != "-1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print long long negative base 16 fail");}
    if(SGEXTN::SingText::String::stringFromUnsignedLongLong(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print unsigned long long positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromUnsignedLongLong(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print unsigned long long positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 3) != "10.333"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float decimal place mode positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(-31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 3) != "-10.333"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float decimal place mode negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 3) != "a.555"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float decimal place mode positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(-31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 3) != "-a.555"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float decimal place mode negative base 16 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 3) != "10.3"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float significant figures mode positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(-31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 3) != "-10.3"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float significant figures mode negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 3) != "a.55"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float significant figures mode positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(-31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 3) != "-a.55"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float significant figures mode negative base 16 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::ScientificNotation, 3) != "1.03^1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float scientific notation mode positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(-1.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::ScientificNotation, 3) != "-3.33^-1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float scientific notation mode negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::ScientificNotation, 3) != "a.55^0"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float scientific notation mode positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromFloat(-1.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::ScientificNotation, 3) != "-5.55^-1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print float scientific notation mode negative base 16 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 3) != "10.333"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double decimal place mode positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(-31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 3) != "-10.333"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double decimal place mode negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 3) != "a.555"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double decimal place mode positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(-31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 3) != "-a.555"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double decimal place mode negative base 16 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 3) != "10.3"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double significant figures mode positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(-31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 3) != "-10.3"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double significant figures mode negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 3) != "a.55"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double significant figures mode positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(-31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 3) != "-a.55"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double significant figures mode negative base 16 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::ScientificNotation, 3) != "1.03^1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double scientific notation mode positive base 10 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(-1.0f / 3.0f, 10, SGEXTN::SingText::FloatPrecisionFormat::ScientificNotation, 3) != "-3.33^-1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double scientific notation mode negative base 10 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::ScientificNotation, 3) != "a.55^0"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double scientific notation mode positive base 16 fail");}
    if(SGEXTN::SingText::String::stringFromDouble(-1.0f / 3.0f, 16, SGEXTN::SingText::FloatPrecisionFormat::ScientificNotation, 3) != "-5.55^-1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String print double scientific notation mode negative base 16 fail");}
    if(SGEXTN::SingText::String("-1.23^+09").prettierScientificNotationBase10() != utf8(u8"-1.23\u00d710\u2079")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String make scientific notation prettier fail");}
    if(SGEXTN::SingText::String("12345").convertNumericSystem(SGEXTN::SingText::Character(0xbe6)) != utf8(u8"\u0be7\u0be8\u0be9\u0bea\u0beb")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String convert to non Latin numbers fail");}
    if(SGEXTN::SingText::String("<b> & </b>#").prepareInnerHtmlText() != "&lt;b&gt; &amp; &lt;/b&gt;#"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String HTML escaping fail");}
    if(SGEXTN::SingText::String("  te xt \t\n  \n \t ").removeLeadingTrailingWhitespace() != "te xt"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String whitespace trimming fail");}
    if(SGEXTN::SingText::String(" a b \nc\t\t\td    e \n \tfgh   ").cleanWhitespace() != "a b c d e fgh"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String whitespace cleaning fail");}
    if(SGEXTN::SingText::String(" a b \nc\t\t\td    e \n \tfgh   ").removeAllWhitespace() != "abcdefgh"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String whitespace removal fail");}
    SGEXTN::Containers::Array<SGEXTN::SingText::String> testSplitString = SGEXTN::SingText::String(",a, bc, \n\td,,, ,e").split(',');
    if(testSplitString.length() != 8 || testSplitString.at(0) != "" || testSplitString.at(1) != "a" || testSplitString.at(2) != " bc" || testSplitString.at(3) != " \n\td" || testSplitString.at(4) != "" || testSplitString.at(5) != "" || testSplitString.at(6) != " " || testSplitString.at(7) != "e"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String split string fail");}
    if(SGEXTN::SingText::String("0123456789").isDigit() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check digit base 10 true fail");}
    if(SGEXTN::SingText::String("0123456789a").isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check digit base 10 false fail");}
    if(SGEXTN::SingText::String("0123456789abcdefABCDEF").isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check digit base 16 true fail");}
    if(SGEXTN::SingText::String("0123456789abcdefg").isDigit(16) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check digit base 16 false fail");}
    if(SGEXTN::SingText::String("qwerty").isEnglishLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check English lowercase true fail");}
    if(SGEXTN::SingText::String("qwertY").isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check English lowercase false fail");}
    if(SGEXTN::SingText::String("QWERTY").isEnglishUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check English uppercase true fail");}
    if(SGEXTN::SingText::String("QWERTy").isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check English uppercase false fail");}
    if(SGEXTN::SingText::String("QWERTYqwerty").isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check English letter true fail");}
    if(SGEXTN::SingText::String("QWERTYqwerty0").isEnglishLetter() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check English letter false fail");}
    if(SGEXTN::SingText::String("QWERTYqwerty0123456789").isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check English alphanumeric true fail");}
    if(SGEXTN::SingText::String("QWERTYqwerty0123456789 ").isEnglishAlphanumeric() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check English alphanumeric false fail");}
    if(SGEXTN::SingText::String("QWERTYqwerty0123456789,.<> ").isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check ASCII true fail");}
    if((SGEXTN::SingText::String("QWERTYqwerty0123456789,.<> ") + SGEXTN::SingText::Character(0xbe6)).isASCII() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check ASCII false fail");}
    if(SGEXTN::SingText::String(" \t\n").isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check whitespace true fail");}
    if(SGEXTN::SingText::String(" \t\n0").isWhitespace() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check whitespace false fail");}
    if(SGEXTN::SingText::String(utf8(u8"A \u0391\u0300_.")).isUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check uppercase true fail");}
    if(SGEXTN::SingText::String(utf8(u8"A \u0391\u0300_.a")).isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check uppercase false fail");}
    if(SGEXTN::SingText::String(utf8(u8"a \u03b1\u0300_.")).isLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check lowercase true fail");}
    if(SGEXTN::SingText::String(utf8(u8"a \u03b1\u0300_.A")).isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check lowercase false fail");}
    if(SGEXTN::SingText::String(utf8(u8"A \u0391\u0300_.\u01c5")).isTitlecase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check titlecase true fail");}
    if(SGEXTN::SingText::String(utf8(u8"A \u0391\u0300_.\u01c4")).isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String check titlecase false fail");}
    const SGEXTN::SingText::String changeCaseTestString = utf8(u8" ./aA\u0391\u03b1\u0300\u01c4\u01c5\u01c6\u4000");
    if(changeCaseTestString.getUppercase() != utf8(u8" ./AA\u0391\u0391\u0300\u01c4\u01c4\u01c4\u4000")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String convert to uppercase fail");}
    if(changeCaseTestString.getLowercase() != utf8(u8" ./aa\u03b1\u03b1\u0300\u01c6\u01c6\u01c6\u4000")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String convert to uppercase fail");}
    if(changeCaseTestString.getTitlecase() != utf8(u8" ./AA\u0391\u0391\u0300\u01c5\u01c5\u01c5\u4000")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String convert to uppercase fail");}
    SGEXTN::Containers::Array<int> unicodeCodePoints = changeCaseTestString.getUnicode();
    SGEXTN::Containers::Array<int> expectedCodePoints = SGEXTN::Containers::Array<int>({0x20, 0x2e, 0x2f, 0x61, 0x41, 0x391, 0x3b1, 0x300, 0x1c4, 0x1c5, 0x1c6, 0x4000});
    if(unicodeCodePoints.length() != expectedCodePoints.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String extract Unicode code points fail");}
    for(int i=0; i<unicodeCodePoints.length(); i++){
        if(unicodeCodePoints.at(i) != expectedCodePoints.at(i)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String extract Unicode code points fail");}
    }
    const SGEXTN::SingText::String unsimplifiedString = utf8(u8"Caf\u00e8 at Yishun \uff2d\uff32\uff34 \u2122 \n\t \U0001d4a9\U0001d4ae\u2081\u2081");
    if(unsimplifiedString.getSimplestEquivalent(false) != "Cafe at Yishun MRT TM NS11"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String case sensitive simplest string conversion fail");}
    if(unsimplifiedString.getSimplestEquivalent(true) != "cafe at yishun mrt tm ns11"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String case insensitive simplest string conversion fail");}
    const SGEXTN::SingText::String sampleText = utf8(u8"I\u2665\U0001f1f8\U0001f1ec");
    SGEXTN::Containers::Array<unsigned char> serialiseArray(726, static_cast<unsigned char>(0));
    SGEXTN::Containers::Array<unsigned char> serialiseDestination(726, static_cast<unsigned char>(0));
    serialiseArray.at(0) = static_cast<unsigned char>(0x0c);
    serialiseArray.at(1) = static_cast<unsigned char>(0x00);
    serialiseArray.at(2) = static_cast<unsigned char>(0x00);
    serialiseArray.at(3) = static_cast<unsigned char>(0x00);
    serialiseArray.at(4) = static_cast<unsigned char>(0x49);
    serialiseArray.at(5) = static_cast<unsigned char>(0xe2);
    serialiseArray.at(6) = static_cast<unsigned char>(0x99);
    serialiseArray.at(7) = static_cast<unsigned char>(0xa5);
    serialiseArray.at(8) = static_cast<unsigned char>(0xf0);
    serialiseArray.at(9) = static_cast<unsigned char>(0x9f);
    serialiseArray.at(10) = static_cast<unsigned char>(0x87);
    serialiseArray.at(11) = static_cast<unsigned char>(0xb8);
    serialiseArray.at(12) = static_cast<unsigned char>(0xf0);
    serialiseArray.at(13) = static_cast<unsigned char>(0x9f);
    serialiseArray.at(14) = static_cast<unsigned char>(0x87);
    serialiseArray.at(15) = static_cast<unsigned char>(0xac);
    isValid = SGEXTN::Containers::Serialise<SGEXTN::SingText::String>::sendOut(sampleText, makeSpan(serialiseDestination, 16));
    if(isValid == false || isBitwiseIdentical(16, serialiseArray, serialiseDestination) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise sendOut SGEXTN::SingText::String fail");}
    SGEXTN::SingText::String unserialisedString;
    isValid = SGEXTN::Containers::Serialise<SGEXTN::SingText::String>::sendIn(unserialisedString, makeSpan(serialiseArray, 16));
    if(isValid == false || unserialisedString != sampleText){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise sendIn SGEXTN::SingText::String fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SingText::String>::sizeOut(sampleText) != 16){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise sizeOut SGEXTN::SingText::String fail");}
    if(SGEXTN::Containers::Serialise<SGEXTN::SingText::String>::sizeIn(makeSpan(serialiseArray, 100)) != 16){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Serialise sizeIn SGEXTN::SingText::String fail");}
    const SGEXTN::SingText::String largeString = SGEXTN::SingText::String::repeat("abcdefghij", 1000);
    for(int i=0; i<10000; i++){
        const unsigned char expected = static_cast<unsigned char>(0x61 + i % 10);
        if(largeString.getCharacterAt(i) != expected){SGEXTN_IMMEDIATE_CRASH("SGEXTN::SingText::String extended test for character indexing fail");}
    }
}
