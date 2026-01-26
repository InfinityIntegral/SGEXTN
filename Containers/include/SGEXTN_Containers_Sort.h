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
    void sort();
};
}
}

#include <private_api/SGEXTN_Containers_Sort_impl.h>
