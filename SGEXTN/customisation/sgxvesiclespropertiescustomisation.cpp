#include "sgxvesiclespropertiescustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfilewriter.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../filesystem/sgxfilereader.h"
#include "../primitives/sgxcolourrgba.h"
#include <QString>
#include "../primitives/sgxtimestamp.h"

void SGXVesiclesPropertiesCustomisation::loadVesicleProperties(){
    const QString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "vesicleproperties.sg");
    if(SGXFileSystem::fileExists(path) == 1){
        {
            const SGXFileReader fileReader(path);
            SGUCentralManagement::cuteVesiclesMembraneThickness = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMaximumCenterDistance = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMaximumVelocity = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMaximumAcceleration = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMaximumRadiusChange = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMinimumRadius = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMaximumRadius = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMaximumRadiusOffset = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMembraneColour = fileReader.readColourRGBA();
            SGUCentralManagement::cuteVesiclesContentsColour = fileReader.readColourRGBA();
            SGUCentralManagement::cuteVesiclesCenterTransparency = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesEdgeTransparency = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesMembraneTransparency = fileReader.readFloat();
            SGUCentralManagement::cuteVesiclesFrameRate = fileReader.readFloat();
        }
    }
    if(SGXTimeStamp::now().isNationalDayPeriod()){
        SGUCentralManagement::cuteVesiclesMembraneColour = SGXColourRGBA(238, 37, 54);
        SGUCentralManagement::cuteVesiclesContentsColour = SGXColourRGBA(255, 255, 255);
    }
}

void SGXVesiclesPropertiesCustomisation::syncVesicleProperties(){
    const QString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "vesicleproperties.sg");
    if(SGXFileSystem::fileExists(path) != 0){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFileWriter fileWriter(path);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMembraneThickness);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumCenterDistance);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumVelocity);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumAcceleration);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusChange);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMinimumRadius);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumRadius);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusOffset);
        fileWriter.writeColourRGBA(SGUCentralManagement::cuteVesiclesMembraneColour);
        fileWriter.writeColourRGBA(SGUCentralManagement::cuteVesiclesContentsColour);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesCenterTransparency);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesEdgeTransparency);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMembraneTransparency);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesFrameRate);
    }
}
