#ifndef SGXFILESYSTEM_H
#define SGXFILESYSTEM_H

#include <QObject>
#include <qtmetamacros.h>
#include <qcontainerfwd.h>
#include "../primitives/sgxtimestamp.h"

class SGXFileSystem : public QObject // non instantiable class containing functions to interact with the file system
{
    Q_OBJECT
public:
    SGXFileSystem() = delete;
    // the SGEXTN file system is quite restrictive to prevent you from hiding your application data, all application data, even if you want it to be secret, are easily accessible by the user, you are strongly discouraged to attempt to hide anything from the user
    static QString rootFilePath; // root of application folder, this path should not be used, you should only use its subfolders for data storage, the path is considered invalid
    static QString userDataFilePath; // root of user data folder
    static QString binFilePath; // root of recycling bin folder, you should only interact with the recycling bin from the SGXFileBinUtilities class, the whole folder is considered invalid
    static QString configFilePath; // root of configs folder, you can use this to store app settings
    static QString joinFilePaths(const QString& a, const QString& b); // joins the 2 parts, a and b, of a file path with a / in between
    static QString encodeBase16(const QString& s); // encode a string to base16 which can be safely used as file name
    static QString decodeBase16(const QString& str); // decode a string from base16
    static bool pathIsValid(const QString& s); // check if a file path is valid, access to invalid file paths is severely restricted to ensure the accessibility of application data to the user
    // do not attempt to use invalid paths in any way, SGEXTN functions will check for path validity and reject invalid paths
    // always use absolute paths, any relative path is considered invalid
    static bool pathIsSubfolder(const QString& childPath, const QString& parentPath); // checks if childPath refers to a subfolder of parentPath
    static int fileExists(const QString& s); // checks if a file exists
    // -1: path is invalid
    // 0: file does not exist
    // 1: file exists
    static int folderExists(const QString& s); // checks if a folder exists
    // -1: path is invalid
    // 0: file does not exist
    // 1: file exists
    static QString getFreePath(const QString& prefix, const QString& unencodedName, const QString& postfix); // gets next available file path for a file in the parent folder prefix, with name as unencodedName, and extension postfix, if the path is taken, numbers are added behind the name
    static int createFile(const QString& s); // create a file
    // -2: file system errors caused file creation to fail
    // -1: path is invalid
    // 0: file already exists
    // 1: creation successful
    static int createFolder(const QString& s); // create a folder
    // -2: file system errors caused folder creation to fail
    // -1: path is invalid
    // 0: folder already exists
    // 1: creation successful
    static QString getParentPath(const QString& s); // get path to parent folder
    static QString getParentName(const QString& s); // get name of parent folder
    static QVector<QString> getFilesList(const QString& s); // get list of files in folder that are direct children
    static QVector<QString> getFilesListRecursive(const QString& s); // get list of files in folder including indirect children
    static QVector<QString> getFoldersList(const QString& s); // get list of folders in folder that are direct children
    static int moveFile(const QString& startPath, const QString& endPath); // move file from startPath to endPath
    // -2: file system error caused operation to fail
    // -1: one or both of the paths is invalid
    // 0: start path does not have a file or destination path already has a file
    // 1: operation successful
    static int moveFolder(const QString& startPath, const QString& endPath); // move folder from startPath to endPath including all direct and indirect children
    // -2: file system error caused operation to fail
    // -1: one or both of the paths is invalid
    // 0: start path does not have a folder or destination path already has a folder
    // 1: operation successful
    static int duplicateFile(const QString& startPath, const QString& endPath); // copy paste a file from startPath to endPath without deleting the original file
    // -2: file system error caused operation to fail
    // -1: one or both of the paths is invalid
    // 0: start path does not have a file or destination path already has a file
    // 1: operation successful
    static int duplicateFolder(const QString& startPath, const QString& endPath); // copy paste a folder including direct and indirect children from startPath to endPath without deleting the original folder
    // -2: file system error caused operation to fail
    // -1: one or both of the paths is invalid
    // 0: start path does not have a folder or destination path already has a folder
    // 1: operation successful
    static int permanentDeleteFile(const QString& s); // permanently delete a file without going through recycling bin
    // -3: file is located in the user data folder, for data protection purposes, all user data deletion must go through the recycling bin
    // -2: file system error caused operation to fail
    // -1: path is invalid
    // 0: file does not exist
    // 1: operation successful
    static int permanentDeleteFolder(const QString& s); // permanently delete a folder including direct and indirect children without going through recycling bin
    // -3: folder is located in the user data folder, for data protection purposes, all user data deletion must go through the recycling bin
    // -2: file system error caused operation to fail
    // -1: path is invalid
    // 0: folder does not exist
    // 1: operation successful
    static long long getFileSize(const QString& s); // get size of file in bytes
    static long long getFolderSize(const QString& s); // get size of folder in bytes, this is the sum of sizes of its direct and indirect children
    static SGXTimeStamp getFileCreationTime(const QString& s); // get time the file was created
    static SGXTimeStamp getFolderCreationTime(const QString& s); // get time the folder was created
    // note that this would always return 0 (19650809 123000) if the system does not support checking file creation time, this is an issue on some Linux distributions
    static SGXTimeStamp getFileLastEditTime(const QString& s); // get time the file was last edited
    static SGXTimeStamp getFolderLastEditTime(const QString& s); // get time the folder was last edited, including its files being edited, files being added, or files being removed from it
    static QString getFolderName(const QString& s); // get name of folder
    static QString getFileName(const QString& s); // get name of file
    static QString getFileExtension(const QString& s); // get file extension
    static QString getFileNameNoExtension(const QString& s); // get name of file with extension removed
    static QVector<QString> getFilesListWithExtension(const QString& s, const QString& ext); // get all direct children files in folder s with extension ext
    static QVector<QString> getFilesListWithExtensionRecursive(const QString& s, const QString& ext); // get all direct and indirect children files in folder s with extension ext
    static QVector<QString> getFilesListContainingName(const QString& s, const QString& name); // get all direct children files in folder s the name of which contains the string name
    static QVector<QString> getFilesListContainingNameRecursive(const QString& s, const QString& name); // get all direct and indirect children files in folder s the name of which contains the string name
};

#endif // SGXFILESYSTEM_H
