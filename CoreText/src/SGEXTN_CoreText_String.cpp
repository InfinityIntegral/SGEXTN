#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_Containers_Vector.h>
#include <SGEXTN_CoreText_Character.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_CoreText_UnicodeQuery.h>
#include <SGEXTN_Math_IntegerLimits.h>
#include <SGEXTN_Math_FloatMath.h>
#include <SGEXTN_Math_FloatLimits.h>
#include <SGEXTN_Containers_Sort.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Containers_ArrayVectorMove.h>

namespace {
int getValueOfDigit(const SGEXTN::CoreText::Character& c, int base){
    if(base != 10){
        if(c.isDigit() == true){return (static_cast<int>(c.byteAt(0)) - static_cast<int>('0'));}
        if(c.isEnglishLowercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('a'));}
        if(c.isEnglishUppercase() == true){return (10 + static_cast<int>(c.byteAt(0)) - static_cast<int>('A'));}
        return -1;
    }
    return c.getDecimalDigitValue();
}

bool parseStringToInteger(const SGEXTN::CoreText::String& s, int base, unsigned long long& output){
    if(s == "" || s == "+"){return false;}
    unsigned long long ans = 0;
    for(int i=0; i<s.characterLength(); i++){
        if(i == 0 && s.getCharacterAt(i) == '+'){continue;}
        const int digit = getValueOfDigit(s.getCharacterAt(i), base);
        if(digit == -1 || digit >= base){return false;}
        if(SGEXTN::Math::IntegerLimits<unsigned long long>::maximum() / base < ans){return false;}
        ans *= base;
        if(SGEXTN::Math::IntegerLimits<unsigned long long>::maximum() - digit < ans){return false;}
        ans += digit;
    }
    output = ans;
    return true;
}

bool parseStringToSignedInteger(const SGEXTN::CoreText::String& s, int base, long long& output){
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

bool parseMantissa(const SGEXTN::CoreText::String& s, int base, unsigned long long& mantissa, int& exponent){
    if(s == ""){return false;}
    mantissa = 0;
    const int digitLimit = static_cast<int>(SGEXTN::Math::FloatMath<double>::naturalLog(static_cast<double>(SGEXTN::Math::IntegerLimits<unsigned long long>::maximum())) / SGEXTN::Math::FloatMath<double>::naturalLog(static_cast<double>(base)));
    int decimalDotIndex = -1;
    int digitsParsed = 0;
    int nonzeroDigitsParsed = 0;
    int additionalDigits = 0;
    for(int i=0; i<s.characterLength(); i++){
        if(s.getCharacterAt(i) == '.'){
            if(decimalDotIndex != -1){return false;}
            decimalDotIndex = digitsParsed + additionalDigits;
            continue;
        }
        const int verifyDigit = getValueOfDigit(s.getCharacterAt(i), base);
        if(mantissa == 0 && verifyDigit == 0){
            if(decimalDotIndex != -1){digitsParsed++;}
            continue;
        }
        if(verifyDigit == -1 || verifyDigit >= base){return false;}
        if(nonzeroDigitsParsed < digitLimit){
            mantissa = base * mantissa + verifyDigit;
            nonzeroDigitsParsed++;
            digitsParsed++;
        }
        else if(decimalDotIndex == -1){additionalDigits++;}
    }
    if(decimalDotIndex == -1){decimalDotIndex = digitsParsed + additionalDigits;}
    exponent = decimalDotIndex - digitsParsed;
    return true;
}

bool parseScientificNotationExponent(const SGEXTN::CoreText::String& s, int base, int& exponent){
    if(s == "" || s == "+" || s == "-"){return false;}
    bool isNegative = false;
    int ans = 0;
    const int digitLimit = static_cast<int>(SGEXTN::Math::FloatMath<float>::naturalLog(100000.0f) / SGEXTN::Math::FloatMath<float>::naturalLog(static_cast<float>(base)));
    for(int i=0; i<s.characterLength(); i++){
        if(i == 0){
            if(s.getCharacterAt(i) == '+'){continue;}
            if(s.getCharacterAt(i) == '-'){
                isNegative = true;
                continue;
            }
        }
        if(i >= digitLimit){
            for(int j=i; j<s.characterLength(); j++){
                const int verifyDigit = getValueOfDigit(s.getCharacterAt(j), base);
                if(verifyDigit == -1 || verifyDigit >= base){return false;}
            }
            if(isNegative == false){exponent = 100000;}
            else{exponent = -100000;}
            return true;
        }
        const int digit = getValueOfDigit(s.getCharacterAt(i), base);
        if(digit == -1 || digit >= base){return false;}
        ans = base * ans + digit;
    }
    if(isNegative == false){exponent = ans;}
    else{exponent = (-1) * ans;}
    return true;
}

bool parseStringToFloatingPoint(const SGEXTN::CoreText::String& s, int base, double& output){
    if(s == ""){return false;}
    int start = 0;
    int end = -1;
    bool isNegative = false;
    if(s.getCharacterAt(0) == '+'){start = 1;}
    else if(s.getCharacterAt(0) == '-'){
        isNegative = true;
        start = 1;
    }
    if(s.containsCharacters('^') == true){end = s.findFirstCharactersFromRight('^');}
    if(base == 10){
        if(s.containsCharacters('e') == true){end = s.findFirstCharactersFromRight('e');}
        if(s.containsCharacters('E') == true){end = s.findFirstCharactersFromRight('E');}
    }
    unsigned long long mantissa = 0;
    int additionalExponent = 0;
    bool mantissaIsValid = false;
    if(end == -1){mantissaIsValid = parseMantissa(s.substringCharactersRight(s.characterLength() - start), base, mantissa, additionalExponent);}
    else{mantissaIsValid = parseMantissa(s.substringCharacters(start, end - start), base, mantissa, additionalExponent);}
    if(mantissaIsValid == false){return false;}
    if(end != -1){
        bool exponentIsValid = false;
        int exponent = 0;
        exponentIsValid = parseScientificNotationExponent(s.substringCharactersRight(s.characterLength() - end - 1), base, exponent);
        if(exponentIsValid == false){return false;}
        additionalExponent += exponent;
    }
    if(mantissa == 0){
        output = 0.0;
        return true;
    }
    double finalAns = static_cast<double>(mantissa) * SGEXTN::Math::FloatMath<double>::powerOf(static_cast<double>(base), static_cast<double>(additionalExponent));
    if(isNegative == true){finalAns = (-1) * finalAns;}
    output = finalAns;
    return true;
}

SGEXTN::CoreText::Character getDigitStringRepresentation(int x){
    if(x >= 0 && x <= 9){return SGEXTN::CoreText::Character(static_cast<int>('0') + x);}
    if(x >= 10 && x < 36){return SGEXTN::CoreText::Character('a' + x - 10);}
    return SGEXTN::CoreText::Character();
}

SGEXTN::CoreText::String makeStringFromInteger(unsigned long long x, int base){
    if(x == 0){return "0";}
    SGEXTN::CoreText::String reverseNum = "";
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

SGEXTN::CoreText::String makeStringFromSignedInteger(long long x, int base){
    bool isNegative = false;
    if(x == SGEXTN::Math::IntegerLimits<long long>::minimum()){return (SGEXTN::CoreText::String("-") + makeStringFromInteger(static_cast<unsigned long long>(SGEXTN::Math::IntegerLimits<long long>::maximum()) + 1, base));}
    if(x < 0){
        isNegative = true;
        x *= -1;
    }
    SGEXTN::CoreText::String positiveOutput = makeStringFromInteger(static_cast<unsigned long long>(x), base);
    if(isNegative == false){return positiveOutput;}
    return (SGEXTN::CoreText::String("-") + positiveOutput);
}

SGEXTN::CoreText::String makeStringFromFloatingPoint(double x, int base, SGEXTN::CoreText::FloatPrecisionFormat format, int precision){
    if(x == SGEXTN::Math::FloatLimits<double>::notANumber()){return "not a number";}
    if(x == SGEXTN::Math::FloatLimits<double>::positiveInfinity()){return "+infinity";}
    if(x == SGEXTN::Math::FloatLimits<double>::negativeInfinity()){return "-infinity";}
    if(x == 0.0){
        if(format == SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation){
            if(precision == 1){return "0^0";}
            return (SGEXTN::CoreText::String("0.") + SGEXTN::CoreText::String::repeat("0", precision - 1) + "^0");
        }
        if(format == SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit){
            if(precision <= 0){return "0";}
            return (SGEXTN::CoreText::String("0.") + SGEXTN::CoreText::String::repeat("0", precision));
        }
        if(format == SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure){
            if(precision == 1){return "0";}
            return (SGEXTN::CoreText::String("0.") + SGEXTN::CoreText::String::repeat("0", precision - 1));
        }
    }
    bool isNegative = false;
    if(x < 0){
        isNegative = true;
        x *= -1;
    }
    SGEXTN::CoreText::String mantissa;
    int exponent = 0;
    const int logarithm = SGEXTN::Math::FloatMath<double>::floorToInt(SGEXTN::Math::FloatMath<double>::naturalLog(x) / SGEXTN::Math::FloatMath<double>::naturalLog(base));
    if(format == SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit){
        precision += (logarithm + 1);
        if(precision <= 0){
            if(x <= 0.5 * SGEXTN::Math::FloatMath<double>::powerOf(base, logarithm + 1 - precision)){
                precision -= (logarithm + 1);
                if(precision <= 0){return "0";}
                return (SGEXTN::CoreText::String("0.") + SGEXTN::CoreText::String::repeat("0", precision));
            }
        }
    }
    const double roundUpError = 0.5 * SGEXTN::Math::FloatMath<double>::powerOf(base, logarithm + 1 - precision);
    if(x + roundUpError >= SGEXTN::Math::FloatMath<double>::powerOf(base, logarithm + 1)){
        if(format == SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit){precision++;}
        exponent = logarithm + 1;
        mantissa = "1";
    }
    else{
        exponent = logarithm;
        x /= SGEXTN::Math::FloatMath<double>::powerOf(base, logarithm - precision);
        mantissa = makeStringFromInteger(static_cast<unsigned long long>(SGEXTN::Math::FloatMath<double>::round(x)), base);
    }
    SGEXTN::CoreText::String sign;
    if(isNegative == true){sign = "-";}
    mantissa = mantissa.fillRightToCharacterLength(precision, '0');
    if(mantissa.characterLength() > precision){
        const int nextChar = getValueOfDigit(mantissa.getCharacterAt(precision), base);
        mantissa = mantissa.substringCharactersLeft(precision);
        if(2 * nextChar >= base){
            const int lastChar = getValueOfDigit(mantissa.getCharacterAt(mantissa.characterLength() - 1), base);
            if(lastChar == base - 1){
                unsigned long long mantissaValue = 0;
                parseStringToInteger(mantissa, base, mantissaValue);
                mantissa = makeStringFromInteger(mantissaValue + 1, base);
                if(mantissa.characterLength() > precision){
                    if(format == SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit){precision++;}
                    mantissa = mantissa.substringCharactersLeft(precision);
                    exponent++;
                }
            }
            else{mantissa.setCharacterAt(mantissa.characterLength() - 1, getDigitStringRepresentation(lastChar + 1));}
        }
    }
    if(format == SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation){
        mantissa = SGEXTN::CoreText::String((mantissa.getCharacterAt(0))) + "." + mantissa.substringCharactersRight(mantissa.characterLength() - 1);
        SGEXTN::CoreText::String exponentString;
        if(exponent < 0){
            exponentString = "-";
            exponent *= -1;
        }
        exponentString += makeStringFromInteger(exponent, base);
        return (sign + mantissa + "^" + exponentString);
    }
    if(exponent < 0){return (sign + "0." + SGEXTN::CoreText::String::repeat("0", (-1) * exponent - 1) + mantissa);}
    if(mantissa.characterLength() <= exponent + 1){return (sign + mantissa + SGEXTN::CoreText::String::repeat("0", exponent + 1 - mantissa.characterLength()));}
    return (sign + mantissa.substringCharactersLeft(exponent + 1) + "." + mantissa.substringCharactersRight(mantissa.characterLength() - exponent - 1));
}

SGEXTN::CoreText::String decompositionEquivalent(const SGEXTN::CoreText::String& s, bool* done){
    bool isDone = true;
    SGEXTN::CoreText::String output;
    SGEXTN::Containers::Array<int> codePoint = s.getUnicode();
    for(int i=0; i<codePoint.length(); i++){
        const SGEXTN::CoreText::String thisChar = SGEXTN::CoreText::UnicodeQuery::getEquivDecomposition(codePoint.at(i));
        if(thisChar == ""){output += SGEXTN::CoreText::Character(codePoint.at(i));}
        else{
            isDone = false;
            output += thisChar;
        }
    }
    (*done) = isDone;
    return output;
}

SGEXTN::CoreText::String decompositionCompatibility(const SGEXTN::CoreText::String& s, bool* done){
    bool isDone = true;
    SGEXTN::CoreText::String output;
    SGEXTN::Containers::Array<int> codePoint = s.getUnicode();
    for(int i=0; i<codePoint.length(); i++){
        const SGEXTN::CoreText::String thisChar = SGEXTN::CoreText::UnicodeQuery::getCompatDecomposition(codePoint.at(i));
        if(thisChar == ""){output += SGEXTN::CoreText::Character(codePoint.at(i));}
        else{
            isDone = false;
            output += thisChar;
        }
    }
    (*done) = isDone;
    return output;
}

SGEXTN::CoreText::String recursiveDecomposeEquivalent(int i){
    bool done = false;
    SGEXTN::CoreText::String output = SGEXTN::CoreText::Character(i);
    while(done == false){
        output = decompositionEquivalent(output, &done);
    }
    return output;
}

SGEXTN::CoreText::String recursiveDecomposeCompatibility(int i){
    bool done = false;
    SGEXTN::CoreText::String output = SGEXTN::CoreText::Character(i);
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
    return (SGEXTN::CoreText::UnicodeQuery::getCombiningMarkOrder(a) < SGEXTN::CoreText::UnicodeQuery::getCombiningMarkOrder(b));
}

SGEXTN::CoreText::String sortCombiningMarks(const SGEXTN::CoreText::String& s){
    int startSort = 0;
    const int endSort = 0;
    SGEXTN::Containers::Array<int> codePoints = s.getUnicode();
    for(int i=0; i<codePoints.length(); i++){
        if(SGEXTN::CoreText::UnicodeQuery::getCombiningMarkOrder(codePoints.at(i)) == 0){
            if(startSort < i){SGEXTN::Containers::Sort<int, SortByCombiningMarkOrder>::sortArray(codePoints, startSort, i - startSort);}
            startSort = i + 1;
        }
    }
    if(startSort != codePoints.length()){SGEXTN::Containers::Sort<int, SortByCombiningMarkOrder>::sortArray(codePoints, startSort, codePoints.length() - startSort);}
    SGEXTN::CoreText::String output;
    for(int i=0; i<codePoints.length(); i++){
        output += SGEXTN::CoreText::Character(codePoints.at(i));
    }
    return output;
}

SGEXTN::CoreText::String unicodeRecompose(const SGEXTN::CoreText::String& s){
    SGEXTN::Containers::Array<int> unicode = s.getUnicode();
    SGEXTN::CoreText::String output;
    int currentStarterIndex = 0;
    while(currentStarterIndex < unicode.length()){
        for(int secondIndex=currentStarterIndex+1; secondIndex<=unicode.length(); secondIndex++){
            if(secondIndex == unicode.length()){
                currentStarterIndex = unicode.length();
                break;
            }
            if(unicode.at(secondIndex) == -1){continue;}
            const int secondCombiningMarkOrder = SGEXTN::CoreText::UnicodeQuery::getCombiningMarkOrder(unicode.at(secondIndex));
            bool canMerge = true;
            for(int i=currentStarterIndex+1; i<secondIndex; i++){
                if(secondCombiningMarkOrder == 0 && unicode.at(i) != -1){canMerge = false;}
                if(secondCombiningMarkOrder != 0 && unicode.at(i) != -1 && SGEXTN::CoreText::UnicodeQuery::getCombiningMarkOrder(unicode.at(i)) >= secondCombiningMarkOrder){canMerge = false;}
            }
            if(canMerge == true){
                const int mergedCharacter = SGEXTN::CoreText::UnicodeQuery::getBinaryRecomposition(unicode.at(currentStarterIndex), unicode.at(secondIndex));
                if(mergedCharacter != -1){
                    unicode.at(currentStarterIndex) = mergedCharacter;
                    unicode.at(secondIndex) = -1;
                    continue;
                }
            }
            if(secondCombiningMarkOrder == 0){
                currentStarterIndex = secondIndex;
                break;
            }
        }
    }
    for(int i=0; i<unicode.length(); i++){
        if(unicode.at(i) != -1){output += SGEXTN::CoreText::Character(unicode.at(i));}
    }
    return output;
}
}

SGEXTN::CoreText::String::String(const SGEXTN::CoreText::String& x) : private_data(x.private_data) {}

SGEXTN::CoreText::String& SGEXTN::CoreText::String::operator=(const SGEXTN::CoreText::String& x){
    if(this == &x){return (*this);}
    private_data = x.private_data;
    if(private_characterOffsets.length() > 0){private_characterOffsets.clear();}
    return (*this);
}

SGEXTN::CoreText::String::String(SGEXTN::CoreText::String&& x) noexcept : private_data(static_cast<SGEXTN::CoreText::TextBuffer&&>(x.private_data)), private_characterOffsets(static_cast<SGEXTN::Containers::Vector<int>&&>(x.private_characterOffsets)) {}

SGEXTN::CoreText::String& SGEXTN::CoreText::String::operator=(SGEXTN::CoreText::String&& x) noexcept {
    private_data = static_cast<SGEXTN::CoreText::TextBuffer&&>(x.private_data);
    private_characterOffsets = static_cast<SGEXTN::Containers::Vector<int>&&>(x.private_characterOffsets);
    return (*this);
}

SGEXTN::CoreText::String::String(unsigned char c){
    if(c > 0x7f){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String constructor crashed because the given unsigned char does not represent a valid ASCII character");}
    private_data.pushBack(c);
}

SGEXTN::CoreText::String::String(const char* s){
    private_data.pushBack(s);
}

SGEXTN::CoreText::String::String(const SGEXTN::CoreText::Character& c){
    private_data.pushBack(c.private_data, 0, c.private_data.length());
}

bool SGEXTN::CoreText::String::operator==(const SGEXTN::CoreText::String& x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::CoreText::String::operator!=(const SGEXTN::CoreText::String& x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::CoreText::String::operator<(const SGEXTN::CoreText::String& x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::CoreText::String::operator>(const SGEXTN::CoreText::String& x) const {
    return (private_data > x.private_data);
}

bool SGEXTN::CoreText::String::operator<=(const SGEXTN::CoreText::String& x) const {
    return (private_data <= x.private_data);
}

bool SGEXTN::CoreText::String::operator>=(const SGEXTN::CoreText::String& x) const {
    return (private_data >= x.private_data);
}

int SGEXTN::CoreText::String::hash() const {
    return private_data.hash();
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::operator+(const SGEXTN::CoreText::String& x) const {
    SGEXTN::CoreText::String output = (*this);
    output += x;
    return output;
}

SGEXTN::CoreText::String& SGEXTN::CoreText::String::operator+=(const SGEXTN::CoreText::String& x){
    private_invalidateOffsets();
    private_data.pushBack(x.private_data, 0, x.private_data.length());
    return (*this);
}

int SGEXTN::CoreText::String::byteLength() const {
    return private_data.length();
}

int SGEXTN::CoreText::String::characterLength() const {
    private_computeOffsets();
    return (private_characterOffsets.length() - 1);
}

unsigned char& SGEXTN::CoreText::String::byteAt(int i){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::byteAt crashed because the index is negative");}
    if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::byteAt crashed because the index points beyond the end of the string");}
    private_invalidateOffsets();
    return private_data.byteAt(i);
}

const unsigned char& SGEXTN::CoreText::String::byteAt(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::byteAt crashed because the index is negative");}
    if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::byteAt crashed because the index points beyond the end of the string");}
    return private_data.byteAt(i);
}

void SGEXTN::CoreText::String::private_computeOffsets() const {
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
    SGEXTN::Containers::Array<SGEXTN::CoreText::GraphemeSegmentationType> segmentationTypes(unicodeList.length());
    SGEXTN::Containers::Array<SGEXTN::CoreText::GraphemeRuleRelatedType> ruleRelatedTypes(unicodeList.length());
    for(int i=0; i<unicodeList.length(); i++){
        segmentationTypes.at(i) = SGEXTN::CoreText::UnicodeQuery::getGraphemeSegmentationType(unicodeList.at(i));
        ruleRelatedTypes.at(i) = SGEXTN::CoreText::UnicodeQuery::getGraphemeRuleRelatedType(unicodeList.at(i));
    }
    private_characterOffsets.pushBack(0);
    if(unicodeList.length() == 0){return;}
    int lastRegionIndicator = 0;
    for(int i=1; i<unicodeList.length(); i++){
        if(segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::Return && segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::NewLine){continue;}
        if(segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::Return || segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::NewLine || segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::ControlCharacter){
            private_characterOffsets.pushBack(codePointOffset.at(i));
            continue;
        }
        if(segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::Return || segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::NewLine || segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::ControlCharacter){
            private_characterOffsets.pushBack(codePointOffset.at(i));
            continue;
        }
        if(segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeading && (segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeading || segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::HangulVowel || segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowel || segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing)){continue;}
        if((segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowel || segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::HangulVowel) && (segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::HangulVowel || segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::HangulTrailing)){continue;}
        if(segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::HangulTrailing && (segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing || segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::HangulTrailing)){continue;}
        if(segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::ZeroWidthJoiner || segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::Extend){continue;}
        if(segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::SpacingCombiningMark){continue;}
        if(segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::Prepend){continue;}
        if(ruleRelatedTypes.at(i) == SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cConsonant){
            bool foundLinker = false;
            bool foundConsonant = false;
            for(int j=i-1; j>=0; j--){
                if(ruleRelatedTypes.at(j) == SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cLinker){foundLinker = true;}
                if(ruleRelatedTypes.at(j) == SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cConsonant){foundConsonant = true;}
                if(ruleRelatedTypes.at(j) != SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cLinker && ruleRelatedTypes.at(j) != SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cExtend){break;}
            }
            if(foundConsonant == true && foundLinker == true){continue;}
        }
        if(ruleRelatedTypes.at(i) == SGEXTN::CoreText::GraphemeRuleRelatedType::Rule11Emoji && segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::ZeroWidthJoiner){
            bool foundStartEmoji = false;
            for(int j=i-2; j>=0; j--){
                if(ruleRelatedTypes.at(j) == SGEXTN::CoreText::GraphemeRuleRelatedType::Rule11Emoji){foundStartEmoji = true;}
                if(segmentationTypes.at(j) != SGEXTN::CoreText::GraphemeSegmentationType::Extend){break;}
            }
            if(foundStartEmoji == true){continue;}
        }
        if(segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::RegionalIndicator && segmentationTypes.at(i - 1) != SGEXTN::CoreText::GraphemeSegmentationType::RegionalIndicator){lastRegionIndicator = i;}
        if(segmentationTypes.at(i) == SGEXTN::CoreText::GraphemeSegmentationType::RegionalIndicator && segmentationTypes.at(i - 1) == SGEXTN::CoreText::GraphemeSegmentationType::RegionalIndicator){
            if((i - lastRegionIndicator + 1) % 2 == 0){continue;}
        }
        private_characterOffsets.pushBack(codePointOffset.at(i));
    }
    private_characterOffsets.pushBack(byteLength());
}

void SGEXTN::CoreText::String::private_invalidateOffsets() const {
    if(private_characterOffsets.length() > 0){private_characterOffsets.clear();}
}

SGEXTN::CoreText::Character SGEXTN::CoreText::String::getCharacterAt(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::getCharacterAt crashed because index is negative");}
    if(i >= characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::getCharacterAt crashed because index points beyond the end of the string");}
    private_computeOffsets();
    SGEXTN::CoreText::Character c;
    c.private_data = SGEXTN::CoreText::TextBuffer();
    c.private_data.pushBack(private_data, private_characterOffsets.at(i), private_characterOffsets.at(i + 1) - private_characterOffsets.at(i));
    return c;
}

void SGEXTN::CoreText::String::setCharacterAt(int i, const SGEXTN::CoreText::Character& c){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::setCharacterAt crashed because index is negative");}
    if(i >= characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::setCharacterAt crashed because index points beyond the end of the string");}
    private_computeOffsets();
    const int rangeBegin = private_characterOffsets.at(i);
    const int rangeEnd = private_characterOffsets.at(i + 1);
    if(rangeEnd - rangeBegin == c.byteLength()){
        for(int j=rangeBegin; j<rangeEnd; j++){
            byteAt(j) = c.byteAt(j - rangeBegin);
        }
    }
    else{
        SGEXTN::CoreText::TextBuffer newBuffer;
        newBuffer.pushBack(private_data, 0, rangeBegin);
        newBuffer.pushBack(c.private_data, 0, c.byteLength());
        newBuffer.pushBack(private_data, rangeEnd, byteLength() - rangeEnd);
        private_data = newBuffer;
    }
    private_invalidateOffsets();
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::fillBytes(unsigned char c) const {
    SGEXTN::CoreText::String output(*this);
    for(int i=0; i<output.byteLength(); i++){
        output.byteAt(i) = c;
    }
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::fillCharacters(const SGEXTN::CoreText::Character& c) const {
    SGEXTN::CoreText::String output;
    for(int i=0; i<characterLength(); i++){
        output.private_data.pushBack(c.private_data, 0, c.byteLength());
    }
    return output;
}

int SGEXTN::CoreText::String::findFirstBytesFromLeftBounded(int start, const SGEXTN::CoreText::String& s) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstBytesFromLeftBounded crashed because the starting point is negative");}
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstBytesFromLeftBounded crashed because the string to find is empty");}
    for(int i=start; i <= byteLength() - s.byteLength(); i++){
        for(int j=0; j<s.byteLength(); j++){
            if(byteAt(i + j) != s.byteAt(j)){break;}
            if(j == s.byteLength() - 1){return i;}
        }
    }
    return -1;
}

int SGEXTN::CoreText::String::findFirstBytesFromRightBounded(int start, const SGEXTN::CoreText::String& s) const {
    if(start >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstBytesFromRightBounded crashed because the starting point is beyond the end of the string");}
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstBytesFromRightBounded crashed because the string to find is empty");}
    if(start > byteLength() - s.byteLength()){start = byteLength() - s.byteLength();}
    for(int i=start; i>=0; i--){
        for(int j=0; j<s.byteLength(); j++){
            if(byteAt(i + j) != s.byteAt(j)){break;}
            if(j == s.byteLength() - 1){return i;}
        }
    }
    return -1;
}

int SGEXTN::CoreText::String::findFirstBytesFromLeft(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstBytesFromLeft crashed because the string to find is empty");}
    return findFirstBytesFromLeftBounded(0, s);
}

int SGEXTN::CoreText::String::findFirstBytesFromRight(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstBytesFromRight crashed because the string to find is empty");}
    return findFirstBytesFromRightBounded(byteLength() - 1, s);
}

int SGEXTN::CoreText::String::findFirstCharactersFromLeftBounded(int start, const SGEXTN::CoreText::String& s) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstCharactersFromLeftBounded crashed because the starting point is negative");}
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstCharacterFromLeftBounded crashed because the string to find is empty");}
    for(int i=start; i <= characterLength() - s.characterLength(); i++){
        for(int j=0; j<s.characterLength(); j++){
            if(getCharacterAt(i + j) != s.getCharacterAt(j)){break;}
            if(j == s.characterLength() - 1){return i;}
        }
    }
    return -1;
}

int SGEXTN::CoreText::String::findFirstCharactersFromRightBounded(int start, const SGEXTN::CoreText::String& s) const {
    if(start >= characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstCharactersFromRightBounded crashed because the starting point is beyond the end of the string");}
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstCharacterFromRightBounded crashed because the string to find is empty");}
    if(start > characterLength() - s.characterLength()){start = characterLength() - s.characterLength();}
    for(int i=start; i>=0; i--){
        for(int j=0; j<s.characterLength(); j++){
            if(getCharacterAt(i + j) != s.getCharacterAt(j)){break;}
            if(j == s.characterLength() - 1){return i;}
        }
    }
    return -1;
}

int SGEXTN::CoreText::String::findFirstCharactersFromLeft(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstCharacterFromLeft crashed because the string to find is empty");}
    return findFirstCharactersFromLeftBounded(0, s);
}

int SGEXTN::CoreText::String::findFirstCharactersFromRight(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::findFirstCharacterFromRight crashed because the string to find is empty");}
    return findFirstCharactersFromRightBounded(characterLength() - 1, s);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::substringBytes(int start, int length) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringBytes crashed because the starting point is negative");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringBytes crashed because the length is negative");}
    if(length + start > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringBytes crashed because the end point is beyond the end of the string");}
    SGEXTN::CoreText::String output;
    output.private_data.pushBack(private_data, start, length);
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::substringBytesLeft(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringBytesLeft crashed because the length is negative");}
    if(length > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringBytesLeft crashed because the end point is beyond the end of the string");}
    return substringBytes(0, length);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::substringBytesRight(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringBytesRight crashed because the length is negative");}
    if(length > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringBytesRight crashed because the start point is beyond the start of the string");}
    return substringBytes(byteLength() - length, length);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::substringCharacters(int start, int length) const {
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringCharacters crashed because the starting point is negative");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringCharacters crashed because the length is negative");}
    if(length + start > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringCharacters crashed because the end point is beyond the end of the string");}
    private_computeOffsets();
    SGEXTN::CoreText::String output;
    output.private_data.pushBack(private_data, private_characterOffsets.at(start), private_characterOffsets.at(start + length) - private_characterOffsets.at(start));
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::substringCharactersLeft(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringCharactersLeft crashed because the length is negative");}
    if(length > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringCharactersLeft crashed because the end point is beyond the end of the string");}
    return substringCharacters(0, length);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::substringCharactersRight(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringCharactersRight crashed because the length is negative");}
    if(length > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::substringCharactersRight crashed because the start point is beyond the start of the string");}
    return substringCharacters(characterLength() - length, length);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::replaceBytes(const SGEXTN::CoreText::String& oldText, const SGEXTN::CoreText::String& newText) const {
    if(oldText == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::replaceBytes crashed because string to replace is empty");}
    SGEXTN::CoreText::String output;
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

SGEXTN::CoreText::String SGEXTN::CoreText::String::replaceCharacters(const SGEXTN::CoreText::String& oldText, const SGEXTN::CoreText::String& newText) const {
    if(oldText == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::replaceCharacters crashed because string to replace is empty");}
    private_computeOffsets();
    SGEXTN::CoreText::String output;
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

SGEXTN::CoreText::String SGEXTN::CoreText::String::removeBytes(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::removeBytes crashed because string to replace is empty");}
    return replaceBytes(s, "");
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::removeCharacters(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::removeCharacters crashed because string to replace is empty");}
    return replaceCharacters(s, "");
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::insertAtByteIndex(int pos, const SGEXTN::CoreText::String& s) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::insertAtByteIndex crashed because position of insertion is negative");}
    if(pos > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::insertAtByteIndex crashed because position of insertion points to more than 1 space beyond the end of the string");}
    SGEXTN::CoreText::String output;
    if(pos > 0){output.private_data.pushBack(private_data, 0, pos);}
    output.private_data.pushBack(s.private_data, 0, s.byteLength());
    if(pos < byteLength()){output.private_data.pushBack(private_data, pos, byteLength() - pos);}
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::insertAtCharacterIndex(int pos, const SGEXTN::CoreText::String& s) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::insertAtCharacterIndex crashed because position of insertion is negative");}
    if(pos > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::insertAtCharacterIndex crashed because position of insertion points to more than 1 space beyond the end of the string");}
    private_computeOffsets();
    SGEXTN::CoreText::String output;
    if(pos > 0){output.private_data.pushBack(private_data, 0, private_characterOffsets.at(pos));}
    output.private_data.pushBack(s.private_data, 0, s.byteLength());
    if(pos < characterLength()){output.private_data.pushBack(private_data, private_characterOffsets.at(pos), byteLength() - private_characterOffsets.at(pos));}
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::removeAtByteIndex(int pos, int length) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::removeAtByteIndex crashed because the start of the range to remove is negative");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::removeAtByteIndex crashed because the length to remove is negative");}
    if(pos + length > byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::removeAtByteIndex crashed because the end of the range to remove points beyond the end of the string");}
    SGEXTN::CoreText::String output;
    if(pos > 0){output.private_data.pushBack(private_data, 0, pos);}
    if(pos + length < byteLength()){output.private_data.pushBack(private_data, pos + length, byteLength() - pos - length);}
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::removeAtCharacterIndex(int pos, int length) const {
    if(pos < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::removeAtCharacterIndex crashed because the start of the range to remove is negative");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::removeAtCharacterIndex crashed because the length to remove is negative");}
    if(pos + length > characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::removeAtCharacterIndex crashed because the end of the range to remove points beyond the end of the string");}
    private_computeOffsets();
    SGEXTN::CoreText::String output;
    if(pos > 0){output.private_data.pushBack(private_data, 0, private_characterOffsets.at(pos));}
    if(pos + length < characterLength()){output.private_data.pushBack(private_data, private_characterOffsets.at(pos + length), byteLength() - private_characterOffsets.at(pos + length));}
    return output;
}

bool SGEXTN::CoreText::String::containsBytes(const SGEXTN::CoreText::String& s) const {
    return (findFirstBytesFromLeft(s) != -1);
}

bool SGEXTN::CoreText::String::containsCharacters(const SGEXTN::CoreText::String& s) const {
    return (findFirstCharactersFromLeft(s) != -1);
}

bool SGEXTN::CoreText::String::startsWithBytes(const SGEXTN::CoreText::String& s) const {
    if(s.byteLength() > byteLength()){return false;}
    return (substringBytesLeft(s.byteLength()) == s);
}

bool SGEXTN::CoreText::String::startsWithCharacters(const SGEXTN::CoreText::String& s) const {
    if(s.characterLength() > characterLength()){return false;}
    return (substringCharactersLeft(s.characterLength()) == s);
}

bool SGEXTN::CoreText::String::endsWithBytes(const SGEXTN::CoreText::String& s) const {
    if(s.byteLength() > byteLength()){return false;}
    return (substringBytesRight(s.byteLength()) == s);
}

bool SGEXTN::CoreText::String::endsWithCharacters(const SGEXTN::CoreText::String& s) const {
    if(s.characterLength() > characterLength()){return false;}
    return (substringCharactersRight(s.characterLength()) == s);
}

int SGEXTN::CoreText::String::countBytes(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::countBytes crashed because string to count is empty");}
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

int SGEXTN::CoreText::String::countCharacters(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::countCharacters crashed because string to count is empty");}
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

int SGEXTN::CoreText::String::countBytesAllowOverlap(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::countBytesAllowOverlap crashed because string to count is empty");}
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

int SGEXTN::CoreText::String::countCharactersAllowOverlap(const SGEXTN::CoreText::String& s) const {
    if(s == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::countCharactersAllowOverlap crashed because string to count is empty");}
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

SGEXTN::CoreText::String SGEXTN::CoreText::String::repeat(const SGEXTN::CoreText::String& s, int count){
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::repeat crashed because count is negative");}
    SGEXTN::CoreText::String output;
    for(int i=0; i<count; i++){
        output.private_data.pushBack(s.private_data, 0, s.byteLength());
    }
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::fillLeftToByteLength(int length, unsigned char fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::fillLeftToByteLength crashed because target length is negative");}
    if(byteLength() >= length){return (*this);}
    return (SGEXTN::CoreText::String::repeat(fillChar, length - byteLength()) + (*this));
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::fillLeftToCharacterLength(int length, const SGEXTN::CoreText::Character& fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::fillLeftToCharacterLength crashed because target length is negative");}
    if(characterLength() >= length){return (*this);}
    return (SGEXTN::CoreText::String::repeat(fillChar, length - characterLength()) + (*this));
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::fillRightToByteLength(int length, unsigned char fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::fillRightToByteLength crashed because target length is negative");}
    if(byteLength() >= length){return (*this);}
    return ((*this) + SGEXTN::CoreText::String::repeat(fillChar, length - byteLength()));
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::fillRightToCharacterLength(int length, const SGEXTN::CoreText::Character& fillChar) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::fillRightToCharacterLength crashed because target length is negative");}
    if(characterLength() >= length){return (*this);}
    return ((*this) + SGEXTN::CoreText::String::repeat(fillChar, length - characterLength()));
}

int SGEXTN::CoreText::String::byteIndexToCharacterIndex(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::byteIndexToCharacterIndex crashed because the index is negative");}
    if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::byteIndexToCharacterIndex crashed because the index points beyond the end of the string");}
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

int SGEXTN::CoreText::String::characterIndexToByteIndex(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::characterIndexToByteIndex crashed because the index is negative");}
    if(i >= characterLength()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::characterIndexToByteIndex crashed because the index points beyond the end of the string");}
    private_computeOffsets();
    return private_characterOffsets.at(i);
}

short SGEXTN::CoreText::String::parseToShort(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::parseToShort crashed because base is not within 2 to 36 inclusive");}
    long long value = 0;
    bool valid = parseStringToSignedInteger((*this), base, value);
    if(value < static_cast<long long>(SGEXTN::Math::IntegerLimits<short>::minimum()) || value > static_cast<long long>(SGEXTN::Math::IntegerLimits<short>::maximum())){valid = false;}
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return static_cast<short>(value);
}

unsigned short SGEXTN::CoreText::String::parseToUnsignedShort(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::parseToUnsignedShort crashed because base is not within 2 to 36 inclusive");}
    unsigned long long value = 0;
    bool valid = parseStringToInteger((*this), base, value);
    if(value > static_cast<unsigned long long>(SGEXTN::Math::IntegerLimits<unsigned short>::maximum())){valid = false;}
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return static_cast<unsigned short>(value);
}

int SGEXTN::CoreText::String::parseToInt(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::parseToInt crashed because base is not within 2 to 36 inclusive");}
    long long value = 0;
    bool valid = parseStringToSignedInteger((*this), base, value);
    if(value < static_cast<long long>(SGEXTN::Math::IntegerLimits<int>::minimum()) || value > static_cast<long long>(SGEXTN::Math::IntegerLimits<int>::maximum())){valid = false;}
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return static_cast<int>(value);
}

unsigned int SGEXTN::CoreText::String::parseToUnsignedInt(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::parseToUnsignedInt crashed because base is not within 2 to 36 inclusive");}
    unsigned long long value = 0;
    bool valid = parseStringToInteger((*this), base, value);
    if(value > static_cast<unsigned long long>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum())){valid = false;}
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return static_cast<unsigned int>(value);
}

long long SGEXTN::CoreText::String::parseToLongLong(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::parseToLongLong crashed because base is not within 2 to 36 inclusive");}
    long long value = 0;
    const bool valid = parseStringToSignedInteger((*this), base, value);
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return value;
}

unsigned long long SGEXTN::CoreText::String::parseToUnsignedLongLong(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::parseToUnsignedLongLong crashed because base is not within 2 to 36 inclusive");}
    unsigned long long value = 0;
    const bool valid = parseStringToInteger((*this), base, value);
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0;}
    return value;
}

float SGEXTN::CoreText::String::parseToFloat(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::parseToFloat crashed because base is not within 2 to 36 inclusive");}
    double value = 0.0f;
    const bool valid = parseStringToFloatingPoint((*this), base, value);
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0.0f;}
    return static_cast<float>(value);
}

double SGEXTN::CoreText::String::parseToDouble(bool* isValid, int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::parseToDouble crashed because base is not within 2 to 36 inclusive");}
    double value = 0.0f;
    const bool valid = parseStringToFloatingPoint((*this), base, value);
    if(isValid != nullptr){(*isValid) = valid;}
    if(valid == false){return 0.0f;}
    return value;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::stringFromShort(short x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromShort crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromSignedInteger(static_cast<long long>(x), base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::stringFromUnsignedShort(unsigned short x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromUnsignedShort crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromInteger(static_cast<unsigned long long>(x), base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::stringFromInt(int x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromInt crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromSignedInteger(static_cast<long long>(x), base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::stringFromUnsignedInt(unsigned int x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromUnsignedInt crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromInteger(static_cast<unsigned long long>(x), base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::stringFromLongLong(long long x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromLongLong crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromSignedInteger(x, base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::stringFromUnsignedLongLong(unsigned long long x, int base){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromUnsignedLongLong crashed because base is not within 2 to 36 inclusive");}
    return makeStringFromInteger(x, base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::stringFromFloat(float x, int base, SGEXTN::CoreText::FloatPrecisionFormat format, int precision){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromFloat crashed because base is not within 2 to 36 inclusive");}
    if(format != SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit && precision <= 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromFloat crashed because precision is nonpositive");}
    if(format != SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit && static_cast<float>(precision) * SGEXTN::Math::FloatMath<float>::naturalLog(static_cast<float>(base)) > 24.0f){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromFloat crashed because precision exceeds maximum numerical precision that a float can represent");}
    return makeStringFromFloatingPoint(static_cast<double>(x), base, format, precision);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::stringFromDouble(double x, int base, SGEXTN::CoreText::FloatPrecisionFormat format, int precision){
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromDouble crashed because base is not within 2 to 36 inclusive");}
    if(format != SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit && precision <= 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromDouble crashed because precision is nonpositive");}
    if(format != SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit && static_cast<float>(precision) * SGEXTN::Math::FloatMath<float>::naturalLog(static_cast<float>(base)) > 53.0f){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::stringFromDouble crashed because precision exceeds maximum numerical precision that a double precision float can represent");}
    return makeStringFromFloatingPoint(x, base, format, precision);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::prettierScientificNotationBase10() const {
    if(containsCharacters("^") == false){return (*this);}
    const int exponentIndex = findFirstCharactersFromLeft("^");
    const SGEXTN::CoreText::String mantissa = substringCharactersLeft(exponentIndex);
    const int exponent = substringCharactersRight(characterLength() - 1 - exponentIndex).parseToInt(nullptr, 10);
    const SGEXTN::CoreText::String exponentString = SGEXTN::CoreText::String::stringFromInt(exponent, 10);
    SGEXTN::CoreText::String formattedExponent;
    for(int i=0; i<exponentString.characterLength(); i++){
        if(exponentString.getCharacterAt(i) == '2' || exponentString.getCharacterAt(i) == '3'){formattedExponent += SGEXTN::CoreText::Character(0x00b0 + exponentString.getCharacterAt(i).getDecimalDigitValue());}
        else if(exponentString.getCharacterAt(i) == '1'){formattedExponent += SGEXTN::CoreText::Character(0x00b9);}
        else if(exponentString.getCharacterAt(i) == '-'){formattedExponent += SGEXTN::CoreText::Character(0x207b);}
        else{formattedExponent += SGEXTN::CoreText::Character(0x2070 + exponentString.getCharacterAt(i).getDecimalDigitValue());}
    }
    return (mantissa + SGEXTN::CoreText::Character(0x00d7) + "10" + formattedExponent);
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::convertNumericSystem(const SGEXTN::CoreText::Character& zeroRepresentation) const {
    if(zeroRepresentation.getDecimalDigitValue() != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::convertNumericSystem crashed because the zero character does not represent a value of 0 in any decimal place value system");}
    const int newZero = zeroRepresentation.getBaseUnicode();
    SGEXTN::CoreText::String output;
    for(int i=0; i<characterLength(); i++){
        const int unicode = getCharacterAt(i).getBaseUnicode();
        if(unicode >= 0x0030 && unicode <= 0x0039){output += SGEXTN::CoreText::Character(unicode - 0x0030 + newZero);}
        else{output += SGEXTN::CoreText::Character(unicode);}
    }
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::prepareInnerHtmlText() const {
    return (*this).replaceBytes("&", "&amp;").replaceBytes("<", "&lt;").replaceBytes(">", "&gt;");
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::removeLeadingTrailingWhitespace() const {
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

SGEXTN::CoreText::String SGEXTN::CoreText::String::cleanWhitespace() const {
    int lastCopy = 0;
    SGEXTN::CoreText::String output;
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

SGEXTN::CoreText::String SGEXTN::CoreText::String::removeAllWhitespace() const {
    return cleanWhitespace().replaceCharacters(" ", "");
}

SGEXTN::Containers::Array<SGEXTN::CoreText::String> SGEXTN::CoreText::String::split(const SGEXTN::CoreText::String& separator) const {
    if(separator == ""){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::split crashed because separator is empty");}
    int currentIndex = 0;
    SGEXTN::Containers::Vector<SGEXTN::CoreText::String> splitStrings;
    while(true){
        const int index = findFirstCharactersFromLeftBounded(currentIndex, separator);
        if(index == -1){break;}
        splitStrings.pushBack(substringCharacters(currentIndex, index - currentIndex));
        currentIndex = index + separator.characterLength();
    }
    splitStrings.pushBack(substringCharacters(currentIndex, characterLength() - currentIndex));
    return SGEXTN::Containers::ArrayVectorMove<SGEXTN::CoreText::String>::convertToArrayAndDestroyVector(splitStrings);
}

bool SGEXTN::CoreText::String::isDigit() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isDigit() == false){return false;}
    }
    return true;
}

bool SGEXTN::CoreText::String::isDigit(int base) const {
    if(base < 2 || base > 36){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String::isDigit crashed because base is not within 2 to 36 inclusive");}
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isDigit(base) == false){return false;}
    }
    return true;
}

bool SGEXTN::CoreText::String::isEnglishLowercase() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isEnglishLowercase() == false){return false;}
    }
    return true;
}

bool SGEXTN::CoreText::String::isEnglishUppercase() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isEnglishUppercase() == false){return false;}
    }
    return true;
}

bool SGEXTN::CoreText::String::isEnglishLetter() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isEnglishLetter() == false){return false;}
    }
    return true;
}

bool SGEXTN::CoreText::String::isEnglishAlphanumeric() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isEnglishAlphanumeric() == false){return false;}
    }
    return true;
}

bool SGEXTN::CoreText::String::isASCII() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isASCII() == false){return false;}
    }
    return true;
}

bool SGEXTN::CoreText::String::isWhitespace() const {
    for(int i=0; i<characterLength(); i++){
        if(getCharacterAt(i).isWhitespace() == false){return false;}
    }
    return true;
}

bool SGEXTN::CoreText::String::isUppercase() const {
    return ((*this) == getUppercase());
}

bool SGEXTN::CoreText::String::isLowercase() const {
    return ((*this) == getLowercase());
}

bool SGEXTN::CoreText::String::isTitlecase() const {
    return ((*this) == getTitlecase());
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::getUppercase() const {
    SGEXTN::CoreText::String output;
    for(int i=0; i<characterLength(); i++){
        output += getCharacterAt(i).getUppercase();
    }
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::getLowercase() const {
    SGEXTN::CoreText::String output;
    for(int i=0; i<characterLength(); i++){
        output += getCharacterAt(i).getLowercase();
    }
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::getTitlecase() const {
    SGEXTN::CoreText::String output;
    for(int i=0; i<characterLength(); i++){
        output += getCharacterAt(i).getTitlecase();
    }
    return output;
}

SGEXTN::Containers::Array<int> SGEXTN::CoreText::String::getUnicode() const {
    SGEXTN::CoreText::Character unicodeExtractor;
    unicodeExtractor.private_data = private_data;
    return unicodeExtractor.getUnicode();
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::getNormalised(SGEXTN::CoreText::NormalisationFormat format) const {
    SGEXTN::CoreText::String output;
    SGEXTN::Containers::Array<int> codePoints = getUnicode();
    if(format == SGEXTN::CoreText::NormalisationFormat::Join || format == SGEXTN::CoreText::NormalisationFormat::Separate){
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
    if(format == SGEXTN::CoreText::NormalisationFormat::Join || format == SGEXTN::CoreText::NormalisationFormat::LossyJoin){output = unicodeRecompose(output);}
    return output;
}

SGEXTN::CoreText::String SGEXTN::CoreText::String::getSimplestEquivalent(bool ignoreCase) const {
    SGEXTN::CoreText::String normalisedString = cleanWhitespace().getNormalised(SGEXTN::CoreText::NormalisationFormat::LossySeparate);
    if(ignoreCase == true){normalisedString = normalisedString.getLowercase();}
    SGEXTN::Containers::Array<int> codePoints = normalisedString.getUnicode();
    SGEXTN::CoreText::String output;
    for(int i=0; i<codePoints.length(); i++){
        const SGEXTN::CoreText::SimplifiedCharacterType simplifiedType = SGEXTN::CoreText::UnicodeQuery::getSimplifiedType(codePoints.at(i));
        if(SGEXTN::CoreText::UnicodeQuery::getFullType(codePoints.at(i)) != SGEXTN::CoreText::FullCharacterType::PrivateUseCharacter){
            if(simplifiedType == SGEXTN::CoreText::SimplifiedCharacterType::Mark || simplifiedType == SGEXTN::CoreText::SimplifiedCharacterType::Other){continue;}
        }
        output += SGEXTN::CoreText::Character(codePoints.at(i));
    }
    return output;
}