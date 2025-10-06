#include "sgxfontsizecustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfile.h"
#include "../primitives/sgxstring.h"
#include "../quickui/sgxquickresizer.h"
#include "../quickui/sgxquickinterface.h"

float SGXFontSizeCustomisation::fontSize = 0.05f;
float SGXFontSizeCustomisation::defaultFontSize = 0.05f; // 0.05 for desktop, 0.08 for mobile

void SGXFontSizeCustomisation::loadFontSize(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "SGEXTN/fontsize.sg");
    if(SGXFileSystem::fileExists(path) == false){return;}
    {
        const SGXFile fileReader(path);
        SGXFontSizeCustomisation::fontSize = fileReader.readFloat() * SGXFontSizeCustomisation::defaultFontSize;
    }
}

void SGXFontSizeCustomisation::syncFontSize(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "SGEXTN/fontsize.sg");
    if(SGXFileSystem::fileExists(path) == true){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFile fileWriter(path);
        fileWriter.writeFloat(SGXFontSizeCustomisation::fontSize / SGXFontSizeCustomisation::defaultFontSize);
    }
}

void SGXFontSizeCustomisation::updateFontSize(){
    (*SGXQuickInterface::resizerSingleton).updateAppWindowSize();
}
