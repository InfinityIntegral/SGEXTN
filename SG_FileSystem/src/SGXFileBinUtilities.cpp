#include <SGXFileBinUtilities.h>
#include <SGXFileSystem.h>
#include <QFile>
#include <QDir>
#include <SGXFile.h>
#include <QFileInfo>
#include <SGLPair.h>
#include <SGXIdentifier.h>
#include <SGXString.h>
#include <SGXTimeStamp.h>
#include <SGLUnorderedMap.h>
#include <SGLEqualsTo.h>
#include <SGLHash.h>

int SGXFileBinUtilities::lifespan = 1000;
SGLUnorderedMap<SGXIdentifier, SGLPair<SGXString, SGXTimeStamp>, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>* SGXFileBinUtilities::deletedFiles = nullptr;
SGXString SGXFileBinUtilities::pathToMetadataFile = "";
SGXString SGXFileBinUtilities::binFilePath = "";

void SGXFileBinUtilities::loadBinData(){
    SGXFileBinUtilities::pathToMetadataFile = SGXFileSystem::joinFilePaths(SGXFileBinUtilities::binFilePath, "metadata.sg");
    if(SGXFileSystem::fileExists(SGXFileBinUtilities::pathToMetadataFile) == false){SGXFileBinUtilities::createEmptyBin();}
    SGXFileBinUtilities::deletedFiles = new SGLUnorderedMap<SGXIdentifier, SGLPair<SGXString, SGXTimeStamp>, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>();
    {
        const SGXFile fileReader(SGXFileBinUtilities::pathToMetadataFile);
        SGXFileBinUtilities::lifespan = fileReader.readInt();
        const int deletedFilesNumber = fileReader.readInt();
        for(int i=0; i<deletedFilesNumber; i++){
            const SGXIdentifier id = fileReader.readIdentifier();
            static_cast<void>(id.registerIdentifier());
            (*SGXFileBinUtilities::deletedFiles).insert(id, SGLPair<SGXString, SGXTimeStamp>(fileReader.readString(), fileReader.readTimeStamp()));
        }
    }
    for(SGLUnorderedMap<SGXIdentifier, SGLPair<SGXString, SGXTimeStamp>, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>::ConstIterator i = (*SGXFileBinUtilities::deletedFiles).constBegin(); i != (*SGXFileBinUtilities::deletedFiles).constEnd(); i++){
        const int f = static_cast<int>(SGXTimeStamp::now().getDaysFrom(i.value().second));
        if(f > SGXFileBinUtilities::lifespan){SGXFileBinUtilities::permanentDeleteFile(i.key());}
    }
}

void SGXFileBinUtilities::createEmptyBin(){
    if(SGXFileSystem::folderExists(SGXFileBinUtilities::binFilePath) == true){SGXFileSystem::permanentDeleteFolder(SGXFileBinUtilities::binFilePath);}
    SGXFileSystem::createFile(SGXFileBinUtilities::pathToMetadataFile);
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
        fileWriter.writeInt((*SGXFileBinUtilities::deletedFiles).length());
        for(SGLUnorderedMap<SGXIdentifier, SGLPair<SGXString, SGXTimeStamp>, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>::ConstIterator i = (*SGXFileBinUtilities::deletedFiles).constBegin(); i != (*SGXFileBinUtilities::deletedFiles).constEnd(); i++){
            fileWriter.writeIdentifier(i.key());
            fileWriter.writeString(i.value().first);
            fileWriter.writeTimeStamp(i.value().second);
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
    (*SGXFileBinUtilities::deletedFiles).insert(id, SGLPair<SGXString, SGXTimeStamp>(s, t));
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
        (*SGXFileBinUtilities::deletedFiles).insert(id, SGLPair<SGXString, SGXTimeStamp>(fileName, t));
    }
    SGXFileSystem::permanentDeleteFolder(s);
    SGXFileBinUtilities::syncMetadata();
    return 1;
}

int SGXFileBinUtilities::restoreFile(SGXIdentifier x){
    if((*SGXFileBinUtilities::deletedFiles).contains(x) == false){return 0;}
    const SGXString filePath = (*SGXFileBinUtilities::deletedFiles).at(x).first;
    const SGXString binPath = SGXFileSystem::joinFilePaths(SGXFileBinUtilities::binFilePath, x.getStringForPrinting() + ".sg");
    if(SGXFileSystem::fileExists(filePath) == true){return -3;}
    if(SGXFileSystem::moveFile(binPath, filePath) != 1){return -2;}
    (*SGXFileBinUtilities::deletedFiles).erase(x);
    SGXFileBinUtilities::syncMetadata();
    return 1;
}

int SGXFileBinUtilities::permanentDeleteFile(SGXIdentifier x){
    if((*SGXFileBinUtilities::deletedFiles).contains(x) == false){return 0;}
    const SGXString binPath = SGXFileSystem::joinFilePaths(SGXFileBinUtilities::binFilePath, x.getStringForPrinting() + ".sg");
    if(QFile::remove(*binPath.data) == false){return -2;}
    (*SGXFileBinUtilities::deletedFiles).erase(x);
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
