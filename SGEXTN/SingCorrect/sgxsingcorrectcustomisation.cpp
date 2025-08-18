#include "sgxsingcorrectcustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfilereader.h"
#include "../filesystem/sgxfilewriter.h"
#include <QHash>
#include <QString>
#include <QChar>
#include "sgxsingcorrectcore.h"

QHash<QString, QChar>* SGXSingCorrectCustomisation::database = nullptr;
bool SGXSingCorrectCustomisation::moduleEnabled = true;

void SGXSingCorrectCustomisation::loadFileData(){
    const QString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "correctionconfigs.sg");
    if(SGXSingCorrectCustomisation::database != nullptr){delete SGXSingCorrectCustomisation::database;}
    SGXSingCorrectCustomisation::database = new QHash<QString, QChar>();
    if(SGXFileSystem::fileExists(path) != 1){return;}
    {
        const SGXFileReader fileReader = SGXFileReader(path);
        SGXSingCorrectCustomisation::moduleEnabled = fileReader.readBool();
        SGXSingCorrectCore::correctionPrefix = fileReader.readString();
        const int n = fileReader.readInt();
        for(int i=0; i<n; i++){
            const QString k = fileReader.readString();
            const QChar v = fileReader.readString()[0];
            (*SGXSingCorrectCustomisation::database).insert(k, v);
        }
    }
}

void SGXSingCorrectCustomisation::syncFileData(){
    const QString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "correctionconfigs.sg");
    if(SGXFileSystem::fileExists(path) != 0){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFileWriter fileWriter = SGXFileWriter(path);
        fileWriter.writeBool(SGXSingCorrectCustomisation::moduleEnabled);
        fileWriter.writeString(SGXSingCorrectCore::correctionPrefix);
        if(SGXSingCorrectCustomisation::database != nullptr){
            fileWriter.writeInt(static_cast<int>((*SGXSingCorrectCustomisation::database).size()));
            for(QHash<QString, QChar>::iterator i = (*SGXSingCorrectCustomisation::database).begin(); i != (*SGXSingCorrectCustomisation::database).end(); i++){
                fileWriter.writeString(i.key());
                fileWriter.writeString(QString(i.value()));
            }
        }
        else{fileWriter.writeInt(0);}
    }
}
