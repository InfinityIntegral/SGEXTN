#include "sgxfilezip.h"
#include "sgxfilesystem.h"
#include "sgxfilereader.h"
#include "sgxfilewriter.h"
#include <QString>
#include <qcontainerfwd.h>
#include <QByteArray>
#include <tuple>

int SGXFileZip::makeZip(const QString &path, const QString &zipLocation){
    if(SGXFileSystem::pathIsValid(path) == false || SGXFileSystem::pathIsValid(zipLocation) == false){return -1;}
    if(SGXFileSystem::folderExists(path) != 1 || SGXFileSystem::fileExists(zipLocation) != 0){return 0;}
    QVector<QString> absolutePaths = SGXFileSystem::getFilesListRecursive(path);
    QVector<QString> relativePaths = QVector<QString>();
    QVector<long long> addressLocations = QVector<long long>();
    for(int i=0; i<absolutePaths.length(); i++){
        relativePaths.push_back(absolutePaths[i].mid(path.length()));
    }
    {
        const SGXFileWriter fileWriter(zipLocation);
        fileWriter.writeInt(static_cast<int>(absolutePaths.length()));
        for(int i=0; i<absolutePaths.length(); i++){
            fileWriter.writeString(relativePaths[i]);
            addressLocations.push_back(fileWriter.getPointerLocation());
            fileWriter.setPointerLocation(fileWriter.getPointerLocation() + 16ll);
        }
        for(int i=0; i<absolutePaths.length(); i++){
            QByteArray fileContents;
            {
                const SGXFileReader fileReader(absolutePaths[i]);
                fileContents = fileReader.readAllBytes();
            }
            const long long beginLocation = fileWriter.getPointerLocation();
            fileWriter.writeBytes(fileContents);
            const long long fileLength = fileWriter.getPointerLocation() - beginLocation;
            const long long thisLocation = fileWriter.getPointerLocation();
            fileWriter.setPointerLocation(addressLocations[i]);
            fileWriter.writeLongLong(beginLocation);
            fileWriter.writeLongLong(fileLength);
            fileWriter.setPointerLocation(thisLocation);
        }
    }
    return 1;
}

int SGXFileZip::makeZip(const QVector<QString> &list, const QString &zipLocation){
    if(SGXFileSystem::pathIsValid(zipLocation) == false){return -1;}
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::pathIsValid(list[i]) == false){return -1;}
    }
    if(SGXFileSystem::fileExists(zipLocation) != 0){return 0;}
    for(int i=0; i<list.length(); i++){
        if(SGXFileSystem::fileExists(list[i]) != 1){return 0;}
    }
    QString path = list[0];
    for(int i=1; i<list.length(); i++){
        int l = 0;
        int h = static_cast<int>(path.length()) + 1;
        while(h - l > 1){
            const int m = (l + h) / 2;
            if(list[i].length() >= m && list[i].left(m) == path.left(m)){l = m;}
            else{h = m;}
        }
        path = path.left(l);
    }
    QVector<QString> relativePaths = QVector<QString>();
    QVector<long long> addressLocations = QVector<long long>();
    for(int i=0; i<list.length(); i++){
        relativePaths.push_back(list[i].mid(path.length()));
    }
    {
        const SGXFileWriter fileWriter(zipLocation);
        fileWriter.writeInt(static_cast<int>(list.length()));
        for(int i=0; i<list.length(); i++){
            fileWriter.writeString(relativePaths[i]);
            addressLocations.push_back(fileWriter.getPointerLocation());
            fileWriter.setPointerLocation(fileWriter.getPointerLocation() + 16ll);
        }
        for(int i=0; i<list.length(); i++){
            QByteArray fileContents;
            {
                const SGXFileReader fileReader(list[i]);
                fileContents = fileReader.readAllBytes();
            }
            const long long beginLocation = fileWriter.getPointerLocation();
            fileWriter.writeBytes(fileContents);
            const long long fileLength = fileWriter.getPointerLocation() - beginLocation;
            const long long thisLocation = fileWriter.getPointerLocation();
            fileWriter.setPointerLocation(addressLocations[i]);
            fileWriter.writeLongLong(beginLocation);
            fileWriter.writeLongLong(fileLength);
            fileWriter.setPointerLocation(thisLocation);
        }
    }
    return 1;
}

int SGXFileZip::unpackZip(const QString &zipLocation, const QString &path){
    if(SGXFileSystem::pathIsValid(zipLocation) == false){return -1;}
    if(SGXFileSystem::pathIsValid(path) == false){return -1;}
    if(SGXFileSystem::fileExists(zipLocation) != 1){return 0;}
    if(SGXFileSystem::folderExists(path) != 0){return 0;}
    SGXFileSystem::createFolder(path);
    {
        const SGXFileReader fileReader(zipLocation);
        const int n = fileReader.readInt();
        for(int i=0; i<n; i++){
            const QString relativePath = fileReader.readString();
            const QString actualPath = SGXFileSystem::joinFilePaths(path, relativePath);
            SGXFileSystem::createFile(actualPath);
            {
                const long long fileOffset = fileReader.readLongLong();
                const long long fileLength = fileReader.readLongLong();
                const long long thisLocation = fileReader.getPointerLocation();
                fileReader.setPointerLocation(fileOffset);
                {
                    const SGXFileWriter fileWriter(actualPath);
                    fileWriter.writeBytes(fileReader.readBytes(fileLength));
                }
                fileReader.setPointerLocation(thisLocation);
            }
        }
    }
    return 1;
}

int SGXFileZip::unpackSingleFileFromZip(const QString &fileName, const QString &zipLocation, const QString &path){
    if(SGXFileSystem::pathIsValid(zipLocation) == false){return -1;}
    if(SGXFileSystem::pathIsValid(path) == false){return -1;}
    if(SGXFileSystem::fileExists(zipLocation) != 1){return 0;}
    if(SGXFileSystem::fileExists(path) != 0){return 0;}
    {
        const SGXFileReader fileReader(zipLocation);
        const int n = fileReader.readInt();
        for(int i=0; i<n; i++){
            const QString s = fileReader.readString();
            if(s == fileName){
                const long long fileOffset = fileReader.readLongLong();
                const long long fileLength = fileReader.readLongLong();
                fileReader.setPointerLocation(fileOffset);
                const QByteArray fileContents = fileReader.readBytes(fileLength);
                SGXFileSystem::createFile(path);
                {
                    const SGXFileWriter fileWriter(path);
                    fileWriter.writeBytes(fileContents);
                }
                return 1;
            }
            fileReader.setPointerLocation(fileReader.getPointerLocation() + 16ll);
        }
    }
    return 0;
}

QVector<std::tuple<QString, long long>> SGXFileZip::getContentsListFromZip(const QString &zipLocation){
    if(SGXFileSystem::pathIsValid(zipLocation) == false){return QVector<std::tuple<QString, long long>>();}
    if(SGXFileSystem::fileExists(zipLocation) != 1){return QVector<std::tuple<QString, long long>>();}
    QVector<std::tuple<QString, long long>> contentsList = QVector<std::tuple<QString, long long>>();
    {
        const SGXFileReader fileReader(zipLocation);
        const int n = fileReader.readInt();
        for(int i=0; i<n; i++){
            const QString fileName = fileReader.readString();
            fileReader.setPointerLocation(fileReader.getPointerLocation() + 8ll);
            const long long fileLength = fileReader.readLongLong();
            contentsList.push_back(std::tuple<QString, long long>(fileName, fileLength));
        }
    }
    return contentsList;
}
