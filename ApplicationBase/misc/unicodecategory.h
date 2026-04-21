#include <QString>
#include <QFile>
#include <QVector>
#include <QMap>
#include <QDebug>
#include <SGEXTN_ApplicationBase_Character.h>
#include <SGEXTN_ApplicationBase_Debug.h>

QMap<int, QVector<QString>> allOfUnicode;
QVector<QString> categoryStorage;

void parseFile(){
    QString dataString = "";
    QFile file("../ApplicationBase/misc/unicode.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        dataString = file.readAll();
        file.close();
    }
    QVector<QString> characters = dataString.split('\n');
    for(int i=0; i<characters.length(); i++){
        QVector<QString> charData = characters.at(i).split(';');
        int codePoint = charData.at(0).toInt(nullptr, 16);
        charData.pop_front();
        allOfUnicode.insert(codePoint, charData);
    }
}

QString sgextnCategoryToOfficialCategory(SGEXTN::ApplicationBase::FullCharacterType c){
    if(c == SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark){return "Mn";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::CombiningMark){return "Mc";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::EnclosingMark){return "Me";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit){return "Nd";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::LetterNumber){return "Nl";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::OtherNumber){return "No";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak){return "Zs";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::LineBreak){return "Zl";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::ParagraphBreak){return "Zp";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::ControlCharacter){return "Cc";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter){return "Cf";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::SurrogateCharacter){return "Cs";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::PrivateUseCharacter){return "Co";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter){return "Cn";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter){return "Lu";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter){return "Ll";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter){return "Lt";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter){return "Lm";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::OtherLetter){return "Lo";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::ConnectorPunctuation){return "Pc";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation){return "Pd";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation){return "Ps";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation){return "Pe";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote){return "Pi";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote){return "Pf";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation){return "Po";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::MathSymbol){return "Sm";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol){return "Sc";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol){return "Sk";}
    if(c == SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol){return "So";}
    return "??";
}

QString officialCategoryToSGExtnCategory(const QString& c){
    if(c == "Mn"){return "NonspacingMark";}
    if(c == "Mc"){return "CombiningMark";}
    if(c == "Me"){return "EnclosingMark";}
    if(c == "Nd"){return "NumericalDigit";}
    if(c == "Nl"){return "LetterNumber";}
    if(c == "No"){return "OtherNumber";}
    if(c == "Zs"){return "SpaceBreak";}
    if(c == "Zl"){return "LineBreak";}
    if(c == "Zp"){return "ParagraphBreak";}
    if(c == "Cc"){return "ControlCharacter";}
    if(c == "Cf"){return "FormatCharacter";}
    if(c == "Cs"){return "SurrogateCharacter";}
    if(c == "Co"){return "PrivateUseCharacter";}
    if(c == "Cn"){return "UnassignedCharacter";}
    if(c == "Lu"){return "UppercaseLetter";}
    if(c == "Ll"){return "LowercaseLetter";}
    if(c == "Lt"){return "TitlecaseLetter";}
    if(c == "Lm"){return "ModifierLetter";}
    if(c == "Lo"){return "OtherLetter";}
    if(c == "Pc"){return "ConnectorPunctuation";}
    if(c == "Pd"){return "DashPunctuation";}
    if(c == "Ps"){return "OpeningPunctuation";}
    if(c == "Pe"){return "ClosingPunctuation";}
    if(c == "Pi"){return "OpeningQuote";}
    if(c == "Pf"){return "ClosingQuote";}
    if(c == "Po"){return "OtherPunctuation";}
    if(c == "Sm"){return "MathSymbol";}
    if(c == "Sc"){return "CurrencySymbol";}
    if(c == "Sk"){return "ModifierSymbol";}
    if(c == "So"){return "OtherSymbol";}
    return (QString("unknown type: ") + c);
}

void extractCategory(){
    categoryStorage = QVector<QString>();
    for(int i=0; i<=0x10ffff; i++){
        QString thisCategory = "UnassignedCharacter";
        if(i >= 0x3400 && i <= 0x4DBF){thisCategory = "OtherLetter";}
        if(i >= 0x4E00 && i <= 0x9FFF){thisCategory = "OtherLetter";}
        if(i >= 0xAC00 && i <= 0xD7AF){thisCategory = "OtherLetter";}
        if(i >= 0x17000 && i <= 0x187ff){thisCategory = "OtherLetter";}
        if(i >= 0x18d00 && i <= 0x18d1e){thisCategory = "OtherLetter";}
        if(i >= 0x20000 && i <= 0x2A6DF){thisCategory = "OtherLetter";}
        if(i >= 0x2A700 && i <= 0x2B739){thisCategory = "OtherLetter";}
        if(i >= 0x2B740 && i <= 0x2B81D){thisCategory = "OtherLetter";}
        if(i >= 0x2B820 && i <= 0x2CEAF){thisCategory = "OtherLetter";}
        if(i >= 0x2ceb0 && i <= 0x2ebe0){thisCategory = "OtherLetter";}
        if(i >= 0x2ebf0 && i <= 0x2ee5d){thisCategory = "OtherLetter";}
        if(i >= 0x30000 && i <= 0x3134a){thisCategory = "OtherLetter";}
        if(i >= 0x31350 && i <= 0x323af){thisCategory = "OtherLetter";}
        if(i >= 0x323b0 && i <= 0x33479){thisCategory = "OtherLetter";}
        if(i >= 0xE000 && i <= 0xF8FF){thisCategory = "PrivateUseCharacter";}
        if(i >= 0xf0000 && i <= 0xffffd){thisCategory = "PrivateUseCharacter";}
        if(i >= 0x100000 && i <= 0x10fffd){thisCategory = "PrivateUseCharacter";}
        if(i >= 0xD800 && i <= 0xDB7F){thisCategory = "SurrogateCharacter";}
        if(i >= 0xDB80 && i <= 0xDBFF){thisCategory = "SurrogateCharacter";}
        if(i >= 0xDC00 && i <= 0xDFFF){thisCategory = "SurrogateCharacter";}
        if(allOfUnicode.contains(i) == true){
            if(allOfUnicode[i].at(1) != ""){
                thisCategory = officialCategoryToSGExtnCategory(allOfUnicode[i].at(1));
            }
        }
        categoryStorage.push_back(thisCategory);
    }
}

void printCategory(int start){
    QString prevCategory = "";
    QString logInfo = "";
    int prevCount = 0;
    for(int i=start; i<categoryStorage.length(); i++){
        if(categoryStorage.at(i) != prevCategory){
            prevCount++;
            logInfo = QString::number(prevCount) + " " + logInfo;
            qDebug().noquote() << logInfo;
            logInfo = QString::number(i, 16).toLower() + " " + categoryStorage.at(i);
            prevCategory = categoryStorage.at(i);
            prevCount = 0;
        }
        else{prevCount++;}
    }
    qDebug().noquote() << logInfo;
}

SGEXTN::ApplicationBase::FullCharacterType getUnicodeFullType(int i){
    if(i < 0x20){return SGEXTN::ApplicationBase::FullCharacterType::ControlCharacter;}
    if(i >= 0x30 && i < 0x3a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
    if(i >= 0x20 && i < 0x41){
        if(i == 0x20){return SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak;}
        if(i >= 0x21 && i < 0x24){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x24){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0x25 && i < 0x28){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x28){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x29){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0x2a || i == 0x2c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2b){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x2d){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x2e && i < 0x30){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x3a && i < 0x3c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x3c && i < 0x3f){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x3f && i < 0x41){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
    }
    if(i >= 0x41 && i < 0x5b){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
    if(i >= 0x5b && i < 0x61){
        if(i == 0x5b){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x5c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x5d){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0x5e || i == 0x60){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0x5f){return SGEXTN::ApplicationBase::FullCharacterType::ConnectorPunctuation;}
    }
    if(i >= 0x61 && i < 0x7b){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
    if(i >= 0x7b && i < 0x7f){
        if(i == 0x7b){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x7c){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x7d){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0x7e){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
    }
    if(i >= 0x7f && i < 0xa0){return SGEXTN::ApplicationBase::FullCharacterType::ControlCharacter;}
    if(i >= 0x4e00 && i <= 0x9fff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0xb80 && i <= 0xbff){
        if(i == 0xb82){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xb83 && i < 0xb8b && i != 0xb84){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb8e && i < 0xb96 && i != 0xb91){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb99 && i < 0xba0 && i != 0xb9b && i != 0xb9d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xba3 && i < 0xba5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xba8 && i < 0xbab){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xbae && i < 0xbba){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xbbe && i < 0xbc0){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xbc0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xbc1 && i < 0xbc3){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xbc6 && i < 0xbc9){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xbca && i < 0xbcd){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xbcd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xbd0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xbd7){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xbe6 && i < 0xbf0){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xbf0 && i < 0xbf3){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0xbf3 && i < 0xbf9){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xbf9){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i == 0xbfa){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2200 && i <= 0x22ff){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}

    if(i >= 0xa0 && i <= 0xff){
        if(i == 0xa0){return SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak;}
        if(i == 0xa1){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa2 && i < 0xa6){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i == 0xa6){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xa7){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xa8){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0xa9){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xaa){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xab){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i == 0xac){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0xad){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i == 0xae){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xaf){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0xb0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xb1){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0xb2 && i < 0xb4){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0xb4){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0xb5){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xb6 && i < 0xb8){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xb8){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0xb9){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0xba){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xbb){return SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote;}
        if(i >= 0xbc && i < 0xbf){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0xbf){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xc0 && i < 0xdf && i != 0xd7){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xdf && i < 0x100 && i != 0xf7){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xd7 || i == 0xf7){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x100 && i <= 0x17f){
        if(i >= 0x100 && i < 0x138 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x100 && i < 0x138){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x138 && i < 0x149 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x138 && i < 0x149){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x149 && i < 0x179 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x149 && i < 0x179){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x179 && i < 0x17f && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x179 && i < 0x17f){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x17f){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x180 && i <= 0x24f){
        if(i == 0x180){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x181){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x182 && i < 0x187 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x182 && i < 0x187){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x187){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x188){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x189 && i < 0x18c){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x18c && i < 0x18e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x18e && i < 0x192){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x192){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x193 && i < 0x195){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x195){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x196 && i < 0x199){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x199 && i < 0x19c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x19c && i < 0x19e){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x19e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x19f && i < 0x1a1){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1a1 && i < 0x1a7 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1a1 && i < 0x1a7){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1a7 && i < 0x1ab && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1a7 && i < 0x1ab){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1ab && i < 0x1af && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1ab && i < 0x1af){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1af){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1b0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1b1 && i < 0x1b4){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1b4 || i == 0x1b6){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1b5){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1b7 && i < 0x1b9){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1b9 && i < 0x1bb){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1bb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1bc){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1bd && i < 0x1c0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1c0 && i < 0x1c4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1c4 || i == 0x1c7 || i == 0x1ca){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1c5 || i == 0x1c8 || i == 0x1cb){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(i == 0x1c6 || i == 0x1c9){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1cc && i < 0x1dd && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1cc && i < 0x1dd){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1dd && i < 0x1f0 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1dd && i < 0x1f0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1f0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1f1){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1f2){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(i == 0x1f3 || i == 0x1f5){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1f4){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f6 && i < 0x1f9){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f9 && i < 0x234 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f9 && i < 0x234){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x234 && i < 0x23a){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x23a && i < 0x23c){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x23c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x23d && i < 0x23f){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x23f && i < 0x241){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x241){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x242){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x243 && i < 0x247){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x247 && i < 0x250 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x247 && i < 0x250){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x250 && i <= 0x2af){
        if(i >= 0x250 && i < 0x294){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 294 && i < 0x296){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x296 && i < 0x2b0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2b0 && i <= 0x2ff){
        if(i >= 0x2b0 && i < 0x2c2){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x2c2 && i < 0x2c6){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x2c6 && i < 0x2d2){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x2d2 && i < 0x2e0){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x2e0 && i < 0x2e5){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x2e5 && i < 0x2ec){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0x2ec || i == 0x2ee){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x2ed){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x2ef && i < 0x300){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x300 && i <= 0x36f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
    if(i >= 0x370 && i <= 0x3ff){
        if(i == 0x370 || i == 0x372){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x371 || i == 0x373){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x374){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x375){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0x376){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x377){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x37a){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x37b && i < 0x37e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x37e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x37f){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x384 && i < 0x386){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0x386){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x387){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x388 && i < 0x38b){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x38c){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x38e && i < 0x390){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x390){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x391 && i < 0x3a2){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3a3 && i < 0x3ac){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3ac && i < 0x3cf){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x3cf){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3d0 && i < 0x3d2){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x3d2 && i < 0x3d5){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3d5 && i < 0x3d8){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x3d8 && i < 0x3f0 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3d8 && i < 0x3f0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x3f0 && i < 0x3f4){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x3f4 || i == 0x3f7){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x3f5 || i == 0x3f8){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x3f6){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x3f9 && i < 0x3fb){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3fb && i < 0x3fd){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x3fd && i < 0x400){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x400 && i <= 0x4ff){
        if(i >= 0x400 && i < 0x430){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x430 && i < 0x460){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x460 && i < 0x482 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x460 && i < 0x482){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x482){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x483 && i < 0x488){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x488 && i < 0x48a){return SGEXTN::ApplicationBase::FullCharacterType::EnclosingMark;}
        if(i >= 0x48a && i < 0x4c1 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x48a && i < 0x4c1){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x4c1 && i < 0x4cf && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x4c1 && i < 0x4cf){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x4cf && i < 0x500 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x4cf && i < 0x500){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x500 && i <= 0x52f){
        if(i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        else{return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
    }
    if(i >= 0x530 && i <= 0x58f){
        if(i >= 0x531 && i < 0x557){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x559){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x55a && i < 0x560){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x560 && i < 0x589){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x589){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x58a){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x58d && i < 0x58f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x58f){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x590 && i <= 0x5ff){
        if(i >= 0x591 && i < 0x5be){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x5be){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i == 0x5bf){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x5c0){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x5c1 && i < 0x5c3){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x5c3){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x5c4 && i < 0x5c6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x5c6){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x5c7){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x5d0 && i < 0x5eb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x5ef && i < 0x5f3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x5f3 && i < 0x5f5){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x600 && i <= 0x6ff){
        if(i >= 0x600 && i < 0x606){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0x606 && i < 0x609){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x609 && i < 0x60b){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x60b){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0x60c && i < 0x60e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x60e && i < 0x610){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x610 && i < 0x61b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x61b){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x61c){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0x61d && i < 0x620){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x620 && i < 0x640){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x640){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x641 && i < 0x64b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x64b && i < 0x660){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x660 && i < 0x66a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x66a && i < 0x66e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x66e && i < 0x670){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x670){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x671 && i < 0x6d4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x6d4){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x6d5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x6d6 && i < 0x6dd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x6dd){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i == 0x6de){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x6df && i < 0x6e5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x6e5 && i < 0x6e7){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x6e7 && i < 0x6e9){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x6e9){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x6ea && i < 0x6ee){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x6ee && i < 0x6f0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x6f0 && i < 0x6fa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x6fa && i < 0x6fd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x6fd && i < 0x6ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x6ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x700 && i <= 0x74f){
        if(i >= 0x700 && i < 0x70e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x70f){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i == 0x710){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x711){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x712 && i < 0x730){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x730 && i < 0x74b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x74d && i < 0x750){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x750 && i <= 0x77f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x780 && i <= 0x7bf){
        if(i >= 0x780 && i < 0x7a6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x7a6 && i < 0x7b1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x7b1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x7c0 && i <= 0x7ff){
        if(i >= 0x7c0 && i < 0x7ca){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x7ca && i < 0x7eb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x7eb && i < 0x7f4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x7f4 && i < 0x7f6){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x7f6){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x7f7 && i < 0x7fa){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x7fa){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x7fd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x7fe && i < 0x800){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x800 && i <= 0x83f){
        if(i >= 0x800 && i < 0x816){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x816 && i < 0x81a){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x81a){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x81b && i < 0x824){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x824){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x825 && i < 0x828){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x828){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x829 && i < 0x82e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x830 && i < 0x83f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x840 && i <= 0x85f){
        if(i >= 0x840 && i < 0x859){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x859 && i < 0x85c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x85e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x860 && i <= 0x86f){
        if(i >= 0x860 && i < 0x86b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x870 && i <= 0x89f){
        if(i >= 0x870 && i < 0x888){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x888){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x889 && i < 0x890){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x890 && i < 0x892){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0x897 && i < 0x8a0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x8a0 && i <= 0x8ff){
        if(i >= 0x8a0 && i < 0x8c9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x8c9){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x8ca && i < 0x8e2){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x8e2){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0x8e3 && i < 0x900){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x900 && i <= 0x97f){
        if(i >= 0x900 && i < 0x903){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x903){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x904 && i < 0x93a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x93a || i == 0x93c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x93b){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x93d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x93e && i < 0x941){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x941 && i < 0x949){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x949 && i < 0x94d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x94d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x94e && i < 0x950){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x950){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x951 && i < 0x958){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x958 && i < 0x962){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x962 && i < 0x964){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x964 && i < 0x966){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x966 && i < 0x970){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x970){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x971){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x972 && i < 0x980){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x980 && i <= 0x9ff){
        if(i == 0x980){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x981){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x982 && i < 0x984){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x985 && i < 0x98d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x98f && i < 0x991){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x993 && i < 0x9a9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x9aa && i < 0x9b1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x9b2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x9b6 && i < 0x9ba){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x9bc){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x9bd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x9be && i < 0x9c1){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x9c1 && i < 0x9c5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x9c7 && i < 0x9c9){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x9cb && i < 0x9cd){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x9cd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x9ce){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x9d7){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x9dc && i < 0x9de){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x9df && i < 0x9e2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x9e2 && i < 0x9e4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x9e6 && i < 0x9f0){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x9f0 && i < 0x9f2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x9f2 && i < 0x9f4){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0x9f4 && i < 0x9fa){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x9fa){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x9fb){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i == 0x9fc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x9fd){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x9fe){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa00 && i <= 0xa7f){
        if(i >= 0xa01 && i < 0xa03){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xa03){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa05 && i < 0xa0b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa0f && i < 0xa11){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa13 && i < 0xa29){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa2a && i < 0xa31){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa32 && i < 0xa34){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa35 && i < 0xa37){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa38 && i < 0xa3a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa3c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa3e && i < 0xa41){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa41 && i < 0xa43){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa47 && i < 0xa49){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa4b && i < 0xa4e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xa51){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa59 && i < 0xa5d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa5e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa66 && i < 0xa70){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xa70 && i < 0xa72){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa72 && i < 0xa75){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa75){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xa76){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa80 && i <= 0xaff){
        if(i >= 0xa81 && i < 0xa83){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xa83){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa85 && i < 0xa8e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa8f && i < 0xa92){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa93 && i<0xaa9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xaaa && i < 0xab1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xab2 && i < 0xab4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xab5 && i < 0xaba){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xabc){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xabd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xabe && i < 0xac1){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xac1 && i < 0xac6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xac7 && i < 0xac9){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xac9 && i < 0xaca){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xacb && i < 0xacd){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xacd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xad0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xae0 && i < 0xae2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xae2 && i < 0xae4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xae6 && i < 0xaf0){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0xaf0){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xaf1){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i == 0xaf9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xafa && i < 0xb00){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xb00 && i <= 0xb7f){
        if(i == 0xb01){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xb02 && i < 0xb04){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xb05 && i < 0xb0d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb0f && i < 0xb11){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb13 && i < 0xb29){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb2a && i < 0xb31){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb32 && i < 0xb34){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb35 && i < 0xb3a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xb3c || i == 0xb3f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xb3d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xb3e || i == 0xb40){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xb41 && i < 0xb45){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xb47 && i < 0xb49){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xb4b && i < 0xb4d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xb4d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xb55 && i < 0xb57){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xb57){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xb5c && i < 0xb5e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb5f && i < 0xb62){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb62 && i < 0xb64){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xb66 && i < 0xb70){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0xb70){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xb71){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xb72 && i < 0xb78){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xc00 && i <= 0xc7f){
        if(i == 0xc00){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xc01 && i < 0xc04){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xc04){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xc05 && i < 0xc0d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc0e && i < 0xc11){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc12 && i < 0xc29){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc2a && i < 0xc3a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xc3c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xc3d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc3e && i < 0xc41){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xc41 && i < 0xc45){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xc46 && i < 0xc49){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xc4a && i < 0xc4e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xc55 && i < 0xc57){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xc58 && i < 0xc5b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc5c && i < 0xc5e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc60 && i < 0xc62){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc62 && i < 0xc64){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xc66 && i < 0xc70){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0xc77){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xc78 && i < 0xc7f){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0xc7f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xc80 && i <= 0xcff){
        if(i == 0xc80){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xc81){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xc82 && i < 0xc84){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xc84){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xc85 && i < 0xc8d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc8e && i < 0xc91){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xc92 && i < 0xca9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xcaa && i < 0xcb4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xcb5 && i < 0xcba){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xcbc){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xcbd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xcbe){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xcbf){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xcc0 && i < 0xcc5){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xcc6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xcc7 && i < 0xcc9){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xcca && i < 0xccc){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xccc && i < 0xcce){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xcd5 && i < 0xcd7){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xcdc && i < 0xcdf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xce0 && i < 0xce2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xce2 && i < 0xce4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xce6 && i < 0xcf0){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xcf1 && i < 0xcf3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xcf3){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xd00 && i <= 0xd7f){
        if(i >= 0xd00 && i < 0xd02){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xd02 && i < 0xd04){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xd04 && i < 0xd0d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xd0e && i < 0xd11){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xd12 && i < 0xd3b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xd3b && i < 0xd3d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xd3d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xd3e && i < 0xd41){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xd41 && i < 0xd45){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xd46 && i < 0xd49){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xd4a && i < 0xd4d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xd4d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xd4e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xd4f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xd54 && i < 0xd57){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xd57){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xd58 && i < 0xd5f){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0xd5f && i < 0xd62){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xd62 && i < 0xd64){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xd66 && i < 0xd70){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xd70 && i < 0xd79){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0xd79){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xd7a && i < 0xd80){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xd80 && i <= 0xdff){
        if(i == 0xd81){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xd82 && i < 0xd84){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xd85 && i < 0xd97){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xd9a && i < 0xdb2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xdb3 && i < 0xdbc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xdbd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xdc0 && i < 0xdc7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xdca){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xdcf && i < 0xdd2){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xdd2 && i < 0xdd5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xdd6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xdd8 && i < 0xde0){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xde6 && i < 0xdf0){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xdf2 && i < 0xdf4){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xdf4){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xe00 && i <= 0xe7f){
        if(i >= 0xe01 && i < 0xe31){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xe31){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xe32 && i < 0xe34){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xe34 && i < 0xe3b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xe3f){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0xe40 && i < 0xe46){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xe46){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xe47 && i < 0xe4f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xe4f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xe50 && i < 0xe5a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xe5a && i < 0xe5c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xe80 && i <= 0xeff){
        if(i >= 0xe81 && i < 0xe83){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xe84){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xe86 && i < 0xe8b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xe8c && i < 0xea4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xea5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xea7 && i < 0xeb1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xeb1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xeb2 && i < 0xeb4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xeb4 && i < 0xebd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xebd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xec0 && i < 0xec5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xec6){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xec8 && i < 0xecf){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xed0 && i < 0xeda){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xedc && i < 0xee0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xf00 && i <= 0xfff){
        if(i == 0xf00){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xf01 && i < 0xf04){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xf04 && i < 0xf13){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xf13){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xf14){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xf15 && i < 0xf18){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xf18 && i < 0xf1a){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xf1a && i < 0xf20){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xf20 && i < 0xf2a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xf2a && i < 0xf34){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0xf34 || i == 0xf36 || i == 0xf38){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xf35 || i == 0xf37 || i == 0xf39){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xf3a || i == 0xf3c){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0xf3b || i == 0xf3d){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0xf3e && i < 0xf40){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xf40 && i < 0xf48){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xf49 && i < 0xf6d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xf71 && i < 0xf7f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xf7f){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xf80 && i < 0xf85){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xf85){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xf86 && i < 0xf88){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xf88 && i < 0xf8d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xf8d && i < 0xf98){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xf99 && i < 0xfbd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xfbe && i < 0xfc6){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xfc6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xfc7 && i < 0xfcd){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xfce && i < 0xfd0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xfd0 && i < 0xfd5){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xfd5 && i < 0xfd9){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xfd9 && i < 0xfdb){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1000 && i <= 0x109f){
        if(i >= 0x1000 && i < 0x102b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x102b && i < 0x102d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x102d && i < 0x1031){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1031){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1032 && i < 0x1038){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1038){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1039 && i < 0x103b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x103b && i < 0x103d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x103d && i < 0x103f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x103f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1040 && i < 0x104a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x104a && i < 0x1050){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1050 && i < 0x1056){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1056 && i < 0x1058){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1058 && i < 0x105a){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x105a && i < 0x105e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x105e && i < 0x1061){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1061){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1062 && i < 0x1065){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1065 && i < 0x1067){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1067 && i < 0x106e){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x106e && i < 0x1071){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1071 && i < 0x1075){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1075 && i < 0x1082){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1082){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1083 && i < 0x1085){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1085 && i < 0x1087){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1087 && i < 0x108d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x108d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x108e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x108f){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1090 && i < 0x109a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x109a && i < 0x109d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x109d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x109e && i < 0x10a0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10a0 && i <= 0x10ff){
        if(i >= 0x10a0 && i < 0x10c6){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x10c7 || i == 0x10cd){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10d0 && i < 0x10fb){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x10fb){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x10fc){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x10fd && i < 0x1100){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1100 && i <= 0x11ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x1200 && i <= 0x137f){
        if(i >= 0x1200 && i < 0x1249){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x124a && i < 0x124e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1250 && i < 0x1257){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1258){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x125a && i < 0x125e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1260 && i < 0x1289){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x128a && i < 0x128e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1290 && i < 0x12b1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x12b2 && i < 0x12b6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x12b8 && i < 0x12bf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x12c0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x12c2 && i < 0x12c6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x12c8 && i < 0x12d7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x12d8 && i < 0x1311){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1312 && i < 0x1316){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1318 && i < 0x135b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x135d && i < 0x1360){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1360 && i < 0x1369){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1369 && i < 0x137d){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1380 && i <= 0x139f){
        if(i >= 0x1380 && i < 0x1390){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1390 && i < 0x139a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x13a0 && i <= 0x13ff){
        if(i >= 0x13a0 && i < 0x13f6){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x13f8 && i < 0x13fe){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1400 && i <= 0x167f){
        if(i == 0x1400){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x1401 && i < 0x166d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x166d){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x166e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x166f && i < 0x1680){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1680 && i <= 0x169f){
        if(i == 0x1680){return SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak;}
        if(i >= 0x1681 && i < 0x169b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x169b){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x169c){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16a0 && i <= 0x16ff){
        if(i >= 0x16a0 && i < 0x16eb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x16eb && i < 0x16ee){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x16ee && i < 0x16f1){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i >= 0x16f1 && i < 0x16f9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1700 && i <= 0x171f){
        if(i >= 0x1700 && i < 0x1712){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1712 && i < 0x1715){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1715){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x171f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1720 && i <= 0x173f){
        if(i >= 0x1720 && i < 0x1732){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1732 && i < 0x1734){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1734){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1735 && i < 0x1737){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1740 && i <= 0x175f){
        if(i >= 0x1740 && i < 0x1752){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1752 && i < 0x1754){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1760 && i <= 0x177f){
        if(i >= 0x1760 && i < 0x176d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x176e && i < 0x1771){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1772 && i < 0x1774){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1780 && i <= 0x17ff){
        if(i >= 0x1780 && i < 0x17b4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x17b4 && i < 0x17b6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x17b6){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x17b7 && i < 0x17be){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x17be && i < 0x17c6){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x17c6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x17c7 && i < 0x17c9){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x17c9 && i < 0x17d4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x17d4 && i < 0x17d7){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x17d7){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x17d8 && i < 0x17db){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x17db){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i == 0x17dc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x17dd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x17e0 && i < 0x17ea){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x17f0 && i < 0x17fa){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1800 && i <= 0x18af){
        if(i >= 0x1800 && i < 0x1806){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x1806){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x1807 && i < 0x180b){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x180b && i < 0x180e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x180e){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i == 0x180f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1810 && i < 0x181a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1820 && i < 0x1843){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1843){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1844 && i < 0x1879){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1880 && i < 0x1885){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1885 && i < 0x1887){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1887 && i < 0x18a9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x18a9){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x18aa){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x18b0 && i <= 0x18ff){
        if(i >= 0x18b0 && i < 0x18f6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1900 && i <= 0x194f){
        if(i >= 0x1900 && i < 0x191f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1920 && i < 0x1923){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1923 && i < 0x1927){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1927 && i < 0x1929){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1929 && i < 0x192c){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1930 && i < 0x1932){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x1932){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1933 && i < 0x1939){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1939 && i < 0x193c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1940){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1944 && i < 0x1946){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1946 && i < 0x1950){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1950 && i <= 0x197f){
        if(i >= 0x1950 && i < 0x196e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1970 && i < 0x1975){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1980 && i <= 0x19df){
        if(i >= 0x1980 && i < 0x19ac){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x19b0 && i < 0x19ca){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x19d0 && i < 0x19da){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x19da){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x19de && i < 0x19e0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x19e0 && i <= 0x19ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x1a00 && i <= 0x1a1f){
        if(i >= 0x1a00 && i < 0x1a17){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1a17 && i < 0x1a19){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1a19 && i < 0x1a1b){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x1a1b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1a1e && i < 0x1a20){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1a20 && i <= 0x1aaf){
        if(i >= 0x1a20 && i < 0x1a55){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1a55 || i == 0x1a57){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x1a56){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1a58 && i < 0x1a5f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1a60 || i == 0x1a62){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1a61){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1a63 && i < 0x1a65){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1a65 && i < 0x1a6d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1a6d && i < 0x1a73){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1a73 && i < 0x1a7d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1a7f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1a80 && i < 0x1a8a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1a90 && i < 0x1a9a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1aa0 && i < 0x1aa7){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x1aa7){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1aa8 && i < 0x1aae){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1ab0 && i <= 0x1aff){
        if(i >= 0x1ab0 && i < 0x1abe){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1abe){return SGEXTN::ApplicationBase::FullCharacterType::EnclosingMark;}
        if(i >= 0x1abf && i < 0x1ade){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1ae0 && i < 0x1aec){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b00 && i <= 0x1b7f){
        if(i >= 0x1b00 && i < 0x1b04){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1b04){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1b05 && i < 0x1b34){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1b34){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1b35){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1b36 && i < 0x1b3b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1b3b){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x1b3c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1b3d && i < 0x1b42){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x1b42){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1b43 && i < 0x1b45){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1b45 && i < 0x1b4d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1b4e && i < 0x1b50){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1b50 && i < 0x1b5a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1b5a && i < 0x1b61){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1b61 && i < 0x1b6b){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1b6b && i < 0x1b74){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1b74 && i < 0x1b7d){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1b7d && i < 0x1b80){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b80 && i <= 0x1bbf){
        if(i >= 0x1b80 && i < 0x1b82){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1b82){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1b83 && i < 0x1ba1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1ba1){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1ba2 && i < 0x1ba6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1ba6 && i < 0x1ba8){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1ba8 && i < 0x1baa){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1baa){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1bab && i < 0x1bae){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1bae && i < 0x1bb0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1bb0 && i < 0x1bba){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1bba && i < 0x1bc0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1bc0 && i <= 0x1bff){
        if(i >= 0x1bc0 && i < 0x1be6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1be6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1be7){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1be8 && i < 0x1bea){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1bea && i < 0x1bed){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x1bed){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1bee){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1bef && i < 0x1bf2){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1bf2 && i < 0x1bf4){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1bfc && i < 0x1c00){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1c00 && i <= 0x1c4f){
        if(i >= 0x1c00 && i < 0x1c24){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1c24 && i < 0x1c2c){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1c2c && i < 0x1c34){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1c34 && i < 0x1c36){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1c36 && i < 0x1c38){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1c3b && i < 0x1c40){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1c40 && i < 0x1c4a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1c4d && i < 0x1c50){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1c50 && i <= 0x1c7f){
        if(i >= 0x1c50 && i < 0x1c5a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1c5a && i < 0x1c78){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1c78 && i < 0x1c7e){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1c7e && i < 0x1c80){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1c80 && i <= 0x1c8f){
        if(i >= 0x1c80 && i < 0x1c89){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1c89){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1c8a){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1c90 && i <= 0x1cbf){
        if(i >= 0x1c90 && i < 0x1cbb){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1cbd && i < 0x1cc0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cc0 && i <= 0x1ccf){
        if(i >= 0x1cc0 && i < 0x1cc8){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cd0 && i <= 0x1cff){
        if(i >= 0x1cd0 && i < 0x1cd3){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1cd3){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1cd4 && i < 0x1ce1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1ce1){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1ce2 && i < 0x1ce9){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1ce9 && i < 0x1ced){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1ced){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1cee && i < 0x1cf4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1cf4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1cf5 && i < 0x1cf7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1cf7){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1cf8 && i < 0x1cfa){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1cfa){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d00 && i <= 0x1d7f){
        if(i >= 0x1d00 && i < 0x1d2c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d2c && i < 0x1d6b){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1d6b && i < 0x1d78){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d78){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1d79 && i < 0x1d80){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d80 && i <= 0x1dbf){
        if(i >= 0x1d80 && i < 0x1d9b){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d9b && i < 0x1dc0){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
    }
    if(i >= 0x1dc0 && i <= 0x1dff){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
    if(i >= 0x1e00 && i <= 0x1eff){
        if(i >= 0x1e00 && i < 0x1e95 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1e00 && i < 0x1e95){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1e95 && i < 0x1e9e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1e9e && i < 0x1f00 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1e9e && i < 0x1f00){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f00 && i <= 0x1fff){
        if(i >= 0x1f00 && i < 0x1f08){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f08 && i < 0x1f10){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f10 && i < 0x1f16){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f18 && i < 0x1f1e){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f20 && i < 0x1f28){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f28 && i < 0x1f30){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f30 && i < 0x1f38){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f38 && i < 0x1f40){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f40 && i < 0x1f46){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f48 && i < 0x1f4e){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f50 && i < 0x1f58){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f59 && i < 0x1f60 && i % 2 == 1){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f60 && i < 0x1f68){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f68 && i < 0x1f70){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f70 && i < 0x1f7e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f80 && i < 0x1f88){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f88 && i < 0x1f90){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1f90 && i < 0x1f98){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f98 && i < 0x1fa0){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1fa0 && i < 0x1fa8){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fa8 && i < 0x1fb0){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1fb0 && i < 0x1fb5){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fb6 && i < 0x1fb8){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fb8 && i < 0x1fbc){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1fbc){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(i == 0x1fbd){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0x1fbe){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fbf && i < 0x1fc2){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1fc2 && i < 0x1fc5){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fc6 && i < 0x1fc8){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fc8 && i < 0x1fcc){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1fcc){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1fcd && i < 0x1fd0){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1fd0 && i < 0x1fd4){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fd6 && i < 0x1fd8){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fd8 && i < 0x1fdc){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1fdd && i < 0x1fe0){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1fe0 && i < 0x1fe8){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fe8 && i < 0x1fed){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1fed && i < 0x1ff0){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1ff2 && i < 0x1ff5){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1ff6 && i < 0x1ff8){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1ff8 && i < 0x1ffc){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1ffc){return SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1ffd && i < 0x1fff){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2000 && i <= 0x206f){
        if(i >= 0x2000 && i < 0x200b){return SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak;}
        if(i >= 0x200b && i < 0x2010){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0x2010 && i < 0x2016){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x2016 && i < 0x2018){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2018){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i == 0x2019 || i == 0x201d){return SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote;}
        if(i == 0x201a || i == 0x201e){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x201b && i < 0x201d){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i >= 0x201f && i < 0x2020){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i >= 0x2020 && i < 0x2028){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2028){return SGEXTN::ApplicationBase::FullCharacterType::LineBreak;}
        if(i == 0x2029){return SGEXTN::ApplicationBase::FullCharacterType::ParagraphBreak;}
        if(i >= 0x202a && i < 0x202f){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i == 0x202f){return SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak;}
        if(i >= 0x2030 && i < 0x2039){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2039){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i == 0x203a){return SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote;}
        if(i >= 0x203b && i < 0x203f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x203f && i < 0x2041){return SGEXTN::ApplicationBase::FullCharacterType::ConnectorPunctuation;}
        if(i >= 0x2041 && i < 0x2044){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2044){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x2045){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x2046){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2047 && i < 0x2052){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2052){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x2053){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2054){return SGEXTN::ApplicationBase::FullCharacterType::ConnectorPunctuation;}
        if(i >= 0x2055 && i < 0x205f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x205f){return SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak;}
        if(i >= 0x2060 && i < 0x2065){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0x2066 && i < 0x2070){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2070 && i <= 0x209f){
        if(i == 0x2070){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x2071){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x2074 && i < 0x207a){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x207a && i < 0x207d){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x207d){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x207e){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0x207f){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x2080 && i < 0x208a){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x208a && i < 0x208d){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x208d){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x208e){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2090 && i < 0x209d){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x20a0 && i <= 0x20cf){
        if(i >= 0x20a0 && i < 0x20c2){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x20d0 && i <= 0x20ff){
        if(i >= 0x20d0 && i < 0x20dd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x20dd && i < 0x20e1){return SGEXTN::ApplicationBase::FullCharacterType::EnclosingMark;}
        if(i == 0x20e1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x20e2 && i < 0x20e5){return SGEXTN::ApplicationBase::FullCharacterType::EnclosingMark;}
        if(i >= 0x20e5 && i < 0x20f1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2100 && i <= 0x214f){
        if(i >= 0x2100 && i < 0x2102){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x2102 || i == 0x2107){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2103 && i < 0x2107){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2108 && i < 0x210a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x210a){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x210b && i < 0x210e){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x210e && i < 0x2110){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2110 && i < 0x2113){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x2113){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x2114){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x2115){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2116 && i < 0x2118){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x2118){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x2119 && i < 0x211e){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x211e && i < 0x2124){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2124 && i < 0x212a && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2124 && i < 0x212a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x212a && i < 0x212e){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x212e){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x212f){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2130 && i < 0x2134){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x2134){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2135 && i < 0x2139){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x2139){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x213a && i < 0x213c){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x213c && i < 0x213e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x213e && i < 0x2140){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2140 && i < 0x2145){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x2145){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2146 && i < 0x214a){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x214a || i == 0x214f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x214b){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x214c && i < 0x214e){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x214e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2150 && i <= 0x218f){
        if(i >= 0x2150 && i < 0x2160){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x2160 && i < 0x2183){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i == 0x2183){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x2184){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2185 && i < 0x2189){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i == 0x2189){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x218a && i < 0x218c){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2190 && i <= 0x21ff){
        if(i >= 0x2190 && i < 0x2195){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x2195 && i < 0x219a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x219a && i < 0x219c){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x219c && i < 0x21a0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x21a0){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x21a1 && i < 0x21a3){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x21a3){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x21a4 && i < 0x21a6){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x21a6){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x21a7 && i < 0x21ae){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x21ae){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x21af && i < 0x21ce){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x21ce && i < 0x21d0){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x21d0 && i < 0x21d2){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x21d2 || i == 0x21d4){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x21d3){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x21d5 && i < 0x21f4){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x21f4 && i < 0x2200){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2300 && i <= 0x23ff){
        if(i >= 0x2300 && i < 0x2308){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x2308 || i == 0x230a){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x2309 || i == 0x230b){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x230c && i < 0x2320){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2320 && i < 0x2322){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x2322 && i < 0x2329){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x2329){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x232a){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x232b && i < 0x237c){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x237c){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x237d && i < 0x239b){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x239b && i < 0x23b4){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x23b4 && i < 0x23dc){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x23dc && i < 0x23e2){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x23e2 && i < 0x2400){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2400 && i <= 0x243f){
        if(i >= 0x2400 && i < 0x242a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2440 && i <= 0x245f){
        if(i >= 0x2440 && i < 0x244b){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2460 && i <= 0x24ff){
        if(i >= 0x2460 && i < 0x249c){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x249c && i < 0x24ea){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x24ea && i < 0x2500){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2500 && i <= 0x257f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x2580 && i <= 0x259f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x25a0 && i <= 0x25ff){
        if(i >= 0x25a0 && i < 0x25b7){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x25b7){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x25b8 && i < 0x25c1){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x25c1){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x25c2 && i < 0x25f8){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x25f8 && i < 0x2600){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2600 && i <= 0x26ff){
        if(i >= 0x2600 && i < 0x266f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x266f){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x2670 && i < 0x2700){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2700 && i <= 0x27bf){
        if(i >= 0x2700 && i < 0x2768){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2768 && i < 0x2776 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x2768 && i < 0x2776){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2776 && i < 0x2794){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x2794 && i < 0x27c0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x27c0 && i <= 0x27ef){
        if(i >= 0x27c0 && i < 0x27c5){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x27c5){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x27c6){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x27c7 && i < 0x27e6){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x27e6 && i < 0x27f0 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x27e6 && i < 0x27f0){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x27f0 && i <= 0x27ff){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
    if(i >= 0x2800 && i <= 0x28ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x2900 && i <= 0x297f){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
    if(i >= 0x2980 && i <= 0x29ff){
        if(i >= 0x2980 && i < 0x2983){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x2983 && i < 0x2999 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2983 && i < 0x2999){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x2999 && i < 0x29d8){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x29d8 || i == 0x29da){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x29d9 || i == 0x29db){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x29dc && i < 0x29fc){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0x29fc){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x29fd){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x29fe && i < 0x2a00){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2a00 && i <= 0x2aff){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
    if(i >= 0x2b00 && i <= 0x2bff){
        if(i >= 0x2b00 && i < 0x2b30){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2b30 && i < 0x2b45){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x2b45 && i < 0x2b47){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2b47 && i < 0x2b4d){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x2b4d && i < 0x2b74){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2b76 && i < 0x2c00){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2c00 && i <= 0x2c5f){
        if(i >= 0x2c00 && i < 0x2c30){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c30 && i < 0x2c60){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2c60 && i <= 0x2c7f){
        if(i == 0x2c60){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x2c61){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2c62 && i < 0x2c65){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c65 && i < 0x2c67){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x2c67 || i == 0x2c69 || i == 0x2c6b){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x2c68 || i == 0x2c6a || i == 0x2c6c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2c6d && i < 0x2c71){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x2c71){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x2c72){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c73 && i < 0x2c75){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x2c75){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c76 && i < 0x2c7c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2c7c && i < 0x2c7e){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x2c7e && i < 0x2c80){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2c80 && i <= 0x2cff){
        if(i >= 0x2c80 && i < 0x2ce3 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c80 && i < 0x2ce3){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2ce3 && i < 0x2ce5){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2ce5 && i < 0x2ceb){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x2ceb){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x2cec || i == 0x2cee){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x2ced){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2cef && i < 0x2cf2){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x2cf2){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x2cf3){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2cf9 && i < 0x2cfd){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2cfd){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x2cfe && i < 0x2d00){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2d00 && i <= 0x2d2f){
        if(i >= 0x2d00 && i < 0x2d26){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x2d27 || i == 0x2d2d){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2d30 && i <= 0x2d7f){
        if(i >= 0x2d30 && i < 0x2d68){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x2d6f){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x2d70){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2d7f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2d80 && i <= 0x2ddf){
        if(i >= 0x2d80 && i < 0x2d97){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2da0 && i < 0x2da7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2da8 && i < 0x2daf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2db0 && i < 0x2db7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2db8 && i < 0x2dbf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2dc0 && i < 0x2dc7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2dc8 && i < 0x2dcf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2dd0 && i < 0x2dd7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2dd8 && i < 0x2ddf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2de0 && i <= 0x2dff){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
    if(i >= 0x2e00 && i <= 0x2e7f){
        if(i >= 0x2e00 && i < 0x2e02){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e02 || i == 0x2e04){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i == 0x2e03 || i == 0x2e05){return SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote;}
        if(i >= 0x2e06 && i < 0x2e09){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e09 || i == 0x2e0c){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i == 0x2e0a || i == 0x2e0d){return SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote;}
        if(i == 0x2e0b){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x2e0e && i < 0x2e17){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e17){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x2e18 && i < 0x2e1a){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e1a){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i == 0x2e1b){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e1c){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i == 0x2e1d){return SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote;}
        if(i >= 0x2e1e && i < 0x2e20){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e20){return SGEXTN::ApplicationBase::FullCharacterType::OpeningQuote;}
        if(i == 0x2e21){return SGEXTN::ApplicationBase::FullCharacterType::ClosingQuote;}
        if(i >= 0x2e22 && i < 0x2e2a && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x2e22 && i < 0x2e2a){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2e2a && i < 0x2e2f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e2f){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x2e30 && i < 0x2e3a){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x2e3a && i < 0x2e3c){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x2e3c && i < 0x2e40){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e40){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i == 0x2e41){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e42){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x2e43 && i < 0x2e50){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x2e50 && i < 0x2e52){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2e52 && i < 0x2e55){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x2e55 && i < 0x2e5d && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2e55 && i < 0x2e5d){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0x2e5d){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2e80 && i <= 0x2eff){
        if(i >= 0x2e80 && i < 0x2e9a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x2e9b && i < 0x2ef4){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2f00 && i <= 0x2fdf){
        if(i >= 0x2f00 && i < 0x2fd6){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2ff0 && i <= 0x2fff){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x3000 && i <= 0x303f){
        if(i == 0x3000){return SGEXTN::ApplicationBase::FullCharacterType::SpaceBreak;}
        if(i >= 0x3001 && i < 0x3004){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x3004){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x3005){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x3006){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x3007){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i >= 0x3008 && i < 0x3012 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x3008 && i < 0x3012){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x3012 && i < 0x3014){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x3014 && i < 0x301c && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x3014 && i < 0x301c){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0x301c){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i == 0x301d){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x301e && i < 0x3020){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0x3020){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x3021 && i < 0x302a){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i >= 0x302a && i < 0x302e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x302e && i < 0x3030){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x3030){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x3031 && i < 0x3036){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x3036 && i < 0x3038){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x3038 && i < 0x303b){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i == 0x303b){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x303c){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x303d){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x303e && i < 0x3040){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3040 && i <= 0x309f){
        if(i >= 0x3041 && i < 0x3097){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x3099 && i < 0x309b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x309b && i < 0x309d){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x309d && i < 0x309f){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x309f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x30a0 && i <= 0x30ff){
        if(i == 0x30a0){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x30a1 && i < 0x30fb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x30fb){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x30fc && i < 0x30ff){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x30ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3100 && i <= 0x312f){
        if(i >= 0x3105 && i < 0x3130){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3130 && i <= 0x318f){
        if(i >= 0x3131 && i < 0x318f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3190 && i <= 0x319f){
        if(i >= 0x3190 && i < 0x3192){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x3192 && i < 0x3196){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x3196 && i < 0x31a0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x31a0 && i <= 0x31bf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x31c0 && i <= 0x31ef){
        if(i >= 0x31c0 && i < 0x31e6){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x31ef){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x31f0 && i <= 0x31ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x3200 && i <= 0x32ff){
        if(i >= 0x3200 && i < 0x321f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x3220 && i < 0x322a){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x322a && i < 0x3248){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x3248 && i < 0x3250){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x3250){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x3251 && i < 0x3260){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x3260 && i < 0x3280){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x3280 && i < 0x328a){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x328a && i < 0x32b1){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x32b1 && i < 0x32c0){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x32c0 && i < 0x3300){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3300 && i <= 0x33ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x3400 && i <= 0x4dbf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x4dc0 && i <= 0x4dff){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0xa000 && i <= 0xa48f){
        if(i >= 0xa000 && i < 0xa015){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa015){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa016 && i < 0xa48d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa490 && i <= 0xa4cf){
        if(i >= 0xa490 && i < 0xa4c7){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa4d0 && i <= 0xa4ff){
        if(i >= 0xa4d0 && i < 0xa4f8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa4f8 && i < 0xa4fe){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa4fe && i < 0xa500){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa500 && i <= 0xa63f){
        if(i >= 0xa500 && i < 0xa60c){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa60c){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa60d && i < 0xa610){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa610 && i < 0xa620){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa620 && i < 0xa62a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xa62a && i < 0xa62c){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa640 && i <= 0xa69f){
        if(i >= 0xa640 && i < 0xa66e && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa640 && i < 0xa66e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xa66e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa66f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa670 && i < 0xa673){return SGEXTN::ApplicationBase::FullCharacterType::EnclosingMark;}
        if(i == 0xa673){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa674 && i < 0xa67e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xa67e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xa67f){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa680 && i < 0xa69c && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa680 && i < 0xa69c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa69c && i < 0xa69e){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa69e && i < 0xa6a0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa6a0 && i <= 0xa6ff){
        if(i >= 0xa6a0 && i < 0xa6e6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa6e6 && i < 0xa6f0){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i >= 0xa6f0 && i < 0xa6f2){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa6f2 && i < 0xa6f8){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa700 && i <= 0xa71f){
        if(i >= 0xa700 && i < 0xa717){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0xa717 && i < 0xa720){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa720 && i <= 0xa7ff){
        if(i >= 0xa720 && i < 0xa722){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0xa722 && i < 0xa72f && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa722 && i < 0xa72f){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa72f && i < 0xa732){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa732 && i < 0xa770 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa732 && i < 0xa770){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xa770){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa771 && i < 0xa779){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa779 && i < 0xa77e && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa779 && i < 0xa77e){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa77e && i < 0xa788 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa77e && i < 0xa788){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xa788){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa789 && i < 0xa78b){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0xa78b || i == 0xa78d){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0xa78c || i == 0xa78e){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xa78f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa790 || i == 0xa792){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0xa791){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa793 && i < 0xa796){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xa796){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa797 && i < 0xa7aa && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa797 && i < 0xa7aa){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7aa && i < 0xa7af){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0xa7af){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7b0 && i < 0xa7b5){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7b5 && i < 0xa7c4 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7b5 && i < 0xa7c4){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7c4 && i < 0xa7c8){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0xa7c8 || i == 0xa7ca){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xa7c9){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7cb && i < 0xa7cd){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7cd && i < 0xa7dd && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7cd && i < 0xa7dd){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7f1 && i < 0xa7f5){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0xa7f5){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0xa7f6){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xa7f7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa7f8 && i < 0xa7fa){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0xa7fa){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7fb && i < 0xa800){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa800 && i <= 0xa82f){
        if(i >= 0xa800 && i < 0xa802){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa802){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa803 && i < 0xa806){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa806){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa807 && i < 0xa80b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa80b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa80c && i < 0xa823){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa823 && i < 0xa825){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa825 && i < 0xa827){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xa827){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa828 && i < 0xa82c){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xa82c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa830 && i <= 0xa83f){
        if(i >= 0xa830 && i < 0xa836){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0xa836 && i < 0xa838){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xa838){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i == 0xa839){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa840 && i <= 0xa87f){
        if(i >= 0xa840 && i < 0xa874){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa874 && i < 0xa878){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa880 && i <= 0xa8df){
        if(i >= 0xa880 && i < 0xa882){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa882 && i < 0xa8b4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa8b4 && i < 0xa8c4){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa8c4 && i < 0xa8c6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa8ce && i < 0xa8d0){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa8d0 && i < 0xa8da){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa8e0 && i <= 0xa8ff){
        if(i >= 0xa8e0 && i < 0xa8f2){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa8f2 && i < 0xa8f8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa8f8 && i < 0xa8fb){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xa8fb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa8fc){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa8fd && i < 0xa8ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa8ff){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa900 && i <= 0xa92f){
        if(i >= 0xa900 && i < 0xa90a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xa90a && i < 0xa926){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa926 && i < 0xa92e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa92e && i < 0xa930){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa930 && i <= 0xa95f){
        if(i >= 0xa930 && i < 0xa947){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa947 && i < 0xa952){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa952 && i < 0xa954){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xa95f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa960 && i <= 0xa97f){
        if(i >= 0xa960 && i < 0xa97d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa980 && i <= 0xa9df){
        if(i >= 0xa980 && i < 0xa983){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xa983){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa984 && i < 0xa9b3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa9b3){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa9b4 && i < 0xa9b6){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa9b6 && i < 0xa9ba){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa9ba && i < 0xa9bc){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa9bc && i < 0xa9be){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xa9be && i < 0xa9c1){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xa9c1 && i < 0xa9ce){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xa9cf){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa9d0 && i < 0xa9da){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xa9de && i < 0xa9e0){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa9e0 && i <= 0xa9ff){
        if(i >= 0xa9e0 && i < 0xa9e5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xa9e5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xa9e6){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xa9e7 && i < 0xa9f0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xa9f0 && i < 0xa9fa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xa9fa && i < 0xa9ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xaa00 && i <= 0xaa5f){
        if(i >= 0xaa00 && i < 0xaa29){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xaa29 && i < 0xaa2f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaa2f && i < 0xaa31){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xaa31 && i < 0xaa33){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaa33 && i < 0xaa35){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xaa35 && i < 0xaa37){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaa40 && i < 0xaa43){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xaa43){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaa44 && i < 0xaa4c){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xaa4c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xaa4d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xaa50 && i < 0xaa5a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xaa5c && i < 0xaa60){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xaa60 && i <= 0xaa7f){
        if(i >= 0xaa60 && i < 0xaa70){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xaa70){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xaa71 && i < 0xaa77){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xaa77 && i < 0xaa7a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0xaa7a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xaa7b || i == 0xaa7d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xaa7c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaa7e && i < 0xaa80){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xaa80 && i <= 0xaadf){
        if(i >= 0xaa80 && i < 0xaab0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xaab0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xaab1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xaab2 && i < 0xaab5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaab5 && i < 0xaab7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xaab7 && i < 0xaab9){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaab9 && i < 0xaabe){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xaabe && i < 0xaac0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0xaac0 || i == 0xaac2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xaac1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaadb && i < 0xaadd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xaadd){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xaade && i < 0xaae0){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xaae0 && i <= 0xaaff){
        if(i >= 0xaae0 && i < 0xaaeb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xaaeb){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xaaec && i < 0xaaee){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xaaee && i < 0xaaf0){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0xaaf0 && i < 0xaaf2){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xaaf2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xaaf3 && i < 0xaaf5){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0xaaf5){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xaaf6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xab00 && i <= 0xab2f){
        if(i >= 0xab01 && i < 0xab07){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xab09 && i < 0xab0f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xab11 && i < 0xab17){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xab20 && i < 0xab27){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xab28 && i < 0xab2f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xab30 && i <= 0xab6f){
        if(i >= 0xab30 && i < 0xab5b){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xab5b){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0xab5c && i < 0xab60){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xab60 && i < 0xab69){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xab69){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xab6a && i < 0xab6c){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xab70 && i <= 0xabbf){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
    if(i >= 0xabc0 && i <= 0xabff){
        if(i >= 0xabc0 && i < 0xabe3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xabe3 && i < 0xabe5){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xabe5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xabe6 && i < 0xabe8){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xabe8){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xabe9 && i < 0xabeb){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xabeb){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xabec){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0xabed){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xabf0 && i < 0xabfa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xac00 && i <= 0xd7af){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0xd7b0 && i <= 0xd7ff){
        if(i >= 0xd7b0 && i < 0xd7c7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xd7cb && i < 0xd7fc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xd800 && i <= 0xdfff){return SGEXTN::ApplicationBase::FullCharacterType::SurrogateCharacter;}
    if(i >= 0xe000 && i <= 0xf8ff){return SGEXTN::ApplicationBase::FullCharacterType::PrivateUseCharacter;}
    if(i >= 0xf900 && i <= 0xfaff){
        if(i >= 0xf900 && i < 0xfa6e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfa70 && i < 0xfada){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfb00 && i <= 0xfb4f){
        if(i >= 0xfb00 && i < 0xfb07){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0xfb13 && i < 0xfb18){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xfb1d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xfb1e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0xfb1f && i < 0xfb29){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xfb29){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0xfb2a && i < 0xfb37){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfb38 && i < 0xfb3d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xfb3e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfb40 && i < 0xfb42){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfb43 && i < 0xfb45){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfb46 && i < 0xfb50){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if((i >= 0xfb50 && i <= 0xfdcf) || (i >= 0xfdf0 && i <= 0xfdff)){
        if(i >= 0xfb50 && i < 0xfbb2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfbb2 && i < 0xfbc3){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0xfbc3 && i < 0xfbd3){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xfbd3 && i < 0xfd3e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xfd3e){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0xfd3f){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0xfd40 && i < 0xfd50){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xfd50 && i < 0xfd90){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfd90 && i < 0xfd92){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xfd92 && i < 0xfdc8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfdc8 && i < 0xfdd0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xfdf0 && i < 0xfdfc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xfdfc){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0xfdfd && i < 0xfe00){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfe00 && i <= 0xfe0f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
    if(i >= 0xfe10 && i <= 0xfe1f){
        if(i >= 0xfe10 && i < 0xfe17){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe17){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0xfe18){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0xfe19){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfe20 && i <= 0xfe2f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
    if(i >= 0xfe30 && i <= 0xfe4f){
        if(i == 0xfe30){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xfe31 && i < 0xfe33){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0xfe33 && i < 0xfe35){return SGEXTN::ApplicationBase::FullCharacterType::ConnectorPunctuation;}
        if(i >= 0xfe35 && i < 0xfe45 && i % 2 == 0){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0xfe35 && i < 0xfe45){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i >= 0xfe45 && i < 0xfe47){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe47){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0xfe48){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0xfe49 && i < 0xfe4d){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xfe4d && i < 0xfe50){return SGEXTN::ApplicationBase::FullCharacterType::ConnectorPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfe50 && i <= 0xfe6f){
        if(i >= 0xfe50 && i < 0xfe53){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xfe54 && i < 0xfe58){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe58){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i == 0xfe59 || i == 0xfe5b || i == 0xfe5d){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0xfe5a || i == 0xfe5c || i == 0xfe5e){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i >= 0xfe5f && i < 0xfe62){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe62){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0xfe63){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0xfe64 && i < 0xfe67){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0xfe68){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe69){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0xfe6a && i < 0xfe6c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfe70 && i <= 0xfeff){
        if(i >= 0xfe70 && i < 0xfe75){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xfe76 && i < 0xfefd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xfeff){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xff00 && i <= 0xffef){
        if(i >= 0xff01 && i < 0xff04){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xff04){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0xff05 && i < 0xff08){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xff08){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0xff09){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0xff0a || i == 0xff0c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xff0b){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0xff0d){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0xff0e && i < 0xff10){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff10 && i < 0xff1a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0xff1a && i < 0xff1c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff1c && i < 0xff1f){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0xff1f && i < 0xff21){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff21 && i < 0xff3b){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0xff3b){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0xff3c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0xff3d){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0xff3e || i == 0xff40){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0xff3f){return SGEXTN::ApplicationBase::FullCharacterType::ConnectorPunctuation;}
        if(i >= 0xff41 && i < 0xff5b){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0xff5b){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0xff5c || i == 0xff5e){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0xff5d){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0xff5f || i == 0xff62){return SGEXTN::ApplicationBase::FullCharacterType::OpeningPunctuation;}
        if(i == 0xff60 || i == 0xff63){return SGEXTN::ApplicationBase::FullCharacterType::ClosingPunctuation;}
        if(i == 0xff61){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff64 && i < 0xff66){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff66 && i < 0xff70){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0xff70){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xff71 && i < 0xff9e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xff9e && i < 0xffa0){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0xffa0 && i < 0xffbf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xffc2 && i < 0xffc8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xffca && i < 0xffd0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xffd2 && i < 0xffd8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xffda && i < 0xffdd){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0xffe0 && i < 0xffe2){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i == 0xffe2){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i == 0xffe3){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i == 0xffe4){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xffe5 && i < 0xffe7){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i == 0xffe8){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0xffe9 && i < 0xffed){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0xffed && i < 0xffef){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfff0 && i <= 0xffff){
        if(i >= 0xfff9 && i < 0xfffc){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0xfffc && i < 0xfffe){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10000 && i <= 0x1007f){
        if(i >= 0x10000 && i < 0x1000c){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1000d && i < 0x10027){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10028 && i < 0x1003b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1003c && i < 0x1003e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1003f && i < 0x1004e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10050 && i < 0x1005e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10080 && i <= 0x100ff){
        if(i >= 0x10080 && i < 0x100fb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10100 && i <= 0x1013f){
        if(i >= 0x10100 && i < 0x10103){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x10107 && i < 0x10134){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x10137 && i < 0x10140){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10140 && i <= 0x1018f){
        if(i >= 0x10140 && i < 0x10175){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i >= 0x10175 && i < 0x10179){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x10179 && i < 0x1018a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1018a && i < 0x1018c){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x1018c && i < 0x1018f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10190 && i <= 0x101cf){
        if(i >= 0x10190 && i < 0x1019d){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x101a0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x101d0 && i <= 0x101ff){
        if(i >= 0x101d0 && i < 0x101fd){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x101fd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10280 && i <= 0x1029f){
        if(i >= 0x10280 && i < 0x1029d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x102a0 && i <= 0x102df){
        if(i >= 0x102a0 && i < 0x102d1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x102e0 && i <= 0x102ff){
        if(i == 0x102e0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x102e1 && i < 0x102fc){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10300 && i <= 0x1032f){
        if(i >= 0x10300 && i < 0x10320){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10320 && i < 0x10324){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x1032d && i < 0x10330){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10330 && i <= 0x1034f){
        if(i >= 0x10330 && i < 0x10341){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x10341){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i >= 0x10342 && i < 0x1034a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1034a){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10350 && i <= 0x1037f){
        if(i >= 0x10350 && i < 0x10376){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10376 && i < 0x1037b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10380 && i <= 0x1039f){
        if(i >= 0x10380 && i < 0x1039e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1039f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x103a0 && i <= 0x103df){
        if(i >= 0x103a0 && i < 0x103c4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x103c8 && i < 0x103d0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x103d0){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x103d1 && i < 0x103d6){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10400 && i <= 0x1044f){
        if(i >= 0x10400 && i < 0x10428){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10428 && i < 0x10450){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10450 && i <= 0x1047f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x10480 && i <= 0x104af){
        if(i >= 0x10480 && i < 0x1049e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x104a0 && i < 0x104aa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x104b0 && i <= 0x104ff){
        if(i >= 0x104b0 && i < 0x104d4){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x104d8 && i < 0x104fc){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10500 && i <= 0x1052f){
        if(i >= 0x10500 && i < 0x10528){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10530 && i <= 0x1056f){
        if(i >= 0x10530 && i < 0x10564){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1056f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10570 && i <= 0x105bf){
        if(i >= 0x10570 && i < 0x1057b){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1057c && i < 0x1058b){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1058c && i < 0x10593){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10594 && i < 0x10596){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10597 && i < 0x105a2){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x105a3 && i < 0x105b2){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x105b3 && i < 0x105ba){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x105bb && i < 0x105bd){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x105c0 && i <= 0x105ff){
        if(i >= 0x105c0 && i < 0x105f4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10600 && i <= 0x1077f){
        if(i >= 0x10600 && i < 0x10737){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10740 && i < 0x10756){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10760 && i < 0x10768){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10780 && i <= 0x107bf){
        if(i >= 0x10780 && i < 0x10786){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x10787 && i < 0x107b1){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x107b2 && i < 0x107bb){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10800 && i <= 0x1083f){
        if(i >= 0x10800 && i < 0x10806){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x10808){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1080a && i < 0x10836){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10837 && i < 0x10839){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1083c || i == 0x1083f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10840 && i <= 0x1085f){
        if(i >= 0x10840 && i < 0x10856){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x10857){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x10858 && i < 0x10860){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10860 && i <= 0x1087f){
        if(i >= 0x10860 && i < 0x10877){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10877 && i < 0x10879){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x10879 && i < 0x10880){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10880 && i <= 0x108af){
        if(i >= 0x10880 && i < 0x1089f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x108a7 && i < 0x108b0){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x108e0 && i <= 0x108ff){
        if(i >= 0x108e0 && i < 0x108f3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x108f4 && i < 0x108f6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x108fb && i < 0x10900){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10900 && i <= 0x1091f){
        if(i >= 0x10900 && i < 0x10916){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10916 && i < 0x1091c){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x1091f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10920 && i <= 0x1093f){
        if(i >= 0x10920 && i < 0x1093a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1093f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10940 && i <= 0x1095f){
        if(i >= 0x10940 && i < 0x1095a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10980 && i <= 0x1099f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x109a0 && i <= 0x109ff){
        if(i >= 0x109a0 && i < 0x109b8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x109bc && i < 0x109be){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x109be && i < 0x109c0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x109c0 && i < 0x109d0){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x109d2 && i < 0x10a00){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10a00 && i <= 0x10a5f){
        if(i == 0x10a00){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10a01 && i < 0x10a04){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x10a05 && i < 0x10a07){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x10a0c && i < 0x10a10){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x10a10 && i < 0x10a14){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10a15 && i < 0x10a18){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10a19 && i < 0x10a36){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10a38 && i < 0x10a3b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x10a3f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x10a40 && i < 0x10a49){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x10a50 && i < 0x10a59){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10a60 && i <= 0x10a7f){
        if(i >= 0x10a60 && i < 0x10a7d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10a7d && i < 0x10a7f){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x10a7f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
    }
    if(i >= 0x10a80 && i <= 0x10a9f){
        if(i >= 0x10a80 && i < 0x10a9d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10a9d && i < 0x10aa0){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10ac0 && i <= 0x10aff){
        if(i >= 0x10ac0 && i < 0x10ac8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x10ac8){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x10ac9 && i < 0x10ae5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10ae5 && i < 0x10ae7){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x10aeb && i < 0x10af0){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x10af0 && i < 0x10af7){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10b00 && i <= 0x10b3f){
        if(i >= 0x10b00 && i < 0x10b36){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10b39 && i < 0x10b40){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10b40 && i <= 0x10b5f){
        if(i >= 0x10b40 && i < 0x10b56){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10b58 && i < 0x10b60){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10b60 && i <= 0x10b7f){
        if(i >= 0x10b60 && i < 0x10b73){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10b78 && i < 0x10b80){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10b80 && i <= 0x10baf){
        if(i >= 0x10b80 && i < 0x10b92){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10b99 && i < 0x10b9d){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x10ba9 && i < 0x10bb0){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10c00 && i <= 0x10c4f){
        if(i >= 0x10c00 && i < 0x10c49){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10c80 && i <= 0x10cff){
        if(i >= 0x10c80 && i < 0x10cb3){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10cc0 && i < 0x10cf3){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x10cfa && i < 0x10d00){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10d00 && i <= 0x10d3f){
        if(i >= 0x10d00 && i < 0x10d24){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10d24 && i < 0x10d28){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x10d30 && i < 0x10d3a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10d40 && i <= 0x10d8f){
        if(i >= 0x10d40 && i < 0x10d4a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x10d4a && i < 0x10d4e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x10d4e){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x10d4f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10d50 && i < 0x10d66){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10d69 && i < 0x10d6e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x10d6e){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i == 0x10d6f){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x10d70 && i < 0x10d86){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x10d8e && i < 0x10d90){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10e60 && i <= 0x10e7f){
        if(i >= 0x10e60 && i < 0x10e7f){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10e80 && i <= 0x10ebf){
        if(i >= 0x10e80 && i < 0x10eaa){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10eab && i < 0x10ead){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x10ead){return SGEXTN::ApplicationBase::FullCharacterType::DashPunctuation;}
        if(i >= 0x10eb0 && i < 0x10eb2){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10ec0 && i <= 0x10eff){
        if(i >= 0x10ec2 && i < 0x10ec5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x10ec5){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x10ec6 && i < 0x10ec8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x10ed0){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x10ed1 && i < 0x10ed9){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x10efa && i < 0x10f00){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10f00 && i <= 0x10f2f){
        if(i >= 0x10f00 && i < 0x10f1d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10f1d && i < 0x10f27){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x10f27){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10f30 && i <= 0x10f6f){
        if(i >= 0x10f30 && i < 0x10f46){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10f46 && i < 0x10f51){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x10f51 && i < 0x10f55){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x10f55 && i < 0x10f5a){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10f70 && i <= 0x10faf){
        if(i >= 0x10f70 && i < 0x10f82){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10f82 && i < 0x10f86){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x10f86 && i < 0x10f8a){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10fb0 && i <= 0x10fdf){
        if(i >= 0x10fb0 && i < 0x10fc5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x10fc5 && i < 0x10fcc){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10fe0 && i <= 0x10fff){
        if(i >= 0x10fe0 && i < 0x10ff7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11000 && i <= 0x1107f){
        if(i == 0x11000 || i == 0x11002){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11001){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11003 && i < 0x11038){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11038 && i < 0x11047){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11047 && i < 0x1104e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11052 && i < 0x11066){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x11066 && i < 0x11070){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x11070){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11071 && i < 0x11073){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11073 && i < 0x11075){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11075){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1107f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11080 && i <= 0x110cf){
        if(i >= 0x11080 && i < 0x11082){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11082){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11083 && i < 0x110b0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x110b0 && i < 0x110b3){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x110b3 && i < 0x110b7){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x110b7 && i < 0x110b9){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x110b9 && i < 0x110bb){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x110bb && i < 0x110bd){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x110bd){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0x110be && i < 0x110c2){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x110c2){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x110cd){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x110d0 && i <= 0x110ff){
        if(i >= 0x110d0 && i < 0x110e9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x110f0 && i < 0x110fa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11100 && i <= 0x1114f){
        if(i >= 0x11100 && i < 0x11103){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11103 && i < 0x11127){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11127 && i < 0x1112c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1112c){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1112d && i < 0x11135){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11136 && i < 0x11140){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x11140 && i < 0x11144){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x11144 || i == 0x11147){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11145 && i < 0x11147){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11150 && i <= 0x1117f){
        if(i >= 0x11150 && i < 0x11173){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11173){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11174 && i < 0x11176){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x11176){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11180 && i <= 0x111df){
        if(i >= 0x11180 && i < 0x11182){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11182){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11183 && i < 0x111b3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x111b3 && i < 0x111b6){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x111b6 && i < 0x111bf){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x111bf && i < 0x111c1){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x111c1 && i < 0x111c5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x111c5 && i < 0x111c9){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x111c9 && i < 0x111cd){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x111cd){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x111ce){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x111cf){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x111d0 && i < 0x111da){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x111da || i == 0x111dc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x111db){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x111dd && i < 0x111e0){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x111e0 && i <= 0x111ff){
        if(i >= 0x111e1 && i < 0x111f5){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11200 && i <= 0x1124f){
        if(i >= 0x11200 && i < 0x11212){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11213 && i < 0x1122c){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1122c && i < 0x1122f){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1122f && i < 0x11232){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11232 && i < 0x11234){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11234){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11235){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11236 && i < 0x11238){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11238 && i < 0x1123e){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x1123e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1123f && i < 0x11241){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11241){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11280 && i <= 0x112af){
        if(i >= 0x11280 && i < 0x11287){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11288){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1128a && i < 0x1128e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1128f && i < 0x1129e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1129f && i < 0x112a9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x112a9){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x112b0 && i <= 0x112ff){
        if(i >= 0x112b0 && i < 0x112df){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x112df){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x112e0 && i < 0x112e3){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x112e3 && i < 0x112eb){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x112f0 && i < 0x112fa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11300 && i <= 0x1137f){
        if(i >= 0x11300 && i < 0x11302){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11302 && i < 0x11304){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11305 && i < 0x1130d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1130f && i < 0x11311){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11313 && i < 0x11329){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1132a && i < 0x11331){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11332 && i < 0x11334){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11335 && i < 0x1133a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1133b && i < 0x1133d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1133d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1133e && i < 0x11340){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11340){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11341 && i < 0x11345){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11347 && i < 0x11349){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1134b && i < 0x1134e){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11350){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11357){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1135d && i < 0x11362){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11362 && i < 0x11364){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11366 && i < 0x1136d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11370 && i < 0x11375){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11380 && i <= 0x113ff){
        if(i >= 0x11380 && i < 0x1138a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1138b || i == 0x1138e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11390 && i < 0x113b6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x113b7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x113b8 && i < 0x113bb){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x113bb && i < 0x113c1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x113c2 || i == 0x113c5){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x113c7 && i < 0x113cb){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x113cc && i < 0x113ce){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x113ce || i == 0x113d0 || i == 0x113d2){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x113cf){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x113d1 || i == 0x113d3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x113d4 && i < 0x113d6){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x113d7 && i < 0x113d9){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x113e1 && i < 0x113e3){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11400 && i <= 0x1147f){
        if(i >= 0x11400 && i < 0x11435){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11435 && i < 0x11438){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11438 && i < 0x11440){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11440 && i < 0x11442){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11442 && i < 0x11445){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11445){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11446){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11447 && i < 0x1144b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1144b && i < 0x11450){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11450 && i < 0x1145a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1145a && i < 0x1145c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x1145d){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x1145e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1145f && i < 0x11462){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11480 && i <= 0x114df){
        if(i >= 0x11480 && i < 0x114b0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x114b0 && i < 0x114b3){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x114b3 && i < 0x114b9){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x114b9){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x114ba){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x114bb && i < 0x114bf){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x114bf && i < 0x114c1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x114c1){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x114c2 && i < 0x114c4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x114c4 && i < 0x114c6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x114c6){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x114c7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x114d0 && i < 0x114da){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11580 && i <= 0x115ff){
        if(i >= 0x11580 && i < 0x115af){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x115af && i < 0x115b2){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x115b2 && i < 0x115b6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x115b8 && i < 0x115bc){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x115bc && i < 0x115be){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x115be){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x115bf && i < 0x115c1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x115c1 && i < 0x115d8){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x115d8 && i < 0x115dc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x115dc && i < 0x115de){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11600 && i <= 0x1165f){
        if(i >= 0x11600 && i < 0x11630){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11630 && i < 0x11633){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11633 && i < 0x1163b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1163b && i < 0x1163d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x1163d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1163e){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1163f && i < 0x11641){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11641 && i < 0x11644){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x11644){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11650 && i < 0x1165a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11660 && i <= 0x1167f){
        if(i >= 0x11660 && i < 0x1166d){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11680 && i <= 0x116cf){
        if(i >= 0x11680 && i < 0x116ab){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x116ab || i == 0x116ad){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x116ac){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x116ae && i < 0x116b0){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x116b0 && i < 0x116b6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x116b6){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x116b7){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x116b8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x116b9){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x116c0 && i < 0x116ca){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x116d0 && i <= 0x116ff){
        if(i >= 0x116d0 && i < 0x116e4){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11700 && i <= 0x1174f){
        if(i >= 0x11700 && i < 0x1171b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1171d || i == 0x1171f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1171e){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11720 && i < 0x11722){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11722 && i < 0x11726){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11726){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11727 && i < 0x1172c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11730 && i < 0x1173a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1173a && i < 0x1173c){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x1173c && i < 0x1173f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x1173f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x11740 && i < 0x11747){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11800 && i <= 0x1184f){
        if(i >= 0x11800 && i < 0x1182c){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1182c && i < 0x1182f){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1182f && i < 0x11838){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11838){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11839 && i < 0x1183b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1183b){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x118a0 && i <= 0x118ff){
        if(i >= 0x118a0 && i < 0x118c0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x118c0 && i < 0x118e0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x118e0 && i < 0x118ea){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x118ea && i < 0x118f3){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x118ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11900 && i <= 0x1195f){
        if(i >= 0x11900 && i < 0x11907){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11909){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1190c && i < 0x11914){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11915 && i < 0x11917){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11918 && i < 0x11930){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11930 && i < 0x11936){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11937 && i < 0x11939){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1193b && i < 0x1193d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1193d || i == 0x11940 || i == 0x11942){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x1193e || i == 0x11943){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1193f || i == 0x11941){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11944 && i < 0x11947){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11950 && i < 0x1195a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x119a0 && i <= 0x119ff){
        if(i >= 0x119a0 && i < 0x119a8){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x119aa && i < 0x119d1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x119d1 && i < 0x119d4){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x119d4 && i < 0x119d8){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x119da && i < 0x119dc){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x119dc && i < 0x119e0){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x119e0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x119e1 || i == 0x119e3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x119e2){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x119e4){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11a00 && i <= 0x11a4f){
        if(i == 0x11a00){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11a01 && i < 0x11a0b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11a0b && i < 0x11a33){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11a33 && i < 0x11a39){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11a39){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11a3a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11a3b && i < 0x11a3f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11a3f && i < 0x11a47){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x11a47){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11a50 && i <= 0x11aaf){
        if(i == 0x11a50){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11a51 && i < 0x11a57){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11a57 && i < 0x11a59){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11a59 && i < 0x11a5c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11a5c && i < 0x11a8a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11a8a && i < 0x11a97){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11a97){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11a98 && i < 0x11a9a){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11a9a && i < 0x11a9d){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x11a9d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11a9e && i < 0x11aa3){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11ab0 && i <= 0x11abf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x11ac0 && i <= 0x11aff){
        if(i >= 0x11ac0 && i < 0x11af9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11b00 && i <= 0x11b5f){
        if(i >= 0x11b00 && i < 0x11b0a){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11b60 && i <= 0x11b7f){
        if(i == 0x11b60){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11b61){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11b62 && i < 0x11b65){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11b65 || i == 0x11b67){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11b66){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11bc0 && i <= 0x11bff){
        if(i >= 0x11bc0 && i < 0x11be1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11be1){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11bf0 && i < 0x11bfa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11c00 && i <= 0x11c6f){
        if(i >= 0x11c00 && i < 0x11c09){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11c0a && i < 0x11c2f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11c2f){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11c30 && i < 0x11c37){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11c38 && i < 0x11c3e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11c3e){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11c3f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11c40){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11c41 && i < 0x11c46){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11c50 && i < 0x11c5a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x11c5a && i < 0x11c6d){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11c70 && i <= 0x11cbf){
        if(i >= 0x11c70 && i < 0x11c72){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11c72 && i < 0x11c90){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11c92 && i < 0x11ca8){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11ca9){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11caa && i < 0x11cb1){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11cb1){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11cb2 && i < 0x11cb4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11cb4){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11cb5 && i < 0x11cb7){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11d00 && i <= 0x11d5f){
        if(i >= 0x11d00 && i < 0x11d07){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11d08 && i < 0x11d0a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11d0b && i < 0x11d31){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11d31 && i < 0x11d37){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11d3a){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11d3c && i < 0x11d3e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11d3f && i < 0x11d46){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11d46){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11d47){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11d50 && i < 0x11d5a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11d60 && i <= 0x11daf){
        if(i >= 0x11d60 && i < 0x11d66){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11d67 && i < 0x11d69){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11d6a && i < 0x11d8a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11d8a && i < 0x11d8f){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11d90 && i < 0x11d92){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11d93 && i < 0x11d95){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11d95 || i == 0x11d97){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11d96){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11d98){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11da0 && i < 0x11daa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11db0 && i <= 0x11def){
        if(i >= 0x11db0 && i < 0x11dd9){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11dd9){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x11dda && i < 0x11ddc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11de0 && i < 0x11dea){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        {return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x11ee0 && i <= 0x11eff){
        if(i >= 0x11ee0 && i < 0x11ef3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11ef3 && i < 0x11ef5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11ef5 && i < 0x11ef7){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11ef7 && i < 0x11ef9){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11f00 && i <= 0x11f5f){
        if(i >= 0x11f00 && i < 0x11f02){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11f02){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x11f03){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11f04 && i < 0x11f11){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11f12 && i < 0x11f34){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x11f34 && i < 0x11f36){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11f36 && i < 0x11f3b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x11f3e && i < 0x11f40){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i == 0x11f40 || i == 0x11f42){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x11f41){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x11f43 && i < 0x11f50){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11f50 && i < 0x11f5a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x11f5a){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11fb0 && i <= 0x11fbf){
        if(i == 0x11fb0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11fc0 && i <= 0x11fff){
        if(i >= 0x11fc0 && i < 0x11fd5){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x11fd5 && i < 0x11fdd){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x11fdd && i < 0x11fe1){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0x11fe1 && i < 0x11ff2){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x11fff){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x12000 && i <= 0x123ff){
        if(i >= 0x12000 && i < 0x1239a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        {return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x12400 && i <= 0x1247f){
        if(i >= 0x12400 && i < 0x1246f){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        if(i >= 0x12470 && i < 0x12475){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x12480 && i <= 0x1254f){
        if(i >= 0x12480 && i < 0x12544){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x12f90 && i <= 0x12fff){
        if(i >= 0x12f90 && i < 0x12ff1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x12ff1 && i < 0x12ff3){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x13000 && i <= 0x1342f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x13430 && i <= 0x1345f){
        if(i >= 0x13430 && i < 0x13440){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i == 0x13440){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x13441 && i < 0x13447){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x13447 && i < 0x13456){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x13460 && i <= 0x143ff){
        if(i >= 0x13460 && i < 0x143fb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x14400 && i <= 0x1467f){
        if(i >= 0x14400 && i < 0x14647){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16100 && i <= 0x1613f){
        if(i >= 0x16100 && i < 0x1611e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1611e && i < 0x1612a){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1612a && i < 0x1612d){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1612d && i < 0x16130){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x16130 && i < 0x1613a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16800 && i <= 0x16a3f){
        if(i >= 0x16800 && i < 0x16a39){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        {return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x16a40 && i <= 0x16a6f){
        if(i >= 0x16a40 && i < 0x16a5f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x16a60 && i < 0x16a6a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x16a6e && i < 0x16b00){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16a70 && i <= 0x16acf){
        if(i >= 0x16a70 && i < 0x16abf){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x16ac0 && i < 0x16aca){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16ad0 && i <= 0x16aff){
        if(i >= 0x16ad0 && i < 0x16aee){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x16af0 && i < 0x16af5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x16af5){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16b00 && i <= 0x16b8f){
        if(i >= 0x16b00 && i < 0x16b30){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x16b30 && i < 0x16b37){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x16b37 && i < 0x16b3c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x16b3c && i < 0x16b40){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x16b40 && i < 0x16b44){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x16b44){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x16b45){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x16b50 && i < 0x16b5a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x16b5b && i < 0x16b62){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x16b63 && i < 0x16b78){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x16b7d && i < 0x16b90){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16d40 && i <= 0x16d7f){
        if(i >= 0x16d40 && i < 0x16d43){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x16d43 && i < 0x16d6b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x16b6b && i < 0x16d6d){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x16b6d && i < 0x16d70){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x16d70 && i < 0x16d7a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16e40 && i <= 0x16e9f){
        if(i >= 0x16e40 && i < 0x16e60){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x16e40 && i < 0x16e80){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x16e80 && i < 0x16e97){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x16e97 && i < 0x16e9b){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16ea0 && i <= 0x16edf){
        if(i >= 0x16ea0 && i < 0x16eb9){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x16ebb && i < 0x16ed4){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        {return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x16f00 && i <= 0x16f9f){
        if(i >= 0x16f00 && i < 0x16f4b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x16f4f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x16f50){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x16f51 && i < 0x16f88){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x16f8f && i < 0x16f93){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x16f93 && i < 0x16fa0){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16fe0 && i <= 0x16fff){
        if(i >= 0x16fe0 && i < 0x16fe2){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x16fe2){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i == 0x16fe3){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x16fe4){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x16ff0 && i < 0x16ff2){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x16ff2 && i < 0x16ff4){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x16ff4 && i < 0x16ff7){return SGEXTN::ApplicationBase::FullCharacterType::LetterNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x17000 && i <= 0x187ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x18800 && i <= 0x18aff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x18b00 && i <= 0x18cff){
        if(i >= 0x18b00 && i < 0x18cd6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x18cff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x18d00 && i <= 0x18d7f){
        if(i >= 0x18d00 && i < 0x18d1f){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x18d80 && i <= 0x18dff){
        if(i >= 0x18d80 && i < 0x18df3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1aff0 && i <= 0x1afff){
        if(i >= 0x1aff0 && i < 0x1aff4){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1aff5 && i < 0x1affc){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1affd && i < 0x1afff){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b000 && i <= 0x1b0ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
    if(i >= 0x1b100 && i <= 0x1b12f){
        if(i >= 0x1b100 && i < 0x1b123){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b130 && i <= 0x1b16f){
        if(i == 0x1b132){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1b150 && i < 0x1b153){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1b155){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1b164 && i < 0x1b168){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b170 && i <= 0x1b2ff){
        if(i >= 0x1b170 && i < 0x1b2fc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1bc00 && i <= 0x1bc9f){
        if(i >= 0x1bc00 && i < 0x1bc6b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1bc70 && i < 0x1bc7d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1bc80 && i < 0x1bc89){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1bc90 && i < 0x1bc9a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1bc9c){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1bc9d && i < 0x1bc9f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1bc9f){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1bca0 && i <= 0x1bcaf){
        if(i >= 0x1bca0 && i < 0x1bca4){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cc00 && i <= 0x1cebf){
        if(i >= 0x1cc00 && i < 0x1ccf0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1ccf0 && i < 0x1ccfa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1ccfa && i < 0x1ccfd){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1cd00 && i < 0x1ceb4){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1ceba && i < 0x1cec0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cec0 && i <= 0x1ceff){
        if(i >= 0x1cec0 && i < 0x1ced1){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1cee0 && i < 0x1cef0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x1cef0){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cf00 && i <= 0x1cfcf){
        if(i >= 0x1cf00 && i < 0x1cf2e){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1cf30 && i < 0x1cf47){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1cf50 && i < 0x1cfc4){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d000 && i <= 0x1d0ff){
        if(i >= 0x1d000 && i < 0x1d0f6){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d100 && i <= 0x1d1ff){
        if(i >= 0x1d100 && i < 0x1d127){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d129 && i < 0x1d165){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d165 && i < 0x1d167){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1d167 && i < 0x1d16a){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1d16a && i < 0x1d16d){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d16d && i < 0x1d173){return SGEXTN::ApplicationBase::FullCharacterType::CombiningMark;}
        if(i >= 0x1d173 && i < 0x1d17b){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0x1d17b && i < 0x1d183){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1d183 && i < 0x1d185){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d185 && i < 0x1d18c){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1d18c && i < 0x1d1aa){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d1aa && i < 0x1d1ae){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1d1ae && i < 0x1d1eb){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d200 && i <= 0x1d24f){
        if(i >= 0x1d200 && i < 0x1d242){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d242 && i < 0x1d245){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1d245){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d2c0 && i <= 0x1d2df){
        if(i >= 0x1d2c0 && i < 0x1d2d4){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d2e0 && i <= 0x1d2ff){
        if(i >= 0x1d2e0 && i < 0x1d2f4){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d300 && i <= 0x1d35f){
        if(i >= 0x1d300 && i < 0x1d357){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d360 && i <= 0x1d37f){
        if(i >= 0x1d360 && i < 0x1d379){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d400 && i <= 0x1d7ff){
        if(i >= 0x1d400 && i < 0x1d41a){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d41a && i < 0x1d434){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d434 && i < 0x1d44e){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d44e && i < 0x1d455){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d456 && i < 0x1d468){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d468 && i < 0x1d482){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d482 && i < 0x1d49c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d49c){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d49e && i < 0x1d4a0){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d4a2){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4a5 && i < 0x1d4a7){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4a9 && i < 0x1d4ad){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4ae && i < 0x1d4b6){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4b6 && i < 0x1d4ba){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d4bb){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d4bd && i < 0x1d4c4){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d4c5 && i < 0x1d4d0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d4d0 && i < 0x1d4ea){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4ea && i < 0x1d504){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d504 && i < 0x1d506){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d507 && i < 0x1d50b){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d50d && i < 0x1d515){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d516 && i < 0x1d51d){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d51e && i < 0x1d538){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d538 && i < 0x1d53a){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d53b && i < 0x1d53f){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d540 && i < 0x1d545){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d546){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d54a && i < 0x1d551){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d552 && i < 0x1d56c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d56c && i < 0x1d586){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d586 && i < 0x1d5a0){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d5a0 && i < 0x1d5ba){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d5ba && i < 0x1d5d4){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d5d4 && i < 0x1d5ee){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d5ee && i < 0x1d608){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d608 && i < 0x1d622){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d622 && i < 0x1d63c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d63c && i < 0x1d656){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d656 && i < 0x1d670){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d670 && i < 0x1d68a){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d68a && i < 0x1d6a6){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d6a8 && i < 0x1d6c1){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d6c1){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d6c2 && i < 0x1d6db){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d6db){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d6dc && i < 0x1d6e2){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d6e2 && i < 0x1d6fb){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d6fb){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d6fc && i < 0x1d715){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d715){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d716 && i < 0x1d71c){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d71c && i < 0x1d735){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d735){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d736 && i < 0x1d74f){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d74f){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d750 && i < 0x1d756){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d756 && i < 0x1d76f){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d76f){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d770 && i < 0x1d789){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d789){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d78a && i < 0x1d790){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d790 && i < 0x1d7a9){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d7a9){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d7aa && i < 0x1d7c3){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d7c3){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        if(i >= 0x1d7c4 && i < 0x1d7ca){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d7ca){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d7cb){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d7ce && i < 0x1d800){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d800 && i <= 0x1daaf){
        if(i >= 0x1d800 && i < 0x1da00){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1da00 && i < 0x1da37){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1da37 && i < 0x1da3b){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1da3b && i < 0x1da6d){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1da6d && i < 0x1da75){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x1da75){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1da76 && i < 0x1da84){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x1da84){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1da85 && i < 0x1da87){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1da87 && i < 0x1da8c){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1da9b && i < 0x1daa0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1daa1 && i < 0x1dab0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1df00 && i <= 0x1dfff){
        if(i >= 0x1df00 && i < 0x1df0a){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i == 0x1df0a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1df0b && i < 0x1df1f){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1df25 && i < 0x1df2b){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e000 && i <= 0x1e02f){
        if(i >= 0x1e000 && i < 0x1e007){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e008 && i < 0x1e019){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e01b && i < 0x1e022){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e023 && i < 0x1e025){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e026 && i < 0x1e02b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e030 && i <= 0x1e08f){
        if(i >= 0x1e030 && i < 0x1e06e){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i == 0x1e08f){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e100 && i <= 0x1e14f){
        if(i >= 0x1e100 && i < 0x1e12d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e130 && i < 0x1e137){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e137 && i < 0x1e13e){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1e140 && i < 0x1e14a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x1e14e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1e14f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e290 && i <= 0x1e2bf){
        if(i >= 0x1e290 && i < 0x1e2ae){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1e2ae){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e2c0 && i <= 0x1e2ff){
        if(i >= 0x1e2c0 && i < 0x1e2ec){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e2ec && i < 0x1e2f0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e2f0 && i < 0x1e2fa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x1e2ff){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e4d0 && i <= 0x1e4ff){
        if(i >= 0x1e4d0 && i < 0x1e4eb){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1e4eb){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1e4ec && i < 0x1e4f0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e4f0 && i < 0x1e4fa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e5d0 && i <= 0x1e5ff){
        if(i >= 0x1e5d0 && i < 0x1e5ee){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e5ee && i < 0x1e5f0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1e5f0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e5f1 && i < 0x1e5fb){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x1e5ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e6c0 && i <= 0x1e6ff){
        if(i >= 0x1e6c0 && i < 0x1e6df){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e6e0 && i < 0x1e6e3){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1e6e3){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e6e4 && i < 0x1e6e6){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1e6e6){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e6e7 && i < 0x1e6ee){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e6ee && i < 0x1e6f0){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i >= 0x1e6f0 && i < 0x1e6f5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1e6f5){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1e6fe){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1e6ff){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e7e0 && i <= 0x1e7ff){
        if(i >= 0x1e7e0 && i < 0x1e7e7){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e7e8 && i < 0x1e7ec){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e7ed && i < 0x1e7ef){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e7f0 && i < 0x1e7ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e800 && i <= 0x1e8df){
        if(i >= 0x1e800 && i < 0x1e8c5){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1e8c7 && i < 0x1e8d0){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x1e8d0 && i < 0x1e8d7){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e900 && i <= 0x1e95f){
        if(i >= 0x1e900 && i < 0x1e922){return SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1e922 && i < 0x1e944){return SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1e944 && i < 0x1e94b){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
        if(i == 0x1e94b){return SGEXTN::ApplicationBase::FullCharacterType::ModifierLetter;}
        if(i >= 0x1e950 && i < 0x1e95a){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i >= 0x1e95e && i < 0x1e960){return SGEXTN::ApplicationBase::FullCharacterType::OtherPunctuation;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1ec70 && i <= 0x1ecbf){
        if(i >= 0x1ec71 && i < 0x1ecac){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x1ecac){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1ecad && i < 0x1ecb0){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x1ecb0){return SGEXTN::ApplicationBase::FullCharacterType::CurrencySymbol;}
        if(i >= 0x1ecb1 && i < 0x1ecb5){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1ed00 && i <= 0x1ed4f){
        if(i >= 0x1ed01 && i < 0x1ed2e){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i == 0x1ed2e){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1ed2f && i < 0x1ed3e){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1ee00 && i <= 0x1eeff){
        if(i >= 0x1ee00 && i < 0x1ee04){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee05 && i < 0x1ee20){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee21 && i < 0x1ee23){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1ee24 || i == 0x1ee27){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee29 && i < 0x1ee33){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee34 && i < 0x1ee38){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1ee39 || i == 0x1ee3b || i == 0x1ee42 || i == 0x1ee47 || i == 0x1ee49 || i == 0x1ee4b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee4d && i < 0x1ee50){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee51 && i < 0x1ee53){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1ee54){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee57 && i < 0x1ee60 && i % 2 == 1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee61 && i < 0x1ee63){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1ee64){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee67 && i < 0x1ee6b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee6c && i < 0x1ee73){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee74 && i < 0x1ee78){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee79 && i < 0x1ee7d){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i == 0x1ee7e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee80 && i < 0x1ee8a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee8b && i < 0x1ee9c){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1eea1 && i < 0x1eea4){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1eea5 && i < 0x1eeaa){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1eeab && i < 0x1eebc){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x1eef0 && i < 0x1eef2){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f000 && i <= 0x1f02f){
        if(i >= 0x1f000 && i < 0x1f02c){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f030 && i <= 0x1f09f){
        if(i >= 0x1f030 && i < 0x1f094){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f0a0 && i <= 0x1f0ff){
        if(i >= 0x1f0a0 && i < 0x1f0af){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f0b1 && i < 0x1f0c0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f0c1 && i < 0x1f0d0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f0d1 && i < 0x1f0f6){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f100 && i <= 0x1f1ff){
        if(i >= 0x1f100 && i < 0x1f10d){return SGEXTN::ApplicationBase::FullCharacterType::OtherNumber;}
        if(i >= 0x1f10d && i < 0x1f1ae){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f1e6 && i < 0x1f200){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f200 && i <= 0x1f2ff){
        if(i >= 0x1f200 && i < 0x1f203){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f210 && i < 0x1f23c){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f240 && i < 0x1f249){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f250 && i < 0x1f252){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f260 && i < 0x1f266){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f300 && i <= 0x1f5ff){
        if(i >= 0x1f300 && i < 0x1f3fb){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f3fb && i < 0x1f400){return SGEXTN::ApplicationBase::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1f400 && i < 0x1f600){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        {return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x1f600 && i <= 0x1f64f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x1f650 && i <= 0x1f67f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x1f680 && i <= 0x1f6ff){
        if(i >= 0x1f680 && i < 0x1f6d9){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f6dc && i < 0x1f6ed){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f6f0 && i < 0x1f6fd){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f700 && i <= 0x1f77f){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x1f780 && i <= 0x1f7ff){
        if(i >= 0x1f780 && i < 0x1f7da){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f7e0 && i < 0x1f7ec){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x1f7f0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f800 && i <= 0x1f8ff){
        if(i >= 0x1f800 && i < 0x1f80c){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f810 && i < 0x1f848){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f850 && i < 0x1f85a){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f860 && i < 0x1f888){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f890 && i < 0x1f8ae){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f8b0 && i < 0x1f8bc){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f8c0 && i < 0x1f8c2){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f8d0 && i < 0x1f8d9){return SGEXTN::ApplicationBase::FullCharacterType::MathSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f900 && i <= 0x1f9ff){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
    if(i >= 0x1fa00 && i <= 0x1fa6f){
        if(i >= 0x1fa00 && i < 0x1fa58){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fa60 && i < 0x1fa6e){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1fa70 && i <= 0x1faff){
        if(i >= 0x1fa70 && i < 0x1fa7d){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fa80 && i < 0x1fa8b){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fa8e && i < 0x1fac7){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i == 0x1fac8){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1facd && i < 0x1fadd){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fadf && i < 0x1faeb){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1faef && i < 0x1faf9){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1fb00 && i <= 0x1fbff){
        if(i >= 0x1fb00 && i < 0x1fb93){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fb94 && i < 0x1fbf0){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fbf0 && i < 0x1fbfa){return SGEXTN::ApplicationBase::FullCharacterType::NumericalDigit;}
        if(i == 0x1fbfa){return SGEXTN::ApplicationBase::FullCharacterType::OtherSymbol;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x20000 && i <= 0x3ffff){
        if(i >= 0x20000 && i < 0x2a6e0){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2a700 && i < 0x2b73a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2b73f && i < 0x2b81e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2b820 && i < 0x2ebe1){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2ebf0 && i < 0x2ee5e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x2f800 && i < 0x2fa1e){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x30000 && i < 0x3134b){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        if(i >= 0x31350 && i < 0x3347a){return SGEXTN::ApplicationBase::FullCharacterType::OtherLetter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xe0000 && i <= 0xe007f){
        if(i == 0xe0001){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        if(i >= 0xe0020 && i < 0xe0080){return SGEXTN::ApplicationBase::FullCharacterType::FormatCharacter;}
        return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xe0100 && i <= 0xe01ef){return SGEXTN::ApplicationBase::FullCharacterType::NonspacingMark;}
    if(i >= 0xf0000 && i <= 0xffffd){return SGEXTN::ApplicationBase::FullCharacterType::PrivateUseCharacter;}
    if(i >= 0x100000 && i <= 0x10fffd){return SGEXTN::ApplicationBase::FullCharacterType::PrivateUseCharacter;}
    return SGEXTN::ApplicationBase::FullCharacterType::UnassignedCharacter;
}

void checkCategory(int end){
    for(int i=0; i<=end; i++){
        if(categoryStorage.at(i) != officialCategoryToSGExtnCategory(sgextnCategoryToOfficialCategory(getUnicodeFullType(i)))){
            qDebug() << QString::number(i, 16) << categoryStorage.at(i) << officialCategoryToSGExtnCategory(sgextnCategoryToOfficialCategory(getUnicodeFullType(i)));
        }
    }
}