#ifndef SGXFILEREADER_H
#define SGXFILEREADER_H

#include <QObject>
#include <QFile>
#include <qtmetamacros.h>
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxidentifier.h"
#include "../primitives/sgxtimestamp.h"
#include "../primitives/sgxvector2.h"

class SGXFileReader : public QObject
{
    Q_OBJECT
public:
    SGXFileReader(const QString& s); // create a file reader to the file s
    // SGXFileReader is only compatible with SGXFileWriter
    SGXFileReader(const SGXFileReader&) = delete;
    SGXFileReader(const SGXFileReader &&) = delete;
    SGXFileReader& operator=(const SGXFileReader&) = delete;
    SGXFileReader& operator=(const SGXFileReader&&) = delete;
    ~SGXFileReader() override;
    QFile* fileControl; // internal file object
    QDataStream* fileData; // internal stream object
    [[nodiscard]] bool readBool() const; // read a bool
    [[nodiscard]] char readChar() const; // read a signed char
    [[nodiscard]] int readInt() const; // read a signed int
    [[nodiscard]] unsigned int readUnsignedInt() const; // read a unsigned int
    [[nodiscard]] long long readLongLong() const; // read a signed long long
    [[nodiscard]] unsigned long long readUnsignedLongLong() const; // read a unsigned long long
    [[nodiscard]] float readFloat() const; // read a float
    [[nodiscard]] double readDouble() const; // read a double
    [[nodiscard]] QString readString() const; // read a string
    [[nodiscard]] SGXColourRGBA readColourRGBA() const; // read a RGBA colour
    [[nodiscard]] SGXColourHSLA readColourHSLA() const; // read a HSLA colour
    [[nodiscard]] SGXTimeStamp readTimeStamp() const; // read a timestamp
    [[nodiscard]] SGXIdentifier readIdentifier() const; // read a identifier
    [[nodiscard]] SGXVector2 readVector2() const; // read a 2D vector
    [[nodiscard]] long long getPointerLocation() const; // get current pointer location
    void setPointerLocation(long long x) const; // set current pointer location
    [[nodiscard]] bool allDataRead() const; // check if all data has been read
};

#endif // SGXFILEREADER_H
