#ifndef SGXFILE_H
#define SGXFILE_H

#include <SGXColourRGBA.h>
#include <SGXColourHSLA.h>
#include <SGXIdentifier.h>
#include <SGXTimeStamp.h>
#include <SGXVector2.h>
#include <SGXChar.h>
#include <SGXString.h>
#include <SGLArray.h>

#include <private_api_FileSystem/SG_Build_FileSystem.h>

class QFile;
class QDataStream;
class SG_FILESYSTEM_DLL SGXFile
{
public:
    enum OpenStatus {
        NotOpen,
        ReadOnly,
        WriteOnly,
        FullAccess
    };
    SGXFile(const SGXString& s, SGXFile::OpenStatus openMode);
    SGXFile(const SGXFile&) = delete;
    SGXFile(const SGXFile&&) = delete;
    SGXFile& operator=(const SGXFile&) = delete;
    SGXFile& operator=(const SGXFile&&) = delete;
    ~SGXFile();
    QFile* fileControl;
    QDataStream* fileData;
    SGXFile::OpenStatus openStatus;
    [[nodiscard]] bool readBool() const;
    [[nodiscard]] char readChar() const;
    [[nodiscard]] SGXChar readSGEXTNChar() const;
    [[nodiscard]] int readInt() const;
    [[nodiscard]] unsigned int readUnsignedInt() const;
    [[nodiscard]] long long readLongLong() const;
    [[nodiscard]] unsigned long long readUnsignedLongLong() const;
    [[nodiscard]] float readFloat() const;
    [[nodiscard]] double readDouble() const;
    [[nodiscard]] SGXString readString() const;
    [[nodiscard]] SGXColourRGBA readColourRGBA() const;
    [[nodiscard]] SGXColourHSLA readColourHSLA() const;
    [[nodiscard]] SGXTimeStamp readTimeStamp() const;
    [[nodiscard]] SGXIdentifier readIdentifier() const;
    [[nodiscard]] SGXVector2 readVector2() const;
    void writeBool(bool x) const;
    void writeChar(char x) const;
    void writeSGEXTNChar(SGXChar x) const;
    void writeInt(int x) const;
    void writeUnsignedInt(unsigned int x) const;
    void writeLongLong(long long x) const;
    void writeUnsignedLongLong(unsigned long long x) const;
    void writeFloat(float x) const;
    void writeDouble(double x) const;
    void writeString(const SGXString& x) const;
    void writeColourRGBA(SGXColourRGBA x) const;
    void writeColourHSLA(SGXColourHSLA x) const;
    void writeTimeStamp(SGXTimeStamp x) const;
    void writeIdentifier(SGXIdentifier x) const;
    void writeVector2(SGXVector2 x) const;
    [[nodiscard]] long long getPointerLocation() const;
    void setPointerLocation(long long x) const;
    [[nodiscard]] SGLArray<char> readBytes(long long n) const;
    [[nodiscard]] SGLArray<char> readAllBytes() const;
    void writeBytes(const SGLArray<char>& x) const;
    static SGXString readAllText(const SGXString& filePath);
    static void writeAllText(const SGXString& filePath, const SGXString& contents);
};

#endif // SGXFILE_H
