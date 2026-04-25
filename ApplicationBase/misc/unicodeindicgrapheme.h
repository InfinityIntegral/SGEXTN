#include <QString>
#include <QFile>
#include <QVector>
#include <QMap>
#include <QDebug>

QVector<bool> propertyStorage;

void parseFile(const QString& s){
    propertyStorage = QVector<bool>();
    for(int i=0; i<=0x10ffff; i++){
        propertyStorage.push_back(false);
    }
    QString dataString = "";
    QFile file("../ApplicationBase/misc/unicodeindicgrapheme.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        dataString = file.readAll();
        file.close();
    }
    QVector<QString> characters = dataString.split('\n');
    for(int i=0; i<characters.length(); i++){
        if(characters.at(i).contains(s) == false){continue;}
        characters[i] = characters.at(i).left(characters.at(i).indexOf(';')).trimmed();
        if(characters.at(i).contains("..")){
            int startCodePoint = characters.at(i).left(characters.at(i).indexOf("..")).toInt(nullptr, 16);
            int endCodePoint = characters.at(i).right(characters.at(i).length() - characters.at(i).indexOf("..") - 2).toInt(nullptr, 16);
            for(int j=startCodePoint; j<=endCodePoint; j++){
                propertyStorage[j] = true;
            }
        }
        else{
            int codePoint = characters.at(i).toInt(nullptr, 16);
            propertyStorage[codePoint] = true;
        }
    }
}

void printInfo(int start){
    int rangeStart = -1;
    for(int i=start; i<=0x10ffff; i++){
        if(propertyStorage.at(i) == true && rangeStart == -1){rangeStart = i;}
        if(propertyStorage.at(i) == false && rangeStart != -1){
            qDebug().noquote() << QString::number(i - rangeStart) << QString::number(rangeStart, 16) << QString::number(i - 1, 16);
            rangeStart = -1;
        }
    }
}

bool isUnicodeIndicGraphemeConsonant(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i >= 0x900 && i <= 0x9ff){
        if(i >= 0x915 && i <= 0x939){return true;}
        if(i >= 0x958 && i <= 0x95f){return true;}
        if(i >= 0x978 && i <= 0x97f){return true;}
        if(i >= 0x995 && i <= 0x9a8){return true;}
        if(i >= 0x9aa && i <= 0x9b0){return true;}
        if(i == 0x9b2){return true;}
        if(i >= 0x9b6 && i <= 0x9b9){return true;}
        if(i >= 0x9dc && i <= 0x9dd){return true;}
        if(i == 0x9df){return true;}
        if(i >= 0x9f0 && i <= 0x9f1){return true;}
    }
    if(i >= 0xa90 && i <= 0xaff){
        if(i >= 0xa95 && i <= 0xaa8){return true;}
        if(i >= 0xaaa && i <= 0xab0){return true;}
        if(i >= 0xab2 && i <= 0xab3){return true;}
        if(i >= 0xab5 && i <= 0xab9){return true;}
        if(i == 0xaf9){return true;}
    }
    if(i >= 0xb00 && i <= 0xb80){
        if(i >= 0xb15 && i <= 0xb28){return true;}
        if(i >= 0xb2a && i <= 0xb30){return true;}
        if(i >= 0xb32 && i <= 0xb33){return true;}
        if(i >= 0xb35 && i <= 0xb39){return true;}
        if(i >= 0xb5c && i <= 0xb5d){return true;}
        if(i == 0xb5f){return true;}
        if(i == 0xb71){return true;}
    }
    if(i >= 0xc00 && i <= 0xc8f){
        if(i >= 0xc15 && i <= 0xc28){return true;}
        if(i >= 0xc2a && i <= 0xc39){return true;}
        if(i >= 0xc58 && i <= 0xc5a){return true;}
    }
    if(i >= 0xd15 && i <= 0xd3a){return true;}
    if(i >= 0x1000 && i <= 0x108f){
        if(i >= 0x1000 && i <= 0x102a){return true;}
        if(i == 0x103f){return true;}
        if(i >= 0x1050 && i <= 0x1055){return true;}
        if(i >= 0x105a && i <= 0x105d){return true;}
        if(i == 0x1061){return true;}
        if(i >= 0x1065 && i <= 0x1066){return true;}
        if(i >= 0x106e && i <= 0x1070){return true;}
        if(i >= 0x1075 && i <= 0x1081){return true;}
        if(i == 0x108e){return true;}
    }
    if(i >= 0x1780 && i <= 0x17b3){return true;}
    if(i >= 0x1a20 && i <= 0x1a54){return true;}
    if(i >= 0x1b00 && i <= 0x1bff){
        if(i >= 0x1b0b && i <= 0x1b0c){return true;}
        if(i >= 0x1b13 && i <= 0x1b33){return true;}
        if(i >= 0x1b45 && i <= 0x1b4c){return true;}
        if(i >= 0x1b83 && i <= 0x1ba0){return true;}
        if(i >= 0x1bae && i <= 0x1baf){return true;}
        if(i >= 0x1bbb && i <= 0x1bbd){return true;}
    }
    if(i >= 0xa980 && i <= 0xa9ff){
        if(i >= 0xa989 && i <= 0xa98b){return true;}
        if(i >= 0xa98f && i <= 0xa9b2){return true;}
        if(i >= 0xa9e0 && i <= 0xa9e4){return true;}
        if(i >= 0xa9e7 && i <= 0xa9ef){return true;}
        if(i >= 0xa9fa && i <= 0xa9fe){return true;}
    }
    if(i >= 0xaa60 && i <= 0xaaff){
        if(i >= 0xaa60 && i <= 0xaa6f){return true;}
        if(i >= 0xaa71 && i <= 0xaa73){return true;}
        if(i == 0xaa7a){return true;}
        if(i >= 0xaa7e && i <= 0xaa7f){return true;}
        if(i >= 0xaae0 && i <= 0xaaea){return true;}
    }
    if(i >= 0xabc0 && i <= 0xabda){return true;}
    if(i >= 0x10a00 && i <= 0x10a3f){
        if(i == 0x10a00){return true;}
        if(i >= 0x10a10 && i <= 0x10a13){return true;}
        if(i >= 0x10a15 && i <= 0x10a17){return true;}
        if(i >= 0x10a19 && i <= 0x10a35){return true;}
    }
    if(i >= 0x11100 && i <= 0x1114f){
        if(i >= 0x11103 && i <= 0x11126){return true;}
        if(i == 0x11144){return true;}
        if(i == 0x11147){return true;}
    }
    if(i >= 0x11380 && i <= 0x113bf){
        if(i >= 0x11380 && i <= 0x11389){return true;}
        if(i == 0x1138b){return true;}
        if(i == 0x1138e){return true;}
        if(i >= 0x11390 && i <= 0x113b5){return true;}
    }
    if(i >= 0x11900 && i <= 0x1192f){
        if(i >= 0x11900 && i <= 0x11906){return true;}
        if(i == 0x11909){return true;}
        if(i >= 0x1190c && i <= 0x11913){return true;}
        if(i >= 0x11915 && i <= 0x11916){return true;}
        if(i >= 0x11918 && i <= 0x1192f){return true;}
    }
    if(i >= 0x11a00 && i <= 0x11aff){
        if(i == 0x11a00){return true;}
        if(i >= 0x11a0b && i <= 0x11a32){return true;}
        if(i == 0x11a50){return true;}
        if(i >= 0x11a5c && i <= 0x11a83){return true;}
    }
    if(i >= 0x11f00 && i <= 0x11f3f){
        if(i >= 0x11f04 && i <= 0x11f10){return true;}
        if(i >= 0x11f12 && i <= 0x11f33){return true;}
    }
    return false;
}

bool isUnicodeIndicGraphemeLinker(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i == 0x94d || i == 0x9cd){return true;}
    if(i == 0xacd){return true;}
    if(i == 0xb4d){return true;}
    if(i == 0xc4d){return true;}
    if(i == 0xd4d){return true;}
    if(i == 0x1039){return true;}
    if(i == 0x17d2){return true;}
    if(i == 0x1a60){return true;}
    if(i == 0x1b44 || i == 0x1bab){return true;}
    if(i == 0xa9c0){return true;}
    if(i == 0xaaf6){return true;}
    if(i == 0x10a3f){return true;}
    if(i == 0x11133 || i == 0x113d0){return true;}
    if(i == 0x1193e){return true;}
    if(i == 0x11a47 || i == 0x11a99){return true;}
    if(i == 0x11f42){return true;}
    return false;
}

bool isUnicodeIndicGraphemeExtend(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){
        if(i == 0xb82 || i == 0xbbe || i == 0xbc0 || i == 0xbcd || i == 0xbd7){return true;}
        return false;
    }
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i >= 0x300 && i <= 0x36f){return true;}
    if(i >= 0x483 && i <= 0x489){return true;}
    if(i >= 0x590 && i <= 0x5cf){
        if(i >= 0x591 && i <= 0x5bd){return true;}
        if(i == 0x5bf){return true;}
        if(i >= 0x5c1 && i <= 0x5c2){return true;}
        if(i >= 0x5c4 && i <= 0x5c5){return true;}
        if(i == 0x5c7){return true;}
    }
    if(i >= 0x600 && i <= 0x6ff){
        if(i >= 0x610 && i <= 0x61a){return true;}
        if(i >= 0x64b && i <= 0x65f){return true;}
        if(i == 0x670){return true;}
        if(i >= 0x6d6 && i <= 0x6dc){return true;}
        if(i >= 0x6df && i <= 0x6e4){return true;}
        if(i >= 0x6e7 && i <= 0x6e8){return true;}
        if(i >= 0x6ea && i <= 0x6ed){return true;}
    }
    if(i >= 0x700 && i <= 0x7ff){
        if(i == 0x711){return true;}
        if(i >= 0x730 && i <= 0x74a){return true;}
        if(i >= 0x7a6 && i <= 0x7b0){return true;}
        if(i >= 0x7eb && i <= 0x7f3){return true;}
        if(i == 0x7fd){return true;}
    }
    if(i >= 0x800 && i <= 0x8ff){
        if(i >= 0x816 && i <= 0x819){return true;}
        if(i >= 0x81b && i <= 0x823){return true;}
        if(i >= 0x825 && i <= 0x827){return true;}
        if(i >= 0x829 && i <= 0x82d){return true;}
        if(i >= 0x859 && i <= 0x85b){return true;}
        if(i >= 0x897 && i <= 0x89f){return true;}
        if(i >= 0x8ca && i <= 0x8e1){return true;}
        if(i >= 0x8e3 && i <= 0x8ff){return true;}
    }
    if(i >= 0x900 && i <= 0x97f){
        if(i >= 0x900 && i <= 0x902){return true;}
        if(i == 0x93a){return true;}
        if(i == 0x93c){return true;}
        if(i >= 0x941 && i <= 0x948){return true;}
        if(i >= 0x951 && i <= 0x957){return true;}
        if(i >= 0x962 && i <= 0x963){return true;}
    }
    if(i >= 0x980 && i <= 0x9ff){
        if(i == 0x981){return true;}
        if(i == 0x9bc){return true;}
        if(i == 0x9be){return true;}
        if(i >= 0x9c1 && i <= 0x9c4){return true;}
        if(i == 0x9d7){return true;}
        if(i >= 0x9e2 && i <= 0x9e3){return true;}
        if(i == 0x9fe){return true;}
    }
    if(i >= 0xa00 && i <= 0xa7f){
        if(i >= 0xa01 && i <= 0xa02){return true;}
        if(i == 0xa3c){return true;}
        if(i >= 0xa41 && i <= 0xa42){return true;}
        if(i >= 0xa47 && i <= 0xa48){return true;}
        if(i >= 0xa4b && i <= 0xa4d){return true;}
        if(i == 0xa51){return true;}
        if(i >= 0xa70 && i <= 0xa71){return true;}
        if(i == 0xa75){return true;}
    }
    if(i >= 0xa80 && i <= 0xaff){
        if(i >= 0xa81 && i <= 0xa82){return true;}
        if(i == 0xabc){return true;}
        if(i >= 0xac1 && i <= 0xac5){return true;}
        if(i >= 0xac7 && i <= 0xac8){return true;}
        if(i >= 0xae2 && i <= 0xae3){return true;}
        if(i >= 0xafa && i <= 0xaff){return true;}
    }
    if(i >= 0xb00 && i <= 0xb7f){
        if(i == 0xb01){return true;}
        if(i == 0xb3c){return true;}
        if(i >= 0xb3e && i <= 0xb3f){return true;}
        if(i >= 0xb41 && i <= 0xb44){return true;}
        if(i >= 0xb55 && i <= 0xb57){return true;}
        if(i >= 0xb62 && i <= 0xb63){return true;}
    }
    if(i >= 0xc00 && i <= 0xc7f){
        if(i == 0xc00){return true;}
        if(i == 0xc04){return true;}
        if(i == 0xc3c){return true;}
        if(i >= 0xc3e && i <= 0xc40){return true;}
        if(i >= 0xc46 && i <= 0xc48){return true;}
        if(i >= 0xc4a && i <= 0xc4c){return true;}
        if(i >= 0xc55 && i <= 0xc56){return true;}
        if(i >= 0xc62 && i <= 0xc63){return true;}
    }
    if(i >= 0xc80 && i <= 0xcff){
        if(i == 0xc81){return true;}
        if(i == 0xcbc){return true;}
        if(i >= 0xcbf && i <= 0xcc0){return true;}
        if(i == 0xcc2){return true;}
        if(i >= 0xcc6 && i <= 0xcc8){return true;}
        if(i >= 0xcca && i <= 0xccd){return true;}
        if(i >= 0xcd5 && i <= 0xcd6){return true;}
        if(i >= 0xce2 && i <= 0xce3){return true;}
    }
    if(i >= 0xd00 && i <= 0xd7f){
        if(i >= 0xd00 && i <= 0xd01){return true;}
        if(i >= 0xd3b && i <= 0xd3c){return true;}
        if(i == 0xd3e){return true;}
        if(i >= 0xd41 && i <= 0xd44){return true;}
        if(i == 0xd57){return true;}
        if(i >= 0xd62 && i <= 0xd63){return true;}
    }
    if(i >= 0xd80 && i <= 0xdff){
        if(i == 0xd81){return true;}
        if(i == 0xdca){return true;}
        if(i == 0xdcf){return true;}
        if(i >= 0xdd2 && i <= 0xdd4){return true;}
        if(i == 0xdd6){return true;}
        if(i == 0xddf){return true;}
    }
    if(i >= 0xe00 && i <= 0xe7f){
        if(i == 0xe31){return true;}
        if(i >= 0xe34 && i <= 0xe3a){return true;}
        if(i >= 0xe47 && i <= 0xe4e){return true;}
    }
    if(i >= 0xe80 && i <= 0xeff){
        if(i == 0xeb1){return true;}
        if(i >= 0xeb4 && i <= 0xebc){return true;}
        if(i >= 0xec8 && i <= 0xece){return true;}
    }
    if(i >= 0xf00 && i <= 0xfff){
        if(i >= 0xf18 && i <= 0xf19){return true;}
        if(i == 0xf35){return true;}
        if(i == 0xf37){return true;}
        if(i == 0xf39){return true;}
        if(i >= 0xf71 && i <= 0xf7e){return true;}
        if(i >= 0xf80 && i <= 0xf84){return true;}
        if(i >= 0xf86 && i <= 0xf87){return true;}
        if(i >= 0xf8d && i <= 0xf97){return true;}
        if(i >= 0xf99 && i <= 0xfbc){return true;}
        if(i == 0xfc6){return true;}
    }
    if(i >= 0x1000 && i <= 0x109f){
        if(i >= 0x102d && i <= 0x1030){return true;}
        if(i >= 0x1032 && i <= 0x1037){return true;}
        if(i == 0x103a){return true;}
        if(i >= 0x103d && i <= 0x103e){return true;}
        if(i >= 0x1058 && i <= 0x1059){return true;}
        if(i >= 0x105e && i <= 0x1060){return true;}
        if(i >= 0x1071 && i <= 0x1074){return true;}
        if(i == 0x1082){return true;}
        if(i >= 0x1085 && i <= 0x1086){return true;}
        if(i == 0x108d){return true;}
        if(i == 0x109d){return true;}
    }
    if(i >= 0x135d && i <= 0x135f){return true;}
    if(i >= 0x1700 && i <= 0x17ff){
        if(i >= 0x1712 && i <= 0x1715){return true;}
        if(i >= 0x1732 && i <= 0x1734){return true;}
        if(i >= 0x1752 && i <= 0x1753){return true;}
        if(i >= 0x1772 && i <= 0x1773){return true;}
        if(i >= 0x17b4 && i <= 0x17b5){return true;}
        if(i >= 0x17b7 && i <= 0x17bd){return true;}
        if(i == 0x17c6){return true;}
        if(i >= 0x17c9 && i <= 0x17d1){return true;}
        if(i == 0x17d3){return true;}
        if(i == 0x17dd){return true;}
    }
    if(i >= 0x1800 && i <= 0x18af){
        if(i >= 0x180b && i <= 0x180d){return true;}
        if(i == 0x180f){return true;}
        if(i >= 0x1885 && i <= 0x1886){return true;}
        if(i == 0x18a9){return true;}
    }
    if(i >= 0x1920 && i <= 0x193f){
        if(i >= 0x1920 && i <= 0x1922){return true;}
        if(i >= 0x1927 && i <= 0x1928){return true;}
        if(i == 0x1932){return true;}
        if(i >= 0x1939 && i <= 0x193b){return true;}
    }
    if(i >= 0x1a00 && i <= 0x1aff){
        if(i >= 0x1a17 && i <= 0x1a18){return true;}
        if(i == 0x1a1b){return true;}
        if(i == 0x1a56){return true;}
        if(i >= 0x1a58 && i <= 0x1a5e){return true;}
        if(i == 0x1a62){return true;}
        if(i >= 0x1a65 && i <= 0x1a6c){return true;}
        if(i >= 0x1a73 && i <= 0x1a7c){return true;}
        if(i == 0x1a7f){return true;}
        if(i >= 0x1ab0 && i <= 0x1add){return true;}
        if(i >= 0x1ae0 && i <= 0x1aeb){return true;}
    }
    if(i >= 0x1b00 && i <= 0x1bff){
        if(i >= 0x1b00 && i <= 0x1b03){return true;}
        if(i >= 0x1b34 && i <= 0x1b3d){return true;}
        if(i >= 0x1b42 && i <= 0x1b43){return true;}
        if(i >= 0x1b6b && i <= 0x1b73){return true;}
        if(i >= 0x1b80 && i <= 0x1b81){return true;}
        if(i >= 0x1ba2 && i <= 0x1ba5){return true;}
        if(i >= 0x1ba8 && i <= 0x1baa){return true;}
        if(i >= 0x1bac && i <= 0x1bad){return true;}
        if(i == 0x1be6){return true;}
        if(i >= 0x1be8 && i <= 0x1be9){return true;}
        if(i == 0x1bed){return true;}
        if(i >= 0x1bef && i <= 0x1bf3){return true;}
    }
    if(i >= 0x1c00 && i <= 0x1cff){
        if(i >= 0x1c2c && i <= 0x1c33){return true;}
        if(i >= 0x1c36 && i <= 0x1c37){return true;}
        if(i >= 0x1cd0 && i <= 0x1cd2){return true;}
        if(i >= 0x1cd4 && i <= 0x1ce0){return true;}
        if(i >= 0x1ce2 && i <= 0x1ce8){return true;}
        if(i == 0x1ced){return true;}
        if(i == 0x1cf4){return true;}
        if(i >= 0x1cf8 && i <= 0x1cf9){return true;}
    }
    if(i >= 0x1dc0 && i <= 0x1dff){return true;}
    if(i == 0x200d){return true;}
    if(i >= 0x20d0 && i <= 0x20f0){return true;}
    if(i >= 0x2cef && i <= 0x2cf1){return true;}
    if(i == 0x2d7f){return true;}
    if(i >= 0x2de0 && i <= 0x2dff){return true;}
    if(i >= 0x302a && i <= 0x302f){return true;}
    if(i >= 0x3099 && i <= 0x309a){return true;}
    if(i >= 0xa660 && i <= 0xa6ff){
        if(i >= 0xa66f && i <= 0xa672){return true;}
        if(i >= 0xa674 && i <= 0xa67d){return true;}
        if(i >= 0xa69e && i <= 0xa69f){return true;}
        if(i >= 0xa6f0 && i <= 0xa6f1){return true;}
    }
    if(i >= 0xa800 && i <= 0xa8ff){
        if(i == 0xa802){return true;}
        if(i == 0xa806){return true;}
        if(i == 0xa80b){return true;}
        if(i >= 0xa825 && i <= 0xa826){return true;}
        if(i == 0xa82c){return true;}
        if(i >= 0xa8c4 && i <= 0xa8c5){return true;}
        if(i >= 0xa8e0 && i <= 0xa8f1){return true;}
        if(i == 0xa8ff){return true;}
    }
    if(i >= 0xa900 && i <= 0xa9ff){
        if(i >= 0xa926 && i <= 0xa92d){return true;}
        if(i >= 0xa947 && i <= 0xa951){return true;}
        if(i == 0xa953){return true;}
        if(i >= 0xa980 && i <= 0xa982){return true;}
        if(i == 0xa9b3){return true;}
        if(i >= 0xa9b6 && i <= 0xa9b9){return true;}
        if(i >= 0xa9bc && i <= 0xa9bd){return true;}
        if(i == 0xa9e5){return true;}
    }
    if(i >= 0xaa00 && i <= 0xaaff){
        if(i >= 0xaa29 && i <= 0xaa2e){return true;}
        if(i >= 0xaa31 && i <= 0xaa32){return true;}
        if(i >= 0xaa35 && i <= 0xaa36){return true;}
        if(i == 0xaa43){return true;}
        if(i == 0xaa4c){return true;}
        if(i == 0xaa7c){return true;}
        if(i == 0xaab0){return true;}
        if(i >= 0xaab2 && i <= 0xaab4){return true;}
        if(i >= 0xaab7 && i <= 0xaab8){return true;}
        if(i >= 0xaabe && i <= 0xaabf){return true;}
        if(i == 0xaac1){return true;}
        if(i >= 0xaaec && i <= 0xaaed){return true;}
    }
    if(i >= 0xabe0 && i <= 0xabef){
        if(i == 0xabe5){return true;}
        if(i == 0xabe8){return true;}
        if(i == 0xabed){return true;}
    }
    if(i == 0xfb1e){return true;}
    if(i >= 0xfe00 && i <= 0xfe0f){return true;}
    if(i >= 0xfe20 && i <= 0xfe2f){return true;}
    if(i >= 0xff9e && i <= 0xff9f){return true;}
    if(i >= 0x10000 && i <= 0x10fff){
        if(i == 0x101fd){return true;}
        if(i == 0x102e0){return true;}
        if(i >= 0x10376 && i <= 0x1037a){return true;}
        if(i >= 0x10a01 && i <= 0x10a03){return true;}
        if(i >= 0x10a05 && i <= 0x10a06){return true;}
        if(i >= 0x10a0c && i <= 0x10a0f){return true;}
        if(i >= 0x10a38 && i <= 0x10a3a){return true;}
        if(i >= 0x10ae5 && i <= 0x10ae6){return true;}
        if(i >= 0x10d24 && i <= 0x10d27){return true;}
        if(i >= 0x10d69 && i <= 0x10d6d){return true;}
        if(i >= 0x10eab && i <= 0x10eac){return true;}
        if(i >= 0x10efa && i <= 0x10eff){return true;}
        if(i >= 0x10f46 && i <= 0x10f50){return true;}
        if(i >= 0x10f82 && i <= 0x10f85){return true;}
    }
    if(i >= 0x11000 && i <= 0x11fff){
        if(i >= 0x11000 && i <= 0x110ff){
            if(i == 0x11001){return true;}
            if(i >= 0x11038 && i <= 0x11046){return true;}
            if(i == 0x11070){return true;}
            if(i >= 0x11073 && i <= 0x11074){return true;}
            if(i >= 0x1107f && i <= 0x11081){return true;}
            if(i >= 0x110b3 && i <= 0x110b6){return true;}
            if(i >= 0x110b9 && i <= 0x110ba){return true;}
            if(i == 0x110c2){return true;}
        }
        if(i >= 0x11100 && i <= 0x111ff){
            if(i >= 0x11100 && i <= 0x11102){return true;}
            if(i >= 0x11127 && i <= 0x1112b){return true;}
            if(i >= 0x1112d && i <= 0x11132){return true;}
            if(i == 0x11134){return true;}
            if(i == 0x11173){return true;}
            if(i >= 0x11180 && i <= 0x11181){return true;}
            if(i >= 0x111b6 && i <= 0x111be){return true;}
            if(i == 0x111c0){return true;}
            if(i >= 0x111c9 && i <= 0x111cc){return true;}
            if(i == 0x111cf){return true;}
        }
        if(i >= 0x11200 && i <= 0x112ff){
            if(i >= 0x1122f && i <= 0x11231){return true;}
            if(i >= 0x11234 && i <= 0x11237){return true;}
            if(i == 0x1123e){return true;}
            if(i == 0x11241){return true;}
            if(i == 0x112df){return true;}
            if(i >= 0x112e3 && i <= 0x112ea){return true;}
        }
        if(i >= 0x11300 && i <= 0x113ff){
            if(i >= 0x11300 && i <= 0x11301){return true;}
            if(i >= 0x1133b && i <= 0x1133c){return true;}
            if(i == 0x1133e){return true;}
            if(i == 0x11340){return true;}
            if(i == 0x1134d){return true;}
            if(i == 0x11357){return true;}
            if(i >= 0x11366 && i <= 0x1136c){return true;}
            if(i >= 0x11370 && i <= 0x11374){return true;}
            if(i == 0x113b8){return true;}
            if(i >= 0x113bb && i <= 0x113c0){return true;}
            if(i == 0x113c2){return true;}
            if(i == 0x113c5){return true;}
            if(i >= 0x113c7 && i <= 0x113c9){return true;}
            if(i >= 0x113ce && i <= 0x113cf){return true;}
            if(i == 0x113d2){return true;}
            if(i >= 0x113e1 && i <= 0x113e2){return true;}
        }
        if(i >= 0x11400 && i <= 0x114ff){
            if(i >= 0x11438 && i <= 0x1143f){return true;}
            if(i >= 0x11442 && i <= 0x11444){return true;}
            if(i == 0x11446){return true;}
            if(i == 0x1145e){return true;}
            if(i == 0x114b0){return true;}
            if(i >= 0x114b3 && i <= 0x114b8){return true;}
            if(i == 0x114ba){return true;}
            if(i == 0x114bd){return true;}
            if(i >= 0x114bf && i <= 0x114c0){return true;}
            if(i >= 0x114c2 && i <= 0x114c3){return true;}
        }
        if(i >= 0x115a0 && i <= 0x115ff){
            if(i == 0x115af){return true;}
            if(i >= 0x115b2 && i <= 0x115b5){return true;}
            if(i >= 0x115bc && i <= 0x115bd){return true;}
            if(i >= 0x115bf && i <= 0x115c0){return true;}
            if(i >= 0x115dc && i <= 0x115dd){return true;}
        }
        if(i >= 0x11600 && i <= 0x116ff){
            if(i >= 0x11633 && i <= 0x1163a){return true;}
            if(i == 0x1163d){return true;}
            if(i >= 0x1163f && i <= 0x11640){return true;}
            if(i == 0x116ab){return true;}
            if(i == 0x116ad){return true;}
            if(i >= 0x116b0 && i <= 0x116b7){return true;}
        }
        if(i >= 0x11710 && i <= 0x1172f){
            if(i == 0x1171d){return true;}
            if(i == 0x1171f){return true;}
            if(i >= 0x11722 && i <= 0x11725){return true;}
            if(i >= 0x11727 && i <= 0x1172b){return true;}
        }
        if(i >= 0x11820 && i <= 0x1183f){
            if(i >= 0x1182f && i <= 0x11837){return true;}
            if(i >= 0x11839 && i <= 0x1183a){return true;}
        }
        if(i >= 0x11900 && i <= 0x119ff){
            if(i == 0x11930){return true;}
            if(i >= 0x1193b && i <= 0x1193d){return true;}
            if(i == 0x11943){return true;}
            if(i >= 0x119d4 && i <= 0x119d7){return true;}
            if(i >= 0x119da && i <= 0x119db){return true;}
            if(i == 0x119e0){return true;}
        }
        if(i >= 0x11a00 && i <= 0x11aff){
            if(i >= 0x11a01 && i <= 0x11a0a){return true;}
            if(i >= 0x11a33 && i <= 0x11a38){return true;}
            if(i >= 0x11a3b && i <= 0x11a3e){return true;}
            if(i >= 0x11a51 && i <= 0x11a56){return true;}
            if(i >= 0x11a59 && i <= 0x11a5b){return true;}
            if(i >= 0x11a8a && i <= 0x11a96){return true;}
            if(i == 0x11a98){return true;}
        }
        if(i >= 0x11b60 && i <= 0x11b6f){
            if(i == 0x11b60){return true;}
            if(i >= 0x11b62 && i <= 0x11b64){return true;}
            if(i == 0x11b66){return true;}
        }
        if(i >= 0x11c00 && i <= 0x11cff){
            if(i >= 0x11c30 && i <= 0x11c36){return true;}
            if(i >= 0x11c38 && i <= 0x11c3d){return true;}
            if(i == 0x11c3f){return true;}
            if(i >= 0x11c92 && i <= 0x11ca7){return true;}
            if(i >= 0x11caa && i <= 0x11cb0){return true;}
            if(i >= 0x11cb2 && i <= 0x11cb3){return true;}
            if(i >= 0x11cb5 && i <= 0x11cb6){return true;}
        }
        if(i >= 0x11d00 && i <= 0x11dff){
            if(i >= 0x11d31 && i <= 0x11d36){return true;}
            if(i == 0x11d3a){return true;}
            if(i >= 0x11d3c && i <= 0x11d3d){return true;}
            if(i >= 0x11d3f && i <= 0x11d45){return true;}
            if(i == 0x11d47){return true;}
            if(i >= 0x11d90 && i <= 0x11d91){return true;}
            if(i == 0x11d95){return true;}
            if(i == 0x11d97){return true;}
        }
        if(i >= 0x11ef3 && i <= 0x11ef4){return true;}
        if(i >= 0x11f00 && i <= 0x11fff){
            if(i >= 0x11f00 && i <= 0x11f01){return true;}
            if(i >= 0x11f36 && i <= 0x11f3a){return true;}
            if(i >= 0x11f40 && i <= 0x11f41){return true;}
            if(i == 0x11f5a){return true;}
        }
    }
    if(i >= 0x13400 && i <= 0x134ff){
        if(i == 0x13440){return true;}
        if(i >= 0x13447 && i <= 0x13455){return true;}
    }
    if(i >= 0x16000 && i <= 0x16fff){
        if(i >= 0x1611e && i <= 0x16129){return true;}
        if(i >= 0x1612d && i <= 0x1612f){return true;}
        if(i >= 0x16af0 && i <= 0x16af4){return true;}
        if(i >= 0x16b30 && i <= 0x16b36){return true;}
        if(i == 0x16f4f){return true;}
        if(i >= 0x16f8f && i <= 0x16f92){return true;}
        if(i == 0x16fe4){return true;}
        if(i >= 0x16ff0 && i <= 0x16ff1){return true;}
    }
    if(i >= 0x1bc9d && i <= 0x1bc9e){return true;}
    if(i >= 0x1cf00 && i <= 0x1cf2d){return true;}
    if(i >= 0x1cf30 && i <= 0x1cf46){return true;}
    if(i >= 0x1d000 && i <= 0x1dfff){
        if(i >= 0x1d165 && i <= 0x1d169){return true;}
        if(i >= 0x1d16d && i <= 0x1d172){return true;}
        if(i >= 0x1d17b && i <= 0x1d182){return true;}
        if(i >= 0x1d185 && i <= 0x1d18b){return true;}
        if(i >= 0x1d1aa && i <= 0x1d1ad){return true;}
        if(i >= 0x1d242 && i <= 0x1d244){return true;}
        if(i >= 0x1da00 && i <= 0x1da36){return true;}
        if(i >= 0x1da3b && i <= 0x1da6c){return true;}
        if(i == 0x1da75){return true;}
        if(i == 0x1da84){return true;}
        if(i >= 0x1da9b && i <= 0x1da9f){return true;}
        if(i >= 0x1daa1 && i <= 0x1daaf){return true;}
    }
    if(i >= 0x1e000 && i <= 0x1efff){
        if(i >= 0x1e000 && i <= 0x1e006){return true;}
        if(i >= 0x1e008 && i <= 0x1e018){return true;}
        if(i >= 0x1e01b && i <= 0x1e021){return true;}
        if(i >= 0x1e023 && i <= 0x1e024){return true;}
        if(i >= 0x1e026 && i <= 0x1e02a){return true;}
        if(i == 0x1e08f){return true;}
        if(i >= 0x1e130 && i <= 0x1e136){return true;}
        if(i == 0x1e2ae){return true;}
        if(i >= 0x1e2ec && i <= 0x1e2ef){return true;}
        if(i >= 0x1e4ec && i <= 0x1e4ef){return true;}
        if(i >= 0x1e5ee && i <= 0x1e5ef){return true;}
        if(i == 0x1e6e3){return true;}
        if(i == 0x1e6e6){return true;}
        if(i >= 0x1e6ee && i <= 0x1e6ef){return true;}
        if(i == 0x1e6f5){return true;}
        if(i >= 0x1e8d0 && i <= 0x1e8d6){return true;}
        if(i >= 0x1e944 && i <= 0x1e94a){return true;}
    }
    if(i >= 0x1f3fb && i <= 0x1f3ff){return true;}
    if(i >= 0xe0020 && i <= 0xe007f){return true;}
    if(i >= 0xe0100 && i <= 0xe01ef){return true;}
    return false;
}

void printEverything(int start1, int start2, int start3){
    qDebug() << "consonant";
    parseFile("; InCB; Consonant #");
    printInfo(start1);
    qDebug() << "linker";
    parseFile("; InCB; Linker #");
    printInfo(start2);
    qDebug() << "extend";
    parseFile("; InCB; Extend #");
    printInfo(start3);
}

void checkEverything(int end){
    qDebug().noquote() << "consonant";
    parseFile("; InCB; Consonant #");
    for(int i=0; i<=end; i++){
        bool received = isUnicodeIndicGraphemeConsonant(i);
        bool expected = propertyStorage.at(i);
        if(received != expected){qDebug().noquote() << QString::number(i, 16) << expected << received;}
    }
    qDebug().noquote() << "linker";
    parseFile("; InCB; Linker #");
    for(int i=0; i<=end; i++){
        bool received = isUnicodeIndicGraphemeLinker(i);
        bool expected = propertyStorage.at(i);
        if(received != expected){qDebug().noquote() << QString::number(i, 16) << expected << received;}
    }
    qDebug().noquote() << "extend";
    parseFile("; InCB; Extend #");
    for(int i=0; i<=end; i++){
        bool received = isUnicodeIndicGraphemeExtend(i);
        bool expected = propertyStorage.at(i);
        if(received != expected){qDebug().noquote() << QString::number(i, 16) << expected << received;}
    }
}