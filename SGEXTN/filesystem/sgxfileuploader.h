#ifndef SGXFILEUPLOADER_H
#define SGXFILEUPLOADER_H

class QObject;
class QQmlComponent;
class SGXString;
class SGXFileUploader
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
