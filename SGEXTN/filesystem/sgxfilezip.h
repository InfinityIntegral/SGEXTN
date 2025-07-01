#ifndef SGXFILEZIP_H
#define SGXFILEZIP_H

#include <QObject>
#include <qtmetamacros.h>
#include <qcontainerfwd.h>
#include <tuple>

class SGXFileZip : public QObject // non instantiable class containing functions to make and read SingZip files
{
    Q_OBJECT
public:
    SGXFileZip() = delete;
    static int makeZip(const QString& path, const QString& zipLocation); // create SingZip file using contents in folder found at path and place the SingZip file at zipLocation
    // -1: path or zipLocation is invalid
    // 0: no folder exists at path or a file already exists at zipLocation
    // 1: operation successful
    static int makeZip(const QVector<QString>& list, const QString& zipLocation); // create SingZip file using files in list and place the SingZip file at zipLocation
    // -1: a path in list or zipLocation is invalid
    // 0: no file exists at a path in list or a file already exists at zipLocation
    // 1: operation successful
    static int unpackZip(const QString& zipLocation, const QString& path); // unpack SingZip file found at zipLocation to create a folder at path
    // -1: path or zipLocation is invalid
    // 0: no file exists at zipLocation or a folder already exists at path
    // 1: operation successful
    static int unpackSingleFileFromZip(const QString& fileName, const QString& zipLocation, const QString& path); // extract the file with relative path fileName inside the SingZip file found at zipLocation and place the extracted file at path
    // -1: path or zipLocation is invalid
    // 0: no file exists at zipLocation, no file with relative path fileName is in the SingZip file, or a file already exists at path
    // 1: operation successful
    static QVector<std::tuple<QString, long long>> getContentsListFromZip(const QString& zipLocation); // get a list of contents in a SingZip file
};

#endif // SGXFILEZIP_H
