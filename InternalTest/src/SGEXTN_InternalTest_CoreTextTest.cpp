#include <private_api/SGEXTN_InternalTest_CoreTextTest.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_CoreText_Character.h>
#include <SGEXTN_Math_FloatLimits.h>

void SGEXTN::InternalTest::CoreTextTest::testAll(){
    SGEXTN::InternalTest::CoreTextTest::testCharacter();
    SGEXTN::InternalTest::CoreTextTest::testString();
}

void SGEXTN::InternalTest::CoreTextTest::testCharacter(){
    if(SGEXTN::CoreText::Character() != SGEXTN::CoreText::Character(0x1f496)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character default value fail");}
    if(SGEXTN::CoreText::Character('A') != SGEXTN::CoreText::Character(65)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character constructor from unsigned char fail");}
    if(SGEXTN::CoreText::Character(reinterpret_cast<const char*>(u8"\U0001f496")) != SGEXTN::CoreText::Character()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character constructor from C string fail");}
    const SGEXTN::CoreText::Character a('a');
    const SGEXTN::CoreText::Character b('b');
    if(a == b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character equality check fail");}
    if(a != SGEXTN::CoreText::Character(0x61)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character inequality check fail");}
    if(b < a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character less than operator fail");}
    if(a > b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character more than operator fail");}
    if(b <= a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character less than or equal to operator fail");}
    if(a >= b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character more than or equal to operator fail");}
    SGEXTN::CoreText::Character c;
    if(c.byteLength() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character check byte length fail");}
    if(c.byteAt(3) != 0x96){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get byte at fail");}
    c.byteAt(3) = 0x97;
    if(c != SGEXTN::CoreText::Character(0x1f497)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character set byte at fail");}
    if(a.baseToAsciiChar() != 'a'){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character convert to C++ unsigned char fail");}
    if(SGEXTN::CoreText::Character('0').isDigit() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 10 fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isDigit() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 10 fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 10 fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 10 fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 10 fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 10 fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 10 fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isDigit(2) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 2 fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 2 fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 2 fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 2 fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 2 fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 2 fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isDigit(2) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 2 fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 16 fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 16 fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 16 fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 16 fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isDigit(16) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 16 fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isDigit(16) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 16 fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isDigit(16) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 16 fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 36 fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 36 fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 36 fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 36 fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 36 fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isDigit(36) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 36 fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isDigit(36) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is digit base 36 fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English lowercase fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English lowercase fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isEnglishLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English lowercase fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English lowercase fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isEnglishLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English lowercase fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English lowercase fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English lowercase fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English uppercase fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English uppercase fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English uppercase fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isEnglishUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English uppercase fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English uppercase fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isEnglishUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English uppercase fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English uppercase fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isEnglishLetter() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English letter fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isEnglishLetter() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English letter fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English letter fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English letter fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English letter fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English letter fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isEnglishLetter() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English letter fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English alphanumeric fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English alphanumeric fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English alphanumeric fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English alphanumeric fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English alphanumeric fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English alphanumeric fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isEnglishAlphanumeric() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is English alphanumeric fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is ASCII fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is ASCII fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is ASCII fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is ASCII fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is ASCII fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is ASCII fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is ASCII fail for punctuation mark");}
    if(SGEXTN::CoreText::Character().isASCII() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is ASCII fail for heart");}
    if(SGEXTN::CoreText::Character().isWhitespace() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is whitespace fail for heart");}
    if(SGEXTN::CoreText::Character("A").isWhitespace() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is whitespace fail for English letter");}
    if(SGEXTN::CoreText::Character(" ").isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is whitespace fail for space");}
    if(SGEXTN::CoreText::Character("\t").isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is whitespace fail for tab");}
    if(SGEXTN::CoreText::Character("\n").isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is whitespace fail for newline");}
    if(SGEXTN::CoreText::Character(0x2003).isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is whitespace fail for unicode space");}
    const SGEXTN::CoreText::Character cWithTail(reinterpret_cast<const char*>(u8"\u0063\u0327"));
    if(cWithTail.getBaseUnicode() != 0x63){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get base unicode fail");}
    SGEXTN::Containers::Array<int> codePoints = cWithTail.getUnicode();
    if(codePoints.length() != 2 || codePoints.at(0) != 0x63 || codePoints.at(1) != 0x327){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get unicode fail");}
    if(SGEXTN::CoreText::Character('a').isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is uppercase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').isUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is uppercase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is uppercase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).isUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is uppercase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is uppercase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is uppercase Dz fail");}
    if(SGEXTN::CoreText::Character('a').isLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is lowercase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is lowercase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).isLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is lowercase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is lowercase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is lowercase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is lowercase Dz fail");}
    if(SGEXTN::CoreText::Character('a').isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is titlecase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is titlecase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is titlecase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is titlecase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is titlecase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).isTitlecase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character is titlecase Dz fail");}
    if(SGEXTN::CoreText::Character('a').getUppercase() != SGEXTN::CoreText::Character('A')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get uppercase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').getUppercase() != SGEXTN::CoreText::Character('A')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get uppercase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).getUppercase() != SGEXTN::CoreText::Character(0x0391)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get uppercase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).getUppercase() != SGEXTN::CoreText::Character(0x0391)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get uppercase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).getUppercase() != SGEXTN::CoreText::Character(0x4e00)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get uppercase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).getUppercase() != SGEXTN::CoreText::Character(0x01c4)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get uppercase Dz fail");}
    if(SGEXTN::CoreText::Character('a').getLowercase() != SGEXTN::CoreText::Character('a')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get lowercase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').getLowercase() != SGEXTN::CoreText::Character('a')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get lowercase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).getLowercase() != SGEXTN::CoreText::Character(0x03b1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get lowercase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).getLowercase() != SGEXTN::CoreText::Character(0x03b1)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get lowercase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).getLowercase() != SGEXTN::CoreText::Character(0x4e00)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get lowercase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).getLowercase() != SGEXTN::CoreText::Character(0x01c6)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get lowercase Dz fail");}
    if(SGEXTN::CoreText::Character('a').getTitlecase() != SGEXTN::CoreText::Character('A')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get titlecase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').getTitlecase() != SGEXTN::CoreText::Character('A')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get titlecase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).getTitlecase() != SGEXTN::CoreText::Character(0x0391)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get titlecase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).getTitlecase() != SGEXTN::CoreText::Character(0x0391)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get titlecase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).getTitlecase() != SGEXTN::CoreText::Character(0x4e00)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get titlecase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).getTitlecase() != SGEXTN::CoreText::Character(0x01c5)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get titlecase Dz fail");}
    if(SGEXTN::CoreText::Character('0').getDecimalDigitValue() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get decimal digit value digit zero fail");}
    if(SGEXTN::CoreText::Character(0x0be6).getDecimalDigitValue() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get decimal digit value Tamil digit zero fail");}
    if(SGEXTN::CoreText::Character(' ').getDecimalDigitValue() != -1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get decimal digit value space fail");}
    if(SGEXTN::CoreText::Character(0xbd).getDecimalDigitValue() != -1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get decimal digit value half fraction fail");}
    if(SGEXTN::CoreText::Character('0').getNumericalValue() != 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get numerical value digit zero fail");}
    if(SGEXTN::CoreText::Character(0x0be6).getNumericalValue() != 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get numerical value Tamil digit zero fail");}
    if(SGEXTN::CoreText::Character(' ').getNumericalValue() != SGEXTN::Math::FloatLimits<float>::negativeInfinity()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get numerical value space fail");}
    if(SGEXTN::CoreText::Character(0xbd).getNumericalValue() != 0.5f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::Character get numerical value half fraction fail");}
}

#define U8(str) reinterpret_cast<const char*>(u8##str)
void SGEXTN::InternalTest::CoreTextTest::testString(){
    SGEXTN::CoreText::String a('a');
    const SGEXTN::CoreText::String b("b");
    if(b != SGEXTN::CoreText::String('b')){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String constructor from C++ unsigned char fail");}
    if(a != SGEXTN::CoreText::String("a")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String constructor from C string fail");}
    if(a != SGEXTN::CoreText::String(SGEXTN::CoreText::Character('a'))){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String constructor from SGEXTN character fail");}
    if(a == b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String equality check fail");}
    if((a != b) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String inequality check fail");}
    if(b < a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String less than operator fail");}
    if(a > b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String more than operator fail");}
    if(b <= a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String less than or equal to operator fail");}
    if(a >= b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String more than or equal to operator fail");}
    if(a + b != "ab"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String string addition fail");}
    a += b;
    if(a != "ab"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String string addition assignment fail");}
    SGEXTN::CoreText::String aAlphaSpaceEpsilonA = U8("\u0061\u03b1\u0301\u0020\u03c3\u0041");
    if(aAlphaSpaceEpsilonA.byteLength() != 9){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check  byte length fail");}
    if(aAlphaSpaceEpsilonA.characterLength() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check character length fail");}
    if(aAlphaSpaceEpsilonA.byteAt(8) != 'A'){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String get byte at fail");}
    aAlphaSpaceEpsilonA.byteAt(8) = 'B';
    if(aAlphaSpaceEpsilonA.byteAt(8) != 'B'){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String set byte at fail");}
    if(aAlphaSpaceEpsilonA.getCharacterAt(1) != U8("\u03b1\u0301")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String get character at fail");}
    aAlphaSpaceEpsilonA.setCharacterAt(1, U8("\u03b1\u0300"));
    if(aAlphaSpaceEpsilonA.getCharacterAt(1) != U8("\u03b1\u0300")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String set character same length fail");}
    aAlphaSpaceEpsilonA.setCharacterAt(4, U8("\uff21"));
    if(aAlphaSpaceEpsilonA.getCharacterAt(4) != SGEXTN::CoreText::Character(0xff21)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String set character different length fail");}
    if(aAlphaSpaceEpsilonA.fillBytes('0') != "00000000000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill bytes fail");}
    if(aAlphaSpaceEpsilonA.fillCharacters(U8("\u03b1\u0301")) != U8("\u03b1\u0301\u03b1\u0301\u03b1\u0301\u03b1\u0301\u03b1\u0301")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill characters fail");}
    SGEXTN::CoreText::String bytesFindString = "__ab_aab_abb";
    if(bytesFindString.findFirstBytesFromLeft("ab") != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String find bytes from left fail");}
    if(bytesFindString.findFirstBytesFromRight("ab") != 9){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String find bytes from right fail");}
    if(bytesFindString.findFirstBytesFromLeftBounded(3, "ab") != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String find bytes from left bounded fail");}
    if(bytesFindString.findFirstBytesFromRightBounded(8, "ab") != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String find bytes from right bounded fail");}
    SGEXTN::CoreText::String charactersFindString = U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2");
    if(charactersFindString.findFirstCharactersFromLeft(U8("\u03b1\u0300\u03b2")) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String find characters from left fail");}
    if(charactersFindString.findFirstCharactersFromRight(U8("\u03b1\u0300\u03b2")) != 9){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String find characters from right fail");}
    if(charactersFindString.findFirstCharactersFromLeftBounded(3, U8("\u03b1\u0300\u03b2")) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String find characters from left bounded fail");}
    if(charactersFindString.findFirstCharactersFromRightBounded(8, U8("\u03b1\u0300\u03b2")) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String find characters from right bounded fail");}
    if(bytesFindString.substringBytes(5, 3) != "aab"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String substring bytes fail");}
    if(bytesFindString.substringBytesLeft(3) != "__a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String substring bytes left fail");}
    if(bytesFindString.substringBytesRight(3) != "abb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String substring bytes right fail");}
    if(charactersFindString.substringCharacters(5, 3) != U8("\u03b1\u0300\u03b1\u0300\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String substring characters fail");}
    if(charactersFindString.substringCharactersLeft(3) != U8("\u0020\u0020\u03b1\u0300")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String substring characters left fail");}
    if(charactersFindString.substringCharactersRight(3) != U8("\u03b1\u0300\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String substring characters right fail");}
    if(bytesFindString.replaceBytes("ab", 'c') != "__c_ac_cb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String replace bytes fail");}
    if(charactersFindString.replaceCharacters(U8("\u03b1\u0300\u03b2"), U8("\u03b3")) != U8("\u0020\u0020\u03b3\u0020\u03b1\u0300\u03b3\u0020\u03b3\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String replace characters fail");}
    if(bytesFindString.removeBytes("ab") != "___a_b"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String remove bytes fail");}
    if(charactersFindString.removeCharacters(U8("\u03b1\u0300\u03b2")) != U8("\u0020\u0020\u0020\u03b1\u0300\u0020\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String remove characters fail");}
    if(bytesFindString.insertAtByteIndex(0, "cc") != "cc__ab_aab_abb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String insert bytes at start fail");}
    if(bytesFindString.insertAtByteIndex(2, "cc") != "__ccab_aab_abb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String insert bytes at middle fail");}
    if(bytesFindString.insertAtByteIndex(12, "cc") != "__ab_aab_abbcc"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String insert bytes at end fail");}
    if(charactersFindString.insertAtCharacterIndex(0, U8("\u03b3\u03b3")) != U8("\u03b3\u03b3\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String insert characters at start fail");}
    if(charactersFindString.insertAtCharacterIndex(2, U8("\u03b3\u03b3")) != U8("\u0020\u0020\u03b3\u03b3\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String insert characters at middle fail");}
    if(charactersFindString.insertAtCharacterIndex(12, U8("\u03b3\u03b3")) != U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2\u03b3\u03b3")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String insert characters at end fail");}
    if(bytesFindString.removeAtByteIndex(5, 3) != "__ab__abb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String remove bytes fail");}
    if(charactersFindString.removeAtCharacterIndex(5, 3) != U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String remove characters fail");}
    if(bytesFindString.containsBytes("ab") == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check if contains existing bytes fail");}
    if(bytesFindString.containsBytes("bc") == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check if contains nonexistent bytes fail");}
    if(charactersFindString.containsCharacters(U8("\u03b1\u0300\u03b2")) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check if contains existing characters fail");}
    if(charactersFindString.containsCharacters(U8("\u0300\u03b2")) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check if contains nonexistent characters fail");}
    if(bytesFindString.startsWithBytes("__") == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check start bytes with matched prefix fail");}
    if(bytesFindString.startsWithBytes("_a") == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check start bytes with unmatched prefix fail");}
    if(charactersFindString.startsWithCharacters(U8("\u0020\u0020")) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check start characters with matched prefix fail");}
    if(charactersFindString.startsWithCharacters(U8("\u0020\u03b1\u0300")) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check start characters with unmatched prefix fail");}
    if(bytesFindString.endsWithBytes("bb") == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check end bytes with matched prefix fail");}
    if(bytesFindString.endsWithBytes("ab") == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check end bytes with unmatched prefix fail");}
    if(charactersFindString.endsWithCharacters(U8("\u03b2\u03b2")) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check end characters with matched prefix fail");}
    if(charactersFindString.endsWithCharacters(U8("\u03b1\u0300\u03b2")) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check end characters with unmatched prefix fail");}
    bytesFindString = SGEXTN::CoreText::String::repeat("a", 7);
    charactersFindString = SGEXTN::CoreText::String::repeat(U8("\u03b1\u0300"), 7);
    if(charactersFindString != U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String repeat given string fail");}
    if(bytesFindString.countBytes("aaa") != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String count bytes no overlap fail");}
    if(charactersFindString.countCharacters(U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300")) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String count characters no overlap fail");}
    if(bytesFindString.countBytesAllowOverlap("aaa") != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String count bytes allow overlap fail");}
    if(charactersFindString.countCharactersAllowOverlap(U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300")) != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String count characters allow overlap fail");}
    if(bytesFindString.fillLeftToByteLength(5, 'b') != bytesFindString){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill left bytes sufficient length fail");}
    if(bytesFindString.fillLeftToByteLength(10, 'b') != "bbbaaaaaaa"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill left bytes insufficient length fail");}
    if(charactersFindString.fillLeftToCharacterLength(5, U8("\u03b2")) != charactersFindString){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill left characters sufficient length fail");}
    if(charactersFindString.fillLeftToCharacterLength(10, U8("\u03b2")) != U8("\u03b2\u03b2\u03b2\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill left characters insufficient length fail");}
    if(bytesFindString.fillRightToByteLength(5, 'b') != bytesFindString){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill right bytes sufficient length fail");}
    if(bytesFindString.fillRightToByteLength(10, 'b') != "aaaaaaabbb"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill right bytes insufficient length fail");}
    if(charactersFindString.fillRightToCharacterLength(5, U8("\u03b2")) != charactersFindString){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill right characters sufficient length fail");}
    if(charactersFindString.fillRightToCharacterLength(10, U8("\u03b2")) != U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b2\u03b2\u03b2")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String fill right characters insufficient length fail");}
    if(charactersFindString.byteIndexToCharacterIndex(1) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String convert byte index to character index fail");}
    if(charactersFindString.characterIndexToByteIndex(1) != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String convert character index to byte index fail");}
    SGEXTN::CoreText::String positiveBase10Number = "26";
    SGEXTN::CoreText::String negativeBase10Number = "-26";
    SGEXTN::CoreText::String positiveBase16Number = "1a";
    SGEXTN::CoreText::String negativeBase16Number = "-1A";
    SGEXTN::CoreText::String positiveNonLatinNumber = U8("\u0be8\u0bec");
    SGEXTN::CoreText::String negativeNonLatinNumber = U8("\u002d\u0be8\u0bec");
    SGEXTN::CoreText::String invalidNumber = "2 6";
    bool isValid = false;
    if(positiveBase10Number.parseToShort(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 10 number to short fail");}
    isValid = false;
    if(negativeBase10Number.parseToShort(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 10 number to short fail");}
    isValid = false;
    if(positiveBase16Number.parseToShort(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 16 number to short fail");}
    isValid = false;
    if(negativeBase16Number.parseToShort(&isValid, 16) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 16 number to short fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToShort(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive non Latin number to short fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToShort(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative non Latin number to short fail");}
    isValid = true;
    if(invalidNumber.parseToShort(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to short fail");}
    if(invalidNumber.parseToShort(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to short no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedShort(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 10 number to unsigned short fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedShort(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 16 number to unsigned short fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedShort(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive non Latin number to unsigned short fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedShort(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to unsigned short fail");}
    if(invalidNumber.parseToUnsignedShort(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to unsigned short no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToInt(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 10 number to int fail");}
    isValid = false;
    if(negativeBase10Number.parseToInt(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 10 number to int fail");}
    isValid = false;
    if(positiveBase16Number.parseToInt(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 16 number to int fail");}
    isValid = false;
    if(negativeBase16Number.parseToInt(&isValid, 16) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 16 number to int fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToInt(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive non Latin number to int fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToInt(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative non Latin number to int fail");}
    isValid = true;
    if(invalidNumber.parseToInt(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to int fail");}
    if(invalidNumber.parseToInt(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to int no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedInt(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 10 number to unsigned int fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedInt(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 16 number to unsigned int fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedInt(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive non Latin number to unsigned int fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedInt(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to unsigned int fail");}
    if(invalidNumber.parseToUnsignedInt(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to unsigned int no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 10 number to long long fail");}
    isValid = false;
    if(negativeBase10Number.parseToLongLong(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 10 number to long long fail");}
    isValid = false;
    if(positiveBase16Number.parseToLongLong(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 16 number to long long fail");}
    isValid = false;
    if(negativeBase16Number.parseToLongLong(&isValid, 16) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 16 number to long long fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive non Latin number to long long fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToLongLong(&isValid, 10) != -26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative non Latin number to long long fail");}
    isValid = true;
    if(invalidNumber.parseToLongLong(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to long long fail");}
    if(invalidNumber.parseToLongLong(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to long long no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 10 number to unsigned long long fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedLongLong(&isValid, 16) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 16 number to unsigned long long fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive non Latin number to unsigned long long fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedLongLong(&isValid, 10) != 0 || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to unsigned long long fail");}
    if(invalidNumber.parseToUnsignedLongLong(nullptr, 10) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to unsigned long long no success flag fail");}
    positiveBase10Number = "10.5";
    negativeBase10Number = "-010.500";
    const SGEXTN::CoreText::String positiveScientificNotation = "5^-1";
    const SGEXTN::CoreText::String negativeScientificNotation = "-5.0^-01";
    positiveBase16Number = "a.8";
    negativeBase16Number = "-0a.80";
    positiveNonLatinNumber = U8("\u0be6\u002e\u0beb");
    negativeNonLatinNumber = U8("\u002d\u0be6\u0be6\u002e\u0beb\u0be6");
    invalidNumber = "-+0.5";
    isValid = false;
    if(positiveBase10Number.parseToFloat(&isValid, 10) != 10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 10 number to float fail");}
    isValid = false;
    if(negativeBase10Number.parseToFloat(&isValid, 10) != -10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 10 number to float fail");}
    isValid = false;
    if(positiveScientificNotation.parseToFloat(&isValid, 10) != 0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive scientific notation number to float fail");}
    isValid = false;
    if(negativeScientificNotation.parseToFloat(&isValid, 10) != -0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative scientific notation number to float fail");}
    isValid = false;
    if(positiveBase16Number.parseToFloat(&isValid, 16) != 10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 16 number to float fail");}
    isValid = false;
    if(negativeBase16Number.parseToFloat(&isValid, 16) != -10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 16 number to float fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToFloat(&isValid, 10) != 0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive non Latin number to float fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToFloat(&isValid, 10) != -0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative non Latin number to float fail");}
    isValid = true;
    if(invalidNumber.parseToFloat(&isValid, 10) != 0.0f || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to float fail");}
    if(invalidNumber.parseToFloat(nullptr, 10) != 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to float no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToDouble(&isValid, 10) != 10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 10 number to double fail");}
    isValid = false;
    if(negativeBase10Number.parseToDouble(&isValid, 10) != -10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 10 number to double fail");}
    isValid = false;
    if(positiveScientificNotation.parseToDouble(&isValid, 10) != 0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive scientific notation number to double fail");}
    isValid = false;
    if(negativeScientificNotation.parseToDouble(&isValid, 10) != -0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative scientific notation number to double fail");}
    isValid = false;
    if(positiveBase16Number.parseToDouble(&isValid, 16) != 10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive base 16 number to double fail");}
    isValid = false;
    if(negativeBase16Number.parseToDouble(&isValid, 16) != -10.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative base 16 number to double fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToDouble(&isValid, 10) != 0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse positive non Latin number to double fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToDouble(&isValid, 10) != -0.5f || isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse negative non Latin number to double fail");}
    isValid = true;
    if(invalidNumber.parseToDouble(&isValid, 10) != 0.0f || isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to double fail");}
    if(invalidNumber.parseToDouble(nullptr, 10) != 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String parse invalid number to double no success flag fail");}
    if(SGEXTN::CoreText::String::stringFromShort(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print short positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromShort(-26, 10) != "-26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print short negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromShort(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print short positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromShort(-26, 16) != "-1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print short negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedShort(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print unsigned short positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedShort(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print unsigned short positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromInt(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print int positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromInt(-26, 10) != "-26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print int negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromInt(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print int positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromInt(-26, 16) != "-1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print int negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedInt(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print unsigned int positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedInt(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print unsigned int positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromLongLong(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print long long positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromLongLong(-26, 10) != "-26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print long long negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromLongLong(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print long long positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromLongLong(-26, 16) != "-1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print long long negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedLongLong(26, 10) != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print unsigned long long positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedLongLong(26, 16) != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print unsigned long long positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "10.333"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float decimal place mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "-10.333"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float decimal place mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "a.555"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float decimal place mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "-a.555"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float decimal place mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "10.3"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float significant figures mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "-10.3"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float significant figures mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "a.55"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float significant figures mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "-a.55"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float significant figures mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "1.03^1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float scientific notation mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-1.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "-3.33^-1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float scientific notation mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "a.55^0"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float scientific notation mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-1.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "-5.55^-1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print float scientific notation mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "10.333"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double decimal place mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "-10.333"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double decimal place mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "a.555"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double decimal place mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "-a.555"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double decimal place mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "10.3"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double significant figures mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "-10.3"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double significant figures mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "a.55"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double significant figures mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "-a.55"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double significant figures mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "1.03^1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double scientific notation mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-1.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "-3.33^-1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double scientific notation mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "a.55^0"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double scientific notation mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-1.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "-5.55^-1"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String print double scientific notation mode negative base 16 fail");}
    if(SGEXTN::CoreText::String("-1.23^+09").prettierScientificNotationBase10() != U8("-1.23\u00d710\u2079")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String make scientific notation prettier fail");}
    if(SGEXTN::CoreText::String("12345").convertNumericSystem(0xbe6) != U8("\u0be7\u0be8\u0be9\u0bea\u0beb")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String convert to non Latin numbers fail");}
    if(SGEXTN::CoreText::String("<b> & </b>#").prepareInnerHtmlText() != "&lt;b&gt; &amp; &lt;/b&gt;#"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String HTML escaping fail");}
    if(SGEXTN::CoreText::String("  te xt \t\n  \n \t ").removeLeadingTrailingWhitespace() != "te xt"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String whitespace trimming fail");}
    if(SGEXTN::CoreText::String(" a b \nc\t\t\td    e \n \tfgh   ").cleanWhitespace() != "a b c d e fgh"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String whitespace cleaning fail");}
    if(SGEXTN::CoreText::String(" a b \nc\t\t\td    e \n \tfgh   ").removeAllWhitespace() != "abcdefgh"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String whitespace removal fail");}
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> testSplitString = SGEXTN::CoreText::String(",a, bc, \n\td,,, ,e").split(',');
    if(testSplitString.length() != 8 || testSplitString.at(0) != "" || testSplitString.at(1) != "a" || testSplitString.at(2) != " bc" || testSplitString.at(3) != " \n\td" || testSplitString.at(4) != "" || testSplitString.at(5) != "" || testSplitString.at(6) != " " || testSplitString.at(7) != "e"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String split string fail");}
    if(SGEXTN::CoreText::String("0123456789").isDigit() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check digit base 10 true fail");}
    if(SGEXTN::CoreText::String("0123456789a").isDigit() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check digit base 10 false fail");}
    if(SGEXTN::CoreText::String("0123456789abcdefABCDEF").isDigit(16) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check digit base 16 true fail");}
    if(SGEXTN::CoreText::String("0123456789abcdefg").isDigit(16) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check digit base 16 false fail");}
    if(SGEXTN::CoreText::String("qwerty").isEnglishLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check English lowercase true fail");}
    if(SGEXTN::CoreText::String("qwertY").isEnglishLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check English lowercase false fail");}
    if(SGEXTN::CoreText::String("QWERTY").isEnglishUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check English uppercase true fail");}
    if(SGEXTN::CoreText::String("QWERTy").isEnglishUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check English uppercase false fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty").isEnglishLetter() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check English letter true fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty0").isEnglishLetter() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check English letter false fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty0123456789").isEnglishAlphanumeric() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check English alphanumeric true fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty0123456789 ").isEnglishAlphanumeric() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check English alphanumeric false fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty0123456789,.<> ").isASCII() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check ASCII true fail");}
    if((SGEXTN::CoreText::String("QWERTYqwerty0123456789,.<> ") + SGEXTN::CoreText::Character(0xbe6)).isASCII() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check ASCII false fail");}
    if(SGEXTN::CoreText::String(" \t\n").isWhitespace() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check whitespace true fail");}
    if(SGEXTN::CoreText::String(" \t\n0").isWhitespace() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check whitespace false fail");}
    if(SGEXTN::CoreText::String(U8("A \u0391\u0300_.")).isUppercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check uppercase true fail");}
    if(SGEXTN::CoreText::String(U8("A \u0391\u0300_.a")).isUppercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check uppercase false fail");}
    if(SGEXTN::CoreText::String(U8("a \u03b1\u0300_.")).isLowercase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check lowercase true fail");}
    if(SGEXTN::CoreText::String(U8("a \u03b1\u0300_.A")).isLowercase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check lowercase false fail");}
    if(SGEXTN::CoreText::String(U8("A \u0391\u0300_.\u01c5")).isTitlecase() == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check titlecase true fail");}
    if(SGEXTN::CoreText::String(U8("A \u0391\u0300_.\u01c4")).isTitlecase() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String check titlecase false fail");}
    const SGEXTN::CoreText::String changeCaseTestString = U8(" ./aA\u0391\u03b1\u0300\u01c4\u01c5\u01c6\u4000");
    if(changeCaseTestString.getUppercase() != U8(" ./AA\u0391\u0391\u0300\u01c4\u01c4\u01c4\u4000")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String convert to uppercase fail");}
    if(changeCaseTestString.getLowercase() != U8(" ./aa\u03b1\u03b1\u0300\u01c6\u01c6\u01c6\u4000")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String convert to uppercase fail");}
    if(changeCaseTestString.getTitlecase() != U8(" ./AA\u0391\u0391\u0300\u01c5\u01c5\u01c5\u4000")){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String convert to uppercase fail");}
    SGEXTN::Containers::Array<int> unicodeCodePoints = changeCaseTestString.getUnicode();
    SGEXTN::Containers::Array<int> expectedCodePoints = SGEXTN::Containers::Array<int>(0x20, 0x2e, 0x2f, 0x61, 0x41, 0x391, 0x3b1, 0x300, 0x1c4, 0x1c5, 0x1c6, 0x4000);
    if(unicodeCodePoints.length() != expectedCodePoints.length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String extract Unicode code points fail");}
    for(int i=0; i<unicodeCodePoints.length(); i++){
        if(unicodeCodePoints.at(i) != expectedCodePoints.at(i)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String extract Unicode code points fail");}
    }
    const SGEXTN::CoreText::String unsimplifiedString = U8("Caf\u00e8 at Yishun \uff2d\uff32\uff34 \u2122 \n\t \U0001d4a9\U0001d4ae\u2081\u2081");
    if(unsimplifiedString.getSimplestEquivalent(false) != "Cafe at Yishun MRT TM NS11"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String case sensitive simplest string conversion fail");}
    if(unsimplifiedString.getSimplestEquivalent(true) != "cafe at yishun mrt tm ns11"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreText::String case insensitive simplest string conversion fail");}
}
#undef U8