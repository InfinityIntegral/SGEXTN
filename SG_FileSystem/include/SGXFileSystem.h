#ifndef SGXFILESYSTEM_H
#define SGXFILESYSTEM_H

#include <SGXTimeStamp.h>
#include <SGXString.h>
#include <SGLArray.h>

#include <private_api_FileSystem/SG_Build_FileSystem.h>

class SG_FILESYSTEM_DLL SGXFileSystem
{
public:
    SGXFileSystem() = delete;
    static SGXString rootFilePath;
    static SGXString userDataFilePath;
    static SGXString configFilePath;
    static SGXString joinFilePaths(const SGXString& a, const SGXString& b);
    static SGXString encodeToFileName(const SGXString& s);
    static SGXString decodeFromFileName(const SGXString& s);
    static bool pathIsSubfolder(const SGXString& childPath, const SGXString& parentPath);
    static bool fileExists(const SGXString& s);
    static bool folderExists(const SGXString& s);
    static SGXString getFreePath(const SGXString& prefix, const SGXString& unencodedName, const SGXString& postfix);
    static int createFile(const SGXString& s);
    static int createFolder(const SGXString& s);
    static SGXString getParentPath(const SGXString& s);
    static SGXString getParentName(const SGXString& s);
    static SGLArray<SGXString> getFilesList(const SGXString& s);
    static SGLArray<SGXString> getFilesListRecursive(const SGXString& s);
    static SGLArray<SGXString> getFoldersList(const SGXString& s);
    static int moveFile(const SGXString& startPath, const SGXString& endPath);
    static int moveFolder(const SGXString& startPath, const SGXString& endPath);
    static int duplicateFile(const SGXString& startPath, const SGXString& endPath);
    static int duplicateFolder(const SGXString& startPath, const SGXString& endPath);
    static int permanentDeleteFile(const SGXString& s);
    static int permanentDeleteFolder(const SGXString& s);
    static long long getFileSize(const SGXString& s);
    static long long getFolderSize(const SGXString& s);
    static SGXTimeStamp getFileCreationTime(const SGXString& s);
    static SGXTimeStamp getFolderCreationTime(const SGXString& s);
    static SGXTimeStamp getFileLastEditTime(const SGXString& s);
    static SGXTimeStamp getFolderLastEditTime(const SGXString& s);
    static SGXString getFolderName(const SGXString& s);
    static SGXString getFileName(const SGXString& s);
    static SGXString getFileExtension(const SGXString& s);
    static SGXString getFileNameNoExtension(const SGXString& s);
    static SGLArray<SGXString> getFilesListWithExtension(const SGXString& s, const SGXString& ext);
    static SGLArray<SGXString> getFilesListWithExtensionRecursive(const SGXString& s, const SGXString& ext);
    static SGLArray<SGXString> getFilesListContainingName(const SGXString& s, const SGXString& name);
    static SGLArray<SGXString> getFilesListContainingNameRecursive(const SGXString& s, const SGXString& name);
    static bool numberAwareLesserThan(const SGXString& s1, const SGXString& s2);
    static bool numberAwareLesserThanBase16(const SGXString& s1, const SGXString& s2);
    static void initialiseAppFolder();
    static void openLink(const SGXString& link);
};

class SG_FILESYSTEM_DLL SGXNumberAwareFilePathLesserThan {
public:
    [[nodiscard]] bool operator()(const SGXString& a, const SGXString& b);
};

class SG_FILESYSTEM_DLL SGXNumberAwareFilePathMoreThan {
public:
    [[nodiscard]] bool operator()(const SGXString& a, const SGXString& b);
};

class SG_FILESYSTEM_DLL SGXNumberAwareFilePathLesserThanBase16 {
public:
    [[nodiscard]] bool operator()(const SGXString& a, const SGXString& b);
};

class SG_FILESYSTEM_DLL SGXNumberAwareFilePathMoreThanBase16 {
public:
    [[nodiscard]] bool operator()(const SGXString& a, const SGXString& b);
};

#endif // SGXFILESYSTEM_H
