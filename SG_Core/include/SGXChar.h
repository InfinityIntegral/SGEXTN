#ifndef SGXCHAR_H
#define SGXCHAR_H

#include <private_api_Core/SG_Build_Core.h>

class SG_CORE_DLL SGXChar
{
public:
    unsigned short data;
    SGXChar() = default;
    SGXChar(char c);
    SGXChar(unsigned short data);
    SGXChar(int unicode);
    [[nodiscard]] operator char() const;
    [[nodiscard]] bool operator==(SGXChar x) const;
    [[nodiscard]] bool operator==(char x) const;
    [[nodiscard]] bool operator!=(SGXChar x) const;
    [[nodiscard]] bool operator!=(char x) const;
    [[nodiscard]] bool operator<(SGXChar x) const;
    [[nodiscard]] bool operator<(char x) const;
    [[nodiscard]] bool operator>(SGXChar x) const;
    [[nodiscard]] bool operator>(char x) const;
    [[nodiscard]] bool operator<=(SGXChar x) const;
    [[nodiscard]] bool operator<=(char x) const;
    [[nodiscard]] bool operator>=(SGXChar x) const;
    [[nodiscard]] bool operator>=(char x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] bool isDigit() const;
    [[nodiscard]] bool isDigitBase16() const;
    [[nodiscard]] bool isEnglishLowercase() const;
    [[nodiscard]] bool isEnglishUppercase() const;
    [[nodiscard]] bool isEnglishLetter() const;
    [[nodiscard]] bool isEnglishAlphanumeric() const;
    [[nodiscard]] bool isASCII() const;
    [[nodiscard]] bool isWhitespace() const;
    [[nodiscard]] int getUnicode() const;
    [[nodiscard]] SGXChar getUpperLanguageAware() const;
    [[nodiscard]] SGXChar getLowerLanguageAware() const;
    void toUpperLanguageAware();
    void toLowerLanguageAware();
};

#endif // SGXCHAR_H
