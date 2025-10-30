#ifndef SGXFILEDOWNLOADER_H
#define SGXFILEDOWNLOADER_H

#include <SGXString.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class QObject;
class QQmlComponent;
class SG_WIDGETS_DLL SGXFileDownloader
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
