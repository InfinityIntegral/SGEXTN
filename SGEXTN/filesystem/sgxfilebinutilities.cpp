#include "sgxfilebinutilities.h"
#include "sgxfilesystem.h"
#include <QFile>
#include <QDir>
#include "sgxfilewriter.h"
#include "sgxfilereader.h"
#include <QFileInfo>
#include <QHash>
#include <tuple>
#include "../primitives/sgxidentifier.h"
#include <QString>
#include "../primitives/sgxtimestamp.h"

int SGXFileBinUtilities::deletedFilesLifespan = 1000;
QHash<SGXIdentifier, std::tuple<QString, SGXTimeStamp>>* SGXFileBinUtilities::deletedFiles = nullptr;
QString SGXFileBinUtilities::pathToMetadataFile = "";

void SGXFileBinUtilities::loadBinData(){
    SGXFileBinUtilities::pathToMetadataFile = SGXFileSystem::joinFilePaths(SGXFileSystem::binFilePath, "metadata.sg");
    if(QFile::exists(SGXFileBinUtilities::pathToMetadataFile) == false){SGXFileBinUtilities::createEmptyBin();}
    SGXFileBinUtilities::deletedFiles = new QHash<SGXIdentifier, std::tuple<QString, SGXTimeStamp>>();
    {
        const SGXFileReader fileReader(SGXFileBinUtilities::pathToMetadataFile);
        SGXFileBinUtilities::deletedFilesLifespan = fileReader.readInt();
        const int deletedFilesNumber = fileReader.readInt();
        for(int i=0; i<deletedFilesNumber; i++){
            const SGXIdentifier id = fileReader.readIdentifier();
            static_cast<void>(id.registerIdentifier());
            (*SGXFileBinUtilities::deletedFiles).insert(id, std::tuple<QString, SGXTimeStamp>(fileReader.readString(), fileReader.readTimeStamp()));
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
        fileWriter.writeInt(static_cast<int>((*SGXFileBinUtilities::deletedFiles).size()));
        for(QHash<SGXIdentifier, std::tuple<QString, SGXTimeStamp>>::const_iterator i = (*SGXFileBinUtilities::deletedFiles).constBegin(); i != (*SGXFileBinUtilities::deletedFiles).constEnd(); i++){
            fileWriter.writeIdentifier(i.key());
            fileWriter.writeString(std::get<0>(i.value()));
            fileWriter.writeTimeStamp(std::get<1>(i.value()));
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
    (*SGXFileBinUtilities::deletedFiles).insert(id, std::tuple<QString, SGXTimeStamp>(s, t));
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
        (*SGXFileBinUtilities::deletedFiles).insert(id, std::tuple<QString, SGXTimeStamp>(f[i].absoluteFilePath(), t));
    }
    QDir(s).removeRecursively();
    SGXFileBinUtilities::syncMetadata();
    return 1;
}
