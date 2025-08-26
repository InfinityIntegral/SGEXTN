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
    static QString binFilePath;
    static void createEmptyBin();
    static void loadBinData();
    static QHash<SGXIdentifier, std::tuple<QString, SGXTimeStamp>>* deletedFiles;
    static QString pathToMetadataFile;
    static int deleteFile(const QString& s);
    static int deleteFolder(const QString& s);
    static void syncMetadata();
    static int restoreFile(SGXIdentifier x);
    static int permanentDeleteFile(SGXIdentifier x);
    static void permanentClearBin();
    static int getLifespan();
    static void setLifespan(int x);
protected:
    static int lifespan;
};

#endif // SGXFILEBINUTILITIES_H
