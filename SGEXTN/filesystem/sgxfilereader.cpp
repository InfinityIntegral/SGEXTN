#include "sgxfilereader.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDataStream>
#include <qnamespace.h>

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
