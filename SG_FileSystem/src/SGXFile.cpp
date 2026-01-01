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
#include <private_api_Containers/SGLCrash.h>

SGXFile::SGXFile(const SGXString &s, OpenStatus openMode){
    fileControl = nullptr;
    fileData = nullptr;
    if(SGXFileSystem::fileExists(s) == false){openStatus = SGXFile::NotOpen;}
    else{
        fileControl = new QFile((*s.data));
        bool isValid = false;
        if(openMode == SGXFile::FullAccess){isValid = (*fileControl).open(QIODevice::ReadWrite);}
        else if(openMode == SGXFile::ReadOnly){isValid = (*fileControl).open(QIODevice::ReadOnly);}
        else if(openMode == SGXFile::WriteOnly){isValid = (*fileControl).open(QIODevice::WriteOnly);}
        if(isValid == true){
            fileData = new QDataStream(fileControl);
            (*fileData).setByteOrder(QDataStream::LittleEndian);
            (*fileData).setVersion(QDataStream::Qt_6_9);
            (*fileData).setFloatingPointPrecision(QDataStream::SinglePrecision);
            openStatus = openMode;
        }
        else{openStatus = SGXFile::NotOpen;}
    }
}

SGXFile::~SGXFile(){
    if(fileControl != nullptr){(*fileControl).close();}
    delete fileData;
    delete fileControl;
}

bool SGXFile::canRead() const {
    if(openStatus == SGXFile::FullAccess || openStatus == SGXFile::ReadOnly){return true;}
    return false;
}

bool SGXFile::canWrite() const {
    if(openStatus == SGXFile::FullAccess || openStatus == SGXFile::WriteOnly){return true;}
    return false;
}

bool SGXFile::readBool() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readBool crashed because the file is not open in a read capable mode");}
    bool x = false;
    (*(*this).fileData) >> x;
    return x;
}

char SGXFile::readChar() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readChar crashed because the file is not open in a read capable mode");}
    char x = '\0';
    (*(*this).fileData) >> x;
    return x;
}

SGXChar SGXFile::readSGEXTNChar() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readSGEXTNChar crashed because the file is not open in a read capable mode");}
    unsigned short x = static_cast<unsigned short>(0);
    (*(*this).fileData) >> x;
    return SGXChar(x);
}

int SGXFile::readInt() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readInt crashed because the file is not open in a read capable mode");}
    int x = 0;
    (*(*this).fileData) >> x;
    return x;
}

unsigned int SGXFile::readUnsignedInt() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readUnsignedInt crashed because the file is not open in a read capable mode");}
    unsigned int x = 0u;
    (*(*this).fileData) >> x;
    return x;
}

long long SGXFile::readLongLong() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readLongLong crashed because the file is not open in a read capable mode");}
    long long x = 0ll;
    (*(*this).fileData) >> x;
    return x;
}

unsigned long long SGXFile::readUnsignedLongLong() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readUnsignedLongLong crashed because the file is not open in a read capable mode");}
    unsigned long long x = 0ull;
    (*(*this).fileData) >> x;
    return x;
}

float SGXFile::readFloat() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readFloat crashed because the file is not open in a read capable mode");}
    float x = 0.0f;
    (*(*this).fileData) >> x;
    return x;
}

double SGXFile::readDouble() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readDouble crashed because the file is not open in a read capable mode");}
    double x = 0.0;
    (*(*this).fileData) >> x;
    return x;
}

SGXString SGXFile::readString() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readString crashed because the file is not open in a read capable mode");}
    QString x = "";
    (*(*this).fileData) >> x;
    SGXString output = "";
    (*output.data) = x;
    return output;
}

SGXColourRGBA SGXFile::readColourRGBA() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readColourRGBA crashed because the file is not open in a read capable mode");}
    return SGXColourRGBA(readUnsignedInt());
}

SGXColourHSLA SGXFile::readColourHSLA() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readColourHSLA crashed because the file is not open in a read capable mode");}
    return SGXColourHSLA(readFloat(), readFloat(), readFloat(), readFloat());
}

SGXTimeStamp SGXFile::readTimeStamp() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readTimeStamp crashed because the file is not open in a read capable mode");}
    return SGXTimeStamp(readLongLong());
}

SGXIdentifier SGXFile::readIdentifier() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readIdentifier crashed because the file is not open in a read capable mode");}
    return SGXIdentifier(readUnsignedInt(), readUnsignedInt(), readUnsignedInt(), readUnsignedInt(), false, nullptr);
}

SGXVector2 SGXFile::readVector2() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readVector2 crashed because the file is not open in a read capable mode");}
    return SGXVector2(readFloat(), readFloat());
}

void SGXFile::writeBool(bool x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeBool crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x;
}

void SGXFile::writeChar(char x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeChar crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x;
}

void SGXFile::writeSGEXTNChar(SGXChar x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeSGEXTNChar crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x.data;
}

void SGXFile::writeInt(int x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeInt crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x;
}

void SGXFile::writeUnsignedInt(unsigned int x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeUnsignedInt crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x;
}

void SGXFile::writeLongLong(long long x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeLongLong crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x;
}

void SGXFile::writeUnsignedLongLong(unsigned long long x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeUnsignedLongLong crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x;
}

void SGXFile::writeFloat(float x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeFloat crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x;
}

void SGXFile::writeDouble(double x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeDouble crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << x;
}

void SGXFile::writeString(const SGXString &x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeString crashed because the file is not open in a write capable mode");}
    (*(*this).fileData) << (*x.data);
}

void SGXFile::writeColourRGBA(SGXColourRGBA x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeColourRGBA crashed because the file is not open in a write capable mode");}
    writeUnsignedInt(x.x);
}

void SGXFile::writeColourHSLA(SGXColourHSLA x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeColourHSLA crashed because the file is not open in a write capable mode");}
    writeFloat(x.h);
    writeFloat(x.s);
    writeFloat(x.l);
    writeFloat(x.a);
}

void SGXFile::writeTimeStamp(SGXTimeStamp x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeTimeStamp crashed because the file is not open in a write capable mode");}
    writeLongLong(x.t);
}

void SGXFile::writeIdentifier(SGXIdentifier x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeIdentifier crashed because the file is not open in a write capable mode");}
    writeUnsignedInt(x.a);
    writeUnsignedInt(x.b);
    writeUnsignedInt(x.c);
    writeUnsignedInt(x.d);
}

void SGXFile::writeVector2(SGXVector2 x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeVector2 crashed because the file is not open in a write capable mode");}
    writeFloat(x.x);
    writeFloat(x.y);
}

long long SGXFile::getPointerLocation() const {
    if(openStatus == SGXFile::NotOpen){SGLCrash::crash("SGXFile::getPointerLocation crashed as the file is not open");}
    return (*fileControl).pos();
}

void SGXFile::setPointerLocation(long long x) const {
    if(x < 0){SGLCrash::crash("SGXFile::setPointerLocation crashed because the target location is negative");}
    if(openStatus == SGXFile::NotOpen){SGLCrash::crash("SGXFile::setPointerLocation crashed as the file is not open");}
    if(x <= (*fileControl).size()){(*fileControl).seek(x);}
    else{
        const long long d = x - (*fileControl).size();
        (*fileControl).seek((*fileControl).size());
        (*fileControl).write(QByteArray(d, '\0'));
    }
}

SGLArray<char> SGXFile::readAllBytes() const {
    if(canRead() == false){SGLCrash::crash("SGXFile::readAllBytes crashed because the file is not open in a read capable mode");}
    const QByteArray data = (*fileControl).readAll();
    SGLArray<char> output(static_cast<int>(data.length()));
    memcpy(output.pointerToData(0), data.constData(), data.length());
    return output;
}

SGLArray<char> SGXFile::readBytes(long long n) const {
    if(n < 0){SGLCrash::crash("SGXFile::readBytes crashed because the number of bytes to read is negative");}
    if(canRead() == false){SGLCrash::crash("SGXFile::readBytes crashed because the file is not open in a read capable mode");}
    const QByteArray data = (*fileControl).read(n);
    SGLArray<char> output(static_cast<int>(data.length()));
    memcpy(output.pointerToData(0), data.constData(), data.length());
    return output;
}

void SGXFile::writeBytes(const SGLArray<char> &x) const {
    if(canWrite() == false){SGLCrash::crash("SGXFile::writeBytes crashed because the file is not open in a write capable mode");}
    const QByteArray data = QByteArray::fromRawData(x.pointerToData(0), x.length());
    (*fileControl).write(data);
}

SGXString SGXFile::readAllText(const SGXString &filePath){
    QFile file(*filePath.data);
    const bool isValid = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(isValid == false){return "";}
    QTextStream stream(&file);
    SGXString contents = "";
    (*contents.data) = stream.readAll();
    file.close();
    return contents;
}

void SGXFile::writeAllText(const SGXString &filePath, const SGXString &contents){
    QFile file(*filePath.data);
    const bool isValid = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(isValid == false){return;}
    QTextStream stream(&file);
    stream << (*contents.data);
    file.close();
}
