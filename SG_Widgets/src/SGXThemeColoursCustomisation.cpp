#include <SGXThemeColoursCustomisation.h>
#include <SGXFileSystem.h>
#include <SGXFile.h>
#include <SGXTimeStamp.h>
#include <SGXColourRGBA.h>
#include <SGXString.h>
#include <SGLArray.h>

SGLArray<SGXColourRGBA> SGXThemeColoursCustomisation::themeColours = SGLArray<SGXColourRGBA>(SGXColourRGBA(202, 0, 159), SGXColourRGBA(177, 0, 139), SGXColourRGBA(148, 0, 116), SGXColourRGBA(255, 249, 253), SGXColourRGBA(255, 237, 248), SGXColourRGBA(255, 224, 243));

void SGXThemeColoursCustomisation::loadThemeColours(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "SGEXTN/themecolours.sg");
    if(SGXFileSystem::fileExists(path) == false){return;}
    {
        const SGXFile fileReader(path, SGXFile::ReadOnly);
        int colourCount = fileReader.readInt();
        SGLArray<SGXColourRGBA> arr(colourCount);
        for(int i=0; i<colourCount; i++){
            arr.at(i) = fileReader.readColourRGBA();
        }
    }
}

void SGXThemeColoursCustomisation::syncThemeColours(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "SGEXTN/themecolours.sg");
    if(SGXFileSystem::fileExists(path) == true){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFile fileWriter(path, SGXFile::WriteOnly);
        fileWriter.writeInt(SGXThemeColoursCustomisation::themeColours.length());
        for(int i=0; i<SGXThemeColoursCustomisation::themeColours.length(); i++){
            fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColours.at(i));
        }
    }
}
