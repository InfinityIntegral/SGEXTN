#ifndef SGXFILE_H
#define SGXFILE_H

#include <QFile>
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxvector2.h"

class SGXFile
{
public:
    SGXFile(const QString& s);
    SGXFile(const SGXFile&) = delete;
    SGXFile(const SGXFile&&) = delete;
    SGXFile& operator=(const SGXFile&) = delete;
    SGXFile& operator=(const SGXFile&&) = delete;
    ~SGXFile();
    QFile* fileControl;
    QDataStream* fileData;
    [[nodiscard]] bool readBool() const;
    [[nodiscard]] char readChar() const;
    [[nodiscard]] int readInt() const;
    [[nodiscard]] unsigned int readUnsignedInt() const;
    [[nodiscard]] long long readLongLong() const;
    [[nodiscard]] unsigned long long readUnsignedLongLong() const;
    [[nodiscard]] float readFloat() const;
    [[nodiscard]] double readDouble() const;
    [[nodiscard]] QString readString() const;
    [[nodiscard]] SGXColourRGBA readColourRGBA() const;
    [[nodiscard]] SGXColourHSLA readColourHSLA() const;
    [[nodiscard]] SGXTimeStamp readTimeStamp() const;
    [[nodiscard]] SGXIdentifier readIdentifier() const;
    [[nodiscard]] SGXVector2 readVector2() const;
    void writeBool(bool x) const;
    void writeChar(char x) const;
    void writeInt(int x) const;
    void writeUnsignedInt(unsigned int x) const;
    void writeLongLong(long long x) const;
    void writeUnsignedLongLong(unsigned long long x) const;
    void writeFloat(float x) const;
    void writeDouble(double x) const;
    void writeString(const QString& x) const;
    void writeColourRGBA(SGXColourRGBA x) const;
    void writeColourHSLA(SGXColourHSLA x) const;
    void writeTimeStamp(SGXTimeStamp x) const;
    void writeIdentifier(SGXIdentifier x) const;
    void writeVector2(SGXVector2 x) const;
    [[nodiscard]] long long getPointerLocation() const;
    void setPointerLocation(long long x) const;
    [[nodiscard]] QByteArray readBytes(long long n) const;
    [[nodiscard]] QByteArray readAllBytes() const;
    void writeBytes(const QByteArray& x) const;
};

#endif // SGXFILE_H
