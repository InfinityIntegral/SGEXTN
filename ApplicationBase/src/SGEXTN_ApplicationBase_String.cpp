#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_ApplicationBase_Char.h>
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

SGEXTN::ApplicationBase::String::String(){
    private_data = new QString("");
}

SGEXTN::ApplicationBase::String::String(const SGEXTN::ApplicationBase::String& s){
    private_data = new QString(*s.private_data);
}

SGEXTN::ApplicationBase::String& SGEXTN::ApplicationBase::String::operator=(const SGEXTN::ApplicationBase::String& s){
    if(this == &s){return (*this);}
    (*private_data) = (*s.private_data);
    return (*this);
}

SGEXTN::ApplicationBase::String::String(String&& s) noexcept {
    private_data = s.private_data;
    s.private_data = nullptr;
}

SGEXTN::ApplicationBase::String& SGEXTN::ApplicationBase::String::operator=(SGEXTN::ApplicationBase::String&& s) noexcept {
    delete private_data;
    private_data = s.private_data;
    s.private_data = nullptr;
    return (*this);
}

SGEXTN::ApplicationBase::String::~String(){
    delete private_data;
}

SGEXTN::ApplicationBase::String::String(SGEXTN::ApplicationBase::Char c){
    private_data = new QString(QChar(c.private_data));
}

SGEXTN::ApplicationBase::String::String(const char* cString){
    private_data = new QString(cString);
}

SGEXTN::ApplicationBase::String::String(const QString& s){
    private_data = new QString(s);
}

bool SGEXTN::ApplicationBase::String::operator==(const SGEXTN::ApplicationBase::String& x) const {
    return ((*private_data) == (*x.private_data));
}

bool SGEXTN::ApplicationBase::String::operator!=(const SGEXTN::ApplicationBase::String& x) const {
    return ((*private_data) != (*x.private_data));
}

bool SGEXTN::ApplicationBase::String::operator<(const SGEXTN::ApplicationBase::String& x) const {
    return ((*private_data) < (*x.private_data));
}

bool SGEXTN::ApplicationBase::String::operator>(const SGEXTN::ApplicationBase::String& x) const {
    return ((*private_data) > (*x.private_data));
}

bool SGEXTN::ApplicationBase::String::operator<=(const SGEXTN::ApplicationBase::String& x) const {
    return ((*private_data) <= (*x.private_data));
}

bool SGEXTN::ApplicationBase::String::operator>=(const SGEXTN::ApplicationBase::String& x) const {
    return ((*private_data) >= (*x.private_data));
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::operator+(const SGEXTN::ApplicationBase::String& x) const {
    SGEXTN::ApplicationBase::String output(*this);
    (*output.private_data) += (*x.private_data);
    return output;
}

int SGEXTN::ApplicationBase::String::hash() const {
    const QByteArray byteSequence = (*private_data).toUtf8();
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(byteSequence.constData()), static_cast<int>(byteSequence.length())));
}

SGEXTN::ApplicationBase::String& SGEXTN::ApplicationBase::String::operator+=(const SGEXTN::ApplicationBase::String& x){
    (*private_data) += (*x.private_data);
    return (*this);
}

SGEXTN::ApplicationBase::Char SGEXTN::ApplicationBase::String::getCharAt(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::getCharAt crashed as the index is negative");}
    if(i >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::getCharAt crashed as the index points beyond the end of the string");}
    return SGEXTN::ApplicationBase::Char((*private_data).at(i).unicode());
}

void SGEXTN::ApplicationBase::String::setCharAt(int i, SGEXTN::ApplicationBase::Char c) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::setCharAt crashed as the index is negative");}
    if(i >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::setCharAt crashed as the index points beyond the end of the string");}
    (*private_data)[i] = QChar(c.private_data);
}

int SGEXTN::ApplicationBase::String::length() const {
    return static_cast<int>((*private_data).length());
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::replace(const SGEXTN::ApplicationBase::String& oldText, const SGEXTN::ApplicationBase::String& newText){
    SGEXTN::ApplicationBase::String output(*this);
    (*output.private_data).replace((*oldText.private_data), (*newText.private_data));
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::insert(int pos, const SGEXTN::ApplicationBase::String& s){
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::insert crashed as the target position is negative");}
    if(pos > length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::insert crashed as the target position points beyond the end of the string");}
    SGEXTN::ApplicationBase::String output(*this);
    (*output.private_data).insert(pos, (*s.private_data));
    return output;
}

bool SGEXTN::ApplicationBase::String::contains(const SGEXTN::ApplicationBase::String& s) const {
    return (*private_data).contains(*s.private_data);
}

int SGEXTN::ApplicationBase::String::findFirstFromLeft(const SGEXTN::ApplicationBase::String& s) const {
    return static_cast<int>((*private_data).indexOf(*s.private_data));
}

int SGEXTN::ApplicationBase::String::findFirstFromRight(const SGEXTN::ApplicationBase::String& s) const {
    return static_cast<int>((*private_data).lastIndexOf(*s.private_data));
}

int SGEXTN::ApplicationBase::String::findFirstFromLeftCustomStart(const SGEXTN::ApplicationBase::String& s, int start) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstFromLeftCustomStart crashed as the starting position is negative");}
    if(start >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstFromLeftCustomStart crashed as the starting position points beyond the end of the string");}
    return static_cast<int>((*private_data).indexOf((*s.private_data), start));
}

int SGEXTN::ApplicationBase::String::findFirstFromRightCustomStart(const SGEXTN::ApplicationBase::String& s, int start) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstFromRightCustomStart crashed as the starting position is negative");}
    if(start >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstFromRightCustomStart crashed as the starting position points beyond the end of the string");}
    return static_cast<int>((*private_data).lastIndexOf((*s.private_data), start));
}

int SGEXTN::ApplicationBase::String::count(const SGEXTN::ApplicationBase::String& s) const {
    return static_cast<int>((*private_data).count(*s.private_data));
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substring(int start, int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substring crashed as the length is negative");}
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substring crashed as the starting position is negative");}
    if(start + length > (*this).length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substring crashed as the ending position, which is start + length - 1, points beyond the end of this string");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).mid(start, length);
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substringLeft(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringLeft crashed as the length is negative");}
    if(length > (*this).length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringLeft crashed as the length exceeds the length of this string");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).left(length);
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substringRight(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringRight crashed as the length is negative");}
    if(length > (*this).length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringRight crashed as the length exceeds the length of this string");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).right(length);
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::fillLeftToLength(int length, SGEXTN::ApplicationBase::Char fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::fillLeftToLength crashed as the length is negative");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).rightJustified(length, QChar(fillChar.private_data));
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::fillRightToLength(int length, SGEXTN::ApplicationBase::Char fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::fillRightToLength crashed as the length is negative");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).leftJustified(length, QChar(fillChar.private_data));
    return output;
}

short SGEXTN::ApplicationBase::String::parseToShort(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToShort crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toShort(isValid, base);
}

unsigned short SGEXTN::ApplicationBase::String::parseToUnsignedShort(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToUnsignedShort crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toUShort(isValid, base);
}

int SGEXTN::ApplicationBase::String::parseToInt(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToInt crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toInt(isValid, base);
}

unsigned int SGEXTN::ApplicationBase::String::parseToUnsignedInt(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToUnsignedInt crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toUInt(isValid, base);
}

long long SGEXTN::ApplicationBase::String::parseToLongLong(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToLongLong crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toLongLong(isValid, base);
}

unsigned long long SGEXTN::ApplicationBase::String::parseToUnsignedLongLong(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToUnsignedLongLong crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    return (*private_data).toULongLong(isValid, base);
}

float SGEXTN::ApplicationBase::String::parseToFloat(bool* isValid) const {
    return (*private_data).toFloat(isValid);
}

double SGEXTN::ApplicationBase::String::parseToDouble(bool* isValid) const {
    return (*private_data).toDouble(isValid);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromShort(short x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromShort crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromUnsignedShort(unsigned short x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromUnsignedShort crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromInt(int x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromInt crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromUnsignedInt(unsigned int x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromUnsignedInt crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromLongLong(long long x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromLongLong crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromUnsignedLongLong(unsigned long long x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromUnsignedLongLong crashed as the base is outside the range supported by Qt, which is 2 to 36");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString::number(x, base).toLower();
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromFloat(float x, SGEXTN::ApplicationBase::FloatDisplayFormat format, int precision){
    if(precision < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromFloat crashed as the precision is nonpositive");}
    if(format == SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace){
        const float powerOf10 = SGEXTN::Math::FloatMath<float>::powerOf(10.0f, -1.0f * static_cast<float>(precision));
        precision = 0;
        x = powerOf10 * SGEXTN::Math::FloatMath<float>::round(x / powerOf10);
    }
    if(format == SGEXTN::ApplicationBase::FloatDisplayFormat::ScientificNotation){precision--;}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString::number(x, floatDisplayFormatToQStringFormatSpecifier(format), precision);
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromDouble(double x, SGEXTN::ApplicationBase::FloatDisplayFormat format, int precision){
    if(precision < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromDouble crashed as the precision is nonpositive");}
    if(format == SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace){
        const double powerOf10 = SGEXTN::Math::FloatMath<double>::powerOf(10.0, -1.0 * static_cast<double>(precision));
        precision = 0;
        x = powerOf10 * SGEXTN::Math::FloatMath<double>::round(x / powerOf10);
    }
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString::number(x, floatDisplayFormatToQStringFormatSpecifier(format), precision);
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::repeatChar(SGEXTN::ApplicationBase::Char c, int count){
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::repeatChar crashed as count is negative");}
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = QString(count, QChar(c.private_data));
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::removeLeadingTrailingWhitespace() const {
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).trimmed();
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::cleanWhitespace() const {
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).simplified();
    return output;
}

SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> SGEXTN::ApplicationBase::String::split(const SGEXTN::ApplicationBase::String& separator) const {
    const QStringList list = (*private_data).split(*separator.private_data);
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> output(static_cast<int>(list.length()));
    for(int i=0; i<list.length(); i++){
        const SGEXTN::ApplicationBase::String s0 = "";
        (*s0.private_data) = list.at(i);
        output.at(i) = s0;
    }
    return output;
}

bool SGEXTN::ApplicationBase::String::isDigit() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isDigit() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isDigitBase16() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isDigitBase16() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isEnglishLowercase() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isEnglishLowercase() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isEnglishUppercase() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isEnglishUppercase() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isEnglishLetter() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isEnglishLetter() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isEnglishAlphanumeric() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isEnglishAlphanumeric() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isASCII() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isASCII() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isWhitespace() const {
    for(int i=0; i<length(); i++){
        if(getCharAt(i).isWhitespace() == false){return false;}
    }
    return true;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::lowercaseLanguageAware() const {
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).toLower();
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::uppercaseLanguageAware() const {
    SGEXTN::ApplicationBase::String output = "";
    (*output.private_data) = (*private_data).toUpper();
    return output;
}
