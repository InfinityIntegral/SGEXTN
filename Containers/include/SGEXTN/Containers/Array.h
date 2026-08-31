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

namespace SGEXTN::Containers {
template <typename T> class ArrayVectorMove;

template <typename T> class ArrayStackStorage {
public:
    static constexpr int maxElements = 60 / sizeof(T);
    static constexpr unsigned int stackFlag = 0x80000000u;
    unsigned int length;
    alignas(T) unsigned char data[SGEXTN::Containers::ArrayStackStorage<T>::maxElements * sizeof(T) + static_cast<int>(SGEXTN::Containers::ArrayStackStorage<T>::maxElements == 0)];
};

template <typename T> class ArrayHeapStorage {
public:
    unsigned int length;
    T* data;
};

template <typename T> class Array {
private:
    friend class ArrayVectorMove<T>;
    union{
        ArrayStackStorage<T> stack_;
        ArrayHeapStorage<T> heap_;
    };
    [[nodiscard]] bool isUsingHeap() const;
    [[nodiscard]] T* getStackSlot(int i);
    [[nodiscard]] const T* getStackSlot(int i) const;
public:
    explicit Array();
    explicit Array(int count, const T& defaultValue);
    template <int N> explicit Array(const T(&xs)[N]);
    Array(const Array& x);
    Array& operator=(const Array& x);
    Array(Array&& x) noexcept;
    Array& operator=(Array&& x) noexcept;
    ~Array();
    void fill(const T& defaultValue);
    [[nodiscard]] int length() const;
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    template <typename Comparator> void sort(int start, int length);
    [[nodiscard]] T* getRawPointer();
    [[nodiscard]] const T* getRawPointer() const;
};
}

#include <SGEXTN/Containers/private_api/Array_impl.h>
