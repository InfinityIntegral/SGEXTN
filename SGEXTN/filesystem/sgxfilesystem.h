#ifndef SGXFILESYSTEM_H
#define SGXFILESYSTEM_H

#include <QObject>
#include <qtmetamacros.h>
#include <qcontainerfwd.h>

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
    /*
move file
move folder
duplicate file
duplicate folder
permanent delete file
permanent delete folder

get file size
get folder size
get file date created
get folder date created
get file date modified
get folder date modified

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
