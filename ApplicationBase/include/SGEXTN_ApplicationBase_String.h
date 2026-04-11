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

class BUILDLAH_DLL_SGEXTN_ApplicationBase String {
public:
    SGEXTN::ApplicationBase::TextBuffer private_data;
    SGEXTN::Containers::Vector<int> characterOffsets;
    void private_computeOffsets();
    void private_invalidateOffsets();
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
    [[nodiscard]] unsigned char& byteAt(int i);
    [[nodiscard]] const unsigned char& byteAt(int i) const;
    [[nodiscard]] SGEXTN::ApplicationBase::Character getCharacterAt(int i) const;
    [[nodiscard]] SGEXTN::ApplicationBase::Character getCharacterAtNoCache(int i) const;
    [[nodiscard]] SGEXTN::ApplicationBase::Character getFirstCharacter() const;
    [[nodiscard]] SGEXTN::ApplicationBase::Character getLastCharacter() const;
    void setCharacterAt(int i, const SGEXTN::ApplicationBase::Character& c);
    void setFirstCharacter(const SGEXTN::ApplicationBase::Character& c);
    void setLastCharacter(const SGEXTN::ApplicationBase::Character& c);
    [[nodiscard]] int byteLength() const;
    [[nodiscard]] int characterLength() const;
    [[nodiscard]] String fillBytes(unsigned char c) const;
    [[nodiscard]] String fillCharacters(const SGEXTN::ApplicationBase::Character& c) const;
    [[nodiscard]] String replace(const String& oldText, const String& newText) const;
    [[nodiscard]] String remove(const String& s) const;
    [[nodiscard]] String insertAtByteIndex(int pos, const String& s) const;
    [[nodiscard]] String insertAtCharacterIndex(int pos, const String& s) const;
    [[nodiscard]] String removeAtByteIndex(int pos, int length) const;
    [[nodiscard]] String removeAtCharacterIndex(int pos, int length) const;
    [[nodiscard]] bool contains(const String& s) const;
    [[nodiscard]] bool startWith(const String& s) const;
    [[nodiscard]] bool endWith(const String& s) const;
    [[nodiscard]] int findFirstFromLeft(const String& s) const;
    [[nodiscard]] int findFirstFromRight(const String& s) const;
    [[nodiscard]] int findFirstFromLeftStartAtByteIndex(int start, const String& s) const;
    [[nodiscard]] int findFirstFromRightStartAtByteIndex(int start, const String& s) const;
    [[nodiscard]] int findFirstFromLeftStartAtCharacterIndex(int start, const String& s) const;
    [[nodiscard]] int findFirstFromRightStartAtCharacterIndex(int start, const String& s) const;
    [[nodiscard]] int count(const String& s) const;
    [[nodiscard]] String substringBytes(int start, int length) const;
    [[nodiscard]] String substringCharacters(int start, int length) const;
    [[nodiscard]] String substringBytesLeft(int length) const;
    [[nodiscard]] String substringCharactersLeft(int length) const;
    [[nodiscard]] String substringBytesRight(int length) const;
    [[nodiscard]] String substringCharactersRight(int length) const;
    [[nodiscard]] String fillLeftToByteLength(int length, unsigned char fillChar) const;
    [[nodiscard]] String fillLeftToCharacterLength(int length, const SGEXTN::ApplicationBase::Character& fillChar) const;
    [[nodiscard]] String fillRightToByteLength(int length, unsigned char fillChar) const;
    [[nodiscard]] String fillRightToCharacterLength(int length, const SGEXTN::ApplicationBase::Character& fillChar) const;
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
    [[nodiscard]] static String repeat(const String& s, int count);
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
    [[nodiscard]] String getUppercase() const;
    [[nodiscard]] String getLowercase() const;
    [[nodiscard]] String getTitlecase() const;
    [[nodiscard]] bool isUppercase() const;
    [[nodiscard]] bool isLowercase() const;
    [[nodiscard]] bool isTitlecase() const;
    [[nodiscard]] String getNormalised() const;
    [[nodiscard]] bool isNormalised() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String getSimplestEquivalent(bool ignoreCase) const;
};
}
}