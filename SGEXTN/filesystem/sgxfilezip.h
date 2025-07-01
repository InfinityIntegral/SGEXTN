#ifndef SGXFILEZIP_H
#define SGXFILEZIP_H

#include <QObject>

class SGXFileZip : public QObject // non instantiable class containing functions to make and read SingZip files
{
    Q_OBJECT
public:
    SGXFileZip() = delete;
    // make zip from folder
    // make zip from list of files
    // unpack zip into folder
    // extract specific file from zip
    // get table of contents of zip with file names and sizes
};

#endif // SGXFILEZIP_H
