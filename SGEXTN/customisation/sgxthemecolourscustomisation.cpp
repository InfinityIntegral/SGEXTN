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
        SGUCentralManagement::themeColour1 = SGXColourRGBA(135, 21, 31);
        SGUCentralManagement::themeColour2 = SGXColourRGBA(185, 29, 42);
        SGUCentralManagement::themeColour3 = SGXColourRGBA(222, 35, 50);
        SGUCentralManagement::themeColour4 = SGXColourRGBA(253, 39, 57);
        SGUCentralManagement::themeColour5 = SGXColourRGBA(254, 139, 143);
        SGUCentralManagement::themeColour6 = SGXColourRGBA(254, 187, 189);
        SGUCentralManagement::themeColour7 = SGXColourRGBA(255, 224, 225);
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
