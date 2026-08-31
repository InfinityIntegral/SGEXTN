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
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/Containers/PlacementNew.h>

template <typename T, typename Comparator> SGEXTN::Containers::Sort<T, Comparator>::Sort(T* start, int length) : firstBuffer_(start), secondBuffer_(nullptr), length_(length), mainIsSecond_(false), comparatorInstance_(), minimumBlockSize_(32) {
    if(length > 0){
        secondBuffer_ = static_cast<T*>(::operator new(length * sizeof(T)));
    }
    for(int i=0; i<length; i++){
        new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(secondBuffer_ + i)) T(*(firstBuffer_ + i));
    }
}

template <typename T, typename Comparator> SGEXTN::Containers::Sort<T, Comparator>::~Sort(){
    for(int i=0; i<length_; i++){
        (*(secondBuffer_ + i)).~T();
    }
    ::operator delete(static_cast<void*>(secondBuffer_));
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::insertSort(int left, int right){
    for(int i=left+1; i<right; i++){
        T thisKey = static_cast<T&&>(*(firstBuffer_ + i));
        int j = i - 1;
        while(j >= left && comparatorInstance_(thisKey, (*(firstBuffer_ + j))) == true){
            (*(firstBuffer_ + j + 1)) = static_cast<T&&>(*(firstBuffer_ + j));
            j--;
        }
        (*(firstBuffer_ + j + 1)) = static_cast<T&&>(thisKey);
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::mergeTwoBlocks(T* initialLocation, T* finalLocation, int firstBlockSize, int secondBlockSize){
    int i1 = 0;
    int i2 = 0;
    for(int i=0; i<firstBlockSize+secondBlockSize; i++){
        if(i2 == secondBlockSize || (i1 != firstBlockSize && comparatorInstance_((*(initialLocation + firstBlockSize + i2)), (*(initialLocation + i1))) == false)){
            (*(finalLocation + i)) = static_cast<T&&>(*(initialLocation + i1));
            i1++;
        }
        else{
            (*(finalLocation + i)) = static_cast<T&&>(*(initialLocation + firstBlockSize + i2));
            i2++;
        }
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::mergeAllBlocks(T* initialLocation, T* finalLocation, int blockSize){
    for(int i=0; i<length_/blockSize; i++){
        mergeTwoBlocks(initialLocation + i * blockSize, finalLocation + i * blockSize, blockSize / 2, blockSize / 2);
    }
    const int remainderStart = blockSize * (length_ / blockSize);
    const int remainderLength = length_ - remainderStart;
    if(remainderLength > blockSize / 2){mergeTwoBlocks(initialLocation + remainderStart, finalLocation + remainderStart, blockSize / 2, remainderLength - blockSize / 2);}
    else{mergeTwoBlocks(initialLocation + remainderStart, finalLocation + remainderStart, remainderLength, 0);}
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::doSort(){
    for(int i=0; i<length_/minimumBlockSize_; i++){
        insertSort(i * minimumBlockSize_, (i + 1) * minimumBlockSize_);
    }
    insertSort(minimumBlockSize_ * (length_ / minimumBlockSize_), length_);
    int blockSize = minimumBlockSize_;
    while(blockSize < length_){
        blockSize *= 2;
        if(mainIsSecond_ == false){
            mainIsSecond_ = true;
            mergeAllBlocks(firstBuffer_, secondBuffer_, blockSize);
        }
        else{
            mainIsSecond_ = false;
            mergeAllBlocks(secondBuffer_, firstBuffer_, blockSize);
        }
    }
    if(mainIsSecond_ == true){
        for(int i=0; i<length_; i++){
            (*(firstBuffer_ + i)) = static_cast<T&&>(*(secondBuffer_ + i));
        }
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::sort(T* start, int length){
    SGEXTN::Containers::Sort<T, Comparator>(start, length).doSort();
}
