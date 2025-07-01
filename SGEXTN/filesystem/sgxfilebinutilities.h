#ifndef SGXFILEBINUTILITIES_H
#define SGXFILEBINUTILITIES_H

#include <QObject>
#include <tuple>
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include <qtmetamacros.h>
#include <QHash>

class SGXFileBinUtilities : public QObject // non instantiable class containing functions to manage recycling bin
{
    Q_OBJECT
public:
    SGXFileBinUtilities() = delete;
    static void createEmptyBin(); // reset recycling bin
    static void loadBinData(); // load recycling bin metadata into app memory
    static int deletedFilesLifespan; // number of days before deleted files in recycling bin are permanently deleted
    static QHash<SGXIdentifier, std::tuple<QString, SGXTimeStamp>>* deletedFiles; // list of deleted files
    static QString pathToMetadataFile; // path to metadata file in recycling bin
    static int deleteFile(const QString& s); // send a file into recycling bin
    // -2: file system error caused operation to fail
    // -1: path is not in user data folder, only user data can be placed into the recycling bin, not app settings
    // 0: file to delete does not exist
    // 1: operation successful
    static int deleteFolder(const QString& s); // send a folder including direct and indirect children into recycling bin
    // -2: file system error caused operation to fail
    // -1: path is not in user data folder, only user data can be placed into the recycling bin, not app settings
    // 0: folder to delete does not exist
    // 1: operation successful
    static void syncMetadata(); // refresh metadata file to match data stored in app memory
    static int restoreFile(SGXIdentifier x); // restore a file from recycling bin
    // -3: metadata does not match file system records
    // -2: file system error caused operation to fail
    // 0: specified file does not exist
    // 1: operation successful
    static int permanentDeleteFile(SGXIdentifier x); // permanently delete a file from recycling bin
    // -3: metadata does not match file system records
    // -2: file system error caused operation to fail
    // 0: specified file does not exist
    // 1: operation successful
    static void permanentClearBin(); // clear recycling bin, equivalent to resetting it
    static void changeFileLifespan(int x); // change lifespan of deleted files
};

#endif // SGXFILEBINUTILITIES_H
