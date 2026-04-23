#include <QString>
#include <QFile>
#include <QVector>
#include <QMap>
#include <QDebug>
#include <SGEXTN_ApplicationBase_Character.h>
#include <SGEXTN_ApplicationBase_Debug.h>
#include <SGEXTN_ApplicationBase_UnicodeQuery.h>
#include <SGEXTN_Math_FloatLimits.h>

QMap<int, QVector<QString>> allOfUnicode;
QVector<int> decimalDigitStorage;
QVector<float> numericalStorage;

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

float parseRationalNumber(const QString& numString){
    if(numString.contains('/') == false){return numString.toFloat();}
    int slashIndex = numString.indexOf('/');
    return (numString.left(slashIndex).toFloat() / numString.right(numString.length() - slashIndex - 1).toFloat());
}

void extractNumbers(){
    decimalDigitStorage = QVector<int>();
    numericalStorage = QVector<float>();
    for(int i=0; i<=0x10ffff; i++){
        int thisDecimalDigit = -1;
        float thisNumericalValue = SGEXTN::Math::FloatLimits<float>::negativeInfinity();
        if(allOfUnicode.contains(i) == true){
            if(allOfUnicode[i].at(5) != ""){thisDecimalDigit = allOfUnicode[i].at(5).toInt();}
            if(allOfUnicode[i].at(7) != ""){
                bool isOk = false;
                thisNumericalValue = parseRationalNumber(allOfUnicode[i].at(7));
            }
        }
        decimalDigitStorage.push_back(thisDecimalDigit);
        numericalStorage.push_back(thisNumericalValue);
    }
}

void printDecimalDigit(int start){
    int previousDecimalDigit = -1;
    QString logInfo = "";
    int prevCount = 0;
    for(int i=start; i<decimalDigitStorage.length(); i++){
        if(decimalDigitStorage.at(i) != previousDecimalDigit){
            prevCount++;
            logInfo = QString::number(prevCount) + " " + logInfo;
            qDebug().noquote() << logInfo;
            logInfo = QString::number(i, 16).toLower() + " " + QString::number(decimalDigitStorage.at(i));
            previousDecimalDigit = decimalDigitStorage.at(i);
            prevCount = 0;
        }
        else{prevCount++;}
    }
    qDebug().noquote() << logInfo;
}

void printNumericalValue(int start){
    float previousNumericalValue = SGEXTN::Math::FloatLimits<float>::negativeInfinity();
    QString logInfo = "";
    int prevCount = 0;
    for(int i=start; i<numericalStorage.length(); i++){
        if(numericalStorage.at(i) != previousNumericalValue){
            prevCount++;
            logInfo = QString::number(prevCount) + " " + logInfo;
            qDebug().noquote() << logInfo;
            logInfo = QString::number(i, 16).toLower() + " " + QString::number(numericalStorage.at(i));
            previousNumericalValue = numericalStorage.at(i);
            prevCount = 0;
        }
        else{prevCount++;}
    }
    qDebug().noquote() << logInfo;
}

int getUnicodeDecimalDigit(int i){
    if(i >= 0x30 && i < 0x3a){return (i - 0x30);}
    if(i < 0x80){return -1;}
    if(i >= 0x4e00 && i <= 0x9fff){return -1;}
    if(i >= 0xbe6 && i < 0xbf0){return (i - 0xbe6);}
    if(i >= 0xb80 && i <= 0xbff){return -1;}
    if(i >= 0x2190 && i <= 0x23ff){return -1;}
    if(i >= 0x600 && i <= 0x1cff){
        if(i >= 0x660 && i < 0x66a){return (i - 0x660);}
        if(i >= 0x6f0 && i < 0x6fa){return (i - 0x6f0);}
        if(i >= 0x7c0 && i < 0x7ca){return (i - 0x7c0);}
        if(i >= 0x966 && i < 0x970){return (i - 0x966);}
        if(i >= 0x9e6 && i < 0x9f0){return (i - 0x9e6);}
        if(i >= 0xa66 && i < 0xa70){return (i - 0xa66);}
        if(i >= 0xae6 && i < 0xaf0){return (i - 0xae6);}
        if(i >= 0xb66 && i < 0xb70){return (i - 0xb66);}
        if(i >= 0xc66 && i < 0xc70){return (i - 0xc66);}
        if(i >= 0xce6 && i < 0xcf0){return (i - 0xce6);}
        if(i >= 0xd66 && i < 0xd70){return (i - 0xd66);}
        if(i >= 0xde6 && i < 0xdf0){return (i - 0xde6);}
        if(i >= 0xe50 && i < 0xe5a){return (i - 0xe50);}
        if(i >= 0xed0 && i < 0xeda){return (i - 0xed0);}
        if(i >= 0xf20 && i < 0xf2a){return (i - 0xf20);}
        if(i >= 0x1040 && i < 0x104a){return (i - 0x1040);}
        if(i >= 0x1090 && i < 0x109a){return (i - 0x1090);}
        if(i >= 0x17e0 && i < 0x17ea){return (i - 0x17e0);}
        if(i >= 0x1810 && i < 0x181a){return (i - 0x1810);}
        if(i >= 0x1946 && i < 0x1950){return (i - 0x1946);}
        if(i >= 0x19d0 && i < 0x19da){return (i - 0x19d0);}
        if(i >= 0x1a80 && i < 0x1a8a){return (i - 0x1a80);}
        if(i >= 0x1a90 && i < 0x1a9a){return (i - 0x1a90);}
        if(i >= 0x1b50 && i < 0x1b5a){return (i - 0x1b50);}
        if(i >= 0x1bb0 && i < 0x1bba){return (i - 0x1bb0);}
        if(i >= 0x1c40 && i < 0x1c4a){return (i - 0x1c40);}
        if(i >= 0x1c50 && i < 0x1c5a){return (i - 0x1c50);}
    }
    if(i >= 0xa600 && i <= 0xabff){
        if(i >= 0xa620 && i < 0xa62a){return (i - 0xa620);}
        if(i >= 0xa8d0 && i < 0xa8da){return (i - 0xa8d0);}
        if(i >= 0xa900 && i < 0xa90a){return (i - 0xa900);}
        if(i >= 0xa9d0 && i < 0xa9da){return (i - 0xa9d0);}
        if(i >= 0xa9f0 && i < 0xa9fa){return (i - 0xa9f0);}
        if(i >= 0xaa50 && i < 0xaa5a){return (i - 0xaa50);}
        if(i >= 0xabf0 && i < 0xabfa){return (i - 0xabf0);}
    }
    if(i >= 0xff10 && i < 0xff1a){return (i - 0xff10);}
    if(i >= 0x104a0 && i < 0x104aa){return (i - 0x104a0);}
    if(i >= 0x10d00 && i <= 0x11fff){
        if(i >= 0x10d30 && i < 0x10d3a){return (i - 0x10d30);}
        if(i >= 0x10d40 && i < 0x10d4a){return (i - 0x10d40);}
        if(i >= 0x11066 && i < 0x11070){return (i - 0x11066);}
        if(i >= 0x110f0 && i < 0x110fa){return (i - 0x110f0);}
        if(i >= 0x11136 && i < 0x11140){return (i - 0x11136);}
        if(i >= 0x111d0 && i < 0x111da){return (i - 0x111d0);}
        if(i >= 0x112f0 && i < 0x112fa){return (i - 0x112f0);}
        if(i >= 0x11450 && i < 0x1145a){return (i - 0x11450);}
        if(i >= 0x114d0 && i < 0x114da){return (i - 0x114d0);}
        if(i >= 0x11650 && i < 0x1165a){return (i - 0x11650);}
        if(i >= 0x116c0 && i < 0x116ca){return (i - 0x116c0);}
        if(i >= 0x116d0 && i < 0x116da){return (i - 0x116d0);}
        if(i >= 0x116da && i < 0x116e4){return (i - 0x116da);}
        if(i >= 0x11730 && i < 0x1173a){return (i - 0x11730);}
        if(i >= 0x118e0 && i < 0x118ea){return (i - 0x118e0);}
        if(i >= 0x11950 && i < 0x1195a){return (i - 0x11950);}
        if(i >= 0x11bf0 && i < 0x11bfa){return (i - 0x11bf0);}
        if(i >= 0x11c50 && i < 0x11c5a){return (i - 0x11c50);}
        if(i >= 0x11d50 && i < 0x11d5a){return (i - 0x11d50);}
        if(i >= 0x11da0 && i < 0x11daa){return (i - 0x11da0);}
        if(i >= 0x11de0 && i < 0x11dea){return (i - 0x11de0);}
        if(i >= 0x11f50 && i < 0x11f5a){return (i - 0x11f50);}
    }
    if(i >= 0x16100 && i <= 0x16dff){
        if(i >= 0x16130 && i < 0x1613a){return (i - 0x16130);}
        if(i >= 0x16a60 && i < 0x16a6a){return (i - 0x16a60);}
        if(i >= 0x16ac0 && i < 0x16aca){return (i - 0x16ac0);}
        if(i >= 0x16b50 && i < 0x16b5a){return (i - 0x16b50);}
        if(i >= 0x16d70 && i < 0x16d7a){return (i - 0x16d70);}
    }
    if(i >= 0x1cc00 && i <= 0x1ffff){
        if(i >= 0x1ccf0 && i < 0x1ccfa){return (i - 0x1ccf0);}
        if(i >= 0x1d7ce && i < 0x1d800){return ((i - 0x1d7ce) % 10);}
        if(i >= 0x1e140 && i < 0x1e14a){return (i - 0x1e140);}
        if(i >= 0x1e2f0 && i < 0x1e2fa){return (i - 0x1e2f0);}
        if(i >= 0x1e4f0 && i < 0x1e4fa){return (i - 0x1e4f0);}
        if(i >= 0x1e5f1 && i < 0x1e5fb){return (i - 0x1e5f1);}
        if(i >= 0x1e950 && i < 0x1e95a){return (i - 0x1e950);}
        if(i >= 0x1fbf0 && i < 0x1fbfa){return (i - 0x1fbf0);}
    }
    return -1;
}

float getUnicodeNumerical(int i){
    int decimalDigit = getUnicodeDecimalDigit(i);
    if(decimalDigit != -1){return static_cast<float>(decimalDigit);}
    if(i < 0x80){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    if(i >= 0x4e00 && i <= 0x9fff){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    if(i >= 0xb80 && i <= 0xbff){
        if(i == 0xbf0){return 10.0f;}
        if(i == 0xbf1){return 100.0f;}
        if(i == 0xbf2){return 1000.0f;}
        return SGEXTN::Math::FloatLimits<float>::negativeInfinity();
    }
    if(i >= 0x2190 && i <= 0x23ff){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    if(i >= 0xb2 && i <= 0xbe){
        if(i == 0xb2){return 2.0f;}
        if(i == 0xb3){return 3.0f;}
        if(i == 0xb9){return 1.0f;}
        if(i == 0xbc){return 0.25f;}
        if(i == 0xbd){return 0.5f;}
        if(i == 0xbe){return 0.75f;}
    }
    if(i >= 0x900 && i <= 0xfff){
        if(i >= 0x9f4 && i <= 0x9f9){
            if(i == 0x9f4){return 0.0625f;}
            if(i == 0x9f5){return 0.125f;}
            if(i == 0x9f6){return 0.1875f;}
            if(i == 0x9f7){return 0.25f;}
            if(i == 0x9f8){return 0.75f;}
            if(i == 0x9f9){return 16.0f;}
        }
        if(i >= 0xb72 && i <= 0xb77){
            if(i == 0xb72){return 0.25f;}
            if(i == 0xb73){return 0.5f;}
            if(i == 0xb74){return 0.75f;}
            if(i == 0xb75){return 0.0625f;}
            if(i == 0xb76){return 0.125f;}
            if(i == 0xb77){return 0.1875f;}
        }
        if(i >= 0xc78 && i <= 0xc7e){
            if(i == 0xc78){return 0.0f;}
            if(i == 0xc79 || i == 0xc7c){return 1.0f;}
            if(i == 0xc7a || i == 0xc7d){return 2.0f;}
            if(i == 0xc7b || i == 0xc7e){return 3.0f;}
        }
        if(i >= 0xd58 && i <= 0xd5e){
            if(i == 0xd58){return 0.00625f;}
            if(i == 0xd59){return 0.025f;}
            if(i == 0xd5a){return 0.0375f;}
            if(i == 0xd5b){return 0.05f;}
            if(i == 0xd5c){return 0.1f;}
            if(i == 0xd5d){return 0.15f;}
            if(i == 0xd5e){return 0.2f;}
        }
        if(i >= 0xd70 && i <= 0xd78){
            if(i == 0xd70){return 10.0f;}
            if(i == 0xd71){return 100.0f;}
            if(i == 0xd72){return 1000.0f;}
            if(i == 0xd73){return 0.25f;}
            if(i == 0xd74){return 0.5f;}
            if(i == 0xd75){return 0.75f;}
            if(i == 0xd76){return 0.0625f;}
            if(i == 0xd77){return 0.125f;}
            if(i == 0xd78){return 0.1875f;}
        }
        if(i >= 0xf2a && i <= 0xf32){return (static_cast<float>((i - 0xf2a) % 10) + 0.5f);}
        if(i == 0xf33){return -0.5f;}
    }
    if(i >= 0x1300 && i <= 0x21ff){
        if(i >= 0x1369 && i <= 0x1371){return static_cast<float>(i - 0x1368);}
        if(i >= 0x1372 && i <= 0x137b){return (10.0f * static_cast<float>(i - 0x1371));}
        if(i == 0x137c){return 10000.0f;}
        if(i >= 0x16ee && i <= 0x16f0){return (17.0f + static_cast<float>(i - 0x16ee));}
        if(i >= 0x17f0 && i <= 0x17f9){return static_cast<float>(i - 0x17f0);}
        if(i == 0x19da){return 1.0f;}
        if(i == 0x2070){return 0.0f;}
        if(i >= 0x2074 && i <= 0x2079){return static_cast<float>(i - 0x2070);}
        if(i >= 0x2080 && i <= 0x2089){return static_cast<float>(i - 0x2080);}
        if(i >= 0x2150 && i <= 0x215f){
            if(i == 0x2150){return (1.0f / 7.0f);}
            if(i == 0x2151){return (1.0f / 9.0f);}
            if(i == 0x2152){return 0.1f;}
            if(i == 0x2153){return (1.0f / 3.0f);}
            if(i == 0x2154){return (2.0f / 3.0f);}
            if(i == 0x2155){return 0.2f;}
            if(i == 0x2156){return 0.4f;}
            if(i == 0x2157){return 0.6f;}
            if(i == 0x2158){return 0.8f;}
            if(i == 0x2159){return (1.0f / 6.0f);}
            if(i == 0x215a){return (5.0f / 6.0f);}
            if(i == 0x215b){return 0.125f;}
            if(i == 0x215c){return 0.375f;}
            if(i == 0x215d){return 0.625f;}
            if(i == 0x215e){return 0.875f;}
            if(i == 0x215f){return 1.0f;}
        }
        if(i >= 0x2160 && i <= 0x216b){return static_cast<float>(i - 0x215f);}
        if(i >= 0x216c && i <= 0x216f){
            if(i == 0x216c){return 50.0f;}
            if(i == 0x216d){return 100.0f;}
            if(i == 0x216e){return 500.0f;}
            if(i == 0x216f){return 1000.0f;}
        }
        if(i >= 0x2170 && i <= 0x217b){return static_cast<float>(i - 0x216f);}
        if(i >= 0x217c && i <= 0x2189){
            if(i == 0x217c){return 50.0f;}
            if(i == 0x217d){return 100.0f;}
            if(i == 0x217e){return 500.0f;}
            if(i == 0x217f){return 1000.0f;}
            if(i == 0x2180){return 1000.0f;}
            if(i == 0x2181){return 5000.0f;}
            if(i == 0x2182){return 10000.0f;}
            if(i == 0x2185){return 6.0f;}
            if(i == 0x2186){return 50.0f;}
            if(i == 0x2187){return 50000.0f;}
            if(i == 0x2188){return 100000.0f;}
            if(i == 0x2189){return 0.0f;}
        }
    }
    if(i >= 0x2400 && i <= 0x24ff){
        if(i >= 0x2460 && i <= 0x2473){return static_cast<float>(i - 0x245f);}
        if(i >= 0x2474 && i <= 0x2487){return static_cast<float>(i - 0x2473);}
        if(i >= 0x2488 && i <= 0x249b){return static_cast<float>(i - 0x2487);}
        if(i == 0x24ea){return 0.0;}
        if(i >= 0x24eb && i <= 0x24f4){return (10.0f + static_cast<float>(i - 0x24ea));}
        if(i >= 0x24f5 && i <= 0x24fe){return static_cast<float>(i - 0x24f4);}
        if(i == 0x24ff){return 0.0f;}
    }
    if(i >= 2700 && i <= 0x27ff){
        if(i >= 0x2776 && i <= 0x277f){return static_cast<float>(i - 0x2775);}
        if(i >= 0x2780 && i <= 0x2789){return static_cast<float>(i - 0x277f);}
        if(i >= 0x278a && i <= 0x2793){return static_cast<float>(i - 0x2789);}
    }
    if(i == 0x2cfd){return 0.5f;}
    if(i >= 0x3000 && i <= 0x32ff){
        if(i == 0x3007){return 0.0f;}
        if(i >= 0x3021 && i <= 0x3029){return static_cast<float>(i - 0x3020);}
        if(i >= 0x3038 && i <= 0x303a){return (10.0f * static_cast<float>(i - 0x3037));}
        if(i >= 0x3192 && i <= 0x3195){return static_cast<float>(i - 0x3191);}
        if(i >= 0x3220 && i <= 0x3229){return static_cast<float>(i - 0x321f);}
        if(i >= 0x3248 && i <= 0x324f){return (10.0f * static_cast<float>(i - 0x3247));}
        if(i >= 0x3251 && i <= 0x325f){return (20.0f + static_cast<float>(i - 0x3250));}
        if(i >= 0x3280 && i <= 0x3289){return static_cast<float>(i - 0x327f);}
        if(i >= 0x32b1 && i <= 0x32bf){return (35.0f + static_cast<float>(i - 0x32b0));}
    }
    if(i >= 0xa600 && i <= 0xa8ff){
        if(i >= 0xa6e6 && i <= 0xa6ee){return static_cast<float>(i - 0xa6e5);}
        if(i == 0xa6ef){return 0.0f;}
        if(i >= 0xa830 && i <= 0xa835){
            if(i == 0xa830){return 0.25f;}
            if(i == 0xa831){return 0.5f;}
            if(i == 0xa832){return 0.75f;}
            if(i == 0xa833){return 0.0625f;}
            if(i == 0xa834){return 0.125f;}
            if(i == 0xa835){return 0.1875f;}
        }
    }
    if(i >= 0xf900 && i <= 0x103ff){
        if(i == 0xf96b){return 3.0f;}
        if(i == 0xf973){return 10.0f;}
        if(i == 0xf978){return 2.0f;}
        if(i == 0xf9b2){return 0.0f;}
        if(i == 0xf9d1 || i == 0xf9d3){return 6.0f;}
        if(i == 0xf9fd){return 10.0f;}
        if(i >= 0x10107 && i <= 0x1010f){return static_cast<float>(i - 0x10106);}
        if(i >= 0x10110 && i <= 0x10118){return (10.0f * static_cast<float>(i - 0x1010f));}
        if(i >= 0x10119 && i <= 0x10121){return (100.0f * static_cast<float>(i - 0x10118));}
        if(i >= 0x10122 && i <= 0x1012a){return (1000.0f * static_cast<float>(i - 0x10121));}
        if(i >= 0x1012b && i <= 0x10133){return (10000.0f * static_cast<float>(i - 0x1012a));}
        if(i >= 0x10140 && i <= 0x1018b){
            if(i == 0x10140 || i == 0x1018b){return 0.25f;}
            if(i == 0x10141 || i == 0x10175 || i == 0x10176){return 0.5f;}
            if(i == 0x10142){return 1.0f;}
            if(i == 0x10143 || i == 0x10148 || i == 0x1014f || i == 0x1015f || i == 0x10173){return 5.0f;}
            if(i == 0x10144 || i == 0x1014a || i == 0x10151 || i == 0x10174){return 50.0f;}
            if(i == 0x10145 || i == 0x1014c || i == 0x10153){return 500.0f;}
            if(i == 0x10146 || i == 0x1014e || i == 0x10172){return 5000.0f;}
            if(i == 0x10147 || i == 0x10156){return 50000.0f;}
            if(i == 0x10149 || i == 0x10150 || i == 0x10157){return 10.0f;}
            if(i == 0x1014b || i == 0x10152 || i == 0x1016a){return 100.0f;}
            if(i == 0x1014d || i == 0x10154 || i == 0x10171){return 1000.0f;}
            if(i == 0x10155){return 10000.0f;}
            if(i >= 0x10158 && i <= 0x1015a){return 1.0f;}
            if(i >= 0x1015b && i <= 0x1015e){return 2.0f;}
            if(i >= 0x10160 && i <= 0x10164){return 10.0f;}
            if(i == 0x10165){return 30.0f;}
            if(i >= 0x10166 && i <= 0x10169){return 50.0f;}
            if(i == 0x1016b){return 300.0f;}
            if(i >= 0x1016c && i <= 0x10170){return 500.0f;}
            if(i == 0x10177){return (2.0f / 3.0f);}
            if(i == 0x10178){return 0.75f;}
            if(i == 0x1018a){return 0.0f;}
        }
        if(i >= 0x102e1 && i <= 0x102e9){return static_cast<float>(i - 0x102e0);}
        if(i >= 0x102ea && i <= 0x102f2){return (10.0f * static_cast<float>(i - 0x102e9));}
        if(i >= 0x102f3 && i <= 0x102fb){return (100.0f * static_cast<float>(i - 0x102f2));}
        if(i >= 0x10320 && i <= 0x10323){
            if(i == 0x10320){return 1.0f;}
            if(i == 0x10321){return 5.0f;}
            if(i == 0x10322){return 10.0f;}
            if(i == 0x10323){return 50.0f;}
        }
        if(i == 0x10341){return 90.0f;}
        if(i == 0x1034a){return 900.0f;}
        if(i >= 0x103d1 && i <= 0x103d5){
            if(i == 0x103d1){return 1.0f;}
            if(i == 0x103d2){return 2.0f;}
            if(i == 0x103d3){return 10.0f;}
            if(i == 0x103d4){return 20.0f;}
            if(i == 0x103d5){return 100.0f;}
        }
    }
    if(i >= 0x10800 && i <= 0x111ff){
        if(i >= 0x10858 && i <= 0x1085f){
            if(i >= 0x10858 && i <= 0x1085a){return static_cast<float>(i - 0x10857);}
            if(i == 0x1085b){return 10.0f;}
            if(i == 0x1085c){return 20.0f;}
            if(i == 0x1085d){return 100.0f;}
            if(i == 0x1085e){return 1000.0f;}
            if(i == 0x1085f){return 10000.0f;}
        }
        if(i >= 0x10879 && i <= 0x1087f){
            if(i >= 0x10879 && i <= 0x1087d){return static_cast<float>(i - 0x10878);}
            if(i == 0x1087e){return 10.0f;}
            if(i == 0x1087f){return 20.0f;}
        }
        if(i >= 0x108a7 && i <= 0x108af){
            if(i >= 0x108a7 && i <= 0x108aa){return static_cast<float>(i - 0x108a6);}
            if(i == 0x108ab){return 4.0f;}
            if(i == 0x108ac){return 5.0f;}
            if(i == 0x108ad){return 10.0f;}
            if(i == 0x108ae){return 20.0f;}
            if(i == 0x108af){return 100.0f;}
        }
        if(i >= 0x108fb && i <= 0x108ff){
            if(i == 0x108fb){return 1.0f;}
            if(i == 0x108fc){return 5.0f;}
            if(i == 0x108fd){return 10.0f;}
            if(i == 0x108fe){return 20.0f;}
            if(i == 0x108ff){return 100.0f;}
        }
        if(i >= 0x10916 && i <= 0x1091b){
            if(i == 0x10916){return 1.0f;}
            if(i == 0x10917){return 10.0f;}
            if(i == 0x10918){return 20.0f;}
            if(i == 0x10919){return 100.0f;}
            if(i == 0x1091a){return 2.0f;}
            if(i == 0x1091b){return 3.0f;}
        }
        if(i == 0x109bc){return (11.0f / 12.0f);}
        if(i == 0x109bd){return 0.5f;}
        if(i >= 0x109c0 && i <= 0x109c8){return static_cast<float>(i - 0x109bf);}
        if(i >= 0x109c9 && i <= 0x109cf){return (10.0f * static_cast<float>(i - 0x109c8));}
        if(i >= 0x109d2 && i <= 0x109da){return (100.0f * static_cast<float>(i - 0x109d1));}
        if(i >= 0x109db && i <= 0x109e3){return (1000.0f * static_cast<float>(i - 0x109da));}
        if(i >= 0x109e4 && i <= 0x109ec){return (10000.0f * static_cast<float>(i - 0x109e3));}
        if(i >= 0x109ed && i <= 0x109f5){return (100000.0f * static_cast<float>(i - 0x109ec));}
        if(i >= 0x109f6 && i <= 0x109ff){return (static_cast<float>(i - 0x109f5) / 12.0f);}
        if(i >= 0x10a40 && i <= 0x10a48){
            if(i >= 0x10a40 && i <= 0x10a43){return static_cast<float>(i - 0x10a3f);}
            if(i == 0x10a44){return 10.0f;}
            if(i == 0x10a45){return 20.0f;}
            if(i == 0x10a46){return 100.0f;}
            if(i == 0x10a47){return 1000.0f;}
            if(i == 0x10a48){return 0.5f;}
        }
        if(i == 0x10a7d){return 1.0f;}
        if(i == 0x10a7e){return 50.0f;}
        if(i >= 0x10a9d && i <= 0x10a9f){
            if(i == 0x10a9d){return 1.0f;}
            if(i == 0x10a9e){return 10.0f;}
            if(i == 0x10a9f){return 20.0f;}
        }
        if(i >= 0x10aeb && i <= 0x10aef){
            if(i == 0x10aeb){return 1.0f;}
            if(i == 0x10aec){return 5.0f;}
            if(i == 0x10aed){return 10.0f;}
            if(i == 0x10aee){return 20.0f;}
            if(i == 0x10aef){return 100.0f;}
        }
        if(i >= 0x10b58 && i <= 0x10b5f){
            if(i >= 0x10b58 && i <= 0x10b5b){return static_cast<float>(i - 0x10b57);}
            if(i == 0x10b5c){return 10.0f;}
            if(i == 0x10b5d){return 20.0f;}
            if(i == 0x10b5e){return 100.0f;}
            if(i == 0x10b5f){return 1000.0f;}
        }
        if(i >= 0x10b78 && i <= 0x10b7f){
            if(i >= 0x10b78 && i <= 0x10b7b){return static_cast<float>(i - 0x10b77);}
            if(i == 0x10b7c){return 10.0f;}
            if(i == 0x10b7d){return 20.0f;}
            if(i == 0x10b7e){return 100.0f;}
            if(i == 0x10b7f){return 1000.0f;}
        }
        if(i >= 0x10ba9 && i <= 0x10baf){
            if(i >= 0x10ba9 && i <= 0x10bac){return static_cast<float>(i - 0x10ba8);}
            if(i == 0x10bad){return 10.0f;}
            if(i == 0x10bae){return 20.0f;}
            if(i == 0x10baf){return 100.0f;}
        }
        if(i >= 0x10cfa && i <= 0x10cff){
            if(i == 0x10cfa){return 1.0f;}
            if(i == 0x10cfb){return 5.0f;}
            if(i == 0x10cfc){return 10.0f;}
            if(i == 0x10cfd){return 50.0f;}
            if(i == 0x10cfe){return 100.0f;}
            if(i == 0x10cff){return 1000.0f;}
        }
        if(i >= 0x10e60 && i <= 0x10e68){return static_cast<float>(i - 0x10e5f);}
        if(i >= 0x10e69 && i <= 0x10e71){return (10.0f * static_cast<float>(i - 0x10e68));}
        if(i >= 0x10e72 && i <= 0x10e7a){return (100.0f * static_cast<float>(i - 0x10e71));}
        if(i >= 0x10e7b && i <= 0x10e7e){
            if(i == 0x10e7b){return 0.5f;}
            if(i == 0x10e7c){return 0.25f;}
            if(i == 0x10e7d){return (1.0f / 3.0f);}
            if(i == 0x10e7e){return (2.0f / 3.0f);}
        }
        if(i >= 0x10f1d && i <= 0x10f21){return static_cast<float>(i - 0x10f1c);}
        if(i >= 0x10f22 && i <= 0x10f24){return (10.0f * static_cast<float>(i - 0x10f21));}
        if(i == 0x10f25){return 100.0f;}
        if(i == 0x10f26){return 0.5f;}
        if(i >= 0x10f51 && i <= 0x10f54){
            if(i == 0x10f51){return 1.0f;}
            if(i == 0x10f52){return 10.0f;}
            if(i == 0x10f53){return 20.0f;}
            if(i == 0x10f54){return 100.0f;}
        }
        if(i >= 0x10fc5 && i <= 0x10fc8){return static_cast<float>(i - 0x10fc4);}
        if(i >= 0x10fc9 && i <= 0x10fcb){
            if(i == 0x10fc9){return 10.0f;}
            if(i == 0x10fca){return 20.0f;}
            if(i == 0x10fcb){return 100.0f;}
        }
        if(i >= 0x11052 && i <= 0x1105a){return static_cast<float>(i - 0x11051);}
        if(i >= 0x1105b && i <= 0x11064){return (10.0f * static_cast<float>(i - 0x1105a));}
        if(i == 0x11065){return 1000.0f;}
        if(i >= 0x111e1 && i <= 0x111e9){return static_cast<float>(i - 0x111e0);}
        if(i >= 0x111ea && i <= 0x111f3){return (10.0f * static_cast<float>(i - 0x111e9));}
        if(i == 0x111f4){return 1000.0f;}
    }
    if(i >= 0x11700 && i <= 0x124ff){
        if(i == 0x1173a){return 10.0f;}
        if(i == 0x1173b){return 20.0f;}
        if(i >= 0x118ea && i <= 0x118f2){return (10.0f * static_cast<float>(i - 0x118e9));}
        if(i >= 0x11c5a && i <= 0x11c62){return static_cast<float>(i - 0x11c59);}
        if(i >= 0x11c63 && i <= 0x11c6c){return (10.0f * static_cast<float>(i - 0x11c62));}
        if(i >= 0x11fc0 && i <= 0x11fd4){
            if(i == 0x11fc0){return 0.003125f;}
            if(i == 0x11fc1){return 0.00625f;}
            if(i == 0x11fc2){return 0.0125f;}
            if(i == 0x11fc3){return 0.015625f;}
            if(i == 0x11fc4){return 0.025f;}
            if(i == 0x11fc5){return 0.03125f;}
            if(i == 0x11fc6){return 0.0375f;}
            if(i == 0x11fc7){return 0.046875f;}
            if(i == 0x11fc8){return 0.05f;}
            if(i == 0x11fc9 || i== 0x11fca){return 0.0625f;}
            if(i == 0x11fcb){return 0.1f;}
            if(i == 0x11fcc){return 0.125f;}
            if(i == 0x11fcd){return 0.15f;}
            if(i == 0x11fce){return 0.1875f;}
            if(i == 0x11fcf){return 0.2f;}
            if(i == 0x11fd0){return 0.25f;}
            if(i == 0x11fd1 || i == 0x11fd2){return 0.5f;}
            if(i == 0x11fd3){return 0.75f;}
            if(i == 0x11fd4){return 0.003125f;}
        }
        if(i == 0x12038 || i == 0x12039){return 1.0f;}
        if(i == 0x12079){return 1.0f;}
        if(i == 0x12226){return 0.5f;}
        if(i == 0x1222b){return 2.0f;}
        if(i == 0x1230b){return 1.0f;}
        if(i == 0x1230d){return 3.0f;}
        if(i == 0x12399){return 2.0f;}
        if(i >= 0x12400 && i <= 0x1246e){
            if(i >= 0x12400 && i <= 0x12407){return static_cast<float>(i - 0x123fe);}
            if(i >= 0x12408 && i <= 0x1240e){return static_cast<float>(i - 0x12405);}
            if(i >= 0x1240f && i <= 0x12414){return static_cast<float>(i - 0x1240b);}
            if(i >= 0x12415 && i <= 0x1241d){return static_cast<float>(i - 0x12414);}
            if(i >= 0x1241e && i <= 0x12422){return static_cast<float>(i - 0x1241d);}
            if(i == 0x12423){return 2.0f;}
            if(i >= 0x12424 && i <= 0x12425){return 3.0f;}
            if(i >= 0x12426 && i <= 0x1242b){return static_cast<float>(i - 0x12422);}
            if(i >= 0x1242c && i <= 0x1242e){return static_cast<float>(i - 0x1242b);}
            if(i >= 0x1242f && i <= 0x12431){return static_cast<float>(i - 0x1242c);}
            if(i == 0x12432){return 216000.0f;}
            if(i == 0x12433){return 432000.0f;}
            if(i >= 0x12434 && i <= 0x12436){return static_cast<float>(i - 0x12433);}
            if(i >= 0x12437 && i <= 0x12439){return static_cast<float>(i - 0x12434);}
            if(i >= 0x1243a && i <= 0x1243b){return 3.0f;}
            if(i >= 0x1243c && i <= 0x1243f){return 4.0f;}
            if(i == 0x12440){return 6.0f;}
            if(i >= 0x12441 && i <= 0x12443){return 7.0f;}
            if(i >= 0x12444 && i <= 0x12445){return 8.0f;}
            if(i >= 0x12446 && i <= 0x12449){return 9.0f;}
            if(i >= 0x1244a && i <= 0x1244e){return static_cast<float>(i - 0x12448);}
            if(i >= 0x1244f && i <= 0x12452){return static_cast<float>(i - 0x1244e);}
            if(i == 0x12453){return 4.0f;}
            if(i >= 0x12454 && i <= 0x12455){return 5.0f;}
            if(i == 0x12456 || i == 0x12459){return 2.0f;}
            if(i == 0x12457){return 3.0f;}
            if(i == 0x12458){return 1.0f;}
            if(i == 0x1245a || i == 0x1245d || i == 0x12465){return (1.0f / 3.0f);}
            if(i == 0x1245b || i == 0x1245e || i == 0x12466){return (2.0f / 3.0f);}
            if(i == 0x1245c){return (5.0f / 6.0f);}
            if(i == 0x1245f){return 0.125f;}
            if(i == 0x12460 || i == 0x12462 || i == 0x12463){return 0.25f;}
            if(i == 0x12461){return (1.0f / 6.0f);}
            if(i == 0x12464){return 0.5f;}
            if(i == 0x12467){return 40.0f;}
            if(i == 0x12468){return 50.0f;}
            if(i >= 0x12469 && i <= 0x1246e){return static_cast<float>(i - 0x12465);}
        }
    }
    if(i >= 0x16b00 && i <= 0x16fff){
        if(i >= 0x16b5b && i <= 0x16b61){
            if(i == 0x16b5b){return 10.0f;}
            if(i == 0x16b5c){return 100.0f;}
            if(i == 0x16b5d){return 10000.0f;}
            if(i == 0x16b5e){return 1000000.0f;}
            if(i == 0x16b5f){return 100000000.0f;}
            if(i == 0x16b60){return 10000000000.0f;}
            if(i == 0x16b61){return 1000000000000.0f;}
        }
        if(i >= 0x16e80 && i <= 0x16e93){return static_cast<float>(i - 0x16e80);}
        if(i >= 0x16e94 && i <= 0x16e96){return static_cast<float>(i - 0x16e93);}
        if(i >= 0x16ff4 && i <= 0x16ff6){return (1.0f + 0.5f * static_cast<float>(i - 0x16ff4));}
    }
    if(i >= 0x1d200 && i <= 0x1d3ff){
        if(i >= 0x1d2c0 && i <= 0x1d2d3){return static_cast<float>(i - 0x1d2c0);}
        if(i >= 0x1d2e0 && i <= 0x1d2f3){return static_cast<float>(i - 0x1d2e0);}
        if(i >= 0x1d360 && i <= 0x1d368){return static_cast<float>(i - 0x1d35f);}
        if(i >= 0x1d369 && i <= 0x1d371){return (10.0f * static_cast<float>(i - 0x1d368));}
        if(i >= 0x1d372 && i <= 0x1d376){return static_cast<float>(i - 0x1d371);}
        if(i == 0x1d377){return 1.0f;}
        if(i == 0x1d378){return 5.0f;}
    }
    if(i >= 0x1e8c7 && i <= 0x1e8cf){return static_cast<float>(i - 0x1e8c6);}
    if(i >= 0x1ec00 && i <= 0x1ed7f){
        if(i >= 0x1ec71 && i <= 0x1ec79){return static_cast<float>(i - 0x1ec70);}
        if(i >= 0x1ec7a && i <= 0x1ec82){return (10.0f * static_cast<float>(i - 0x1ec79));}
        if(i >= 0x1ec83 && i <= 0x1ec8b){return (100.0f * static_cast<float>(i - 0x1ec82));}
        if(i >= 0x1ec8c && i <= 0x1ec94){return (1000.0f * static_cast<float>(i - 0x1ec8b));}
        if(i >= 0x1ec95 && i <= 0x1ec9e){return (10000.0f * static_cast<float>(i - 0x1ec94));}
        if(i == 0x1ec9f){return 200000.0f;}
        if(i == 0x1eca0){return 100000.0f;}
        if(i == 0x1eca1){return 10000000.0f;}
        if(i == 0x1eca2){return 20000000.0f;}
        if(i >= 0x1eca3 && i <= 0x1ecab){return static_cast<float>(i - 0x1eca2);}
        if(i >= 0x1ecad && i <= 0x1ecaf){return (0.25f * static_cast<float>(i - 0x1ecac));}
        if(i == 0x1ecb1){return 1.0f;}
        if(i == 0x1ecb2){return 2.0f;}
        if(i == 0x1ecb3){return 10000.0f;}
        if(i == 0x1ecb4){return 100000.0f;}
        if(i >= 0x1ed01 && i <= 0x1ed09){return static_cast<float>(i - 0x1ed00);}
        if(i >= 0x1ed0a && i <= 0x1ed12){return (10.0f * static_cast<float>(i - 0x1ed09));}
        if(i >= 0x1ed13 && i <= 0x1ed1b){return (100.0f * static_cast<float>(i - 0x1ed12));}
        if(i >= 0x1ed1c && i <= 0x1ed24){return (1000.0f * static_cast<float>(i - 0x1ed1b));}
        if(i >= 0x1ed25 && i <= 0x1ed2d){return (10000.0f * static_cast<float>(i - 0x1ed24));}
        if(i >= 0x1ed2f && i <= 0x1ed37){return static_cast<float>(i - 0x1ed2d);}
        if(i == 0x1ed38){return 400.0f;}
        if(i == 0x1ed39){return 600.0f;}
        if(i == 0x1ed3a){return 2000.0f;}
        if(i == 0x1ed3b){return 10000.0f;}
        if(i == 0x1ed3c){return 0.5f;}
        if(i == 0x1ed3d){return (1.0f / 6.0f);}
    }
    if(i >= 0x1f100 && i <= 0x1f10f){
        if(i == 0x1f100 || i == 0x1f10b || i == 0x1f10c){return 0.0f;}
        if(i >= 0x1f101 && i <= 0x1f10a){return static_cast<float>(i - 0x1f101);}
    }
    if(i == 0x2f890){return 9.0f;}
    return SGEXTN::Math::FloatLimits<float>::negativeInfinity();
}

void checkDecimalDigit(int end){
    for(int i=0; i<=end; i++){
        if(decimalDigitStorage.at(i) != getUnicodeDecimalDigit(i)){
            qDebug() << QString::number(i, 16) << decimalDigitStorage.at(i) << getUnicodeDecimalDigit(i);
        }
    }
}

void checkNumericalValue(int end){
    for(int i=0; i<=end; i++){
        if(numericalStorage.at(i) != getUnicodeNumerical(i)){
            qDebug() << QString::number(i, 16) << numericalStorage.at(i) << getUnicodeNumerical(i);
        }
    }
}