#include <SGEXTN_ApplicationBase_OldString.h>
#include <SGEXTN_ApplicationBase_OldChar.h>
#include <SGEXTN_Containers_Array.h>
#include <QString>
#include <QChar>
#include <SGEXTN_Containers_HashAlgorithm.h>
#include <SGEXTN_Containers_Span.h>
#include <QList>
#include <QByteArray>
#include <QStringList>
#include <qcontainerfwd.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Math_FloatMath.h>

namespace {
char floatDisplayFormatToQStringFormatSpecifier(SGEXTN::ApplicationBase::FloatDisplayFormat x){
    if(x == SGEXTN::ApplicationBase::FloatDisplayFormat::Default){return 'g';}
    if(x == SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace){return 'f';}
    return 'e';
}
}

SGEXTN::ApplicationBase::OldString::OldString(){
    private_data = new QString("");
}

SGEXTN::ApplicationBase::OldString::OldString(const SGEXTN::ApplicationBase::OldString& s){
    private_data = new QString(*s.private_data);
}

SGEXTN::ApplicationBase::OldString& SGEXTN::ApplicationBase::OldString::operator=(const SGEXTN::ApplicationBase::OldString& s){
    if(this == &s){return (*this);}
    (*private_data) = (*s.private_data);
    return (*this);
}

SGEXTN::ApplicationBase::OldString::OldString(OldString&& s) noexcept {
    private_data = s.private_data;
    s.private_data = nullptr;
}

SGEXTN::ApplicationBase::OldString& SGEXTN::ApplicationBase::OldString::operator=(SGEXTN::ApplicationBase::OldString&& s) noexcept {
    delete private_data;
    private_data = s.private_data;
    s.private_data = nullptr;
    return (*this);
}

SGEXTN::ApplicationBase::OldString::~OldString(){
    delete private_data;
}

SGEXTN::ApplicationBase::OldString::OldString(SGEXTN::ApplicationBase::OldChar c){
    private_data = new QString(QChar(c.private_data));
}

SGEXTN::ApplicationBase::OldString::OldString(const char* cString){
    private_data = new QString(cString);
}

SGEXTN::ApplicationBase::OldString::OldString(const QString& s){
    private_data = new QString(s);
}

bool SGEXTN::ApplicationBase::OldString::operator==(const SGEXTN::ApplicationBase::OldString& x) const {
    return ((*private_data) == (*x.private_data));
}

bool SGEXTN::ApplicationBase::OldString::operator!=(const SGEXTN::ApplicationBase::OldString& x) const {
    return ((*private_data) != (*x.private_data));
}

bool SGEXTN::ApplicationBase::OldString::operator<(const SGEXTN::ApplicationBase::OldString& x) const {
    return ((*private_data) < (*x.private_data));
}

bool SGEXTN::ApplicationBase::OldString::operator>(const SGEXTN::ApplicationBase::OldString& x) const {
    return ((*private_data) > (*x.private_data));
}

bool SGEXTN::ApplicationBase::OldString::operator<=(const SGEXTN::ApplicationBase::OldString& x) const {
    return ((*private_data) <= (*x.private_data));
}

bool SGEXTN::ApplicationBase::OldString::operator>=(const SGEXTN::ApplicationBase::OldString& x) const {
    return ((*private_data) >= (*x.private_data));
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::operator+(const SGEXTN::ApplicationBase::OldString& x) const {
    SGEXTN::ApplicationBase::OldString output(*this);
    (*output.private_data) += (*x.private_data);
    return output;
}

int SGEXTN::ApplicationBase::OldString::hash() const {
    const QByteArray byteSequence = (*private_data).toUtf8();
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(byteSequence.constData()), static_cast<int>(byteSequence.length())));
}

SGEXTN::ApplicationBase::OldString& SGEXTN::ApplicationBase::OldString::operator+=(const SGEXTN::ApplicationBase::OldString& x){
    (*private_data) += (*x.private_data);
    return (*this);
}

SGEXTN::ApplicationBase::OldChar SGEXTN::ApplicationBase::OldString::getCharAt(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::getCharAt crashed as the index is negative");}
    if(i >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::getCharAt crashed as the index points beyond the end of the string");}
    return SGEXTN::ApplicationBase::OldChar((*private_data).at(i).unicode());
}

void SGEXTN::ApplicationBase::OldString::setCharAt(int i, SGEXTN::ApplicationBase::OldChar c){ // NOLINT(readability-make-member-function-const)
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::setCharAt crashed as the index is negative");}
    if(i >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::setCharAt crashed as the index points beyond the end of the string");}
    (*private_data)[i] = QChar(c.private_data);
}

int SGEXTN::ApplicationBase::OldString::length() const {
    return static_cast<int>((*private_data).length());
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::replace(const SGEXTN::ApplicationBase::OldString& oldText, const SGEXTN::ApplicationBase::OldString& newText) const {
    SGEXTN::ApplicationBase::OldString output(*this);
    (*output.private_data).replace((*oldText.private_data), (*newText.private_data));
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::insert(int pos, const SGEXTN::ApplicationBase::OldString& s) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::insert crashed as the target position is negative");}
    if(pos > length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::insert crashed as the target position points beyond the end of the string");}
    SGEXTN::ApplicationBase::OldString output(*this);
    (*output.private_data).insert(pos, (*s.private_data));
    return output;
}

bool SGEXTN::ApplicationBase::OldString::contains(const SGEXTN::ApplicationBase::OldString& s) const {
    return (*private_data).contains(*s.private_data);
}

int SGEXTN::ApplicationBase::OldString::findFirstFromLeft(const SGEXTN::ApplicationBase::OldString& s) const {
    return static_cast<int>((*private_data).indexOf(*s.private_data));
}

int SGEXTN::ApplicationBase::OldString::findFirstFromRight(const SGEXTN::ApplicationBase::OldString& s) const {
    return static_cast<int>((*private_data).lastIndexOf(*s.private_data));
}

int SGEXTN::ApplicationBase::OldString::findFirstFromLeftCustomStart(const SGEXTN::ApplicationBase::OldString& s, int start) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::findFirstFromLeftCustomStart crashed as the starting position is negative");}
    if(start >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::findFirstFromLeftCustomStart crashed as the starting position points beyond the end of the string");}
    return static_cast<int>((*private_data).indexOf((*s.private_data), start));
}

int SGEXTN::ApplicationBase::OldString::findFirstFromRightCustomStart(const SGEXTN::ApplicationBase::OldString& s, int start) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::findFirstFromRightCustomStart crashed as the starting position is negative");}
    if(start >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::findFirstFromRightCustomStart crashed as the starting position points beyond the end of the string");}
    return static_cast<int>((*private_data).lastIndexOf((*s.private_data), start));
}

int SGEXTN::ApplicationBase::OldString::count(const SGEXTN::ApplicationBase::OldString& s) const {
    return static_cast<int>((*private_data).count(*s.private_data));
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::substring(int start, int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::substring crashed as the length is negative");}
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::substring crashed as the starting position is negative");}
    if(start + length > (*this).length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::substring crashed as the ending position, which is start + length - 1, points beyond the end of this string");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).mid(start, length);
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::substringLeft(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::substringLeft crashed as the length is negative");}
    if(length > (*this).length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::substringLeft crashed as the length exceeds the length of this string");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).left(length);
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::substringRight(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::substringRight crashed as the length is negative");}
    if(length > (*this).length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::substringRight crashed as the length exceeds the length of this string");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).right(length);
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::fillLeftToLength(int length, SGEXTN::ApplicationBase::OldChar fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::fillLeftToLength crashed as the length is negative");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).rightJustified(length, QChar(fillChar.private_data));
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::fillRightToLength(int length, SGEXTN::ApplicationBase::OldChar fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::fillRightToLength crashed as the length is negative");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).leftJustified(length, QChar(fillChar.private_data));
    return output;
}

short SGEXTN::ApplicationBase::OldString::parseToShort(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::parseToShort crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toShort(isValid, base);
}

unsigned short SGEXTN::ApplicationBase::OldString::parseToUnsignedShort(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::parseToUnsignedShort crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toUShort(isValid, base);
}

int SGEXTN::ApplicationBase::OldString::parseToInt(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::parseToInt crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toInt(isValid, base);
}

unsigned int SGEXTN::ApplicationBase::OldString::parseToUnsignedInt(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::parseToUnsignedInt crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toUInt(isValid, base);
}

long long SGEXTN::ApplicationBase::OldString::parseToLongLong(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::parseToLongLong crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toLongLong(isValid, base);
}

unsigned long long SGEXTN::ApplicationBase::OldString::parseToUnsignedLongLong(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::parseToUnsignedLongLong crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toULongLong(isValid, base);
}

float SGEXTN::ApplicationBase::OldString::parseToFloat(bool* isValid) const {
    return (*private_data).toFloat(isValid);
}

double SGEXTN::ApplicationBase::OldString::parseToDouble(bool* isValid) const {
    return (*private_data).toDouble(isValid);
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::stringFromShort(short x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::stringFromShort crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::stringFromUnsignedShort(unsigned short x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::stringFromUnsignedShort crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::stringFromInt(int x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::stringFromInt crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::stringFromUnsignedInt(unsigned int x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::stringFromUnsignedInt crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::stringFromLongLong(long long x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::stringFromLongLong crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::stringFromUnsignedLongLong(unsigned long long x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::stringFromUnsignedLongLong crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::stringFromFloat(float x, SGEXTN::ApplicationBase::FloatDisplayFormat format, int precision){
    if(format == SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace && precision < 0){
        const float powerOf10 = SGEXTN::Math::FloatMath<float>::powerOf(10.0f, -1.0f * static_cast<float>(precision));
        precision = 0;
        x = powerOf10 * SGEXTN::Math::FloatMath<float>::round(x / powerOf10);
    }
    else if(precision < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::stringFromFloat crashed as the number of significant figures is nonpositive");}
    if(format == SGEXTN::ApplicationBase::FloatDisplayFormat::ScientificNotation){precision--;}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString::number(x, floatDisplayFormatToQStringFormatSpecifier(format), precision);
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::stringFromDouble(double x, SGEXTN::ApplicationBase::FloatDisplayFormat format, int precision){
    if(format == SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace && precision < 0){
        const double powerOf10 = SGEXTN::Math::FloatMath<double>::powerOf(10.0, -1.0 * static_cast<double>(precision));
        precision = 0;
        x = powerOf10 * SGEXTN::Math::FloatMath<double>::round(x / powerOf10);
    }
    else if(precision < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::stringFromDouble crashed as the number of significant figures is nonpositive");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString::number(x, floatDisplayFormatToQStringFormatSpecifier(format), precision);
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::repeatChar(SGEXTN::ApplicationBase::OldChar c, int count){
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::OldString::repeatChar crashed as count is negative");}
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = QString(count, QChar(c.private_data));
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::removeLeadingTrailingWhitespace() const {
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).trimmed();
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::cleanWhitespace() const {
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).simplified();
    return output;
}

SGEXTN::Containers::Array<SGEXTN::ApplicationBase::OldString> SGEXTN::ApplicationBase::OldString::split(const SGEXTN::ApplicationBase::OldString& separator) const {
    const QStringList list = (*private_data).split(*separator.private_data);
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::OldString> output(static_cast<int>(list.length()));
    for(int i=0; i<list.length(); i++){
        const SGEXTN::ApplicationBase::OldString s0 = "";
        (*s0.private_data) = list.at(i);
        output.at(i) = s0;
    }
    return output;
}

bool SGEXTN::ApplicationBase::OldString::isDigit() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isDigit() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::OldString::isDigitBase16() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isDigitBase16() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::OldString::isEnglishLowercase() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isEnglishLowercase() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::OldString::isEnglishUppercase() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isEnglishUppercase() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::OldString::isEnglishLetter() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isEnglishLetter() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::OldString::isEnglishAlphanumeric() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isEnglishAlphanumeric() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::OldString::isASCII() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isASCII() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::OldString::isWhitespace() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isWhitespace() == false){return false;}
    }
    return true;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::lowercaseLanguageAware() const {
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).toLower();
    return output;
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::OldString::uppercaseLanguageAware() const {
    SGEXTN::ApplicationBase::OldString output = "";
    (*output.private_data) = (*private_data).toUpper();
    return output;
}
