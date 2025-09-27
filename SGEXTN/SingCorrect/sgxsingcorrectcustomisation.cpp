#include "sgxsingcorrectcustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfile.h"
#include <QHash>
#include "../primitives/sgxstring.h"
#include "../primitives/sgxchar.h"
#include "sgxsingcorrectcore.h"

QHash<SGXString, SGXChar>* SGXSingCorrectCustomisation::database = nullptr;
bool SGXSingCorrectCustomisation::moduleEnabled = true;

void SGXSingCorrectCustomisation::loadFileData(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "correctionconfigs.sg");
    delete SGXSingCorrectCustomisation::database;
    SGXSingCorrectCustomisation::database = new QHash<SGXString, SGXChar>();
    if(SGXFileSystem::fileExists(path) == false){return;}
    {
        const SGXFile fileReader = SGXFile(path);
        SGXSingCorrectCustomisation::moduleEnabled = fileReader.readBool();
        SGXSingCorrectCore::correctionPrefix = fileReader.readString();
        const int n = fileReader.readInt();
        for(int i=0; i<n; i++){
            const SGXString k = fileReader.readString();
            const SGXChar v = fileReader.readSGEXTNChar();
            (*SGXSingCorrectCustomisation::database).insert(k, v);
        }
    }
}

void SGXSingCorrectCustomisation::syncFileData(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "correctionconfigs.sg");
    if(SGXFileSystem::fileExists(path) == true){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFile fileWriter = SGXFile(path);
        fileWriter.writeBool(SGXSingCorrectCustomisation::moduleEnabled);
        fileWriter.writeString(SGXSingCorrectCore::correctionPrefix);
        if(SGXSingCorrectCustomisation::database != nullptr){
            fileWriter.writeInt(static_cast<int>((*SGXSingCorrectCustomisation::database).size()));
            for(QHash<SGXString, SGXChar>::const_iterator i = (*SGXSingCorrectCustomisation::database).begin(); i != (*SGXSingCorrectCustomisation::database).end(); i++){
                fileWriter.writeString(i.key());
                fileWriter.writeSGEXTNChar(i.value());
            }
        }
        else{fileWriter.writeInt(0);}
    }
}
