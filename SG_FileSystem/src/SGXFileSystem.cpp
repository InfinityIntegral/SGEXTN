#include <SGXFileSystem.h>
#include <string>
#include <cstdint>
#include <SGXString.h>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QIODevice>
#include <SGLQueue.h>
#include <SGXTimeStamp.h>
#include <SGXChar.h>
#include <SGLArray.h>
#include <SGLVector.h>
#include <QDateTime>
#include <QTimeZone>
#include <SGXFileBinUtilities.h>
#include <QStandardPaths>
#include <SGXCentral.h>
#include <QDesktopServices>
#include <QUrl>

namespace{
inline SGXString temp_stdStringToSGXString(const std::string& s){
    SGXString o = "";
    (*o.data) = QString::fromStdString(s);
    return o;
}

std::string temp_sgxStringToStdString(const SGXString& s){
    return (*s.data).toUtf8().toStdString();
}

QDateTime temp_zeroAsQDateTime = QDateTime(QDate(1965, 8, 9), QTime(10, 30, 0), QTimeZone("Asia/Singapore"));

SGXTimeStamp temp_qDateTimeToSGXTimeStamp(const QDateTime& dt){
    if(dt.isValid() == false || dt.isNull() == true){return SGXTimeStamp::zero;}
    return SGXTimeStamp((temp_zeroAsQDateTime).secsTo(dt));
}
}

SGXString SGXFileSystem::rootFilePath = "";
SGXString SGXFileSystem::userDataFilePath = "";
SGXString SGXFileSystem::configFilePath = "";

SGXString SGXFileSystem::joinFilePaths(const SGXString &a, const SGXString &b){
    SGXString a0 = a;
    SGXString b0 = b;
    SGXChar pathSeparator = SGXChar(QDir::separator().toLatin1());
    a0 = a0.replace('/', pathSeparator).replace('\\', pathSeparator);
    b0 = b0.replace('/', pathSeparator).replace('\\', pathSeparator);
    if(a0.at(a0.length() - 1) != pathSeparator){a0 += pathSeparator;}
    if(b0.at(0) == pathSeparator){b0 = b0.substringRight(b0.length() - 1);}
    return (a0 + b0);
}

SGXString SGXFileSystem::encodeBase16(const SGXString &s){
    SGXString s0 = "";
    for(int i=0; i<s.length(); i++){
        std::string thisChar = temp_sgxStringToStdString(SGXString(s.at(i)));
        if(thisChar.length() == 1){
            std::string stringToAdd = {'0', '0'};
            const uint8_t c = thisChar.at(0);
            stringToAdd.at(0) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(1) = static_cast<char>((c & 0xF) + 97);
            s0 += temp_stdStringToSGXString(stringToAdd);
        }
        else if(thisChar.length() == 2){
            std::string stringToAdd = {'x', '0', '0', '0', '0'};
            uint8_t c = thisChar.at(0);
            stringToAdd.at(1) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(2) = static_cast<char>((c & 0xF) + 97);
            c = thisChar.at(1);
            stringToAdd.at(3) = static_cast<char>((c & 0xF0) / 0xF + 97);
            stringToAdd.at(4) = static_cast<char>((c & 0xF) + 97);
            s0 += temp_stdStringToSGXString(stringToAdd);
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
            s0 += temp_stdStringToSGXString(stringToAdd);
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
            s0 += temp_stdStringToSGXString(stringToAdd);
        }
    }
    return s0;
}

SGXString SGXFileSystem::decodeBase16(const SGXString &str){
    int i = 0;
    std::string s = temp_sgxStringToStdString(str);
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
            s0 += temp_stdStringToSGXString(stringToAdd);
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
            s0 += temp_stdStringToSGXString(stringToAdd);
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
            s0 += temp_stdStringToSGXString(stringToAdd);
            i += 9;
        }
        else{
            std::string stringToAdd = {'0'};
            const uint8_t a = s.at(i);
            const uint8_t b = s.at(i+1);
            stringToAdd.at(0) = static_cast<char>(((a - 97) << 4) | (b - 97));
            s0 += temp_stdStringToSGXString(stringToAdd);
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
        for(int i=unencodedName.length()-1; i>=0; i--){
            if(unencodedName.at(i).isDigit() == true){reversedNumber += unencodedName.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=reversedNumber.length()-1; i>=0; i--){
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

SGLArray<SGXString> SGXFileSystem::getFilesList(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return SGLArray<SGXString>(0);}
    const QFileInfoList f = QDir(*s.data).entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    SGLArray<SGXString> list = SGLArray<SGXString>(static_cast<int>(f.length()));
    for(int i=0; i<f.length(); i++){
        const SGXString s0 = "";
        (*s0.data) = f.at(i).absoluteFilePath();
        list.at(i) = s0;
    }
    return list;
}

SGLArray<SGXString> SGXFileSystem::getFoldersList(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return SGLArray<SGXString>(0);}
    const QFileInfoList f = QDir(*s.data).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    SGLArray<SGXString> list = SGLArray<SGXString>(static_cast<int>(f.length()));
    for(int i=0; i<f.length(); i++){
        const SGXString s0 = "";
        (*s0.data) = f.at(i).absoluteFilePath();
        list.at(i) = s0;
    }
    return list;
}

SGLArray<SGXString> SGXFileSystem::getFilesListRecursive(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return SGLArray<SGXString>(0);}
    SGLQueue<SGXString> pathsToCheck = SGLQueue<SGXString>();
    pathsToCheck.push(s);
    SGLVector<SGXString> list = SGLVector<SGXString>();
    while(pathsToCheck.length() > 0){
        const SGXString path = pathsToCheck.front();
        pathsToCheck.pop();
        QFileInfoList f = QDir(*path.data).entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for(int i=0; i<f.length(); i++){
            const SGXString s0 = "";
            (*s0.data) = f.at(i).absoluteFilePath();
            list.pushBack(s0);
        }
        f = QDir(*path.data).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for(int i=0; i<f.length(); i++){
            const SGXString s0 = "";
            (*s0.data) = f.at(i).absoluteFilePath();
            pathsToCheck.push(s0);
        }
    }
    SGLArray<SGXString> output = SGLArray<SGXString>(list.length());
    for(int i=0; i<list.length(); i++){
        output.at(i) = list.at(i);
    }
    return output;
}

int SGXFileSystem::moveFile(const SGXString &startPath, const SGXString &endPath){
    if(SGXFileSystem::fileExists(startPath) == false || SGXFileSystem::fileExists(endPath) == true){return 0;}
    if(QFile(*startPath.data).rename(*endPath.data) == true){return 1;}
    return -2;
}

int SGXFileSystem::moveFolder(const SGXString &startPath, const SGXString &endPath){
    if(SGXFileSystem::folderExists(startPath) == false || SGXFileSystem::folderExists(endPath) == true){return 0;}
    const SGLArray<SGXString> startList = SGXFileSystem::getFilesListRecursive(startPath);
    SGLArray<SGXString> endList = SGLArray<SGXString>(startList.length());
    for(int i=0; i<startList.length(); i++){
        endList.at(i) = endPath + startList.at(i).substringRight(startList.at(i).length() - startPath.length());
    }
    for(int i=0; i<startList.length(); i++){
        const SGXString parentFolder = SGXFileSystem::getParentPath(endList.at(i));
        if(SGXFileSystem::folderExists(parentFolder) == false){SGXFileSystem::createFolder(parentFolder);}
        if(QFile(*startList.at(i).data).rename(*endList.at(i).data) == false){return -2;}
    }
    SGLQueue<SGXString> emptyFolders = SGLQueue<SGXString>();
    emptyFolders.push(startPath);
    while(emptyFolders.length() > 0){
        const SGXString path = emptyFolders.front();
        emptyFolders.pop();
        const SGLArray<SGXString> foldersInside = SGXFileSystem::getFoldersList(path);
        if(foldersInside.length() > 0){
            for(int i=0; i<foldersInside.length(); i++){
                emptyFolders.push(foldersInside.at(i));
            }
            emptyFolders.push(path);
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
    const SGLArray<SGXString> startList = SGXFileSystem::getFilesListRecursive(startPath);
    SGLArray<SGXString> endList = SGLArray<SGXString>(startList.length());
    for(int i=0; i<startList.length(); i++){
        endList.at(i) = endPath + startList.at(i).substringRight(startList.at(i).length() - startPath.length());
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
    const SGLArray<SGXString> pathList = SGXFileSystem::getFilesListRecursive(s);
    for(int i=0; i<pathList.length(); i++){
        if(QFile::remove(*pathList.at(i).data) == false){return -2;}
    }
    SGLQueue<SGXString> emptyFolders = SGLQueue<SGXString>();
    emptyFolders.push(s);
    while(emptyFolders.length() > 0){
        const SGXString path = emptyFolders.front();
        emptyFolders.pop();
        const SGLArray<SGXString> foldersInside = SGXFileSystem::getFoldersList(path);
        if(foldersInside.length() > 0){
            for(int i=0; i<foldersInside.length(); i++){
                emptyFolders.push(foldersInside.at(i));
            }
            emptyFolders.push(path);
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
    const SGLArray<SGXString> fileList = SGXFileSystem::getFilesListRecursive(s);
    for(int i=0; i<fileList.length(); i++){
        totalSize += QFileInfo(*fileList.at(i).data).size();
    }
    return totalSize;
}

SGXTimeStamp SGXFileSystem::getFileCreationTime(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == false){return SGXTimeStamp::zero;}
    return temp_qDateTimeToSGXTimeStamp(QFileInfo(*s.data).birthTime());
}

SGXTimeStamp SGXFileSystem::getFolderCreationTime(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return SGXTimeStamp::zero;}
    return temp_qDateTimeToSGXTimeStamp(QFileInfo(*s.data).birthTime());
}

SGXTimeStamp SGXFileSystem::getFileLastEditTime(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == false){return SGXTimeStamp::zero;}
    return temp_qDateTimeToSGXTimeStamp(QFileInfo(*s.data).lastModified());
}

SGXTimeStamp SGXFileSystem::getFolderLastEditTime(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return SGXTimeStamp::zero;}
    return temp_qDateTimeToSGXTimeStamp(QFileInfo(*s.data).lastModified());
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

SGLArray<SGXString> SGXFileSystem::getFilesListWithExtension(const SGXString &s, const SGXString &ext){
    if(SGXFileSystem::folderExists(s) == false){return SGLArray<SGXString>(0);}
    const SGLArray<SGXString> list = SGXFileSystem::getFilesList(s);
    SGLVector<SGXString> finalList = SGLVector<SGXString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileExtension(list.at(i)) == ext){finalList.pushBack(list.at(i));}
    }
    SGLArray<SGXString> output = SGLArray<SGXString>(finalList.length());
    for(int i=0; i<finalList.length(); i++){
        output.at(i) = finalList.at(i);
    }
    return output;
}

SGLArray<SGXString> SGXFileSystem::getFilesListWithExtensionRecursive(const SGXString &s, const SGXString &ext){
    if(SGXFileSystem::folderExists(s) == false){return SGLArray<SGXString>(0);}
    const SGLArray<SGXString> list = SGXFileSystem::getFilesListRecursive(s);
    SGLVector<SGXString> finalList = SGLVector<SGXString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileExtension(list.at(i)) == ext){finalList.pushBack(list.at(i));}
    }
    SGLArray<SGXString> output = SGLArray<SGXString>(finalList.length());
    for(int i=0; i<finalList.length(); i++){
        output.at(i) = finalList.at(i);
    }
    return output;
}

SGLArray<SGXString> SGXFileSystem::getFilesListContainingName(const SGXString &s, const SGXString &name){
    if(SGXFileSystem::folderExists(s) == false){return SGLArray<SGXString>(0);}
    const SGLArray<SGXString> list = SGXFileSystem::getFilesList(s);
    SGLVector<SGXString> finalList = SGLVector<SGXString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileNameNoExtension(list.at(i)).contains(name)){finalList.pushBack(list.at(i));}
    }
    SGLArray<SGXString> output = SGLArray<SGXString>(finalList.length());
    for(int i=0; i<finalList.length(); i++){
        output.at(i) = finalList.at(i);
    }
    return output;
}

SGLArray<SGXString> SGXFileSystem::getFilesListContainingNameRecursive(const SGXString &s, const SGXString &name){
    if(SGXFileSystem::folderExists(s) == false){return SGLArray<SGXString>(0);}
    const SGLArray<SGXString> list = SGXFileSystem::getFilesListRecursive(s);
    SGLVector<SGXString> finalList = SGLVector<SGXString>();
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::getFileNameNoExtension(list.at(i)).contains(name)){finalList.pushBack(list.at(i));}
    }
    SGLArray<SGXString> output = SGLArray<SGXString>(finalList.length());
    for(int i=0; i<finalList.length(); i++){
        output.at(i) = finalList.at(i);
    }
    return output;
}

bool SGXFileSystem::numberAwareLesserThan(const SGXString &s1, const SGXString &s2){
    SGXString s1NoExtension = SGXFileSystem::joinFilePaths(SGXFileSystem::getParentPath(s1), SGXFileSystem::getFileNameNoExtension(s1));
    int s1Number = -1;
    if(s1NoExtension.at(s1NoExtension.length() - 1).isDigit() == true){
        SGXString reversedNumber = "";
        for(int i=s1NoExtension.length()-1; i>=0; i--){
            if(s1NoExtension.at(i).isDigit() == true){reversedNumber += s1NoExtension.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=reversedNumber.length()-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        s1Number = correctNumber.parseToInt(nullptr);
        s1NoExtension = s1NoExtension.substringLeft(s1NoExtension.length() - correctNumber.length());
    }
    SGXString s2NoExtension = SGXFileSystem::joinFilePaths(SGXFileSystem::getParentPath(s2), SGXFileSystem::getFileNameNoExtension(s2));
    int s2Number = -1;
    if(s2NoExtension.at(s2NoExtension.length() - 1).isDigit() == true){
        SGXString reversedNumber = "";
        for(int i=s2NoExtension.length()-1; i>=0; i--){
            if(s2NoExtension.at(i).isDigit() == true){reversedNumber += s2NoExtension.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=reversedNumber.length()-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        s2Number = correctNumber.parseToInt(nullptr);
        s2NoExtension = s2NoExtension.substringLeft(s2NoExtension.length() - correctNumber.length());
    }
    if(s1NoExtension != s2NoExtension){return (s1NoExtension < s2NoExtension);}
    if(s1Number != s2Number){return (s1Number < s2Number);}
    return (SGXFileSystem::getFileExtension(s1) < SGXFileSystem::getFileExtension(s2));
}

bool SGXFileSystem::numberAwareLesserThanBase16(const SGXString &s1, const SGXString &s2){
    SGXString s1NoExtension = SGXFileSystem::joinFilePaths(SGXFileSystem::getParentPath(s1), SGXFileSystem::getFileNameNoExtension(s1));
    int s1Number = -1;
    if(s1NoExtension.at(s1NoExtension.length() - 1).isDigitBase16() == true){
        SGXString reversedNumber = "";
        for(int i=s1NoExtension.length()-1; i>=0; i--){
            if(s1NoExtension.at(i).isDigitBase16() == true){reversedNumber += s1NoExtension.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=reversedNumber.length()-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        s1Number = correctNumber.parseToInt(nullptr);
        s1NoExtension = s1NoExtension.substringLeft(s1NoExtension.length() - correctNumber.length());
    }
    SGXString s2NoExtension = SGXFileSystem::joinFilePaths(SGXFileSystem::getParentPath(s2), SGXFileSystem::getFileNameNoExtension(s2));
    int s2Number = -1;
    if(s2NoExtension.at(s2NoExtension.length() - 1).isDigitBase16() == true){
        SGXString reversedNumber = "";
        for(int i=s2NoExtension.length()-1; i>=0; i--){
            if(s2NoExtension.at(i).isDigitBase16() == true){reversedNumber += s2NoExtension.at(i);}
            else{break;}
        }
        SGXString correctNumber = "";
        for(int i=reversedNumber.length()-1; i>=0; i--){
            correctNumber += reversedNumber.at(i);
        }
        s2Number = correctNumber.parseToInt(nullptr);
        s2NoExtension = s2NoExtension.substringLeft(s2NoExtension.length() - correctNumber.length());
    }
    if(s1NoExtension != s2NoExtension){return (s1NoExtension < s2NoExtension);}
    if(s1Number != s2Number){return (s1Number < s2Number);}
    return (SGXFileSystem::getFileExtension(s1) < SGXFileSystem::getFileExtension(s2));
}

bool SGXNumberAwareFilePathLesserThan::operator()(const SGXString& a, const SGXString& b){
    return SGXFileSystem::numberAwareLesserThan(a, b);
}

bool SGXNumberAwareFilePathMoreThan::operator()(const SGXString& a, const SGXString& b){
    return SGXFileSystem::numberAwareLesserThan(b, a);
}

bool SGXNumberAwareFilePathLesserThanBase16::operator()(const SGXString& a, const SGXString& b){
    return SGXFileSystem::numberAwareLesserThanBase16(a, b);
}

bool SGXNumberAwareFilePathMoreThanBase16::operator()(const SGXString& a, const SGXString& b){
    return SGXFileSystem::numberAwareLesserThanBase16(b, a);
}

void SGXFileSystem::initialiseAppFolder(){
    const SGXString standardPath = "";
    (*standardPath.data) = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    SGXFileSystem::rootFilePath = SGXFileSystem::joinFilePaths(standardPath, SGXCentral::folderName);
    SGXFileSystem::userDataFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "yourdata");
    SGXFileSystem::configFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "settings");
    SGXFileBinUtilities::binFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "recyclebin");
    if(SGXFileSystem::folderExists(SGXFileSystem::userDataFilePath) == false){SGXFileSystem::createFolder(SGXFileSystem::userDataFilePath);}
    if(SGXFileSystem::folderExists(SGXFileSystem::configFilePath) == false){SGXFileSystem::createFolder(SGXFileSystem::configFilePath);}
    SGXFileBinUtilities::loadBinData();
}

void SGXFileSystem::openLink(const SGXString &link){
    QDesktopServices::openUrl(static_cast<QUrl>(QString("https://") + (*link.data)));
}
