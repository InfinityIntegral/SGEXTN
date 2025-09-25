#include "sgxfile.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDataStream>
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxvector2.h"
#include <QChar>
#include <string>
#include <qnamespace.h>
#include "sgxfilesystem.h"

SGXFile::SGXFile(const QString &s){
    if(SGXFileSystem::fileExists(s) == false){isValid = false;}
    else{
        fileControl = new QFile(s);
        isValid = (*fileControl).open(QIODevice::ReadWrite);
        if(isValid == true){
            fileData = new QDataStream(fileControl);
            (*fileData).setByteOrder(QDataStream::LittleEndian);
            (*fileData).setVersion(QDataStream::Qt_6_9);
            (*fileData).setFloatingPointPrecision(QDataStream::SinglePrecision);
        }
    }
}

SGXFile::SGXFile(const QString &s, bool /*unused*/){
    isValid = false;
    fileControl = new QFile(s);
    (*fileControl).open(QIODevice::ReadWrite);
    fileData = new QDataStream(fileControl);
    (*fileData).setByteOrder(QDataStream::LittleEndian);
    (*fileData).setVersion(QDataStream::Qt_6_9);
    (*fileData).setFloatingPointPrecision(QDataStream::SinglePrecision);
}

SGXFile::~SGXFile(){
    (*fileControl).close();
    delete fileData;
    delete fileControl;
}

bool SGXFile::readBool() const {
    bool x = false;
    (*(*this).fileData) >> x;
    return x;
}

char SGXFile::readChar() const {
    char x = '\0';
    (*(*this).fileData) >> x;
    return x;
}

QChar SGXFile::readQChar() const {
    QChar x = '\0';
    (*(*this).fileData) >> x;
    return x;
}

int SGXFile::readInt() const {
    int x = 0;
    (*(*this).fileData) >> x;
    return x;
}

unsigned int SGXFile::readUnsignedInt() const {
    unsigned int x = 0u;
    (*(*this).fileData) >> x;
    return x;
}

long long SGXFile::readLongLong() const {
    long long x = 0ll;
    (*(*this).fileData) >> x;
    return x;
}

unsigned long long SGXFile::readUnsignedLongLong() const {
    unsigned long long x = 0ull;
    (*(*this).fileData) >> x;
    return x;
}

float SGXFile::readFloat() const {
    float x = 0.0f;
    (*(*this).fileData) >> x;
    return x;
}

double SGXFile::readDouble() const {
    double x = 0.0;
    (*(*this).fileData) >> x;
    return x;
}

std::string SGXFile::readCppString() const {
    int x = 0;
    (*(*this).fileData) >> x;
    QByteArray byteSequence(x, Qt::Uninitialized);
    (*(*this).fileData).readRawData(byteSequence.data(), x);
    return std::string(byteSequence.constData(), byteSequence.size());
}

QString SGXFile::readString() const {
    int x = 0;
    (*(*this).fileData) >> x;
    QByteArray byteSequence(x, Qt::Uninitialized);
    (*(*this).fileData).readRawData(byteSequence.data(), x);
    return QString::fromUtf8(byteSequence);
}

SGXColourRGBA SGXFile::readColourRGBA() const {
    return SGXColourRGBA(readUnsignedInt());
}

SGXColourHSLA SGXFile::readColourHSLA() const {
    return SGXColourHSLA(readFloat(), readFloat(), readFloat(), readFloat());
}

SGXTimeStamp SGXFile::readTimeStamp() const {
    return SGXTimeStamp(readLongLong());
}

SGXIdentifier SGXFile::readIdentifier() const {
    return SGXIdentifier(readUnsignedInt(), readUnsignedInt(), readUnsignedInt(), readUnsignedInt(), false, nullptr);
}

SGXVector2 SGXFile::readVector2() const {
    return SGXVector2(readFloat(), readFloat());
}

void SGXFile::writeBool(bool x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeChar(char x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeQChar(QChar x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeInt(int x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeUnsignedInt(unsigned int x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeLongLong(long long x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeUnsignedLongLong(unsigned long long x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeFloat(float x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeDouble(double x) const {
    (*(*this).fileData) << x;
}

void SGXFile::writeCppString(const std::string &x) const {
    const QByteArray byteSequence = QByteArray(x.c_str(), static_cast<long long>(x.size()));
    (*(*this).fileData) << static_cast<int>(byteSequence.length());
    (*(*this).fileData).writeRawData(byteSequence.constData(), static_cast<int>(byteSequence.length()));
}

void SGXFile::writeString(const QString &x) const {
    const QByteArray byteSequence = x.toUtf8();
    (*(*this).fileData) << static_cast<int>(byteSequence.length());
    (*(*this).fileData).writeRawData(byteSequence.constData(), static_cast<int>(byteSequence.length()));
}

void SGXFile::writeColourRGBA(SGXColourRGBA x) const {
    writeUnsignedInt(x.x);
}

void SGXFile::writeColourHSLA(SGXColourHSLA x) const {
    writeFloat(x.h);
    writeFloat(x.s);
    writeFloat(x.l);
    writeFloat(x.a);
}

void SGXFile::writeTimeStamp(SGXTimeStamp x) const {
    writeLongLong(x.t);
}

void SGXFile::writeIdentifier(SGXIdentifier x) const {
    writeUnsignedInt(x.a);
    writeUnsignedInt(x.b);
    writeUnsignedInt(x.c);
    writeUnsignedInt(x.d);
}

void SGXFile::writeVector2(SGXVector2 x) const {
    writeFloat(x.x);
    writeFloat(x.y);
}

long long SGXFile::getPointerLocation() const {
    return (*fileControl).pos();
}

void SGXFile::setPointerLocation(long long x) const {
    if(x <= (*fileControl).size()){(*fileControl).seek(x);}
    else{
        const long long d = x - (*fileControl).size();
        (*fileControl).seek((*fileControl).size());
        (*fileControl).write(QByteArray(d, '\0'));
    }
}

QByteArray SGXFile::readAllBytes() const {
    return (*fileControl).readAll();
}

QByteArray SGXFile::readBytes(long long n) const {
    return (*fileControl).read(n);
}

void SGXFile::writeBytes(const QByteArray &x) const {
    (*fileControl).write(x);
}
