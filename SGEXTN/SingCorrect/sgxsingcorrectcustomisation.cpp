#include "sgxsingcorrectcustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfile.h"
#include "../containers/sglunorderedmap.h"
#include "../containers/sglhash.h"
#include "../containers/sglequalsto.h"
#include "../primitives/sgxstring.h"
#include "../primitives/sgxchar.h"
#include "sgxsingcorrectcore.h"

SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>* SGXSingCorrectCustomisation::database = nullptr;
bool SGXSingCorrectCustomisation::moduleEnabled = true;

void SGXSingCorrectCustomisation::loadFileData(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "SGEXTN/correctionconfigs.sg");
    delete SGXSingCorrectCustomisation::database;
    SGXSingCorrectCustomisation::database = new SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>();
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
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "SGEXTN/correctionconfigs.sg");
    if(SGXFileSystem::fileExists(path) == true){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFile fileWriter = SGXFile(path);
        fileWriter.writeBool(SGXSingCorrectCustomisation::moduleEnabled);
        fileWriter.writeString(SGXSingCorrectCore::correctionPrefix);
        if(SGXSingCorrectCustomisation::database != nullptr){
            fileWriter.writeInt((*SGXSingCorrectCustomisation::database).length());
            for(SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>::ConstIterator i = (*SGXSingCorrectCustomisation::database).constBegin(); i != (*SGXSingCorrectCustomisation::database).constEnd(); i++){
                fileWriter.writeString(i.key());
                fileWriter.writeSGEXTNChar(i.value());
            }
        }
        else{fileWriter.writeInt(0);}
    }
}
