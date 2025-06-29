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

void SGXFileWriter::writeBool(bool x) const {
    (*(*this).fileData) << x;
}

void SGXFileWriter::writeChar(char x) const {
    (*(*this).fileData) << x;
}

void SGXFileWriter::writeInt(int x) const {
    (*(*this).fileData) << x;
}

void SGXFileWriter::writeUnsignedInt(unsigned int x) const {
    (*(*this).fileData) << x;
}

void SGXFileWriter::writeLongLong(long long x) const {
    (*(*this).fileData) << x;
}

void SGXFileWriter::writeUnsignedLongLong(unsigned long long x) const {
    (*(*this).fileData) << x;
}

void SGXFileWriter::writeFloat(float x) const {
    (*(*this).fileData) << x;
}

void SGXFileWriter::writeDouble(double x) const {
    (*(*this).fileData) << x;
}

void SGXFileWriter::writeString(const QString &x) const {
    const QByteArray byteSequence = x.toUtf8();
    (*(*this).fileData) << static_cast<int>(byteSequence.length());
    (*(*this).fileData).writeRawData(byteSequence.constData(), static_cast<int>(byteSequence.length()));
}
