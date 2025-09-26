#include "sgxfileuploader.h"
#include "sgxfilesystem.h"
#include <QQmlComponent>
#include <QObject>
#include "../primitives/sgxstring.h"
#include <QMetaObject>
#include <QUrl>
#include "sgxfile.h"
#include "../quickui/sgxquickinterface.h"
#include <QQmlApplicationEngine>

QQmlComponent* SGXFileUploader::fileUploadTemplate = nullptr;
QObject* SGXFileUploader::fileUploadInstance = nullptr;
void (*SGXFileUploader::fileAcceptor)(const SGXString&) = nullptr;

void SGXFileUploader::uploadFile(void (*attachedFunction)(const SGXString &)){
    if(SGXFileUploader::fileUploadTemplate == nullptr){SGXFileUploader::fileUploadTemplate = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/fileupload.qml");}
    SGXFileUploader::fileUploadInstance = (*SGXFileUploader::fileUploadTemplate).create();
    QObject::connect(SGXFileUploader::fileUploadInstance, &QObject::objectNameChanged, &SGXFileUploader::checkUploadedFile);
    QMetaObject::invokeMethod(SGXFileUploader::fileUploadInstance, "open");
    SGXFileUploader::fileAcceptor = attachedFunction;
}

void SGXFileUploader::checkUploadedFile(){
    SGXString urlPath = "";
    (*urlPath.data) = (*SGXFileUploader::fileUploadInstance).property("selectedFilePath").toString();
    if(urlPath != ""){
        (*urlPath.data) = QUrl(*urlPath.data).toLocalFile();
        const SGXString realPath = SGXFileSystem::getFreePath(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp"), "temp", ".sg");
        if(SGXFileSystem::folderExists(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp")) == false){SGXFileSystem::createFolder(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp"));}
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
