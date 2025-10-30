#ifndef SGRDATABUFFER_H
#define SGRDATABUFFER_H

#include <private_api_RI/SG_Build_RI.h>

class QRhi;
class QRhiBuffer;
class SG_RI_DLL SGRDataBuffer
{
public:
    QRhi* rhi;
    QRhiBuffer* data;
    SGRDataBuffer(const SGRDataBuffer&) = delete;
    SGRDataBuffer& operator=(const SGRDataBuffer&) = delete;
    SGRDataBuffer(SGRDataBuffer&& x) = delete;
    SGRDataBuffer& operator=(SGRDataBuffer&&) = delete;
    ~SGRDataBuffer();
    [[nodiscard]] int length() const;
    void doubleBuffer() const;
protected:
    SGRDataBuffer() = default;
};

#endif // SGRDATABUFFER_H
