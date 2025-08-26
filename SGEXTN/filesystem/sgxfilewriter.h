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

class SGXFileWriter : public QObject
{
    Q_OBJECT
public:
    SGXFileWriter(const QString& s);
    SGXFileWriter(const SGXFileWriter&) = delete;
    SGXFileWriter(const SGXFileWriter&&) = delete;
    SGXFileWriter& operator=(const SGXFileWriter&) = delete;
    SGXFileWriter& operator=(const SGXFileWriter&&) = delete;
    ~SGXFileWriter() override;
    QFile* fileControl;
    QDataStream* fileData;
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

#endif // SGXFILEWRITER_H
