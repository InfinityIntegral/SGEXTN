#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_Containers_Vector.h>
#include <SGEXTN_ApplicationBase_Character.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_ApplicationBase_UnicodeQuery.h>
#include <SGEXTN_Math_IntegerLimits.h>
#include <SGEXTN_Math_FloatMath.h>
#include <SGEXTN_Math_FloatLimits.h>
#include <SGEXTN_Containers_Sort.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_ApplicationBase_OldString.h>
#include <QString>

namespace {
int getValueAsDigit(const SGEXTN::ApplicationBase::Character& c, int base){
    if(base != 10){
        if(c.isDigit() == true){return (static_cast<int>(c.byteAt(0)) - static_cast<int>('0'));}
        if(c.isEnglishLowercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('a'));}
        if(c.isEnglishUppercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('A'));}
        return -1;
    }
    return c.getDecimalDigitValue();
}

bool parseStringToInteger(const SGEXTN::ApplicationBase::String& s, int base, unsigned long long& output){
    if(s == "" || s == "+"){return false;}
    unsigned long long ans = 0;
    for(int i=0; i<s.characterLength(); i++){
        if(i == 0 && s.getCharacterAt(i) == '+'){continue;}
        const int digit = getValueAsDigit(s.getCharacterAt(i), base);
        if(digit == -1 || digit >= base){return false;}
        if(SGEXTN::Math::IntegerLimits<unsigned long long>::maximum() / base < ans){return false;}
        ans *= base;
        if(SGEXTN::Math::IntegerLimits<unsigned long long>::maximum() - digit < ans){return false;}
        ans += digit;
    }
    output = ans;
    return true;
}

bool parseStringToSignedInteger(const SGEXTN::ApplicationBase::String& s, int base, long long& output){
    if(s == "" || s == "+" || s == "-"){return false;}
    if(s.characterLength() >= 2 && s.substringCharactersLeft(2) == "-+"){return false;}
    bool isNegative = false;
    if(s.getCharacterAt(0) == '-'){isNegative = true;}
    unsigned long long absValue = 0;
    bool isValid = false;
    if(isNegative == false){isValid = parseStringToInteger(s, base, absValue);}
    else{isValid = parseStringToInteger(s.substringCharactersRight(s.characterLength() - 1), base, absValue);}
    if(isValid == false){return false;}
    if(absValue == static_cast<unsigned long long>(SGEXTN::Math::IntegerLimits<long long>::maximum()) + 1){
        output = SGEXTN::Math::IntegerLimits<long long>::minimum();
        return true;
    }
    if(absValue > static_cast<unsigned long long>(SGEXTN::Math::IntegerLimits<long long>::maximum())){return false;}
    if(isNegative == false){output = static_cast<long long>(absValue);}
    else{output = (-1) * static_cast<long long>(absValue);}
    return true;
}

bool parseMantissa(const SGEXTN::ApplicationBase::String& s, int base, unsigned long long& mantissa, int& exponent){
    if(s == ""){return false;}
    const int digitLimit = static_cast<int>(SGEXTN::Math::FloatMath<double>::logBase2(static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned long long>::maximum())) / SGEXTN::Math::FloatMath<double>::logBase2(static_cast<double>(base)));
    int decimalPointIndex = -1;
    int lastIndex = -1;
    int digitCount = 0;
    unsigned long long ans = 0;
    for(int i=0; i<s.characterLength(); i++){
        if(s.getCharacterAt(i) == '.'){
            if(decimalPointIndex != -1){return false;}
            if(i != s.characterLength() - 1){decimalPointIndex = i;}
            continue;
        }
        if(digitCount >= digitLimit){
            for(int j=i; j<s.characterLength(); j++){
                const int verifyDigit = getValueAsDigit(s.getCharacterAt(j), base);
                if(verifyDigit == -1 || verifyDigit >= base){return false;}
            }
            if(decimalPointIndex != -1){lastIndex = i;}
            break;
        }
        const int digit = getValueAsDigit(s.getCharacterAt(i), base);
        if(digit == -1 || digit >= base){return false;}
        ans = base * ans + digit;
        if(ans != 0 || decimalPointIndex != -1){digitCount++;}
    }
    if(decimalPointIndex == -1){exponent = 0;}
    else if(lastIndex != -1){exponent = decimalPointIndex - lastIndex;}
    else{exponent = decimalPointIndex - s.characterLength() + 1;}
    mantissa = ans;
    return true;
}

bool parseScientificNotationExponent(const SGEXTN::ApplicationBase::String& s, int base, int& exponent){
    if(s == "" || s == "+" || s == "-"){return false;}
    bool isNegative = false;
    int ans = 0;
    for(int i=0; i<s.characterLength(); i++){
        if(i == 0){
            if(s.getCharacterAt(i) == '+'){continue;}
            if(s.getCharacterAt(i) == '-'){
                isNegative = true;
                continue;
            }
        }
        if(i >= 5){
            for(int j=i; j<s.characterLength(); j++){
                const int verifyDigit = getValueAsDigit(s.getCharacterAt(j), base);
                if(verifyDigit == -1 || verifyDigit >= base){return false;}
            }
            if(isNegative == false){exponent = 100000;}
            else{exponent = -100000;}
            return true;
        }
        const int digit = getValueAsDigit(s.getCharacterAt(i), base);
        if(digit == -1 || digit >= base){return false;}
        ans = base * ans + digit;
    }
    if(isNegative == false){exponent = ans;}
    else{exponent = (-1) * ans;}
    return true;
}

bool parseStringToFloatingPoint(const SGEXTN::ApplicationBase::String& s, int base, double& output){
    if(s == ""){return false;}
    int start = 0;
    int end = -1;
    bool isNegative = false;
    if(s.getCharacterAt(0) == '+'){start = 1;}
    else if(s.getCharacterAt(0) == '-'){
        isNegative = true;
        start = 1;
    }
    if(s.containsCharacters('e') == true){end = s.findFirstCharactersFromRight('e');}
    else if(s.containsCharacters('E') == true){end = s.findFirstCharactersFromRight('E');}
    else if(base == 10 && s.containsCharacters("⏨") == true){end = s.findFirstCharactersFromRight("⏨");}
    unsigned long long mantissa = 0;
    int additionalExponent = 0;
    bool mantissaIsValid = false;
    if(end == -1){mantissaIsValid = parseMantissa(s.substringCharactersRight(s.characterLength() - start), base, mantissa, additionalExponent);}
    else{mantissaIsValid = parseMantissa(s.substringCharacters(start, end - start), base, mantissa, additionalExponent);}
    if(mantissaIsValid == false){return false;}
    if(end != -1){
        bool exponentIsValid = false;
        int exponent = 0;
        exponentIsValid = parseScientificNotationExponent(s.substringCharactersRight(s.characterLength() - end - 1), 10, exponent);
        if(exponentIsValid == false){return false;}
        additionalExponent += exponent;
    }
    double finalAns = static_cast<double>(mantissa) * SGEXTN::Math::FloatMath<double>::powerOf(static_cast<double>(base), static_cast<double>(additionalExponent));
    if(isNegative == true){finalAns = (-1) * finalAns;}
    output = finalAns;
    return true;
}

SGEXTN::ApplicationBase::Character getDigitStringRepresentation(int x){
    if(x >= 0 && x <= 9){return SGEXTN::ApplicationBase::Character(static_cast<int>('0') + x);}
    if(x >= 10 && x < 36){return SGEXTN::ApplicationBase::Character('a' + x - 10);}
    return SGEXTN::ApplicationBase::Character();
}

SGEXTN::ApplicationBase::String makeStringFromInteger(unsigned long long x, int base){
    if(x == 0){return "0";}
    SGEXTN::ApplicationBase::String reverseNum = "";
    while(x > 0){
        const int thisDigit = static_cast<int>(x % static_cast<unsigned long long>(base));
        reverseNum += getDigitStringRepresentation(thisDigit);
        x /= static_cast<unsigned long long>(base);
    }
    for(int i=0; i<reverseNum.byteLength()/2; i++){
        const unsigned char temp = reverseNum.byteAt(i);
        reverseNum.byteAt(i) = reverseNum.byteAt(reverseNum.byteLength() - 1 - i);
        reverseNum.byteAt(reverseNum.byteLength() - 1 - i) = temp;
    }
    return reverseNum;
}

SGEXTN::ApplicationBase::String makeStringFromSignedInteger(long long x, int base){
    bool isNegative = false;
    if(x == SGEXTN::Math::IntegerLimits<long long>::minimum()){return (SGEXTN::ApplicationBase::String("-") + makeStringFromInteger(static_cast<unsigned long long>(SGEXTN::Math::IntegerLimits<long long>::maximum()) + 1, base));}
    if(x < 0){
        isNegative = true;
        x *= -1;
    }
    SGEXTN::ApplicationBase::String positiveOutput = makeStringFromInteger(static_cast<unsigned long long>(x), base);
    if(isNegative == false){return positiveOutput;}
    return (SGEXTN::ApplicationBase::String("-") + positiveOutput);
}

SGEXTN::ApplicationBase::String makeStringFromFloatingPoint(double x, int base, SGEXTN::ApplicationBase::FloatPrecisionFormat format, int precision){
    if(x == SGEXTN::Math::FloatLimits<double>::notANumber()){return "not a number";}
    if(x == SGEXTN::Math::FloatLimits<double>::positiveInfinity()){return "+infinity";}
    if(x == SGEXTN::Math::FloatLimits<double>::negativeInfinity()){return "-infinity";}
    if(x == 0.0){
        if(format == SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation){
            if(precision == 1){return "0e+00";}
            return (SGEXTN::ApplicationBase::String("0.") + SGEXTN::ApplicationBase::String::repeat("0", precision - 1) + "e+00");
        }
        if(format == SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace){
            if(precision <= 0){return "0";}
            return (SGEXTN::ApplicationBase::String("0.") + SGEXTN::ApplicationBase::String::repeat("0", precision));
        }
        if(format == SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure){
            if(precision == 1){return "0";}
            return (SGEXTN::ApplicationBase::String("0.") + SGEXTN::ApplicationBase::String::repeat("0", precision - 1));
        }
    }
    bool isNegative = false;
    if(x < 0){
        isNegative = true;
        x *= -1;
    }
    SGEXTN::ApplicationBase::String mantissa;
    int exponent = 0;
    const int logarithm = SGEXTN::Math::FloatMath<double>::floorToInt(SGEXTN::Math::FloatMath<double>::logBase2(x) / SGEXTN::Math::FloatMath<double>::logBase2(base));
    if(format == SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace){
        precision += (logarithm + 1);
        if(precision <= 0){
            if(x < 0.5 * SGEXTN::Math::FloatMath<double>::powerOf(base, precision - logarithm - 1)){return "0";}
            precision = 1;
        }
    }
    const double roundUpError = 0.5 * SGEXTN::Math::FloatMath<double>::powerOf(base, logarithm + 1 - precision);
    if(x + roundUpError >= SGEXTN::Math::FloatMath<double>::powerOf(base, logarithm + 1)){
        exponent = logarithm + 1;
        mantissa = "1";
    }
    else{
        exponent = logarithm;
        x /= SGEXTN::Math::FloatMath<double>::powerOf(base, logarithm - precision);
        mantissa = makeStringFromInteger(static_cast<unsigned long long>(SGEXTN::Math::FloatMath<double>::round(x)), base);
    }
    SGEXTN::ApplicationBase::String sign;
    if(isNegative == true){sign = "-";}
    if(format == SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation){
        mantissa = mantissa.fillRightToCharacterLength(precision, '0').substringCharactersLeft(precision);
        mantissa = SGEXTN::ApplicationBase::String((mantissa.getCharacterAt(0))) + "." + mantissa.substringCharactersRight(mantissa.characterLength() - 1);
        SGEXTN::ApplicationBase::String exponentString = "+";
        if(exponent < 0){
            exponentString = "-";
            exponent *= -1;
        }
        exponentString += makeStringFromInteger(exponent, base).fillLeftToCharacterLength(2, '0');
        return (sign + mantissa + "e" + exponentString);
    }
    {
        mantissa = mantissa.fillRightToCharacterLength(precision, '0').substringCharactersLeft(precision);
        if(exponent < 0){return (sign + "0." + SGEXTN::ApplicationBase::String::repeat("0", (-1) * exponent - 1) + mantissa);}
        {
            if(mantissa.characterLength() <= exponent + 1){return (sign + mantissa + SGEXTN::ApplicationBase::String::repeat("0", exponent + 1 - mantissa.characterLength()));}
            return (sign + mantissa.substringCharactersLeft(exponent + 1) + "." + mantissa.substringCharactersRight(mantissa.characterLength() - exponent - 1));
        }
    }
}

SGEXTN::ApplicationBase::String decompositionEquivalent(const SGEXTN::ApplicationBase::String& s, bool* done){
    bool isDone = true;
    SGEXTN::ApplicationBase::String output;
    SGEXTN::Containers::Array<int> codePoint = s.getUnicode();
    for(int i=0; i<codePoint.length(); i++){
        const SGEXTN::ApplicationBase::String thisChar = SGEXTN::ApplicationBase::UnicodeQuery::getEquivDecomposition(codePoint.at(i));
        if(thisChar == ""){output += SGEXTN::ApplicationBase::Character(codePoint.at(i));}
        else{
            isDone = false;
            output += thisChar;
        }
    }
    (*done) = isDone;
    return output;
}

SGEXTN::ApplicationBase::String decompositionCompatibility(const SGEXTN::ApplicationBase::String& s, bool* done){
    bool isDone = true;
    SGEXTN::ApplicationBase::String output;
    SGEXTN::Containers::Array<int> codePoint = s.getUnicode();
    for(int i=0; i<codePoint.length(); i++){
        const SGEXTN::ApplicationBase::String thisChar = SGEXTN::ApplicationBase::UnicodeQuery::getCompatDecomposition(codePoint.at(i));
        if(thisChar == ""){output += SGEXTN::ApplicationBase::Character(codePoint.at(i));}
        else{
            isDone = false;
            output += thisChar;
        }
    }
    (*done) = isDone;
    return output;
}

SGEXTN::ApplicationBase::String recursiveDecomposeEquivalent(int i){
    bool done = false;
    SGEXTN::ApplicationBase::String output = SGEXTN::ApplicationBase::Character(i);
    while(done == false){
        output = decompositionEquivalent(output, &done);
    }
    return output;
}

SGEXTN::ApplicationBase::String recursiveDecomposeCompatibility(int i){
    bool done = false;
    SGEXTN::ApplicationBase::String output = SGEXTN::ApplicationBase::Character(i);
    while(done == false){
        output = decompositionCompatibility(output, &done);
    }
    return output;
}

struct SortByCombiningMarkOrder {
public:
    bool operator()(int a, int b);
};

bool SortByCombiningMarkOrder::operator()(int a, int b){
    return (SGEXTN::ApplicationBase::UnicodeQuery::getCombiningMarkOrder(a) < SGEXTN::ApplicationBase::UnicodeQuery::getCombiningMarkOrder(b));
}

SGEXTN::ApplicationBase::String sortCombiningMarks(const SGEXTN::ApplicationBase::String& s){
    int startSort = 0;
    const int endSort = 0;
    SGEXTN::Containers::Array<int> codePoints = s.getUnicode();
    for(int i=0; i<codePoints.length(); i++){
        if(SGEXTN::ApplicationBase::UnicodeQuery::getCombiningMarkOrder(codePoints.at(i)) == 0){
            if(startSort < i){SGEXTN::Containers::Sort<int, SortByCombiningMarkOrder>::sort(codePoints.pointerToData(startSort), i - startSort);}
            startSort = i + 1;
        }
    }
    if(startSort != codePoints.length()){SGEXTN::Containers::Sort<int, SortByCombiningMarkOrder>::sort(codePoints.pointerToData(startSort), codePoints.length() - startSort);}
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<codePoints.length(); i++){
        output += SGEXTN::ApplicationBase::Character(codePoints.at(i));
    }
    return output;
}

SGEXTN::ApplicationBase::String recursiveRecomposeCombiningMarks(const SGEXTN::ApplicationBase::String& combiningMarksGroup){
    SGEXTN::Containers::Array<int> unicode = combiningMarksGroup.getUnicode();
    while(true){
        int secondIndex = -1;
        int joinedIndex = -1;
        for(int i=1; i<unicode.length(); i++){
            const int secondCombiningMarkOrder = SGEXTN::ApplicationBase::UnicodeQuery::getCombiningMarkOrder(unicode.at(i));
            bool isBlocked = false;
            for(int j=1; j<i; j++){
                if(SGEXTN::ApplicationBase::UnicodeQuery::getCombiningMarkOrder(unicode.at(j)) >= secondCombiningMarkOrder){
                    isBlocked = true;
                    break;
                }
            }
            if(isBlocked == true){continue;}
            joinedIndex = SGEXTN::ApplicationBase::UnicodeQuery::getBinaryRecomposition(unicode.at(0), unicode.at(i));
            if(joinedIndex != -1){
                secondIndex = i;
                break;
            }
        }
        if(secondIndex == -1){break;}
        SGEXTN::ApplicationBase::String newCombiningMarksGroup = SGEXTN::ApplicationBase::Character(joinedIndex);
        for(int i=1; i<secondIndex; i++){
            newCombiningMarksGroup += SGEXTN::ApplicationBase::Character(unicode.at(i));
        }
        for(int i=secondIndex+1; i<unicode.length(); i++){
            newCombiningMarksGroup += SGEXTN::ApplicationBase::Character(unicode.at(i));
        }
        unicode = newCombiningMarksGroup.getUnicode();
    }
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<unicode.length(); i++){
        output += SGEXTN::ApplicationBase::Character(unicode.at(i));
    }
    return output;
}

SGEXTN::ApplicationBase::String unicodeRecompose(const SGEXTN::ApplicationBase::String& s){
    SGEXTN::Containers::Array<int> unicode = s.getUnicode();
    SGEXTN::ApplicationBase::String output;
    int combiningMarkBufferStart = 0;
    for(int i=0; i<unicode.length(); i++){
        if(SGEXTN::ApplicationBase::UnicodeQuery::getCombiningMarkOrder(unicode.at(i)) == 0){
            if(combiningMarkBufferStart < i){
                if(combiningMarkBufferStart == i - 1){output += SGEXTN::ApplicationBase::Character(unicode.at(i - 1));}
                else{
                    SGEXTN::ApplicationBase::String combiningMarksBuffer = "";
                    for(int j=combiningMarkBufferStart; j<i; j++){
                        combiningMarksBuffer += SGEXTN::ApplicationBase::Character(unicode.at(j));
                    }
                    output += recursiveRecomposeCombiningMarks(combiningMarksBuffer);
                }
            }
            combiningMarkBufferStart = i;
        }
        if(unicode.at(i) >= 0x1100 && unicode.at(i) < 0x1113 && i + 1 < unicode.length() && unicode.at(i + 1) >= 0x1161 && unicode.at(i + 1) < 0x1176){
            combiningMarkBufferStart = i + 1;
            const int leadingHangulIndex = unicode.at(i) - 0x1100;
            const int vowelHangulIndex = unicode.at(i + 1) - 0x1161;
            const int leadingAndVowelHangulCodePoint = 0xac00 + (leadingHangulIndex * 21 + vowelHangulIndex) * 28;
            if(i + 2 < unicode.length() && unicode.at(i + 2) >= 0x11a8 && unicode.at(i + 2) < 0x11c3){
                const int trailingHangulIndex = unicode.at(i + 2) - 0x11a7;
                output += SGEXTN::ApplicationBase::Character(leadingAndVowelHangulCodePoint + trailingHangulIndex);
                i += 2;
            }
            else{
                output += SGEXTN::ApplicationBase::Character(leadingAndVowelHangulCodePoint);
                i++;
            }
        }
        if(unicode.at(i) >= 0xac00 && unicode.at(i) < 0xd7a4 && (unicode.at(i) - 0xac00) % 28 == 0 && i + 1 < unicode.length() && unicode.at(i + 1) >= 0x11a8 && unicode.at(i + 1) < 0x11c3){
            combiningMarkBufferStart = i + 1;
            const int trailingHangulIndex = unicode.at(i + 1) - 0x11a7;
            output += SGEXTN::ApplicationBase::Character(unicode.at(i) + trailingHangulIndex);
            i++;
        }
    }
    if(combiningMarkBufferStart < unicode.length()){
        if(combiningMarkBufferStart == unicode.length() - 1){output += SGEXTN::ApplicationBase::Character(unicode.at(unicode.length() - 1));}
        else{
            SGEXTN::ApplicationBase::String combiningMarksBuffer = "";
            for(int j=combiningMarkBufferStart; j<unicode.length(); j++){
                combiningMarksBuffer += SGEXTN::ApplicationBase::Character(unicode.at(j));
            }
            output += recursiveRecomposeCombiningMarks(combiningMarksBuffer);
        }
    }
    return output;
}
}

SGEXTN::ApplicationBase::String::String(const SGEXTN::ApplicationBase::String& x){
    private_data = x.private_data;
}

SGEXTN::ApplicationBase::String& SGEXTN::ApplicationBase::String::operator=(const SGEXTN::ApplicationBase::String& x){
    if(this == &x){return (*this);}
    private_data = x.private_data;
    if(private_characterOffsets.length() > 0){private_characterOffsets = SGEXTN::Containers::Vector<int>();}
    return (*this);
}

SGEXTN::ApplicationBase::String::String(SGEXTN::ApplicationBase::String&& x) noexcept {
    private_data = static_cast<SGEXTN::ApplicationBase::TextBuffer&&>(x.private_data);
    private_characterOffsets = static_cast<SGEXTN::Containers::Vector<int>&&>(x.private_characterOffsets);
}

SGEXTN::ApplicationBase::String& SGEXTN::ApplicationBase::String::operator=(SGEXTN::ApplicationBase::String&& x) noexcept {
    private_data = static_cast<SGEXTN::ApplicationBase::TextBuffer&&>(x.private_data);
    private_characterOffsets = static_cast<SGEXTN::Containers::Vector<int>&&>(x.private_characterOffsets);
    return (*this);
}

SGEXTN::ApplicationBase::String::String(char c){
    private_data.pushBack(c);
}

SGEXTN::ApplicationBase::String::String(const char* s){
    private_data.pushBack(s);
}

SGEXTN::ApplicationBase::String::String(const SGEXTN::ApplicationBase::Character& c){
    private_data.pushBack(c.private_data, 0, c.private_data.length());
}

bool SGEXTN::ApplicationBase::String::operator==(const SGEXTN::ApplicationBase::String& x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::ApplicationBase::String::operator!=(const SGEXTN::ApplicationBase::String& x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::ApplicationBase::String::operator<(const SGEXTN::ApplicationBase::String& x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::ApplicationBase::String::operator>(const SGEXTN::ApplicationBase::String& x) const {
    return (private_data > x.private_data);
}

bool SGEXTN::ApplicationBase::String::operator<=(const SGEXTN::ApplicationBase::String& x) const {
    return (private_data <= x.private_data);
}

bool SGEXTN::ApplicationBase::String::operator>=(const SGEXTN::ApplicationBase::String& x) const {
    return (private_data >= x.private_data);
}

int SGEXTN::ApplicationBase::String::hash() const {
    return private_data.hash();
}

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::String::debugLog() const {
    return SGEXTN::ApplicationBase::OldString(QString::fromUtf8(reinterpret_cast<const char*>(&private_data.byteAt(0)), byteLength()));
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::operator+(const SGEXTN::ApplicationBase::String& x) const {
    SGEXTN::ApplicationBase::String output = (*this);
    output += x;
    return output;
}

SGEXTN::ApplicationBase::String& SGEXTN::ApplicationBase::String::operator+=(const SGEXTN::ApplicationBase::String& x){
    private_invalidateOffsets();
    private_data.pushBack(x.private_data, 0, x.private_data.length());
    return (*this);
}

int SGEXTN::ApplicationBase::String::byteLength() const {
    return private_data.length();
}

int SGEXTN::ApplicationBase::String::characterLength() const {
    private_computeOffsets();
    return (private_characterOffsets.length() - 1);
}

unsigned char& SGEXTN::ApplicationBase::String::byteAt(int i){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::byteAt crashed because the index is negative");}
    if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::byteAt crashed because the index points beyond the end of the string");}
    private_invalidateOffsets();
    return private_data.byteAt(i);
}

const unsigned char& SGEXTN::ApplicationBase::String::byteAt(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::byteAt crashed because the index is negative");}
    if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::byteAt crashed because the index points beyond the end of the string");}
    return private_data.byteAt(i);
}

void SGEXTN::ApplicationBase::String::private_computeOffsets() const {
    if(private_characterOffsets.length() > 0){return;}
    SGEXTN::Containers::Array<int> unicodeList = getUnicode();
    SGEXTN::Containers::Array<int> codePointOffset(unicodeList.length());
    int currentCodePointOffset = 0;
    for(int i=0; i<unicodeList.length(); i++){
        codePointOffset.at(i) = currentCodePointOffset;
        if(unicodeList.at(i) <= 0x7f){currentCodePointOffset++;}
        else if(unicodeList.at(i) <= 0x7ff){currentCodePointOffset += 2;}
        else if(unicodeList.at(i) <= 0xffff){currentCodePointOffset += 3;}
        else{currentCodePointOffset += 4;}
    }
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::GraphemeSegmentationType> segmentationTypes(unicodeList.length());
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::GraphemeRuleRelatedType> ruleRelatedTypes(unicodeList.length());
    for(int i=0; i<unicodeList.length(); i++){
        segmentationTypes.at(i) = SGEXTN::ApplicationBase::UnicodeQuery::getGraphemeSegmentationType(unicodeList.at(i));
        ruleRelatedTypes.at(i) = SGEXTN::ApplicationBase::UnicodeQuery::getGraphemeRuleRelatedType(unicodeList.at(i));
    }
    private_characterOffsets.pushBack(0);
    if(unicodeList.length() == 0){return;}
    for(int i=1; i<unicodeList.length(); i++){
        if(segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::Return && segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::NewLine){continue;}
        if(segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::Return || segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::NewLine || segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::ControlCharacter){
            private_characterOffsets.pushBack(codePointOffset.at(i));
            continue;
        }
        if(segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::Return || segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::NewLine || segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::ControlCharacter){
            private_characterOffsets.pushBack(codePointOffset.at(i));
            continue;
        }
        if(segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeading && (segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeading || segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulVowel || segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeadingAndVowel || segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing)){continue;}
        if((segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeadingAndVowel || segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulVowel) && (segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulVowel || segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulTrailing)){continue;}
        if(segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulTrailing && (segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing || segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulTrailing)){continue;}
        if(segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::ZeroWidthJoiner || segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::Extend){continue;}
        if(segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::SpacingCombiningMark){continue;}
        if(segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::Prepend){continue;}
        if(ruleRelatedTypes.at(i) == SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule9cConsonant){
            bool foundLinker = false;
            bool foundConsonant = false;
            for(int j=i-1; j>=0; j--){
                if(ruleRelatedTypes.at(j) == SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule9cLinker){foundLinker = true;}
                if(ruleRelatedTypes.at(j) == SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule9cConsonant){foundConsonant = true;}
                if(ruleRelatedTypes.at(j) != SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule9cLinker && ruleRelatedTypes.at(j) != SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule9cExtend){break;}
            }
            if(foundConsonant == true && foundLinker == true){continue;}
        }
        if(ruleRelatedTypes.at(i) == SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule11Emoji && segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::ZeroWidthJoiner){
            bool foundStartEmoji = false;
            for(int j=i-2; j>=0; j--){
                if(ruleRelatedTypes.at(j) == SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule11Emoji){foundStartEmoji = true;}
                if(segmentationTypes.at(j) != SGEXTN::ApplicationBase::GraphemeSegmentationType::Extend){break;}
            }
            if(foundStartEmoji == true){continue;}
        }
        if(segmentationTypes.at(i) == SGEXTN::ApplicationBase::GraphemeSegmentationType::RegionalIndicator && segmentationTypes.at(i - 1) == SGEXTN::ApplicationBase::GraphemeSegmentationType::RegionalIndicator){
            if(i - 2 < 0 || segmentationTypes.at(i - 2) != SGEXTN::ApplicationBase::GraphemeSegmentationType::RegionalIndicator){continue;}
            if(private_characterOffsets.at(private_characterOffsets.length() - 1) == codePointOffset.at(i - 2)){continue;}
        }
        private_characterOffsets.pushBack(codePointOffset.at(i));
    }
    private_characterOffsets.pushBack(byteLength());
}

void SGEXTN::ApplicationBase::String::private_invalidateOffsets() const {
    if(private_characterOffsets.length() > 0){private_characterOffsets = SGEXTN::Containers::Vector<int>();}
}

SGEXTN::ApplicationBase::Character SGEXTN::ApplicationBase::String::getCharacterAt(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::getCharacterAt crashed because index is negative");}
    if(i >= characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::getCharacterAt crashed because index points beyond the end of the string");}
    private_computeOffsets();
    SGEXTN::ApplicationBase::Character c;
    c.private_data = SGEXTN::ApplicationBase::TextBuffer();
    c.private_data.pushBack(private_data, private_characterOffsets.at(i), private_characterOffsets.at(i + 1) - private_characterOffsets.at(i));
    return c;
}

void SGEXTN::ApplicationBase::String::setCharacterAt(int i, const SGEXTN::ApplicationBase::Character& c){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::setCharacterAt crashed because index is negative");}
    if(i >= characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::setCharacterAt crashed because index points beyond the end of the string");}
    private_computeOffsets();
    int rangeBegin = private_characterOffsets.at(i);
    int rangeEnd = private_characterOffsets.at(i + 1);
    if(rangeEnd - rangeBegin == c.byteLength()){
        for(int j=rangeBegin; j<rangeEnd; j++){
            byteAt(j) = c.byteAt(j - rangeBegin);
        }
    }
    else{
        SGEXTN::ApplicationBase::TextBuffer newBuffer;
        newBuffer.pushBack(private_data, 0, rangeBegin);
        newBuffer.pushBack(c.private_data, 0, c.byteLength());
        newBuffer.pushBack(private_data, rangeEnd, byteLength() - rangeEnd);
        private_data = newBuffer;
    }
    private_invalidateOffsets();
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::fillBytes(unsigned char c) const {
    SGEXTN::ApplicationBase::String output(*this);
    for(int i=0; i<output.byteLength(); i++){
        output.byteAt(i) = c;
    }
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::fillCharacters(const SGEXTN::ApplicationBase::Character& c) const {
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<characterLength(); i++){
        output.private_data.pushBack(c.private_data, 0, c.byteLength());
    }
    return output;
}

int SGEXTN::ApplicationBase::String::findFirstBytesFromLeftBounded(int start, const SGEXTN::ApplicationBase::String& s) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstBytesFromLeftBounded crashed because the starting point is negative");}
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstBytesFromLeftBounded crashed because the string to find is empty");}
    for(int i=start; i <= byteLength() - s.byteLength(); i++){
        for(int j=0; j<s.byteLength(); j++){
            if(byteAt(i + j) != s.byteAt(j)){break;}
            if(j == s.byteLength() - 1){return i;}
        }
    }
    return -1;
}

int SGEXTN::ApplicationBase::String::findFirstBytesFromRightBounded(int start, const SGEXTN::ApplicationBase::String& s) const {
    if(start >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstBytesFromRightBounded crashed because the starting point is beyond the end of the string");}
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstBytesFromRightBounded crashed because the string to find is empty");}
    if(start > byteLength() - s.byteLength()){start = byteLength() - s.byteLength();}
    for(int i=start; i>=0; i--){
        for(int j=0; j<s.byteLength(); j++){
            if(byteAt(i + j) != s.byteAt(j)){break;}
            if(j == s.byteLength() - 1){return i;}
        }
    }
    return -1;
}

int SGEXTN::ApplicationBase::String::findFirstBytesFromLeft(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstBytesFromLeft crashed because the string to find is empty");}
    return findFirstBytesFromLeftBounded(0, s);
}

int SGEXTN::ApplicationBase::String::findFirstBytesFromRight(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstBytesFromRight crashed because the string to find is empty");}
    return findFirstBytesFromRightBounded(byteLength() - 1, s);
}

int SGEXTN::ApplicationBase::String::findFirstCharactersFromLeftBounded(int start, const SGEXTN::ApplicationBase::String& s) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstCharactersFromLeftBounded crashed because the starting point is negative");}
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstCharacterFromLeftBounded crashed because the string to find is empty");}
    for(int i=start; i <= characterLength() - s.characterLength(); i++){
        for(int j=0; j<s.characterLength(); j++){
            if(getCharacterAt(i + j) != s.getCharacterAt(j)){break;}
            if(j == s.characterLength() - 1){return i;}
        }
    }
    return -1;
}

int SGEXTN::ApplicationBase::String::findFirstCharactersFromRightBounded(int start, const SGEXTN::ApplicationBase::String& s) const {
    if(start >= characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstCharactersFromRightBounded crashed because the starting point is beyond the end of the string");}
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstCharacterFromRightBounded crashed because the string to find is empty");}
    if(start > characterLength() - s.characterLength()){start = characterLength() - s.characterLength();}
    for(int i=start; i>=0; i--){
        for(int j=0; j<s.characterLength(); j++){
            if(getCharacterAt(i + j) != s.getCharacterAt(j)){break;}
            if(j == s.characterLength() - 1){return i;}
        }
    }
    return -1;
}

int SGEXTN::ApplicationBase::String::findFirstCharactersFromLeft(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstCharacterFromLeft crashed because the string to find is empty");}
    return findFirstCharactersFromLeftBounded(0, s);
}

int SGEXTN::ApplicationBase::String::findFirstCharactersFromRight(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::findFirstCharacterFromRight crashed because the string to find is empty");}
    return findFirstCharactersFromRightBounded(characterLength() - 1, s);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substringBytes(int start, int length) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringBytes crashed because the starting point is negative");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringBytes crashed because the length is negative");}
    if(length + start > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringBytes crashed because the end point is beyond the end of the string");}
    SGEXTN::ApplicationBase::String output;
    output.private_data.pushBack(private_data, start, length);
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substringBytesLeft(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringBytesLeft crashed because the length is negative");}
    if(length > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringBytesLeft crashed because the end point is beyond the end of the string");}
    return substringBytes(0, length);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substringBytesRight(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringBytesRight crashed because the length is negative");}
    if(length > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringBytesRight crashed because the start point is beyond the start of the string");}
    return substringBytes(byteLength() - length, length);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substringCharacters(int start, int length) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringCharacters crashed because the starting point is negative");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringCharacters crashed because the length is negative");}
    if(length + start > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringCharacters crashed because the end point is beyond the end of the string");}
    private_computeOffsets();
    SGEXTN::ApplicationBase::String output;
    output.private_data.pushBack(private_data, private_characterOffsets.at(start), private_characterOffsets.at(start + length) - private_characterOffsets.at(start));
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substringCharactersLeft(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringCharactersLeft crashed because the length is negative");}
    if(length > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringCharactersLeft crashed because the end point is beyond the end of the string");}
    return substringCharacters(0, length);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::substringCharactersRight(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringCharactersRight crashed because the length is negative");}
    if(length > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::substringCharactersRight crashed because the start point is beyond the start of the string");}
    return substringCharacters(characterLength() - length, length);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::replaceBytes(const SGEXTN::ApplicationBase::String& oldText, const SGEXTN::ApplicationBase::String& newText) const {
    if(oldText == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::replaceBytes crashed because string to replace is empty");}
    SGEXTN::ApplicationBase::String output;
    int lastCheck = 0;
    while(lastCheck != -1){
        const int nextIndex = findFirstBytesFromLeftBounded(lastCheck, oldText);
        if(nextIndex == -1){
            output.private_data.pushBack(private_data, lastCheck, byteLength() - lastCheck);
            lastCheck = -1;
        }
        else{
            output.private_data.pushBack(private_data, lastCheck, nextIndex - lastCheck);
            output.private_data.pushBack(newText.private_data, 0, newText.byteLength());
            lastCheck = nextIndex + oldText.byteLength();
            if(lastCheck == byteLength()){lastCheck = -1;}
        }
    }
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::replaceCharacters(const SGEXTN::ApplicationBase::String& oldText, const SGEXTN::ApplicationBase::String& newText) const {
    if(oldText == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::replaceCharacters crashed because string to replace is empty");}
    private_computeOffsets();
    SGEXTN::ApplicationBase::String output;
    int lastCheck = 0;
    while(lastCheck != -1){
        const int nextIndex = findFirstCharactersFromLeftBounded(lastCheck, oldText);
        if(nextIndex == -1){
            output.private_data.pushBack(private_data, private_characterOffsets.at(lastCheck), byteLength() - private_characterOffsets.at(lastCheck));
            lastCheck = -1;
        }
        else{
            output.private_data.pushBack(private_data, private_characterOffsets.at(lastCheck), private_characterOffsets.at(nextIndex) - private_characterOffsets.at(lastCheck));
            output.private_data.pushBack(newText.private_data, 0, newText.byteLength());
            lastCheck = nextIndex + oldText.characterLength();
            if(lastCheck == characterLength()){lastCheck = -1;}
        }
    }
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::removeBytes(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::removeBytes crashed because string to replace is empty");}
    return replaceBytes(s, "");
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::removeCharacters(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::removeCharacters crashed because string to replace is empty");}
    return replaceCharacters(s, "");
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::insertAtByteIndex(int pos, const SGEXTN::ApplicationBase::String& s) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::insertAtByteIndex crashed because position of insertion is negative");}
    if(pos > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::Application::String::insertAtByteIndex crashed because position of insertion points to more than 1 space beyond the end of the string");}
    SGEXTN::ApplicationBase::String output;
    if(pos > 0){output.private_data.pushBack(private_data, 0, pos);}
    output.private_data.pushBack(s.private_data, 0, s.byteLength());
    if(pos < byteLength()){output.private_data.pushBack(private_data, pos, byteLength() - pos);}
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::insertAtCharacterIndex(int pos, const SGEXTN::ApplicationBase::String& s) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::insertAtCharacterIndex crashed because position of insertion is negative");}
    if(pos > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::insertAtCharacterIndex crashed because position of insertion points to more than 1 space beyond the end of the string");}
    private_computeOffsets();
    SGEXTN::ApplicationBase::String output;
    if(pos > 0){output.private_data.pushBack(private_data, 0, private_characterOffsets.at(pos));}
    output.private_data.pushBack(s.private_data, 0, s.byteLength());
    if(pos < characterLength()){output.private_data.pushBack(private_data, private_characterOffsets.at(pos), byteLength() - private_characterOffsets.at(pos));}
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::removeAtByteIndex(int pos, int length) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::removeAtByteIndex crashed because the start of the range to remove is negative");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::removeAtByteIndex crashed because the length to remove is negative");}
    if(pos + length > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::removeAtByteIndex crashed because the end of the range to remove points beyond the end of the string");}
    SGEXTN::ApplicationBase::String output;
    if(pos > 0){output.private_data.pushBack(private_data, 0, pos);}
    if(pos + length < byteLength()){output.private_data.pushBack(private_data, pos + length, byteLength() - pos - length);}
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::removeAtCharacterIndex(int pos, int length) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::removeAtCharacterIndex crashed because the start of the range to remove is negative");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::removeAtCharacterIndex crashed because the length to remove is negative");}
    if(pos + length > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::removeAtCharacterIndex crashed because the end of the range to remove points beyond the end of the string");}
    private_computeOffsets();
    SGEXTN::ApplicationBase::String output;
    if(pos > 0){output.private_data.pushBack(private_data, 0, private_characterOffsets.at(pos));}
    if(pos + length < characterLength()){output.private_data.pushBack(private_data, private_characterOffsets.at(pos + length), byteLength() - private_characterOffsets.at(pos + length));}
    return output;
}

bool SGEXTN::ApplicationBase::String::containsBytes(const SGEXTN::ApplicationBase::String& s) const {
    return (findFirstBytesFromLeft(s) != -1);
}

bool SGEXTN::ApplicationBase::String::containsCharacters(const SGEXTN::ApplicationBase::String& s) const {
    return (findFirstCharactersFromLeft(s) != -1);
}

bool SGEXTN::ApplicationBase::String::startsWithBytes(const SGEXTN::ApplicationBase::String& s) const {
    if(s.byteLength() > byteLength()){return false;}
    return (substringBytesLeft(s.byteLength()) == s);
}

bool SGEXTN::ApplicationBase::String::startsWithCharacters(const SGEXTN::ApplicationBase::String& s) const {
    if(s.characterLength() > characterLength()){return false;}
    return (substringCharactersLeft(s.characterLength()) == s);
}

bool SGEXTN::ApplicationBase::String::endsWithBytes(const SGEXTN::ApplicationBase::String& s) const {
    if(s.byteLength() > byteLength()){return false;}
    return (substringBytesRight(s.byteLength()) == s);
}

bool SGEXTN::ApplicationBase::String::endsWithCharacters(const SGEXTN::ApplicationBase::String& s) const {
    if(s.characterLength() > characterLength()){return false;}
    return (substringCharactersRight(s.characterLength()) == s);
}

int SGEXTN::ApplicationBase::String::countBytes(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::countBytes crashed because string to count is empty");}
    int lastCheck = 0;
    int count = 0;
    while(true){
        const int nextIndex = findFirstBytesFromLeftBounded(lastCheck, s);
        if(nextIndex == -1){break;}
        count++;
        if(nextIndex == byteLength() - 1){break;}
        lastCheck = nextIndex + s.byteLength();
    }
    return count;
}

int SGEXTN::ApplicationBase::String::countCharacters(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::countCharacters crashed because string to count is empty");}
    int lastCheck = 0;
    int count = 0;
    while(true){
        const int nextIndex = findFirstCharactersFromLeftBounded(lastCheck, s);
        if(nextIndex == -1){break;}
        count++;
        if(nextIndex == characterLength() - 1){break;}
        lastCheck = nextIndex + s.characterLength();
    }
    return count;
}

int SGEXTN::ApplicationBase::String::countBytesAllowOverlap(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::countBytesAllowOverlap crashed because string to count is empty");}
    int lastCheck = 0;
    int count = 0;
    while(true){
        const int nextIndex = findFirstBytesFromLeftBounded(lastCheck, s);
        if(nextIndex == -1){break;}
        count++;
        if(nextIndex == byteLength() - 1){break;}
        lastCheck = nextIndex + 1;
    }
    return count;
}

int SGEXTN::ApplicationBase::String::countCharactersAllowOverlap(const SGEXTN::ApplicationBase::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::countCharactersAllowOverlap crashed because string to count is empty");}
    int lastCheck = 0;
    int count = 0;
    while(true){
        const int nextIndex = findFirstCharactersFromLeftBounded(lastCheck, s);
        if(nextIndex == -1){break;}
        count++;
        if(nextIndex == characterLength() - 1){break;}
        lastCheck = nextIndex + 1;
    }
    return count;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::repeat(const SGEXTN::ApplicationBase::String& s, int count){
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::repeat crashed because count is negative");}
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<count; i++){
        output.private_data.pushBack(s.private_data, 0, s.byteLength());
    }
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::fillLeftToByteLength(int length, char fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::fillLeftToByteLength crashed because target length is negative");}
    if(byteLength() >= length){return (*this);}
    return (SGEXTN::ApplicationBase::String::repeat(fillChar, length - byteLength()) + (*this));
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::fillLeftToCharacterLength(int length, const SGEXTN::ApplicationBase::Character& fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::fillLeftToCharacterLength crashed because target length is negative");}
    if(characterLength() >= length){return (*this);}
    return (SGEXTN::ApplicationBase::String::repeat(fillChar, length - characterLength()) + (*this));
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::fillRightToByteLength(int length, char fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::fillRightToByteLength crashed because target length is negative");}
    if(byteLength() >= length){return (*this);}
    return ((*this) + SGEXTN::ApplicationBase::String::repeat(fillChar, length - byteLength()));
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::fillRightToCharacterLength(int length, const SGEXTN::ApplicationBase::Character& fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::fillRightToCharacterLength crashed because target length is negative");}
    if(characterLength() >= length){return (*this);}
    return ((*this) + SGEXTN::ApplicationBase::String::repeat(fillChar, length - characterLength()));
}

int SGEXTN::ApplicationBase::String::byteIndexToCharacterIndex(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::byteIndexToCharacterIndex crashed because the index is negative");}
    if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::byteIndexToCharacterIndex crashed because the index points beyond the end of the string");}
    private_computeOffsets();
    int low = 0;
    int high = characterLength();
    while(high - low > 1){
        const int mid = (low + high) / 2;
        if(private_characterOffsets.at(mid) > i){high = mid;}
        else{low = mid;}
    }
    return low;
}

int SGEXTN::ApplicationBase::String::characterIndexToByteIndex(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::characterIndexToByteIndex crashed because the index is negative");}
    if(i >= characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::characterIndexToByteIndex crashed because the index points beyond the end of the string");}
    private_computeOffsets();
    return private_characterOffsets.at(i);
}

short SGEXTN::ApplicationBase::String::parseToShort(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToShort crashed because base is not within 2 to 36 inclusive");}
    long long value = 0;
    bool valid = parseStringToSignedInteger((*this), base, value);
    if(value < static_cast<long long>(SGEXTN::Math::IntegerLimits<short>::minimum()) || value > static_cast<long long>(SGEXTN::Math::IntegerLimits<short>::maximum())){valid = false;}
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return static_cast<short>(value);
}

unsigned short SGEXTN::ApplicationBase::String::parseToUnsignedShort(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToUnsignedShort crashed because base is not within 2 to 36 inclusive");}
    unsigned long long value = 0;
    bool valid = parseStringToInteger((*this), base, value);
    if(value > static_cast<unsigned long long>(SGEXTN::Math::IntegerLimits<unsigned short>::maximum())){valid = false;}
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return static_cast<unsigned short>(value);
}

int SGEXTN::ApplicationBase::String::parseToInt(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToInt crashed because base is not within 2 to 36 inclusive");}
    long long value = 0;
    bool valid = parseStringToSignedInteger((*this), base, value);
    if(value < static_cast<long long>(SGEXTN::Math::IntegerLimits<int>::minimum()) || value > static_cast<long long>(SGEXTN::Math::IntegerLimits<int>::maximum())){valid = false;}
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return static_cast<int>(value);
}

unsigned int SGEXTN::ApplicationBase::String::parseToUnsignedInt(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToUnsignedInt crashed because base is not within 2 to 36 inclusive");}
    unsigned long long value = 0;
    bool valid = parseStringToInteger((*this), base, value);
    if(value > static_cast<unsigned long long>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum())){valid = false;}
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return static_cast<unsigned int>(value);
}

long long SGEXTN::ApplicationBase::String::parseToLongLong(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToLongLong crashed because base is not within 2 to 36 inclusive");}
    long long value = 0;
    const bool valid = parseStringToSignedInteger((*this), base, value);
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return value;
}

unsigned long long SGEXTN::ApplicationBase::String::parseToUnsignedLongLong(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToUnsignedLongLong crashed because base is not within 2 to 36 inclusive");}
    unsigned long long value = 0;
    const bool valid = parseStringToInteger((*this), base, value);
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return value;
}

float SGEXTN::ApplicationBase::String::parseToFloat(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToFloat crashed because base is not within 2 to 36 inclusive");}
    double value = 0.0f;
    const bool valid = parseStringToFloatingPoint((*this), base, value);
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0.0f;}
    return static_cast<float>(value);
}

double SGEXTN::ApplicationBase::String::parseToDouble(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::parseToDouble crashed because base is not within 2 to 36 inclusive");}
    double value = 0.0f;
    const bool valid = parseStringToFloatingPoint((*this), base, value);
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0.0f;}
    return value;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromShort(short x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromShort crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromSignedInteger(static_cast<long long>(x), base);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromUnsignedShort(unsigned short x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromUnsignedShort crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromInteger(static_cast<unsigned long long>(x), base);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromInt(int x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromInt crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromSignedInteger(static_cast<long long>(x), base);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromUnsignedInt(unsigned int x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromUnsignedInt crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromInteger(static_cast<unsigned long long>(x), base);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromLongLong(long long x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromLongLong crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromSignedInteger(x, base);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromUnsignedLongLong(unsigned long long x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromUnsignedLongLong crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromInteger(x, base);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromFloat(float x, int base, SGEXTN::ApplicationBase::FloatPrecisionFormat format, int precision){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromFloat crashed because base is not within 2 to 36 inclusive");}
    if(format != SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace && precision <= 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromFloat crashed because precision is nonpositive");}
    if(static_cast<float>(precision) * SGEXTN::Math::FloatMath<float>::logBase2(static_cast<float>(base)) > 24.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromFloat crashed because precision exceeds maximum numerical precision that a float can represent");}
    return makeStringFromFloatingPoint(static_cast<double>(x), base, format, precision);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::stringFromDouble(double x, int base, SGEXTN::ApplicationBase::FloatPrecisionFormat format, int precision){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromDouble crashed because base is not within 2 to 36 inclusive");}
    if(format != SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace && precision <= 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromDouble crashed because precision is nonpositive");}
    if(static_cast<float>(precision) * SGEXTN::Math::FloatMath<float>::logBase2(static_cast<float>(base)) > 53.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::stringFromDouble crashed because precision exceeds maximum numerical precision that a double precision float can represent");}
    return makeStringFromFloatingPoint(x, base, format, precision);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::prettierScientificNotation() const {
    if(containsCharacters("e") == false){return (*this);}
    const int exponentIndex = findFirstCharactersFromLeft("e");
    const SGEXTN::ApplicationBase::String mantissa = substringCharactersLeft(exponentIndex);
    const int exponent = substringCharactersRight(characterLength() - 1 - exponentIndex).parseToInt(nullptr, 10);
    const SGEXTN::ApplicationBase::String exponentString = SGEXTN::ApplicationBase::String::stringFromInt(exponent, 10);
    SGEXTN::ApplicationBase::String formattedExponent;
    for(int i=0; i<exponentString.characterLength(); i++){
        if(exponentString.getCharacterAt(i) == '2' || exponentString.getCharacterAt(i) == '3'){formattedExponent += SGEXTN::ApplicationBase::Character(0x00b0 + exponentString.getCharacterAt(i).getDecimalDigitValue());}
        else if(exponentString.getCharacterAt(i) == '1'){formattedExponent += SGEXTN::ApplicationBase::Character(0x00b9);}
        else if(exponentString.getCharacterAt(i) == '-'){formattedExponent += SGEXTN::ApplicationBase::Character(0x207b);}
        else{formattedExponent += SGEXTN::ApplicationBase::Character(0x2070 + exponentString.getCharacterAt(i).getDecimalDigitValue());}
    }
    return (mantissa + SGEXTN::ApplicationBase::Character(0x00d7) + "10" + formattedExponent);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::convertNumericSystem(const SGEXTN::ApplicationBase::Character& zeroRepresentation) const {
    if(zeroRepresentation.getDecimalDigitValue() != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::convertNumericSystem crashed because the zero character does not represent a value of 0 in any decimal place value system");}
    const int newZero = zeroRepresentation.getBaseUnicode();
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<characterLength(); i++){
        const int unicode = getCharacterAt(i).getBaseUnicode();
        if(unicode >= 0x0030 && unicode <= 0x0039){output += SGEXTN::ApplicationBase::Character(unicode - 0x0030 + newZero);}
        else{output += SGEXTN::ApplicationBase::Character(unicode);}
    }
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::prepareInnerHtmlText() const {
    return (*this).replaceBytes("&", "&amp;").replaceBytes("<", "&lt;").replaceBytes(">", "&gt;");
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::removeLeadingTrailingWhitespace() const {
    int start = 0;
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isWhitespace() == true){start++;}
        else{break;}
    }
    if(start == characterLength()){return "";}
    int end = characterLength() - 1;
    for(int i=characterLength()-1; i>=0; i--){
        if(getCharacterAt(i).isWhitespace() == true){end--;}
        else{break;}
    }
    return substringCharacters(start, end - start + 1);
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::cleanWhitespace() const {
    int lastCopy = 0;
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isWhitespace() == true){
            if(i - lastCopy > 0){
                if(output != ""){output += " ";}
                output += substringCharacters(lastCopy, i - lastCopy);
            }
            lastCopy = i + 1;
        }
    }
    if(lastCopy != characterLength()){
        output += " ";
        output += substringCharactersRight(characterLength() - lastCopy);
    }
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::removeAllWhitespace() const {
    return cleanWhitespace().replaceCharacters(" ", "");
}

SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> SGEXTN::ApplicationBase::String::split(const SGEXTN::ApplicationBase::String& separator) const {
    if(separator == ""){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::split crashed because separator is empty");}
    int currentIndex = 0;
    SGEXTN::Containers::Vector<SGEXTN::ApplicationBase::String> splitStrings;
    while(true){
        int index = findFirstCharactersFromLeftBounded(currentIndex, separator);
        if(index == -1){break;}
        splitStrings.pushBack(substringCharacters(currentIndex, index - currentIndex));
        currentIndex = index + separator.characterLength();
    }
    splitStrings.pushBack(substringCharacters(currentIndex, characterLength() - currentIndex));
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> output(splitStrings.length());
    for(int i=0; i<splitStrings.length(); i++){
        output.at(i) = splitStrings.at(i);
    }
    return output;
}

bool SGEXTN::ApplicationBase::String::isDigit() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isDigit() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isDigit(int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String::isDigit crashed because base is not within 2 to 36 inclusive");}
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isDigit(base) == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isEnglishLowercase() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isEnglishLowercase() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isEnglishUppercase() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isEnglishUppercase() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isEnglishLetter() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isEnglishLetter() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isEnglishAlphanumeric() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isEnglishAlphanumeric() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isASCII() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isASCII() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isWhitespace() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isWhitespace() == false){return false;}
    }
    return true;
}

bool SGEXTN::ApplicationBase::String::isUppercase() const {
    return ((*this) == getUppercase());
}

bool SGEXTN::ApplicationBase::String::isLowercase() const {
    return ((*this) == getLowercase());
}

bool SGEXTN::ApplicationBase::String::isTitlecase() const {
    return ((*this) == getTitlecase());
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::getUppercase() const {
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<characterLength(); i++){
        output += getCharacterAt(i).getUppercase();
    }
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::getLowercase() const {
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<characterLength(); i++){
        output += getCharacterAt(i).getLowercase();
    }
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::getTitlecase() const {
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<characterLength(); i++){
        output += getCharacterAt(i).getTitlecase();
    }
    return output;
}

SGEXTN::Containers::Array<int> SGEXTN::ApplicationBase::String::getUnicode() const {
    SGEXTN::ApplicationBase::Character unicodeExtractor;
    unicodeExtractor.private_data = private_data;
    return unicodeExtractor.getUnicode();
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::getNormalised(SGEXTN::ApplicationBase::NormalisationFormat format) const {
    SGEXTN::ApplicationBase::String output;
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(format == SGEXTN::ApplicationBase::NormalisationFormat::Join || format == SGEXTN::ApplicationBase::NormalisationFormat::Separate){
        for(int i=0; i<codePoints.length(); i++){
            output += recursiveDecomposeEquivalent(codePoints.at(i));
        }
    }
    else{
        for(int i=0; i<codePoints.length(); i++){
            output += recursiveDecomposeCompatibility(codePoints.at(i));
        }
    }
    output = sortCombiningMarks(output);
    if(format == SGEXTN::ApplicationBase::NormalisationFormat::Join || format == SGEXTN::ApplicationBase::NormalisationFormat::LossyJoin){output = unicodeRecompose(output);}
    return output;
}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::String::getSimplestEquivalent(bool ignoreCase) const {
    SGEXTN::ApplicationBase::String normalisedString = cleanWhitespace().getNormalised(SGEXTN::ApplicationBase::NormalisationFormat::LossySeparate);
    if(ignoreCase == true){normalisedString = normalisedString.getLowercase();}
    SGEXTN::Containers::Array<int> codePoints = normalisedString.getUnicode();
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<codePoints.length(); i++){
        const SGEXTN::ApplicationBase::SimplifiedCharacterType simplifiedType = SGEXTN::ApplicationBase::UnicodeQuery::getSimplifiedType(codePoints.at(i));
        if(SGEXTN::ApplicationBase::UnicodeQuery::getFullType(codePoints.at(i)) != SGEXTN::ApplicationBase::FullCharacterType::PrivateUseCharacter){
            if(simplifiedType == SGEXTN::ApplicationBase::SimplifiedCharacterType::Mark || simplifiedType == SGEXTN::ApplicationBase::SimplifiedCharacterType::Other){continue;}
        }
        output += SGEXTN::ApplicationBase::Character(codePoints.at(i));
    }
    return output;
}