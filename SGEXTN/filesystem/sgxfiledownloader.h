#ifndef SGXFILEDOWNLOADER_H
#define SGXFILEDOWNLOADER_H

#include <QObject>
#include <QQmlComponent>
#include <qtmetamacros.h>

class SGXFileDownloader : public QObject // non instantiable class containing functions to allow user to download files outside the application folder
{
    Q_OBJECT
public:
    SGXFileDownloader() = delete;
    static QQmlComponent* fileDownloadTemplate; // QML template for file downloader
    static QObject* fileDownloadInstance; // instance of file downloader, deleted after each use
    static void downloadFile(const QString& s); // function to request a file download using the file found at path s
    static void checkDownloadedFile(); // callback function to write data into download location
    static QString sourcePath; // contain path to download source
};

#endif // SGXFILEDOWNLOADER_H
