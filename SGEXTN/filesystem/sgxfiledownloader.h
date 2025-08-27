#ifndef SGXFILEDOWNLOADER_H
#define SGXFILEDOWNLOADER_H

#include <QQmlComponent>

class SGXFileDownloader
{
public:
    SGXFileDownloader() = delete;
    static QQmlComponent* fileDownloadTemplate;
    static QObject* fileDownloadInstance;
    static void downloadFile(const QString& s);
    static void checkDownloadedFile();
    static QString sourcePath;
};

#endif // SGXFILEDOWNLOADER_H
