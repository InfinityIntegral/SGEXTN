#ifndef SGXCHAR_H
#define SGXCHAR_H

class SGXChar
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
    [[nodiscard]] bool isDigit() const;
    [[nodiscard]] bool isDigitBase16() const;
    [[nodiscard]] bool isEnglishLowercase() const;
    [[nodiscard]] bool isEnglishUppercase() const;
    [[nodiscard]] bool isEnglishLetter() const;
    [[nodiscard]] bool isEnglishAlphanumeric() const;
    [[nodiscard]] bool isASCII() const;
    [[nodiscard]] char getASCII() const;
    [[nodiscard]] int getUnicode() const;
    [[nodiscard]] SGXChar getUpperLanguageAware() const;
    [[nodiscard]] SGXChar getLowerLanguageAware() const;
    void toUpperLanguageAware();
    void toLowerLanguageAware();
};

inline unsigned int qHash(SGXChar x, unsigned int seed = 0){
    return (seed ^ static_cast<unsigned int>(x.data));
}

#endif // SGXCHAR_H
