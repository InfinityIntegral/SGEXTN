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
    [[nodiscard]] SGXColourRGBA readColourRGBA() const;
    [[nodiscard]] SGXColourHSLA readColourHSLA() const;
    [[nodiscard]] SGXTimeStamp readTimeStamp() const;
    [[nodiscard]] SGXIdentifier readIdentifier() const;
    [[nodiscard]] SGXVector2 readVector2() const;
    [[nodiscard]] long long getPointerLocation() const;
    void setPointerLocation(long long x) const;
    [[nodiscard]] bool allDataRead() const;
};

#endif // SGXFILEREADER_H
