#ifndef SGLUNORDEREDMAP_H
#define SGLUNORDEREDMAP_H

#include <private_api_Containers/SGLCrash.h>

template <typename K, typename V, typename EqualityCheck, typename HashFunction> class SGLUnorderedMap {
protected:
    class Slot {
    public:
        static const char unused = 0;
        static const char active = 1;
        static const char deleted = 2;
        char usageStatus;
        K key;
        V value;
        Slot();
    };
    Slot* dataInternal;
    int lengthInternal;
    int memoryUsedInternal;
    int memoryLengthInternal;
    EqualityCheck equalityCheckInstance;
    HashFunction hashFunctionInstance;
    void rehash(const K& xKey, const V& xValue);
    
public:
    SGLUnorderedMap();
    SGLUnorderedMap(const SGLUnorderedMap& x);
    SGLUnorderedMap& operator=(const SGLUnorderedMap& x);
    SGLUnorderedMap(SGLUnorderedMap&& x) noexcept;
    SGLUnorderedMap& operator=(SGLUnorderedMap&& x) noexcept;
    ~SGLUnorderedMap();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    void insert(const K& xKey, const V& xValue);
    void erase(const K& x);
    [[nodiscard]] bool contains(const K& x) const;
    [[nodiscard]] int count(const K& x) const;
    [[nodiscard]] V& at(const K& x);
    [[nodiscard]] const V& at(const K &x) const;
    
    class Iterator {
        friend class SGLUnorderedMap;
    public:
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(Iterator x);
        bool operator!=(Iterator x);
        const K& key();
        V& value();
    protected:
        int slot;
        SGLUnorderedMap* associatedSet;
        Iterator(int x, SGLUnorderedMap* s);
    };
    
    class ConstIterator {
        friend class SGLUnorderedMap;
    public:
        ConstIterator& operator++();
        ConstIterator operator++(int);
        ConstIterator& operator--();
        ConstIterator operator--(int);
        bool operator==(ConstIterator x);
        bool operator!=(ConstIterator x);
        const K& key();
        const V& value();
    protected:
        int slot;
        const SGLUnorderedMap* associatedSet;
        ConstIterator(int x, const SGLUnorderedMap* s);
    };
    
    [[nodiscard]] Iterator begin();
    [[nodiscard]] Iterator end();
    [[nodiscard]] ConstIterator constBegin() const;
    [[nodiscard]] ConstIterator constEnd() const;
    void erase(Iterator& x);
    [[nodiscard]] Iterator find(const K& x);
    [[nodiscard]] ConstIterator find(const K& x) const;
};

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::SGLUnorderedMap(){
    dataInternal = nullptr;
    lengthInternal = 0;
    memoryUsedInternal = 0;
    memoryLengthInternal = 0;
    equalityCheckInstance = EqualityCheck();
    hashFunctionInstance = HashFunction();
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Slot::Slot(){
    usageStatus = unused;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::SGLUnorderedMap(const SGLUnorderedMap& x){
    equalityCheckInstance = EqualityCheck();
    hashFunctionInstance = HashFunction();
    dataInternal = new Slot[x.memoryLengthInternal];
    lengthInternal = x.lengthInternal;
    memoryUsedInternal = 0;
    memoryLengthInternal = x.memoryLengthInternal;
    for(int i=0; i<memoryLengthInternal; i++){
        if((*(x.dataInternal + i)).usageStatus == Slot::active){
          rehash((*(x.dataInternal + i)).key, (*(x.dataInternal + i)).value);
          memoryUsedInternal++;
        }
    }
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::operator=(const SGLUnorderedMap& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new Slot[x.memoryLengthInternal];
    lengthInternal = x.lengthInternal;
    memoryUsedInternal = 0;
    memoryLengthInternal = x.memoryLengthInternal;
    for(int i=0; i<memoryLengthInternal; i++){
        if((*(x.dataInternal + i)).usageStatus == Slot::active){
          rehash((*(x.dataInternal + i)).key, (*(x.dataInternal + i)).value);
          memoryUsedInternal++;
        }
    }
    return (*this);
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::SGLUnorderedMap(SGLUnorderedMap&& x) noexcept {
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::operator=(SGLUnorderedMap&& x) noexcept {
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::~SGLUnorderedMap(){
    delete[] dataInternal;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> int SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::length() const {
    return lengthInternal;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> void SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLengthInternal){return;}
    Slot* oldPointer = dataInternal;
    int oldMemoryLength = memoryLengthInternal;
    dataInternal = new Slot[newMemoryLength];
    memoryLengthInternal = newMemoryLength;
    memoryUsedInternal = 0;
    for(int i=0; i<oldMemoryLength; i++){
        if((*(oldPointer + i)).usageStatus == Slot::active){
            rehash((*(oldPointer + i)).key, (*(oldPointer + i)).value);
            memoryUsedInternal++;
        }
    }
    delete[] oldPointer;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> void SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::rehash(const K& xKey, const V& xValue){
    int hash = hashFunctionInstance(xKey) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).key, xKey) == true){SGLCrash::crashOnInsert();}
        if((*(dataInternal + hash)).usageStatus != Slot::active){
            (*(dataInternal + hash)).key = xKey;
            (*(dataInternal + hash)).value = xValue;
            (*(dataInternal + hash)).usageStatus = Slot::active;
            return;
        }
        hash++;
    }
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> void SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::insert(const K& xKey, const V& xValue){
    if(memoryLengthInternal == 0){reserve(3);}
    else if(3 * memoryUsedInternal >= memoryLengthInternal){reserve(3 * memoryLengthInternal);}
    rehash(xKey, xValue);
    memoryUsedInternal++;
    lengthInternal++;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> void SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::erase(const K& x){
    Iterator i = find(x);
    erase(i);
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::contains(const K& x) const {
    if(find(x) == constEnd()){return false;}
    return true;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> int SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::count(const K& x) const {
    if(find(x) == constEnd()){return 0;}
    return 1;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::Iterator(int x, SGLUnorderedMap* s){
    slot = x;
    associatedSet = s;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::ConstIterator(int x, const SGLUnorderedMap* s){
    slot = x;
    associatedSet = s;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::operator++(){
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::operator++(){
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::operator++(int){
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::operator++(int){
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::operator--(){
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::operator--(){
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::operator--(int){
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::operator--(int){
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

template <typename K, typename V, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::operator==(Iterator x){
    return (slot == x.slot && associatedSet == x.associatedSet);
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::operator==(ConstIterator x){
    return (slot == x.slot && associatedSet == x.associatedSet);
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::operator!=(Iterator x){
    return (slot != x.slot || associatedSet != x.associatedSet);
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> bool SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::operator!=(ConstIterator x){
    return (slot != x.slot || associatedSet != x.associatedSet);
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> const K& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::key(){
    return (*((*associatedSet).dataInternal + slot)).key;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> V& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator::value(){
    return (*((*associatedSet).dataInternal + slot)).value;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> const K& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::key(){
    return (*((*associatedSet).dataInternal + slot)).key;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> const V& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator::value(){
    return (*((*associatedSet).dataInternal + slot)).value;
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::begin(){
    return (++end());
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::end(){
    return Iterator(-1, this);
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::constBegin() const {
    return (++constEnd());
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::constEnd() const {
    return ConstIterator(-1, this);
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> void SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::erase(Iterator& x){
    if(x.slot < 0 || x.slot >= memoryLengthInternal){SGLCrash::crashOnRemove();}
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
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::Iterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::find(const K& x){
    if(memoryLengthInternal == 0){return end();}
    int hash = hashFunctionInstance(x) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).key, x) == true){return Iterator(hash, this);}
        if((*(dataInternal + hash)).usageStatus == Slot::unused){return Iterator(-1, this);}
        hash++;
    }
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> typename SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::ConstIterator SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::find(const K& x) const {
    if(memoryLengthInternal == 0){return constEnd();}
    int hash = hashFunctionInstance(x) % memoryLengthInternal;
    if(hash < 0){hash += memoryLengthInternal;}
    while(true){
        if(hash == memoryLengthInternal){hash = 0;}
        if((*(dataInternal + hash)).usageStatus == Slot::active && equalityCheckInstance((*(dataInternal + hash)).key, x) == true){return ConstIterator(hash, this);}
        if((*(dataInternal + hash)).usageStatus == Slot::unused){return ConstIterator(-1, this);}
        hash++;
    }
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> V& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::at(const K& x){
    Iterator i = find(x);
    if(i == end()){SGLCrash::crash();}
    return i.value();
}

template <typename K, typename V, typename EqualityCheck, typename HashFunction> const V& SGLUnorderedMap<K, V, EqualityCheck, HashFunction>::at(const K& x) const {
    ConstIterator i = find(x);
    if(i == constEnd()){SGLCrash::crash();}
    return i.value();
}

#endif // SGLUNORDEREDMAP_H
