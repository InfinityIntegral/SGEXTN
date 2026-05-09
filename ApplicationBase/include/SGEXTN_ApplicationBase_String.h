#pragma once
#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>
#include <SGEXTN_Containers_Vector.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Array;
}

namespace ApplicationBase {
class Character;

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase FloatPrecisionFormat : unsigned char {SignificantFigure, DecimalPlace, ScientificNotation};

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase NormalisationFormat : unsigned char {Join, Separate, LossyJoin, LossySeparate};

class BUILDLAH_DLL_SGEXTN_ApplicationBase String {
public:
    SGEXTN::ApplicationBase::TextBuffer private_data;
    mutable SGEXTN::Containers::Vector<int> private_characterOffsets;
    void private_computeOffsets() const;
    void private_invalidateOffsets() const;
    String();
    String(const String& s);
    String& operator=(const String& s);
    String(String&& s) noexcept;
    String& operator=(String&& s) noexcept;
    ~String();
    String(char c);
    String(const char* s);
    String(const SGEXTN::ApplicationBase::Character& c);
    [[nodiscard]] bool operator==(const String& x) const;
    [[nodiscard]] bool operator!=(const String& x) const;
    [[nodiscard]] bool operator<(const String& x) const;
    [[nodiscard]] bool operator>(const String& x) const;
    [[nodiscard]] bool operator<=(const String& x) const;
    [[nodiscard]] bool operator>=(const String& x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] String debugLog() const;
    [[nodiscard]] String operator+(const String& x) const;
    String& operator+=(const String& x);
    [[nodiscard]] int byteLength() const;
    [[nodiscard]] int characterLength() const;
    [[nodiscard]] unsigned char& byteAt(int i);
    [[nodiscard]] const unsigned char& byteAt(int i) const;
    [[nodiscard]] SGEXTN::ApplicationBase::Character getCharacterAt(int i) const;
    void setCharacterAt(int i, const SGEXTN::ApplicationBase::Character& c);
    [[nodiscard]] String fillBytes(unsigned char c) const;
    [[nodiscard]] String fillCharacters(const SGEXTN::ApplicationBase::Character& c) const;
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
    [[nodiscard]] String fillLeftToCharacterLength(int length, const SGEXTN::ApplicationBase::Character& fillChar) const;
    [[nodiscard]] String fillRightToByteLength(int length, unsigned char fillChar) const;
    [[nodiscard]] String fillRightToCharacterLength(int length, const SGEXTN::ApplicationBase::Character& fillChar) const;
    [[nodiscard]] int byteIndexToCharacterIndex(int i) const;
    [[nodiscard]] int characterIndexToByteIndex(int i) const;
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
    [[nodiscard]] static String stringFromFloat(float x, int base, SGEXTN::ApplicationBase::FloatPrecisionFormat format, int precision);
    [[nodiscard]] static String stringFromDouble(double x, int base, SGEXTN::ApplicationBase::FloatPrecisionFormat format, int precision);
    [[nodiscard]] String prettierScientificNotation() const;
    [[nodiscard]] String convertNumericSystem(const SGEXTN::ApplicationBase::Character& zeroRepresentation) const;
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

    [[nodiscard]] String getNormalised(SGEXTN::ApplicationBase::NormalisationFormat format) const;
    [[nodiscard]] SGEXTN::ApplicationBase::String getSimplestEquivalent(bool ignoreCase) const;
};
}
}