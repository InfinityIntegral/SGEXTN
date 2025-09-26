#ifndef SGXFILEBINUTILITIES_H
#define SGXFILEBINUTILITIES_H

#include "../primitives/sgxidentifier.h"
#include <tuple>
#include "../primitives/sgxstring.h"

template <typename T1, typename T2> class QHash;
class SGXTimeStamp;
class SGXFileBinUtilities
{
public:
    SGXFileBinUtilities() = delete;
    static SGXString binFilePath;
    static void createEmptyBin();
    static void loadBinData();
    static QHash<SGXIdentifier, std::tuple<SGXString, SGXTimeStamp>>* deletedFiles;
    static SGXString pathToMetadataFile;
    static int deleteFile(const SGXString& s);
    static int deleteFolder(const SGXString& s);
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
