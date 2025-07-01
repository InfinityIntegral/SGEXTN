#ifndef SGXFILEUPLOADER_H
#define SGXFILEUPLOADER_H

#include <QObject>
#include <QQmlComponent>
#include <qtmetamacros.h>

class SGXFileUploader : public QObject // non instantiable class containing functions to allow user to upload files outside the application folder
{
    Q_OBJECT
public:
    SGXFileUploader() = delete;
    static QQmlComponent* fileUploadTemplate; // QML template for file uploader
    static QObject* fileUploadInstance; // instance of file uploader, deleted after each use
    static void uploadFile(void (*attachedFunction)(const QString&)); // function to request a file upload
    static void checkUploadedFile(); // callback function to process uploaded file based on function chosen by user
    static void (*fileAcceptor)(const QString&); // user defined function to be run when a file is selected, it also must handle when the file is not selected and am empty string is passed
};

#endif // SGXFILEUPLOADER_H
