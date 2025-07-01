#ifndef SGXFILEWRITER_H
#define SGXFILEWRITER_H

#include <QObject>
#include <QFile>
#include <qtmetamacros.h>
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxvector2.h"

class SGXFileWriter : public QObject // object to write into a file
{
    Q_OBJECT
public:
    SGXFileWriter(const QString& s); // create a file writer to the path s
    // SGXFileWriter is only compatible with SGXFileReader
    SGXFileWriter(const SGXFileWriter&) = delete;
    SGXFileWriter(const SGXFileWriter&&) = delete;
    SGXFileWriter& operator=(const SGXFileWriter&) = delete;
    SGXFileWriter& operator=(const SGXFileWriter&&) = delete;
    ~SGXFileWriter() override;
    QFile* fileControl; // internal file object
    QDataStream* fileData; // internal stream object
    void writeBool(bool x) const; // write a bool
    void writeChar(char x) const; // write a signed char
    void writeInt(int x) const; // write a signed int
    void writeUnsignedInt(unsigned int x) const; // write a unsigned int
    void writeLongLong(long long x) const; // write a signed long long
    void writeUnsignedLongLong(unsigned long long x) const; // write a unsigned long long
    void writeFloat(float x) const; // write a float
    void writeDouble(double x) const; // write a double
    void writeString(const QString& x) const; // write a string
    void writeColourRGBA(SGXColourRGBA x) const; // write a RGBA colour
    void writeColourHSLA(SGXColourHSLA x) const; // write a HSLA colour
    void writeTimeStamp(SGXTimeStamp x) const; // write a timestamp
    void writeIdentifier(SGXIdentifier x) const; // write a identifier
    void writeVector2(SGXVector2 x) const; // write a 2D vector
    [[nodiscard]] long long getPointerLocation() const; // get current pointer location
    void setPointerLocation(long long x) const; // set current pointer location
};

#endif // SGXFILEWRITER_H
