#include "sgxvesiclespropertiescustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfile.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../primitives/sgxstring.h"

void SGXVesiclesPropertiesCustomisation::loadVesicleProperties(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "vesicleproperties.sg");
    if(SGXFileSystem::fileExists(path) == false){return;}
    {
        const SGXFile fileReader(path);
        SGUCentralManagement::cuteVesiclesMembraneThickness = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMaximumCenterDistance = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMaximumVelocity = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMaximumAcceleration = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMaximumRadiusChange = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMinimumRadius = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMaximumRadius = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMaximumRadiusOffset = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesCenterTransparency = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesEdgeTransparency = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesMembraneTransparency = fileReader.readFloat();
        SGUCentralManagement::cuteVesiclesFrameRate = fileReader.readFloat();
    }
}

void SGXVesiclesPropertiesCustomisation::syncVesicleProperties(){
    const SGXString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "vesicleproperties.sg");
    if(SGXFileSystem::fileExists(path) == true){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFile fileWriter(path);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMembraneThickness);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumCenterDistance);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumVelocity);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumAcceleration);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusChange);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMinimumRadius);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumRadius);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusOffset);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesCenterTransparency);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesEdgeTransparency);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesMembraneTransparency);
        fileWriter.writeFloat(SGUCentralManagement::cuteVesiclesFrameRate);
    }
}
