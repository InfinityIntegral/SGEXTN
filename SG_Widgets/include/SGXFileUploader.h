#ifndef SGXFILEUPLOADER_H
#define SGXFILEUPLOADER_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class QObject;
class QQmlComponent;
class SGXString;
class SG_WIDGETS_DLL SGXFileUploader
{
public:
    SGXFileUploader() = delete;
    static QQmlComponent* fileUploadTemplate;
    static QObject* fileUploadInstance;
    static void uploadFile(void (*attachedFunction)(const SGXString&));
    static void checkUploadedFile();
    static void (*fileAcceptor)(const SGXString&);
};

#endif // SGXFILEUPLOADER_H
