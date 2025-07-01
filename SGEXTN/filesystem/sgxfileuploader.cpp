#include "sgxfileuploader.h"
#include "../quickui/sgxquickuiinterface.h"
#include "sgxfilesystem.h"
#include <QFile>
#include <QQmlComponent>
#include <QObject>
#include <QString>
#include <QQuickItem>
#include <QMetaObject>
#include <QUrl>

QQmlComponent* SGXFileUploader::fileUploadTemplate = nullptr;
QObject* SGXFileUploader::fileUploadInstance = nullptr;
void (*SGXFileUploader::fileAcceptor)(const QString&) = nullptr;

void SGXFileUploader::uploadFile(void (*attachedFunction)(const QString &)){
    if(SGXFileUploader::fileUploadTemplate == nullptr){SGXFileUploader::fileUploadTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/fileupload.qml");}
    SGXFileUploader::fileUploadInstance = qobject_cast<QObject*>((*SGXFileUploader::fileUploadTemplate).create());
    connect(SGXFileUploader::fileUploadInstance, &QQuickItem::objectNameChanged, &SGXFileUploader::checkUploadedFile);
    QMetaObject::invokeMethod(SGXFileUploader::fileUploadInstance, "open");
    SGXFileUploader::fileAcceptor = attachedFunction;
}

void SGXFileUploader::checkUploadedFile(){
    QString urlPath = (*SGXFileUploader::fileUploadInstance).property("selectedFilePath").toString();
    QString realPath = SGXFileSystem::getFreePath(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp"), "temp", ".sg");
    if(SGXFileSystem::folderExists(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp")) != 1){SGXFileSystem::createFolder(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "temp"));}
#ifdef Q_OS_ANDROID
    // use the shared container library
#else
    if(urlPath != ""){
        urlPath = QUrl(urlPath).toLocalFile();
        QFile(urlPath).copy(realPath);
    }
#endif
    if(urlPath == ""){realPath = "";}
    SGXFileUploader::fileAcceptor(realPath);
    if(SGXFileSystem::fileExists(realPath) == 1){SGXFileSystem::permanentDeleteFile(realPath);}
    (*SGXFileUploader::fileUploadInstance).deleteLater();
}
