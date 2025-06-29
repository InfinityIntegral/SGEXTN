#include "sgxfilereader.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDataStream>

SGXFileReader::SGXFileReader(const QString &s){
    fileControl = new QFile(s);
    (*fileControl).open(QIODevice::ReadOnly);
    fileData = new QDataStream(fileControl);
}

SGXFileReader::~SGXFileReader(){
    (*fileControl).close();
    delete fileData;
    delete fileControl;
}
