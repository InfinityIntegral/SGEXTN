#ifndef SGLSORT_H
#define SGLSORT_H

class SGLSort {
protected:
    template <typename T, typename Comparator> static void insertionSort(T* start, int left, int right, Comparator comparatorInstance);
    template <typename T, typename Comparator> static void enforceHeap(T* start, int count, int index, int left, Comparator comparatorInstance);
    template <typename T, typename Comparator> static void heapSort(T* start, int left, int right, Comparator comparatorInstance);
    template <typename T, typename Comparator> static int partition(T* start, int low, int high, Comparator comparatorInstance);
    template <typename T, typename Comparator> static void introSort(T* start, int low, int high, int maximumDepth, Comparator comparatorInstance);
public:
    template <typename T, typename Comparator> static void sort(T* start, T* end);
};

inline int log2(int n){
    if(n < 4){return 1;}
    if(n < 8){return 2;}
    if(n < 16){return 3;}
    if(n < 32){return 4;}
    if(n < 64){return 5;}
    if(n < 128){return 6;}
    if(n < 256){return 7;}
    if(n < 512){return 8;}
    if(n < 1024){return 9;}
    if(n < 2048){return 10;}
    if(n < 4096){return 11;}
    if(n < 8192){return 12;}
    if(n < 16384){return 13;}
    if(n < 32768){return 14;}
    if(n < 65536){return 15;}
    return 16;
}

template <typename T, typename Comparator> void SGLSort::sort(T* start, T* end){
    if(start >= end){return;}
    int log2 = 10;
    SGLSort::introSort(start, 0, end - start - 1, 2 * log2(end - start), Comparator());
}

template <typename T, typename Comparator> void SGLSort::insertionSort(T* start, int left, int right, Comparator comparatorInstance){
    for (int i = left + 1; i <= right; i++) {
        T key = (*(start + i));
        int j = i - 1;
        while(j >= left && comparatorInstance(key, (*(start + j))) == true){
            (*(start + j + 1)) = (*(start + j));
            j--;
        }
        (*(start + j + 1)) = key;
    }    
}

template <typename T, typename Comparator> void SGLSort::enforceHeap(T* start, int count, int index, int left, Comparator comparatorInstance){
    int largest = index;
    int l = 2*index - left + 1;
    int r = l + 1;
    if(r < left + count && comparatorInstance((*(start + largest)), (*(start + r))) == true){
        if(comparatorInstance((*(start + l)), (*(start + r))) == true){largest = r;}
        else{largest = l;}
    }
    else if(l < left + count && comparatorInstance((*(start + largest)), (*(start + l))) == true){largest = l;}
    if(largest != index){
        const T& tempVal = (*(start + largest));
        (*(start + largest)) = (*(start + index));
        (*(start + index)) = tempVal;
        SGLSort::enforceHeap(start, count, largest, left, comparatorInstance);
    }
}

template <typename T, typename Comparator> void SGLSort::heapSort(T* start, int left, int right, Comparator comparatorInstance){
    int n = right - left + 1;
    for(int i = left + n/2 - 1; i >= left; i--){
        SGLSort::enforceHeap(start, n, i, left, comparatorInstance);
    }
    for(int i = right; i > left; i--){
        T tempVal = (*(start + left));
        (*(start + left)) = (*(start + i));
        (*(start + i)) = tempVal;
        SGLSort::enforceHeap(start, i - left, left, left, comparatorInstance);
    }
}

template <typename T, typename Comparator> int SGLSort::partition(T* start, int low, int high, Comparator comparatorInstance){
    int i = low - 1;
    for(int j = low; j < high; j++){
        if(comparatorInstance((*(start + high)), (*(start + j))) == false){
            i++;
            T tempVal = (*(start + i));
            (*(start + i)) = (*(start + j));
            (*(start + j)) = tempVal;
        }
    }
    i++;
    T tempVal0 = (*(start + i));
    (*(start + i)) = (*(start + high));
    (*(start + high)) = tempVal0;
    return i;
}

template <typename T, typename Comparator> void SGLSort::introSort(T* start, int low, int high, int maximumDepth, Comparator comparatorInstance){
    const int size = high - low + 1;
    if(size <= 16){
        SGLSort::insertionSort(start, low, high, comparatorInstance);
        return;
    }
    if(maximumDepth == 0){
        SGLSort::heapSort(start, low, high, comparatorInstance);
        return;
    }
    int p = SGLSort::partition(start, low, high, comparatorInstance);
    SGLSort::introSort(start, low, p - 1, maximumDepth - 1, comparatorInstance);
    SGLSort::introSort(start, p + 1, high, maximumDepth - 1, comparatorInstance);
}

#endif // SGLSORT_H
