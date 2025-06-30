#ifndef SGXFILEBINUTILITIES_H
#define SGXFILEBINUTILITIES_H

#include <QObject>

class SGXFileBinUtilities : public QObject
{
    Q_OBJECT
public:
    SGXFileBinUtilities() = delete;
};
/*
initialise bin
delete file
delete folder
restore file from bin
restore folder from bin
delete file from bin
delete folder from bin
clear bin
set bin time
*/

#endif // SGXFILEBINUTILITIES_H
