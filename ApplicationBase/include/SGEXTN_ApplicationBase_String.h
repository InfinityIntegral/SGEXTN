#pragma once
#include <SGEXTN_ApplicationBase_Char.h>
#include <SGEXTN_Containers_Array.h>

class QString;
namespace SGEXTN {
namespace ApplicationBase {
enum class BUILDLAH_DLL_SGEXTN_ApplicationBase FloatDisplayFormat {Default, DecimalPlace, ScientificNotation};

class BUILDLAH_DLL_SGEXTN_ApplicationBase String {
public:
    QString* private_data;
    String();
    String(const String& s);
    String& operator=(const String& s);
    String(String&& s) noexcept;
    String& operator=(String&& s) noexcept;
    ~String();
    String(SGEXTN::ApplicationBase::Char c);
    String(const char* cString);
    String(const QString& s);
    [[nodiscard]] bool operator==(const String& x) const;
    [[nodiscard]] bool operator!=(const String& x) const;
    [[nodiscard]] bool operator<(const String& x) const;
    [[nodiscard]] bool operator>(const String& x) const;
    [[nodiscard]] bool operator<=(const String& x) const;
    [[nodiscard]] bool operator>=(const String& x) const;
    [[nodiscard]] String operator+(const String& x) const;
    [[nodiscard]] int hash() const;
    String& operator+=(const String& x);
    [[nodiscard]] SGEXTN::ApplicationBase::Char getCharAt(int i) const;
    void setCharAt(int i, SGEXTN::ApplicationBase::Char c);
    [[nodiscard]] int length() const;
    [[nodiscard]] String replace(const String& oldText, const String& newText) const;
    [[nodiscard]] String insert(int pos, const String& s) const;
    [[nodiscard]] bool contains(const String& s) const;
    [[nodiscard]] int findFirstFromLeft(const String& s) const;
    [[nodiscard]] int findFirstFromRight(const String& s) const;
    [[nodiscard]] int findFirstFromLeftCustomStart(const String& s, int start) const;
    [[nodiscard]] int findFirstFromRightCustomStart(const String& s, int start) const;
    [[nodiscard]] int count(const String& s) const;
    [[nodiscard]] String substring(int start, int length) const;
    [[nodiscard]] String substringLeft(int length) const;
    [[nodiscard]] String substringRight(int length) const;
    [[nodiscard]] String fillLeftToLength(int length, SGEXTN::ApplicationBase::Char fillChar) const;
    [[nodiscard]] String fillRightToLength(int length, SGEXTN::ApplicationBase::Char fillChar) const;
    [[nodiscard]] short parseToShort(bool* isValid, int base) const;
    [[nodiscard]] unsigned short parseToUnsignedShort(bool* isValid, int base) const;
    [[nodiscard]] int parseToInt(bool* isValid, int base) const;
    [[nodiscard]] unsigned int parseToUnsignedInt(bool* isValid, int base) const;
    [[nodiscard]] long long parseToLongLong(bool* isValid, int base) const;
    [[nodiscard]] unsigned long long parseToUnsignedLongLong(bool* isValid, int base) const;
    [[nodiscard]] float parseToFloat(bool* isValid) const;
    [[nodiscard]] double parseToDouble(bool* isValid) const;
    static String stringFromShort(short x, int base);
    static String stringFromUnsignedShort(unsigned short x, int base);
    static String stringFromInt(int x, int base);
    static String stringFromUnsignedInt(unsigned int x, int base);
    static String stringFromLongLong(long long x, int base);
    static String stringFromUnsignedLongLong(unsigned long long x, int base);
    static String stringFromFloat(float x, SGEXTN::ApplicationBase::FloatDisplayFormat format, int precision);
    static String stringFromDouble(double x, SGEXTN::ApplicationBase::FloatDisplayFormat format, int precision);
    static String repeatChar(SGEXTN::ApplicationBase::Char c, int count);
    String removeLeadingTrailingWhitespace() const;
    String cleanWhitespace() const;
    [[nodiscard]] SGEXTN::Containers::Array<String> split(const String& separator) const;
    [[nodiscard]] bool isDigit() const;
    [[nodiscard]] bool isDigitBase16() const;
    [[nodiscard]] bool isEnglishLowercase() const;
    [[nodiscard]] bool isEnglishUppercase() const;
    [[nodiscard]] bool isEnglishLetter() const;
    [[nodiscard]] bool isEnglishAlphanumeric() const;
    [[nodiscard]] bool isASCII() const;
    [[nodiscard]] bool isWhitespace() const;
    [[nodiscard]] String lowercaseLanguageAware() const;
    [[nodiscard]] String uppercaseLanguageAware() const;
};
}
}
