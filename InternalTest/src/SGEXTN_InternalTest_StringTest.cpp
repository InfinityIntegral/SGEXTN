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
}

void SGEXTN::InternalTest::StringTest::testAll(){
    SGEXTN::InternalTest::StringTest::testUnicodeQuery();
    SGEXTN::InternalTest::StringTest::testCharacter();
    SGEXTN::InternalTest::StringTest::testString();
}

void SGEXTN::InternalTest::StringTest::testUnicodeQuery(){
    fillUnicodeDatabase();
    fillGraphemeBreakDatabase();
    fillDerivedCoreDatabase();
    fillEmojiTypeDatabase();
    fillRecomposeExclusionDatabase();
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
            if(unicodeDatabase.at(i).at(5) != "" && unicodeDatabase.at(i).at(5).containsCharacters('>') == true){compatDecompose = parseCodePointList(unicodeDatabase.at(i).at(5).substringCharactersRight(unicodeDatabase.at(i).at(5).characterLength() - 1 - unicodeDatabase.at(i).at(5).findFirstCharactersFromLeft('>')).removeLeadingTrailingWhitespace());}
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

}

void SGEXTN::InternalTest::StringTest::testString(){
    // grapheme boundary unit tests
    // normalisation unit tests
}