#include "sgxthemecolourscustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfile.h"
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxstring.h"

SGXColourRGBA SGXThemeColoursCustomisation::themeColour0 = SGXColourRGBA(0, 0, 0);
SGXColourRGBA SGXThemeColoursCustomisation::themeColour1 = SGXColourRGBA(64, 0, 50);
SGXColourRGBA SGXThemeColoursCustomisation::themeColour2 = SGXColourRGBA(128, 0, 100);
SGXColourRGBA SGXThemeColoursCustomisation::themeColour3 = SGXColourRGBA(191, 0, 150);
SGXColourRGBA SGXThemeColoursCustomisation::themeColour4 = SGXColourRGBA(255, 0, 200);
SGXColourRGBA SGXThemeColoursCustomisation::themeColour5 = SGXColourRGBA(255, 64, 214);
SGXColourRGBA SGXThemeColoursCustomisation::themeColour6 = SGXColourRGBA(255, 128, 227);
SGXColourRGBA SGXThemeColoursCustomisation::themeColour7 = SGXColourRGBA(255, 191, 241);
SGXColourRGBA SGXThemeColoursCustomisation::themeColour8 = SGXColourRGBA(255, 255, 255);

void SGXThemeColoursCustomisation::loadThemeColours(){
    if(SGXTimeStamp::now().isNationalDayPeriod()){
        SGXThemeColoursCustomisation::themeColour0 = SGXColourRGBA(0, 0, 0);
        SGXThemeColoursCustomisation::themeColour1 = SGXColourRGBA(60, 9, 14);
        SGXThemeColoursCustomisation::themeColour2 = SGXColourRGBA(119, 19, 27);
        SGXThemeColoursCustomisation::themeColour3 = SGXColourRGBA(179, 28, 41);
        SGXThemeColoursCustomisation::themeColour4 = SGXColourRGBA(238, 37, 54);
        SGXThemeColoursCustomisation::themeColour5 = SGXColourRGBA(242, 92, 104);
        SGXThemeColoursCustomisation::themeColour6 = SGXColourRGBA(247, 146, 155);
        SGXThemeColoursCustomisation::themeColour7 = SGXColourRGBA(251, 201, 205);
        SGXThemeColoursCustomisation::themeColour8 = SGXColourRGBA(255, 255, 255);
        return;
    }
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "themecolours.sg");
    if(SGXFileSystem::fileExists(path) == false){return;}
    {
        const SGXFile fileReader(path);
        SGXThemeColoursCustomisation::themeColour0 = fileReader.readColourRGBA();
        SGXThemeColoursCustomisation::themeColour1 = fileReader.readColourRGBA();
        SGXThemeColoursCustomisation::themeColour2 = fileReader.readColourRGBA();
        SGXThemeColoursCustomisation::themeColour3 = fileReader.readColourRGBA();
        SGXThemeColoursCustomisation::themeColour4 = fileReader.readColourRGBA();
        SGXThemeColoursCustomisation::themeColour5 = fileReader.readColourRGBA();
        SGXThemeColoursCustomisation::themeColour6 = fileReader.readColourRGBA();
        SGXThemeColoursCustomisation::themeColour7 = fileReader.readColourRGBA();
        SGXThemeColoursCustomisation::themeColour8 = fileReader.readColourRGBA();
    }
}

void SGXThemeColoursCustomisation::syncThemeColours(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "themecolours.sg");
    if(SGXFileSystem::fileExists(path) == true){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFile fileWriter(path);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour0);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour1);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour2);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour3);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour4);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour5);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour6);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour7);
        fileWriter.writeColourRGBA(SGXThemeColoursCustomisation::themeColour8);
    }
}
