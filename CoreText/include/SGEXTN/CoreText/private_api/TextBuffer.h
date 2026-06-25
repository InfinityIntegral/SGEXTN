/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#pragma once
#include <SGEXTN/CoreText/private_api/ByteVector.h>

namespace SGEXTN {
namespace CoreText {
class BuildLah_SGEXTN_CoreText TextBuffer {
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
