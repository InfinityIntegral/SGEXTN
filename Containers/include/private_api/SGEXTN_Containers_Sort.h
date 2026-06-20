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
template <typename T, typename Comparator> class Sort {
public:
    Sort(T* start, int length);
    Sort(const Sort& x) = delete;
    Sort& operator=(const Sort& x) = delete;
    Sort(Sort&& x) = delete;
    Sort& operator=(Sort&& x) = delete;
    ~Sort();
    T* private_firstBuffer;
    T* private_secondBuffer;
    int private_length;
    int private_minimumBlockSize;
    bool private_mainIsSecond;
    Comparator private_comparatorInstance;
    void private_insertSort(int left, int right);
    void private_mergeTwoBlocks(T* initialLocation, T* finalLocation, int firstBlockSize, int secondBlockSize);
    void private_mergeAllBlocks(T* initialLocation, T* finalLocation, int blockSize);
    void doSort();
    static void private_sort(T* start, int length);
};
}
}

#include <private_api/SGEXTN_Containers_Sort_impl.h>
