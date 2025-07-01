#include "sgxfilereader.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDataStream>
#include <qnamespace.h>
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxvector2.h"

SGXFileReader::SGXFileReader(const QString &s){
    fileControl = new QFile(s);
    (*fileControl).open(QIODevice::ReadOnly);
    fileData = new QDataStream(fileControl);
    (*fileData).setByteOrder(QDataStream::LittleEndian);
    (*fileData).setVersion(QDataStream::Qt_6_9);
    (*fileData).setFloatingPointPrecision(QDataStream::SinglePrecision);
}

SGXFileReader::~SGXFileReader(){
    (*fileControl).close();
    delete fileData;
    delete fileControl;
}

bool SGXFileReader::readBool() const {
    bool x = false;
    (*(*this).fileData) >> x;
    return x;
}

char SGXFileReader::readChar() const {
    char x = '\0';
    (*(*this).fileData) >> x;
    return x;
}

int SGXFileReader::readInt() const {
    int x = 0;
    (*(*this).fileData) >> x;
    return x;
}

unsigned int SGXFileReader::readUnsignedInt() const {
    unsigned int x = 0u;
    (*(*this).fileData) >> x;
    return x;
}

long long SGXFileReader::readLongLong() const {
    long long x = 0ll;
    (*(*this).fileData) >> x;
    return x;
}

unsigned long long SGXFileReader::readUnsignedLongLong() const {
    unsigned long long x = 0ull;
    (*(*this).fileData) >> x;
    return x;
}

float SGXFileReader::readFloat() const {
    float x = 0.0f;
    (*(*this).fileData) >> x;
    return x;
}

double SGXFileReader::readDouble() const {
    double x = 0.0;
    (*(*this).fileData) >> x;
    return x;
}

QString SGXFileReader::readString() const {
    int x = 0;
    (*(*this).fileData) >> x;
    QByteArray byteSequence(x, Qt::Uninitialized);
    (*(*this).fileData).readRawData(byteSequence.data(), x);
    return QString::fromUtf8(byteSequence);
}

SGXColourRGBA SGXFileReader::readColourRGBA() const {
    return SGXColourRGBA(readUnsignedInt());
}

SGXColourHSLA SGXFileReader::readColourHSLA() const {
    return SGXColourHSLA(readFloat(), readFloat(), readFloat(), readFloat());
}

SGXTimeStamp SGXFileReader::readTimeStamp() const {
    return SGXTimeStamp(readLongLong());
}

SGXIdentifier SGXFileReader::readIdentifier() const {
    int errCode = 0;
    return SGXIdentifier(readUnsignedInt(), readUnsignedInt(), readUnsignedInt(), readUnsignedInt(), false, errCode);
}

SGXVector2 SGXFileReader::readVector2() const {
    return SGXVector2(readFloat(), readFloat());
}

long long SGXFileReader::getPointerLocation() const {
    return (*fileControl).pos();
}

void SGXFileReader::setPointerLocation(long long x) const {
    (*fileControl).seek(x);
}

bool SGXFileReader::allDataRead() const {
    return (*fileControl).atEnd();
}

QByteArray SGXFileReader::readAllBytes() const {
    return (*fileControl).readAll();
}

QByteArray SGXFileReader::readBytes(long long n) const {
    return (*fileControl).read(n);
}
