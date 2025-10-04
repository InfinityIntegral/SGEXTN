#ifndef SGXFILEBINUTILITIES_H
#define SGXFILEBINUTILITIES_H

#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxstring.h"

template <typename K, typename V, typename EqualityCheck, typename HashFunction> class SGLUnorderedMap;
template <typename T> class SGLEqualsTo;
template <typename T> class SGLHash;
template <typename T1, typename T2> class SGLPair;
class SGXTimeStamp;
class SGXFileBinUtilities
{
public:
    SGXFileBinUtilities() = delete;
    static SGXString binFilePath;
    static void createEmptyBin();
    static void loadBinData();
    static SGLUnorderedMap<SGXIdentifier, SGLPair<SGXString, SGXTimeStamp>, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>* deletedFiles;
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
