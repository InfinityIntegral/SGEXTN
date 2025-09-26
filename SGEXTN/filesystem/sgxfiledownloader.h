#ifndef SGXFILEDOWNLOADER_H
#define SGXFILEDOWNLOADER_H

#include "../primitives/sgxstring.h"

class QObject;
class QQmlComponent;
class SGXFileDownloader
{
public:
    SGXFileDownloader() = delete;
    static QQmlComponent* fileDownloadTemplate;
    static QObject* fileDownloadInstance;
    static void downloadFile(const SGXString& s);
    static void checkDownloadedFile();
    static SGXString sourcePath;
};

#endif // SGXFILEDOWNLOADER_H
