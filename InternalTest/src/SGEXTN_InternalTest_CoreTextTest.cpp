#include <private_api/SGEXTN_InternalTest_CoreTextTest.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_CoreText_UnicodeQuery.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_CoreText_Character.h>
#include <SGEXTN_Math_FloatLimits.h>
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_Pair.h>
#include <SGEXTN_Math_FloatMath.h>
#include <SGEXTN_Containers_Vector.h>
#include <fstream>
#include <ios>
#include <charconv>
#include <cstring>
#include <system_error>

namespace {
bool testExternalUnitTests = false;

bool testAllOfUnicode = true;
bool testUnicodeExternal = true;
bool testNumericParsingExternal = true;

int parseCStringToInt(const char* s, bool* isValid, int base){
    const int length = static_cast<int>(std::strlen(s));
    const char* endPointer = s + length;
    if(length > 0 && s[0] == '+' && (length == 1 || s[1] != '-')){s++;}
    int output = 0;
    const std::from_chars_result parseResult = std::from_chars(s, endPointer, output, base);
    (*isValid) = true;
    if(parseResult.ec != std::errc() || parseResult.ptr != endPointer){(*isValid) = false;}
    if((*isValid) == false){return 0;}
    return output;
}

const char* printIntToCString(int x, int base){
    char* output = new char[50];
    const std::to_chars_result printResult = std::to_chars(output, output + 49, x, base);
    if(printResult.ec == std::errc()){(*printResult.ptr) = '\0';}
    else{(*output) = '\0';}
    return output;
}

float parseCStringToFloat(const char* s, bool* isValid){
    const int length = static_cast<int>(std::strlen(s));
    const char* endPointer = s + length;
    if(length > 0 && s[0] == '+' && (length == 1 || s[1] != '-')){s++;}
    float output = 0.0f;
    const std::from_chars_result parseResult = std::from_chars(s, endPointer, output);
    (*isValid) = true;
    if(parseResult.ec != std::errc() || parseResult.ptr != endPointer){(*isValid) = false;}
    if((*isValid) == false){return 0.0f;}
    return output;
}

SGEXTN::CoreText::String readFile(const SGEXTN::CoreText::String& filePath){
    SGEXTN::CoreText::String pathToFile = "../../InternalTest/assets/";
    pathToFile += filePath;
    pathToFile += '\0';
    const char* rawPath = reinterpret_cast<const char*>(&pathToFile.private_data.byteAt(0));
    std::ifstream file(rawPath, std::ios::binary | std::ios::ate);
    if(file.is_open() == false){return "";}
    const std::streamsize streamSize = file.tellg();
    file.seekg(0, std::ios::beg);
    char* cString = new char[streamSize + 1];
    SGEXTN::CoreText::String outputString;
    if(file.read(cString, streamSize)){
        cString[streamSize] = '\0';
        outputString = cString;
    }
    delete[] cString;
    return outputString;
}

SGEXTN::Containers::Array<SGEXTN::Containers::Array<SGEXTN::CoreText::String>> unicodeDatabase(0x110000, SGEXTN::Containers::Array<SGEXTN::CoreText::String>(15));

void fillUnicodeDatabase(){
    const SGEXTN::CoreText::String dataString = readFile("unicodedata.txt");
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> dataTable = dataString.split('\n');
    SGEXTN::Containers::Array<int> codePoint(dataTable.length());
    for(int i=0; i<dataTable.length(); i++){
        codePoint.at(i) = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft(';')).parseToInt(nullptr, 16);
    }
    for(int i=0; i<dataTable.length(); i++){
        SGEXTN::Containers::Array<SGEXTN::CoreText::String> fields = dataTable.at(i).split(';');
        if(fields.at(1).containsCharacters("First>")){
            const int start = fields.at(0).parseToInt(nullptr, 16);
            const int end = dataTable.at(i + 1).substringCharactersLeft(dataTable.at(i + 1).findFirstCharactersFromLeft(';')).parseToInt(nullptr, 16);
            for(int j=start; j<=end; j++){
                unicodeDatabase.at(j).at(0) = SGEXTN::CoreText::String::stringFromInt(j, 16);
                for(int k=1; k<15; k++){
                    unicodeDatabase.at(j).at(k) = fields.at(k);
                }
            }
            i++;
        }
        else{
            const int codePoint = fields.at(0).parseToInt(nullptr, 16);
            for(int j=0; j<15; j++){
                unicodeDatabase.at(codePoint).at(j) = fields.at(j);
            }
        }
    }
    for(int first=0x1100; first<0x1113; first++){
        for(int second=0x1161; second<0x1176; second++){
            const int combined = 0xac00 + 28 * (21 * (first - 0x1100) + (second - 0x1161));
            unicodeDatabase.at(combined).at(5) = SGEXTN::CoreText::String::stringFromInt(first, 16) + " " + SGEXTN::CoreText::String::stringFromInt(second, 16);
        }
    }
    for(int first=0xac00; first<0xd7a4; first+=28){
        for(int second=0x11a8; second<0x11c3; second++){
            const int combined = first + (second - 0x11a7);
            unicodeDatabase.at(combined).at(5) = SGEXTN::CoreText::String::stringFromInt(first, 16) + " " + SGEXTN::CoreText::String::stringFromInt(second, 16);
        }
    }
}

SGEXTN::CoreText::FullCharacterType parseFullType(const SGEXTN::CoreText::String& s){
    const SGEXTN::CoreText::Character first = s.getCharacterAt(0);
    const SGEXTN::CoreText::Character second = s.getCharacterAt(1);
    if(first == 'M'){
        if(second == 'n'){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(second == 'c'){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(second == 'e'){return SGEXTN::CoreText::FullCharacterType::EnclosingMark;}
    }
    if(first == 'N'){
        if(second == 'd'){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(second == 'l'){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(second == 'o'){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
    }
    if(first == 'Z'){
        if(second == 's'){return SGEXTN::CoreText::FullCharacterType::SpaceBreak;}
        if(second == 'l'){return SGEXTN::CoreText::FullCharacterType::LineBreak;}
        if(second == 'p'){return SGEXTN::CoreText::FullCharacterType::ParagraphBreak;}
    }
    if(first == 'C'){
        if(second == 'c'){return SGEXTN::CoreText::FullCharacterType::ControlCharacter;}
        if(second == 'f'){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(second == 's'){return SGEXTN::CoreText::FullCharacterType::SurrogateCharacter;}
        if(second == 'o'){return SGEXTN::CoreText::FullCharacterType::PrivateUseCharacter;}
        if(second == 'n'){return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;}
    }
    if(first == 'L'){
        if(second == 'u'){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(second == 'l'){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(second == 't'){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(second == 'm'){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(second == 'o'){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    }
    if(first == 'P'){
        if(second == 'c'){return SGEXTN::CoreText::FullCharacterType::ConnectorPunctuation;}
        if(second == 'd'){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(second == 's'){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(second == 'e'){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(second == 'i'){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(second == 'f'){return SGEXTN::CoreText::FullCharacterType::ClosingQuote;}
        if(second == 'o'){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
    }
    if(first == 'S'){
        if(second == 'm'){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(second == 'c'){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(second == 'k'){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(second == 'o'){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    }
    return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
}

SGEXTN::CoreText::SimplifiedCharacterType parseSimplifiedType(const SGEXTN::CoreText::String& s){
    const SGEXTN::CoreText::Character first = s.getCharacterAt(0);
    if(first == 'M'){return SGEXTN::CoreText::SimplifiedCharacterType::Mark;}
    if(first == 'N'){return SGEXTN::CoreText::SimplifiedCharacterType::Number;}
    if(first == 'Z'){return SGEXTN::CoreText::SimplifiedCharacterType::Whitespace;}
    if(first == 'L'){return SGEXTN::CoreText::SimplifiedCharacterType::Letter;}
    if(first == 'P'){return SGEXTN::CoreText::SimplifiedCharacterType::Punctuation;}
    if(first == 'S'){return SGEXTN::CoreText::SimplifiedCharacterType::Symbol;}
    if(first == 'C'){return SGEXTN::CoreText::SimplifiedCharacterType::Other;}
    return SGEXTN::CoreText::SimplifiedCharacterType::Other;
}

float parseRationalNumber(const SGEXTN::CoreText::String& s){
    if(s.containsCharacters('/') == false){return s.parseToFloat(nullptr, 10);}
    const int numerator = s.substringCharactersLeft(s.findFirstCharactersFromLeft('/')).parseToInt(nullptr, 10);
    const int denominator = s.substringCharactersRight(s.characterLength() - 1 - s.findFirstCharactersFromLeft('/')).parseToInt(nullptr, 10);
    return (static_cast<float>(numerator) / static_cast<float>(denominator));
}

SGEXTN::Containers::Array<SGEXTN::CoreText::String> graphemeBreakDatabase(0x110000);

void parseAuxillaryFile(const SGEXTN::CoreText::String& fileName, void (*toDoFunction)(int, const SGEXTN::CoreText::String&)){
    const SGEXTN::CoreText::String dataString = readFile(SGEXTN::CoreText::String(fileName + ".txt"));
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> dataTable = dataString.split('\n');
    for(int i=0; i<dataTable.length(); i++){
        SGEXTN::CoreText::String thisData = dataTable.at(i);
        if(dataTable.at(i).containsCharacters('#') == true){thisData = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft('#'));}
        if(thisData.containsCharacters(';') == false){continue;}
        const SGEXTN::CoreText::String codePoints = thisData.substringCharactersLeft(thisData.findFirstCharactersFromLeft(';'));
        const SGEXTN::CoreText::String propertyValue = thisData.substringCharactersRight(thisData.characterLength() - 1 - thisData.findFirstCharactersFromLeft(';')).removeLeadingTrailingWhitespace();
        int start = -1;
        int end = -1;
        if(codePoints.containsCharacters("..") == false){
            start = codePoints.removeLeadingTrailingWhitespace().parseToInt(nullptr, 16);
            end = start;
        }
        else{
            start = codePoints.substringCharactersLeft(codePoints.findFirstCharactersFromLeft("..")).removeLeadingTrailingWhitespace().parseToInt(nullptr, 16);
            end = codePoints.substringCharactersRight(codePoints.characterLength() - 2 - codePoints.findFirstCharactersFromLeft("..")).removeLeadingTrailingWhitespace().parseToInt(nullptr, 16);
        }
        for(int j=start; j<=end; j++){
            toDoFunction(j, propertyValue);
        }
    }
}

void setGraphemeBreakDatabaseValue(int j, const SGEXTN::CoreText::String& propertyValue){
    graphemeBreakDatabase.at(j) = propertyValue;
}

void fillGraphemeBreakDatabase(){
    parseAuxillaryFile("graphemebreakproperty", &setGraphemeBreakDatabaseValue);
}

SGEXTN::CoreText::GraphemeSegmentationType parseGraphemeSegmentationType(const SGEXTN::CoreText::String& s){
    if(s == "Prepend"){return SGEXTN::CoreText::GraphemeSegmentationType::Prepend;}
    if(s == "CR"){return SGEXTN::CoreText::GraphemeSegmentationType::Return;}
    if(s == "LF"){return SGEXTN::CoreText::GraphemeSegmentationType::NewLine;}
    if(s == "Control"){return SGEXTN::CoreText::GraphemeSegmentationType::ControlCharacter;}
    if(s == "Extend"){return SGEXTN::CoreText::GraphemeSegmentationType::Extend;}
    if(s == "Regional_Indicator"){return SGEXTN::CoreText::GraphemeSegmentationType::RegionalIndicator;}
    if(s == "SpacingMark"){return SGEXTN::CoreText::GraphemeSegmentationType::SpacingCombiningMark;}
    if(s == "L"){return SGEXTN::CoreText::GraphemeSegmentationType::HangulLeading;}
    if(s == "V"){return SGEXTN::CoreText::GraphemeSegmentationType::HangulVowel;}
    if(s == "T"){return SGEXTN::CoreText::GraphemeSegmentationType::HangulTrailing;}
    if(s == "LV"){return SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowel;}
    if(s == "LVT"){return SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing;}
    if(s == "ZWJ"){return SGEXTN::CoreText::GraphemeSegmentationType::ZeroWidthJoiner;}
    return SGEXTN::CoreText::GraphemeSegmentationType::Other;
}

SGEXTN::Containers::Array<SGEXTN::Containers::UnorderedSet<SGEXTN::CoreText::String, SGEXTN::Containers::EqualTo<SGEXTN::CoreText::String>, SGEXTN::Containers::Hash<SGEXTN::CoreText::String>>> derivedCoreDatabase(0x110000);

void appendToDerivedCoreDatabase(int j, const SGEXTN::CoreText::String& propertyValue){
    derivedCoreDatabase.at(j).insert(propertyValue);
}

void fillDerivedCoreDatabase(){
    parseAuxillaryFile("derivedcoreproperties", &appendToDerivedCoreDatabase);
}

SGEXTN::Containers::Array<SGEXTN::CoreText::String> emojiTypeDatabase(0x110000);

void setEmojiTypeDatabaseValue(int j, const SGEXTN::CoreText::String& propertyValue){
    emojiTypeDatabase.at(j) = propertyValue;
}

void fillEmojiTypeDatabase(){
    parseAuxillaryFile("emojidata", &setEmojiTypeDatabaseValue);
}

SGEXTN::CoreText::String parseCodePointList(const SGEXTN::CoreText::String& s){
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> splitStr = s.split(" ");
    SGEXTN::CoreText::String output;
    for(int i=0; i<splitStr.length(); i++){
        output += SGEXTN::CoreText::Character(splitStr.at(i).parseToInt(nullptr, 16));
    }
    return output;
}

SGEXTN::Containers::Array<bool> recomposeExclusionDatabase(0x110000, false);

void fillRecomposeExclusionDatabase(){
    const SGEXTN::CoreText::String dataString = readFile("compositionexclusions.txt");
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> dataTable = dataString.split('\n');
    for(int i=0; i<dataTable.length(); i++){
        if(dataTable.at(i).containsCharacters('#') == false){continue;}
        const SGEXTN::CoreText::String codePoints = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft('#')).removeLeadingTrailingWhitespace();
        if(codePoints.containsCharacters("..") == false){recomposeExclusionDatabase.at(codePoints.parseToInt(nullptr, 16)) = true;}
        else{
            const int start = codePoints.substringCharactersLeft(codePoints.findFirstCharactersFromLeft("..")).parseToInt(nullptr, 16);
            const int end = codePoints.substringCharactersRight(codePoints.characterLength() - 1 - codePoints.findFirstCharactersFromLeft("..")).parseToInt(nullptr, 16);
            for(int j=start; j<=end; j++){
                recomposeExclusionDatabase.at(j) = true;
            }
        }
    }
}

SGEXTN::Containers::Array<SGEXTN::Containers::UnorderedSet<SGEXTN::CoreText::String, SGEXTN::Containers::EqualTo<SGEXTN::CoreText::String>, SGEXTN::Containers::Hash<SGEXTN::CoreText::String>>> propertyListDatabase(0x110000);

void appendToPropertyListDatabase(int j, const SGEXTN::CoreText::String& propertyValue){
    propertyListDatabase.at(j).insert(propertyValue);
}

void fillPropertyListDatabase(){
    parseAuxillaryFile("proplist", &appendToPropertyListDatabase);
}

SGEXTN::Containers::Vector<SGEXTN::Containers::Array<SGEXTN::CoreText::String>> normalisationTestDatabase;

void fillNormalisationTestDatabase(){
    const SGEXTN::CoreText::String dataString = readFile("normalisationtest.txt");
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> dataTable = dataString.split('\n');
    for(int i=0; i<dataTable.length(); i++){
        if(dataTable.at(i).findFirstCharactersFromLeft('#') == -1){continue;}
        const SGEXTN::CoreText::String thisTest = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft('#'));
        SGEXTN::Containers::Array<SGEXTN::CoreText::String> testData = thisTest.split(';');
        if(testData.length() < 5){continue;}
        const SGEXTN::CoreText::String c1 = parseCodePointList(testData.at(0));
        const SGEXTN::CoreText::String c2 = parseCodePointList(testData.at(1));
        const SGEXTN::CoreText::String c3 = parseCodePointList(testData.at(2));
        const SGEXTN::CoreText::String c4 = parseCodePointList(testData.at(3));
        const SGEXTN::CoreText::String c5 = parseCodePointList(testData.at(4));
        normalisationTestDatabase.pushBack(SGEXTN::Containers::Array<SGEXTN::CoreText::String>(c1, c2, c3, c4, c5));
    }
}

SGEXTN::Containers::Vector<SGEXTN::Containers::Pair<SGEXTN::CoreText::String, SGEXTN::CoreText::String>> graphemeBoundaryTestDatabase;

void fillGraphemeBoundaryTestDatabase(){
    const SGEXTN::CoreText::String dataString = readFile("graphemebreaktest.txt");
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> dataTable = dataString.split('\n');
    for(int i=0; i<dataTable.length(); i++){
        if(dataTable.at(i).findFirstCharactersFromLeft('#') == -1){continue;}
        const SGEXTN::CoreText::String thisTest = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft('#')).removeLeadingTrailingWhitespace();
        if(thisTest == ""){continue;}
        SGEXTN::Containers::Array<SGEXTN::CoreText::String> characters = thisTest.split(' ');
        SGEXTN::CoreText::String originalString;
        for(int j=0; j<characters.length(); j++){
            bool isValid = false;
            const int codePoint = characters.at(j).parseToInt(&isValid, 16);
            if(isValid == true){originalString += SGEXTN::CoreText::Character(codePoint);}
        }
        graphemeBoundaryTestDatabase.pushBack(SGEXTN::Containers::Pair<SGEXTN::CoreText::String, SGEXTN::CoreText::String>(originalString, thisTest));
    }
}

bool isCloseEnough(float a, float b){
    if(a < -0.0001 && 1.0001 * a <= b && 0.9999 * a >= b){return true;}
    if(a > 0.0001 && 1.0001 * a >= b && 0.9999 * a <= b){return true;}
    if(b >= a - 0.0001 && b <= a + 0.0001){return true;}
    return false;
}

SGEXTN::Containers::Vector<SGEXTN::CoreText::String> numericParsingTestsDatabase;
int numericParsingTestsDatabaseUniqueFloatLength = 0;

void fillNumericParsingTestsDatabase(){
    const SGEXTN::CoreText::String dataString = readFile("nigeltaotencentrapidjson.txt");
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> dataTable = dataString.split('\n');
    for(int i=0; i<dataTable.length(); i++){
        SGEXTN::Containers::Array<SGEXTN::CoreText::String> thisTest = dataTable.at(i).split(' ');
        if(thisTest.length() != 4){continue;}
        numericParsingTestsDatabase.pushBack(thisTest.at(3));
    }
    const int databaseLength = numericParsingTestsDatabase.length();
    for(int i=0; i<databaseLength; i++){
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String('-') + numericParsingTestsDatabase.at(i));
    }
    numericParsingTestsDatabaseUniqueFloatLength = numericParsingTestsDatabase.length();
    for(int i=0; i<databaseLength; i++){
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String('+') + numericParsingTestsDatabase.at(i));
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String("00000") + numericParsingTestsDatabase.at(i));
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String("+00000") + numericParsingTestsDatabase.at(i));
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String("-00000") + numericParsingTestsDatabase.at(i));
        numericParsingTestsDatabase.pushBack(numericParsingTestsDatabase.at(i) + ".00000");
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String('-') + numericParsingTestsDatabase.at(i) + ".00000");
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String('+') + numericParsingTestsDatabase.at(i) + ".00000");
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String("00000") + numericParsingTestsDatabase.at(i) + ".00000");
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String("+00000") + numericParsingTestsDatabase.at(i) + ".00000");
        numericParsingTestsDatabase.pushBack(SGEXTN::CoreText::String("-00000") + numericParsingTestsDatabase.at(i) + ".00000");
    }
}

bool isNumericalDigit(const SGEXTN::CoreText::Character& c){
    return (c != '+' && c != '-' && c != '.');
}

void countSignificantFigures(int& minimum, int& maximum, const SGEXTN::CoreText::String& s){
    int firstSignificant = -1;
    int maximumLastSignificant = -1;
    int minimumLastSignificant = -1;
    for(int i=0; i<s.characterLength(); i++){
        if(isNumericalDigit(s.getCharacterAt(i)) == true && s.getCharacterAt(i) != '0'){
            firstSignificant = i;
            break;
        }
    }
    if(s.containsCharacters('.') == true){
        minimumLastSignificant = s.characterLength() - 1;
        maximumLastSignificant = s.characterLength() - 1;
    }
    else{
        maximumLastSignificant = s.characterLength() - 1;
        for(int i=s.characterLength()-1; i>=0; i--){
            if(isNumericalDigit(s.getCharacterAt(i)) == true && s.getCharacterAt(i) != '0'){
                minimumLastSignificant = i;
                break;
            }
        }
    }
    minimum = 0;
    maximum = 0;
    if(firstSignificant == -1){firstSignificant = 0;}
    for(int i=firstSignificant; i<=minimumLastSignificant; i++){
        if(isNumericalDigit(s.getCharacterAt(i)) == true){minimum++;}
    }
    for(int i=firstSignificant; i<=maximumLastSignificant; i++){
        if(isNumericalDigit(s.getCharacterAt(i)) == true){maximum++;}
    }
}

void countDecimalPlaces(int& minimum, int& maximum, const SGEXTN::CoreText::String& s){
    if(s.containsCharacters('.') == true){
        minimum = s.characterLength() - 1 - s.findFirstCharactersFromRight('.');
        maximum = minimum;
    }
    else{
        maximum = 0;
        int zeroCount = 0;
        for(int i=s.characterLength()-1; i>=0; i--){
            if(s.getCharacterAt(i) == '0'){zeroCount++;}
            else{break;}
        }
        minimum = (-1) * zeroCount;
    }
    if(minimum == (-1) * s.characterLength()){minimum = -1000;}
}
}

void SGEXTN::InternalTest::CoreTextTest::testAll(){
    SGEXTN::InternalTest::CoreTextTest::testCharacter();
    SGEXTN::InternalTest::CoreTextTest::testString();
    if(testExternalUnitTests == true){
        SGEXTN::InternalTest::CoreTextTest::testUnicodeQuery();
        SGEXTN::InternalTest::CoreTextTest::runExternalUnicodeTests();
        SGEXTN::InternalTest::CoreTextTest::runExternalNumericParsingTests();
    }
}

void SGEXTN::InternalTest::CoreTextTest::testUnicodeQuery(){
    if(testAllOfUnicode == false){return;}
    fillUnicodeDatabase();
    fillGraphemeBreakDatabase();
    fillDerivedCoreDatabase();
    fillEmojiTypeDatabase();
    fillRecomposeExclusionDatabase();
    fillPropertyListDatabase();
    for(int i=0; i<0x110000; i++){
        int uppercase = i;
        if(unicodeDatabase.at(i).at(12) != ""){uppercase = unicodeDatabase.at(i).at(12).parseToInt(nullptr, 16);}
        if(uppercase != SGEXTN::CoreText::UnicodeQuery::getUppercase(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery check uppercase fail");}
        int lowercase = i;
        if(unicodeDatabase.at(i).at(13) != ""){lowercase = unicodeDatabase.at(i).at(13).parseToInt(nullptr, 16);}
        if(lowercase != SGEXTN::CoreText::UnicodeQuery::getLowercase(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery check lowercase fail");}
        int titlecase = i;
        if(unicodeDatabase.at(i).at(14) != ""){titlecase = unicodeDatabase.at(i).at(14).parseToInt(nullptr, 16);}
        if(titlecase != SGEXTN::CoreText::UnicodeQuery::getTitlecase(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery check titlecase fail");}
        bool isWhitespace = false;
        if(propertyListDatabase.at(i).contains("White_Space") == true){isWhitespace = true;}
        if(isWhitespace != SGEXTN::CoreText::UnicodeQuery::isWhitespace(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery check whitespace fail");}
        SGEXTN::CoreText::FullCharacterType fullType = SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
        if(unicodeDatabase.at(i).at(2) != ""){fullType = parseFullType(unicodeDatabase.at(i).at(2));}
        if(fullType != SGEXTN::CoreText::UnicodeQuery::getFullType(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get full type fail");}
        SGEXTN::CoreText::SimplifiedCharacterType simplifiedType = SGEXTN::CoreText::SimplifiedCharacterType::Other;
        if(unicodeDatabase.at(i).at(2) != ""){simplifiedType = parseSimplifiedType(unicodeDatabase.at(i).at(2));}
        if(simplifiedType != SGEXTN::CoreText::UnicodeQuery::getSimplifiedType(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get simplified type fail");}
        int decimalDigit = -1;
        if(unicodeDatabase.at(i).at(6) != ""){decimalDigit = unicodeDatabase.at(i).at(6).parseToInt(nullptr, 16);}
        if(decimalDigit != SGEXTN::CoreText::UnicodeQuery::getDecimalDigitValue(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get decimal digit value fail");}
        float numericalValue = SGEXTN::Math::FloatLimits<float>::negativeInfinity();
        if(unicodeDatabase.at(i).at(8) != ""){numericalValue = parseRationalNumber(unicodeDatabase.at(i).at(8));}
        if(numericalValue != SGEXTN::CoreText::UnicodeQuery::getNumericalValue(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get numerical value fail");}
        SGEXTN::CoreText::GraphemeSegmentationType graphemeSegmentationType = SGEXTN::CoreText::GraphemeSegmentationType::Other;
        if(graphemeBreakDatabase.at(i) != ""){graphemeSegmentationType = parseGraphemeSegmentationType(graphemeBreakDatabase.at(i));}
        if(graphemeSegmentationType != SGEXTN::CoreText::UnicodeQuery::getGraphemeSegmentationType(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get grapheme segmentation type fail");}
        SGEXTN::CoreText::GraphemeRuleRelatedType graphemeRuleRelatedType = SGEXTN::CoreText::GraphemeRuleRelatedType::None;
        if(derivedCoreDatabase.at(i).contains("InCB; Consonant") == true){graphemeRuleRelatedType = SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cConsonant;}
        else if(derivedCoreDatabase.at(i).contains("InCB; Extend") == true){graphemeRuleRelatedType = SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cExtend;}
        else if(derivedCoreDatabase.at(i).contains("InCB; Linker") == true){graphemeRuleRelatedType = SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cLinker;}
        else if(emojiTypeDatabase.at(i) == "Extended_Pictographic"){graphemeRuleRelatedType = SGEXTN::CoreText::GraphemeRuleRelatedType::Rule11Emoji;}
        if(graphemeRuleRelatedType != SGEXTN::CoreText::UnicodeQuery::getGraphemeRuleRelatedType(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get grapheme rule related type fail");}
        int combiningMarkOrder = 0;
        if(unicodeDatabase.at(i).at(3) != ""){combiningMarkOrder = unicodeDatabase.at(i).at(3).parseToInt(nullptr, 10);}
        if(combiningMarkOrder != SGEXTN::CoreText::UnicodeQuery::getCombiningMarkOrder(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get combining mark order fail");}
        SGEXTN::CoreText::String equivDecompose = "";
        if(unicodeDatabase.at(i).at(5) != "" && unicodeDatabase.at(i).at(5).containsCharacters('>') == false){equivDecompose = parseCodePointList(unicodeDatabase.at(i).at(5));}
        if(equivDecompose != SGEXTN::CoreText::UnicodeQuery::getEquivDecomposition(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get equivalent decomposition fail");}
        SGEXTN::CoreText::String compatDecompose = "";
        if(unicodeDatabase.at(i).at(5) != ""){
            if(unicodeDatabase.at(i).at(5).containsCharacters('>') == true){compatDecompose = parseCodePointList(unicodeDatabase.at(i).at(5).substringCharactersRight(unicodeDatabase.at(i).at(5).characterLength() - 1 - unicodeDatabase.at(i).at(5).findFirstCharactersFromLeft('>')).removeLeadingTrailingWhitespace());}
            else{compatDecompose = parseCodePointList(unicodeDatabase.at(i).at(5));}
        }
        if(compatDecompose != SGEXTN::CoreText::UnicodeQuery::getCompatDecomposition(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get compatibility decomposition fail");}
        SGEXTN::Containers::Array<int> equivDecompCodePoints = equivDecompose.getUnicode();
        if(equivDecompCodePoints.length() == 2){
            int recomposedCodePoint = i;
            if(combiningMarkOrder != 0 || SGEXTN::CoreText::UnicodeQuery::getCombiningMarkOrder(equivDecompCodePoints.at(0)) != 0){recomposedCodePoint = -1;}
            if(recomposeExclusionDatabase.at(i) == true){recomposedCodePoint = -1;}
            if(recomposedCodePoint != SGEXTN::CoreText::UnicodeQuery::getBinaryRecomposition(equivDecompCodePoints.at(0), equivDecompCodePoints.at(1))){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::UnicodeQuery get unicode binary recomposition fail");}
        }
    }
}

void SGEXTN::InternalTest::CoreTextTest::testCharacter(){
    if(SGEXTN::CoreText::Character() != SGEXTN::CoreText::Character(0x1f496)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character default value fail");}
    if(SGEXTN::CoreText::Character('A') != SGEXTN::CoreText::Character(65)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character constructor from unsigned char fail");}
    if(SGEXTN::CoreText::Character(reinterpret_cast<const char*>(u8"\U0001f496")) != SGEXTN::CoreText::Character()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character constructor from C string fail");}
    const SGEXTN::CoreText::Character a('a');
    const SGEXTN::CoreText::Character b('b');
    if(a == b){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character equality check fail");}
    if(a != SGEXTN::CoreText::Character(0x61)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character inequality check fail");}
    if(b < a){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character less than operator fail");}
    if(a > b){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character more than operator fail");}
    if(b <= a){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character less than or equal to operator fail");}
    if(a >= b){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character more than or equal to operator fail");}
    SGEXTN::CoreText::Character c;
    if(c.byteLength() != 4){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character check byte length fail");}
    if(c.byteAt(3) != 0x96){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get byte at fail");}
    c.byteAt(3) = 0x97;
    if(c != SGEXTN::CoreText::Character(0x1f497)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character set byte at fail");}
    if(a.baseToAsciiChar() != 'a'){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character convert to C++ unsigned char fail");}
    if(SGEXTN::CoreText::Character('0').isDigit() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 10 fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isDigit() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 10 fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 10 fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 10 fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 10 fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 10 fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 10 fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isDigit(2) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 2 fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 2 fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 2 fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 2 fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 2 fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 2 fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 2 fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 16 fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 16 fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 16 fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 16 fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isDigit(16) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 16 fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isDigit(16) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 16 fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isDigit(16) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 16 fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 36 fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 36 fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 36 fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 36 fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 36 fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 36 fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isDigit(36) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is digit base 36 fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English lowercase fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English lowercase fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isEnglishLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English lowercase fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English lowercase fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isEnglishLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English lowercase fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English lowercase fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English lowercase fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English uppercase fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English uppercase fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English uppercase fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isEnglishUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English uppercase fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English uppercase fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isEnglishUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English uppercase fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English uppercase fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English letter fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English letter fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English letter fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English letter fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English letter fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English letter fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English letter fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English alphanumeric fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English alphanumeric fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English alphanumeric fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English alphanumeric fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English alphanumeric fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English alphanumeric fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isEnglishAlphanumeric() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is English alphanumeric fail for punctuation mark");}
    if(SGEXTN::CoreText::Character('0').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is ASCII fail for digit 0");}
    if(SGEXTN::CoreText::Character('5').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is ASCII fail for digit 5");}
    if(SGEXTN::CoreText::Character('a').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is ASCII fail for small letter a");}
    if(SGEXTN::CoreText::Character('A').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is ASCII fail for capital letter A");}
    if(SGEXTN::CoreText::Character('x').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is ASCII fail for small letter x");}
    if(SGEXTN::CoreText::Character('X').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is ASCII fail for capital letter X");}
    if(SGEXTN::CoreText::Character('/').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is ASCII fail for punctuation mark");}
    if(SGEXTN::CoreText::Character().isASCII() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is ASCII fail for heart");}
    if(SGEXTN::CoreText::Character().isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is whitespace fail for heart");}
    if(SGEXTN::CoreText::Character("A").isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is whitespace fail for English letter");}
    if(SGEXTN::CoreText::Character(" ").isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is whitespace fail for space");}
    if(SGEXTN::CoreText::Character("\t").isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is whitespace fail for tab");}
    if(SGEXTN::CoreText::Character("\n").isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is whitespace fail for newline");}
    if(SGEXTN::CoreText::Character(0x2003).isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is whitespace fail for unicode space");}
    const SGEXTN::CoreText::Character cWithTail(reinterpret_cast<const char*>(u8"\u0063\u0327"));
    if(cWithTail.getBaseUnicode() != 0x63){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get base unicode fail");}
    SGEXTN::Containers::Array<int> codePoints = cWithTail.getUnicode();
    if(codePoints.length() != 2 || codePoints.at(0) != 0x63 || codePoints.at(1) != 0x327){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get unicode fail");}
    if(SGEXTN::CoreText::Character('a').isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is uppercase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').isUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is uppercase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is uppercase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).isUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is uppercase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is uppercase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is uppercase Dz fail");}
    if(SGEXTN::CoreText::Character('a').isLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is lowercase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is lowercase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).isLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is lowercase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is lowercase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is lowercase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is lowercase Dz fail");}
    if(SGEXTN::CoreText::Character('a').isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is titlecase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is titlecase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is titlecase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is titlecase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is titlecase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).isTitlecase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character is titlecase Dz fail");}
    if(SGEXTN::CoreText::Character('a').getUppercase() != SGEXTN::CoreText::Character('A')){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get uppercase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').getUppercase() != SGEXTN::CoreText::Character('A')){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get uppercase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).getUppercase() != SGEXTN::CoreText::Character(0x0391)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get uppercase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).getUppercase() != SGEXTN::CoreText::Character(0x0391)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get uppercase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).getUppercase() != SGEXTN::CoreText::Character(0x4e00)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get uppercase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).getUppercase() != SGEXTN::CoreText::Character(0x01c4)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get uppercase Dz fail");}
    if(SGEXTN::CoreText::Character('a').getLowercase() != SGEXTN::CoreText::Character('a')){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get lowercase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').getLowercase() != SGEXTN::CoreText::Character('a')){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get lowercase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).getLowercase() != SGEXTN::CoreText::Character(0x03b1)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get lowercase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).getLowercase() != SGEXTN::CoreText::Character(0x03b1)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get lowercase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).getLowercase() != SGEXTN::CoreText::Character(0x4e00)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get lowercase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).getLowercase() != SGEXTN::CoreText::Character(0x01c6)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get lowercase Dz fail");}
    if(SGEXTN::CoreText::Character('a').getTitlecase() != SGEXTN::CoreText::Character('A')){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get titlecase English lowercase fail");}
    if(SGEXTN::CoreText::Character('A').getTitlecase() != SGEXTN::CoreText::Character('A')){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get titlecase English uppercase fail");}
    if(SGEXTN::CoreText::Character(0x03b1).getTitlecase() != SGEXTN::CoreText::Character(0x0391)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get titlecase Greek lowercase fail");}
    if(SGEXTN::CoreText::Character(0x0391).getTitlecase() != SGEXTN::CoreText::Character(0x0391)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get titlecase Greek uppercase fail");}
    if(SGEXTN::CoreText::Character(0x4e00).getTitlecase() != SGEXTN::CoreText::Character(0x4e00)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get titlecase Chinese letter fail");}
    if(SGEXTN::CoreText::Character(0x01c5).getTitlecase() != SGEXTN::CoreText::Character(0x01c5)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get titlecase Dz fail");}
    if(SGEXTN::CoreText::Character('0').getDecimalDigitValue() != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get decimal digit value digit zero fail");}
    if(SGEXTN::CoreText::Character(0x0be6).getDecimalDigitValue() != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get decimal digit value Tamil digit zero fail");}
    if(SGEXTN::CoreText::Character(' ').getDecimalDigitValue() != -1){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get decimal digit value space fail");}
    if(SGEXTN::CoreText::Character(0xbd).getDecimalDigitValue() != -1){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get decimal digit value half fraction fail");}
    if(SGEXTN::CoreText::Character('0').getNumericalValue() != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get numerical value digit zero fail");}
    if(SGEXTN::CoreText::Character(0x0be6).getNumericalValue() != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get numerical value Tamil digit zero fail");}
    if(SGEXTN::CoreText::Character(' ').getNumericalValue() != SGEXTN::Math::FloatLimits<float>::negativeInfinity()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get numerical value space fail");}
    if(SGEXTN::CoreText::Character(0xbd).getNumericalValue() != 0.5f){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::Character get numerical value half fraction fail");}
}

#define U8(str) reinterpret_cast<const char*>(u8##str)
void SGEXTN::InternalTest::CoreTextTest::testString(){
    SGEXTN::CoreText::String a('a');
    const SGEXTN::CoreText::String b("b");
    if(b != SGEXTN::CoreText::String('b')){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String constructor from C++ unsigned char fail");}
    if(a != SGEXTN::CoreText::String("a")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String constructor from C string fail");}
    if(a != SGEXTN::CoreText::String(SGEXTN::CoreText::Character('a'))){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String constructor from SGEXTN character fail");}
    if(a == b){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String equality check fail");}
    if((a != b) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String inequality check fail");}
    if(b < a){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String less than operator fail");}
    if(a > b){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String more than operator fail");}
    if(b <= a){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String less than or equal to operator fail");}
    if(a >= b){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String more than or equal to operator fail");}
    if(a + b != "ab"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String string addition fail");}
    a += b;
    if(a != "ab"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String string addition assignment fail");}
    SGEXTN::CoreText::String aAlphaSpaceEpsilonA = U8("\u0061\u03b1\u0301\u0020\u03c3\u0041");
    if(aAlphaSpaceEpsilonA.byteLength() != 9){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check  byte length fail");}
    if(aAlphaSpaceEpsilonA.characterLength() != 5){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check character length fail");}
    if(aAlphaSpaceEpsilonA.byteAt(8) != 'A'){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String get byte at fail");}
    aAlphaSpaceEpsilonA.byteAt(8) = 'B';
    if(aAlphaSpaceEpsilonA.byteAt(8) != 'B'){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String set byte at fail");}
    if(aAlphaSpaceEpsilonA.getCharacterAt(1) != U8("\u03b1\u0301")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String get character at fail");}
    aAlphaSpaceEpsilonA.setCharacterAt(1, U8("\u03b1\u0300"));
    if(aAlphaSpaceEpsilonA.getCharacterAt(1) != U8("\u03b1\u0300")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String set character same length fail");}
    aAlphaSpaceEpsilonA.setCharacterAt(4, U8("\uff21"));
    if(aAlphaSpaceEpsilonA.getCharacterAt(4) != SGEXTN::CoreText::Character(0xff21)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String set character different length fail");}
    if(aAlphaSpaceEpsilonA.fillBytes('0') != "00000000000"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill bytes fail");}
    if(aAlphaSpaceEpsilonA.fillCharacters(U8("\u03b1\u0301")) != U8("\u03b1\u0301\u03b1\u0301\u03b1\u0301\u03b1\u0301\u03b1\u0301")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill characters fail");}
    SGEXTN::CoreText::String bytesFindString = "__ab_aab_abb";
    if(bytesFindString.findFirstBytesFromLeft("ab") != 2){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find bytes from left fail");}
    if(bytesFindString.findFirstBytesFromRight("ab") != 9){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find bytes from right fail");}
    if(bytesFindString.findFirstBytesFromLeftBounded(3, "ab") != 6){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find bytes from left bounded fail");}
    if(bytesFindString.findFirstBytesFromRightBounded(8, "ab") != 6){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find bytes from right bounded fail");}
    SGEXTN::CoreText::String charactersFindString = U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2");
    if(charactersFindString.findFirstCharactersFromLeft(U8("\u03b1\u0300\u03b2")) != 2){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find characters from left fail");}
    if(charactersFindString.findFirstCharactersFromRight(U8("\u03b1\u0300\u03b2")) != 9){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find characters from right fail");}
    if(charactersFindString.findFirstCharactersFromLeftBounded(3, U8("\u03b1\u0300\u03b2")) != 6){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find characters from left bounded fail");}
    if(charactersFindString.findFirstCharactersFromRightBounded(8, U8("\u03b1\u0300\u03b2")) != 6){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find characters from right bounded fail");}
    if(bytesFindString.substringBytes(5, 3) != "aab"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String substring bytes fail");}
    if(bytesFindString.substringBytesLeft(3) != "__a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String substring bytes left fail");}
    if(bytesFindString.substringBytesRight(3) != "abb"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String substring bytes right fail");}
    if(charactersFindString.substringCharacters(5, 3) != U8("\u03b1\u0300\u03b1\u0300\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String substring characters fail");}
    if(charactersFindString.substringCharactersLeft(3) != U8("\u0020\u0020\u03b1\u0300")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String substring characters left fail");}
    if(charactersFindString.substringCharactersRight(3) != U8("\u03b1\u0300\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String substring characters right fail");}
    if(bytesFindString.replaceBytes("ab", 'c') != "__c_ac_cb"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String replace bytes fail");}
    if(charactersFindString.replaceCharacters(U8("\u03b1\u0300\u03b2"), U8("\u03b3")) != U8("\u0020\u0020\u03b3\u0020\u03b1\u0300\u03b3\u0020\u03b3\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String replace characters fail");}
    if(bytesFindString.removeBytes("ab") != "___a_b"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String remove bytes fail");}
    if(charactersFindString.removeCharacters(U8("\u03b1\u0300\u03b2")) != U8("\u0020\u0020\u0020\u03b1\u0300\u0020\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String remove characters fail");}
    if(bytesFindString.insertAtByteIndex(0, "cc") != "cc__ab_aab_abb"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String insert bytes at start fail");}
    if(bytesFindString.insertAtByteIndex(2, "cc") != "__ccab_aab_abb"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String insert bytes at middle fail");}
    if(bytesFindString.insertAtByteIndex(12, "cc") != "__ab_aab_abbcc"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String insert bytes at end fail");}
    if(charactersFindString.insertAtCharacterIndex(0, U8("\u03b3\u03b3")) != U8("\u03b3\u03b3\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String insert characters at start fail");}
    if(charactersFindString.insertAtCharacterIndex(2, U8("\u03b3\u03b3")) != U8("\u0020\u0020\u03b3\u03b3\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String insert characters at middle fail");}
    if(charactersFindString.insertAtCharacterIndex(12, U8("\u03b3\u03b3")) != U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2\u03b3\u03b3")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String insert characters at end fail");}
    if(bytesFindString.removeAtByteIndex(5, 3) != "__ab__abb"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String remove bytes fail");}
    if(charactersFindString.removeAtCharacterIndex(5, 3) != U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String remove characters fail");}
    if(bytesFindString.containsBytes("ab") == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check if contains existing bytes fail");}
    if(bytesFindString.containsBytes("bc") == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check if contains nonexistent bytes fail");}
    if(charactersFindString.containsCharacters(U8("\u03b1\u0300\u03b2")) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check if contains existing characters fail");}
    if(charactersFindString.containsCharacters(U8("\u0300\u03b2")) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check if contains nonexistent characters fail");}
    if(bytesFindString.startsWithBytes("__") == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check start bytes with matched prefix fail");}
    if(bytesFindString.startsWithBytes("_a") == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check start bytes with unmatched prefix fail");}
    if(charactersFindString.startsWithCharacters(U8("\u0020\u0020")) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check start characters with matched prefix fail");}
    if(charactersFindString.startsWithCharacters(U8("\u0020\u03b1\u0300")) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check start characters with unmatched prefix fail");}
    if(bytesFindString.endsWithBytes("bb") == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check end bytes with matched prefix fail");}
    if(bytesFindString.endsWithBytes("ab") == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check end bytes with unmatched prefix fail");}
    if(charactersFindString.endsWithCharacters(U8("\u03b2\u03b2")) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check end characters with matched prefix fail");}
    if(charactersFindString.endsWithCharacters(U8("\u03b1\u0300\u03b2")) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check end characters with unmatched prefix fail");}
    bytesFindString = SGEXTN::CoreText::String::repeat("a", 7);
    charactersFindString = SGEXTN::CoreText::String::repeat(U8("\u03b1\u0300"), 7);
    if(charactersFindString != U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String repeat given string fail");}
    if(bytesFindString.countBytes("aaa") != 2){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String count bytes no overlap fail");}
    if(charactersFindString.countCharacters(U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300")) != 2){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String count characters no overlap fail");}
    if(bytesFindString.countBytesAllowOverlap("aaa") != 5){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String count bytes allow overlap fail");}
    if(charactersFindString.countCharactersAllowOverlap(U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300")) != 5){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String count characters allow overlap fail");}
    if(bytesFindString.fillLeftToByteLength(5, 'b') != bytesFindString){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill left bytes sufficient length fail");}
    if(bytesFindString.fillLeftToByteLength(10, 'b') != "bbbaaaaaaa"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill left bytes insufficient length fail");}
    if(charactersFindString.fillLeftToCharacterLength(5, U8("\u03b2")) != charactersFindString){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill left characters sufficient length fail");}
    if(charactersFindString.fillLeftToCharacterLength(10, U8("\u03b2")) != U8("\u03b2\u03b2\u03b2\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill left characters insufficient length fail");}
    if(bytesFindString.fillRightToByteLength(5, 'b') != bytesFindString){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill right bytes sufficient length fail");}
    if(bytesFindString.fillRightToByteLength(10, 'b') != "aaaaaaabbb"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill right bytes insufficient length fail");}
    if(charactersFindString.fillRightToCharacterLength(5, U8("\u03b2")) != charactersFindString){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill right characters sufficient length fail");}
    if(charactersFindString.fillRightToCharacterLength(10, U8("\u03b2")) != U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b2\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String fill right characters insufficient length fail");}
    if(charactersFindString.byteIndexToCharacterIndex(1) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String convert byte index to character index fail");}
    if(charactersFindString.characterIndexToByteIndex(1) != 4){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String convert character index to byte index fail");}
    SGEXTN::CoreText::String positiveBase10Number = "26";
    SGEXTN::CoreText::String negativeBase10Number = "-26";
    SGEXTN::CoreText::String positiveBase16Number = "1a";
    SGEXTN::CoreText::String negativeBase16Number = "-1A";
    SGEXTN::CoreText::String positiveNonLatinNumber = U8("\u0be8\u0bec");
    SGEXTN::CoreText::String negativeNonLatinNumber = U8("\u002d\u0be8\u0bec");
    SGEXTN::CoreText::String invalidNumber = "2 6";
    bool isValid = false;
    if(positiveBase10Number.parseToShort(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 10 number to short fail");}
    isValid = false;
    if(negativeBase10Number.parseToShort(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 10 number to short fail");}
    isValid = false;
    if(positiveBase16Number.parseToShort(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 16 number to short fail");}
    isValid = false;
    if(negativeBase16Number.parseToShort(&isValid, 16) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 16 number to short fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToShort(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive non Latin number to short fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToShort(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative non Latin number to short fail");}
    isValid = true;
    if(invalidNumber.parseToShort(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to short fail");}
    if(invalidNumber.parseToShort(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to short no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedShort(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 10 number to unsigned short fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedShort(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 16 number to unsigned short fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedShort(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive non Latin number to unsigned short fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedShort(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to unsigned short fail");}
    if(invalidNumber.parseToUnsignedShort(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to unsigned short no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToInt(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 10 number to int fail");}
    isValid = false;
    if(negativeBase10Number.parseToInt(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 10 number to int fail");}
    isValid = false;
    if(positiveBase16Number.parseToInt(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 16 number to int fail");}
    isValid = false;
    if(negativeBase16Number.parseToInt(&isValid, 16) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 16 number to int fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToInt(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive non Latin number to int fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToInt(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative non Latin number to int fail");}
    isValid = true;
    if(invalidNumber.parseToInt(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to int fail");}
    if(invalidNumber.parseToInt(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to int no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedInt(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 10 number to unsigned int fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedInt(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 16 number to unsigned int fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedInt(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive non Latin number to unsigned int fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedInt(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to unsigned int fail");}
    if(invalidNumber.parseToUnsignedInt(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to unsigned int no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 10 number to long long fail");}
    isValid = false;
    if(negativeBase10Number.parseToLongLong(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 10 number to long long fail");}
    isValid = false;
    if(positiveBase16Number.parseToLongLong(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 16 number to long long fail");}
    isValid = false;
    if(negativeBase16Number.parseToLongLong(&isValid, 16) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 16 number to long long fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive non Latin number to long long fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToLongLong(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative non Latin number to long long fail");}
    isValid = true;
    if(invalidNumber.parseToLongLong(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to long long fail");}
    if(invalidNumber.parseToLongLong(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to long long no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 10 number to unsigned long long fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedLongLong(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 16 number to unsigned long long fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive non Latin number to unsigned long long fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedLongLong(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to unsigned long long fail");}
    if(invalidNumber.parseToUnsignedLongLong(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to unsigned long long no success flag fail");}
    positiveBase10Number = "10.5";
    negativeBase10Number = "-010.500";
    const SGEXTN::CoreText::String positiveScientificNotation = "5^-1";
    const SGEXTN::CoreText::String negativeScientificNotation = "-5.0^-01";
    positiveBase16Number = "a.8";
    negativeBase16Number = "-0a.80";
    positiveNonLatinNumber = U8("\u0be6\u002e\u0beb");
    negativeNonLatinNumber = U8("\u002d\u0be6\u0be6\u002e\u0beb\u0be6");
    invalidNumber = "-+0.5";
    isValid = false;
    if(positiveBase10Number.parseToFloat(&isValid, 10) != 10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 10 number to float fail");}
    isValid = false;
    if(negativeBase10Number.parseToFloat(&isValid, 10) != -10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 10 number to float fail");}
    isValid = false;
    if(positiveScientificNotation.parseToFloat(&isValid, 10) != 0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive scientific notation number to float fail");}
    isValid = false;
    if(negativeScientificNotation.parseToFloat(&isValid, 10) != -0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative scientific notation number to float fail");}
    isValid = false;
    if(positiveBase16Number.parseToFloat(&isValid, 16) != 10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 16 number to float fail");}
    isValid = false;
    if(negativeBase16Number.parseToFloat(&isValid, 16) != -10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 16 number to float fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToFloat(&isValid, 10) != 0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive non Latin number to float fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToFloat(&isValid, 10) != -0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative non Latin number to float fail");}
    isValid = true;
    if(invalidNumber.parseToFloat(&isValid, 10) != 0.0f || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to float fail");}
    if(invalidNumber.parseToFloat(nullptr, 10) != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to float no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToDouble(&isValid, 10) != 10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 10 number to double fail");}
    isValid = false;
    if(negativeBase10Number.parseToDouble(&isValid, 10) != -10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 10 number to double fail");}
    isValid = false;
    if(positiveScientificNotation.parseToDouble(&isValid, 10) != 0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive scientific notation number to double fail");}
    isValid = false;
    if(negativeScientificNotation.parseToDouble(&isValid, 10) != -0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative scientific notation number to double fail");}
    isValid = false;
    if(positiveBase16Number.parseToDouble(&isValid, 16) != 10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive base 16 number to double fail");}
    isValid = false;
    if(negativeBase16Number.parseToDouble(&isValid, 16) != -10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative base 16 number to double fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToDouble(&isValid, 10) != 0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse positive non Latin number to double fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToDouble(&isValid, 10) != -0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse negative non Latin number to double fail");}
    isValid = true;
    if(invalidNumber.parseToDouble(&isValid, 10) != 0.0f || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to double fail");}
    if(invalidNumber.parseToDouble(nullptr, 10) != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid number to double no success flag fail");}
    if(SGEXTN::CoreText::String::stringFromShort(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print short positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromShort(-26, 10) != "-26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print short negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromShort(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print short positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromShort(-26, 16) != "-1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print short negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedShort(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print unsigned short positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedShort(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print unsigned short positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromInt(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print int positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromInt(-26, 10) != "-26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print int negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromInt(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print int positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromInt(-26, 16) != "-1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print int negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedInt(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print unsigned int positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedInt(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print unsigned int positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromLongLong(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print long long positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromLongLong(-26, 10) != "-26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print long long negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromLongLong(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print long long positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromLongLong(-26, 16) != "-1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print long long negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedLongLong(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print unsigned long long positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromUnsignedLongLong(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print unsigned long long positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "10.333"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float decimal place mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "-10.333"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float decimal place mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "a.555"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float decimal place mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "-a.555"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float decimal place mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "10.3"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float significant figures mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "-10.3"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float significant figures mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "a.55"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float significant figures mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "-a.55"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float significant figures mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "1.03^1"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float scientific notation mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-1.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "-3.33^-1"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float scientific notation mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "a.55^0"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float scientific notation mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromFloat(-1.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "-5.55^-1"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print float scientific notation mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "10.333"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double decimal place mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "-10.333"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double decimal place mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "a.555"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double decimal place mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) != "-a.555"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double decimal place mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "10.3"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double significant figures mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "-10.3"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double significant figures mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "a.55"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double significant figures mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 3) != "-a.55"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double significant figures mode negative base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "1.03^1"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double scientific notation mode positive base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-1.0f / 3.0f, 10, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "-3.33^-1"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double scientific notation mode negative base 10 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "a.55^0"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double scientific notation mode positive base 16 fail");}
    if(SGEXTN::CoreText::String::stringFromDouble(-1.0f / 3.0f, 16, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 3) != "-5.55^-1"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print double scientific notation mode negative base 16 fail");}
    if(SGEXTN::CoreText::String("-1.23^+09").prettierScientificNotationBase10() != U8("-1.23\u00d710\u2079")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String make scientific notation prettier fail");}
    if(SGEXTN::CoreText::String("12345").convertNumericSystem(0xbe6) != U8("\u0be7\u0be8\u0be9\u0bea\u0beb")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String convert to non Latin numbers fail");}
    if(SGEXTN::CoreText::String("<b> & </b>#").prepareInnerHtmlText() != "&lt;b&gt; &amp; &lt;/b&gt;#"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String HTML escaping fail");}
    if(SGEXTN::CoreText::String("  te xt \t\n  \n \t ").removeLeadingTrailingWhitespace() != "te xt"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String whitespace trimming fail");}
    if(SGEXTN::CoreText::String(" a b \nc\t\t\td    e \n \tfgh   ").cleanWhitespace() != "a b c d e fgh"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String whitespace cleaning fail");}
    if(SGEXTN::CoreText::String(" a b \nc\t\t\td    e \n \tfgh   ").removeAllWhitespace() != "abcdefgh"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String whitespace removal fail");}
    SGEXTN::Containers::Array<SGEXTN::CoreText::String> testSplitString = SGEXTN::CoreText::String(",a, bc, \n\td,,, ,e").split(',');
    if(testSplitString.length() != 8 || testSplitString.at(0) != "" || testSplitString.at(1) != "a" || testSplitString.at(2) != " bc" || testSplitString.at(3) != " \n\td" || testSplitString.at(4) != "" || testSplitString.at(5) != "" || testSplitString.at(6) != " " || testSplitString.at(7) != "e"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String split string fail");}
    if(SGEXTN::CoreText::String("0123456789").isDigit() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check digit base 10 true fail");}
    if(SGEXTN::CoreText::String("0123456789a").isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check digit base 10 false fail");}
    if(SGEXTN::CoreText::String("0123456789abcdefABCDEF").isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check digit base 16 true fail");}
    if(SGEXTN::CoreText::String("0123456789abcdefg").isDigit(16) == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check digit base 16 false fail");}
    if(SGEXTN::CoreText::String("qwerty").isEnglishLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check English lowercase true fail");}
    if(SGEXTN::CoreText::String("qwertY").isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check English lowercase false fail");}
    if(SGEXTN::CoreText::String("QWERTY").isEnglishUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check English uppercase true fail");}
    if(SGEXTN::CoreText::String("QWERTy").isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check English uppercase false fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty").isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check English letter true fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty0").isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check English letter false fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty0123456789").isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check English alphanumeric true fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty0123456789 ").isEnglishAlphanumeric() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check English alphanumeric false fail");}
    if(SGEXTN::CoreText::String("QWERTYqwerty0123456789,.<> ").isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check ASCII true fail");}
    if((SGEXTN::CoreText::String("QWERTYqwerty0123456789,.<> ") + SGEXTN::CoreText::Character(0xbe6)).isASCII() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check ASCII false fail");}
    if(SGEXTN::CoreText::String(" \t\n").isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check whitespace true fail");}
    if(SGEXTN::CoreText::String(" \t\n0").isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check whitespace false fail");}
    if(SGEXTN::CoreText::String(U8("A \u0391\u0300_.")).isUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check uppercase true fail");}
    if(SGEXTN::CoreText::String(U8("A \u0391\u0300_.a")).isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check uppercase false fail");}
    if(SGEXTN::CoreText::String(U8("a \u03b1\u0300_.")).isLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check lowercase true fail");}
    if(SGEXTN::CoreText::String(U8("a \u03b1\u0300_.A")).isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check lowercase false fail");}
    if(SGEXTN::CoreText::String(U8("A \u0391\u0300_.\u01c5")).isTitlecase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check titlecase true fail");}
    if(SGEXTN::CoreText::String(U8("A \u0391\u0300_.\u01c4")).isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String check titlecase false fail");}
    const SGEXTN::CoreText::String changeCaseTestString = U8(" ./aA\u0391\u03b1\u0300\u01c4\u01c5\u01c6\u4000");
    if(changeCaseTestString.getUppercase() != U8(" ./AA\u0391\u0391\u0300\u01c4\u01c4\u01c4\u4000")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String convert to uppercase fail");}
    if(changeCaseTestString.getLowercase() != U8(" ./aa\u03b1\u03b1\u0300\u01c6\u01c6\u01c6\u4000")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String convert to uppercase fail");}
    if(changeCaseTestString.getTitlecase() != U8(" ./AA\u0391\u0391\u0300\u01c5\u01c5\u01c5\u4000")){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String convert to uppercase fail");}
    SGEXTN::Containers::Array<int> unicodeCodePoints = changeCaseTestString.getUnicode();
    SGEXTN::Containers::Array<int> expectedCodePoints = SGEXTN::Containers::Array<int>(0x20, 0x2e, 0x2f, 0x61, 0x41, 0x391, 0x3b1, 0x300, 0x1c4, 0x1c5, 0x1c6, 0x4000);
    if(unicodeCodePoints.length() != expectedCodePoints.length()){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String extract Unicode code points fail");}
    for(int i=0; i<unicodeCodePoints.length(); i++){
        if(unicodeCodePoints.at(i) != expectedCodePoints.at(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String extract Unicode code points fail");}
    }
    const SGEXTN::CoreText::String unsimplifiedString = U8("Caf\u00e8 at Yishun \uff2d\uff32\uff34 \u2122 \n\t \U0001d4a9\U0001d4ae\u2081\u2081");
    if(unsimplifiedString.getSimplestEquivalent(false) != "Cafe at Yishun MRT TM NS11"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String case sensitive simplest string conversion fail");}
    if(unsimplifiedString.getSimplestEquivalent(true) != "cafe at yishun mrt tm ns11"){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String case insensitive simplest string conversion fail");}
}
#undef U8

void SGEXTN::InternalTest::CoreTextTest::runExternalUnicodeTests(){
    if(testUnicodeExternal == false){return;}
    fillNormalisationTestDatabase();
    fillGraphemeBoundaryTestDatabase();
    for(int i=0; i<normalisationTestDatabase.length(); i++){
        if(normalisationTestDatabase.at(i).at(0).getNormalised(SGEXTN::CoreText::NormalisationFormat::Join) != normalisationTestDatabase.at(i).at(1)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFC test invariant 0 fail");}
        if(normalisationTestDatabase.at(i).at(1).getNormalised(SGEXTN::CoreText::NormalisationFormat::Join) != normalisationTestDatabase.at(i).at(1)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFC test invariant 1 fail");}
        if(normalisationTestDatabase.at(i).at(2).getNormalised(SGEXTN::CoreText::NormalisationFormat::Join) != normalisationTestDatabase.at(i).at(1)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFC test invariant 2 fail");}
        if(normalisationTestDatabase.at(i).at(3).getNormalised(SGEXTN::CoreText::NormalisationFormat::Join) != normalisationTestDatabase.at(i).at(3)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFC test invariant 3 fail");}
        if(normalisationTestDatabase.at(i).at(4).getNormalised(SGEXTN::CoreText::NormalisationFormat::Join) != normalisationTestDatabase.at(i).at(3)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFC test invariant 4 fail");}
        if(normalisationTestDatabase.at(i).at(0).getNormalised(SGEXTN::CoreText::NormalisationFormat::Separate) != normalisationTestDatabase.at(i).at(2)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFD test invariant 0 fail");}
        if(normalisationTestDatabase.at(i).at(1).getNormalised(SGEXTN::CoreText::NormalisationFormat::Separate) != normalisationTestDatabase.at(i).at(2)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFD test invariant 1 fail");}
        if(normalisationTestDatabase.at(i).at(2).getNormalised(SGEXTN::CoreText::NormalisationFormat::Separate) != normalisationTestDatabase.at(i).at(2)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFD test invariant 2 fail");}
        if(normalisationTestDatabase.at(i).at(3).getNormalised(SGEXTN::CoreText::NormalisationFormat::Separate) != normalisationTestDatabase.at(i).at(4)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFD test invariant 3 fail");}
        if(normalisationTestDatabase.at(i).at(4).getNormalised(SGEXTN::CoreText::NormalisationFormat::Separate) != normalisationTestDatabase.at(i).at(4)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFD test invariant 4 fail");}
        if(normalisationTestDatabase.at(i).at(0).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossyJoin) != normalisationTestDatabase.at(i).at(3)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKC test invariant 0 fail");}
        if(normalisationTestDatabase.at(i).at(1).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossyJoin) != normalisationTestDatabase.at(i).at(3)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKC test invariant 1 fail");}
        if(normalisationTestDatabase.at(i).at(2).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossyJoin) != normalisationTestDatabase.at(i).at(3)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKC test invariant 2 fail");}
        if(normalisationTestDatabase.at(i).at(3).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossyJoin) != normalisationTestDatabase.at(i).at(3)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKC test invariant 3 fail");}
        if(normalisationTestDatabase.at(i).at(4).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossyJoin) != normalisationTestDatabase.at(i).at(3)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKC test invariant 4 fail");}
        if(normalisationTestDatabase.at(i).at(0).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossySeparate) != normalisationTestDatabase.at(i).at(4)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKD test invariant 0 fail");}
        if(normalisationTestDatabase.at(i).at(1).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossySeparate) != normalisationTestDatabase.at(i).at(4)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKD test invariant 1 fail");}
        if(normalisationTestDatabase.at(i).at(2).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossySeparate) != normalisationTestDatabase.at(i).at(4)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKD test invariant 2 fail");}
        if(normalisationTestDatabase.at(i).at(3).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossySeparate) != normalisationTestDatabase.at(i).at(4)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKD test invariant 3 fail");}
        if(normalisationTestDatabase.at(i).at(4).getNormalised(SGEXTN::CoreText::NormalisationFormat::LossySeparate) != normalisationTestDatabase.at(i).at(4)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String normalisation NFKD test invariant 4 fail");}
    }
    for(int i=0; i<graphemeBoundaryTestDatabase.length(); i++){
        const SGEXTN::CoreText::String originalString = graphemeBoundaryTestDatabase.at(i).first;
        SGEXTN::CoreText::String expectedTestString;
        for(int j=0; j<originalString.characterLength(); j++){
            SGEXTN::Containers::Array<int> codePoints = originalString.getCharacterAt(j).getUnicode();
            expectedTestString += SGEXTN::CoreText::Character(0xf7);
            expectedTestString += " ";
            for(int k=0; k<codePoints.length(); k++){
                if(k != 0){
                    expectedTestString += SGEXTN::CoreText::Character(0xd7);
                    expectedTestString += " ";
                }
                expectedTestString += SGEXTN::CoreText::String::stringFromInt(codePoints.at(k), 16).getUppercase().fillLeftToCharacterLength(4, '0');
                expectedTestString += " ";
            }
        }
        expectedTestString += SGEXTN::CoreText::Character(0xf7);
        if(expectedTestString != graphemeBoundaryTestDatabase.at(i).second){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find character boundary fail");}
    }
}

void SGEXTN::InternalTest::CoreTextTest::runExternalNumericParsingTests(){
    if(testNumericParsingExternal == false){return;}
    fillNumericParsingTestsDatabase();
    for(int i=0; i<numericParsingTestsDatabase.length(); i++){
        bool isValid = false;
        SGEXTN::CoreText::String nullTerminatedString = numericParsingTestsDatabase.at(i) + '\0';
        const int expectedInt = parseCStringToInt(reinterpret_cast<const char*>(&nullTerminatedString.byteAt(0)), &isValid, 10);
        if(isValid == true){
            bool parseSuccess = false;
            if(expectedInt != numericParsingTestsDatabase.at(i).parseToInt(&parseSuccess, 10) || parseSuccess == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse base 10 integer fail");}
            if(expectedInt != numericParsingTestsDatabase.at(i).parseToInt(nullptr, 10)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse base 10 integer no success flag fail");}
            if(i < numericParsingTestsDatabaseUniqueFloatLength){
                for(int base=2; base<=36; base++){
                    const char* intAsCString = printIntToCString(expectedInt, base);
                    const SGEXTN::CoreText::String expectedNumString = intAsCString;
                    delete[] intAsCString;
                    if(expectedNumString.getLowercase() != SGEXTN::CoreText::String::stringFromInt(expectedInt, base)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print integer fail");}
                    parseSuccess = false;
                    if(expectedInt != expectedNumString.getUppercase().parseToInt(&parseSuccess, base) || parseSuccess == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse uppercase integer fail");}
                    parseSuccess = false;
                    if(expectedInt != expectedNumString.getLowercase().parseToInt(&parseSuccess, base) || parseSuccess == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse lowercase integer fail");}
                }
            }
        }
        else{
            bool parseSuccess = true;
            if(numericParsingTestsDatabase.at(i).parseToInt(&parseSuccess, 10) != 0 || parseSuccess == true){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid integer fail");}
        }
        isValid = false;
        const float expectedFloat = parseCStringToFloat(reinterpret_cast<const char*>(&nullTerminatedString.byteAt(0)), &isValid);
        if(isValid == true){
            bool parseSuccess = false;
            if(isCloseEnough(expectedFloat, numericParsingTestsDatabase.at(i).parseToFloat(&parseSuccess, 10)) == false || parseSuccess == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse base 10 floating point number fail");}
            if(isCloseEnough(expectedFloat, numericParsingTestsDatabase.at(i).parseToFloat(nullptr, 10)) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse base 10 floating point number no success flag fail");}
            if(i < numericParsingTestsDatabaseUniqueFloatLength){
                for(int base=2; base<=36; base++){
                    SGEXTN::CoreText::String numString = SGEXTN::CoreText::String::stringFromFloat(expectedFloat, base, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 4);
                    int maximumPrecision = 0;
                    int minimumPrecision = 0;
                    countSignificantFigures(minimumPrecision, maximumPrecision, numString);
                    if(4 < minimumPrecision || 4 > maximumPrecision){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print floating point number by significant figures fail");}
                    float roundError = SGEXTN::Math::FloatMath<float>::absoluteValue(expectedFloat) * SGEXTN::Math::FloatMath<float>::powerOf(static_cast<float>(base), -3.0f);
                    parseSuccess = false;
                    float roundedFloat = numString.parseToFloat(&parseSuccess, base);
                    if(parseSuccess == false || roundedFloat < expectedFloat - roundError || roundedFloat > expectedFloat + roundError){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print floating point number by significant figures fail");}
                    if(SGEXTN::Math::FloatMath<float>::absoluteValue(expectedFloat) < 100.0f){
                        numString = SGEXTN::CoreText::String::stringFromFloat(expectedFloat, base, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 2);
                        countDecimalPlaces(minimumPrecision, maximumPrecision, numString);
                        if(2 < minimumPrecision || 2 > maximumPrecision){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print floating point number by positive decimal places fail");}
                        roundError = 0.5f * SGEXTN::Math::FloatMath<float>::powerOf(static_cast<float>(base), -2.0f) + 0.5f * SGEXTN::Math::FloatMath<float>::powerOf(static_cast<float>(base), -3.0f);
                        parseSuccess = false;
                        roundedFloat = numString.parseToFloat(&parseSuccess, base);
                        if(parseSuccess == false || roundedFloat < expectedFloat - roundError || roundedFloat > expectedFloat + roundError){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print floating point number by positive decimal places fail");}
                    }
                    if(SGEXTN::Math::FloatMath<float>::absoluteValue(expectedFloat) < 1000000.0f){
                        numString = SGEXTN::CoreText::String::stringFromFloat(expectedFloat, base, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, -2);
                        countDecimalPlaces(minimumPrecision, maximumPrecision, numString);
                        if(-2 < minimumPrecision || -2 > maximumPrecision){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print floating point number by negative decimal places fail");}
                        roundError = 0.5f * SGEXTN::Math::FloatMath<float>::powerOf(static_cast<float>(base), 2.0f) + 0.5f * SGEXTN::Math::FloatMath<float>::powerOf(static_cast<float>(base), 1.0f);
                        parseSuccess = false;
                        roundedFloat = numString.parseToFloat(&parseSuccess, base);
                        if(parseSuccess == false || roundedFloat < expectedFloat - roundError || roundedFloat > expectedFloat + roundError){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print floating point number by negative decimal places fail");}
                    }
                    numString = SGEXTN::CoreText::String::stringFromFloat(expectedFloat, base, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 4);
                    maximumPrecision = 0;
                    minimumPrecision = 0;
                    countSignificantFigures(minimumPrecision, maximumPrecision, numString.substringCharactersLeft(numString.findFirstCharactersFromLeft('^')));
                    if(4 < minimumPrecision || 4 > maximumPrecision){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print floating point number by scientific notation fail");}
                    roundError = SGEXTN::Math::FloatMath<float>::absoluteValue(expectedFloat) * SGEXTN::Math::FloatMath<float>::powerOf(static_cast<float>(base), -3.0f);
                    parseSuccess = false;
                    roundedFloat = numString.parseToFloat(&parseSuccess, base);
                    if(parseSuccess == false || roundedFloat < expectedFloat - roundError || roundedFloat > expectedFloat + roundError){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String print floating point number by scientific notation fail");}
                }
            }
        }
        else{
            bool parseSuccess = true;
            const float floatValue = numericParsingTestsDatabase.at(i).parseToFloat(&parseSuccess, 10);
            if(parseSuccess == true && floatValue != 0.0f && SGEXTN::Math::FloatLimits<float>::isInfinite(floatValue) == false){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String parse invalid floating point number fail");}
        }
    }
}