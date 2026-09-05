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
#include <SGEXTN/SingText/private_api/BoundariesArray.h>
#include <SGEXTN/SingText/private_api/ByteVector.h>

namespace SGEXTN::Containers {
template <typename T> class Array;
template <typename T> class Span;
}

namespace SGEXTN::SingText {
class Character;
class String;

enum class FloatPrecisionFormat : unsigned char {
    SignificantFigure = 1,
    FractionalDigit = 2,
    ScientificNotation = 3
};

enum class NormalisationFormat : unsigned char {
    Join = 1,
    Separate = 2,
    LossyJoin = 3,
    LossySeparate = 4
};

class BuildLah_SGEXTN_SingText StringStackStorage {
private:
    friend class SGEXTN::SingText::String;
    static constexpr unsigned int stackFlag = 0x80000000u;
    unsigned int length_;
    mutable unsigned int boundaries_[2];
    unsigned char data_[52];
};

class BuildLah_SGEXTN_SingText StringHeapStorage {
private:
    friend class SGEXTN::SingText::String;
    unsigned int length_;
    mutable SGEXTN::SingText::BoundariesArray boundaries_;
    SGEXTN::SingText::ByteVector data_;
public:
    StringHeapStorage() = delete;
};

class BuildLah_SGEXTN_SingText String {
private:
    union {
        StringStackStorage stack_;
        StringHeapStorage heap_;
    };
    [[nodiscard]] bool isUsingHeap() const;
    void computeGraphemeBoundaries() const;
    void invalidateGraphemeBoundaries() const;
    [[nodiscard]] bool readBoundary(int i) const;
    void writeBoundaryTrue(int i) const;
public:
    String();
    String(const String& x);
    String& operator=(const String& x);
    String(String&& x) noexcept;
    String& operator=(String&& x) noexcept;
    ~String();
    explicit(false) String(unsigned char c);
    explicit(false) String(const char* s);
    explicit(false) String(const SGEXTN::SingText::Character& c);
    [[nodiscard]] bool operator==(const String& x) const;
    [[nodiscard]] bool operator!=(const String& x) const;
    [[nodiscard]] bool operator<(const String& x) const;
    [[nodiscard]] bool operator>(const String& x) const;
    [[nodiscard]] bool operator<=(const String& x) const;
    [[nodiscard]] bool operator>=(const String& x) const;
    [[nodiscard]] static bool sendOut(const String& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(String& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(const String& x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] String operator+(const String& x) const;
    String& operator+=(const String& x);
    [[nodiscard]] int byteLength() const;
    [[nodiscard]] int characterLength() const;
    [[nodiscard]] unsigned char* getRawPointer();
    [[nodiscard]] const unsigned char* getRawPointer() const;
    [[nodiscard]] unsigned char& byteAt(int i);
    [[nodiscard]] const unsigned char& byteAt(int i) const;
    [[nodiscard]] SGEXTN::SingText::Character getCharacterAt(int i) const;
    void setCharacterAt(int i, const SGEXTN::SingText::Character& c);
    [[nodiscard]] int byteIndexToCharacterIndex(int i) const;
    [[nodiscard]] int characterIndexToByteIndex(int i) const;
    [[nodiscard]] String fillBytes(unsigned char c) const;
    [[nodiscard]] String fillCharacters(const SGEXTN::SingText::Character& c) const;
    [[nodiscard]] int findFirstBytesFromLeft(const String& s) const;
    [[nodiscard]] int findFirstBytesFromRight(const String& s) const;
    [[nodiscard]] int findFirstCharactersFromLeft(const String& s) const;
    [[nodiscard]] int findFirstCharactersFromRight(const String& s) const;
    [[nodiscard]] int findFirstBytesFromLeftBounded(int start, const String& s) const;
    [[nodiscard]] int findFirstBytesFromRightBounded(int start, const String& s) const;
    [[nodiscard]] int findFirstCharactersFromLeftBounded(int start, const String& s) const;
    [[nodiscard]] int findFirstCharactersFromRightBounded(int start, const String& s) const;
    [[nodiscard]] String substringBytes(int start, int length) const;
    [[nodiscard]] String substringCharacters(int start, int length) const;
    [[nodiscard]] String substringBytesLeft(int length) const;
    [[nodiscard]] String substringCharactersLeft(int length) const;
    [[nodiscard]] String substringBytesRight(int length) const;
    [[nodiscard]] String substringCharactersRight(int length) const;
    [[nodiscard]] String replaceBytes(const String& oldText, const String& newText) const;
    [[nodiscard]] String replaceCharacters(const String& oldText, const String& newText) const;
    [[nodiscard]] String removeBytes(const String& s) const;
    [[nodiscard]] String removeCharacters(const String& s) const;
    [[nodiscard]] String insertAtByteIndex(int pos, const String& s) const;
    [[nodiscard]] String insertAtCharacterIndex(int pos, const String& s) const;
    [[nodiscard]] String removeAtByteIndex(int pos, int length) const;
    [[nodiscard]] String removeAtCharacterIndex(int pos, int length) const;
    [[nodiscard]] bool containsBytes(const String& s) const;
    [[nodiscard]] bool containsCharacters(const String& s) const;
    [[nodiscard]] bool startsWithBytes(const String& s) const;
    [[nodiscard]] bool startsWithCharacters(const String& s) const;
    [[nodiscard]] bool endsWithBytes(const String& s) const;
    [[nodiscard]] bool endsWithCharacters(const String& s) const;
    [[nodiscard]] int countBytes(const String& s) const;
    [[nodiscard]] int countCharacters(const String& s) const;
    [[nodiscard]] int countBytesAllowOverlap(const String& s) const;
    [[nodiscard]] int countCharactersAllowOverlap(const String& s) const;
    [[nodiscard]] static String repeat(const String& s, int count);
    [[nodiscard]] String fillLeftToByteLength(int length, unsigned char fillChar) const;
    [[nodiscard]] String fillLeftToCharacterLength(int length, const SGEXTN::SingText::Character& fillChar) const;
    [[nodiscard]] String fillRightToByteLength(int length, unsigned char fillChar) const;
    [[nodiscard]] String fillRightToCharacterLength(int length, const SGEXTN::SingText::Character& fillChar) const;
    [[nodiscard]] short parseToShort(bool* isValid, int base) const;
    [[nodiscard]] unsigned short parseToUnsignedShort(bool* isValid, int base) const;
    [[nodiscard]] int parseToInt(bool* isValid, int base) const;
    [[nodiscard]] unsigned int parseToUnsignedInt(bool* isValid, int base) const;
    [[nodiscard]] long long parseToLongLong(bool* isValid, int base) const;
    [[nodiscard]] unsigned long long parseToUnsignedLongLong(bool* isValid, int base) const;
    [[nodiscard]] float parseToFloat(bool* isValid, int base) const;
    [[nodiscard]] double parseToDouble(bool* isValid, int base) const;
    [[nodiscard]] static String stringFromShort(short x, int base);
    [[nodiscard]] static String stringFromUnsignedShort(unsigned short x, int base);
    [[nodiscard]] static String stringFromInt(int x, int base);
    [[nodiscard]] static String stringFromUnsignedInt(unsigned int x, int base);
    [[nodiscard]] static String stringFromLongLong(long long x, int base);
    [[nodiscard]] static String stringFromUnsignedLongLong(unsigned long long x, int base);
    [[nodiscard]] static String stringFromFloat(float x, int base, SGEXTN::SingText::FloatPrecisionFormat format, int precision);
    [[nodiscard]] static String stringFromDouble(double x, int base, SGEXTN::SingText::FloatPrecisionFormat format, int precision);
    [[nodiscard]] String prettierScientificNotationBase10() const;
    [[nodiscard]] String convertNumericSystem(const SGEXTN::SingText::Character& zeroRepresentation) const;
    [[nodiscard]] String prepareInnerHtmlText() const;
    [[nodiscard]] String removeLeadingTrailingWhitespace() const;
    [[nodiscard]] String cleanWhitespace() const;
    [[nodiscard]] String removeAllWhitespace() const;
    [[nodiscard]] SGEXTN::Containers::Array<String> split(const String& separator) const;
    [[nodiscard]] bool isDigit() const;
    [[nodiscard]] bool isDigit(int base) const;
    [[nodiscard]] bool isEnglishLowercase() const;
    [[nodiscard]] bool isEnglishUppercase() const;
    [[nodiscard]] bool isEnglishLetter() const;
    [[nodiscard]] bool isEnglishAlphanumeric() const;
    [[nodiscard]] bool isASCII() const;
    [[nodiscard]] bool isWhitespace() const;
    [[nodiscard]] bool isUppercase() const;
    [[nodiscard]] bool isLowercase() const;
    [[nodiscard]] bool isTitlecase() const;
    [[nodiscard]] String getUppercase() const;
    [[nodiscard]] String getLowercase() const;
    [[nodiscard]] String getTitlecase() const;
    [[nodiscard]] SGEXTN::Containers::Array<int> getUnicode() const;
    [[nodiscard]] String getNormalised(SGEXTN::SingText::NormalisationFormat format) const;
    [[nodiscard]] SGEXTN::SingText::String getSimplestEquivalent(bool ignoreCase) const;
    [[nodiscard]] static String stringFromUnicode(int unicode);
    [[nodiscard]] static String stringFromUnicode(const SGEXTN::Containers::Array<int>& codePoints);
};
}
