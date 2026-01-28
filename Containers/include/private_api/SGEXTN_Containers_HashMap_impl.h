#pragma once

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>::HashMapSlot(){
    status = HashMapSlotStatus::Unused;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::HashMap(){
    data = nullptr;
    activeLength = 0;
    memoryUsedLength = 0;
    memoryTotalLength = 0;
    loadFactor = 0.4f;
    efficiencyFactor = 0.5f;
    equalityCheckInstance = EqualityCheck();
    hashFunctionInstance = HashFunction();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::HashMap(const SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>& x){
    loadFactor = x.loadFactor;
    efficiencyFactor = x.efficiencyFactor;
    equalityCheckInstance = x.equalityCheckInstance;
    hashFunctionInstance = x.hashFunctionInstance;
    activeLength = x.activeLength;
    memoryUsedLength = x.memoryUsedLength;
    memoryTotalLength = x.memoryTotalLength;
    if(x.data == nullptr){data = nullptr;}
    else{
        data = new HashMapSlot<Key, Value, EqualityCheck, HashFunction>[x.memoryTotalLength];
        for(int i=0; i<x.memoryTotalLength; i++){
            if((*(x.data + i)).status == SGEXTN::Containers::HashMapSlotStatus::Active){
                rehash((*(x.data + i)).key, (*(x.data + i)).value, true);
                memoryUsedLength++;
            }
        }
    }
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::operator=(const SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>& x){
    if(this == &x){return (*this);}
    delete[] data;
    loadFactor = x.loadFactor;
    efficiencyFactor = x.efficiencyFactor;
    equalityCheckInstance = x.equalityCheckInstance;
    hashFunctionInstance = x.hashFunctionInstance;
    activeLength = x.activeLength;
    memoryUsedLength = x.memoryUsedLength;
    memoryTotalLength = x.memoryTotalLength;
    if(x.data == nullptr){data = nullptr;}
    else{
        data = new HashMapSlot<Key, Value, EqualityCheck, HashFunction>[x.memoryTotalLength];
        for(int i=0; i<x.memoryTotalLength; i++){
            if((*(x.data + i)).status == SGEXTN::Containers::HashMapSlotStatus::Active){
                rehash((*(x.data + i)).key, (*(x.data + i)).value, true);
                memoryUsedLength++;
            }
        }
    }
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::HashMap(SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>&& x) noexcept {
    data = x.data;
    loadFactor = x.loadFactor;
    efficiencyFactor = x.efficiencyFactor;
    equalityCheckInstance = x.equalityCheckInstance;
    hashFunctionInstance = x.hashFunctionInstance;
    activeLength = x.activeLength;
    memoryUsedLength = x.memoryUsedLength;
    memoryTotalLength = x.memoryTotalLength;
    x.data = nullptr;
    x.activeLength = 0;
    x.memoryUsedLength = 0;
    x.memoryTotalLength = 0;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::operator=(SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>&& x) noexcept {
    delete[] data;
    data = x.data;
    loadFactor = x.loadFactor;
    efficiencyFactor = x.efficiencyFactor;
    equalityCheckInstance = x.equalityCheckInstance;
    hashFunctionInstance = x.hashFunctionInstance;
    activeLength = x.activeLength;
    memoryUsedLength = x.memoryUsedLength;
    memoryTotalLength = x.memoryTotalLength;
    x.data = nullptr;
    x.activeLength = 0;
    x.memoryUsedLength = 0;
    x.memoryTotalLength = 0;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::~HashMap(){
    delete[] data;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::getHashIndex(const Key& x) const {
    int hash = hashFunctionInstance(x) % memoryTotalLength;
    if(hash < 0){hash += memoryTotalLength;}
    return hash;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::rehash(const Key& key, const Value& value, bool allowDuplicate){
    int hash = getHashIndex(key);
    while(true){
        if(hash == memoryTotalLength){hash = 0;}
        if(allowDuplicate == false && (*(data + hash)).status == SGEXTN::Containers::HashMapSlotStatus::Active && equalityCheckInstance((*(data + hash)).key, key) == true){return false;}
        if((*(data + hash)).status != SGEXTN::Containers::HashMapSlotStatus::Active){
            (*(data + hash)).key = key;
            (*(data + hash)).value = value;
            (*(data + hash)).status = SGEXTN::Containers::HashMapSlotStatus::Active;
            return true;
        }
        hash++;
    }
    return true;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::rehashAll(int newMemoryLength){
    SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* oldPointer = data;
    int oldMemoryLength = memoryTotalLength;
    memoryTotalLength = newMemoryLength;
    data = new SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>[newMemoryLength];
    memoryUsedLength = 0;
    for(int i=0; i<oldMemoryLength; i++){
        if((*(oldPointer + i)).status == SGEXTN::Containers::HashMapSlotStatus::Active){
            rehash((*(oldPointer + i)).key, (*(oldPointer + i)).value, true);
            memoryUsedLength++;
        }
    }
    delete[] oldPointer;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::length() const {
    return activeLength;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryTotalLength){return;}
    rehashAll(newMemoryLength);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::insert(const Key& key, const Value& value, bool allowDuplicate){
    if(memoryTotalLength == 0 || static_cast<float>(memoryUsedLength) / static_cast<float>(memoryTotalLength) >= loadFactor){rehashAll(3 * memoryTotalLength + 3);}
    if(memoryUsedLength > 0 && static_cast<float>(memoryUsedLength - activeLength) / static_cast<float>(memoryUsedLength) >= efficiencyFactor){rehashAll(memoryTotalLength);}
    bool result = rehash(key, value, allowDuplicate);
    if(result == true){
        memoryUsedLength++;
        activeLength++;
    }
    return result;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::erase(const Key& x){
    HashMapIterator i = find(x);
    return erase(i);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::contains(const Key& x) const {
    return (constFind(x) != constEnd());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::count(const Key& x) const {
    if(memoryTotalLength == 0){return 0;}
    int hash = getHashIndex(x);
    int count = 0;
    while(true){
        if(hash == memoryTotalLength){hash = 0;}
        if((*(data + hash)).status == SGEXTN::Containers::HashMapSlotStatus::Active && equalityCheckInstance((*(data + hash)).key, x) == true){count++;}
        if((*(data + hash)).status == SGEXTN::Containers::HashMapSlotStatus::Unused){break;}
        hash++;
    }
    return count;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::at(const Key& x){
    return find(x).value();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::at(const Key& x) const {
    return constFind(x).value();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::begin(){
    return (++end());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::constBegin() const {
    return (++constEnd());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::end(){
    return SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>(nullptr, this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::constEnd() const {
    return SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>(nullptr, this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::erase(SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& i){
    if(i.associatedSlot == nullptr || (*i.associatedSlot).status != SGEXTN::Containers::HashMapSlotStatus::Active){return false;}
    (*i.associatedSlot).status = SGEXTN::Containers::HashMapSlotStatus::Deleted;
    activeLength--;
    return true;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::getSlotFromKey(const Key& x) const {
    if(memoryTotalLength == 0){return nullptr;}
    int hash = getHashIndex(x);
    while(true){
        if(hash == memoryTotalLength){hash = 0;}
        if((*(data + hash)).status == SGEXTN::Containers::HashMapSlotStatus::Active && equalityCheckInstance((*(data + hash)).key, x) == true){return (data + hash);}
        if((*(data + hash)).status == SGEXTN::Containers::HashMapSlotStatus::Unused){return nullptr;}
        hash++;
    }
    return nullptr;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::find(const Key& x){
    return SGEXTN::Containers::HashMapIterator(getSlotFromKey(x), this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::constFind(const Key& x) const {
    return SGEXTN::Containers::HashMapConstIterator(getSlotFromKey(x), this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::HashMapIterator(SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slot, SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>* map){
    associatedSlot = slot;
    associatedMap = map;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::HashMapConstIterator(SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slot, const SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>* map){
    associatedSlot = slot;
    associatedMap = map;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::getPreviousSlot(SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* x) const {
    if(memoryTotalLength == 0){return nullptr;}
    int offset = memoryTotalLength;
    if(x != nullptr){offset = x - data;}
    while(true){
        offset--;
        if(offset == -1){return nullptr;}
        if((*(data + offset)).status == SGEXTN::Containers::HashMapSlotStatus::Active){return (data + offset);}
    }
    return nullptr;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::getNextSlot(SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* x) const {
    if(memoryTotalLength == 0){return nullptr;}
    int offset = -1;
    if(x != nullptr){offset = x - data;}
    while(true){
        offset++;
        if(offset == memoryTotalLength){return nullptr;}
        if((*(data + offset)).status == SGEXTN::Containers::HashMapSlotStatus::Active){return (data + offset);}
    }
    return nullptr;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    associatedSlot = (*associatedMap).getNextSlot(associatedSlot);
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::HashMapIterator prev = (*this);
    associatedSlot = (*associatedMap).getNextSlot(associatedSlot);
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    associatedSlot = (*associatedMap).getPreviousSlot(associatedSlot);
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::HashMapIterator prev = (*this);
    associatedSlot = (*associatedMap).getPreviousSlot(associatedSlot);
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (associatedSlot == x.associatedSlot && associatedMap == x.associatedMap);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (associatedSlot != x.associatedSlot || associatedMap != x.associatedMap);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::key(){
    return (*associatedSlot).key;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::value(){
    return (*associatedSlot).value;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    associatedSlot = (*associatedMap).getNextSlot(associatedSlot);
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::HashMapConstIterator prev = (*this);
    associatedSlot = (*associatedMap).getNextSlot(associatedSlot);
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    associatedSlot = (*associatedMap).getPreviousSlot(associatedSlot);
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::HashMapConstIterator prev = (*this);
    associatedSlot = (*associatedMap).getPreviousSlot(associatedSlot);
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (associatedSlot == x.associatedSlot && associatedMap == x.associatedMap);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (associatedSlot != x.associatedSlot || associatedMap != x.associatedMap);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::key(){
    return (*associatedSlot).key;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::value(){
    return (*associatedSlot).value;
}
