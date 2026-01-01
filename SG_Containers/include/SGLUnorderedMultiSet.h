#ifndef SGLUNORDEREDMULTISET_H
#define SGLUNORDEREDMULTISET_H

#include <private_api_Containers/SGLCrash.h>

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedMultiSet {
protected:
    class Slot;
    Slot* dataInternal;
    int lengthInternal;
    int memoryUsedInternal;
    int memoryLengthInternal;
    EqualityCheck equalityCheckInstance;
    HashFunction hashFunctionInstance;
    bool rehash(const T& x, int count);
    
public:
    SGLUnorderedMultiSet();
    SGLUnorderedMultiSet(const SGLUnorderedMultiSet& x);
    SGLUnorderedMultiSet& operator=(const SGLUnorderedMultiSet& x);
    SGLUnorderedMultiSet(SGLUnorderedMultiSet&& x) noexcept;
    SGLUnorderedMultiSet& operator=(SGLUnorderedMultiSet&& x) noexcept;
    ~SGLUnorderedMultiSet();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    void insert(const T& x);
    bool erase(const T& x);
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] int count(const T& x) const;
    
    class Iterator;
    class ConstIterator;
    
    [[nodiscard]] Iterator begin();
    [[nodiscard]] Iterator end();
    [[nodiscard]] ConstIterator constBegin() const;
    [[nodiscard]] ConstIterator constEnd() const;
    bool erase(Iterator& x);
    [[nodiscard]] Iterator find(const T& x);
    [[nodiscard]] ConstIterator find(const T& x) const;
};

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Slot {
public:
    static const char unused = 0;
    static const char active = 1;
    static const char deleted = 2;
    char usageStatus;
    T value;
    int count;
    Slot();
};

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator {
    friend class SGLUnorderedMultiSet;
public:
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(Iterator x);
    bool operator!=(Iterator x);
    const T& operator*();
protected:
    int slot;
    int copy;
    SGLUnorderedMultiSet* associatedSet;
    Iterator(int x, int c, SGLUnorderedMultiSet* s);
};

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator {
    friend class SGLUnorderedMultiSet;
public:
    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);
    bool operator==(ConstIterator x);
    bool operator!=(ConstIterator x);
    const T& operator*();
protected:
    int slot;
    int copy;
    const SGLUnorderedMultiSet* associatedSet;
    ConstIterator(int x, int c, const SGLUnorderedMultiSet* s);
};

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::SGLUnorderedMultiSet(){
    dataInternal = nullptr;
    lengthInternal = 0;
    memoryUsedInternal = 0;
    memoryLengthInternal = 0;
    equalityCheckInstance = EqualityCheck();
    hashFunctionInstance = HashFunction();
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Slot::Slot(){
    usageStatus = unused;
    count = 0;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::SGLUnorderedMultiSet(const SGLUnorderedMultiSet& x){
    equalityCheckInstance = EqualityCheck();
    hashFunctionInstance = HashFunction();
    dataInternal = new Slot[x.memoryLengthInternal];
    lengthInternal = x.lengthInternal;
    memoryUsedInternal = 0;
    memoryLengthInternal = x.memoryLengthInternal;
    for(int i=0; i<memoryLengthInternal; i++){
        if((*(x.dataInternal + i)).usageStatus == Slot::active){
          bool addedMemory = rehash((*(x.dataInternal + i)).value, (*(x.dataInternal + i)).count);
          if(addedMemory == true){memoryUsedInternal++;}
        }
    }
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>& SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::operator=(const SGLUnorderedMultiSet& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new Slot[x.memoryLengthInternal];
    lengthInternal = x.lengthInternal;
    memoryUsedInternal = 0;
    memoryLengthInternal = x.memoryLengthInternal;
    for(int i=0; i<memoryLengthInternal; i++){
        if((*(x.dataInternal + i)).usageStatus == Slot::active){
          bool addedMemory = rehash((*(x.dataInternal + i)).value, (*(x.dataInternal + i)).count);
          if(addedMemory == true){memoryUsedInternal++;}
        }
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::SGLUnorderedMultiSet(SGLUnorderedMultiSet&& x) noexcept {
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    memoryUsedInternal = x.memoryUsedInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    x.memoryUsedInternal = 0;
    x.memoryLengthInternal = 0;
    equalityCheckInstance = EqualityCheck();
    hashFunctionInstance = HashFunction();
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>& SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::operator=(SGLUnorderedMultiSet&& x) noexcept {
    delete[] dataInternal;
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    memoryUsedInternal = x.memoryUsedInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    x.memoryUsedInternal = 0;
    x.memoryLengthInternal = 0;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::~SGLUnorderedMultiSet(){
    delete[] dataInternal;
}

template <typename T, typename EqualityCheck, typename HashFunction> int SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::length() const {
    return lengthInternal;
}

template <typename T, typename EqualityCheck, typename HashFunction> void SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLengthInternal){return;}
    Slot* oldPointer = dataInternal;
    int oldMemoryLength = memoryLengthInternal;
    dataInternal = new Slot[newMemoryLength];
    memoryLengthInternal = newMemoryLength;
    memoryUsedInternal = 0;
    for(int i=0; i<oldMemoryLength; i++){
        if((*(oldPointer + i)).usageStatus == Slot::active){
            bool addedMemory = rehash((*(oldPointer + i)).value, (*(oldPointer + i)).count);
            if(addedMemory == true){memoryUsedInternal++;}
        }
    }
    delete[] oldPointer;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::rehash(const T& x, int count){
    int hash = hashFunctionInstance(x) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).value, x) == true){
            (*(dataInternal + hash)).count += count;
            return false;
        }
        if((*(dataInternal + hash)).usageStatus != Slot::active){
            (*(dataInternal + hash)).value = x;
            (*(dataInternal + hash)).usageStatus = Slot::active;
            (*(dataInternal + hash)).count = count;
            return true;
        }
        hash++;
    }
}

template <typename T, typename EqualityCheck, typename HashFunction> void SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::insert(const T& x){
    if(memoryLengthInternal == 0){reserve(3);}
    else if(3 * memoryUsedInternal >= memoryLengthInternal){reserve(3 * memoryLengthInternal);}
    bool addedMemory = rehash(x, 1);
    if(addedMemory == true){memoryUsedInternal++;}
    lengthInternal++;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::erase(const T& x){
    Iterator i = find(x);
    return erase(i);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::contains(const T& x) const {
    if(find(x) == constEnd()){return false;}
    return true;
}

template <typename T, typename EqualityCheck, typename HashFunction> int SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::count(const T& x) const {
    if(find(x) == constEnd()){return 0;}
    return (*(dataInternal + find(x).slot)).count;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator::Iterator(int x, int c, SGLUnorderedMultiSet* s){
    slot = x;
    copy = c;
    associatedSet = s;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator::ConstIterator(int x, int c, const SGLUnorderedMultiSet* s){
    slot = x;
    copy = c;
    associatedSet = s;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator& SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator::operator++(){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    if(slot != -1 && copy < (*((*associatedSet).dataInternal + slot)).count - 1){
        copy++;
        return (*this);
    }
    while(true){
        slot++;
        if(slot == (*associatedSet).memoryLengthInternal){
            slot = -1;
            copy = 0;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){
            copy = 0;
            break;
        }
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator& SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator::operator++(){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    if(slot != -1 && copy < (*((*associatedSet).dataInternal + slot)).count - 1){
        copy++;
        return (*this);
    }
    while(true){
        slot++;
        if(slot == (*associatedSet).memoryLengthInternal){
            slot = -1;
            copy = 0;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){
            copy = 0;
            break;
        }
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator::operator++(int){
    Iterator prev = (*this);
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    if(slot != -1 && copy < (*((*associatedSet).dataInternal + slot)).count - 1){
        copy++;
        return prev;
    }
    while(true){
        slot++;
        if(slot == -1 || slot == (*associatedSet).memoryLengthInternal){
            slot = -1;
            copy = 0;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){
            copy = 0;
            break;
        }
    }
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator::operator++(int){
    ConstIterator prev = (*this);
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    if(slot != -1 && copy < (*((*associatedSet).dataInternal + slot)).count - 1){
        copy++;
        return prev;
    }
    while(true){
        slot++;
        if(slot == (*associatedSet).memoryLengthInternal){
            slot = -1;
            copy = 0;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){
            copy = 0;
            break;
        }
    }
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator& SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator::operator--(){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    if(copy > 0){
        copy--;
        return (*this);
    }
    while(true){
        slot--;
        if(slot == -2){
            slot = (*associatedSet).memoryLengthInternal - 1;
            copy = (*((*associatedSet).dataInternal + (*associatedSet).memoryLengthInternal - 1)).count - 1;
            break;
        }
        if(slot == -1){
            copy = 0;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){
            copy = (*((*associatedSet).dataInternal + slot)).count - 1;
            break;
        }
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator& SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator::operator--(){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    if(copy > 0){
        copy--;
        return (*this);
    }
    while(true){
        slot--;
        if(slot == -2){
            slot = (*associatedSet).memoryLengthInternal - 1;
            copy = (*((*associatedSet).dataInternal + (*associatedSet).memoryLengthInternal - 1)).count - 1;
            break;
        }
        if(slot == -1){
            copy = 0;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){
            copy = (*((*associatedSet).dataInternal + slot)).count - 1;
            break;
        }
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator::operator--(int){
    Iterator prev = (*this);
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    if(copy > 0){
        copy--;
        return prev;
    }
    while(true){
        slot--;
        if(slot == -2){
            slot = (*associatedSet).memoryLengthInternal - 1;
            copy = (*((*associatedSet).dataInternal + (*associatedSet).memoryLengthInternal - 1)).count - 1;
            break;
        }
        if(slot == -1){
            copy = 0;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){
            copy = (*((*associatedSet).dataInternal + slot)).count - 1;
            break;
        }
    }
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator::operator--(int){
    ConstIterator prev = (*this);
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    if(copy > 0){
        copy--;
        return prev;
    }
    while(true){
        slot--;
        if(slot == -2){
            slot = (*associatedSet).memoryLengthInternal - 1;
            copy = (*((*associatedSet).dataInternal + (*associatedSet).memoryLengthInternal - 1)).count - 1;
            break;
        }
        if(slot == -1){
            copy = 0;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){
            copy = (*((*associatedSet).dataInternal + slot)).count - 1;
            break;
        }
    }
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator::operator==(Iterator x){
    return (slot == x.slot && associatedSet == x.associatedSet && copy == x.copy);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator::operator==(ConstIterator x){
    return (slot == x.slot && associatedSet == x.associatedSet && copy == x.copy);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator::operator!=(Iterator x){
    return (slot != x.slot || associatedSet != x.associatedSet || copy != x.copy);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator::operator!=(ConstIterator x){
    return (slot != x.slot || associatedSet != x.associatedSet || copy != x.copy);
}

template <typename T, typename EqualityCheck, typename HashFunction> const T& SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator::operator*(){
    if(slot == -1){SGLCrash::crash("SGLUnorderedMultiSet::Iterator::operator* crashed because the iterator is the end iterator");}
    return (*((*associatedSet).dataInternal + slot)).value;
}

template <typename T, typename EqualityCheck, typename HashFunction> const T& SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator::operator*(){
    if(slot == -1){SGLCrash::crash("SGLUnorderedMultiSet::ConstIterator::operator* crashed because the iterator is the end iterator");}
    return (*((*associatedSet).dataInternal + slot)).value;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::begin(){
    return (++end());
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::end(){
    return Iterator(-1, 0, this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::constBegin() const {
    return (++constEnd());
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::constEnd() const {
    return ConstIterator(-1, 0, this);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::erase(Iterator& x){
    if(x.slot < 0 || x.slot >= memoryLengthInternal){return false;}
    int pos = x.slot;
    x.slot--;
    if((*(dataInternal + pos)).count > 1){
        (*(dataInternal + pos)).count--;
        lengthInternal--;
        return true;
    }
    (*(dataInternal + pos)).usageStatus = Slot::deleted;
    (*(dataInternal + pos)).count = 0;
    const int oldPos = pos;
    bool canDelete = false;
    bool wrapAround = false;
    for(; pos<memoryLengthInternal; pos++){
        if((*(dataInternal + pos)).usageStatus == Slot::active){break;}
        if((*(dataInternal + pos)).usageStatus == Slot::unused){
            canDelete = true;
            pos--;
            break;
        }
        if(pos == memoryLengthInternal - 1){wrapAround = true;}
    }
    if(wrapAround == true){
        for(pos=0; pos<=oldPos; pos++){
            if(pos == oldPos){
                canDelete = true;
                break;
            }
            if((*(dataInternal + pos)).usageStatus == Slot::unused){
                canDelete = true;
                pos--;
                break;
            }
            if((*(dataInternal + pos)).usageStatus == Slot::active){break;}
        }
    }
    if(canDelete == true){
        int deleted = 0;
        if(wrapAround == false){
            for(int i=oldPos; i<=pos; i++){
                (*(dataInternal + i)).usageStatus = Slot::unused;
                deleted++;
            }
        }
        else{
            for(int i=oldPos; i<memoryLengthInternal; i++){
                (*(dataInternal + i)).usageStatus = Slot::unused;
                deleted++;
            }
            for(int i=0; i<=pos; i++){
                (*(dataInternal + i)).usageStatus = Slot::unused;
                deleted++;
            }
        }
        memoryUsedInternal -= deleted;
    }
    lengthInternal--;
    return true;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::find(const T& x){
    if(memoryLengthInternal == 0){return end();}
    int hash = hashFunctionInstance(x) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).value, x) == true){return Iterator(hash, 0, this);}
        if((*(dataInternal + hash)).usageStatus == Slot::unused){return Iterator(-1, 0, this);}
        hash++;
    }
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMultiSet<T, EqualityCheck, HashFunction>::find(const T& x) const {
    if(memoryLengthInternal == 0){return constEnd();}
    int hash = hashFunctionInstance(x) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).value, x) == true){return ConstIterator(hash, 0, this);}
        if((*(dataInternal + hash)).usageStatus == Slot::unused){return ConstIterator(-1, 0, this);}
        hash++;
    }
}

#endif // SGLUNORDEREDMULTISET_H
