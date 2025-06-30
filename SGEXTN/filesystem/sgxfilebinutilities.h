#ifndef SGXFILEBINUTILITIES_H
#define SGXFILEBINUTILITIES_H

#include <QObject>
#include <tuple>
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include <qtmetamacros.h>
#include <qcontainerfwd.h>

class SGXFileBinUtilities : public QObject
{
    Q_OBJECT
public:
    SGXFileBinUtilities() = delete;
    static void createEmptyBin();
    static void loadBinData();
    static int deletedFilesLifespan;
    static QVector<std::tuple<SGXIdentifier, QString, SGXTimeStamp>>* deletedFiles;
    static QString pathToMetadataFile;
    static int deleteFile(const QString& s);
    static int deleteFolder(const QString& s);
    static void syncMetadata();
};
/*
restore file from bin
restore folder from bin
delete file from bin
delete folder from bin
clear bin
set bin time
*/

#endif // SGXFILEBINUTILITIES_H
