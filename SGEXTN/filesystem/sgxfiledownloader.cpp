#include "sgxfiledownloader.h"
#include "sgxfilesystem.h"
#include <QQmlComponent>
#include <QObject>
#include "../primitives/sgxstring.h"
#include <QMetaObject>
#include <QUrl>
#include "sgxfile.h"
#include "../quickui/sgxquickinterface.h"
#include <QQmlApplicationEngine>

QQmlComponent* SGXFileDownloader::fileDownloadTemplate = nullptr;
QObject* SGXFileDownloader::fileDownloadInstance = nullptr;
SGXString SGXFileDownloader::sourcePath = "";

void SGXFileDownloader::downloadFile(const SGXString &s){
    if(SGXFileSystem::fileExists(s) == false){return;}
    if(SGXFileDownloader::fileDownloadTemplate == nullptr){SGXFileDownloader::fileDownloadTemplate = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/filedownload.qml");}
    SGXFileDownloader::fileDownloadInstance = (*SGXFileDownloader::fileDownloadTemplate).create();
    QObject::connect(SGXFileDownloader::fileDownloadInstance, &QObject::objectNameChanged, &SGXFileDownloader::checkDownloadedFile);
    QMetaObject::invokeMethod(SGXFileDownloader::fileDownloadInstance, "open");
    SGXFileDownloader::sourcePath = s;
}

void SGXFileDownloader::checkDownloadedFile(){
    const SGXString urlPath = "";
    (*urlPath.data) = (*SGXFileDownloader::fileDownloadInstance).property("selectedFilePath").toString();
    if(urlPath != ""){
        (*urlPath.data) = QUrl(*urlPath.data).toLocalFile();
        {
            const SGXFile fileReader(sourcePath);
            const SGXFile fileWriter(urlPath);
            fileWriter.writeBytes(fileReader.readAllBytes());
        }
    }
    (*SGXFileDownloader::fileDownloadInstance).deleteLater();
    SGXFileDownloader::fileDownloadInstance = nullptr;
    SGXFileDownloader::sourcePath = "";
}
