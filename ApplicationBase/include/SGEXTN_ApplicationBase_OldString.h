#pragma once
#include <SGEXTN_ApplicationBase_OldChar.h>
#include <SGEXTN_Containers_Array.h>

class QString;
namespace SGEXTN {
namespace ApplicationBase {
enum class BUILDLAH_DLL_SGEXTN_ApplicationBase FloatDisplayFormat : unsigned char {Default, DecimalPlace, ScientificNotation};

class BUILDLAH_DLL_SGEXTN_ApplicationBase OldString {
public:
    QString* private_data;
    OldString();
    OldString(const OldString& s);
    OldString& operator=(const OldString& s);
    OldString(OldString&& s) noexcept;
    OldString& operator=(OldString&& s) noexcept;
    ~OldString();
    OldString(SGEXTN::ApplicationBase::OldChar c);
    OldString(const char* cString);
    OldString(const QString& s);
    [[nodiscard]] bool operator==(const OldString& x) const;
    [[nodiscard]] bool operator!=(const OldString& x) const;
    [[nodiscard]] bool operator<(const OldString& x) const;
    [[nodiscard]] bool operator>(const OldString& x) const;
    [[nodiscard]] bool operator<=(const OldString& x) const;
    [[nodiscard]] bool operator>=(const OldString& x) const;
    [[nodiscard]] OldString operator+(const OldString& x) const;
    [[nodiscard]] int hash() const;
    OldString& operator+=(const OldString& x);
    [[nodiscard]] SGEXTN::ApplicationBase::OldChar getCharAt(int i) const;
    void setCharAt(int i, SGEXTN::ApplicationBase::OldChar c);
    [[nodiscard]] int length() const;
    [[nodiscard]] OldString replace(const OldString& oldText, const OldString& newText) const;
    [[nodiscard]] OldString insert(int pos, const OldString& s) const;
    [[nodiscard]] bool contains(const OldString& s) const;
    [[nodiscard]] int findFirstFromLeft(const OldString& s) const;
    [[nodiscard]] int findFirstFromRight(const OldString& s) const;
    [[nodiscard]] int findFirstFromLeftCustomStart(const OldString& s, int start) const;
    [[nodiscard]] int findFirstFromRightCustomStart(const OldString& s, int start) const;
    [[nodiscard]] int count(const OldString& s) const;
    [[nodiscard]] OldString substring(int start, int length) const;
    [[nodiscard]] OldString substringLeft(int length) const;
    [[nodiscard]] OldString substringRight(int length) const;
    [[nodiscard]] OldString fillLeftToLength(int length, SGEXTN::ApplicationBase::OldChar fillChar) const;
    [[nodiscard]] OldString fillRightToLength(int length, SGEXTN::ApplicationBase::OldChar fillChar) const;
    [[nodiscard]] short parseToShort(bool* isValid, int base) const;
    [[nodiscard]] unsigned short parseToUnsignedShort(bool* isValid, int base) const;
    [[nodiscard]] int parseToInt(bool* isValid, int base) const;
    [[nodiscard]] unsigned int parseToUnsignedInt(bool* isValid, int base) const;
    [[nodiscard]] long long parseToLongLong(bool* isValid, int base) const;
    [[nodiscard]] unsigned long long parseToUnsignedLongLong(bool* isValid, int base) const;
    [[nodiscard]] float parseToFloat(bool* isValid) const;
    [[nodiscard]] double parseToDouble(bool* isValid) const;
    [[nodiscard]] static OldString stringFromShort(short x, int base);
    [[nodiscard]] static OldString stringFromUnsignedShort(unsigned short x, int base);
    [[nodiscard]] static OldString stringFromInt(int x, int base);
    [[nodiscard]] static OldString stringFromUnsignedInt(unsigned int x, int base);
    [[nodiscard]] static OldString stringFromLongLong(long long x, int base);
    [[nodiscard]] static OldString stringFromUnsignedLongLong(unsigned long long x, int base);
    [[nodiscard]] static OldString stringFromFloat(float x, SGEXTN::ApplicationBase::FloatDisplayFormat format, int precision);
    [[nodiscard]] static OldString stringFromDouble(double x, SGEXTN::ApplicationBase::FloatDisplayFormat format, int precision);
    [[nodiscard]] static OldString repeatChar(SGEXTN::ApplicationBase::OldChar c, int count);
    OldString removeLeadingTrailingWhitespace() const;
    OldString cleanWhitespace() const;
    [[nodiscard]] SGEXTN::Containers::Array<OldString> split(const OldString& separator) const;
    [[nodiscard]] bool isDigit() const;
    [[nodiscard]] bool isDigitBase16() const;
    [[nodiscard]] bool isEnglishLowercase() const;
    [[nodiscard]] bool isEnglishUppercase() const;
    [[nodiscard]] bool isEnglishLetter() const;
    [[nodiscard]] bool isEnglishAlphanumeric() const;
    [[nodiscard]] bool isASCII() const;
    [[nodiscard]] bool isWhitespace() const;
    [[nodiscard]] OldString lowercaseLanguageAware() const;
    [[nodiscard]] OldString uppercaseLanguageAware() const;
};
}
}
