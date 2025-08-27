#include "sgxfileuploader.h"
#include "sgxfilesystem.h"
#include <QQmlComponent>
#include <QObject>
#include <QString>
#include <QMetaObject>
#include <QUrl>
#include "sgxfile.h"
#include "../quickui/sgxquickinterface.h"

QQmlComponent* SGXFileUploader::fileUploadTemplate = nullptr;
QObject* SGXFileUploader::fileUploadInstance = nullptr;
void (*SGXFileUploader::fileAcceptor)(const QString&) = nullptr;

void SGXFileUploader::uploadFile(void (*attachedFunction)(const QString &)){
    if(SGXFileUploader::fileUploadTemplate == nullptr){SGXFileUploader::fileUploadTemplate = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/fileupload.qml");}
    SGXFileUploader::fileUploadInstance = qobject_cast<QObject*>((*SGXFileUploader::fileUploadTemplate).create());
    connect(SGXFileUploader::fileUploadInstance, &QObject::objectNameChanged, &SGXFileUploader::checkUploadedFile);
    QMetaObject::invokeMethod(SGXFileUploader::fileUploadInstance, "open");
    SGXFileUploader::fileAcceptor = attachedFunction;
}

void SGXFileUploader::checkUploadedFile(){
    QString urlPath = (*SGXFileUploader::fileUploadInstance).property("selectedFilePath").toString();
    if(urlPath != ""){
        urlPath = QUrl(urlPath).toLocalFile();
        const QString realPath = SGXFileSystem::getFreePath(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp"), "temp", ".sg");
        if(SGXFileSystem::folderExists(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp")) != 1){SGXFileSystem::createFolder(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp"));}
        SGXFileSystem::createFile(realPath);
        {
            const SGXFile fileReader(urlPath);
            const SGXFile fileWriter(realPath);
            fileWriter.writeBytes(fileReader.readAllBytes());
        }
        SGXFileUploader::fileAcceptor(realPath);
        SGXFileSystem::permanentDeleteFile(realPath);
    }
    else{SGXFileUploader::fileAcceptor("");}
    (*SGXFileUploader::fileUploadInstance).deleteLater();
    SGXFileUploader::fileUploadInstance = nullptr;
    SGXFileUploader::fileAcceptor = nullptr;
}
