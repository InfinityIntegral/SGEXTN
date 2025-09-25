#include "sgxsingcorrectcustomisation.h"
#include "../filesystem/sgxfilesystem.h"
#include "../filesystem/sgxfile.h"
#include <QHash>
#include <QString>
#include <QChar>
#include "sgxsingcorrectcore.h"

QHash<QString, QChar>* SGXSingCorrectCustomisation::database = nullptr;
bool SGXSingCorrectCustomisation::moduleEnabled = true;

void SGXSingCorrectCustomisation::loadFileData(){
    const QString path = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "correctionconfigs.sg");
    delete SGXSingCorrectCustomisation::database;
    SGXSingCorrectCustomisation::database = new QHash<QString, QChar>();
    if(SGXFileSystem::fileExists(path) == false){return;}
    {
        const SGXFile fileReader = SGXFile(path);
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
    if(SGXFileSystem::fileExists(path) == true){SGXFileSystem::permanentDeleteFile(path);}
    SGXFileSystem::createFile(path);
    {
        const SGXFile fileWriter = SGXFile(path);
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
