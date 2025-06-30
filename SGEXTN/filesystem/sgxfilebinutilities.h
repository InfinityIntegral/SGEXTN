#ifndef SGXFILEBINUTILITIES_H
#define SGXFILEBINUTILITIES_H

#include <QObject>
#include <tuple>
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include <qtmetamacros.h>
#include <QHash>

class SGXFileBinUtilities : public QObject
{
    Q_OBJECT
public:
    SGXFileBinUtilities() = delete;
    static void createEmptyBin();
    static void loadBinData();
    static int deletedFilesLifespan;
    static QHash<SGXIdentifier, std::tuple<QString, SGXTimeStamp>>* deletedFiles;
    static QString pathToMetadataFile;
    static int deleteFile(const QString& s);
    static int deleteFolder(const QString& s);
    static void syncMetadata();
    static int restoreFile(SGXIdentifier x);
    static int permanentDeleteFile(SGXIdentifier x);
    // refactor to use QHash for list of deleted files
};
/*
clear bin
set bin time
*/

#endif // SGXFILEBINUTILITIES_H
