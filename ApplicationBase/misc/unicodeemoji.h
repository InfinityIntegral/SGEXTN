#include <QString>
#include <QFile>
#include <QVector>
#include <QMap>
#include <QDebug>

QVector<bool> propertyStorage;

void parseFile(){
    for(int i=0; i<=0x10ffff; i++){
        propertyStorage.push_back(false);
    }
    QString dataString = "";
    QFile file("../ApplicationBase/misc/unicodeemoji.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        dataString = file.readAll();
        file.close();
    }
    QVector<QString> characters = dataString.split('\n');
    for(int i=0; i<characters.length(); i++){
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

bool isUnicodeEmoji(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2200 && i <= 0x22ff){return false;}
    if(i == 0xa9 || i == 0xae){return true;}
    if(i == 0x203c || i == 0x2049){return true;}
    if(i >= 0x2100 && i <= 0x21ff){
        if(i == 0x2122){return true;}
        if(i == 0x2139){return true;}
        if(i >= 0x2194 && i <= 0x2199){return true;}
        if(i >= 0x21a9 && i <= 0x21aa){return true;}
    }
    if(i >= 0x2300 && i <= 0x23ff){
        if(i >= 0x231a && i <= 0x231b){return true;}
        if(i == 0x2328){return true;}
        if(i == 0x23cf){return true;}
        if(i >= 0x23e9 && i <= 0x23f3){return true;}
        if(i >= 0x23f8 && i <= 0x23fa){return true;}
    }
    if(i == 0x24c2){return true;}
    if(i >= 0x25a0 && i <= 0x25ff){
        if(i >= 0x25aa && i <= 0x25ab){return true;}
        if(i == 0x25b6){return true;}
        if(i == 0x25c0){return true;}
        if(i >= 0x25fb && i <= 0x25fe){return true;}
    }
    if(i >= 0x2600 && i <= 0x26ff){
        if(i >= 0x2600 && i <= 0x2604){return true;}
        if(i == 0x260e){return true;}
        if(i == 0x2611){return true;}
        if(i >= 0x2614 && i <= 0x2615){return true;}
        if(i == 0x2618){return true;}
        if(i == 0x261d){return true;}
        if(i == 0x2620){return true;}
        if(i >= 0x2622 && i <= 0x2623){return true;}
        if(i == 0x2626){return true;}
        if(i == 0x262a){return true;}
        if(i >= 0x262e && i <= 0x262f){return true;}
        if(i >= 0x2638 && i <= 0x263a){return true;}
        if(i == 0x2640){return true;}
        if(i == 0x2642){return true;}
        if(i >= 0x2648 && i <= 0x2653){return true;}
        if(i >= 0x265f && i <= 0x2660){return true;}
        if(i == 0x2663){return true;}
        if(i >= 0x2665 && i <= 0x2666){return true;}
        if(i == 0x2668){return true;}
        if(i == 0x267b){return true;}
        if(i >= 0x267e && i <= 0x267f){return true;}
        if(i >= 0x2692 && i <= 0x2697){return true;}
        if(i == 0x2699){return true;}
        if(i >= 0x269b && i <= 0x269c){return true;}
        if(i >= 0x26a0 && i <= 0x26a1){return true;}
        if(i == 0x26a7){return true;}
        if(i >= 0x26aa && i <= 0x26ab){return true;}
        if(i >= 0x26b0 && i <= 0x26b1){return true;}
        if(i >= 0x26bd && i <= 0x26be){return true;}
        if(i >= 0x26c4 && i <= 0x26c5){return true;}
        if(i == 0x26c8){return true;}
        if(i >= 0x26ce && i <= 0x26cf){return true;}
        if(i == 0x26d1){return true;}
        if(i >= 0x26d3 && i <= 0x26d4){return true;}
        if(i >= 0x26e9 && i <= 0x26ea){return true;}
        if(i >= 0x26f0 && i <= 0x26f5){return true;}
        if(i >= 0x26f7 && i <= 0x26fa){return true;}
        if(i == 0x26fd){return true;}
    }
    if(i >= 0x2700 && i <= 0x27ff){
        if(i == 0x2702){return true;}
        if(i == 0x2705){return true;}
        if(i >= 0x2708 && i <= 0x270d){return true;}
        if(i == 0x270f){return true;}
        if(i == 0x2712){return true;}
        if(i == 0x2714){return true;}
        if(i == 0x2716){return true;}
        if(i == 0x271d){return true;}
        if(i == 0x2721){return true;}
        if(i == 0x2728){return true;}
        if(i >= 0x2733 && i <= 0x2734){return true;}
        if(i == 0x2744){return true;}
        if(i == 0x2747){return true;}
        if(i == 0x274c){return true;}
        if(i == 0x274e){return true;}
        if(i >= 0x2753 && i <= 0x2755){return true;}
        if(i == 0x2757){return true;}
        if(i >= 0x2763 && i <= 0x2764){return true;}
        if(i >= 0x2795 && i <= 0x2797){return true;}
        if(i == 0x27a1){return true;}
        if(i == 0x27b0){return true;}
        if(i == 0x27bf){return true;}
    }
    if(i >= 0x2934 && i <= 0x2935){return true;}
    if(i >= 0x2b00 && i <= 0x2b7f){
        if(i >= 0x2b05 && i <= 0x2b07){return true;}
        if(i >= 0x2b1b && i <= 0x2b1c){return true;}
        if(i == 0x2b50){return true;}
        if(i == 0x2b55){return true;}
    }
    if(i == 0x3030 || i == 0x303d){return true;}
    if(i == 0x3297 || i == 0x3299){return true;}
    if(i >= 0x1f000 && i <= 0x1ffff){
        if(i == 0x1f004){return true;}
        if(i >= 0x1f02c && i <= 0x1f02f){return true;}
        if(i >= 0x1f094 && i <= 0x1f09f){return true;}
        if(i >= 0x1f0af && i <= 0x1f0b0){return true;}
        if(i == 0x1f0c0){return true;}
        if(i >= 0x1f0cf && i <= 0x1f0d0){return true;}
        if(i >= 0x1f0f6 && i <= 0x1f0ff){return true;}
        if(i >= 0x1f170 && i <= 0x1f171){return true;}
        if(i >= 0x1f17e && i <= 0x1f17f){return true;}
        if(i == 0x1f18e){return true;}
        if(i >= 0x1f191 && i <= 0x1f19a){return true;}
        if(i >= 0x1f1ae && i <= 0x1f1e5){return true;}
        if(i >= 0x1f201 && i <= 0x1f20f){return true;}
        if(i == 0x1f21a){return true;}
        if(i == 0x1f22f){return true;}
        if(i >= 0x1f232 && i <= 0x1f23a){return true;}
        if(i >= 0x1f23c && i <= 0x1f23f){return true;}
        if(i >= 0x1f249 && i <= 0x1f25f){return true;}
        if(i >= 0x1f266 && i <= 0x1f321){return true;}
        if(i >= 0x1f324 && i <= 0x1f393){return true;}
        if(i >= 0x1f396 && i <= 0x1f397){return true;}
        if(i >= 0x1f399 && i <= 0x1f39b){return true;}
        if(i >= 0x1f39e && i <= 0x1f3f0){return true;}
        if(i >= 0x1f3f3 && i <= 0x1f3f5){return true;}
        if(i >= 0x1f3f7 && i <= 0x1f3fa){return true;}
        if(i >= 0x1f400 && i <= 0x1f4fd){return true;}
        if(i >= 0x1f4ff && i <= 0x1f53d){return true;}
        if(i >= 0x1f549 && i <= 0x1f54e){return true;}
        if(i >= 0x1f550 && i <= 0x1f567){return true;}
        if(i >= 0x1f56f && i <= 0x1f570){return true;}
        if(i >= 0x1f573 && i <= 0x1f57a){return true;}
        if(i == 0x1f587){return true;}
        if(i >= 0x1f58a && i <= 0x1f58d){return true;}
        if(i == 0x1f590){return true;}
        if(i >= 0x1f595 && i <= 0x1f596){return true;}
        if(i >= 0x1f5a4 && i <= 0x1f5a5){return true;}
        if(i == 0x1f5a8){return true;}
        if(i >= 0x1f5b1 && i <= 0x1f5b2){return true;}
        if(i == 0x1f5bc){return true;}
        if(i >= 0x1f5c2 && i <= 0x1f5c4){return true;}
        if(i >= 0x1f5d1 && i <= 0x1f5d3){return true;}
        if(i >= 0x1f5dc && i <= 0x1f5de){return true;}
        if(i == 0x1f5e1){return true;}
        if(i == 0x1f5e3){return true;}
        if(i == 0x1f5e8){return true;}
        if(i == 0x1f5ef){return true;}
        if(i == 0x1f5f3){return true;}
        if(i >= 0x1f5fa && i <= 0x1f64f){return true;}
        if(i >= 0x1f680 && i <= 0x1f6c5){return true;}
        if(i >= 0x1f6cb && i <= 0x1f6d2){return true;}
        if(i >= 0x1f6d5 && i <= 0x1f6e5){return true;}
        if(i == 0x1f6e9){return true;}
        if(i >= 0x1f6eb && i <= 0x1f6f0){return true;}
        if(i >= 0x1f6f3 && i <= 0x1f6ff){return true;}
        if(i >= 0x1f7da && i <= 0x1f7ff){return true;}
        if(i >= 0x1f80c && i <= 0x1f80f){return true;}
        if(i >= 0x1f848 && i <= 0x1f84f){return true;}
        if(i >= 0x1f85a && i <= 0x1f85f){return true;}
        if(i >= 0x1f888 && i <= 0x1f88f){return true;}
        if(i >= 0x1f8ae && i <= 0x1f8af){return true;}
        if(i >= 0x1f8bc && i <= 0x1f8bf){return true;}
        if(i >= 0x1f8c2 && i <= 0x1f8cf){return true;}
        if(i >= 0x1f8d9 && i <= 0x1f8ff){return true;}
        if(i >= 0x1f90c && i <= 0x1f93a){return true;}
        if(i >= 0x1f93c && i <= 0x1f945){return true;}
        if(i >= 0x1f947 && i <= 0x1f9ff){return true;}
        if(i >= 0x1fa58 && i <= 0x1fa5f){return true;}
        if(i >= 0x1fa6e && i <= 0x1faff){return true;}
        if(i >= 0x1fc00 && i <= 0x1fffd){return true;}
    }
    return false;
}

void checkEmoji(int end){
    for(int i=0; i<=end; i++){
        bool received = isUnicodeEmoji(i);
        bool expected = propertyStorage.at(i);
        if(received != expected){qDebug().noquote() << QString::number(i, 16) << expected << received;}
    }
}