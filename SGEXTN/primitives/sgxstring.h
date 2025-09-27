#ifndef SGXSTRING_H
#define SGXSTRING_H

#include "sgxchar.h"
#include <vector>
#include <string>
#include <functional>

class QString;
class SGXString
{
public:
    QString* data;
    SGXString();
    SGXString(const SGXString& s);
    SGXString& operator=(const SGXString& s);
    SGXString(SGXString&& s) noexcept;
    SGXString& operator=(SGXString&& s) noexcept;
    ~SGXString();
    SGXString(SGXChar c);
    SGXString(char c);
    SGXString(const char* cString);
    SGXString(const std::string& s);
    [[nodiscard]] bool operator==(const SGXString& x) const;
    [[nodiscard]] bool operator!=(const SGXString& x) const;
    [[nodiscard]] bool operator<(const SGXString& x) const;
    [[nodiscard]] bool operator>(const SGXString& x) const;
    [[nodiscard]] bool operator<=(const SGXString& x) const;
    [[nodiscard]] bool operator>=(const SGXString& x) const;
    [[nodiscard]] SGXString operator+(const SGXString& x) const;
    [[nodiscard]] SGXString operator+(SGXChar x) const;
    friend SGXString operator+(SGXChar x, const SGXString& s);
    SGXString& operator+=(const SGXString& x);
    SGXString& operator+=(SGXChar x);
    [[nodiscard]] SGXChar at(int i) const;
    [[nodiscard]] int length() const;
    SGXString& replace(SGXChar oldChar, SGXChar newChar);
    SGXString& replace(const SGXString& oldText, const SGXString& newText);
    SGXString& insert(int pos, SGXChar c);
    SGXString& insert(int pos, const SGXString& s);
    [[nodiscard]] bool contains(SGXChar c) const;
    [[nodiscard]] bool contains(const SGXString& s) const;
    [[nodiscard]] int findFirstFromLeft(SGXChar c) const;
    [[nodiscard]] int findFirstFromLeft(const SGXString& s) const;
    [[nodiscard]] int findFirstFromLeftCustomStart(SGXChar c, int start) const;
    [[nodiscard]] int findFirstFromLeftCustomStart(const SGXString& s, int start) const;
    [[nodiscard]] int findFirstFromRight(SGXChar c) const;
    [[nodiscard]] int findFirstFromRight(const SGXString& s) const;
    [[nodiscard]] int findFirstFromRightCustomStart(SGXChar c, int start) const;
    [[nodiscard]] int findFirstFromRightCustomStart(const SGXString& s, int start) const;
    [[nodiscard]] int count(SGXChar c) const;
    [[nodiscard]] int count(const SGXString& s) const;
    [[nodiscard]] SGXString substring(int start, int length) const;
    [[nodiscard]] SGXString substringLeft(int length) const;
    [[nodiscard]] SGXString substringRight(int length) const;
    [[nodiscard]] SGXString fillLeftToLength(int length, SGXChar fillChar) const;
    [[nodiscard]] SGXString fillRightToLength(int length, SGXChar fillChar) const;
    [[nodiscard]] int parseToInt(bool* isValid) const;
    [[nodiscard]] int parseToIntBase16(bool* isValid) const;
    [[nodiscard]] int parseToIntCustomBase(bool* isValid, int base) const;
    [[nodiscard]] unsigned int parseToUnsignedInt(bool* isValid) const;
    [[nodiscard]] unsigned int parseToUnsignedIntBase16(bool* isValid) const;
    [[nodiscard]] unsigned int parseToUnsignedIntCustomBase(bool* isValid, int base) const;
    [[nodiscard]] long long parseToLongLong(bool* isValid) const;
    [[nodiscard]] long long parseToLongLongBase16(bool* isValid) const;
    [[nodiscard]] long long parseToLongLongCustomBase(bool* isValid, int base) const;
    [[nodiscard]] unsigned long long parseToUnsignedLongLong(bool* isValid) const;
    [[nodiscard]] unsigned long long parseToUnsignedLongLongBase16(bool* isValid) const;
    [[nodiscard]] unsigned long long parseToUnsignedLongLongCustomBase(bool* isValid, int base) const;
    [[nodiscard]] float parseToFloat(bool* isValid) const;
    [[nodiscard]] double parseToDouble(bool* isValid) const;
    static SGXString intToString(int x);
    static SGXString intToStringBase16(int x);
    static SGXString intToStringCustomBase(int x, int base);
    static SGXString unsignedIntToString(unsigned int x);
    static SGXString unsignedIntToStringBase16(unsigned int x);
    static SGXString unsignedIntToStringCustomBase(unsigned int x, int base);
    static SGXString longLongToString(long long x);
    static SGXString longLongToStringBase16(long long x);
    static SGXString longLongToStringCustomBase(long long x, int base);
    static SGXString unsignedLongLongToString(unsigned long long x);
    static SGXString unsignedLongLongToStringBase16(unsigned long long x);
    static SGXString unsignedLongLongToStringCustomBase(unsigned long long x, int base);
    static SGXString floatToString(float x);
    static SGXString floatToStringDecimalPlaces(float x, int dp);
    static SGXString floatToStringSignificantFigures(float x, int sf);
    static SGXString floatToStringScientificNotation(float x, int sf);
    static SGXString doubleToString(double x);
    static SGXString doubleToStringDecimalPlaces(double x, int dp);
    static SGXString doubleToStringSignificantFigures(double x, int sf);
    static SGXString doubleToStringScientificNotation(double x, int sf);
    static SGXString repeatChar(SGXChar c, int count);
    void removeLeadingTrailingWhitespace() const;
    void cleanWhitespace() const;
    [[nodiscard]] std::vector<SGXString> split() const;
    [[nodiscard]] std::vector<SGXString> splitCustomSeparator(SGXChar separator) const;
    [[nodiscard]] std::vector<SGXString> splitCustomSeparator(const SGXString& separator) const;
    [[nodiscard]] std::string toStdString() const;
    [[nodiscard]] bool isDigit() const;
    [[nodiscard]] bool isDigitBase16() const;
    [[nodiscard]] bool isEnglishLowercase() const;
    [[nodiscard]] bool isEnglishUppercase() const;
    [[nodiscard]] bool isEnglishLetter() const;
    [[nodiscard]] bool isEnglishAlphanumeric() const;
    [[nodiscard]] bool isASCII() const;
    [[nodiscard]] bool isWhitespace() const;
    [[nodiscard]] SGXString getUpperLanguageAware() const;
    [[nodiscard]] SGXString getLowerLanguageAware() const;
    void toUpperLanguageAware() const;
    void toLowerLanguageAware() const;
};

inline unsigned int qHash(const SGXString& x, unsigned int seed = 0){
    return (seed ^ static_cast<unsigned int>(std::hash<std::string>{}(x.toStdString())));
}

#endif // SGXSTRING_H
