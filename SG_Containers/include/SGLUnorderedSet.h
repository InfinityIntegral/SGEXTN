#ifndef SGLUNORDEREDSET_H
#define SGLUNORDEREDSET_H

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedSet {
protected:
    class Slot;
    Slot* dataInternal;
    int lengthInternal;
    int memoryUsedInternal;
    int memoryLengthInternal;
    EqualityCheck equalityCheckInstance;
    HashFunction hashFunctionInstance;
    bool rehash(const T& x);
    
public:
    SGLUnorderedSet();
    SGLUnorderedSet(const SGLUnorderedSet& x);
    SGLUnorderedSet& operator=(const SGLUnorderedSet& x);
    SGLUnorderedSet(SGLUnorderedSet&& x) noexcept;
    SGLUnorderedSet& operator=(SGLUnorderedSet&& x) noexcept;
    ~SGLUnorderedSet();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    bool insert(const T& x);
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

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedSet<T, EqualityCheck, HashFunction>::Slot {
public:
    static const char unused = 0;
    static const char active = 1;
    static const char deleted = 2;
    char usageStatus;
    T value;
    Slot();
};

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator {
    friend class SGLUnorderedSet;
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
    SGLUnorderedSet* associatedSet;
    Iterator(int x, SGLUnorderedSet* s);
};

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator {
    friend class SGLUnorderedSet;
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
    const SGLUnorderedSet* associatedSet;
    ConstIterator(int x, const SGLUnorderedSet* s);
};

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>::SGLUnorderedSet(){
    dataInternal = nullptr;
    lengthInternal = 0;
    memoryUsedInternal = 0;
    memoryLengthInternal = 0;
    equalityCheckInstance = EqualityCheck();
    hashFunctionInstance = HashFunction();
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>::Slot::Slot(){
    usageStatus = unused;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>::SGLUnorderedSet(const SGLUnorderedSet& x){
    equalityCheckInstance = EqualityCheck();
    hashFunctionInstance = HashFunction();
    dataInternal = new Slot[x.memoryLengthInternal];
    lengthInternal = x.lengthInternal;
    memoryUsedInternal = 0;
    memoryLengthInternal = x.memoryLengthInternal;
    for(int i=0; i<memoryLengthInternal; i++){
        if((*(x.dataInternal + i)).usageStatus == Slot::active){
          rehash((*(x.dataInternal + i)).value);
          memoryUsedInternal++;
        }
    }
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>& SGLUnorderedSet<T, EqualityCheck, HashFunction>::operator=(const SGLUnorderedSet& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new Slot[x.memoryLengthInternal];
    lengthInternal = x.lengthInternal;
    memoryUsedInternal = 0;
    memoryLengthInternal = x.memoryLengthInternal;
    for(int i=0; i<memoryLengthInternal; i++){
        if((*(x.dataInternal + i)).usageStatus == Slot::active){
          rehash((*(x.dataInternal + i)).value);
          memoryUsedInternal++;
        }
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>::SGLUnorderedSet(SGLUnorderedSet&& x) noexcept {
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

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>& SGLUnorderedSet<T, EqualityCheck, HashFunction>::operator=(SGLUnorderedSet&& x) noexcept {
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

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>::~SGLUnorderedSet(){
    delete[] dataInternal;
}

template <typename T, typename EqualityCheck, typename HashFunction> int SGLUnorderedSet<T, EqualityCheck, HashFunction>::length() const {
    return lengthInternal;
}

template <typename T, typename EqualityCheck, typename HashFunction> void SGLUnorderedSet<T, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLengthInternal){return;}
    Slot* oldPointer = dataInternal;
    int oldMemoryLength = memoryLengthInternal;
    dataInternal = new Slot[newMemoryLength];
    memoryLengthInternal = newMemoryLength;
    memoryUsedInternal = 0;
    for(int i=0; i<oldMemoryLength; i++){
        if((*(oldPointer + i)).usageStatus == Slot::active){
            rehash((*(oldPointer + i)).value);
            memoryUsedInternal++;
        }
    }
    delete[] oldPointer;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::rehash(const T& x){
    int hash = hashFunctionInstance(x) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).value, x) == true){return false;}
        if((*(dataInternal + hash)).usageStatus != Slot::active){
            (*(dataInternal + hash)).value = x;
            (*(dataInternal + hash)).usageStatus = Slot::active;
            return true;
        }
        hash++;
    }
    return true;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::insert(const T& x){
    if(memoryLengthInternal == 0){reserve(3);}
    else if(3 * memoryUsedInternal >= memoryLengthInternal){reserve(3 * memoryLengthInternal);}
    bool result = rehash(x);
    if(result == true){
        memoryUsedInternal++;
        lengthInternal++;
    }
    return result;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::erase(const T& x){
    Iterator i = find(x);
    return erase(i);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::contains(const T& x) const {
    if(find(x) == constEnd()){return false;}
    return true;
}

template <typename T, typename EqualityCheck, typename HashFunction> int SGLUnorderedSet<T, EqualityCheck, HashFunction>::count(const T& x) const {
    if(find(x) == constEnd()){return 0;}
    return 1;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator::Iterator(int x, SGLUnorderedSet* s){
    slot = x;
    associatedSet = s;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator::ConstIterator(int x, const SGLUnorderedSet* s){
    slot = x;
    associatedSet = s;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator& SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator::operator++(){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    while(true){
        slot++;
        if(slot == (*associatedSet).memoryLengthInternal){
            slot = -1;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){break;}
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator& SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator::operator++(){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    while(true){
        slot++;
        if(slot == (*associatedSet).memoryLengthInternal){
            slot = -1;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){break;}
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator::operator++(int){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    Iterator prev = (*this);
    while(true){
        slot++;
        if(slot == (*associatedSet).memoryLengthInternal){
            slot = -1;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){break;}
    }
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator::operator++(int){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    ConstIterator prev = (*this);
    while(true){
        slot++;
        if(slot == (*associatedSet).memoryLengthInternal){
            slot = -1;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){break;}
    }
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator& SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator::operator--(){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    while(true){
        slot--;
        if(slot == -2){
            slot = (*associatedSet).memoryLengthInternal - 1;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){break;}
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator& SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator::operator--(){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    while(true){
        slot--;
        if(slot == -2){
            slot = (*associatedSet).memoryLengthInternal - 1;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){break;}
    }
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator::operator--(int){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    Iterator prev = (*this);
    while(true){
        slot--;
        if(slot == -2){
            slot = (*associatedSet).memoryLengthInternal - 1;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){break;}
    }
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator::operator--(int){
    if((*associatedSet).memoryLengthInternal == 0){
        slot = -1;
        return (*this);
    }
    ConstIterator prev = (*this);
    while(true){
        slot--;
        if(slot == -2){
            slot = (*associatedSet).memoryLengthInternal - 1;
            break;
        }
        if((*((*associatedSet).dataInternal + slot)).usageStatus == Slot::active){break;}
    }
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator::operator==(Iterator x){
    return (slot == x.slot && associatedSet == x.associatedSet);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator::operator==(ConstIterator x){
    return (slot == x.slot && associatedSet == x.associatedSet);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator::operator!=(Iterator x){
    return (slot != x.slot || associatedSet != x.associatedSet);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator::operator!=(ConstIterator x){
    return (slot != x.slot || associatedSet != x.associatedSet);
}

template <typename T, typename EqualityCheck, typename HashFunction> const T& SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator::operator*(){
    return (*((*associatedSet).dataInternal + slot)).value;
}

template <typename T, typename EqualityCheck, typename HashFunction> const T& SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator::operator*(){
    return (*((*associatedSet).dataInternal + slot)).value;
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::begin(){
    return (++end());
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::end(){
    return Iterator(-1, this);
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::constBegin() const {
    return (++constEnd());
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::constEnd() const {
    return ConstIterator(-1, this);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGLUnorderedSet<T, EqualityCheck, HashFunction>::erase(Iterator& x){
    if(x.slot < 0 || x.slot >= memoryLengthInternal){return false;}
    int pos = x.slot;
    x.slot--;
    (*(dataInternal + pos)).usageStatus = Slot::deleted;
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

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::Iterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::find(const T& x){
    if(memoryLengthInternal == 0){return end();}
    int hash = hashFunctionInstance(x) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).value, x) == true){return Iterator(hash, this);}
        if((*(dataInternal + hash)).usageStatus == Slot::unused){return Iterator(-1, this);}
        hash++;
    }
}

template <typename T, typename EqualityCheck, typename HashFunction> typename SGLUnorderedSet<T, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedSet<T, EqualityCheck, HashFunction>::find(const T& x) const {
    if(memoryLengthInternal == 0){return constEnd();}
    int hash = hashFunctionInstance(x) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).value, x) == true){return ConstIterator(hash, this);}
        if((*(dataInternal + hash)).usageStatus == Slot::unused){return ConstIterator(-1, this);}
        hash++;
    }
}

#endif // SGLUNORDEREDSET_H
