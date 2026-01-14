#include <SGXThemeColoursCustomisation.h>
#include <SGXFileSystem.h>
#include <SGXFile.h>
#include <SGXTimeStamp.h>
#include <SGXColourRGBA.h>
#include <SGXString.h>
#include <SGLArray.h>
#include <SGXThemeColours.h>

SGLArray<SGXColourRGBA> SGXThemeColoursCustomisation::themeColours = SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(255, 0, 200), false);

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
        SGXThemeColoursCustomisation::themeColours = arr;
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
