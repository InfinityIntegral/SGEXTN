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
QVector<int> markOrderStorage;

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

void extractMarkOrder(){
    markOrderStorage = QVector<int>();
    for(int i=0; i<=0x10ffff; i++){
        int thisMarkOrder = 0;
        if(allOfUnicode.contains(i) == true){
            if(allOfUnicode[i].at(2) != ""){thisMarkOrder = allOfUnicode[i].at(2).toInt();}
        }
        markOrderStorage.push_back(thisMarkOrder);
    }
}

void printMarkOrder(int start){
    int previousMarkOrder = -1;
    QString logInfo = "";
    int prevCount = 0;
    for(int i=start; i<markOrderStorage.length(); i++){
        if(markOrderStorage.at(i) != previousMarkOrder){
            prevCount++;
            logInfo = QString::number(prevCount) + " " + logInfo;
            qDebug().noquote() << logInfo;
            logInfo = QString::number(i, 16).toLower() + " " + QString::number(markOrderStorage.at(i));
            previousMarkOrder = markOrderStorage.at(i);
            prevCount = 0;
        }
        else{prevCount++;}
    }
    qDebug().noquote() << logInfo;
}

int getUnicodeCombiningMarkOrder(int i){
    if(i < 0x80){return 0;}
    if(i >= 0x4e00 && i <= 0x9fff){return 0;}
    if(i == 0xbcd){return 9;}
    if(i >= 0xb80 && i <= 0xbff){return 0;}
    if(i >= 0x2190 && i <= 0x23ff){return 0;}
    if(i >= 0x300 && i < 0x370){
        if(i >= 0x300 && i < 0x315){return 230;}
        if(i == 0x315){return 232;}
        if(i >= 0x316 && i < 0x31a){return 220;}
        if(i == 0x31a){return 232;}
        if(i == 0x31b){return 216;}
        if(i >= 0x31c && i < 0x321){return 220;}
        if(i >= 0x321 && i < 0x323){return 202;}
        if(i >= 0x323 && i < 0x327){return 220;}
        if(i >= 0x327 && i < 0x329){return 202;}
        if(i >= 0x329 && i < 0x334){return 220;}
        if(i >= 0x334 && i < 0x339){return 1;}
        if(i >= 0x339 && i < 0x33d){return 220;}
        if(i >= 0x33d && i < 0x345){return 230;}
        if(i == 0x345){return 240;}
        if(i == 0x346){return 230;}
        if(i >= 0x347 && i < 0x34a){return 220;}
        if(i >= 0x34a && i < 0x34d){return 230;}
        if(i >= 0x34d && i < 0x34f){return 220;}
        if(i >= 0x350 && i < 0x353){return 230;}
        if(i >= 0x353 && i < 0x357){return 220;}
        if(i == 0x357){return 230;}
        if(i == 0x358){return 232;}
        if(i >= 0x359 && i < 0x35b){return 220;}
        if(i == 0x35b){return 230;}
        if(i == 0x35c || i == 0x35f || i == 0x362){return 233;}
        if(i >= 0x35d && i < 0x35f){return 234;}
        if(i >= 0x360 && i < 0x362){return 234;}
        if(i >= 0x363 && i < 0x370){return 230;}
        return 0;
    }
    if(i >= 0x483 && i < 0x488){return 230;}
    if(i >= 0x591 && i < 0x5c8){
        if(i == 0x591){return 220;}
        if(i >= 0x592 && i < 0x596){return 230;}
        if(i == 0x596){return 220;}
        if(i >= 0x597 && i < 0x59a){return 230;}
        if(i == 0x59a){return 222;}
        if(i == 0x59b){return 220;}
        if(i >= 0x59c && i < 0x5a2){return 230;}
        if(i >= 0x5a2 && i < 0x5a8){return 220;}
        if(i >= 0x5a8 && i < 0x5aa){return 230;}
        if(i == 0x5aa){return 220;}
        if(i >= 0x5ab && i < 0x5ad){return 230;}
        if(i == 0x5ad){return 222;}
        if(i == 0x5ae){return 228;}
        if(i == 0x5af){return 230;}
        if(i >= 0x5b0 && i < 0x5ba){return (10 + i - 0x5b0);}
        if(i >= 0x5ba && i < 0x5be){return (19 + i - 0x5ba);}
        if(i == 0x5bf){return 23;}
        if(i >= 0x5c1 && i < 0x5c3){return (24 + i - 0x5c1);}
        if(i == 0x5c4){return 230;}
        if(i == 0x5c5){return 220;}
        if(i == 0x5c7){return 18;}
        return 0;
    }
    if(i >= 0x600 && i < 0x700){
        if(i >= 0x610 && i < 0x618){return 230;}
        if(i >= 0x618 && i < 0x61b){return (30 + i - 0x618);}
        if(i >= 0x64b && i < 0x653){return (27 + i - 0x64b);}
        if(i >= 0x653 && i < 0x655){return 230;}
        if(i >= 0x655 && i < 0x657){return 220;}
        if(i >= 0x657 && i < 0x65c){return 230;}
        if(i == 0x65c || i == 0x65f){return 220;}
        if(i >= 0x65d && i < 0x65f){return 230;}
        if(i == 0x670){return 35;}
        if(i >= 0x6d6 && i < 0x6dd){return 230;}
        if(i >= 0x6df && i < 0x6e3){return 230;}
        if(i == 0x6e3){return 220;}
        if(i == 0x6e4){return 230;}
        if(i >= 0x6e7 && i < 0x6e9){return 230;}
        if(i == 0x6ea || i == 0x6ed){return 220;}
        if(i >= 0x6eb && i < 0x6ed){return 230;}
        return 0;
    }
    if(i >= 0x700 && i < 0x800){
        if(i == 0x711){return 36;}
        if(i == 0x730){return 230;}
        if(i == 0x731){return 220;}
        if(i >= 0x732 && i < 0x734){return 230;}
        if(i == 0x734){return 220;}
        if(i >= 0x735 && i < 0x737){return 230;}
        if(i >= 0x737 && i < 0x73a){return 220;}
        if(i == 0x73a){return 230;}
        if(i >= 0x73b && i < 0x73d){return 220;}
        if(i == 0x73d){return 230;}
        if(i == 0x73e){return 220;}
        if(i >= 0x73f && i < 0x742){return 230;}
        if(i >= 0x742 && i < 0x749 && i % 2 == 0){return 220;}
        if(i >= 0x742 && i < 0x749){return 230;}
        if(i >= 0x749 && i < 0x74b){return 230;}
        if(i >= 0x7eb && i < 0x7f2){return 230;}
        if(i == 0x7f2){return 220;}
        if(i == 0x7f3){return 230;}
        if(i == 0x7fd){return 220;}
        return 0;
    }
    if(i >= 0x800 && i < 0x900){
        if(i >= 0x816 && i < 0x81a){return 230;}
        if(i >= 0x81b && i < 0x824){return 230;}
        if(i >= 0x825 && i < 0x828){return 230;}
        if(i >= 0x829 && i < 0x82e){return 230;}
        if(i >= 0x859 && i < 0x85c){return 220;}
        if(i >= 0x897 && i < 0x899){return 230;}
        if(i >= 0x899 && i < 0x89c){return 220;}
        if(i >= 0x89c && i < 0x8a0){return 230;}
        if(i >= 0x8ca && i < 0x8cf){return 230;}
        if(i >= 0x8cf && i < 0x8d4){return 220;}
        if(i >= 0x8d4 && i < 0x8e2){return 230;}
        if(i == 0x8e3){return 220;}
        if(i >= 0x8e4 && i < 0x8e6){return 230;}
        if(i == 0x8e6){return 220;}
        if(i >= 0x8e7 && i < 0x8e9){return 230;}
        if(i == 0x8e9){return 220;}
        if(i >= 0x8ea && i < 0x8ed){return 230;}
        if(i >= 0x8ed && i < 0x8f0){return 220;}
        if(i >= 0x8f0 && i < 0x8f3){return (27 + i - 0x8f0);}
        if(i >= 0x8f3 && i < 0x8f6){return 230;}
        if(i == 0x8f6){return 220;}
        if(i >= 0x8f7 && i < 0x8f9){return 230;}
        if(i >= 0x8f9 && i < 0x8fb){return 220;}
        if(i >= 0x8fb && i < 0x900){return 230;}
        return 0;
    }
    if(i >= 0x900 && i < 0xa00){
        if(i == 0x93c){return 7;}
        if(i == 0x94d){return 9;}
        if(i == 0x951){return 230;}
        if(i == 0x952){return 220;}
        if(i >= 0x953 && i < 0x955){return 230;}
        if(i == 0x9bc){return 7;}
        if(i == 0x9cd){return 9;}
        if(i == 0x9fe){return 230;}
        return 0;
    }
    if(i >= 0xa00 && i < 0xb80){
        if(i == 0xa3c){return 7;}
        if(i == 0xa4d){return 9;}
        if(i == 0xabc){return 7;}
        if(i == 0xacd){return 9;}
        if(i == 0xb3c){return 7;}
        if(i == 0xb4d){return 9;}
        return 0;
    }
    if(i >= 0xc00 && i < 0xe00){
        if(i == 0xc3c){return 7;}
        if(i == 0xc4d){return 9;}
        if(i == 0xc55){return 84;}
        if(i == 0xc56){return 91;}
        if(i == 0xcbc){return 7;}
        if(i == 0xccd){return 9;}
        if(i >= 0xd3b && i < 0xd3d){return 9;}
        if(i == 0xd4d){return 9;}
        if(i == 0xdca){return 9;}
        return 0;
    }
    if(i >= 0xe00 && i < 0xf00){
        if(i >= 0xe38 && i < 0xe3a){return 103;}
        if(i == 0xe3a){return 9;}
        if(i >= 0xe48 && i < 0xe4c){return 107;}
        if(i >= 0xeb8 && i < 0xeba){return 118;}
        if(i == 0xeba){return 9;}
        if(i >= 0xec8 && i < 0xecc){return 122;}
        return 0;
    }
    if(i >= 0xf00 && i < 0x1000){
        if(i >= 0xf18 && i < 0xf1a){return 220;}
        if(i == 0xf35){return 220;}
        if(i == 0xf37){return 220;}
        if(i == 0xf39){return 216;}
        if(i == 0xf71){return 129;}
        if(i == 0xf72){return 130;}
        if(i == 0xf74){return 132;}
        if(i >= 0xf7a && i < 0xf7e){return 130;}
        if(i == 0xf80){return 130;}
        if(i >= 0xf82 && i < 0xf84){return 230;}
        if(i == 0xf84){return 9;}
        if(i >= 0xf86 && i < 0xf88){return 230;}
        if(i == 0xfc6){return 220;}
        return 0;
    }
    if(i >= 0x1000 && i < 0x1100){
        if(i == 0x1037){return 7;}
        if(i >= 0x1039 && i < 0x103b){return 9;}
        if(i == 0x108d){return 220;}
        return 0;
    }
    if(i >= 0x135d && i < 0x1360){return 230;}
    if(i >= 0x1700 && i < 0x1800){
        if(i >= 0x1714 && i < 0x1716){return 9;}
        if(i == 0x1734){return 9;}
        if(i == 0x17d2){return 9;}
        if(i == 0x17dd){return 230;}
        return 0;
    }
    if(i == 0x18a9){return 228;}
    if(i >= 0x1939 && i < 0x193c){
        if(i == 0x1939){return 222;}
        if(i == 0x193a){return 230;}
        if(i == 0x193b){return 220;}
    }
    if(i >= 0x1a00 && i < 0x1b00){
        if(i == 0x1a17){return 230;}
        if(i == 0x1a18){return 220;}
        if(i == 0x1a60){return 9;}
        if(i >= 0x1a75 && i < 0x1a7d){return 230;}
        if(i == 0x1a7f){return 220;}
        if(i >= 0x1ab0 && i < 0x1ab5){return 230;}
        if(i >= 0x1ab5 && i < 0x1abb){return 220;}
        if(i >= 0x1abb && i < 0x1abd){return 230;}
        if(i == 0x1abd){return 220;}
        if(i >= 0x1abf && i < 0x1ac1){return 220;}
        if(i >= 0x1ac1 && i < 0x1ac3){return 230;}
        if(i >= 0x1ac3 && i < 0x1ac5){return 220;}
        if(i >= 0x1ac5 && i < 0x1aca){return 230;}
        if(i == 0x1aca){return 220;}
        if(i >= 0x1acb && i < 0x1add){return 230;}
        if(i == 0x1add){return 220;}
        if(i >= 0x1ae0 && i < 0x1ae6){return 230;}
        if(i == 0x1ae6){return 220;}
        if(i >= 0x1ae7 && i < 0x1aeb){return 230;}
        if(i == 0x1aeb){return 234;}
        return 0;
    }
    if(i >= 0x1b00 && i < 0x1c00){
        if(i == 0x1b34){return 7;}
        if(i == 0x1b44){return 9;}
        if(i == 0x1b6b){return 230;}
        if(i == 0x1b6c){return 220;}
        if(i >= 0x1b6d && i < 0x1b74){return 230;}
        if(i >= 0x1baa && i < 0x1bac){return 9;}
        if(i == 0x1be6){return 7;}
        if(i >= 0x1bf2 && i < 0x1bf4){return 9;}
        return 0;
    }
    if(i >= 0x1c00 && i < 0x1d00){
        if(i == 0x1c37){return 7;}
        if(i >= 0x1cd0 && i < 0x1cd3){return 230;}
        if(i == 0x1cd4){return 1;}
        if(i >= 0x1cd5 && i < 0x1cda){return 220;}
        if(i >= 0x1cda && i < 0x1cdc){return 230;}
        if(i >= 0x1cdc && i < 0x1ce0){return 220;}
        if(i == 0x1ce0){return 230;}
        if(i >= 0x1ce2 && i < 0x1ce9){return 1;}
        if(i == 0x1ced){return 220;}
        if(i == 0x1cf4){return 230;}
        if(i >= 0x1cf8 && i < 0x1cfa){return 230;}
        return 0;
    }
    if(i >= 0x1d00 && i < 0x1e00){
        if(i >= 0x1dc0 && i < 0x1dc2){return 230;}
        if(i == 0x1dc2){return 220;}
        if(i >= 0x1dc3 && i < 0x1dca){return 230;}
        if(i == 0x1dca){return 220;}
        if(i >= 0x1dcb && i < 0x1dcd){return 230;}
        if(i == 0x1dcd){return 234;}
        if(i == 0x1dce){return 214;}
        if(i == 0x1dcf){return 220;}
        if(i == 0x1dd0){return 202;}
        if(i >= 0x1dd1 && i < 0x1df6){return 230;}
        if(i == 0x1df6){return 232;}
        if(i >= 0x1df7 && i < 0x1df9){return 228;}
        if(i == 0x1df9){return 220;}
        if(i == 0x1dfa){return 218;}
        if(i == 0x1dfb){return 230;}
        if(i == 0x1dfc){return 233;}
        if(i == 0x1dfd){return 220;}
        if(i == 0x1dfe){return 230;}
        if(i == 0x1dff){return 220;}
        return 0;
    }
    if(i >= 0x20d0 && i < 0x2100){
        if(i >= 0x20d0 && i < 0x20d2){return 230;}
        if(i >= 0x20d2 && i < 0x20d4){return 1;}
        if(i >= 0x20d4 && i < 0x20d8){return 230;}
        if(i >= 0x20d8 && i < 0x20db){return 1;}
        if(i >= 0x20db && i < 0x20dd){return 230;}
        if(i == 0x20e1){return 230;}
        if(i >= 0x20e5 && i < 0x20e7){return 1;}
        if(i == 0x20e7){return 230;}
        if(i == 0x20e8){return 220;}
        if(i == 0x20e9){return 230;}
        if(i >= 0x20ea && i < 0x20ec){return 1;}
        if(i >= 0x20ec && i < 0x20f0){return 220;}
        if(i == 0x20f0){return 230;}
        return 0;
    }
    if(i >= 0x2cef && i < 0x2cf2){return 230;}
    if(i == 0x2d7f){return 9;}
    if(i >= 0x2de0 && i < 0x2e00){return 230;}
    if(i >= 0x3000 && i < 0x3100){
        if(i == 0x302a){return 218;}
        if(i == 0x302b){return 228;}
        if(i == 0x302c){return 232;}
        if(i == 0x302d){return 222;}
        if(i >= 0x302e && i < 0x3030){return 224;}
        if(i >= 0x3099 && i < 0x309b){return 8;}
        return 0;
    }
    if(i >= 0xa600 && i < 0xac00){
        if(i == 0xa66f){return 230;}
        if(i >= 0xa674 && i < 0xa67e){return 230;}
        if(i >= 0xa69e && i < 0xa6a0){return 230;}
        if(i >= 0xa6f0 && i < 0xa6f2){return 230;}
        if(i == 0xa806){return 9;}
        if(i == 0xa82c){return 9;}
        if(i == 0xa8c4){return 9;}
        if(i >= 0xa8e0 && i < 0xa8f2){return 230;}
        if(i >= 0xa92b && i < 0xa92e){return 220;}
        if(i == 0xa953){return 9;}
        if(i == 0xa9b3){return 7;}
        if(i == 0xa9c0){return 9;}
        if(i == 0xaab0){return 230;}
        if(i >= 0xaab2 && i < 0xaab4){return 230;}
        if(i == 0xaab4){return 220;}
        if(i >= 0xaab7 && i < 0xaab9){return 230;}
        if(i >= 0xaabe && i < 0xaac0){return 230;}
        if(i == 0xaac1){return 230;}
        if(i == 0xaaf6){return 9;}
        if(i == 0xabed){return 9;}
        return 0;
    }
    if(i >= 0xfb00 && i < 0xff00){
        if(i == 0xfb1e){return 26;}
        if(i >= 0xfe20 && i < 0xfe27){return 230;}
        if(i >= 0xfe27 && i < 0xfe2e){return 220;}
        if(i >= 0xfe2e && i < 0xfe30){return 230;}
        return 0;
    }
    if(i >= 0x10000 && i < 0x11000){
        if(i == 0x101fd){return 220;}
        if(i == 0x102e0){return 220;}
        if(i >= 0x10376 && i < 0x1037b){return 230;}
        if(i == 0x10a0d){return 220;}
        if(i == 0x10a0f){return 230;}
        if(i == 0x10a38){return 230;}
        if(i == 0x10a39){return 1;}
        if(i == 0x10a3a){return 220;}
        if(i == 0x10a3f){return 9;}
        if(i == 0x10ae5){return 230;}
        if(i == 0x10ae6){return 220;}
        if(i >= 0x10d24 && i < 0x10d28){return 230;}
        if(i >= 0x10d69 && i < 0x10d6e){return 230;}
        if(i >= 0x10eab && i < 0x10ead){return 230;}
        if(i >= 0x10efa && i < 0x10efc){return 220;}
        if(i >= 0x10efd && i < 0x10f00){return 220;}
        if(i >= 0x10f46 && i < 0x10f48){return 220;}
        if(i >= 0x10f48 && i < 0x10f4b){return 230;}
        if(i == 0x10f4b){return 220;}
        if(i == 0x10f4c){return 230;}
        if(i >= 0x10f4d && i < 0x10f51){return 220;}
        if(i == 0x10f82){return 230;}
        if(i == 0x10f83){return 220;}
        if(i == 0x10f84){return 230;}
        if(i == 0x10f85){return 220;}
        return 0;
    }
    if(i >= 0x11000 && i < 0x12000){
        if(i == 0x11046){return 9;}
        if(i == 0x11070){return 9;}
        if(i == 0x1107f){return 9;}
        if(i == 0x110b9){return 9;}
        if(i == 0x110ba){return 7;}
        if(i >= 0x11100 && i < 0x11103){return 230;}
        if(i >= 0x11133 && i < 0x11135){return 9;}
        if(i == 0x11173){return 7;}
        if(i == 0x111c0){return 9;}
        if(i == 0x111ca){return 7;}
        if(i == 0x11235){return 9;}
        if(i == 0x11236){return 7;}
        if(i == 0x112e9){return 7;}
        if(i == 0x112ea){return 9;}
        if(i >= 0x1133b && i < 0x1133d){return 7;}
        if(i == 0x1134d){return 9;}
        if(i >= 0x11366 && i < 0x1136d){return 230;}
        if(i >= 0x11370 && i < 0x11375){return 230;}
        if(i >= 0x113ce && i < 0x113d1){return 9;}
        if(i == 0x11442){return 9;}
        if(i == 0x11446){return 7;}
        if(i == 0x1145e){return 230;}
        if(i == 0x114c2){return 9;}
        if(i == 0x114c3){return 7;}
        if(i == 0x115bf){return 9;}
        if(i == 0x115c0){return 7;}
        if(i == 0x1163f){return 9;}
        if(i == 0x116b6){return 9;}
        if(i == 0x116b7){return 7;}
        if(i == 0x1172b){return 9;}
        if(i == 0x11839){return 9;}
        if(i == 0x1183a){return 7;}
        if(i >= 0x1193d && i < 0x1193f){return 9;}
        if(i == 0x11943){return 7;}
        if(i == 0x119e0){return 9;}
        if(i == 0x11a34){return 9;}
        if(i == 0x11a47){return 9;}
        if(i == 0x11a99){return 9;}
        if(i == 0x11c3f){return 9;}
        if(i == 0x11d42){return 7;}
        if(i >= 0x11d44 && i < 0x11d46){return 9;}
        if(i == 0x11d97){return 9;}
        if(i >= 0x11f41 && i < 0x11f43){return 9;}
        return 0;
    }
    if(i >= 0x16000 && i < 0x17000){
        if(i == 0x1612f){return 9;}
        if(i >= 0x16af0 && i < 0x16af5){return 1;}
        if(i >= 0x16b30 && i < 0x16b37){return 230;}
        if(i >= 0x16ff0 && i < 0x16ff2){return 6;}
        return 0;
    }
    if(i == 0x1bc9e){return 1;}
    if(i >= 0x1d000 && i < 0x1e000){
        if(i >= 0x1d165 && i < 0x1d167){return 216;}
        if(i >= 0x1d167 && i < 0x1d16a){return 1;}
        if(i == 0x1d16d){return 226;}
        if(i >= 0x1d16e && i < 0x1d173){return 216;}
        if(i >= 0x1d17b && i < 0x1d183){return 220;}
        if(i >= 0x1d185 && i < 0x1d18a){return 230;}
        if(i >= 0x1d18a && i < 0x1d18c){return 220;}
        if(i >= 0x1d1aa && i < 0x1d1ae){return 230;}
        if(i >= 0x1d242 && i < 0x1d245){return 230;}
        return 0;
    }
    if(i >= 0x1e000 && i < 0x1f000){
        if(i >= 0x1e000 && i < 0x1e007){return 230;}
        if(i >= 0x1e008 && i < 0x1e019){return 230;}
        if(i >= 0x1e01b && i < 0x1e022){return 230;}
        if(i >= 0x1e023 && i < 0x1e025){return 230;}
        if(i >= 0x1e026 && i < 0x1e02b){return 230;}
        if(i == 0x1e08f){return 230;}
        if(i >= 0x1e130 && i < 0x1e137){return 230;}
        if(i == 0x1e2ae){return 230;}
        if(i >= 0x1e2ec && i < 0x1e2f0){return 230;}
        if(i >= 0x1e4ec && i < 0x1e4ee){return 232;}
        if(i == 0x1e4ee){return 220;}
        if(i == 0x1e4ef){return 230;}
        if(i == 0x1e5ee){return 230;}
        if(i == 0x1e5ef){return 220;}
        if(i == 0x1e6e3){return 230;}
        if(i == 0x1e6e6){return 230;}
        if(i >= 0x1e6ee && i < 0x1e6f0){return 230;}
        if(i == 0x1e6f5){return 230;}
        if(i >= 0x1e8d0 && i < 0x1e8d7){return 220;}
        if(i >= 0x1e944 && i < 0x1e94a){return 230;}
        if(i == 0x1e94a){return 7;}
        return 0;
    }
    return 0;
}

void checkMarkOrder(int end){
    for(int i=0; i<=end; i++){
        if(markOrderStorage.at(i) != getUnicodeCombiningMarkOrder(i)){
            qDebug() << QString::number(i, 16) << markOrderStorage.at(i) << getUnicodeCombiningMarkOrder(i);
        }
    }
}