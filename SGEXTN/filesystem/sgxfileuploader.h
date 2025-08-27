#ifndef SGXFILEUPLOADER_H
#define SGXFILEUPLOADER_H

#include <QQmlComponent>

class SGXFileUploader
{
public:
    SGXFileUploader() = delete;
    static QQmlComponent* fileUploadTemplate;
    static QObject* fileUploadInstance;
    static void uploadFile(void (*attachedFunction)(const QString&));
    static void checkUploadedFile();
    static void (*fileAcceptor)(const QString&);
};

#endif // SGXFILEUPLOADER_H
