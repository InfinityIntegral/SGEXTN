#include "sgxfilewriter.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDataStream>

SGXFileWriter::SGXFileWriter(const QString &s){
    fileControl = new QFile(s);
    (*fileControl).open(QIODevice::WriteOnly);
    fileData = new QDataStream(fileControl);
}

SGXFileWriter::~SGXFileWriter(){
    (*fileControl).close();
    delete fileData;
    delete fileControl;
}
