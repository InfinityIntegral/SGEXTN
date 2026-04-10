#include <private_api/SGEXTN_ApplicationBase_UnitTests.h>
#include <SGEXTN_ApplicationBase_OldChar.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_ApplicationBase_OldString.h>
#include <SGEXTN_Containers_Array.h>

void SGEXTN::ApplicationBase::UnitTests::testChar(){
    if(SGEXTN::ApplicationBase::OldChar(65) != SGEXTN::ApplicationBase::OldChar('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - constructor fail");}
    if(SGEXTN::ApplicationBase::OldChar('a') >= SGEXTN::ApplicationBase::OldChar('b')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - comparison fail");}
    const SGEXTN::ApplicationBase::OldChar uppercaseA('A');
    if(uppercaseA.toChar() != 'A'){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - to char fail");}
    if(uppercaseA.toSignedChar() != static_cast<signed char>(65)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - to signed char fail");}
    if(uppercaseA.toUnsignedChar() != static_cast<unsigned char>(65)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - to unsigned char fail");}
    if(SGEXTN::ApplicationBase::OldChar('0').isDigit() == false || SGEXTN::ApplicationBase::OldChar('.').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - is digit fail");}
    if(SGEXTN::ApplicationBase::OldChar('0').isDigitBase16() == false || SGEXTN::ApplicationBase::OldChar('.').isDigitBase16() == true || SGEXTN::ApplicationBase::OldChar('a').isDigitBase16() == false || SGEXTN::ApplicationBase::OldChar('A').isDigitBase16() == false || SGEXTN::ApplicationBase::OldChar('G').isDigitBase16() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - is digit base 16 fail");}
    if(SGEXTN::ApplicationBase::OldChar('0').isEnglishLowercase() == true || SGEXTN::ApplicationBase::OldChar('.').isEnglishLowercase() == true || SGEXTN::ApplicationBase::OldChar('a').isEnglishLowercase() == false || SGEXTN::ApplicationBase::OldChar('A').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - is English lowercase fail");}
    if(SGEXTN::ApplicationBase::OldChar('0').isEnglishUppercase() == true || SGEXTN::ApplicationBase::OldChar('.').isEnglishUppercase() == true || SGEXTN::ApplicationBase::OldChar('a').isEnglishUppercase() == true || SGEXTN::ApplicationBase::OldChar('A').isEnglishUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - is English uppercase fail");}
    if(SGEXTN::ApplicationBase::OldChar('0').isEnglishLetter() == true || SGEXTN::ApplicationBase::OldChar('.').isEnglishLetter() == true || SGEXTN::ApplicationBase::OldChar('a').isEnglishLetter() == false || SGEXTN::ApplicationBase::OldChar('A').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - is English letter fail");}
    if(SGEXTN::ApplicationBase::OldChar('0').isEnglishAlphanumeric() == false || SGEXTN::ApplicationBase::OldChar('.').isEnglishAlphanumeric() == true || SGEXTN::ApplicationBase::OldChar('a').isEnglishAlphanumeric() == false || SGEXTN::ApplicationBase::OldChar('A').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - is English alphanumeric fail");}
    if(SGEXTN::ApplicationBase::OldChar(129).isASCII() == true || SGEXTN::ApplicationBase::OldChar('A').isASCII() == false || SGEXTN::ApplicationBase::OldChar('~').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - is ASCII fail");}
    if(SGEXTN::ApplicationBase::OldChar(' ').isWhitespace() == false || SGEXTN::ApplicationBase::OldChar('\t').isWhitespace() == false || SGEXTN::ApplicationBase::OldChar('\n').isWhitespace() == false || SGEXTN::ApplicationBase::OldChar('.').isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - is whitespace fail");}
    if(SGEXTN::ApplicationBase::OldChar('A').getUnicode() != 65){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - get unicode fail");}
    if(SGEXTN::ApplicationBase::OldChar('.').lowercaseLanguageAware() != SGEXTN::ApplicationBase::OldChar('.') || SGEXTN::ApplicationBase::OldChar('A').lowercaseLanguageAware() != SGEXTN::ApplicationBase::OldChar('a')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - get lowercase fail");}
    if(SGEXTN::ApplicationBase::OldChar('.').uppercaseLanguageAware() != SGEXTN::ApplicationBase::OldChar('.') || SGEXTN::ApplicationBase::OldChar('a').uppercaseLanguageAware() != SGEXTN::ApplicationBase::OldChar('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldChar - get uppercase fail");}
}

void SGEXTN::ApplicationBase::UnitTests::testString(){
    if(SGEXTN::ApplicationBase::OldString("test") != "test"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - constructor from C string crashed");}
    if(SGEXTN::ApplicationBase::OldString(SGEXTN::ApplicationBase::OldChar('A')) != "A"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - constructor from char failed");}
    if(SGEXTN::ApplicationBase::OldString("A") >= SGEXTN::ApplicationBase::OldString("B")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - comparator for non overlapping strings fail");}
    if(SGEXTN::ApplicationBase::OldString("AC") <= SGEXTN::ApplicationBase::OldString("AB")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - comparator for strings with common substring fail");}
    if(SGEXTN::ApplicationBase::OldString("AZ") > SGEXTN::ApplicationBase::OldString("BY")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - comparator priority based on order of characters fail");}
    if(SGEXTN::ApplicationBase::OldString("a") < SGEXTN::ApplicationBase::OldString("B")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - comparator unicode compliance fail");}
    if(SGEXTN::ApplicationBase::OldString("") >= SGEXTN::ApplicationBase::OldString("A")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - comparator empty substring fail");}
    if(SGEXTN::ApplicationBase::OldString("A") >= SGEXTN::ApplicationBase::OldString("AA")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - comparator non empty substring fail");}
    if(SGEXTN::ApplicationBase::OldString("A") + SGEXTN::ApplicationBase::OldString("B") != "AB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string addition fail");}
    SGEXTN::ApplicationBase::OldString s("A");
    s += "B";
    if(s != "AB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string addition assign fail");}
    s = "SGEXTN";
    if(s.getCharAt(0) != 'S' || s.getCharAt(1) != 'G' || s.getCharAt(2) != 'E' || s.getCharAt(3) != 'X' || s.getCharAt(4) != 'T' || s.getCharAt(5) != 'N'){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - get char at index fail");}
    s.setCharAt(5, '.');
    if(s != "SGEXT."){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - set char at index fail");}
    if(s.length() != 6){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - length check fail");}
    s = "ABCABACABAB";
    if(s.replace("AB", ".") != ".C.AC.."){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - replace string fail");}
    if(s.insert(0, "D") != "DABCABACABAB" || s.insert(11, "D") != "ABCABACABABD" || s.insert(5, "D") != "ABCABDACABAB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - insert string fail");}
    if(s.contains("A") == false || s.contains("D") == true || s.contains("AB") == false || s.contains("AD") == true || s.contains("CB") == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - contains check fail");}
    if(s.findFirstFromLeft("AB") != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - find first from left fail");}
    if(s.findFirstFromRight("AB") != 9){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - find first from right fail");}
    if(s.findFirstFromLeftCustomStart("AB", 2) != 3 || s.findFirstFromLeftCustomStart("AB", 3) != 3 || s.findFirstFromLeftCustomStart("AB", 4) != 7){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - find first from left custom start fail");}
    if(s.findFirstFromRightCustomStart("AB", 2) != 0 || s.findFirstFromRightCustomStart("AB", 3) != 3 || s.findFirstFromRightCustomStart("AB", 4) != 3){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - find first from right custom start fail");}
    if(s.count("AB") != 4 || s.count("A") != 5){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - count instance of substring fail");}
    if(s.substring(1, 5) != "BCABA"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - substring fail");}
    if(s.substringLeft(5) != "ABCAB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - substring left fail");}
    if(s.substringRight(5) != "CABAB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - substring right fail");}
    s = "26";
    if(s.fillLeftToLength(1, '0') != "26" || s.fillLeftToLength(4, '0') != "0026"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - fill left to length fail");}
    if(s.fillRightToLength(1, '0') != "26" || s.fillRightToLength(4, '0') != "2600"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - fill right to length fail");}
    bool ok = false;
    if(SGEXTN::ApplicationBase::OldString("26").parseToInt(nullptr, 10) != 26){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse positive int fail");}
    if(SGEXTN::ApplicationBase::OldString("26").parseToInt(&ok, 10) != 26 || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse positive int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("-26").parseToInt(nullptr, 10) != -26){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse negative int fail");}
    if(SGEXTN::ApplicationBase::OldString("-26").parseToInt(&ok, 10) != -26 || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse negative int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("26").parseToUnsignedInt(nullptr, 10) != 26u){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse positive unsigned int fail");}
    if(SGEXTN::ApplicationBase::OldString("26").parseToUnsignedInt(&ok, 10) != 26u || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse positive unsigned int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("-26").parseToUnsignedInt(nullptr, 10) != 0u){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse negative int to unsigned int fail");}
    if(SGEXTN::ApplicationBase::OldString("-26").parseToUnsignedInt(&ok, 10) != 0u || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse negative int to unsigned int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("2a").parseToInt(nullptr, 16) != 42){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse base 16 positive int fail");}
    if(SGEXTN::ApplicationBase::OldString("2a").parseToInt(&ok, 16) != 42 || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse base 16 positive int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("-2a").parseToInt(nullptr, 16) != -42){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse base 16 negative int fail");}
    if(SGEXTN::ApplicationBase::OldString("-2a").parseToInt(&ok, 16) != -42 || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse base 16 negative int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("2a").parseToUnsignedInt(nullptr, 16) != 42u){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse base 16 positive unsigned int fail");}
    if(SGEXTN::ApplicationBase::OldString("2a").parseToUnsignedInt(&ok, 16) != 42u || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse base 16 positive unsigned int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("-2a").parseToUnsignedInt(nullptr, 16) != 0u){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse base 16 negative int to unsigned int fail");}
    if(SGEXTN::ApplicationBase::OldString("-2a").parseToUnsignedInt(&ok, 16) != 0u || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse base 16 negative int to unsigned int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("").parseToInt(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse empty string to int fail");}
    if(SGEXTN::ApplicationBase::OldString("").parseToInt(&ok, 10) != 0 || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse empty string to int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("aaaaa").parseToInt(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse nonsensical string to int fail");}
    if(SGEXTN::ApplicationBase::OldString("aaaaa").parseToInt(&ok, 10) != 0 || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse nonsensical string to int with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("26").parseToFloat(nullptr) != 26.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse positive int to float fail");}
    if(SGEXTN::ApplicationBase::OldString("26").parseToFloat(&ok) != 26.0f || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse positive int to float with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("-26").parseToFloat(nullptr) != -26.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse negative int to float fail");}
    if(SGEXTN::ApplicationBase::OldString("-26").parseToFloat(&ok) != -26.0f || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse negative int to float with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("0.26").parseToFloat(nullptr) != 0.26f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse positive float fail");}
    if(SGEXTN::ApplicationBase::OldString("0.26").parseToFloat(&ok) != 0.26f || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse positive float with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("-0.26").parseToFloat(nullptr) != -0.26f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse negative float fail");}
    if(SGEXTN::ApplicationBase::OldString("-0.26").parseToFloat(&ok) != -0.26f || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse negative float with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("").parseToFloat(nullptr) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse empty string to float fail");}
    if(SGEXTN::ApplicationBase::OldString("").parseToFloat(&ok) != 0 || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse empty string to float with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString("aaaaa").parseToFloat(nullptr) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse nonsensical string to float fail");}
    if(SGEXTN::ApplicationBase::OldString("aaaaa").parseToFloat(&ok) != 0 || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - parse nonsensical string to float with error checking fail");}
    if(SGEXTN::ApplicationBase::OldString::stringFromInt(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string from positive int fail");}
    if(SGEXTN::ApplicationBase::OldString::stringFromInt(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string from base 16 positive int fail");}
    if(SGEXTN::ApplicationBase::OldString::stringFromInt(-26, 10) != "-26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string from positive int fail");}
    if(SGEXTN::ApplicationBase::OldString::stringFromInt(-26, 16) != "-1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string from base 16 positive int fail");}
    if(SGEXTN::ApplicationBase::OldString::stringFromFloat(26.060f, SGEXTN::ApplicationBase::FloatDisplayFormat::Default, 5) != "26.06"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string from float default formatting fail");}
    if(SGEXTN::ApplicationBase::OldString::stringFromFloat(26.060f, SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 5) != "26.06000"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string from float decimal place formatting fail");}
    if(SGEXTN::ApplicationBase::OldString::stringFromFloat(26.060f, SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, -1) != "30"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string from float decimal place formatting with rounding fail");}
    if(SGEXTN::ApplicationBase::OldString::stringFromFloat(26.060f, SGEXTN::ApplicationBase::FloatDisplayFormat::ScientificNotation, 5) != "2.6060e+01"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - string from float scientific notation formatting fail");}
    if(SGEXTN::ApplicationBase::OldString::repeatChar('x', 0) != "" || SGEXTN::ApplicationBase::OldString::repeatChar('x', 3) != "xxx"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - repeat char fail");}
    s = " t\te\nst \t";
    if(s.removeLeadingTrailingWhitespace() != "t\te\nst"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - remove leading trailing whitespace fail");}
    if(s.cleanWhitespace() != "t e st"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - clean whitespace fail");}
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::OldString> separatedString = s.cleanWhitespace().split(" ");
    if(separatedString.length() != 3 || separatedString.at(0) != "t" || separatedString.at(1) != "e" || separatedString.at(2) != "st"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - split string fail");}
    if(SGEXTN::ApplicationBase::OldString("00").isDigit() == false || SGEXTN::ApplicationBase::OldString("0x").isDigit() == true || SGEXTN::ApplicationBase::OldString("xx").isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - is digit fail");}
    if(SGEXTN::ApplicationBase::OldString("aa").isDigitBase16() == false || SGEXTN::ApplicationBase::OldString("ax").isDigitBase16() == true || SGEXTN::ApplicationBase::OldString("xx").isDigitBase16() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - is digit base 16 fail");}
    if(SGEXTN::ApplicationBase::OldString("aa").isEnglishLowercase() == false || SGEXTN::ApplicationBase::OldString("aA").isEnglishLowercase() == true || SGEXTN::ApplicationBase::OldString("AA").isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - is English lowercase fail");}
    if(SGEXTN::ApplicationBase::OldString("AA").isEnglishUppercase() == false || SGEXTN::ApplicationBase::OldString("Aa").isEnglishUppercase() == true || SGEXTN::ApplicationBase::OldString("aa").isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - is English uppercase fail");}
    if(SGEXTN::ApplicationBase::OldString("xx").isEnglishLetter() == false || SGEXTN::ApplicationBase::OldString("0x").isEnglishLetter() == true || SGEXTN::ApplicationBase::OldString("00").isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - is English letter fail");}
    if(SGEXTN::ApplicationBase::OldString("0a").isEnglishAlphanumeric() == false || SGEXTN::ApplicationBase::OldString("0x.").isEnglishAlphanumeric() == true || SGEXTN::ApplicationBase::OldString("...").isEnglishAlphanumeric() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - is English alphanumeric fail");}
    if(SGEXTN::ApplicationBase::OldString("00").isASCII() == false || SGEXTN::ApplicationBase::OldString("0\u0081").isASCII() == true || SGEXTN::ApplicationBase::OldString("\u0081\u0081").isASCII() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - is ASCII fail");}
    if(SGEXTN::ApplicationBase::OldString("  ").isWhitespace() == false || SGEXTN::ApplicationBase::OldString("0 ").isWhitespace() == true || SGEXTN::ApplicationBase::OldString("00").isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - is whitespace fail");}
    if(SGEXTN::ApplicationBase::OldString("Test ...").lowercaseLanguageAware() != "test ..."){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - lowercase fail");}
    if(SGEXTN::ApplicationBase::OldString("Test ...").uppercaseLanguageAware() != "TEST ..."){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString - uppercase fail");}
}

void SGEXTN::ApplicationBase::UnitTests::testAll(){
    SGEXTN::ApplicationBase::UnitTests::testChar();
    SGEXTN::ApplicationBase::UnitTests::testString();
}
