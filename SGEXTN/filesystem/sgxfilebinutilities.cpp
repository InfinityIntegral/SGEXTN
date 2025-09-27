#include "sgxfilebinutilities.h"
#include "sgxfilesystem.h"
#include <QFile>
#include <QDir>
#include "sgxfile.h"
#include <QFileInfo>
#include <QHash>
#include <tuple>
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxstring.h"
#include "../primitives/sgxtimestamp.h"

int SGXFileBinUtilities::lifespan = 1000;
QHash<SGXIdentifier, std::tuple<SGXString, SGXTimeStamp>>* SGXFileBinUtilities::deletedFiles = nullptr;
SGXString SGXFileBinUtilities::pathToMetadataFile = "";
SGXString SGXFileBinUtilities::binFilePath = "";

void SGXFileBinUtilities::loadBinData(){
    SGXFileBinUtilities::pathToMetadataFile = SGXFileSystem::joinFilePaths(SGXFileBinUtilities::binFilePath, "metadata.sg");
    if(SGXFileSystem::fileExists(SGXFileBinUtilities::pathToMetadataFile) == false){SGXFileBinUtilities::createEmptyBin();}
    SGXFileBinUtilities::deletedFiles = new QHash<SGXIdentifier, std::tuple<SGXString, SGXTimeStamp>>();
    {
        const SGXFile fileReader(SGXFileBinUtilities::pathToMetadataFile);
        SGXFileBinUtilities::lifespan = fileReader.readInt();
        const int deletedFilesNumber = fileReader.readInt();
        for(int i=0; i<deletedFilesNumber; i++){
            const SGXIdentifier id = fileReader.readIdentifier();
            static_cast<void>(id.registerIdentifier());
            (*SGXFileBinUtilities::deletedFiles).insert(id, std::tuple<SGXString, SGXTimeStamp>(fileReader.readString(), fileReader.readTimeStamp()));
        }
    }
    for(QHash<SGXIdentifier, std::tuple<SGXString, SGXTimeStamp>>::const_iterator i = (*SGXFileBinUtilities::deletedFiles).constBegin(); i != (*SGXFileBinUtilities::deletedFiles).constEnd(); i++){
        const int f = static_cast<int>(SGXTimeStamp::now().getDaysFrom(std::get<1>(i.value())));
        if(f > SGXFileBinUtilities::lifespan){SGXFileBinUtilities::permanentDeleteFile(i.key());}
    }
}

void SGXFileBinUtilities::createEmptyBin(){
    if(SGXFileSystem::folderExists(SGXFileBinUtilities::binFilePath) == true){SGXFileSystem::permanentDeleteFolder(SGXFileBinUtilities::binFilePath);}
    SGXFileSystem::createFolder(SGXFileBinUtilities::binFilePath);
    {
        const SGXFile fileWriter(SGXFileBinUtilities::pathToMetadataFile);
        fileWriter.writeInt(SGXFileBinUtilities::lifespan);
        fileWriter.writeInt(0);
    }
}

void SGXFileBinUtilities::syncMetadata(){
    {
        const SGXFile fileWriter(SGXFileBinUtilities::pathToMetadataFile);
        fileWriter.writeInt(SGXFileBinUtilities::lifespan);
        fileWriter.writeInt(static_cast<int>((*SGXFileBinUtilities::deletedFiles).size()));
        for(QHash<SGXIdentifier, std::tuple<SGXString, SGXTimeStamp>>::const_iterator i = (*SGXFileBinUtilities::deletedFiles).constBegin(); i != (*SGXFileBinUtilities::deletedFiles).constEnd(); i++){
            fileWriter.writeIdentifier(i.key());
            fileWriter.writeString(std::get<0>(i.value()));
            fileWriter.writeTimeStamp(std::get<1>(i.value()));
        }
    }
}

int SGXFileBinUtilities::deleteFile(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == false){return 0;}
    const SGXIdentifier id = SGXIdentifier(true);
    const SGXTimeStamp t = SGXTimeStamp::now();
    const SGXString endPath = SGXFileSystem::joinFilePaths(SGXFileBinUtilities::binFilePath, id.getStringForPrinting() + ".sg");
    if(SGXFileSystem::moveFile(s, endPath) != 1){return -2;}
    static_cast<void>(id.registerIdentifier());
    (*SGXFileBinUtilities::deletedFiles).insert(id, std::tuple<SGXString, SGXTimeStamp>(s, t));
    SGXFileBinUtilities::syncMetadata();
    return 1;
}

int SGXFileBinUtilities::deleteFolder(const SGXString &s){
    if(SGXFileSystem::folderExists(s) == false){return 0;}
    const QFileInfoList f = QDir(*s.data).entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for(int i=0; i<f.length(); i++){
        const SGXIdentifier id = SGXIdentifier(true);
        const SGXTimeStamp t = SGXTimeStamp::now();
        const SGXString endPath = SGXFileSystem::joinFilePaths(SGXFileBinUtilities::binFilePath, id.getStringForPrinting() + ".sg");
        const SGXString fileName = "";
        (*fileName.data) = f.at(i).absoluteFilePath();
        if(SGXFileSystem::moveFile(fileName, endPath) != 1){return -2;}
        static_cast<void>(id.registerIdentifier());
        (*SGXFileBinUtilities::deletedFiles).insert(id, std::tuple<SGXString, SGXTimeStamp>(fileName, t));
    }
    SGXFileSystem::permanentDeleteFolder(s);
    SGXFileBinUtilities::syncMetadata();
    return 1;
}

int SGXFileBinUtilities::restoreFile(SGXIdentifier x){
    if((*SGXFileBinUtilities::deletedFiles).contains(x) == false){return 0;}
    const SGXString filePath = std::get<0>((*SGXFileBinUtilities::deletedFiles)[x]);
    const SGXString binPath = SGXFileSystem::joinFilePaths(SGXFileBinUtilities::binFilePath, x.getStringForPrinting() + ".sg");
    if(SGXFileSystem::fileExists(filePath) == true){return -3;}
    if(SGXFileSystem::moveFile(binPath, filePath) != 1){return -2;}
    (*SGXFileBinUtilities::deletedFiles).remove(x);
    SGXFileBinUtilities::syncMetadata();
    return 1;
}

int SGXFileBinUtilities::permanentDeleteFile(SGXIdentifier x){
    if((*SGXFileBinUtilities::deletedFiles).contains(x) == false){return 0;}
    const SGXString binPath = SGXFileSystem::joinFilePaths(SGXFileBinUtilities::binFilePath, x.getStringForPrinting() + ".sg");
    if(QFile::remove(*binPath.data) == false){return -2;}
    (*SGXFileBinUtilities::deletedFiles).remove(x);
    SGXFileBinUtilities::syncMetadata();
    return 1;
}

void SGXFileBinUtilities::permanentClearBin(){
    SGXFileBinUtilities::createEmptyBin();
}

int SGXFileBinUtilities::getLifespan(){
    return SGXFileBinUtilities::lifespan;
}

void SGXFileBinUtilities::setLifespan(int x){
    SGXFileBinUtilities::lifespan = x;
    {
        const SGXFile fileWriter(SGXFileBinUtilities::pathToMetadataFile);
        fileWriter.writeInt(SGXFileBinUtilities::lifespan);
    }
}
