#include <QString>
#include <QFile>
#include <QVector>
#include <QMap>
#include <QDebug>

QMap<int, QVector<QString>> allOfUnicode;
QVector<int> offsetStorage;

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

// 12 uppercase, 13 lowercase, 14 titlecase
void extractOffsets(int column){
    offsetStorage = QVector<int>();
    for(int i=0; i<=0x10ffff; i++){
        int thisOffset = 0;
        if(allOfUnicode.contains(i) == true){
            if(allOfUnicode[i].at(column) != ""){
                thisOffset = allOfUnicode[i].at(column).toInt(nullptr, 16) - i;
            }
        }
        offsetStorage.push_back(thisOffset);
    }
}

void printOffsets(int start){
    int prevOffset = 0x7fffffff;
    for(int i=start; i<offsetStorage.length(); i++){
        if(offsetStorage.at(i) != prevOffset){
            qDebug() << i << offsetStorage.at(i);
            prevOffset = offsetStorage.at(i);
        }
    }
}
#include <SGEXTN_Containers_Array.h>
int getUppercaseOffset(int i){
    if(i >= 65 && i < 91){return 32;}
    if(i < 128){return 0;}
    if(i >= 19968 && i <= 40959){return 0;}
    if(i >= 2944 && i <= 3071){return 0;}

    if(i >= 192 && i < 223 && i != 215){return 32;}
    if(i == 304){return -199;}
    if(i >= 256 && i < 312 && i % 2 == 0){return 1;}
    if(i >= 312 && i < 329 && i % 2 == 1){return 1;}
    if(i >= 329 && i < 376 && i % 2 == 0){return 1;}
    SGEXTN::Containers::Array<int> o376(-121, 1, 0, 1, 0, 1, 0, 0, 0, 210, 1, 0, 1, 0, 206, 1, 0, 205, 205, 1, 0, 0, 79, 202, 203, 1, 0, 205, 207, 0, 211, 209, 1, 0, 0, 0, 211, 213, 0, 214, 1, 0, 1, 0, 1, 0, 218, 1, 0, 218, 0, 0, 1, 0, 218, 1, 0, 217, 217, 1, 0, 1, 0, 219, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 1, 0, 2);
    if(i >= 376 && i < 459){return o376.at(i - 376);}
    if(i >= 459 && i < 477 && i % 2 == 1){return 1;}
    if(i >= 477 && i < 496 && i % 2 == 0){return 1;}
    SGEXTN::Containers::Array<int> o496(0, 2, 1, 0, 1, 0, -97, -56);
    if(i >= 496 && i < 504){return o496.at(i - 496);}
    if(i == 544){return -130;}
    if(i >= 504 && i < 564 && i % 2 == 0){return 1;}
    SGEXTN::Containers::Array<int> o570(10795, 1, 0, -163, 10792, 0, 0, 1, 0, -195, 69, 71);
    if(i >= 570 && i < 582){return o570.at(i - 570);}
    if(i >= 582 && i < 591 && i % 2 == 0){return 1;}
    SGEXTN::Containers::Array<int> o880(1, 0, 1, 0, 0, 0, 1);
    if(i >= 880 && i < 887){return o880.at(i - 880);}
    if(i == 895){return 116;}
    SGEXTN::Containers::Array<int> o902(38, 0, 37, 37, 37, 0, 64, 0, 63, 63, 0);
    if(i >= 902 && i < 913){return o902.at(i - 902);}
    if(i >= 913 && i < 940 && i != 930){return 32;}
    if(i == 975){return 8;}
    if(i >= 984 && i < 1007 && i % 2 == 0){return 1;}
    SGEXTN::Containers::Array<int> o1012(-60, 0, 0, 1, 0, -7, 1, 0, 0, -130, -130, -130);
    if(i >= 1012 && i < 1024){return o1012.at(i - 1012);}
    if(i >= 1024 && i < 1040){return 80;}
    if(i >= 1040 && i < 1072){return 32;}
    if(i >= 1120 && i < 1154 && i % 2 == 0){return 1;}
    if(i >= 1161 && i < 1216 && i % 2 == 0){return 1;}
    if(i == 1216){return 15;}
    if(i >= 1216 && i < 1231 && i % 2 == 1){return 1;}
    if(i >= 1231 && i < 1328 && i % 2 == 0){return 1;}
    if(i >= 1329 && i < 1367){return 48;}
    if(i >= 4256 && i < 4294){return 7264;}
    if(i == 4295){return 7264;}
    if(i == 4301){return 7264;}
    if(i >= 5024 && i < 5104){return 38864;}
    if(i >= 5104 && i < 5110){return 8;}
    if(i == 7305){return 1;}
    if(i >= 7312 && i < 7355){return -3008;}
    if(i >= 7357 && i < 7360){return -3008;}
    if(i >= 7680 && i < 7830 && i % 2 == 0){return 1;}
    if(i == 7838){return -7615;}
    if(i >= 7837 && i < 7935 && i % 2 == 0){return 1;}
    if(i >= 7944 && i < 7952){return -8;}
    if(i >= 7960 && i < 7966){return -8;}
    if(i >= 7976 && i < 7984){return -8;}
    if(i >= 7992 && i < 8000){return -8;}
    if(i >= 8008 && i < 8014){return -8;}
    if(i >= 8025 && i < 8032 && i % 2 == 1){return -8;}
    if(i >= 8040 && i < 8048){return -8;}
    if(i >= 8072 && i < 8080){return -8;}
    if(i >= 8088 && i < 8096){return -8;}
    if(i >= 8104 && i < 8112){return -8;}
    SGEXTN::Containers::Array<int> o8120(-8, -8, -74, -74, -9);
    if(i >= 8120 && i < 8125){return o8120.at(i - 8120);}
    SGEXTN::Containers::Array<int> o8136(-86, -86, -86, -86, -9);
    if(i >= 8136 && i < 8141){return o8136.at(i - 8136);}
    SGEXTN::Containers::Array<int> o8152(-8, -8, -100, -100);
    if(i >= 8152 && i < 8156){return o8152.at(i - 8152);}
    SGEXTN::Containers::Array<int> o8168(-8, -8, -112, -112, -7);
    if(i >= 8168 && i < 8173){return o8168.at(i - 8168);}
    SGEXTN::Containers::Array<int> o8184(-128, -128, -126, -126, -9);
    if(i >= 8184 && i < 8189){return o8184.at(i - 8184);}
    SGEXTN::Containers::Array<int> o8486(-7517, 0, 0, 0, -8383, -8262);
    if(i >= 8486 && i < 8492){return o8486.at(i - 8486);}
    if(i == 8498){return 28;}
    if(i >= 8544 && i < 8560){return 16;}
    if(i == 8579){return 1;}
    if(i >= 9398 && i < 9424){return 26;}
    if(i >= 11264 && i < 11312){return 48;}
    SGEXTN::Containers::Array<int> o11360(1, 0, -10743, -3814, -10727, 0, 0, 1, 0, 1, 0, 1, 0, -10780, -10749, -10783, -10782, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -10815, -10815);
    if(i >= 11360 && i < 11392){return o11360.at(i - 11360);}
    if(i >= 11392 && i < 11492 && i % 2 == 0){return 1;}
    if(i == 11499){return 1;}
    if(i == 11501){return 1;}
    if(i == 11506){return 1;}
    if(i >= 42560 && i < 42606 && i % 2 == 0){return 1;}
    if(i >= 42624 && i < 42651 && i % 2 == 0){return 1;}
    if(i >= 42786 && i < 42863 && i % 2 == 0 && i != 42800){return 1;}
    SGEXTN::Containers::Array<int> o42873(1, 0, 1, 0, -35332, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, -42280, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, -42308, -42319, -42315, -42305, -42308, 0, -42258, -42282, -42261, 928, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, -48, -42307, -35384, 1, 0, 1, 0, -42343);
    if(i >= 42873 && i < 42956){return o42873.at(i - 42873);}
    if(i >= 42956 && i < 42971 && i % 2 == 0){return 1;}
    if(i == 42972){return -42561;}
    if(i == 42997){return 1;}
    if(i >= 65313 && i < 65339){return 32;}
    if(i >= 66560 && i < 66600){return 40;}
    if(i >= 66736 && i < 66772){return 40;}
    if(i >= 66928 && i < 66966 && i != 66939 && i != 66955 && i != 66963){return 39;}
    if(i >= 68736 && i < 68787){return 64;}
    if(i >= 68944 && i < 68966){return 32;}
    if(i >= 71840 && i < 71872){return 32;}
    if(i >= 93760 && i < 93792){return 32;}
    if(i >= 93856 && i < 93881){return 27;}
    if(i >= 125184 && i < 125218){return 34;}
    return 0;
}

void testToUppercaseOffsets(){
    for(int i=0; i<=0x10ffff; i++){
        if(getUppercaseOffset(i) != offsetStorage.at(i)){
            qDebug() << i << offsetStorage.at(i) << getUppercaseOffset(i);
        }
    }
}