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
#include <private_api/SGEXTN_Containers_RingBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Stack {
public:
    Stack();
    [[nodiscard]] T& top();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] int length() const;
    void push(const T& x);
    void pop();
    void clear();
    void reserve(int newMemoryLength);
    SGEXTN::Containers::RingBuffer<T> private_ringBuffer;
};
}
}

#include <private_api/SGEXTN_Containers_Stack_impl.h>
