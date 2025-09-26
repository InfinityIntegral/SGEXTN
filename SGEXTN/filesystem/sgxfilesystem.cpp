#include "sgxfilesystem.h"
#include <string>
#include <cstdint>
#include "../primitives/sgxstring.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QIODevice>
#include <QQueue>
#include <qcontainerfwd.h>
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxchar.h"

SGXString SGXFileSystem::rootFilePath = "";
SGXString SGXFileSystem::userDataFilePath = "";
SGXString SGXFileSystem::configFilePath = "";

SGXString SGXFileSystem::joinFilePaths(const SGXString &a, const SGXString &b){
    return (a + "/" + b);
}

SGXString SGXFileSystem::encodeBase16(const SGXString &s){
    SGXString s0 = "";
    for(int i=0; i<s.length(); i++){
        std::string thisChar = SGXString(s.at(i)).toStdString();
        if(thisChar.length() == 1){
            std::string stringToAdd = {'0', '0'};
            const uint8_t c = thisChar.at(0);
            stringToAdd.at(0) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(1) = static_cast<char>((c & 0xF) + 97);
            s0 += SGXString(stringToAdd);
        }
        else if(thisChar.length() == 2){
            std::string stringToAdd = {'x', '0', '0', '0', '0'};
            uint8_t c = thisChar.at(0);
            stringToAdd.at(1) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(2) = static_cast<char>((c & 0xF) + 97);
            c = thisChar.at(1);
            stringToAdd.at(3) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(4) = static_cast<char>((c & 0xF) + 97);
            s0 += SGXString(stringToAdd);
        }
        else if(thisChar.length() == 3){
            std::string stringToAdd = {'y', '0', '0', '0', '0', '0', '0'};
            uint8_t c = thisChar.at(0);
            stringToAdd.at(1) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(2) = static_cast<char>((c & 0xF) + 97);
            c = thisChar.at(1);
            stringToAdd.at(3) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(4) = static_cast<char>((c & 0xF) + 97);
            c = thisChar.at(2);
            stringToAdd.at(5) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(6) = static_cast<char>((c & 0xF) + 97);
            s0 += SGXString(stringToAdd);
        }
        else{
            std::string stringToAdd = {'z', '0', '0', '0', '0', '0', '0', '0', '0'};
            uint8_t c = thisChar.at(0);
            stringToAdd.at(1) = static_cast<char>(((c & 0xF0) >> 4) + 97);
            stringToAdd.at(2) = static_cast<char>((c & 0xF) + 97);
            c = thisChar.at(1);
            stringToAdd.at(3) = static_cast<char>(((c & 0xF0) >> 4) + 97);
            stringToAdd.at(4) = static_cast<char>((c & 0xF) + 97);
            c = thisChar.at(2);
            stringToAdd.at(5) = static_cast<char>(((c & 0xF0) >> 4) + 97);
            stringToAdd.at(6) = static_cast<char>((c & 0xF) + 97);
            c = thisChar.at(3);
            stringToAdd.at(7) = static_cast<char>(((c & 0xF0) >> 4) + 97);
            stringToAdd.at(8) = static_cast<char>((c & 0xF) + 97);
            s0 += SGXString(stringToAdd);
        }
    }
    return s0;
}

SGXString SGXFileSystem::decodeBase16(const SGXString &str){
    int i = 0;
    std::string s = str.toStdString();
    SGXString s0 = "";
    while(i < static_cast<int>(s.length())){
        if(s.at(i) == 'x'){
            std::string stringToAdd = {'0', '0'};
            uint8_t a = s.at(i+1);
            uint8_t b = s.at(i+2);
            stringToAdd.at(0) = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s.at(i+3);
            b = s.at(i+4);
            stringToAdd.at(1) = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += SGXString(stringToAdd);
            i += 5;
        }
        else if(s.at(i) == 'y'){
            std::string stringToAdd = {'0', '0', '0'};
            uint8_t a = s.at(i+1);
            uint8_t b = s.at(i+2);
            stringToAdd.at(0) = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s.at(i+3);
            b = s.at(i+4);
            stringToAdd.at(1) = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s.at(i+5);
            b = s.at(i+6);
            stringToAdd.at(2) = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += SGXString(stringToAdd);
            i += 7;
        }
        else if(s.at(i) == 'z'){
            std::string stringToAdd = {'0', '0', '0', '0'};
            uint8_t a = s.at(i+1);
            uint8_t b = s.at(i+2);
            stringToAdd.at(0) = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s.at(i+3);
            b = s.at(i+4);
            stringToAdd.at(1) = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s.at(i+5);
            b = s.at(i+6);
            stringToAdd.at(2) = static_cast<char>(((a - 97) << 4) | (b - 97));
            a = s.at(i+7);
            b = s.at(i+8);
            stringToAdd.at(3) = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += SGXString(stringToAdd);
            i += 9;
        }
        else{
            std::string stringToAdd = {'0'};
            const uint8_t a = s.at(i);
            const uint8_t b = s.at(i+1);
            stringToAdd.at(0) = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += SGXString(stringToAdd);
            i += 2;
        }
    }
    return s0;
}

bool SGXFileSystem::pathIsSubfolder(const SGXString &childPath, const SGXString &parentPath){
    if(childPath.length() > parentPath.length() + 1 && childPath.substringLeft(parentPath.length() + 1) == parentPath + "/"){return true;}
    return false;
}

bool SGXFileSystem::fileExists(const SGXString &s){
    if(QFile::exists(*s.data) == true){return true;}
    return false;
}

bool SGXFileSystem::folderExists(const SGXString &s){
    if(QDir(*s.data).exists() == true){return true;}
    return false;
}

SGXString SGXFileSystem::getFreePath(const SGXString &prefix, const SGXString &unencodedName, const SGXString &postfix){
    bool endsWithNumber = false;
    SGXString cleanedName = unencodedName;
    int startIndex = 1;
    {
        SGXString reversedNumber = "";
        for(int i=static_cast<int>(unencodedName.length())-1; i>=0; i--){
            if(unencodedName.at(i) >= '0' && unencodedName.at(i) <= '9'){reversedNumber += unencodedName.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=static_cast<int>(reversedNumber.length())-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        if(correctNumber != ""){
            startIndex = correctNumber.parseToInt(nullptr);
            cleanedName = unencodedName.substringLeft(unencodedName.length() - correctNumber.length());
            endsWithNumber = true;
        }
    }
    if(endsWithNumber == false){
        SGXString path = SGXFileSystem::joinFilePaths(prefix, SGXFileSystem::encodeBase16(unencodedName) + postfix);
        if(SGXFileSystem::fileExists(path) == false && SGXFileSystem::folderExists(path) == false){return path;}
    }
    int i = startIndex;
    while(true){
        SGXString path = SGXFileSystem::joinFilePaths(prefix, SGXFileSystem::encodeBase16(cleanedName + SGXString::intToString(i)) + postfix);
        if(SGXFileSystem::fileExists(path) == false && SGXFileSystem::folderExists(path) == false){return path;}
        i++;
    }
}

int SGXFileSystem::createFile(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == true){return 0;}
    const QDir parentFolder = QFileInfo(*s.data).dir();
    if(parentFolder.exists() == false){QDir().mkpath(parentFolder.absolutePath());}
    QFile f(*s.data);
    if(f.open(QIODevice::WriteOnly)){
        f.close();
        return 1;
    }
    return -2;
}

int SGXFileSystem::createFolder(const SGXString& s){
    if(SGXFileSystem::folderExists(s) == true){return 0;}
    if(QDir().mkpath(*s.data)){return 1;}
    return -2;
}

SGXString SGXFileSystem::getParentPath(const SGXString &s){
    SGXString parentPath = "";
    (*parentPath.data) = QFileInfo(*s.data).absolutePath();
    return parentPath;
}

SGXString SGXFileSystem::getParentName(const SGXString &s){
    const SGXString parentPath = SGXFileSystem::getParentPath(s);
    SGXString output = "";
    (*output.data) = QFileInfo(*parentPath.data).fileName();
    return output;
}

QVector<SGXString> SGXFileSystem::getFilesList(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return QVector<SGXString>();}
    QFileInfoList f = QDir(*s.data).entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QVector<SGXString> list = QVector<SGXString>();
    for(int i=0; i<f.length(); i++){
        SGXString s0 = "";
        (*s0.data) = f.at(i).absoluteFilePath();
        list.push_back(s0);
    }
    return list;
}

QVector<SGXString> SGXFileSystem::getFoldersList(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return QVector<SGXString>();}
    QFileInfoList f = QDir(*s.data).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QVector<SGXString> list = QVector<SGXString>();
    for(int i=0; i<f.length(); i++){
        SGXString s0 = "";
        (*s0.data) = f.at(i).absoluteFilePath();
        list.push_back(s0);
    }
    return list;
}

QVector<SGXString> SGXFileSystem::getFilesListRecursive(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return QVector<SGXString>();}
    QQueue<SGXString> pathsToCheck = QQueue<SGXString>();
    pathsToCheck.enqueue(s);
    QVector<SGXString> list = QVector<SGXString>();
    while(pathsToCheck.length() > 0){
        const SGXString path = pathsToCheck.dequeue();
        QFileInfoList f = QDir(*path.data).entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for(int i=0; i<f.length(); i++){
            SGXString s0 = "";
            (*s0.data) = f.at(i).absoluteFilePath();
            list.push_back(s0);
        }
        f = QDir(*path.data).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for(int i=0; i<f.length(); i++){
            SGXString s0 = "";
            (*s0.data) = f.at(i).absoluteFilePath();
            pathsToCheck.enqueue(s0);
        }
    }
    return list;
}

int SGXFileSystem::moveFile(const SGXString &startPath, const SGXString &endPath){
    if(SGXFileSystem::fileExists(startPath) == false || SGXFileSystem::fileExists(endPath) == true){return 0;}
    if(QFile(*startPath.data).rename(*endPath.data) == true){return 1;}
    return -2;
}

int SGXFileSystem::moveFolder(const SGXString &startPath, const SGXString &endPath){
    if(SGXFileSystem::folderExists(startPath) == false || SGXFileSystem::folderExists(endPath) == true){return 0;}
    QVector<SGXString> startList = SGXFileSystem::getFilesListRecursive(startPath);
    QVector<SGXString> endList = QVector<SGXString>();
    for(int i=0; i<startList.length(); i++){
        endList.push_back(endPath + startList.at(i).substringRight(startList.at(i).length() - startPath.length()));
    }
    for(int i=0; i<startList.length(); i++){
        const SGXString parentFolder = SGXFileSystem::getParentPath(endList.at(i));
        if(SGXFileSystem::folderExists(parentFolder) == false){SGXFileSystem::createFolder(parentFolder);}
        if(QFile(*startList.at(i).data).rename(*endList.at(i).data) == false){return -2;}
    }
    QQueue<SGXString> emptyFolders = QQueue<SGXString>();
    emptyFolders.enqueue(startPath);
    while(emptyFolders.length() > 0){
        const SGXString path = emptyFolders.dequeue();
        QVector<SGXString> foldersInside = SGXFileSystem::getFoldersList(path);
        if(foldersInside.length() > 0){
            for(int i=0; i<foldersInside.length(); i++){
                emptyFolders.enqueue(foldersInside.at(i));
            }
            emptyFolders.enqueue(path);
        }
        else{
            if(QDir().rmdir(*path.data) == false){return -2;}
        }
    }
    return 1;
}

int SGXFileSystem::duplicateFile(const SGXString &startPath, const SGXString &endPath){
    if(SGXFileSystem::fileExists(startPath) == false || SGXFileSystem::fileExists(endPath) == true){return 0;}
    if(QFile(*startPath.data).copy(*endPath.data) == true){return 1;}
    return -2;
}

int SGXFileSystem::duplicateFolder(const SGXString &startPath, const SGXString &endPath){
    if(SGXFileSystem::folderExists(startPath) == false || SGXFileSystem::folderExists(endPath) == true){return 0;}
    QVector<SGXString> startList = SGXFileSystem::getFilesListRecursive(startPath);
    QVector<SGXString> endList = QVector<SGXString>();
    for(int i=0; i<startList.length(); i++){
        endList.push_back(endPath + startList.at(i).substringRight(startList.at(i).length() - startPath.length()));
    }
    for(int i=0; i<startList.length(); i++){
        const SGXString parentFolder = SGXFileSystem::getParentPath(endList.at(i));
        if(SGXFileSystem::folderExists(parentFolder) == false){SGXFileSystem::createFolder(parentFolder);}
        if(QFile(*startList.at(i).data).copy(*endList.at(i).data) == false){return -2;}
    }
    return 1;
}

int SGXFileSystem::permanentDeleteFile(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == false){return 0;}
    if(QFile::remove(*s.data) == true){return 1;}
    return -2;
}

int SGXFileSystem::permanentDeleteFolder(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return 0;}
    QVector<SGXString> pathList = SGXFileSystem::getFilesListRecursive(s);
    for(int i=0; i<pathList.length(); i++){
        if(QFile::remove(*pathList.at(i).data) == false){return -2;}
    }
    QQueue<SGXString> emptyFolders = QQueue<SGXString>();
    emptyFolders.enqueue(s);
    while(emptyFolders.length() > 0){
        const SGXString path = emptyFolders.dequeue();
        QVector<SGXString> foldersInside = SGXFileSystem::getFoldersList(path);
        if(foldersInside.length() > 0){
            for(int i=0; i<foldersInside.length(); i++){
                emptyFolders.enqueue(foldersInside.at(i));
            }
            emptyFolders.enqueue(path);
        }
        else{
            if(QDir().rmdir(*path.data) == false){return -2;}
        }
    }
    return 1;
}

long long SGXFileSystem::getFileSize(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == false){return -1ll;}
    return QFileInfo(*s.data).size();
}

long long SGXFileSystem::getFolderSize(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return -1ll;}
    long long totalSize = 0ll;
    QVector<SGXString> fileList = SGXFileSystem::getFilesListRecursive(s);
    for(int i=0; i<fileList.length(); i++){
        totalSize += QFileInfo(*fileList.at(i).data).size();
    }
    return totalSize;
}

SGXTimeStamp SGXFileSystem::getFileCreationTime(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == false){return SGXTimeStamp::zero;}
    return SGXTimeStamp(QFileInfo(*s.data).birthTime());
}

SGXTimeStamp SGXFileSystem::getFolderCreationTime(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return SGXTimeStamp::zero;}
    return SGXTimeStamp(QFileInfo(*s.data).birthTime());
}

SGXTimeStamp SGXFileSystem::getFileLastEditTime(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == false){return SGXTimeStamp::zero;}
    return SGXTimeStamp(QFileInfo(*s.data).lastModified());
}

SGXTimeStamp SGXFileSystem::getFolderLastEditTime(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return SGXTimeStamp::zero;}
    return SGXTimeStamp(QFileInfo(*s.data).lastModified());
}

SGXString SGXFileSystem::getFolderName(const SGXString &s){
    SGXString output = "";
    (*output.data) = QFileInfo(*s.data).fileName();
    return output;
}

SGXString SGXFileSystem::getFileName(const SGXString &s){
    SGXString output = "";
    (*output.data) = QFileInfo(*s.data).fileName();
    return output;
}

SGXString SGXFileSystem::getFileExtension(const SGXString &s){
    SGXString output = "";
    (*output.data) = QFileInfo(*s.data).suffix();
    return output;
}

SGXString SGXFileSystem::getFileNameNoExtension(const SGXString &s){
    SGXString output = "";
    (*output.data) = QFileInfo(*s.data).completeBaseName();
    return output;
}

QVector<SGXString> SGXFileSystem::getFilesListWithExtension(const SGXString &s, const SGXString &ext){
    if(SGXFileSystem::folderExists(s) == false){return QVector<SGXString>();}
    QVector<SGXString> list = SGXFileSystem::getFilesList(s);
    QVector<SGXString> finalList = QVector<SGXString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileExtension(list.at(i)) == ext){finalList.push_back(list.at(i));}
    }
    return finalList;
}

QVector<SGXString> SGXFileSystem::getFilesListWithExtensionRecursive(const SGXString &s, const SGXString &ext){
    if(SGXFileSystem::folderExists(s) == false){return QVector<SGXString>();}
    QVector<SGXString> list = SGXFileSystem::getFilesListRecursive(s);
    QVector<SGXString> finalList = QVector<SGXString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileExtension(list.at(i)) == ext){finalList.push_back(list.at(i));}
    }
    return finalList;
}

QVector<SGXString> SGXFileSystem::getFilesListContainingName(const SGXString &s, const SGXString &name){
    if(SGXFileSystem::folderExists(s) == false){return QVector<SGXString>();}
    QVector<SGXString> list = SGXFileSystem::getFilesList(s);
    QVector<SGXString> finalList = QVector<SGXString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileNameNoExtension(list.at(i)).contains(name)){finalList.push_back(list.at(i));}
    }
    return finalList;
}

QVector<SGXString> SGXFileSystem::getFilesListContainingNameRecursive(const SGXString &s, const SGXString &name){
    if(SGXFileSystem::folderExists(s) == false){return QVector<SGXString>();}
    QVector<SGXString> list = SGXFileSystem::getFilesListRecursive(s);
    QVector<SGXString> finalList = QVector<SGXString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileNameNoExtension(list.at(i)).contains(name)){finalList.push_back(list.at(i));}
    }
    return finalList;
}

bool SGXFileSystem::numberAwareLesserThan(const SGXString &s1, const SGXString &s2){
    if(s1.at(s1.length()-1) < '0' || s1.at(s1.length()-1) > '9' || s2.at(s2.length()-1) < '0' || s2.at(s2.length()-1) > '9'){return (s1 < s2);}
    int s1Number = -1;
    SGXString s1CleanedName = s1;
    {
        SGXString reversedNumber = "";
        for(int i=static_cast<int>(s1.length())-1; i>=0; i--){
            if(s1.at(i) >= '0' && s1.at(i) <= '9'){reversedNumber += s1.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=static_cast<int>(reversedNumber.length())-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        s1Number = correctNumber.parseToInt(nullptr);
        s1CleanedName = s1.substringLeft(s1.length() - correctNumber.length());
    }
    int s2Number = -1;
    SGXString s2CleanedName = s2;
    {
        SGXString reversedNumber = "";
        for(int i=static_cast<int>(s2.length())-1; i>=0; i--){
            if(s2.at(i) >= '0' && s2.at(i) <= '9'){reversedNumber += s2.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=static_cast<int>(reversedNumber.length())-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        s2Number = correctNumber.parseToInt(nullptr);
        s2CleanedName = s2.substringLeft(s2.length() - correctNumber.length());
    }
    if(s1CleanedName != s2CleanedName){return (s1CleanedName < s2CleanedName);}
    return (s1Number < s2Number);
}

bool SGXFileSystem::numberAwareLesserThanBase16(const SGXString &s1, const SGXString &s2){
    SGXChar c1 = s1.at(s1.length()-1);
    SGXChar c2 = s2.at(s2.length()-1);
    if(((c1 < '0' || c1 > '9') && (c1 < 'a' || c1 > 'f') && (c1 < 'A' || c1 > 'F')) || ((c2 < '0' || c2 > '9') && (c2 < 'a' || c2 > 'f') && (c2 < 'A' || c2 > 'F'))){return (s1 < s2);}
    int s1Number = -1;
    SGXString s1CleanedName = s1;
    {
        SGXString reversedNumber = "";
        for(int i=static_cast<int>(s1.length())-1; i>=0; i--){
            if((s1.at(i) >= '0' && s1.at(i) <= '9') || (s1.at(i) >= 'a' && s1.at(i) <= 'f') || (s1.at(i) >= 'A' && s1.at(i) <= 'F')){reversedNumber += s1.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=static_cast<int>(reversedNumber.length())-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        s1Number = correctNumber.parseToIntBase16(nullptr);
        s1CleanedName = s1.substringLeft(s1.length() - correctNumber.length());
    }
    int s2Number = -1;
    SGXString s2CleanedName = s2;
    {
        SGXString reversedNumber = "";
        for(int i=static_cast<int>(s2.length())-1; i>=0; i--){
            if((s2.at(i) >= '0' && s2.at(i) <= '9') || (s2.at(i) >= 'a' && s2.at(i) <= 'f') || (s2.at(i) >= 'A' && s2.at(i) <= 'F')){reversedNumber += s2.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=static_cast<int>(reversedNumber.length())-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        s2Number = correctNumber.parseToIntBase16(nullptr);
        s2CleanedName = s2.substringLeft(s2.length() - correctNumber.length());
    }
    if(s1CleanedName != s2CleanedName){return (s1CleanedName < s2CleanedName);}
    return (s1Number < s2Number);
}
