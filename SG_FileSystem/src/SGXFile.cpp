#include <SGXFile.h>
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDataStream>
#include <SGXColourRGBA.h>
#include <SGXColourHSLA.h>
#include <SGXIdentifier.h>
#include <SGXTimeStamp.h>
#include <SGXVector2.h>
#include <SGXChar.h>
#include <SGXFileSystem.h>
#include <SGXString.h>
#include <QByteArray>
#include <SGLArray.h>
#include <cstring>
#include <QTextStream>

SGXFile::SGXFile(const SGXString &s){
    fileControl = nullptr;
    fileData = nullptr;
    if(SGXFileSystem::fileExists(s) == false){isValid = false;}
    else{
        fileControl = new QFile((*s.data));
        isValid = (*fileControl).open(QIODevice::ReadWrite);
        if(isValid == true){
            fileData = new QDataStream(fileControl);
            (*fileData).setByteOrder(QDataStream::LittleEndian);
            (*fileData).setVersion(QDataStream::Qt_6_9);
            (*fileData).setFloatingPointPrecision(QDataStream::SinglePrecision);
        }
    }
}

SGXFile::~SGXFile(){
    if(fileControl != nullptr){(*fileControl).close();}
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

SGXChar SGXFile::readSGEXTNChar() const {
    unsigned short x = static_cast<unsigned short>(0);
    (*(*this).fileData) >> x;
    return SGXChar(x);
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

SGXString SGXFile::readString() const {
    QString x = "";
    (*(*this).fileData) >> x;
    SGXString output = "";
    (*output.data) = x;
    return output;
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

void SGXFile::writeSGEXTNChar(SGXChar x) const {
    (*(*this).fileData) << x.data;
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

void SGXFile::writeString(const SGXString &x) const {
    (*(*this).fileData) << (*x.data);
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

SGLArray<char> SGXFile::readAllBytes() const {
    const QByteArray data = (*fileControl).readAll();
    SGLArray<char> output(static_cast<int>(data.length()));
    memcpy(output.pointerToData(0), data.constData(), data.length());
    return output;
}

SGLArray<char> SGXFile::readBytes(long long n) const {
    const QByteArray data = (*fileControl).read(n);
    SGLArray<char> output(static_cast<int>(data.length()));
    memcpy(output.pointerToData(0), data.constData(), data.length());
    return output;
}

void SGXFile::writeBytes(const SGLArray<char> &x) const {
    const QByteArray data = QByteArray::fromRawData(x.pointerToData(0), x.length());
    (*fileControl).write(data);
}

SGXString SGXFile::readAllText(const SGXString &filePath){
    QFile file(*filePath.data);
    (void)file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    SGXString contents = "";
    (*contents.data) = stream.readAll();
    file.close();
    return contents;
}

void SGXFile::writeAllText(const SGXString &filePath, const SGXString &contents){
    QFile file(*filePath.data);
    (void)file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&file);
    stream << (*contents.data);
    file.close();
}
