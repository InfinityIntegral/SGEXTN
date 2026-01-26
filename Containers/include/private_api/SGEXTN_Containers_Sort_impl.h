#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T, typename Comparator> SGEXTN::Containers::Sort<T, Comparator>::Sort(T* start, int length){
    if(start == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Sort constructor crashed as starting position is nullptr");}
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Sort constructor crashed as length is negative");}
    private_firstBuffer = start;
    private_secondBuffer = new T[length];
    private_length = length;
    private_mainIsSecond = false;
    private_comparatorInstance = Comparator();
    private_minimumBlockSize = 32;
}

template <typename T, typename Comparator> SGEXTN::Containers::Sort<T, Comparator>::~Sort(){
    delete[] private_secondBuffer;
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::private_insertSort(int left, int right){
    for(int i=left+1; i<right; i++){
        T thisKey = (*(private_firstBuffer + i));
        int j = i - 1;
        while(j >= left && private_comparatorInstance(thisKey, (*(private_firstBuffer + j))) == true){
            (*(private_firstBuffer + j + 1)) = (*(private_firstBuffer + j));
            j--;
        }
        (*(private_firstBuffer + j + 1)) = thisKey;
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::private_mergeTwoBlocks(T* initialLocation, T* finalLocation, int firstBlockSize, int secondBlockSize){
    int i1 = 0;
    int i2 = 0;
    for(int i=0; i<firstBlockSize+secondBlockSize; i++){
        if(i2 == secondBlockSize || (i1 != firstBlockSize && private_comparatorInstance((*(initialLocation + firstBlockSize + i2)), (*(initialLocation + i1))) == false)){
            (*(finalLocation + i)) = (*(initialLocation + i1));
            i1++;
        }
        else{
            (*(finalLocation + i)) = (*(initialLocation + firstBlockSize + i2));
            i2++;
        }
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::private_mergeAllBlocks(T* initialLocation, T* finalLocation, int blockSize){
    for(int i=0; i<private_length/blockSize; i++){
        private_mergeTwoBlocks(initialLocation + i * blockSize, finalLocation + i * blockSize, blockSize / 2, blockSize / 2);
    }
    int remainderStart = blockSize * (private_length / blockSize);
    int remainderLength = private_length - remainderStart;
    if(remainderLength > blockSize / 2){private_mergeTwoBlocks(initialLocation + remainderStart, finalLocation + remainderStart, blockSize / 2, remainderLength - blockSize / 2);}
    else{private_mergeTwoBlocks(initialLocation + remainderStart, finalLocation + remainderStart, remainderLength, 0);}
}

template <typename T, typename Comparator> void SGEXTN::Containers::Sort<T, Comparator>::sort(){
    for(int i=0; i<private_length/private_minimumBlockSize; i++){
        private_insertSort(i * private_minimumBlockSize, (i + 1) * private_minimumBlockSize);
    }
    private_insertSort(private_minimumBlockSize * (private_length / private_minimumBlockSize), private_length);
    int blockSize = private_minimumBlockSize;
    while(blockSize < private_length){
        blockSize *= 2;
        if(private_mainIsSecond == false){
            private_mainIsSecond = true;
            private_mergeAllBlocks(private_firstBuffer, private_secondBuffer, blockSize);
        }
        else{
            private_mainIsSecond = false;
            private_mergeAllBlocks(private_secondBuffer, private_firstBuffer, blockSize);
        }
    }
    if(private_mainIsSecond == true){
        for(int i=0; i<private_length; i++){
            (*(private_firstBuffer + i)) = (*(private_secondBuffer + i));
        }
    }
}
