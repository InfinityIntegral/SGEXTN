#include <private_api/SGEXTN_InternalTest_StringTest.h>
#include <QFile>
#include <QByteArray>
#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_ApplicationBase_UnicodeQuery.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_ApplicationBase_Character.h>
#include <SGEXTN_Math_FloatLimits.h>
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>

namespace {
bool testAllOfUnicode = false;

SGEXTN::ApplicationBase::String readFile(const SGEXTN::ApplicationBase::String& filePath){
    if(filePath == ""){return "";}
    QByteArray data;
    QFile file(QString::fromUtf8(reinterpret_cast<const char*>(&filePath.private_data.byteAt(0)), filePath.byteLength()));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        data = file.readAll();
        file.close();
    }
    return SGEXTN::ApplicationBase::String(data.constData());
}

SGEXTN::Containers::Array<SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String>> unicodeDatabase(0x110000, SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String>(15));

void fillUnicodeDatabase(){
    SGEXTN::ApplicationBase::String dataString = readFile(":/SGEXTN_InternalTest/unicodedata.txt");
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> dataTable = dataString.split('\n');
    SGEXTN::Containers::Array<int> codePoint(dataTable.length());
    for(int i=0; i<dataTable.length(); i++){
        codePoint.at(i) = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft(';')).parseToInt(nullptr, 16);
    }
    for(int i=0; i<dataTable.length(); i++){
        SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> fields = dataTable.at(i).split(';');
        if(fields.at(1).containsCharacters("First>")){
            int start = fields.at(0).parseToInt(nullptr, 16);
            int end = dataTable.at(i + 1).substringCharactersLeft(dataTable.at(i + 1).findFirstCharactersFromLeft(';')).parseToInt(nullptr, 16);
            for(int j=start; j<=end; j++){
                unicodeDatabase.at(j).at(0) = SGEXTN::ApplicationBase::String::stringFromInt(j, 16);
                for(int k=1; k<15; k++){
                    unicodeDatabase.at(j).at(k) = fields.at(k);
                }
            }
            i++;
        }
        else{
            int codePoint = fields.at(0).parseToInt(nullptr, 16);
            for(int j=0; j<15; j++){
                unicodeDatabase.at(codePoint).at(j) = fields.at(j);
            }
        }
    }
}

SGEXTN::ApplicationBase::FullCharacterType parseFullType(const SGEXTN::ApplicationBase::String& s){
    SGEXTN::ApplicationBase::Character first = s.getCharacterAt(0);
    SGEXTN::ApplicationBase::Character second = s.getCharacterAt(1);
    if(first == 'M'){
        if(second == 'n'){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingCombiningMark;}
        if(second == 'c'){return SGEXTN::ApplicationBase::FullCharacterType::SpacingCombiningMark;}
        if(second == 'e'){return SGEXTN::ApplicationBase::FullCharacterType::EnclosingMark;}
    }
    if(first == 'N'){
        if(second == 'd'){return SGEXTN::ApplicationBase::FullCharacterType::DecimalDigit;}
        if(second == 'l'){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(second == 'o'){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
    }
    if(first == 'Z'){
        if(second == 's'){return SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak;}
        if(second == 'l'){return SGEXTN::ApplicationBase::FullCharacterType::LineBreak;}
        if(second == 'p'){return SGEXTN::ApplicationBase::FullCharacterType::ParagraphBreak;}
    }
    if(first == 'C'){
        if(second == 'c'){return SGEXTN::ApplicationBase::FullCharacterType::ControlCharacter;}
        if(second == 'f'){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(second == 's'){return SGEXTN::ApplicationBase::FullCharacterType::SurrogateCharacter;}
        if(second == 'o'){return SGEXTN::ApplicationBase::FullCharacterType::PrivateUseCharacter;}
        if(second == 'n'){return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;}
    }
    if(first == 'L'){
        if(second == 'u'){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(second == 'l'){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(second == 't'){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(second == 'm'){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(second == 'o'){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    }
    if(first == 'P'){
        if(second == 'c'){return SGEXTN::ApplicationBase::FullCharacterType::ConnectorPunctuation;}
        if(second == 'd'){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(second == 's'){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(second == 'e'){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(second == 'i'){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(second == 'f'){return SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote;}
        if(second == 'o'){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
    }
    if(first == 'S'){
        if(second == 'm'){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(second == 'c'){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(second == 'k'){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(second == 'o'){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    }
    return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
}

SGEXTN::ApplicationBase::SimplifiedCharacterType parseSimplifiedType(const SGEXTN::ApplicationBase::String& s){
    SGEXTN::ApplicationBase::Character first = s.getCharacterAt(0);
    if(first == 'M'){return SGEXTN::ApplicationBase::SimplifiedCharacterType::Mark;}
    if(first == 'N'){return SGEXTN::ApplicationBase::SimplifiedCharacterType::Number;}
    if(first == 'Z'){return SGEXTN::ApplicationBase::SimplifiedCharacterType::Whitespace;}
    if(first == 'L'){return SGEXTN::ApplicationBase::SimplifiedCharacterType::Letter;}
    if(first == 'P'){return SGEXTN::ApplicationBase::SimplifiedCharacterType::Punctuation;}
    if(first == 'S'){return SGEXTN::ApplicationBase::SimplifiedCharacterType::Symbol;}
    if(first == 'C'){return SGEXTN::ApplicationBase::SimplifiedCharacterType::Other;}
    return SGEXTN::ApplicationBase::SimplifiedCharacterType::Other;
}

float parseRationalNumber(const SGEXTN::ApplicationBase::String& s){
    if(s.containsCharacters('/') == false){return s.parseToFloat(nullptr, 10);}
    int numerator = s.substringCharactersLeft(s.findFirstCharactersFromLeft('/')).parseToInt(nullptr, 10);
    int denominator = s.substringCharactersRight(s.characterLength() - 1 - s.findFirstCharactersFromLeft('/')).parseToInt(nullptr, 10);
    return (static_cast<float>(numerator) / static_cast<float>(denominator));
}

SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> graphemeBreakDatabase(0x110000);

void parseAuxillaryFile(const SGEXTN::ApplicationBase::String& fileName, void (*toDoFunction)(int, const SGEXTN::ApplicationBase::String&)){
    SGEXTN::ApplicationBase::String dataString = readFile(SGEXTN::ApplicationBase::String(":/SGEXTN_InternalTest/") + fileName + ".txt");
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> dataTable = dataString.split('\n');
    for(int i=0; i<dataTable.length(); i++){
        SGEXTN::ApplicationBase::String thisData = dataTable.at(i);
        if(dataTable.at(i).containsCharacters('#') == true){thisData = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft('#'));}
        if(thisData.containsCharacters(';') == false){continue;}
        SGEXTN::ApplicationBase::String codePoints = thisData.substringCharactersLeft(thisData.findFirstCharactersFromLeft(';'));
        SGEXTN::ApplicationBase::String propertyValue = thisData.substringCharactersRight(thisData.characterLength() - 1 - thisData.findFirstCharactersFromLeft(';')).removeLeadingTrailingWhitespace();
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

void setGraphemeBreakDatabaseValue(int j, const SGEXTN::ApplicationBase::String& propertyValue){
    graphemeBreakDatabase.at(j) = propertyValue;
}

void fillGraphemeBreakDatabase(){
    parseAuxillaryFile("graphemebreakproperty", &setGraphemeBreakDatabaseValue);
}

SGEXTN::ApplicationBase::GraphemeSegmentationType parseGraphemeSegmentationType(const SGEXTN::ApplicationBase::String& s){
    if(s == "Prepend"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::Prepend;}
    if(s == "CR"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::Return;}
    if(s == "LF"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::NewLine;}
    if(s == "Control"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::ControlCharacter;}
    if(s == "Extend"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::Extend;}
    if(s == "Regional_Indicator"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::RegionalIndicator;}
    if(s == "SpacingMark"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::SpacingCombiningMark;}
    if(s == "L"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeading;}
    if(s == "V"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulVowel;}
    if(s == "T"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulTrailing;}
    if(s == "LV"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeadingAndVowel;}
    if(s == "LVT"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing;}
    if(s == "ZWJ"){return SGEXTN::ApplicationBase::GraphemeSegmentationType::ZeroWidthJoiner;}
    return SGEXTN::ApplicationBase::GraphemeSegmentationType::Other;
}

SGEXTN::Containers::Array<SGEXTN::Containers::UnorderedSet<SGEXTN::ApplicationBase::String, SGEXTN::Containers::EqualTo<SGEXTN::ApplicationBase::String>, SGEXTN::Containers::Hash<SGEXTN::ApplicationBase::String>>> derivedCoreDatabase(0x110000);

void appendToDerivedCoreDatabase(int j, const SGEXTN::ApplicationBase::String& propertyValue){
    derivedCoreDatabase.at(j).insert(propertyValue);
}

void fillDerivedCoreDatabase(){
    parseAuxillaryFile("derivedcoreproperties", &appendToDerivedCoreDatabase);
}

SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> emojiTypeDatabase(0x110000);

void setEmojiTypeDatabaseValue(int j, const SGEXTN::ApplicationBase::String& propertyValue){
    emojiTypeDatabase.at(j) = propertyValue;
}

void fillEmojiTypeDatabase(){
    parseAuxillaryFile("emojidata", &setEmojiTypeDatabaseValue);
}

SGEXTN::ApplicationBase::String parseCodePointList(const SGEXTN::ApplicationBase::String& s){
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> splitStr = s.split(" ");
    SGEXTN::ApplicationBase::String output;
    for(int i=0; i<splitStr.length(); i++){
        output += SGEXTN::ApplicationBase::Character(splitStr.at(i).parseToInt(nullptr, 16));
    }
    return output;
}

SGEXTN::Containers::Array<bool> recomposeExclusionDatabase(0x110000, false);

void fillRecomposeExclusionDatabase(){
    SGEXTN::ApplicationBase::String dataString = readFile(":/SGEXTN_InternalTest/compositionexclusions.txt");
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> dataTable = dataString.split('\n');
    for(int i=0; i<dataTable.length(); i++){
        if(dataTable.at(i).containsCharacters('#') == false){continue;}
        SGEXTN::ApplicationBase::String codePoints = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft('#')).removeLeadingTrailingWhitespace();
        if(codePoints.containsCharacters("..") == false){recomposeExclusionDatabase.at(codePoints.parseToInt(nullptr, 16)) = true;}
        else{
            int start = codePoints.substringCharactersLeft(codePoints.findFirstCharactersFromLeft("..")).parseToInt(nullptr, 16);
            int end = codePoints.substringCharactersRight(codePoints.characterLength() - 1 - codePoints.findFirstCharactersFromLeft("..")).parseToInt(nullptr, 16);
            for(int j=start; j<=end; j++){
                recomposeExclusionDatabase.at(j) = true;
            }
        }
    }
}

SGEXTN::Containers::Array<SGEXTN::Containers::UnorderedSet<SGEXTN::ApplicationBase::String, SGEXTN::Containers::EqualTo<SGEXTN::ApplicationBase::String>, SGEXTN::Containers::Hash<SGEXTN::ApplicationBase::String>>> propertyListDatabase(0x110000);

void appendToPropertyListDatabase(int j, const SGEXTN::ApplicationBase::String& propertyValue){
    propertyListDatabase.at(j).insert(propertyValue);
}

void fillPropertyListDatabase(){
    parseAuxillaryFile("proplist", &appendToPropertyListDatabase);
}
}

void SGEXTN::InternalTest::StringTest::testAll(){
    SGEXTN::InternalTest::StringTest::testUnicodeQuery();
    SGEXTN::InternalTest::StringTest::testCharacter();
    SGEXTN::InternalTest::StringTest::testString();
}

void SGEXTN::InternalTest::StringTest::testUnicodeQuery(){
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
        if(uppercase != SGEXTN::ApplicationBase::UnicodeQuery::getUppercase(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery check uppercase fail");}
        int lowercase = i;
        if(unicodeDatabase.at(i).at(13) != ""){lowercase = unicodeDatabase.at(i).at(13).parseToInt(nullptr, 16);}
        if(lowercase != SGEXTN::ApplicationBase::UnicodeQuery::getLowercase(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery check lowercase fail");}
        int titlecase = i;
        if(unicodeDatabase.at(i).at(14) != ""){titlecase = unicodeDatabase.at(i).at(14).parseToInt(nullptr, 16);}
        if(titlecase != SGEXTN::ApplicationBase::UnicodeQuery::getTitlecase(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery check titlecase fail");}
        bool isWhitespace = false;
        if(propertyListDatabase.at(i).contains("White_Space") == true){isWhitespace = true;}
        if(isWhitespace != SGEXTN::ApplicationBase::UnicodeQuery::isWhitespace(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery check whitespace fail");}
        SGEXTN::ApplicationBase::FullCharacterType fullType = SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
        if(unicodeDatabase.at(i).at(2) != ""){fullType = parseFullType(unicodeDatabase.at(i).at(2));}
        if(fullType != SGEXTN::ApplicationBase::UnicodeQuery::getFullType(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get full type fail");}
        SGEXTN::ApplicationBase::SimplifiedCharacterType simplifiedType = SGEXTN::ApplicationBase::SimplifiedCharacterType::Other;
        if(unicodeDatabase.at(i).at(2) != ""){simplifiedType = parseSimplifiedType(unicodeDatabase.at(i).at(2));}
        if(simplifiedType != SGEXTN::ApplicationBase::UnicodeQuery::getSimplifiedType(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get simplified type fail");}
        int decimalDigit = -1;
        if(unicodeDatabase.at(i).at(6) != ""){decimalDigit = unicodeDatabase.at(i).at(6).parseToInt(nullptr, 16);}
        if(decimalDigit != SGEXTN::ApplicationBase::UnicodeQuery::getDecimalDigitValue(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get decimal digit value fail");}
        float numericalValue = SGEXTN::Math::FloatLimits<float>::negativeInfinity();
        if(unicodeDatabase.at(i).at(8) != ""){numericalValue = parseRationalNumber(unicodeDatabase.at(i).at(8));}
        if(numericalValue != SGEXTN::ApplicationBase::UnicodeQuery::getNumericalValue(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get numerical value fail");}
        SGEXTN::ApplicationBase::GraphemeSegmentationType graphemeSegmentationType = SGEXTN::ApplicationBase::GraphemeSegmentationType::Other;
        if(graphemeBreakDatabase.at(i) != ""){graphemeSegmentationType = parseGraphemeSegmentationType(graphemeBreakDatabase.at(i));}
        if(graphemeSegmentationType != SGEXTN::ApplicationBase::UnicodeQuery::getGraphemeSegmentationType(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get grapheme segmentation type fail");}
        SGEXTN::ApplicationBase::GraphemeRuleRelatedType graphemeRuleRelatedType = SGEXTN::ApplicationBase::GraphemeRuleRelatedType::None;
        if(derivedCoreDatabase.at(i).contains("InCB; Consonant") == true){graphemeRuleRelatedType = SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule9cConsonant;}
        else if(derivedCoreDatabase.at(i).contains("InCB; Extend") == true){graphemeRuleRelatedType = SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule9cExtend;}
        else if(derivedCoreDatabase.at(i).contains("InCB; Linker") == true){graphemeRuleRelatedType = SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule9cLinker;}
        else if(emojiTypeDatabase.at(i) == "Extended_Pictographic"){graphemeRuleRelatedType = SGEXTN::ApplicationBase::GraphemeRuleRelatedType::Rule11Emoji;}
        if(graphemeRuleRelatedType != SGEXTN::ApplicationBase::UnicodeQuery::getGraphemeRuleRelatedType(i)){SGEXTN::Containers::Crash::crash("SGEXTN::AppplicationBase::UnicodeQuery get grapheme rule related type fail");}
        int combiningMarkOrder = 0;
        if(unicodeDatabase.at(i).at(3) != ""){combiningMarkOrder = unicodeDatabase.at(i).at(3).parseToInt(nullptr, 10);}
        if(combiningMarkOrder != SGEXTN::ApplicationBase::UnicodeQuery::getCombiningMarkOrder(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get combining mark order fail");}
        if(i < 0xac00 || i > 0xd7a3){
            SGEXTN::ApplicationBase::String equivDecompose = "";
            if(unicodeDatabase.at(i).at(5) != "" && unicodeDatabase.at(i).at(5).containsCharacters('>') == false){equivDecompose = parseCodePointList(unicodeDatabase.at(i).at(5));}
            if(equivDecompose != SGEXTN::ApplicationBase::UnicodeQuery::getEquivDecomposition(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get equivalent decomposition fail");}
            SGEXTN::ApplicationBase::String compatDecompose = "";
            if(unicodeDatabase.at(i).at(5) != ""){
                if(unicodeDatabase.at(i).at(5).containsCharacters('>') == true){compatDecompose = parseCodePointList(unicodeDatabase.at(i).at(5).substringCharactersRight(unicodeDatabase.at(i).at(5).characterLength() - 1 - unicodeDatabase.at(i).at(5).findFirstCharactersFromLeft('>')).removeLeadingTrailingWhitespace());}
                else{compatDecompose = parseCodePointList(unicodeDatabase.at(i).at(5));}
            }
            if(compatDecompose != SGEXTN::ApplicationBase::UnicodeQuery::getCompatDecomposition(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get compatibility decomposition fail");}
            SGEXTN::Containers::Array<int> equivDecompCodePoints = equivDecompose.getUnicode();
            if(equivDecompCodePoints.length() == 2){
                int recomposedCodePoint = i;
                if(combiningMarkOrder != 0 || SGEXTN::ApplicationBase::UnicodeQuery::getCombiningMarkOrder(equivDecompCodePoints.at(0)) != 0){recomposedCodePoint = -1;}
                if(recomposeExclusionDatabase.at(i) == true){recomposedCodePoint = -1;}
                if(recomposedCodePoint != SGEXTN::ApplicationBase::UnicodeQuery::getBinaryRecomposition(equivDecompCodePoints.at(0), equivDecompCodePoints.at(1))){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery get unicode binary recomposition fail");}
            }
        }
    }
}

void SGEXTN::InternalTest::StringTest::testCharacter(){
    if(SGEXTN::ApplicationBase::Character() != SGEXTN::ApplicationBase::Character(0x2665)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character default value fail");}
    if(SGEXTN::ApplicationBase::Character('A') != SGEXTN::ApplicationBase::Character(65)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor from char fail");}
    if(SGEXTN::ApplicationBase::Character(reinterpret_cast<const char*>(u8"\u2665")) != SGEXTN::ApplicationBase::Character()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor from C string fail");}
    SGEXTN::ApplicationBase::Character a('a');
    SGEXTN::ApplicationBase::Character b('b');
    if(a == b){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character equality check fail");}
    if(a != SGEXTN::ApplicationBase::Character(0x61)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character inequality check fail");}
    if(b < a){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character less than operator fail");}
    if(a > b){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character more than operator fail");}
    if(b <= a){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character less than or equal to operator fail");}
    if(a >= b){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character more than or equal to operator fail");}
    SGEXTN::ApplicationBase::Character c;
    if(c.byteLength() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character check byte length fail");}
    if(c.byteAt(2) != 0xa5){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get byte at fail");}
    c.byteAt(2) = 0xa6;
    if(c != SGEXTN::ApplicationBase::Character(0x2666)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character set byte at fail");}
    if(a.baseToChar() != 'a'){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character convert to C++ char fail");}
    if(SGEXTN::ApplicationBase::Character('0').isDigit() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 10 fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isDigit() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 10 fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 10 fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 10 fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 10 fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 10 fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 10 fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character('0').isDigit(2) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 2 fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 2 fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 2 fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 2 fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 2 fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 2 fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isDigit(2) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 2 fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character('0').isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 16 fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 16 fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 16 fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 16 fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isDigit(16) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 16 fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isDigit(16) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 16 fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isDigit(16) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 16 fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character('0').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 36 fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 36 fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 36 fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 36 fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 36 fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isDigit(36) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 36 fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isDigit(36) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is digit base 36 fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character('0').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English lowercase fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English lowercase fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isEnglishLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English lowercase fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English lowercase fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isEnglishLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English lowercase fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English lowercase fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English lowercase fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character('0').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English uppercase fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English uppercase fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English uppercase fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isEnglishUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English uppercase fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English uppercase fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isEnglishUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English uppercase fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English uppercase fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character('0').isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English letter fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English letter fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English letter fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English letter fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English letter fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English letter fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English letter fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character('0').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English alphanumeric fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English alphanumeric fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English alphanumeric fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English alphanumeric fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English alphanumeric fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English alphanumeric fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isEnglishAlphanumeric() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is English alphanumeric fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character('0').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is ASCII fail for digit 0");}
    if(SGEXTN::ApplicationBase::Character('5').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is ASCII fail for digit 5");}
    if(SGEXTN::ApplicationBase::Character('a').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is ASCII fail for small letter a");}
    if(SGEXTN::ApplicationBase::Character('A').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is ASCII fail for capital letter A");}
    if(SGEXTN::ApplicationBase::Character('x').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is ASCII fail for small letter x");}
    if(SGEXTN::ApplicationBase::Character('X').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is ASCII fail for capital letter X");}
    if(SGEXTN::ApplicationBase::Character('/').isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is ASCII fail for punctuation mark");}
    if(SGEXTN::ApplicationBase::Character().isASCII() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is ASCII fail for heart");}
    if(SGEXTN::ApplicationBase::Character().isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is whitespace fail for heart");}
    if(SGEXTN::ApplicationBase::Character("A").isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is whitespace fail for English letter");}
    if(SGEXTN::ApplicationBase::Character(" ").isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is whitespace fail for space");}
    if(SGEXTN::ApplicationBase::Character("\t").isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is whitespace fail for tab");}
    if(SGEXTN::ApplicationBase::Character("\n").isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is whitespace fail for newline");}
    if(SGEXTN::ApplicationBase::Character(0x2003).isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is whitespace fail for unicode space");}
    SGEXTN::ApplicationBase::Character cWithTail(reinterpret_cast<const char*>(u8"\u0063\u0327"));
    if(cWithTail.getBaseUnicode() != 0x63){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get base unicode fail");}
    SGEXTN::Containers::Array<int> codePoints = cWithTail.getUnicode();
    if(codePoints.length() != 2 || codePoints.at(0) != 0x63 || codePoints.at(1) != 0x327){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get unicode fail");}
    if(SGEXTN::ApplicationBase::Character('a').isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is uppercase English lowercase fail");}
    if(SGEXTN::ApplicationBase::Character('A').isUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is uppercase English uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x03b1).isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is uppercase Greek lowercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x0391).isUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is uppercase Greek uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x4e00).isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is uppercase Chinese letter fail");}
    if(SGEXTN::ApplicationBase::Character(0x01c5).isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is uppercase Dz fail");}
    if(SGEXTN::ApplicationBase::Character('a').isLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is lowercase English lowercase fail");}
    if(SGEXTN::ApplicationBase::Character('A').isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is lowercase English uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x03b1).isLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is lowercase Greek lowercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x0391).isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is lowercase Greek uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x4e00).isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is lowercase Chinese letter fail");}
    if(SGEXTN::ApplicationBase::Character(0x01c5).isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is lowercase Dz fail");}
    if(SGEXTN::ApplicationBase::Character('a').isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is titlecase English lowercase fail");}
    if(SGEXTN::ApplicationBase::Character('A').isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is titlecase English uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x03b1).isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is titlecase Greek lowercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x0391).isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is titlecase Greek uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x4e00).isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is titlecase Chinese letter fail");}
    if(SGEXTN::ApplicationBase::Character(0x01c5).isTitlecase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character is titlecase Dz fail");}
    if(SGEXTN::ApplicationBase::Character('a').getUppercase() != SGEXTN::ApplicationBase::Character('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get uppercase English lowercase fail");}
    if(SGEXTN::ApplicationBase::Character('A').getUppercase() != SGEXTN::ApplicationBase::Character('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get uppercase English uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x03b1).getUppercase() != SGEXTN::ApplicationBase::Character(0x0391)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get uppercase Greek lowercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x0391).getUppercase() != SGEXTN::ApplicationBase::Character(0x0391)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get uppercase Greek uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x4e00).getUppercase() != SGEXTN::ApplicationBase::Character(0x4e00)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get uppercase Chinese letter fail");}
    if(SGEXTN::ApplicationBase::Character(0x01c5).getUppercase() != SGEXTN::ApplicationBase::Character(0x01c4)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get uppercase Dz fail");}
    if(SGEXTN::ApplicationBase::Character('a').getLowercase() != SGEXTN::ApplicationBase::Character('a')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get lowercase English lowercase fail");}
    if(SGEXTN::ApplicationBase::Character('A').getLowercase() != SGEXTN::ApplicationBase::Character('a')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get lowercase English uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x03b1).getLowercase() != SGEXTN::ApplicationBase::Character(0x03b1)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get lowercase Greek lowercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x0391).getLowercase() != SGEXTN::ApplicationBase::Character(0x03b1)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get lowercase Greek uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x4e00).getLowercase() != SGEXTN::ApplicationBase::Character(0x4e00)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get lowercase Chinese letter fail");}
    if(SGEXTN::ApplicationBase::Character(0x01c5).getLowercase() != SGEXTN::ApplicationBase::Character(0x01c6)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get lowercase Dz fail");}
    if(SGEXTN::ApplicationBase::Character('a').getTitlecase() != SGEXTN::ApplicationBase::Character('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get titlecase English lowercase fail");}
    if(SGEXTN::ApplicationBase::Character('A').getTitlecase() != SGEXTN::ApplicationBase::Character('A')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get titlecase English uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x03b1).getTitlecase() != SGEXTN::ApplicationBase::Character(0x0391)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get titlecase Greek lowercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x0391).getTitlecase() != SGEXTN::ApplicationBase::Character(0x0391)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get titlecase Greek uppercase fail");}
    if(SGEXTN::ApplicationBase::Character(0x4e00).getTitlecase() != SGEXTN::ApplicationBase::Character(0x4e00)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get titlecase Chinese letter fail");}
    if(SGEXTN::ApplicationBase::Character(0x01c5).getTitlecase() != SGEXTN::ApplicationBase::Character(0x01c5)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get titlecase Dz fail");}
    if(SGEXTN::ApplicationBase::Character('0').getDecimalDigitValue() != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get decimal digit value digit zero fail");}
    if(SGEXTN::ApplicationBase::Character(0x0be6).getDecimalDigitValue() != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get decimal digit value Tamil digit zero fail");}
    if(SGEXTN::ApplicationBase::Character(' ').getDecimalDigitValue() != -1){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get decimal digit value space fail");}
    if(SGEXTN::ApplicationBase::Character(0xbd).getDecimalDigitValue() != -1){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get decimal digit value half fraction fail");}
    if(SGEXTN::ApplicationBase::Character('0').getNumericalValue() != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get numerical value digit zero fail");}
    if(SGEXTN::ApplicationBase::Character(0x0be6).getNumericalValue() != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get numerical value Tamil digit zero fail");}
    if(SGEXTN::ApplicationBase::Character(' ').getNumericalValue() != SGEXTN::Math::FloatLimits<float>::negativeInfinity()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get numerical value space fail");}
    if(SGEXTN::ApplicationBase::Character(0xbd).getNumericalValue() != 0.5f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character get numerical value half fraction fail");}
}

#define U8(str) reinterpret_cast<const char*>(u8##str)
void SGEXTN::InternalTest::StringTest::testString(){
    SGEXTN::ApplicationBase::String a('a');
    SGEXTN::ApplicationBase::String b("b");
    if(b != SGEXTN::ApplicationBase::String('b')){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String constructor from C++ char fail");}
    if(a != SGEXTN::ApplicationBase::String("a")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String constructor from C string fail");}
    if(a != SGEXTN::ApplicationBase::String(SGEXTN::ApplicationBase::Character('a'))){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String constructor from SGEXTN character fail");}
    if(a == b){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String equality check fail");}
    if((a != b) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String inequality check fail");}
    if(b < a){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String less than operator fail");}
    if(a > b){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String more than operator fail");}
    if(b <= a){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String less than or equal to operator fail");}
    if(a >= b){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String more than or equal to operator fail");}
    if(a + b != "ab"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String string addition fail");}
    a += b;
    if(a != "ab"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String string addition assignment fail");}
    SGEXTN::ApplicationBase::String aAlphaSpaceEpsilonA = U8("\u0061\u03b1\u0301\u0020\u03c3\u0041");
    if(aAlphaSpaceEpsilonA.byteLength() != 9){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check  byte length fail");}
    if(aAlphaSpaceEpsilonA.characterLength() != 5){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check character length fail");}
    if(aAlphaSpaceEpsilonA.byteAt(8) != 'A'){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String get byte at fail");}
    aAlphaSpaceEpsilonA.byteAt(8) = 'B';
    if(aAlphaSpaceEpsilonA.byteAt(8) != 'B'){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String set byte at fail");}
    if(aAlphaSpaceEpsilonA.getCharacterAt(1) != U8("\u03b1\u0301")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String get character at fail");}
    aAlphaSpaceEpsilonA.setCharacterAt(1, U8("\u03b1\u0300"));
    if(aAlphaSpaceEpsilonA.getCharacterAt(1) != U8("\u03b1\u0300")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String set character same length fail");}
    aAlphaSpaceEpsilonA.setCharacterAt(4, U8("\uff21"));
    if(aAlphaSpaceEpsilonA.getCharacterAt(4) != SGEXTN::ApplicationBase::Character(0xff21)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String set character different length fail");}
    if(aAlphaSpaceEpsilonA.fillBytes('0') != "00000000000"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill bytes fail");}
    if(aAlphaSpaceEpsilonA.fillCharacters(U8("\u03b1\u0301")) != U8("\u03b1\u0301\u03b1\u0301\u03b1\u0301\u03b1\u0301\u03b1\u0301")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill characters fail");}
    SGEXTN::ApplicationBase::String bytesFindString = "__ab_aab_abb";
    if(bytesFindString.findFirstBytesFromLeft("ab") != 2){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String find bytes from left fail");}
    if(bytesFindString.findFirstBytesFromRight("ab") != 9){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String find bytes from right fail");}
    if(bytesFindString.findFirstBytesFromLeftBounded(3, "ab") != 6){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String find bytes from left bounded fail");}
    if(bytesFindString.findFirstBytesFromRightBounded(8, "ab") != 6){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String find bytes from right bounded fail");}
    SGEXTN::ApplicationBase::String charactersFindString = U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2");
    if(charactersFindString.findFirstCharactersFromLeft(U8("\u03b1\u0300\u03b2")) != 2){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String find characters from left fail");}
    if(charactersFindString.findFirstCharactersFromRight(U8("\u03b1\u0300\u03b2")) != 9){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String find characters from right fail");}
    if(charactersFindString.findFirstCharactersFromLeftBounded(3, U8("\u03b1\u0300\u03b2")) != 6){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String find characters from left bounded fail");}
    if(charactersFindString.findFirstCharactersFromRightBounded(8, U8("\u03b1\u0300\u03b2")) != 6){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String find characters from right bounded fail");}
    if(bytesFindString.substringBytes(5, 3) != "aab"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String substring bytes fail");}
    if(bytesFindString.substringBytesLeft(3) != "__a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String substring bytes left fail");}
    if(bytesFindString.substringBytesRight(3) != "abb"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String substring bytes right fail");}
    if(charactersFindString.substringCharacters(5, 3) != U8("\u03b1\u0300\u03b1\u0300\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String substring characters fail");}
    if(charactersFindString.substringCharactersLeft(3) != U8("\u0020\u0020\u03b1\u0300")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String substring characters left fail");}
    if(charactersFindString.substringCharactersRight(3) != U8("\u03b1\u0300\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String substring characters right fail");}
    if(bytesFindString.replaceBytes("ab", 'c') != "__c_ac_cb"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String replace bytes fail");}
    if(charactersFindString.replaceCharacters(U8("\u03b1\u0300\u03b2"), U8("\u03b3")) != U8("\u0020\u0020\u03b3\u0020\u03b1\u0300\u03b3\u0020\u03b3\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String replace characters fail");}
    if(bytesFindString.removeBytes("ab") != "___a_b"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String remove bytes fail");}
    if(charactersFindString.removeCharacters(U8("\u03b1\u0300\u03b2")) != U8("\u0020\u0020\u0020\u03b1\u0300\u0020\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String remove characters fail");}
    if(bytesFindString.insertAtByteIndex(0, "cc") != "cc__ab_aab_abb"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String insert bytes at start fail");}
    if(bytesFindString.insertAtByteIndex(2, "cc") != "__ccab_aab_abb"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String insert bytes at middle fail");}
    if(bytesFindString.insertAtByteIndex(12, "cc") != "__ab_aab_abbcc"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String insert bytes at end fail");}
    if(charactersFindString.insertAtCharacterIndex(0, U8("\u03b3\u03b3")) != U8("\u03b3\u03b3\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String insert characters at start fail");}
    if(charactersFindString.insertAtCharacterIndex(2, U8("\u03b3\u03b3")) != U8("\u0020\u0020\u03b3\u03b3\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String insert characters at middle fail");}
    if(charactersFindString.insertAtCharacterIndex(12, U8("\u03b3\u03b3")) != U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b1\u0300\u03b2\u0020\u03b1\u0300\u03b2\u03b2\u03b3\u03b3")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String insert characters at end fail");}
    if(bytesFindString.removeAtByteIndex(5, 3) != "__ab__abb"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String remove bytes fail");}
    if(charactersFindString.removeAtCharacterIndex(5, 3) != U8("\u0020\u0020\u03b1\u0300\u03b2\u0020\u0020\u03b1\u0300\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String remove characters fail");}
    if(bytesFindString.containsBytes("ab") == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check if contains existing bytes fail");}
    if(bytesFindString.containsBytes("bc") == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check if contains nonexistent bytes fail");}
    if(charactersFindString.containsCharacters(U8("\u03b1\u0300\u03b2")) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check if contains existing characters fail");}
    if(charactersFindString.containsCharacters(U8("\u0300\u03b2")) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check if contains nonexistent characters fail");}
    if(bytesFindString.startsWithBytes("__") == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check start bytes with matched prefix fail");}
    if(bytesFindString.startsWithBytes("_a") == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check start bytes with unmatched prefix fail");}
    if(charactersFindString.startsWithCharacters(U8("\u0020\u0020")) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check start characters with matched prefix fail");}
    if(charactersFindString.startsWithCharacters(U8("\u0020\u03b1\u0300")) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check start characters with unmatched prefix fail");}
    if(bytesFindString.endsWithBytes("bb") == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check end bytes with matched prefix fail");}
    if(bytesFindString.endsWithBytes("ab") == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check end bytes with unmatched prefix fail");}
    if(charactersFindString.endsWithCharacters(U8("\u03b2\u03b2")) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check end characters with matched prefix fail");}
    if(charactersFindString.endsWithCharacters(U8("\u03b1\u0300\u03b2")) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check end characters with unmatched prefix fail");}
    bytesFindString = SGEXTN::ApplicationBase::String::repeat("a", 7);
    charactersFindString = SGEXTN::ApplicationBase::String::repeat(U8("\u03b1\u0300"), 7);
    if(charactersFindString != U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String repeat given string fail");}
    if(bytesFindString.countBytes("aaa") != 2){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String count bytes no overlap fail");}
    if(charactersFindString.countCharacters(U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300")) != 2){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String count characters no overlap fail");}
    if(bytesFindString.countBytesAllowOverlap("aaa") != 5){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String count bytes allow overlap fail");}
    if(charactersFindString.countCharactersAllowOverlap(U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300")) != 5){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String count characters allow overlap fail");}
    if(bytesFindString.fillLeftToByteLength(5, 'b') != bytesFindString){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill left bytes sufficient length fail");}
    if(bytesFindString.fillLeftToByteLength(10, 'b') != "bbbaaaaaaa"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill left bytes insufficient length fail");}
    if(charactersFindString.fillLeftToCharacterLength(5, U8("\u03b2")) != charactersFindString){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill left characters sufficient length fail");}
    if(charactersFindString.fillLeftToCharacterLength(10, U8("\u03b2")) != U8("\u03b2\u03b2\u03b2\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill left characters insufficient length fail");}
    if(bytesFindString.fillRightToByteLength(5, 'b') != bytesFindString){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill right bytes sufficient length fail");}
    if(bytesFindString.fillRightToByteLength(10, 'b') != "aaaaaaabbb"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill right bytes insufficient length fail");}
    if(charactersFindString.fillRightToCharacterLength(5, U8("\u03b2")) != charactersFindString){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill right characters sufficient length fail");}
    if(charactersFindString.fillRightToCharacterLength(10, U8("\u03b2")) != U8("\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b1\u0300\u03b2\u03b2\u03b2")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String fill right characters insufficient length fail");}
    if(charactersFindString.byteIndexToCharacterIndex(1) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String convert byte index to character index fail");}
    if(charactersFindString.characterIndexToByteIndex(1) != 4){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String convert character index to byte index fail");}
    SGEXTN::ApplicationBase::String positiveBase10Number = "26";
    SGEXTN::ApplicationBase::String negativeBase10Number = "-26";
    SGEXTN::ApplicationBase::String positiveBase16Number = "1a";
    SGEXTN::ApplicationBase::String negativeBase16Number = "-1A";
    SGEXTN::ApplicationBase::String positiveNonLatinNumber = U8("\u0be8\u0bec");
    SGEXTN::ApplicationBase::String negativeNonLatinNumber = U8("\u002d\u0be8\u0bec");
    SGEXTN::ApplicationBase::String invalidNumber = "2 6";
    bool isValid = false;
    if(positiveBase10Number.parseToShort(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 10 number to short fail");}
    isValid = false;
    if(negativeBase10Number.parseToShort(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 10 number to short fail");}
    isValid = false;
    if(positiveBase16Number.parseToShort(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 16 number to short fail");}
    isValid = false;
    if(negativeBase16Number.parseToShort(&isValid, 16) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 16 number to short fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToShort(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive non Latin number to short fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToShort(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative non Latin number to short fail");}
    isValid = true;
    if(invalidNumber.parseToShort(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to short fail");}
    if(invalidNumber.parseToShort(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to short no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedShort(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 10 number to unsigned short fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedShort(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 16 number to unsigned short fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedShort(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive non Latin number to unsigned short fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedShort(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to unsigned short fail");}
    if(invalidNumber.parseToUnsignedShort(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to unsigned short no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToInt(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 10 number to int fail");}
    isValid = false;
    if(negativeBase10Number.parseToInt(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 10 number to int fail");}
    isValid = false;
    if(positiveBase16Number.parseToInt(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 16 number to int fail");}
    isValid = false;
    if(negativeBase16Number.parseToInt(&isValid, 16) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 16 number to int fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToInt(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive non Latin number to int fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToInt(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative non Latin number to int fail");}
    isValid = true;
    if(invalidNumber.parseToInt(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to int fail");}
    if(invalidNumber.parseToInt(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to int no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedInt(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 10 number to unsigned int fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedInt(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 16 number to unsigned int fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedInt(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive non Latin number to unsigned int fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedInt(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to unsigned int fail");}
    if(invalidNumber.parseToUnsignedInt(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to unsigned int no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 10 number to long long fail");}
    isValid = false;
    if(negativeBase10Number.parseToLongLong(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 10 number to long long fail");}
    isValid = false;
    if(positiveBase16Number.parseToLongLong(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 16 number to long long fail");}
    isValid = false;
    if(negativeBase16Number.parseToLongLong(&isValid, 16) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 16 number to long long fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive non Latin number to long long fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToLongLong(&isValid, 10) != -26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative non Latin number to long long fail");}
    isValid = true;
    if(invalidNumber.parseToLongLong(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to long long fail");}
    if(invalidNumber.parseToLongLong(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to long long no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToUnsignedLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 10 number to unsigned long long fail");}
    isValid = false;
    if(positiveBase16Number.parseToUnsignedLongLong(&isValid, 16) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 16 number to unsigned long long fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToUnsignedLongLong(&isValid, 10) != 26 || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive non Latin number to unsigned long long fail");}
    isValid = true;
    if(invalidNumber.parseToUnsignedLongLong(&isValid, 10) != 0 || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to unsigned long long fail");}
    if(invalidNumber.parseToUnsignedLongLong(nullptr, 10) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to unsigned long long no success flag fail");}
    positiveBase10Number = "10.5";
    negativeBase10Number = "-010.500";
    SGEXTN::ApplicationBase::String positiveScientificNotation = "5e-1";
    SGEXTN::ApplicationBase::String negativeScientificNotation = "-5.0e-01";
    positiveBase16Number = "a.8";
    negativeBase16Number = "-0a.80";
    positiveNonLatinNumber = U8("\u0be6\u002e\u0beb");
    negativeNonLatinNumber = U8("\u002d\u0be6\u0be6\u002e\u0beb\u0be6");
    invalidNumber = "-+0.5";
    isValid = false;
    if(positiveBase10Number.parseToFloat(&isValid, 10) != 10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 10 number to float fail");}
    isValid = false;
    if(negativeBase10Number.parseToFloat(&isValid, 10) != -10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 10 number to float fail");}
    isValid = false;
    if(positiveScientificNotation.parseToFloat(&isValid, 10) != 0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive scientific notation number to float fail");}
    isValid = false;
    if(negativeScientificNotation.parseToFloat(&isValid, 10) != -0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative scientific notation number to float fail");}
    isValid = false;
    if(positiveBase16Number.parseToFloat(&isValid, 16) != 10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 16 number to float fail");}
    isValid = false;
    if(negativeBase16Number.parseToFloat(&isValid, 16) != -10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 16 number to float fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToFloat(&isValid, 10) != 0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive non Latin number to float fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToFloat(&isValid, 10) != -0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative non Latin number to float fail");}
    isValid = true;
    if(invalidNumber.parseToFloat(&isValid, 10) != 0.0f || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to float fail");}
    if(invalidNumber.parseToFloat(nullptr, 10) != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to float no success flag fail");}
    isValid = false;
    if(positiveBase10Number.parseToDouble(&isValid, 10) != 10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 10 number to double fail");}
    isValid = false;
    if(negativeBase10Number.parseToDouble(&isValid, 10) != -10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 10 number to double fail");}
    isValid = false;
    if(positiveScientificNotation.parseToDouble(&isValid, 10) != 0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive scientific notation number to double fail");}
    isValid = false;
    if(negativeScientificNotation.parseToDouble(&isValid, 10) != -0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative scientific notation number to double fail");}
    isValid = false;
    if(positiveBase16Number.parseToDouble(&isValid, 16) != 10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive base 16 number to double fail");}
    isValid = false;
    if(negativeBase16Number.parseToDouble(&isValid, 16) != -10.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative base 16 number to double fail");}
    isValid = false;
    if(positiveNonLatinNumber.parseToDouble(&isValid, 10) != 0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse positive non Latin number to double fail");}
    isValid = false;
    if(negativeNonLatinNumber.parseToDouble(&isValid, 10) != -0.5f || isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse negative non Latin number to double fail");}
    isValid = true;
    if(invalidNumber.parseToDouble(&isValid, 10) != 0.0f || isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to double fail");}
    if(invalidNumber.parseToDouble(nullptr, 10) != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String parse invalid number to double no success flag fail");}
    if(SGEXTN::ApplicationBase::String::stringFromShort(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print short positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromShort(-26, 10) != "-26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print short negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromShort(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print short positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromShort(-26, 16) != "-1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print short negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromUnsignedShort(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print unsigned short positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromUnsignedShort(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print unsigned short positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromInt(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print int positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromInt(-26, 10) != "-26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print int negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromInt(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print int positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromInt(-26, 16) != "-1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print int negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromUnsignedInt(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print unsigned int positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromUnsignedInt(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print unsigned int positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromLongLong(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print long long positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromLongLong(-26, 10) != "-26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print long long negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromLongLong(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print long long positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromLongLong(-26, 16) != "-1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print long long negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromUnsignedLongLong(26, 10) != "26"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print unsigned long long positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromUnsignedLongLong(26, 16) != "1a"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print unsigned long long positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace, 3) != "10.333"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float decimal place mode positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(-31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace, 3) != "-10.333"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float decimal place mode negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace, 3) != "a.555"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float decimal place mode positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(-31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace, 3) != "-a.555"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float decimal place mode negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 3) != "10.3"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float significant figures mode positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(-31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 3) != "-10.3"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float significant figures mode negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 3) != "a.55"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float significant figures mode positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(-31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 3) != "-a.55"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float significant figures mode negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation, 3) != "1.03e+01"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float scientific notation mode positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(-1.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation, 3) != "-3.33e-01"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float scientific notation mode negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation, 3) != "a.55e+00"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float scientific notation mode positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromFloat(-1.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation, 3) != "-5.55e-01"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print float scientific notation mode negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace, 3) != "10.333"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double decimal place mode positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(-31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace, 3) != "-10.333"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double decimal place mode negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace, 3) != "a.555"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double decimal place mode positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(-31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::DecimalPlace, 3) != "-a.555"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double decimal place mode negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 3) != "10.3"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double significant figures mode positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(-31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 3) != "-10.3"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double significant figures mode negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 3) != "a.55"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double significant figures mode positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(-31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 3) != "-a.55"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double significant figures mode negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(31.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation, 3) != "1.03e+01"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double scientific notation mode positive base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(-1.0f / 3.0f, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation, 3) != "-3.33e-01"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double scientific notation mode negative base 10 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(31.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation, 3) != "a.55e+00"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double scientific notation mode positive base 16 fail");}
    if(SGEXTN::ApplicationBase::String::stringFromDouble(-1.0f / 3.0f, 16, SGEXTN::ApplicationBase::FloatPrecisionFormat::ScientificNotation, 3) != "-5.55e-01"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String print double scientific notation mode negative base 16 fail");}
    if(SGEXTN::ApplicationBase::String("-1.23e+09").prettierScientificNotation() != U8("-1.23\u00d710\u2079")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String make scientific notation prettier fail");}
    if(SGEXTN::ApplicationBase::String("12345").convertNumericSystem(0xbe6) != U8("\u0be7\u0be8\u0be9\u0bea\u0beb")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String convert to non Latin numbers fail");}
    if(SGEXTN::ApplicationBase::String("<b> & </b>#").prepareInnerHtmlText() != "&lt;b&gt; &amp; &lt;/b&gt;#"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String HTML escaping fail");}
    if(SGEXTN::ApplicationBase::String("  te xt \t\n  \n \t ").removeLeadingTrailingWhitespace() != "te xt"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String whitespace trimming fail");}
    if(SGEXTN::ApplicationBase::String(" a b \nc\t\t\td    e \n \tfgh   ").cleanWhitespace() != "a b c d e fgh"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String whitespace cleaning fail");}
    if(SGEXTN::ApplicationBase::String(" a b \nc\t\t\td    e \n \tfgh   ").removeAllWhitespace() != "abcdefgh"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String whitespace removal fail");}
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> testSplitString = SGEXTN::ApplicationBase::String(",a, bc, \n\td,,, ,e").split(',');
    if(testSplitString.length() != 8 || testSplitString.at(0) != "" || testSplitString.at(1) != "a" || testSplitString.at(2) != " bc" || testSplitString.at(3) != " \n\td" || testSplitString.at(4) != "" || testSplitString.at(5) != "" || testSplitString.at(6) != " " || testSplitString.at(7) != "e"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String split string fail");}
    if(SGEXTN::ApplicationBase::String("0123456789").isDigit() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check digit base 10 true fail");}
    if(SGEXTN::ApplicationBase::String("0123456789a").isDigit() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check digit base 10 false fail");}
    if(SGEXTN::ApplicationBase::String("0123456789abcdefABCDEF").isDigit(16) == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check digit base 16 true fail");}
    if(SGEXTN::ApplicationBase::String("0123456789abcdefg").isDigit(16) == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check digit base 16 false fail");}
    if(SGEXTN::ApplicationBase::String("qwerty").isEnglishLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check English lowercase true fail");}
    if(SGEXTN::ApplicationBase::String("qwertY").isEnglishLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check English lowercase false fail");}
    if(SGEXTN::ApplicationBase::String("QWERTY").isEnglishUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check English uppercase true fail");}
    if(SGEXTN::ApplicationBase::String("QWERTy").isEnglishUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check English uppercase false fail");}
    if(SGEXTN::ApplicationBase::String("QWERTYqwerty").isEnglishLetter() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check English letter true fail");}
    if(SGEXTN::ApplicationBase::String("QWERTYqwerty0").isEnglishLetter() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check English letter false fail");}
    if(SGEXTN::ApplicationBase::String("QWERTYqwerty0123456789").isEnglishAlphanumeric() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check English alphanumeric true fail");}
    if(SGEXTN::ApplicationBase::String("QWERTYqwerty0123456789 ").isEnglishAlphanumeric() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check English alphanumeric false fail");}
    if(SGEXTN::ApplicationBase::String("QWERTYqwerty0123456789,.<> ").isASCII() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check ASCII true fail");}
    if((SGEXTN::ApplicationBase::String("QWERTYqwerty0123456789,.<> ") + SGEXTN::ApplicationBase::Character(0xbe6)).isASCII() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check ASCII false fail");}
    if(SGEXTN::ApplicationBase::String(" \t\n").isWhitespace() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check whitespace true fail");}
    if(SGEXTN::ApplicationBase::String(" \t\n0").isWhitespace() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check whitespace false fail");}
    if(SGEXTN::ApplicationBase::String(U8("A \u0391\u0300_.")).isUppercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check uppercase true fail");}
    if(SGEXTN::ApplicationBase::String(U8("A \u0391\u0300_.a")).isUppercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check uppercase false fail");}
    if(SGEXTN::ApplicationBase::String(U8("a \u03b1\u0300_.")).isLowercase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check lowercase true fail");}
    if(SGEXTN::ApplicationBase::String(U8("a \u03b1\u0300_.A")).isLowercase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check lowercase false fail");}
    if(SGEXTN::ApplicationBase::String(U8("A \u0391\u0300_.\u01c5")).isTitlecase() == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check titlecase true fail");}
    if(SGEXTN::ApplicationBase::String(U8("A \u0391\u0300_.\u01c4")).isTitlecase() == true){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String check titlecase false fail");}
    SGEXTN::ApplicationBase::String changeCaseTestString = U8(" ./aA\u0391\u03b1\u0300\u01c4\u01c5\u01c6\u4000");
    if(changeCaseTestString.getUppercase() != U8(" ./AA\u0391\u0391\u0300\u01c4\u01c4\u01c4\u4000")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String convert to uppercase fail");}
    if(changeCaseTestString.getLowercase() != U8(" ./aa\u03b1\u03b1\u0300\u01c6\u01c6\u01c6\u4000")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String convert to uppercase fail");}
    if(changeCaseTestString.getTitlecase() != U8(" ./AA\u0391\u0391\u0300\u01c5\u01c5\u01c5\u4000")){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String convert to uppercase fail");}
    SGEXTN::Containers::Array<int> unicodeCodePoints = changeCaseTestString.getUnicode();
    SGEXTN::Containers::Array<int> expectedCodePoints = SGEXTN::Containers::Array<int>(0x20, 0x2e, 0x2f, 0x61, 0x41, 0x391, 0x3b1, 0x300, 0x1c4, 0x1c5, 0x1c6, 0x4000);
    if(unicodeCodePoints.length() != expectedCodePoints.length()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String extract Unicode code points fail");}
    for(int i=0; i<unicodeCodePoints.length(); i++){
        if(unicodeCodePoints.at(i) != expectedCodePoints.at(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String extract Unicode code points fail");}
    }
    SGEXTN::ApplicationBase::String unsimplifiedString = U8("Caf\u00e8 at Yishun \uff2d\uff32\uff34 \u2122 \n\t \U0001d4a9\U0001d4ae\u2081\u2081");
    if(unsimplifiedString.getSimplestEquivalent(false) != "Cafe at Yishun MRT TM NS11"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String case sensitive simplest string conversion fail");}
    if(unsimplifiedString.getSimplestEquivalent(true) != "cafe at yishun mrt tm ns11"){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::String case insensitive simplest string conversion fail");}
}
#undef U8

void SGEXTN::InternalTest::StringTest::runExternalTests(){
    // grapheme boundary unit tests
    // normalisation unit tests
    // external floating point and integer parsing tests
}