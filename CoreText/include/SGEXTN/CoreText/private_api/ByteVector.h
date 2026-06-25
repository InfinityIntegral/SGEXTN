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
