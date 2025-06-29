#ifndef SGXFILEREADER_H
#define SGXFILEREADER_H

#include <QObject>
#include <QFile>
#include <qtmetamacros.h>

class SGXFileReader : public QObject
{
    Q_OBJECT
public:
    SGXFileReader(const QString& s);
    SGXFileReader(const SGXFileReader&) = delete;
    SGXFileReader(const SGXFileReader &&) = delete;
    SGXFileReader& operator=(const SGXFileReader&) = delete;
    SGXFileReader& operator=(const SGXFileReader&&) = delete;
    ~SGXFileReader() override;
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
/*
SGXColourRGBA
SGXColourHSLA
SGXIdentifier
SGXTimeStamp
SGXVector2

get location
set location
*/
};

#endif // SGXFILEREADER_H
