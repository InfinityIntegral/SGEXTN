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

#pragma once
#include <private_api/SGEXTN_CoreText_TextBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Array;
}

namespace CoreText {
class String;

class BuildLah_SGEXTN_CoreText Character {
public:
    SGEXTN::CoreText::TextBuffer private_data;
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
