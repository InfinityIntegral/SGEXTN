#ifndef SGXFILEBINUTILITIES_H
#define SGXFILEBINUTILITIES_H

#include "../primitives/sgxidentifier.h"
#include <tuple>

template <typename T1, typename T2> class QHash;
class SGXTimeStamp;
class SGXFileBinUtilities
{
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
