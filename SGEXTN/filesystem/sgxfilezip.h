#ifndef SGXFILEZIP_H
#define SGXFILEZIP_H

#include <qcontainerfwd.h>
#include <tuple>
#include "../primitives/sgxstring.h"

class SGXFileZip
{
public:
    SGXFileZip() = delete;
    static int makeZip(const SGXString& path, const SGXString& zipLocation);
    static int makeZip(const QVector<SGXString>& list, const SGXString& zipLocation);
    static int unpackZip(const SGXString& zipLocation, const SGXString& path);
    static int unpackSingleFileFromZip(const SGXString& fileName, const SGXString& zipLocation, const SGXString& path);
    static QVector<std::tuple<SGXString, long long>> getContentsListFromZip(const SGXString& zipLocation);
};

#endif // SGXFILEZIP_H
