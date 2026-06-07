#pragma once
#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Array;
}

namespace ApplicationBase {
class String;

class BUILDLAH_DLL_SGEXTN_ApplicationBase Character {
public:
    SGEXTN::ApplicationBase::TextBuffer private_data;
    Character();
    Character(unsigned char c);
    Character(const char* s);
    Character(int unicode);
    [[nodiscard]] bool operator==(const Character& x) const;
    [[nodiscard]] bool operator!=(const Character& x) const;
    [[nodiscard]] bool operator<(const Character& x) const;
    [[nodiscard]] bool operator>(const Character& x) const;
    [[nodiscard]] bool operator<=(const Character& x) const;
    [[nodiscard]] bool operator>=(const Character& x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] int byteLength() const;
    [[nodiscard]] unsigned char& byteAt(int i);
    [[nodiscard]] const unsigned char& byteAt(int i) const;
    [[nodiscard]] unsigned char baseToAsciiChar() const;
    [[nodiscard]] bool isDigit() const;
    [[nodiscard]] bool isDigit(int base) const;
    [[nodiscard]] bool isEnglishLowercase() const;
    [[nodiscard]] bool isEnglishUppercase() const;
    [[nodiscard]] bool isEnglishLetter() const;
    [[nodiscard]] bool isEnglishAlphanumeric() const;
    [[nodiscard]] bool isASCII() const;
    [[nodiscard]] bool isWhitespace() const;
    [[nodiscard]] int getBaseUnicode() const;
    [[nodiscard]] SGEXTN::Containers::Array<int> getUnicode() const;
    [[nodiscard]] bool isUppercase() const;
    [[nodiscard]] bool isLowercase() const;
    [[nodiscard]] bool isTitlecase() const;
    [[nodiscard]] Character getUppercase() const;
    [[nodiscard]] Character getLowercase() const;
    [[nodiscard]] Character getTitlecase() const;
    [[nodiscard]] int getDecimalDigitValue() const;
    [[nodiscard]] float getNumericalValue() const;
};
}
}