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
namespace Containers {
template <typename T> class RingBufferSlot {
public:
    union {
        unsigned char constructorRemover;
        T object;
    };
    RingBufferSlot();
    RingBufferSlot(const RingBufferSlot&) = delete;
    RingBufferSlot& operator=(const RingBufferSlot&) = delete;
    RingBufferSlot(RingBufferSlot&&) = delete;
    RingBufferSlot& operator=(RingBufferSlot&&) = delete;
    ~RingBufferSlot();
};

template <typename T> class RingBuffer {
public:
    RingBuffer();
    RingBuffer(int count, const T& defaultValue);
    RingBuffer(const RingBuffer& x);
    RingBuffer& operator=(const RingBuffer& x);
    RingBuffer(RingBuffer&& x) noexcept;
    RingBuffer& operator=(RingBuffer&& x) noexcept;
    ~RingBuffer();
    void fill(const T& defaultValue);
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] T& front();
    [[nodiscard]] const T& front() const;
    [[nodiscard]] T& back();
    [[nodiscard]] const T& back() const;
    [[nodiscard]] int length() const;
    void pushBack(const T& x);
    void popBack();
    void pushFront(const T& x);
    void popFront();
    void reserve(int newMemoryLength);
    void clear();
    RingBufferSlot<T>* private_data;
    int private_start;
    int private_length;
    int private_memoryLength;
    [[nodiscard]] int private_getMemoryIndex(int i) const;
};
}
}

#include <private_api/SGEXTN_Containers_RingBuffer_impl.h>
