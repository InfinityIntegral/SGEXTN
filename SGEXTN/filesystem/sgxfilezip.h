#ifndef SGXFILEZIP_H
#define SGXFILEZIP_H

#include <qcontainerfwd.h>
#include <tuple>

class SGXFileZip
{
public:
    SGXFileZip() = delete;
    static int makeZip(const QString& path, const QString& zipLocation);
    static int makeZip(const QVector<QString>& list, const QString& zipLocation);
    static int unpackZip(const QString& zipLocation, const QString& path);
    static int unpackSingleFileFromZip(const QString& fileName, const QString& zipLocation, const QString& path);
    static QVector<std::tuple<QString, long long>> getContentsListFromZip(const QString& zipLocation);
};

#endif // SGXFILEZIP_H
