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
#include <SGEXTN/Containers/private_api/RingBuffer.h>

namespace SGEXTN::Containers {
template <typename T> class ArrayVectorMove;

template <typename T> class Vector {
private:
    friend class SGEXTN::Containers::ArrayVectorMove<T>;
    SGEXTN::Containers::RingBuffer<T> ringBuffer_;
public:
    Vector();
    explicit Vector(int count, const T& defaultValue);
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] int length() const;
    void fill(const T& defaultValue);
    void reserve(int newMemoryLength);
    void pushBack(const T& x);
    void popBack();
    void clear();
};
}

#include <SGEXTN/Containers/private_api/Vector_impl.h>
