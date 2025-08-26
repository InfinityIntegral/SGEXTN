#ifndef SGXFILEDOWNLOADER_H
#define SGXFILEDOWNLOADER_H

#include <QObject>
#include <QQmlComponent>
#include <qtmetamacros.h>

class SGXFileDownloader : public QObject
{
    Q_OBJECT
public:
    SGXFileDownloader() = delete;
    static QQmlComponent* fileDownloadTemplate;
    static QObject* fileDownloadInstance;
    static void downloadFile(const QString& s);
    static void checkDownloadedFile();
    static QString sourcePath;
};

#endif // SGXFILEDOWNLOADER_H
