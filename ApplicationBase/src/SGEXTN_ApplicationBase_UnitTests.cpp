#include <private_api/SGEXTN_ApplicationBase_UnitTests.h>
#include <SGEXTN_ApplicationBase_Char.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_Containers_Array.h>

void SGEXTN::ApplicationBase::UnitTests::testChar(){
    if(SGEXTN::ApplicationBase::Char(65) != SGEXTN::ApplicationBase::Char('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - constructor fail");}
    if(SGEXTN::ApplicationBase::Char('a') >= SGEXTN::ApplicationBase::Char('b')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - comparison fail");}
    const SGEXTN::ApplicationBase::Char uppercaseA('A');
    if(uppercaseA.toChar() != 'A'){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - to char fail");}
    if(uppercaseA.toSignedChar() != static_cast<signed char>(65)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - to signed char fail");}
    if(uppercaseA.toUnsignedChar() != static_cast<unsigned char>(65)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - to unsigned char fail");}
    if(SGEXTN::ApplicationBase::Char('0').isDigit() == false || SGEXTN::ApplicationBase::Char('.').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - is digit fail");}
    if(SGEXTN::ApplicationBase::Char('0').isDigitBase16() == false || SGEXTN::ApplicationBase::Char('.').isDigitBase16() == true || SGEXTN::ApplicationBase::Char('a').isDigitBase16() == false || SGEXTN::ApplicationBase::Char('A').isDigitBase16() == false || SGEXTN::ApplicationBase::Char('G').isDigitBase16() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - is digit base 16 fail");}
    if(SGEXTN::ApplicationBase::Char('0').isEnglishLowercase() == true || SGEXTN::ApplicationBase::Char('.').isEnglishLowercase() == true || SGEXTN::ApplicationBase::Char('a').isEnglishLowercase() == false || SGEXTN::ApplicationBase::Char('A').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - is English lowercase fail");}
    if(SGEXTN::ApplicationBase::Char('0').isEnglishUppercase() == true || SGEXTN::ApplicationBase::Char('.').isEnglishUppercase() == true || SGEXTN::ApplicationBase::Char('a').isEnglishUppercase() == true || SGEXTN::ApplicationBase::Char('A').isEnglishUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - is English uppercase fail");}
    if(SGEXTN::ApplicationBase::Char('0').isEnglishLetter() == true || SGEXTN::ApplicationBase::Char('.').isEnglishLetter() == true || SGEXTN::ApplicationBase::Char('a').isEnglishLetter() == false || SGEXTN::ApplicationBase::Char('A').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - is English letter fail");}
    if(SGEXTN::ApplicationBase::Char('0').isEnglishAlphanumeric() == false || SGEXTN::ApplicationBase::Char('.').isEnglishAlphanumeric() == true || SGEXTN::ApplicationBase::Char('a').isEnglishAlphanumeric() == false || SGEXTN::ApplicationBase::Char('A').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - is English alphanumeric fail");}
    if(SGEXTN::ApplicationBase::Char(129).isASCII() == true || SGEXTN::ApplicationBase::Char('A').isASCII() == false || SGEXTN::ApplicationBase::Char('~').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - is ASCII fail");}
    if(SGEXTN::ApplicationBase::Char(' ').isWhitespace() == false || SGEXTN::ApplicationBase::Char('\t').isWhitespace() == false || SGEXTN::ApplicationBase::Char('\n').isWhitespace() == false || SGEXTN::ApplicationBase::Char('.').isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - is whitespace fail");}
    if(SGEXTN::ApplicationBase::Char('A').getUnicode() != 65){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - get unicode fail");}
    if(SGEXTN::ApplicationBase::Char('.').lowercaseLanguageAware() != SGEXTN::ApplicationBase::Char('.') || SGEXTN::ApplicationBase::Char('A').lowercaseLanguageAware() != SGEXTN::ApplicationBase::Char('a')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - get lowercase fail");}
    if(SGEXTN::ApplicationBase::Char('.').uppercaseLanguageAware() != SGEXTN::ApplicationBase::Char('.') || SGEXTN::ApplicationBase::Char('a').uppercaseLanguageAware() != SGEXTN::ApplicationBase::Char('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - get uppercase fail");}
}

void SGEXTN::ApplicationBase::UnitTests::testString(){
    if(SGEXTN::ApplicationBase::String("test") != "test"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - constructor from C string crashed");}
    if(SGEXTN::ApplicationBase::String(SGEXTN::ApplicationBase::Char('A')) != "A"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - constructor from char failed");}
    if(SGEXTN::ApplicationBase::String("A") >= SGEXTN::ApplicationBase::String("B")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - comparator for non overlapping strings fail");}
    if(SGEXTN::ApplicationBase::String("AC") <= SGEXTN::ApplicationBase::String("AB")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - comparator for strings with common substring fail");}
    if(SGEXTN::ApplicationBase::String("AZ") > SGEXTN::ApplicationBase::String("BY")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - comparator priority based on order of characters fail");}
    if(SGEXTN::ApplicationBase::String("a") < SGEXTN::ApplicationBase::String("B")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - comparator unicode compliance fail");}
    if(SGEXTN::ApplicationBase::String("") >= SGEXTN::ApplicationBase::String("A")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - comparator empty substring fail");}
    if(SGEXTN::ApplicationBase::String("A") >= SGEXTN::ApplicationBase::String("AA")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - comparator non empty substring fail");}
    if(SGEXTN::ApplicationBase::String("A") + SGEXTN::ApplicationBase::String("B") != "AB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string addition fail");}
    SGEXTN::ApplicationBase::String s("A");
    s += "B";
    if(s != "AB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string addition assign fail");}
    s = "SGEXTN";
    if(s.getCharAt(0) != 'S' || s.getCharAt(1) != 'G' || s.getCharAt(2) != 'E' || s.getCharAt(3) != 'X' || s.getCharAt(4) != 'T' || s.getCharAt(5) != 'N'){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - get char at index fail");}
    s.setCharAt(5, '.');
    if(s != "SGEXT."){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - set char at index fail");}
    if(s.length() != 6){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - length check fail");}
    s = "ABCABACABAB";
    if(s.replace("AB", ".") != ".C.AC.."){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - replace string fail");}
    if(s.insert(0, "D") != "DABCABACABAB" || s.insert(11, "D") != "ABCABACABABD" || s.insert(5, "D") != "ABCABDACABAB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - insert string fail");}
    if(s.contains("A") == false || s.contains("D") == true || s.contains("AB") == false || s.contains("AD") == true || s.contains("CB") == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - contains check fail");}
    if(s.findFirstFromLeft("AB") != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - find first from left fail");}
    if(s.findFirstFromRight("AB") != 9){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - find first from right fail");}
    if(s.findFirstFromLeftCustomStart("AB", 2) != 3 || s.findFirstFromLeftCustomStart("AB", 3) != 3 || s.findFirstFromLeftCustomStart("AB", 4) != 7){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - find first from left custom start fail");}
    if(s.findFirstFromRightCustomStart("AB", 2) != 0 || s.findFirstFromRightCustomStart("AB", 3) != 3 || s.findFirstFromRightCustomStart("AB", 4) != 3){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - find first from right custom start fail");}
    if(s.count("AB") != 4 || s.count("A") != 5){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - count instance of substring fail");}
    if(s.substring(1, 5) != "BCABA"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - substring fail");}
    if(s.substringLeft(5) != "ABCAB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - substring left fail");}
    if(s.substringRight(5) != "CABAB"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - substring right fail");}
    s = "26";
    if(s.fillLeftToLength(1, '0') != "26" || s.fillLeftToLength(4, '0') != "0026"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - fill left to length fail");}
    if(s.fillRightToLength(1, '0') != "26" || s.fillRightToLength(4, '0') != "2600"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - fill right to length fail");}
    bool ok = false;
    if(SGEXTN::ApplicationBase::String("26").parseToInt(nullptr, 10) != 26){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse positive int fail");}
    if(SGEXTN::ApplicationBase::String("26").parseToInt(&ok, 10) != 26 || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse positive int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("-26").parseToInt(nullptr, 10) != -26){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse negative int fail");}
    if(SGEXTN::ApplicationBase::String("-26").parseToInt(&ok, 10) != -26 || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse negative int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("26").parseToUnsignedInt(nullptr, 10) != 26u){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse positive unsigned int fail");}
    if(SGEXTN::ApplicationBase::String("26").parseToUnsignedInt(&ok, 10) != 26u || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse positive unsigned int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("-26").parseToUnsignedInt(nullptr, 10) != 0u){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse negative int to unsigned int fail");}
    if(SGEXTN::ApplicationBase::String("-26").parseToUnsignedInt(&ok, 10) != 0u || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse negative int to unsigned int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("2a").parseToInt(nullptr, 16) != 42){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse base 16 positive int fail");}
    if(SGEXTN::ApplicationBase::String("2a").parseToInt(&ok, 16) != 42 || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse base 16 positive int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("-2a").parseToInt(nullptr, 16) != -42){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse base 16 negative int fail");}
    if(SGEXTN::ApplicationBase::String("-2a").parseToInt(&ok, 16) != -42 || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse base 16 negative int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("2a").parseToUnsignedInt(nullptr, 16) != 42u){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse base 16 positive unsigned int fail");}
    if(SGEXTN::ApplicationBase::String("2a").parseToUnsignedInt(&ok, 16) != 42u || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse base 16 positive unsigned int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("-2a").parseToUnsignedInt(nullptr, 16) != 0u){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse base 16 negative int to unsigned int fail");}
    if(SGEXTN::ApplicationBase::String("-2a").parseToUnsignedInt(&ok, 16) != 0u || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse base 16 negative int to unsigned int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("").parseToInt(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse empty string to int fail");}
    if(SGEXTN::ApplicationBase::String("").parseToInt(&ok, 10) != 0 || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse empty string to int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("aaaaa").parseToInt(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse nonsensical string to int fail");}
    if(SGEXTN::ApplicationBase::String("aaaaa").parseToInt(&ok, 10) != 0 || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse nonsensical string to int with error checking fail");}
    if(SGEXTN::ApplicationBase::String("26").parseToFloat(nullptr) != 26.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse positive int to float fail");}
    if(SGEXTN::ApplicationBase::String("26").parseToFloat(&ok) != 26.0f || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse positive int to float with error checking fail");}
    if(SGEXTN::ApplicationBase::String("-26").parseToFloat(nullptr) != -26.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse negative int to float fail");}
    if(SGEXTN::ApplicationBase::String("-26").parseToFloat(&ok) != -26.0f || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse negative int to float with error checking fail");}
    if(SGEXTN::ApplicationBase::String("0.26").parseToFloat(nullptr) != 0.26f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse positive float fail");}
    if(SGEXTN::ApplicationBase::String("0.26").parseToFloat(&ok) != 0.26f || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse positive float with error checking fail");}
    if(SGEXTN::ApplicationBase::String("-0.26").parseToFloat(nullptr) != -0.26f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse negative float fail");}
    if(SGEXTN::ApplicationBase::String("-0.26").parseToFloat(&ok) != -0.26f || ok == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse negative float with error checking fail");}
    if(SGEXTN::ApplicationBase::String("").parseToFloat(nullptr) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse empty string to float fail");}
    if(SGEXTN::ApplicationBase::String("").parseToFloat(&ok) != 0 || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse empty string to float with error checking fail");}
    if(SGEXTN::ApplicationBase::String("aaaaa").parseToFloat(nullptr) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse nonsensical string to float fail");}
    if(SGEXTN::ApplicationBase::String("aaaaa").parseToFloat(&ok) != 0 || ok == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - parse nonsensical string to float with error checking fail");}
    if(SGEXTN::ApplicationBase::String::stringFromInt(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string from positive int fail");}
    if(SGEXTN::ApplicationBase::String::stringFromInt(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string from base 16 positive int fail");}
    if(SGEXTN::ApplicationBase::String::stringFromInt(-26, 10) != "-26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string from positive int fail");}
    if(SGEXTN::ApplicationBase::String::stringFromInt(-26, 16) != "-1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string from base 16 positive int fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(26.0f, SGEXTN::ApplicationBase::FloatDisplayFormat::Default, 5) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string from float default formatting fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(26.0f, SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 5) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string from float decimal place formatting fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(26.0f, SGEXTN::ApplicationBase::FloatDisplayFormat::ScientificNotation, 5) != "2.6000e+01"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - string from float scientific notation formatting fail");}
    if(SGEXTN::ApplicationBase::String::repeatChar('x', 0) != "" || SGEXTN::ApplicationBase::String::repeatChar('x', 3) != "xxx"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - repeat char fail");}
    s = " t\te\nst \t";
    if(s.removeLeadingTrailingWhitespace() != "t\te\nst"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - remove leading trailing whitespace fail");}
    if(s.cleanWhitespace() != "t e st"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - clean whitespace fail");}
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> separatedString = s.cleanWhitespace().split(" ");
    if(separatedString.length() != 3 || separatedString.at(0) != "t" || separatedString.at(1) != "e" || separatedString.at(2) != "st"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - split string fail");}
    if(SGEXTN::ApplicationBase::String("00").isDigit() == false || SGEXTN::ApplicationBase::String("0x").isDigit() == true || SGEXTN::ApplicationBase::String("xx").isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - is digit fail");}
    if(SGEXTN::ApplicationBase::String("aa").isDigitBase16() == false || SGEXTN::ApplicationBase::String("ax").isDigitBase16() == true || SGEXTN::ApplicationBase::String("xx").isDigitBase16() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - is digit base 16 fail");}
    if(SGEXTN::ApplicationBase::String("aa").isEnglishLowercase() == false || SGEXTN::ApplicationBase::String("aA").isEnglishLowercase() == true || SGEXTN::ApplicationBase::String("AA").isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - is English lowercase fail");}
    if(SGEXTN::ApplicationBase::String("AA").isEnglishUppercase() == false || SGEXTN::ApplicationBase::String("Aa").isEnglishUppercase() == true || SGEXTN::ApplicationBase::String("aa").isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - is English uppercase fail");}
    if(SGEXTN::ApplicationBase::String("xx").isEnglishLetter() == false || SGEXTN::ApplicationBase::String("0x").isEnglishLetter() == true || SGEXTN::ApplicationBase::String("00").isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - is English letter fail");}
    if(SGEXTN::ApplicationBase::String("0a").isEnglishAlphanumeric() == false || SGEXTN::ApplicationBase::String("0x.").isEnglishAlphanumeric() == true || SGEXTN::ApplicationBase::String("...").isEnglishAlphanumeric() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - is English alphanumeric fail");}
    if(SGEXTN::ApplicationBase::String("00").isASCII() == false || SGEXTN::ApplicationBase::String("0\u0081").isASCII() == true || SGEXTN::ApplicationBase::String("\u0081\u0081").isASCII() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - is ASCII fail");}
    if(SGEXTN::ApplicationBase::String("  ").isWhitespace() == false || SGEXTN::ApplicationBase::String("0 ").isWhitespace() == true || SGEXTN::ApplicationBase::String("00").isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - is whitespace fail");}
    if(SGEXTN::ApplicationBase::String("Test ...").lowercaseLanguageAware() != "test ..."){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - lowercase fail");}
    if(SGEXTN::ApplicationBase::String("Test ...").uppercaseLanguageAware() != "TEST ..."){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String - uppercase fail");}
}

void SGEXTN::ApplicationBase::UnitTests::testAll(){
    SGEXTN::ApplicationBase::UnitTests::testChar();
    SGEXTN::ApplicationBase::UnitTests::testString();
}
