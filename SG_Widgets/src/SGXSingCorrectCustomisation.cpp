#include <private_api_Widgets/SGXSingCorrectCustomisation.h>
#include <SGXFileSystem.h>
#include <SGXFile.h>
#include <SGLUnorderedMap.h>
#include <SGLHash.h>
#include <SGLEqualsTo.h>
#include <SGXString.h>
#include <SGXChar.h>
#include <SGXSingCorrectCore.h>

SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>* SGXSingCorrectCustomisation::database = nullptr;
bool SGXSingCorrectCustomisation::moduleEnabled = true;

void SGXSingCorrectCustomisation::loadFileData(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "SGEXTN/correctionconfigs.sg");
    delete SGXSingCorrectCustomisation::database;
    SGXSingCorrectCustomisation::database = new SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>();
    if(SGXFileSystem::fileExists(path) == false){return;}
    {
        const SGXFile fileReader = SGXFile(path, SGXFile::ReadOnly);
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
        const SGXFile fileWriter = SGXFile(path, SGXFile::WriteOnly);
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
