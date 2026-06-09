#include <private_api/SGEXTN_InternalTest_ExternalTest.h>
#include <SGEXTN_Utilities_DateTime.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_CoreText_UnicodeQuery.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_CoreText_Character.h>
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Math_FloatLimits.h>
#include <SGEXTN_Math_FloatMath.h>
#include <SGEXTN_Containers_Vector.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <chrono>
#include <format>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <charconv>
#include <cstring>
#include <system_error>

namespace {
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

SGEXTN::Containers::Vector<SGEXTN::CoreText::String> graphemeBoundaryTestStrings;
SGEXTN::Containers::Vector<SGEXTN::CoreText::String> graphemeBoundaryTestExpectedResults;

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
        graphemeBoundaryTestStrings.pushBack(originalString);
        graphemeBoundaryTestExpectedResults.pushBack(thisTest);
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

bool SGEXTN::InternalTest::ExternalTest::ifTestAll = false;
bool SGEXTN::InternalTest::ExternalTest::ifTestDateTimeExternal = true;
bool SGEXTN::InternalTest::ExternalTest::ifTestUnicodeQueryExternal = true;
bool SGEXTN::InternalTest::ExternalTest::ifTestUnicodeExternal = true;
bool SGEXTN::InternalTest::ExternalTest::ifTestNumericalParsing = true;

void SGEXTN::InternalTest::ExternalTest::testDateTimeExternal(){
    for(int year=-100; year<100; year++){
        for(int month=1; month<=12; month++){
            for(int day=1; day<=31; day++){
                bool isLeapYear = false;
                if((year - 35) % 4 == 0 && (year - 35) % 100 != 0){isLeapYear = true;}
                if((year - 35) % 400 == 0){isLeapYear = true;}
                if(day > 28 && month == 2 && isLeapYear == false){continue;}
                if(day > 29 && month == 2 && isLeapYear == true){continue;}
                if(day == 31 && (month == 4 || month == 6 || month == 9 || month == 11)){continue;}
                const int hour = (year % 24 + 24) % 24;
                const int minute = ((year + month + day) % 60 + 60) % 60;
                const int second = ((year + month + day) % 60 + 60) % 60;
                const std::chrono::sys_days thisDay{std::chrono::year{year + 1965} / std::chrono::month{static_cast<unsigned int>(month)} / std::chrono::day{static_cast<unsigned int>(day)}};
                const std::chrono::sys_time<std::chrono::seconds> externalBeginningOfTime{std::chrono::sys_days{std::chrono::year{1965} / std::chrono::August / 9} + std::chrono::hours{10} + std::chrono::minutes{30}};
                const std::chrono::sys_time<std::chrono::seconds> externalDateTime{thisDay + std::chrono::hours{hour} + std::chrono::minutes{minute} + std::chrono::seconds{second}};
                SGEXTN::Utilities::DateTime thisDateTime(year, month, day, hour, minute, second);
                if(std::chrono::duration_cast<std::chrono::seconds>(externalDateTime - externalBeginningOfTime).count() != thisDateTime.private_data){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime components constructor fail");}
                if(thisDateTime.getPart(SGEXTN::Utilities::TimeUnit::Year) != year){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime get year fail");}
                if(thisDateTime.getPart(SGEXTN::Utilities::TimeUnit::Month) != month){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime get month fail");}
                if(thisDateTime.getPart(SGEXTN::Utilities::TimeUnit::Day) != day){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime get day fail");}
                if(thisDateTime.getPart(SGEXTN::Utilities::TimeUnit::Hour) != hour){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime get hour fail");}
                if(thisDateTime.getPart(SGEXTN::Utilities::TimeUnit::Minute) != minute){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime get minute fail");}
                if(thisDateTime.getPart(SGEXTN::Utilities::TimeUnit::Second) != second){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime get second fail");}
                const SGEXTN::Utilities::DateTime originalDateTime = thisDateTime;
                thisDateTime.setPart(SGEXTN::Utilities::TimeUnit::Year, 0);
                if(thisDateTime != SGEXTN::Utilities::DateTime(0, month, day, hour, minute, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime set year fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Utilities::TimeUnit::Month, 8);
                if(thisDateTime != SGEXTN::Utilities::DateTime(year, 8, day, hour, minute, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime set month fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Utilities::TimeUnit::Day, 9);
                if(thisDateTime != SGEXTN::Utilities::DateTime(year, month, 9, hour, minute, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime set day fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Utilities::TimeUnit::Hour, 10);
                if(thisDateTime != SGEXTN::Utilities::DateTime(year, month, day, 10, minute, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime set hour fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Utilities::TimeUnit::Minute, 30);
                if(thisDateTime != SGEXTN::Utilities::DateTime(year, month, day, hour, 30, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime set minute fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Utilities::TimeUnit::Second, 0);
                if(thisDateTime != SGEXTN::Utilities::DateTime(year, month, day, hour, minute, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime set second fail");}
                thisDateTime = originalDateTime;
                if(thisDateTime.getDayOfWeek() != (std::chrono::weekday{thisDay}).iso_encoding()){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime get day of week fail");}
                if(thisDateTime.getDayOfYear() != static_cast<int>((thisDay - std::chrono::sys_days{std::chrono::year{year + 1965} / std::chrono::January / 1}).count() + 1)){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime get day of year fail");}
                if(thisDateTime.countDaysInMonth() != static_cast<int>(static_cast<unsigned int>((std::chrono::year{year + 1965} / std::chrono::month{static_cast<unsigned int>(month)} / std::chrono::last).day()))){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime count days in month fail");}
                if(thisDateTime.countDaysInYear() != 365 + static_cast<int>((std::chrono::year{year + 1965}).is_leap())){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime count days in year fail");}
                if(thisDateTime.getStartOfDay().private_data != (std::chrono::duration_cast<std::chrono::seconds>(thisDay.time_since_epoch()).count() - externalBeginningOfTime.time_since_epoch().count())){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime start of day fail");}
                if(thisDateTime.getEndOfDay().private_data != std::chrono::duration_cast<std::chrono::seconds>(thisDay.time_since_epoch()).count() - externalBeginningOfTime.time_since_epoch().count() + 86400ll){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime end of day fail");}
                char* weekNumberString = new char[3];
                std::format_to_n(weekNumberString, 2, "{:%V}", externalDateTime);
                (*(weekNumberString + 2)) = '\0';
                if(thisDateTime.getWeekOfYear() != std::atoi(weekNumberString)){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime week count fail");}
                delete[] weekNumberString;
                const int diffYear = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Utilities::DateTime::beginningOfTime(), SGEXTN::Utilities::TimeUnit::Year);
                const int diffMonth = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Utilities::DateTime::beginningOfTime(), SGEXTN::Utilities::TimeUnit::Month);
                if(diffMonth < 0 || diffMonth > 11){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime time after display part month fail");}
                const int diffDay = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Utilities::DateTime::beginningOfTime(), SGEXTN::Utilities::TimeUnit::Day);
                if(diffDay < 0 || diffDay > 30){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime time after display part day fail");}
                const int diffHour = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Utilities::DateTime::beginningOfTime(), SGEXTN::Utilities::TimeUnit::Hour);
                if(diffHour < 0 || diffHour > 23){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime time after display part hour fail");}
                const int diffMinute = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Utilities::DateTime::beginningOfTime(), SGEXTN::Utilities::TimeUnit::Minute);
                if(diffMinute < 0 || diffMinute > 59){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime time after display part minute fail");}
                const int diffSecond = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Utilities::DateTime::beginningOfTime(), SGEXTN::Utilities::TimeUnit::Second);
                if(diffSecond < 0 || diffSecond > 59){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime time after display part second fail");}
                SGEXTN::Utilities::DateTime zero = SGEXTN::Utilities::DateTime::beginningOfTime();
                zero.advanceTime(diffYear, SGEXTN::Utilities::TimeUnit::Year);
                zero.advanceTime(diffMonth, SGEXTN::Utilities::TimeUnit::Month);
                zero.advanceTime(diffDay, SGEXTN::Utilities::TimeUnit::Day);
                zero.advanceTime(diffHour, SGEXTN::Utilities::TimeUnit::Hour);
                zero.advanceTime(diffMinute, SGEXTN::Utilities::TimeUnit::Minute);
                zero.advanceTime(diffSecond, SGEXTN::Utilities::TimeUnit::Second);
                if(zero != thisDateTime){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime advance time fail");}
            }
        }
    }
}

void SGEXTN::InternalTest::ExternalTest::testUnicodeQueryExternal(){
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

void SGEXTN::InternalTest::ExternalTest::testUnicodeExternal(){
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
    for(int i=0; i<graphemeBoundaryTestStrings.length(); i++){
        const SGEXTN::CoreText::String& originalString = graphemeBoundaryTestStrings.at(i);
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
        if(expectedTestString != graphemeBoundaryTestExpectedResults.at(i)){SGEXTN::Containers::Crash::crash("SGEXTN::CoreText::String find character boundary fail");}
    }
}

void SGEXTN::InternalTest::ExternalTest::testNumericalParsing(){
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

void SGEXTN::InternalTest::ExternalTest::testAll(){
    if(SGEXTN::InternalTest::ExternalTest::ifTestAll == false){return;}
    if(SGEXTN::InternalTest::ExternalTest::ifTestDateTimeExternal == true){SGEXTN::InternalTest::ExternalTest::testDateTimeExternal();}
    if(SGEXTN::InternalTest::ExternalTest::ifTestUnicodeQueryExternal == true){SGEXTN::InternalTest::ExternalTest::testUnicodeQueryExternal();}
    if(SGEXTN::InternalTest::ExternalTest::ifTestUnicodeExternal == true){SGEXTN::InternalTest::ExternalTest::testUnicodeExternal();}
    if(SGEXTN::InternalTest::ExternalTest::ifTestNumericalParsing == true){SGEXTN::InternalTest::ExternalTest::testNumericalParsing();}
}