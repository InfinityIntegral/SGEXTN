#include "sgxfilesystem.h"
#include <string>
#include <cstdint>
#include <QString>

QString SGXFileSystem::rootFilePath = "";
QString SGXFileSystem::userDataFilePath = "";
QString SGXFileSystem::configFilePath = "";
QString SGXFileSystem::binFilePath = "";

QString SGXFileSystem::joinFilePaths(const QString &a, const QString &b){
    return (a + '/' + b);
}

QString SGXFileSystem::encodeBase16(const QString &s){
    QString s0 = "";
    for(int i=0; i<s.length(); i++){
        std::string thisChar = QString(s[i]).toUtf8().toStdString();
        if(thisChar.length() == 1){
            std::string stringToAdd = {'0', '0'};
            const uint8_t c = thisChar[0];
            stringToAdd[0] = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd[1] = static_cast<char>((c & 0xF) + 97);
            s0 += QString::fromStdString(stringToAdd);
        }
        else if(thisChar.length() == 2){
            std::string stringToAdd = {'x', '0', '0', '0', '0'};
            uint8_t c = thisChar[0];
            stringToAdd[1] = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd[2] = static_cast<char>((c & 0xF) + 97);
            c = thisChar[1];
            stringToAdd[3] = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd[4] = static_cast<char>((c & 0xF) + 97);
            s0 += QString::fromStdString(stringToAdd);
        }
        else if(thisChar.length() == 3){
            std::string stringToAdd = {'y', '0', '0', '0', '0', '0', '0'};
            uint8_t c = thisChar[0];
            stringToAdd[1] = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd[2] = static_cast<char>((c & 0xF) + 97);
            c = thisChar[1];
            stringToAdd[3] = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd[4] = static_cast<char>((c & 0xF) + 97);
            c = thisChar[2];
            stringToAdd[5] = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd[6] = static_cast<char>((c & 0xF) + 97);
            s0 += QString::fromStdString(stringToAdd);
        }
        else{
            std::string stringToAdd = {'z', '0', '0', '0', '0', '0', '0', '0', '0'};
            uint8_t c = thisChar[0];
            stringToAdd[1] = static_cast<char>(((c & 0xF0) >> 4) + 97);
            stringToAdd[2] = static_cast<char>((c & 0xF) + 97);
            c = thisChar[1];
            stringToAdd[3] = static_cast<char>(((c & 0xF0) >> 4) + 97);
            stringToAdd[4] = static_cast<char>((c & 0xF) + 97);
            c = thisChar[2];
            stringToAdd[5] = static_cast<char>(((c & 0xF0) >> 4) + 97);
            stringToAdd[6] = static_cast<char>((c & 0xF) + 97);
            c = thisChar[3];
            stringToAdd[7] = static_cast<char>(((c & 0xF0) >> 4) + 97);
            stringToAdd[8] = static_cast<char>((c & 0xF) + 97);
            s0 += QString::fromStdString(stringToAdd);
        }
    }
    return s0;
}

QString SGXFileSystem::decodeBase16(const QString &str){
    int i = 0;
    std::string s = str.toStdString();
    QString s0 = "";
    while(i < static_cast<int>(s.length())){
        if(s[i] == 'x'){
            std::string stringToAdd = {'0', '0'};
            uint8_t a = s[i + 1];
            uint8_t b = s[i + 2];
            stringToAdd[0] = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s[i + 3];
            b = s[i + 4];
            stringToAdd[1] = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += QString::fromStdString(stringToAdd);
            i += 5;
        }
        else if(s[i] == 'y'){
            std::string stringToAdd = {'0', '0', '0'};
            uint8_t a = s[i + 1];
            uint8_t b = s[i + 2];
            stringToAdd[0] = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s[i + 3];
            b = s[i + 4];
            stringToAdd[1] = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s[i + 5];
            b = s[i + 6];
            stringToAdd[2] = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += QString::fromStdString(stringToAdd);
            i += 7;
        }
        else if(s[i] == 'z'){
            std::string stringToAdd = {'0', '0', '0', '0'};
            uint8_t a = s[i + 1];
            uint8_t b = s[i + 2];
            stringToAdd[0] = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s[i + 3];
            b = s[i + 4];
            stringToAdd[1] = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s[i + 5];
            b = s[i + 6];
            stringToAdd[2] = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s[i + 7];
            b = s[i + 8];
            stringToAdd[3] = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += QString::fromStdString(stringToAdd);
            i += 9;
        }
        else{
            std::string stringToAdd = {'0'};
            const uint8_t a = s[i];
            const uint8_t b = s[i + 1];
            stringToAdd[0] = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += QString::fromStdString(stringToAdd);
            i += 2;
        }
    }
    return s0;
}
