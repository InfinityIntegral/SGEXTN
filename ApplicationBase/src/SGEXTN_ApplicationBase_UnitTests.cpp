#include <private_api/SGEXTN_ApplicationBase_UnitTests.h>
#include <SGEXTN_ApplicationBase_Char.h>
#include <private_api/SGEXTN_Containers_Crash.h>

void SGEXTN::ApplicationBase::UnitTests::testChar(){
    if(SGEXTN::ApplicationBase::Char(65) != SGEXTN::ApplicationBase::Char('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - constructor fail");}
    if(SGEXTN::ApplicationBase::Char('a') >= SGEXTN::ApplicationBase::Char('b')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Char - comparison fail");}
    SGEXTN::ApplicationBase::Char uppercaseA('A');
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

void SGEXTN::ApplicationBase::UnitTests::testAll(){
    SGEXTN::ApplicationBase::UnitTests::testChar();
}
