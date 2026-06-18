#pragma once

namespace SGEXTN {
namespace CoreText {
class BuildLah_SGEXTN_CoreText ByteVector {
public:
    unsigned char* private_data;
    int private_length;
    int private_memoryLength;
    ByteVector();
    ByteVector(const ByteVector& x);
    ByteVector& operator=(const ByteVector& x);
    ByteVector(ByteVector&& x) noexcept;
    ByteVector& operator=(ByteVector&& x) noexcept;
    ~ByteVector();
    [[nodiscard]] unsigned char& at(int i);
    [[nodiscard]] const unsigned char& at(int i) const;
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    void pushBack(unsigned char c);
    void pushBack(const unsigned char* start, int length);
};
}
}
