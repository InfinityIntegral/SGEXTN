#include "sgxfilesystem.h"
#include <string>
#include <cstdint>
#include <QString>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QIODevice>

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

bool SGXFileSystem::pathIsValid(const QString &s){
    const QString root = SGXFileSystem::rootFilePath + '/';
    if(s.left(root.length()) == root){return true;}
    return false;
}

int SGXFileSystem::fileExists(const QString &s){
    if(SGXFileSystem::pathIsValid(s) == false){return -1;}
    if(QFile::exists(s) == true){return 1;}
    return 0;
}

int SGXFileSystem::folderExists(const QString &s){
    if(SGXFileSystem::pathIsValid(s) == false){return -1;}
    if(QDir(s).exists() == true){return 1;}
    return 0;
}

QString SGXFileSystem::getFreePath(const QString &prefix, const QString &unencodedName, const QString &postfix){
    if(SGXFileSystem::pathIsValid(prefix) == false){return "";}
    bool endsWithNumber = false;
    QString cleanedName = unencodedName;
    int startIndex = 1;
    {
        QString reversedNumber = "";
        for(int i=static_cast<int>(unencodedName.length())-1; i>=0; i--){
            if(unencodedName[i] >= '0' && unencodedName[i] <= '9'){reversedNumber += unencodedName[i];}
            else{break;}
        }
        QString correctNumber = "";
        for(int i=static_cast<int>(reversedNumber.length())-1; i>=0; i--){
            correctNumber += reversedNumber[i];
        }
        if(correctNumber != ""){
            startIndex = correctNumber.toInt();
            cleanedName = unencodedName.left(unencodedName.length() - correctNumber.length());
            endsWithNumber = true;
        }
    }
    if(endsWithNumber == false){
        QString path = SGXFileSystem::joinFilePaths(prefix, SGXFileSystem::encodeBase16(unencodedName) + postfix);
        if(SGXFileSystem::fileExists(path) == 0 && SGXFileSystem::folderExists(path) == 0){return path;}
    }
    int i = startIndex;
    while(true){
        QString path = SGXFileSystem::joinFilePaths(prefix, SGXFileSystem::encodeBase16(cleanedName + QString::number(i)) + postfix);
        if(SGXFileSystem::fileExists(path) == 0 && SGXFileSystem::folderExists(path) == 0){return path;}
        i++;
    }
}

int SGXFileSystem::createFile(const QString &s){
    if(SGXFileSystem::pathIsValid(s) == false){return -1;}
    if(SGXFileSystem::fileExists(s) != 1){return 0;}
    const QDir parentFolder = QFileInfo(s).dir();
    if(parentFolder.exists() == false){QDir().mkpath(parentFolder.absolutePath());}
    QFile f(s);
    if(f.open(QIODevice::WriteOnly)){
        f.close();
        return 1;
    }
    return -2;
}

int SGXFileSystem::createFolder(const QString& s){
    if(SGXFileSystem::pathIsValid(s) == false){return -1;}
    if(SGXFileSystem::folderExists(s) != 1){return 0;}
    if(QDir().mkpath(s)){return 1;}
    return -2;
}
