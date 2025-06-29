#ifndef SGXFILESYSTEM_H
#define SGXFILESYSTEM_H

#include <QObject>
#include <qtmetamacros.h>
#include <qcontainerfwd.h>
#include "../primitives/sgxtimestamp.h"

class SGXFileSystem : public QObject
{
    Q_OBJECT
public:
    SGXFileSystem() = delete;
    static QString rootFilePath;
    static QString userDataFilePath;
    static QString binFilePath;
    static QString configFilePath;
    static QString joinFilePaths(const QString& a, const QString& b);
    static QString encodeBase16(const QString& s);
    static QString decodeBase16(const QString& str);
    static bool pathIsValid(const QString& s);
    static bool pathIsSubfolder(const QString& childPath, const QString& parentPath);
    static int fileExists(const QString& s);
    static int folderExists(const QString& s);
    static QString getFreePath(const QString& prefix, const QString& unencodedName, const QString& postfix);
    static int createFile(const QString& s);
    static int createFolder(const QString& s);
    static QString getParentPath(const QString& s);
    static QString getParentName(const QString& s);
    static QVector<QString> getFilesList(const QString& s);
    static QVector<QString> getFilesListRecursive(const QString& s);
    static QVector<QString> getFoldersList(const QString& s);
    static int moveFile(const QString& startPath, const QString& endPath);
    static int moveFolder(const QString& startPath, const QString& endPath);
    static int duplicateFile(const QString& startPath, const QString& endPath);
    static int duplicateFolder(const QString& startPath, const QString& endPath);
    static int permanentDeleteFile(const QString& s);
    static int permanentDeleteFolder(const QString& s);
    static long long getFileSize(const QString& s);
    static long long getFolderSize(const QString& s);
    static SGXTimeStamp getFileCreationTime(const QString& s);
    static SGXTimeStamp getFolderCreationTime(const QString& s);
    static SGXTimeStamp getFileLastEditTime(const QString& s);
    static SGXTimeStamp getFolderLastEditTime(const QString& s);
    /*
get file extension
get file name
get file name without extension

get files with extension
get files with extension recursive
get folders with string in name
get files with string in name
get files with string in name recursive

get file reader
get file writer

delete file
delete folder
restore file from bin
restore folder from bin
delete file from bin
delete folder from bin
clear bin
set bin time

bring in external file

zip folder
unzip folder
*/
};

#endif // SGXFILESYSTEM_H
