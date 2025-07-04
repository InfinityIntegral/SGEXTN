#include "sgxfiledownloader.h"
#include "../quickui/sgxquickuiinterface.h"
#include "sgxfilesystem.h"
#include <QQmlComponent>
#include <QObject>
#include <QString>
#include <QMetaObject>
#include <QUrl>
#include "sgxfilereader.h"
#include "sgxfilewriter.h"

QQmlComponent* SGXFileDownloader::fileDownloadTemplate = nullptr;
QObject* SGXFileDownloader::fileDownloadInstance = nullptr;
QString SGXFileDownloader::sourcePath = "";

void SGXFileDownloader::downloadFile(const QString &s){
    if(SGXFileSystem::pathIsValid(s) == false || SGXFileSystem::fileExists(s) != 1){return;}
    if(SGXFileDownloader::fileDownloadTemplate == nullptr){SGXFileDownloader::fileDownloadTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/filedownload.qml");}
    SGXFileDownloader::fileDownloadInstance = qobject_cast<QObject*>((*SGXFileDownloader::fileDownloadTemplate).create());
    connect(SGXFileDownloader::fileDownloadInstance, &QObject::objectNameChanged, &SGXFileDownloader::checkDownloadedFile);
    QMetaObject::invokeMethod(SGXFileDownloader::fileDownloadInstance, "open");
    SGXFileDownloader::sourcePath = s;
}

void SGXFileDownloader::checkDownloadedFile(){
    QString urlPath = (*SGXFileDownloader::fileDownloadInstance).property("selectedFilePath").toString();
    if(urlPath != ""){
        urlPath = QUrl(urlPath).toLocalFile();
        {
            const SGXFileReader fileReader(sourcePath);
            const SGXFileWriter fileWriter(urlPath);
            fileWriter.writeBytes(fileReader.readAllBytes());
        }
    }
    (*SGXFileDownloader::fileDownloadInstance).deleteLater();
    SGXFileDownloader::fileDownloadInstance = nullptr;
    SGXFileDownloader::sourcePath = "";
}
