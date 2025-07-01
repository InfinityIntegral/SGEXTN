#include "sgxfilewriter.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDataStream>
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxvector2.h"

SGXFileWriter::SGXFileWriter(const QString &s){
    fileControl = new QFile(s);
    (*fileControl).open(QIODevice::ReadWrite);
    fileData = new QDataStream(fileControl);
    (*fileData).setByteOrder(QDataStream::LittleEndian);
    (*fileData).setVersion(QDataStream::Qt_6_9);
    (*fileData).setFloatingPointPrecision(QDataStream::SinglePrecision);
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

void SGXFileWriter::writeColourRGBA(SGXColourRGBA x) const {
    writeUnsignedInt(x.x);
}

void SGXFileWriter::writeColourHSLA(SGXColourHSLA x) const {
    writeFloat(x.h);
    writeFloat(x.s);
    writeFloat(x.l);
    writeFloat(x.a);
}

void SGXFileWriter::writeTimeStamp(SGXTimeStamp x) const {
    writeLongLong(x.t);
}

void SGXFileWriter::writeIdentifier(SGXIdentifier x) const {
    writeUnsignedInt(x.a);
    writeUnsignedInt(x.b);
    writeUnsignedInt(x.c);
    writeUnsignedInt(x.d);
}

void SGXFileWriter::writeVector2(SGXVector2 x) const {
    writeFloat(x.x);
    writeFloat(x.y);
}

long long SGXFileWriter::getPointerLocation() const {
    return (*fileControl).pos();
}

void SGXFileWriter::setPointerLocation(long long x) const {
    (*fileControl).seek(x);
}

QByteArray SGXFileWriter::readAllBytes() const {
    return (*fileControl).readAll();
}

QByteArray SGXFileWriter::readBytes(long long n) const {
    return (*fileControl).read(n);
}

void SGXFileWriter::writeBytes(const QByteArray &x) const {
    (*fileControl).write(x);
}
