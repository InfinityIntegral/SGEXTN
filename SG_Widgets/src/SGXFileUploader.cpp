#include <SGXFileUploader.h>
#include <SGXFileSystem.h>
#include <QQmlComponent>
#include <QObject>
#include <SGXString.h>
#include <QMetaObject>
#include <QUrl>
#include <SGXFile.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <QQmlApplicationEngine>

QQmlComponent* SGXFileUploader::fileUploadTemplate = nullptr;
QObject* SGXFileUploader::fileUploadInstance = nullptr;
void (*SGXFileUploader::fileAcceptor)(const SGXString&) = nullptr;

void SGXFileUploader::uploadFile(void (*attachedFunction)(const SGXString &)){
    if(SGXFileUploader::fileUploadTemplate == nullptr){SGXFileUploader::fileUploadTemplate = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/FileUpload.qml");}
    SGXFileUploader::fileUploadInstance = (*SGXFileUploader::fileUploadTemplate).create();
    QObject::connect(SGXFileUploader::fileUploadInstance, &QObject::objectNameChanged, &SGXFileUploader::checkUploadedFile);
    QMetaObject::invokeMethod(SGXFileUploader::fileUploadInstance, "open");
    SGXFileUploader::fileAcceptor = attachedFunction;
}

void SGXFileUploader::checkUploadedFile(){
    const SGXString urlPath = "";
    (*urlPath.data) = (*SGXFileUploader::fileUploadInstance).property("selectedFilePath").toString();
    if(urlPath != ""){
        (*urlPath.data) = QUrl(*urlPath.data).toLocalFile();
        const SGXString realPath = SGXFileSystem::getFreePath(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "SGEXTN/temp"), "temp", ".sg");
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
