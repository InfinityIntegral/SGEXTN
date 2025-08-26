#ifndef SGXFILEUPLOADER_H
#define SGXFILEUPLOADER_H

#include <QObject>
#include <QQmlComponent>
#include <qtmetamacros.h>

class SGXFileUploader : public QObject
{
    Q_OBJECT
public:
    SGXFileUploader() = delete;
    static QQmlComponent* fileUploadTemplate;
    static QObject* fileUploadInstance;
    static void uploadFile(void (*attachedFunction)(const QString&));
    static void checkUploadedFile();
    static void (*fileAcceptor)(const QString&);
};

#endif // SGXFILEUPLOADER_H
