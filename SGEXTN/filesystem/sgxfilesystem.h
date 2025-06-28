#ifndef SGXFILESYSTEM_H
#define SGXFILESYSTEM_H

#include <QObject>
#include <qtmetamacros.h>

class SGXFileSystem : public QObject
{
    Q_OBJECT
public:
    SGXFileSystem() = delete;
    /*
create file
create folder
delete file
delete folder
move file
move folder
permanent delete file
permanent delete folder
duplicate file
duplicate folder
check file exists
check folder exists
get file size
get folder size
get file date created
get folder date created
get file date modified
get folder date modified
get file extension
get file name
get file name without extension
get nth parent folder path
get nth parent folder name
base16 encode
base16 decode
get list of files
get list of folders
get recursive list of files
get files with extension
get files with string in name
get file reader
get file writer
get root path
join path
get bin path
restore file from bin
restore folder from bin
delete file from bin
delete folder from bin
clear bin
set bin time
bring in external file
zip folder
unzip folder
*/
};

#endif // SGXFILESYSTEM_H
