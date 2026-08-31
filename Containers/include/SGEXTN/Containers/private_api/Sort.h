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
template <typename T, typename Comparator> class Sort {
private:
    explicit Sort(T* start, int length);
    T* firstBuffer_;
    T* secondBuffer_;
    int length_;
    int minimumBlockSize_;
    bool mainIsSecond_;
    Comparator comparatorInstance_;
    void insertSort(int left, int right);
    void mergeTwoBlocks(T* initialLocation, T* finalLocation, int firstBlockSize, int secondBlockSize);
    void mergeAllBlocks(T* initialLocation, T* finalLocation, int blockSize);
    void doSort();
public:
    Sort(const Sort& x) = delete;
    Sort& operator=(const Sort& x) = delete;
    Sort(Sort&& x) = delete;
    Sort& operator=(Sort&& x) = delete;
    ~Sort();
    static void sort(T* start, int length);
};
}

#include <SGEXTN/Containers/private_api/Sort_impl.h>
