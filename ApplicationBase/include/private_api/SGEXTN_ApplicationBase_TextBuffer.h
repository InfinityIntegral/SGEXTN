#pragma once
#include <SGEXTN_Containers_Vector.h>

namespace SGEXTN {
namespace ApplicationBase {
class BUILDLAH_DLL_SGEXTN_ApplicationBase TextBuffer {
public:
    TextBuffer(char c);
    TextBuffer(const char* s);
    TextBuffer(const TextBuffer& data, int start, int length);
    TextBuffer(const TextBuffer& x);
    TextBuffer& operator=(const TextBuffer& x);
    TextBuffer(TextBuffer&& x) noexcept;
    TextBuffer& operator=(TextBuffer&& x) noexcept;
    ~TextBuffer();
    bool isHeapAlloc;
    union {
        struct{unsigned char stackAllocData[24];}; // last byte is the length
        SGEXTN::Containers::Vector<unsigned char> heapAllocData;
    }
    [[nodiscard]] unsigned char& byteAt(int i);
    [[nodiscard]] const unsigned char& byteAt(int i) const;
    [[nodiscard]] int length() const;
    void pushBack(char c);
    void pushBack(const char* s);
    void pushBack(const TextBuffer& data, int start, int length);
    void popBack(int count);
};
}
}