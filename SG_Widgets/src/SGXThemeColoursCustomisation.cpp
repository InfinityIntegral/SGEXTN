#include <SGXThemeColoursCustomisation.h>
#include <SGXFileSystem.h>
#include <SGXFile.h>
#include <SGXTimeStamp.h>
#include <SGXColourRGBA.h>
#include <SGXString.h>
#include <SGLArray.h>

SGLArray<SGXColourRGBA> SGXThemeColoursCustomisation::themeColours = SGLArray<SGXColourRGBA>(SGXColourRGBA(153, 0, 120), SGXColourRGBA(115, 0, 90), SGXColourRGBA(77, 0, 60), SGXColourRGBA(255, 242, 252), SGXColourRGBA(255, 217, 247), SGXColourRGBA(255, 191, 241));

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
