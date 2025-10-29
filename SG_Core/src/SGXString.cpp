#include <SGXString.h>
#include <SGXChar.h>
#include <SGLArray.h>
#include <QString>
#include <QChar>
#include <SGLHashAlgorithm.h>
#include <SGLSpan.h>
#include <QList>
#include <QByteArray>
#include <QStringList>
#include <qcontainerfwd.h>

SGXString::SGXString(){
    (*this).data = new QString("");
}

SGXString::SGXString(const SGXString &s){
    (*this).data = new QString(*s.data);
}

SGXString& SGXString::operator=(const SGXString& s){
    if(this == &s){return (*this);}
    (*(*this).data) = (*s.data);
    return (*this);
}

SGXString::SGXString(SGXString &&s) noexcept {
    (*this).data = s.data;
    s.data = nullptr;
}

SGXString& SGXString::operator= (SGXString&& s) noexcept {
    delete (*this).data;
    (*this).data = s.data;
    s.data = nullptr;
    return (*this);
}

SGXString::~SGXString(){
    delete data;
}

SGXString::SGXString(SGXChar c){
    data = new QString(QChar(c.data));
}

SGXString::SGXString(char c){
    data = new QString(QChar(c));
}

SGXString::SGXString(const char *cString){
    data = new QString(cString);
}

bool SGXString::operator==(const SGXString& x) const {
    return ((*data) == (*x.data));
}

bool SGXString::operator!=(const SGXString& x) const {
    return ((*data) != (*x.data));
}

bool SGXString::operator<(const SGXString& x) const {
    return ((*data) < (*x.data));
}

bool SGXString::operator>(const SGXString& x) const {
    return ((*data) > (*x.data));
}

bool SGXString::operator<=(const SGXString& x) const {
    return ((*data) <= (*x.data));
}

bool SGXString::operator>=(const SGXString& x) const {
    return ((*data) >= (*x.data));
}

SGXString SGXString::operator+(const SGXString& x) const {
    SGXString output(*this);
    (*output.data) += (*x.data);
    return output;
}

SGXString SGXString::operator+(SGXChar x) const {
    SGXString output(*this);
    (*output.data) += QChar(x.data);
    return output;
}

SGXString operator+(SGXChar x, const SGXString& s){
    return (s + x);
}

SGXString& SGXString::operator+=(const SGXString& x){
    (*(*this).data) += (*x.data);
    return (*this);
}

SGXString& SGXString::operator+=(SGXChar x){
    (*(*this).data) += QChar(x.data);
    return (*this);
}

int SGXString::hash() const {
    const QByteArray byteSequence = (*data).toUtf8();
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(byteSequence.constData()), static_cast<int>(byteSequence.length())));
}

SGXChar SGXString::at(int i) const {
    return SGXChar((*(*this).data).at(i).unicode());
}

int SGXString::length() const {
    return static_cast<int>((*(*this).data).length());
}

SGXString& SGXString::replace(SGXChar oldChar, SGXChar newChar){
    (*(*this).data).replace(QChar(oldChar.data), QChar(newChar.data));
    return (*this);
}

SGXString& SGXString::replace(const SGXString &oldText, const SGXString &newText){
    (*(*this).data).replace((*oldText.data), (*newText.data));
    return (*this);
}

SGXString& SGXString::insert(int pos, SGXChar c){
    (*(*this).data).insert(pos, QChar(c.data));
    return (*this);
}

SGXString& SGXString::insert(int pos, const SGXString &s){
    (*(*this).data).insert(pos, (*s.data));
    return (*this);
}

bool SGXString::contains(SGXChar c) const {
    return (*(*this).data).contains(QChar(c.data));
}

bool SGXString::contains(const SGXString &s) const {
    return (*(*this).data).contains((*s.data));
}

int SGXString::findFirstFromLeft(SGXChar c) const {
    return static_cast<int>((*(*this).data).indexOf(QChar(c.data)));
}

int SGXString::findFirstFromLeft(const SGXString &s) const {
    return static_cast<int>((*(*this).data).indexOf(*s.data));
}

int SGXString::findFirstFromLeftCustomStart(SGXChar c, int start) const {
    return static_cast<int>((*(*this).data).indexOf(QChar(c.data), start));
}

int SGXString::findFirstFromLeftCustomStart(const SGXString &s, int start) const {
    return static_cast<int>((*(*this).data).indexOf((*s.data), start));
}

int SGXString::findFirstFromRight(SGXChar c) const {
    return static_cast<int>((*(*this).data).lastIndexOf(QChar(c.data)));
}

int SGXString::findFirstFromRight(const SGXString &s) const {
    return static_cast<int>((*(*this).data).lastIndexOf(*s.data));
}

int SGXString::findFirstFromRightCustomStart(SGXChar c, int start) const {
    return static_cast<int>((*(*this).data).lastIndexOf(QChar(c.data), start));
}

int SGXString::findFirstFromRightCustomStart(const SGXString &s, int start) const {
    return static_cast<int>((*(*this).data).lastIndexOf((*s.data), start));
}

int SGXString::count(SGXChar c) const {
    return static_cast<int>((*(*this).data).count(QChar(c.data)));
}

int SGXString::count(const SGXString &s) const {
    return static_cast<int>((*(*this).data).count(*s.data));
}

SGXString SGXString::substring(int start, int length) const {
    SGXString output = "";
    (*output.data) = (*(*this).data).mid(start, length);
    return output;
}

SGXString SGXString::substringLeft(int length) const {
    SGXString output = "";
    (*output.data) = (*(*this).data).left(length);
    return output;
}

SGXString SGXString::substringRight(int length) const {
    SGXString output = "";
    (*output.data) = (*(*this).data).right(length);
    return output;
}

SGXString SGXString::fillLeftToLength(int length, SGXChar fillChar) const {
    SGXString output = "";
    (*output.data) = (*(*this).data).rightJustified(length, QChar(fillChar.data));
    return output;
}

SGXString SGXString::fillRightToLength(int length, SGXChar fillChar) const {
    SGXString output = "";
    (*output.data)  = (*(*this).data).leftJustified(length, QChar(fillChar.data));
    return output;
}

int SGXString::parseToInt(bool *isValid) const {
    return (*(*this).data).toInt(isValid);
}

int SGXString::parseToIntBase16(bool *isValid) const {
    return (*(*this).data).toInt(isValid, 16);
}

int SGXString::parseToIntCustomBase(bool *isValid, int base) const {
    return (*(*this).data).toInt(isValid, base);
}

unsigned int SGXString::parseToUnsignedInt(bool *isValid) const {
    return (*(*this).data).toUInt(isValid);
}

unsigned int SGXString::parseToUnsignedIntBase16(bool *isValid) const {
    return (*(*this).data).toUInt(isValid, 16);
}

unsigned int SGXString::parseToUnsignedIntCustomBase(bool *isValid, int base) const {
    return (*(*this).data).toUInt(isValid, base);
}

long long SGXString::parseToLongLong(bool *isValid) const {
    return (*(*this).data).toLongLong(isValid);
}

long long SGXString::parseToLongLongBase16(bool *isValid) const {
    return (*(*this).data).toLongLong(isValid, 16);
}

long long SGXString::parseToLongLongCustomBase(bool *isValid, int base) const {
    return (*(*this).data).toLongLong(isValid, base);
}

unsigned long long SGXString::parseToUnsignedLongLong(bool *isValid) const {
    return (*(*this).data).toULongLong(isValid);
}

unsigned long long SGXString::parseToUnsignedLongLongBase16(bool *isValid) const {
    return (*(*this).data).toULongLong(isValid, 16);
}

unsigned long long SGXString::parseToUnsignedLongLongCustomBase(bool *isValid, int base) const {
    return (*(*this).data).toULongLong(isValid, base);
}

float SGXString::parseToFloat(bool *isValid) const {
    return (*(*this).data).toFloat(isValid);
}

double SGXString::parseToDouble(bool *isValid) const {
    return (*(*this).data).toDouble(isValid);
}

SGXString SGXString::intToString(int x){
    SGXString output = "";
    (*output.data) = QString::number(x);
    return output;
}

SGXString SGXString::intToStringBase16(int x){
    SGXString output = "";
    (*output.data) = QString::number(x, 16).toUpper();
    return output;
}

SGXString SGXString::intToStringCustomBase(int x, int base){
    SGXString output = "";
    (*output.data) = QString::number(x, base).toUpper();
    return output;
}

SGXString SGXString::unsignedIntToString(unsigned int x){
    SGXString output = "";
    (*output.data) = QString::number(x);
    return output;
}

SGXString SGXString::unsignedIntToStringBase16(unsigned int x){
    SGXString output = "";
    (*output.data) = QString::number(x, 16).toUpper();
    return output;
}

SGXString SGXString::unsignedIntToStringCustomBase(unsigned int x, int base){
    SGXString output = "";
    (*output.data) = QString::number(x, base).toUpper();
    return output;
}

SGXString SGXString::longLongToString(long long x){
    SGXString output = "";
    (*output.data) = QString::number(x);
    return output;
}

SGXString SGXString::longLongToStringBase16(long long x){
    SGXString output = "";
    (*output.data) = QString::number(x, 16).toUpper();
    return output;
}

SGXString SGXString::longLongToStringCustomBase(long long x, int base){
    SGXString output = "";
    (*output.data) = QString::number(x, base).toUpper();
    return output;
}

SGXString SGXString::unsignedLongLongToString(unsigned long long x){
    SGXString output = "";
    (*output.data) = QString::number(x);
    return output;
}

SGXString SGXString::unsignedLongLongToStringBase16(unsigned long long x){
    SGXString output = "";
    (*output.data) = QString::number(x, 16).toUpper();
    return output;
}

SGXString SGXString::unsignedLongLongToStringCustomBase(unsigned long long x, int base){
    SGXString output = "";
    (*output.data) = QString::number(x, base).toUpper();
    return output;
}

SGXString SGXString::floatToString(float x){
    SGXString output = "";
    (*output.data) = QString::number(x);
    return output;
}

SGXString SGXString::floatToStringDecimalPlaces(float x, int dp){
    SGXString output = "";
    (*output.data) = QString::number(x, 'f', dp);
    return output;
}

SGXString SGXString::floatToStringSignificantFigures(float x, int sf){
    SGXString output = "";
    (*output.data) = QString::number(x, 'g', sf);
    return output;
}

SGXString SGXString::floatToStringScientificNotation(float x, int sf){
    SGXString output = "";
    (*output.data) = QString::number(x, 'e', sf-1);
    return output;
}

SGXString SGXString::doubleToString(double x){
    SGXString output = "";
    (*output.data) = QString::number(x);
    return output;
}

SGXString SGXString::doubleToStringDecimalPlaces(double x, int dp){
    SGXString output = "";
    (*output.data) = QString::number(x, 'f', dp);
    return output;
}

SGXString SGXString::doubleToStringSignificantFigures(double x, int sf){
    SGXString output = "";
    (*output.data) = QString::number(x, 'g', sf);
    return output;
}

SGXString SGXString::doubleToStringScientificNotation(double x, int sf){
    SGXString output = "";
    (*output.data) = QString::number(x, 'e', sf-1);
    return output;
}

SGXString SGXString::repeatChar(SGXChar c, int count){
    SGXString output = "";
    (*output.data) = QString(count, QChar(c.data));
    return output;
}

void SGXString::removeLeadingTrailingWhitespace() const {
    (*(*this).data) = (*(*this).data).trimmed();
}

void SGXString::cleanWhitespace() const {
    (*(*this).data) = (*(*this).data).simplified();
}

SGLArray<SGXString> SGXString::split() const {
    const QStringList list = (*(*this).data).split(' ');
    SGLArray<SGXString> output(static_cast<int>(list.length()));
    for(int i=0; i<list.length(); i++){
        const SGXString s0 = "";
        (*s0.data) = list.at(i);
        output.at(i) = s0;
    }
    return output;
}

SGLArray<SGXString> SGXString::splitCustomSeparator(SGXChar separator) const {
    const QStringList list = (*(*this).data).split(QChar(separator.data));
    SGLArray<SGXString> output(static_cast<int>(list.length()));
    for(int i=0; i<list.length(); i++){
        const SGXString s0 = "";
        (*s0.data) = list.at(i);
        output.at(i) = s0;
    }
    return output;
}

SGLArray<SGXString> SGXString::splitCustomSeparator(const SGXString &separator) const {
    const QStringList list = (*(*this).data).split(*separator.data);
    SGLArray<SGXString> output(static_cast<int>(list.length()));
    for(int i=0; i<list.length(); i++){
        const SGXString s0 = "";
        (*s0.data) = list.at(i);
        output.at(i) = s0;
    }
    return output;
}

bool SGXString::isDigit() const {
    for(int i=0; i<length(); i++){
        if(at(i).isDigit() == false){return false;}
    }
    return true;
}

bool SGXString::isDigitBase16() const {
    for(int i=0; i<length(); i++){
        if(at(i).isDigitBase16() == false){return false;}
    }
    return true;
}

bool SGXString::isEnglishLowercase() const {
    for(int i=0; i<length(); i++){
        if(at(i).isEnglishLowercase() == false){return false;}
    }
    return true;
}

bool SGXString::isEnglishUppercase() const {
    for(int i=0; i<length(); i++){
        if(at(i).isEnglishUppercase() == false){return false;}
    }
    return true;
}

bool SGXString::isEnglishLetter() const {
    for(int i=0; i<length(); i++){
        if(at(i).isEnglishLetter() == false){return false;}
    }
    return true;
}

bool SGXString::isEnglishAlphanumeric() const {
    for(int i=0; i<length(); i++){
        if(at(i).isEnglishAlphanumeric() == false){return false;}
    }
    return true;
}

bool SGXString::isASCII() const {
    for(int i=0; i<length(); i++){
        if(at(i).isASCII() == false){return false;}
    }
    return true;
}

bool SGXString::isWhitespace() const {
    for(int i=0; i<length(); i++){
        if(at(i).isWhitespace() == false){return false;}
    }
    return true;
}

SGXString SGXString::getUpperLanguageAware() const {
    SGXString output = "";
    (*output.data) = (*(*this).data).toUpper();
    return output;
}

SGXString SGXString::getLowerLanguageAware() const {
    SGXString output = "";
    (*output.data) = (*(*this).data).toLower();
    return output;
}

void SGXString::toUpperLanguageAware() const {
    (*(*this).data) = (*(*this).data).toUpper();
}

void SGXString::toLowerLanguageAware() const {
    (*(*this).data) = (*(*this).data).toLower();
}
