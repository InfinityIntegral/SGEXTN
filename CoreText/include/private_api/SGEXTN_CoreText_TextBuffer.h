#pragma once
#include <private_api/SGEXTN_CoreText_ByteVector.h>

namespace SGEXTN {
namespace CoreText {
class BUILDLAH_DLL_SGEXTN_CoreText TextBuffer {
public:
    TextBuffer();
    TextBuffer(const TextBuffer& x);
    TextBuffer& operator=(const TextBuffer& x);
    TextBuffer(TextBuffer&& x) noexcept;
    TextBuffer& operator=(TextBuffer&& x) noexcept;
    ~TextBuffer();
    bool private_isHeapAlloc;
    union {
        unsigned char private_stackAllocData[16];
        SGEXTN::CoreText::ByteVector private_heapAllocData;
    };
    [[nodiscard]] unsigned char& private_lengthByte();
    [[nodiscard]] const unsigned char& private_lengthByte() const;
    void private_moveToHeap();
    [[nodiscard]] unsigned char& byteAt(int i);
    [[nodiscard]] const unsigned char& byteAt(int i) const;
    [[nodiscard]] int length() const;
    void pushBack(unsigned char c);
    void pushBack(const char* s);
    void pushBack(const TextBuffer& data, int start, int length);
    [[nodiscard]] bool operator==(const TextBuffer& x) const;
    [[nodiscard]] bool operator!=(const TextBuffer& x) const;
    [[nodiscard]] bool operator<(const TextBuffer& x) const;
    [[nodiscard]] bool operator>(const TextBuffer& x) const;
    [[nodiscard]] bool operator<=(const TextBuffer& x) const;
    [[nodiscard]] bool operator>=(const TextBuffer& x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] TextBuffer substring(int start, int length) const;
    [[nodiscard]] TextBuffer substringLeft(int length) const;
    [[nodiscard]] TextBuffer substringRight(int length) const;
};
}
}