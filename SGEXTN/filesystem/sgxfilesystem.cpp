#include "sgxfilesystem.h"
#include <string>
#include <cstdint>
#include <QString>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QIODevice>
#include <QQueue>
#include <qcontainerfwd.h>
#include "../primitives/sgxtimestamp.h"

QString SGXFileSystem::rootFilePath = "";
QString SGXFileSystem::userDataFilePath = "";
QString SGXFileSystem::configFilePath = "";

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

bool SGXFileSystem::pathIsSubfolder(const QString &childPath, const QString &parentPath){
    if(childPath.length() > parentPath.length() + 1 && childPath.left(parentPath.length() + 1) == parentPath + '/'){return true;}
    return false;
}

bool SGXFileSystem::fileExists(const QString &s){
    if(QFile::exists(s) == true){return true;}
    return false;
}

int SGXFileSystem::folderExists(const QString &s){
    if(QDir(s).exists() == true){return 1;}
    return 0;
}

QString SGXFileSystem::getFreePath(const QString &prefix, const QString &unencodedName, const QString &postfix){
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
        if(SGXFileSystem::fileExists(path) == false && SGXFileSystem::folderExists(path) == false){return path;}
    }
    int i = startIndex;
    while(true){
        QString path = SGXFileSystem::joinFilePaths(prefix, SGXFileSystem::encodeBase16(cleanedName + QString::number(i)) + postfix);
        if(SGXFileSystem::fileExists(path) == false && SGXFileSystem::folderExists(path) == false){return path;}
        i++;
    }
}

int SGXFileSystem::createFile(const QString &s){
    if(SGXFileSystem::fileExists(s) == true){return 0;}
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
    if(SGXFileSystem::folderExists(s) != 0){return 0;}
    if(QDir().mkpath(s)){return 1;}
    return -2;
}

QString SGXFileSystem::getParentPath(const QString &s){
    QString parentPath = QFileInfo(s).absolutePath();
    return parentPath;
}

QString SGXFileSystem::getParentName(const QString &s){
    const QString parentPath = SGXFileSystem::getParentPath(s);
    return QFileInfo(parentPath).fileName();
}

QVector<QString> SGXFileSystem::getFilesList(const QString &s){
    if(SGXFileSystem::folderExists(s) != 1){return QVector<QString>();}
    QFileInfoList f = QDir(s).entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QVector<QString> list = QVector<QString>();
    for(int i=0; i<f.length(); i++){
        list.push_back(f[i].absoluteFilePath());
    }
    return list;
}

QVector<QString> SGXFileSystem::getFoldersList(const QString &s){
    if(SGXFileSystem::folderExists(s) != 1){return QVector<QString>();}
    QFileInfoList f = QDir(s).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QVector<QString> list = QVector<QString>();
    for(int i=0; i<f.length(); i++){
        list.push_back(f[i].absoluteFilePath());
    }
    return list;
}

QVector<QString> SGXFileSystem::getFilesListRecursive(const QString &s){
    if(SGXFileSystem::folderExists(s) != 1){return QVector<QString>();}
    QQueue<QString> pathsToCheck = QQueue<QString>();
    pathsToCheck.enqueue(s);
    QVector<QString> list = QVector<QString>();
    while(pathsToCheck.length() > 0){
        const QString path = pathsToCheck.dequeue();
        QFileInfoList f = QDir(path).entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for(int i=0; i<f.length(); i++){
            list.push_back(f[i].absoluteFilePath());
        }
        f = QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for(int i=0; i<f.length(); i++){
            pathsToCheck.enqueue(f[i].absoluteFilePath());
        }
    }
    return list;
}

int SGXFileSystem::moveFile(const QString &startPath, const QString &endPath){
    if(SGXFileSystem::fileExists(startPath) == false || SGXFileSystem::fileExists(endPath) == true){return 0;}
    if(QFile(startPath).rename(endPath) == true){return 1;}
    return -2;
}

int SGXFileSystem::moveFolder(const QString &startPath, const QString &endPath){
    if(SGXFileSystem::folderExists(startPath) != 1 || SGXFileSystem::folderExists(endPath) != 0){return 0;}
    QVector<QString> startList = SGXFileSystem::getFilesListRecursive(startPath);
    QVector<QString> endList = QVector<QString>();
    for(int i=0; i<startList.length(); i++){
        endList.push_back(endPath + startList[i].mid(startPath.length()));
    }
    for(int i=0; i<startList.length(); i++){
        const QString parentFolder = SGXFileSystem::getParentPath(endList[i]);
        if(SGXFileSystem::folderExists(parentFolder) != 1){SGXFileSystem::createFolder(parentFolder);}
        if(QFile(startList[i]).rename(endList[i]) == false){return -2;}
    }
    QQueue<QString> emptyFolders = QQueue<QString>();
    emptyFolders.enqueue(startPath);
    while(emptyFolders.length() > 0){
        const QString path = emptyFolders.dequeue();
        QVector<QString> foldersInside = SGXFileSystem::getFoldersList(path);
        if(foldersInside.length() > 0){
            for(int i=0; i<foldersInside.length(); i++){
                emptyFolders.enqueue(foldersInside[i]);
            }
            emptyFolders.enqueue(path);
        }
        else{
            if(QDir().rmdir(path) == false){return -2;}
        }
    }
    return 1;
}

int SGXFileSystem::duplicateFile(const QString &startPath, const QString &endPath){
    if(SGXFileSystem::fileExists(startPath) == false || SGXFileSystem::fileExists(endPath) == true){return 0;}
    if(QFile(startPath).copy(endPath) == true){return 1;}
    return -2;
}

int SGXFileSystem::duplicateFolder(const QString &startPath, const QString &endPath){
    if(SGXFileSystem::folderExists(startPath) == false || SGXFileSystem::folderExists(endPath) == true){return 0;}
    QVector<QString> startList = SGXFileSystem::getFilesListRecursive(startPath);
    QVector<QString> endList = QVector<QString>();
    for(int i=0; i<startList.length(); i++){
        endList.push_back(endPath + startList[i].mid(startPath.length()));
    }
    for(int i=0; i<startList.length(); i++){
        const QString parentFolder = SGXFileSystem::getParentPath(endList[i]);
        if(SGXFileSystem::folderExists(parentFolder) != 1){SGXFileSystem::createFolder(parentFolder);}
        if(QFile(startList[i]).copy(endList[i]) == false){return -2;}
    }
    return 1;
}

int SGXFileSystem::permanentDeleteFile(const QString &s){
    if(SGXFileSystem::fileExists(s) == false){return 0;}
    if(QFile::remove(s) == true){return 1;}
    return -2;
}

int SGXFileSystem::permanentDeleteFolder(const QString &s){
    if(SGXFileSystem::folderExists(s) != 1){return 0;}
    QVector<QString> pathList = SGXFileSystem::getFilesListRecursive(s);
    for(int i=0; i<pathList.length(); i++){
        if(QFile::remove(pathList[i]) == false){return -2;}
    }
    QQueue<QString> emptyFolders = QQueue<QString>();
    emptyFolders.enqueue(s);
    while(emptyFolders.length() > 0){
        const QString path = emptyFolders.dequeue();
        QVector<QString> foldersInside = SGXFileSystem::getFoldersList(path);
        if(foldersInside.length() > 0){
            for(int i=0; i<foldersInside.length(); i++){
                emptyFolders.enqueue(foldersInside[i]);
            }
            emptyFolders.enqueue(path);
        }
        else{
            if(QDir().rmdir(path) == false){return -2;}
        }
    }
    return 1;
}

long long SGXFileSystem::getFileSize(const QString &s){
    if(SGXFileSystem::fileExists(s) == false){return -1ll;}
    return QFileInfo(s).size();
}

long long SGXFileSystem::getFolderSize(const QString &s){
    if(SGXFileSystem::folderExists(s) != 1){return -1ll;}
    long long totalSize = 0ll;
    QVector<QString> fileList = SGXFileSystem::getFilesListRecursive(s);
    for(int i=0; i<fileList.length(); i++){
        totalSize += QFileInfo(fileList[i]).size();
    }
    return totalSize;
}

SGXTimeStamp SGXFileSystem::getFileCreationTime(const QString &s){
    if(SGXFileSystem::fileExists(s) == false){return SGXTimeStamp::zero;}
    return SGXTimeStamp(QFileInfo(s).birthTime());
}

SGXTimeStamp SGXFileSystem::getFolderCreationTime(const QString &s){
    if(SGXFileSystem::folderExists(s) != 1){return SGXTimeStamp::zero;}
    return SGXTimeStamp(QFileInfo(s).birthTime());
}

SGXTimeStamp SGXFileSystem::getFileLastEditTime(const QString &s){
    if(SGXFileSystem::fileExists(s) == false){return SGXTimeStamp::zero;}
    return SGXTimeStamp(QFileInfo(s).lastModified());
}

SGXTimeStamp SGXFileSystem::getFolderLastEditTime(const QString &s){
    if(SGXFileSystem::folderExists(s) != 1){return SGXTimeStamp::zero;}
    return SGXTimeStamp(QFileInfo(s).lastModified());
}

QString SGXFileSystem::getFolderName(const QString &s){
    return QFileInfo(s).fileName();
}

QString SGXFileSystem::getFileName(const QString &s){
    return QFileInfo(s).fileName();
}

QString SGXFileSystem::getFileExtension(const QString &s){
    return QFileInfo(s).suffix();
}

QString SGXFileSystem::getFileNameNoExtension(const QString &s){
    return QFileInfo(s).completeBaseName();
}

QVector<QString> SGXFileSystem::getFilesListWithExtension(const QString &s, const QString &ext){
    if(SGXFileSystem::folderExists(s) != 1){return QVector<QString>();}
    QVector<QString> list = SGXFileSystem::getFilesList(s);
    QVector<QString> finalList = QVector<QString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileExtension(list[i]) == ext){finalList.push_back(list[i]);}
    }
    return finalList;
}

QVector<QString> SGXFileSystem::getFilesListWithExtensionRecursive(const QString &s, const QString &ext){
    if(SGXFileSystem::folderExists(s) != 1){return QVector<QString>();}
    QVector<QString> list = SGXFileSystem::getFilesListRecursive(s);
    QVector<QString> finalList = QVector<QString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileExtension(list[i]) == ext){finalList.push_back(list[i]);}
    }
    return finalList;
}

QVector<QString> SGXFileSystem::getFilesListContainingName(const QString &s, const QString &name){
    if(SGXFileSystem::folderExists(s) != 1){return QVector<QString>();}
    QVector<QString> list = SGXFileSystem::getFilesList(s);
    QVector<QString> finalList = QVector<QString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileNameNoExtension(list[i]).contains(name)){finalList.push_back(list[i]);}
    }
    return finalList;
}

QVector<QString> SGXFileSystem::getFilesListContainingNameRecursive(const QString &s, const QString &name){
    if(SGXFileSystem::folderExists(s) != 1){return QVector<QString>();}
    QVector<QString> list = SGXFileSystem::getFilesListRecursive(s);
    QVector<QString> finalList = QVector<QString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileNameNoExtension(list[i]).contains(name)){finalList.push_back(list[i]);}
    }
    return finalList;
}
