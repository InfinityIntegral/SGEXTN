#include "sgxfilebinutilities.h"
#include "sgxfilesystem.h"
#include <QFile>
#include <QDir>
#include "sgxfilewriter.h"
#include "sgxfilereader.h"
#include <QFileInfo>
#include <qcontainerfwd.h>
#include <tuple>
#include "../primitives/sgxidentifier.h"
#include <QString>
#include "../primitives/sgxtimestamp.h"

int SGXFileBinUtilities::deletedFilesLifespan = 1000;
QVector<std::tuple<SGXIdentifier, QString, SGXTimeStamp>>* SGXFileBinUtilities::deletedFiles = nullptr;
QString SGXFileBinUtilities::pathToMetadataFile = "";

void SGXFileBinUtilities::loadBinData(){
    SGXFileBinUtilities::pathToMetadataFile = SGXFileSystem::joinFilePaths(SGXFileSystem::binFilePath, "metadata.sg");
    if(QFile::exists(SGXFileBinUtilities::pathToMetadataFile) == false){SGXFileBinUtilities::createEmptyBin();}
    SGXFileBinUtilities::deletedFiles = new QVector<std::tuple<SGXIdentifier, QString, SGXTimeStamp>>();
    {
        const SGXFileReader fileReader(SGXFileBinUtilities::pathToMetadataFile);
        SGXFileBinUtilities::deletedFilesLifespan = fileReader.readInt();
        const int deletedFilesNumber = fileReader.readInt();
        for(int i=0; i<deletedFilesNumber; i++){
            const SGXIdentifier id = fileReader.readIdentifier();
            static_cast<void>(id.registerIdentifier());
            (*SGXFileBinUtilities::deletedFiles).push_back(std::tuple<SGXIdentifier, QString, SGXTimeStamp>(id, fileReader.readString(), fileReader.readTimeStamp()));
        }
    }
}

void SGXFileBinUtilities::createEmptyBin(){
    if(QDir(SGXFileSystem::binFilePath).exists() == true){QDir(SGXFileSystem::binFilePath).removeRecursively();}
    QDir().mkpath(SGXFileSystem::binFilePath);
    {
        const SGXFileWriter fileWriter(SGXFileBinUtilities::pathToMetadataFile);
        fileWriter.writeInt(SGXFileBinUtilities::deletedFilesLifespan);
        fileWriter.writeInt(0);
    }
}

void SGXFileBinUtilities::syncMetadata(){
    {
        const SGXFileWriter fileWriter(SGXFileBinUtilities::pathToMetadataFile);
        fileWriter.writeInt(SGXFileBinUtilities::deletedFilesLifespan);
        fileWriter.writeInt(static_cast<int>((*SGXFileBinUtilities::deletedFiles).length()));
        for(int i=0; i<(*SGXFileBinUtilities::deletedFiles).length(); i++){
            fileWriter.writeIdentifier(std::get<0>((*SGXFileBinUtilities::deletedFiles)[i]));
            fileWriter.writeString(std::get<1>((*SGXFileBinUtilities::deletedFiles)[i]));
            fileWriter.writeTimeStamp(std::get<2>((*SGXFileBinUtilities::deletedFiles)[i]));
        }
    }
}

int SGXFileBinUtilities::deleteFile(const QString &s){
    if(SGXFileSystem::pathIsSubfolder(s, SGXFileSystem::userDataFilePath) == false){return -1;}
    if(QFile::exists(s) == false){return 0;}
    const SGXIdentifier id = SGXIdentifier(true);
    const SGXTimeStamp t = SGXTimeStamp::now();
    const QString endPath = SGXFileSystem::joinFilePaths(SGXFileSystem::binFilePath, id.getStringForPrinting() + ".sg");
    if(QFile(s).rename(endPath) == false){return -2;}
    static_cast<void>(id.registerIdentifier());
    (*SGXFileBinUtilities::deletedFiles).push_back(std::tuple<SGXIdentifier, QString, SGXTimeStamp>(id, s, t));
    SGXFileBinUtilities::syncMetadata();
    return 1;
}

int SGXFileBinUtilities::deleteFolder(const QString &s){
    if(SGXFileSystem::pathIsSubfolder(s, SGXFileSystem::userDataFilePath) == false){return -1;}
    if(QDir(s).exists() == false){return 0;}
    QFileInfoList f = QDir(s).entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for(int i=0; i<f.length(); i++){
        const SGXIdentifier id = SGXIdentifier(true);
        const SGXTimeStamp t = SGXTimeStamp::now();
        const QString endPath = SGXFileSystem::joinFilePaths(SGXFileSystem::binFilePath, id.getStringForPrinting() + ".sg");
        if(QFile(f[i].absoluteFilePath()).rename(endPath) == false){return -2;}
        static_cast<void>(id.registerIdentifier());
        (*SGXFileBinUtilities::deletedFiles).push_back(std::tuple<SGXIdentifier, QString, SGXTimeStamp>(id, f[i].absoluteFilePath(), t));
    }
    QDir(s).removeRecursively();
    SGXFileBinUtilities::syncMetadata();
    return 1;
}
