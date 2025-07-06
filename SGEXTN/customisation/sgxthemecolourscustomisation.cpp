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
        SGUCentralManagement::themeColour1 = SGXColourRGBA(59, 5, 9);
        SGUCentralManagement::themeColour2 = SGXColourRGBA(118, 9, 18);
        SGUCentralManagement::themeColour3 = SGXColourRGBA(177, 14, 28);
        SGUCentralManagement::themeColour4 = SGXColourRGBA(237, 18, 37);
        SGUCentralManagement::themeColour5 = SGXColourRGBA(241, 78, 91);
        SGUCentralManagement::themeColour6 = SGXColourRGBA(246, 137, 146);
        SGUCentralManagement::themeColour7 = SGXColourRGBA(250, 196, 200);
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
