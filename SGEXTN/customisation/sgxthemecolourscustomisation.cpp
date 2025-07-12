#include "sgxthemecolourscustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfilewriter.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../filesystem/sgxfilereader.h"
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxcolourrgba.h"
#include <QString>

void SGXThemeColoursCustomisation::loadThemeColours(){
    if(SGXTimeStamp::now().isNationalDayPeriod()){
        SGUCentralManagement::themeColour0 = SGXColourRGBA(0, 0, 0);
        SGUCentralManagement::themeColour1 = SGXColourRGBA(60, 9, 14);
        SGUCentralManagement::themeColour2 = SGXColourRGBA(119, 19, 27);
        SGUCentralManagement::themeColour3 = SGXColourRGBA(179, 28, 41);
        SGUCentralManagement::themeColour4 = SGXColourRGBA(238, 37, 54);
        SGUCentralManagement::themeColour5 = SGXColourRGBA(242, 92, 104);
        SGUCentralManagement::themeColour6 = SGXColourRGBA(247, 146, 155);
        SGUCentralManagement::themeColour7 = SGXColourRGBA(251, 201, 205);
        SGUCentralManagement::themeColour8 = SGXColourRGBA(255, 255, 255);
        return;
    }
    const QString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "themecolours.sg");
    if(SGXFileSystem::fileExists(path) == 1){
        {
            const SGXFileReader fileReader(path);
            SGUCentralManagement::themeColour0 = fileReader.readColourRGBA();
            SGUCentralManagement::themeColour1 = fileReader.readColourRGBA();
            SGUCentralManagement::themeColour2 = fileReader.readColourRGBA();
            SGUCentralManagement::themeColour3 = fileReader.readColourRGBA();
            SGUCentralManagement::themeColour4 = fileReader.readColourRGBA();
            SGUCentralManagement::themeColour5 = fileReader.readColourRGBA();
            SGUCentralManagement::themeColour6 = fileReader.readColourRGBA();
            SGUCentralManagement::themeColour7 = fileReader.readColourRGBA();
            SGUCentralManagement::themeColour8 = fileReader.readColourRGBA();
        }
    }
}

void SGXThemeColoursCustomisation::syncThemeColours(){
    const QString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "themecolours.sg");
    if(SGXFileSystem::fileExists(path) != 0){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFileWriter fileWriter(path);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour0);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour1);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour2);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour3);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour4);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour5);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour6);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour7);
        fileWriter.writeColourRGBA(SGUCentralManagement::themeColour8);
    }
}
