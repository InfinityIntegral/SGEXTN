#pragma once

namespace SGEXTN {
namespace ApplicationBase {
class BUILDLAH_DLL_SGEXTN_ApplicationBase Char {
public:
    unsigned short private_data;
    Char() = default;
    Char(char c);
    Char(unsigned short data);
    Char(int unicode);
    [[nodiscard]] char toChar() const;
    [[nodiscard]] signed char toSignedChar() const;
    [[nodiscard]] unsigned char toUnsignedChar() const;
    [[nodiscard]] bool operator==(Char x) const;
    [[nodiscard]] bool operator!=(Char x) const;
    [[nodiscard]] bool operator<(Char x) const;
    [[nodiscard]] bool operator>(Char x) const;
    [[nodiscard]] bool operator<=(Char x) const;
    [[nodiscard]] bool operator>=(Char x) const;
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
    [[nodiscard]] Char uppercaseLanguageAware() const;
    [[nodiscard]] Char lowercaseLanguageAware() const;
};
}
}
