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
#include <SGEXTN/Containers/PlacementNew.h>

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>::HashMapSlot() : status_(HashMapSlotStatus::Unused), keyConstructorRemover_(static_cast<unsigned char>(0)), valueConstructorRemover_(static_cast<unsigned char>(0)) {}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>::~HashMapSlot(){}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::HashMap() : data_(nullptr), activeLength_(0), memoryUsedLength_(0), memoryTotalLength_(0), loadFactor_(0.4f), efficiencyFactor_(0.5f), equalityCheckInstance_(), hashFunctionInstance_() {}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::HashMap(const SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>& x) : loadFactor_(x.loadFactor_), efficiencyFactor_(x.efficiencyFactor_), equalityCheckInstance_(x.equalityCheckInstance_), hashFunctionInstance_(x.hashFunctionInstance_), activeLength_(x.activeLength_), memoryUsedLength_(0), memoryTotalLength_(x.memoryTotalLength_), data_(nullptr){
    if(x.data_ != nullptr){
        data_ = new HashMapSlot<Key, Value, EqualityCheck, HashFunction>[x.memoryTotalLength_];
        for(int i=0; i<x.memoryTotalLength_; i++){
            if((*(x.data_ + i)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){
                hashInto((*(x.data_ + i)).keyObject_, (*(x.data_ + i)).valueObject_);
            }
        }
    }
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::operator=(const SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>& x){
    if(this == &x){return (*this);}
    for(int i=0; i<memoryTotalLength_; i++){
        if((*(data_ + i)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){
            (*(data_ + i)).keyObject_.~Key();
            (*(data_ + i)).valueObject_.~Value();
        }
    }
    delete[] data_;
    loadFactor_ = x.loadFactor_;
    efficiencyFactor_ = x.efficiencyFactor_;
    equalityCheckInstance_ = x.equalityCheckInstance_;
    hashFunctionInstance_ = x.hashFunctionInstance_;
    activeLength_ = x.activeLength_;
    memoryUsedLength_ = 0;
    memoryTotalLength_ = x.memoryTotalLength_;
    if(x.data_ == nullptr){data_ = nullptr;}
    else{
        data_ = new HashMapSlot<Key, Value, EqualityCheck, HashFunction>[x.memoryTotalLength_];
        for(int i=0; i<x.memoryTotalLength_; i++){
            if((*(x.data_ + i)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){
                hashInto((*(x.data_ + i)).keyObject_, (*(x.data_ + i)).valueObject_);
            }
        }
    }
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::HashMap(SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>&& x) noexcept : data_(x.data_), loadFactor_(x.loadFactor_), efficiencyFactor_(x.efficiencyFactor_), equalityCheckInstance_(static_cast<EqualityCheck&&>(x.equalityCheckInstance_)), hashFunctionInstance_(static_cast<HashFunction&&>(x.hashFunctionInstance_)), activeLength_(x.activeLength_), memoryUsedLength_(x.memoryUsedLength_), memoryTotalLength_(x.memoryTotalLength_) {
    x.data_ = nullptr;
    x.activeLength_ = 0;
    x.memoryUsedLength_ = 0;
    x.memoryTotalLength_ = 0;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::operator=(SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>&& x) noexcept {
    if(this == &x){return (*this);}
    for(int i=0; i<memoryTotalLength_; i++){
        if((*(data_ + i)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){
            (*(data_ + i)).keyObject_.~Key();
            (*(data_ + i)).valueObject_.~Value();
        }
    }
    delete[] data_;
    data_ = x.data_;
    loadFactor_ = x.loadFactor_;
    efficiencyFactor_ = x.efficiencyFactor_;
    equalityCheckInstance_ = static_cast<EqualityCheck&&>(x.equalityCheckInstance_);
    hashFunctionInstance_ = static_cast<HashFunction&&>(x.hashFunctionInstance_);
    activeLength_ = x.activeLength_;
    memoryUsedLength_ = x.memoryUsedLength_;
    memoryTotalLength_ = x.memoryTotalLength_;
    x.data_ = nullptr;
    x.activeLength_ = 0;
    x.memoryUsedLength_ = 0;
    x.memoryTotalLength_ = 0;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::~HashMap(){
    for(int i=0; i<memoryTotalLength_; i++){
        if((*(data_ + i)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){
            (*(data_ + i)).keyObject_.~Key();
            (*(data_ + i)).valueObject_.~Value();
        }
    }
    delete[] data_;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::getHashIndex(const Key& x) const {
    return (hashFunctionInstance_(x) & (memoryTotalLength_ - 1));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::hashInto(const Key& key, const Value& value){
    int hash = getHashIndex(key);
    while(true){
        if(hash == memoryTotalLength_){hash = 0;}
        if((*(data_ + hash)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active && equalityCheckInstance_((*(data_ + hash)).keyObject_, key) == true){return false;}
        if((*(data_ + hash)).status_ != SGEXTN::Containers::HashMapSlotStatus::Active){
            if((*(data_ + hash)).status_ == SGEXTN::Containers::HashMapSlotStatus::Unused){memoryUsedLength_++;}
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&(*(data_ + hash)).keyObject_)) Key(key);
            new (SGEXTN::Containers::PlacementNew::Placeholder, static_cast<void*>(&(*(data_ + hash)).valueObject_)) Value(value);
            (*(data_ + hash)).status_ = SGEXTN::Containers::HashMapSlotStatus::Active;
            return true;
        }
        hash++;
    }
    return true;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::rehashAll(int newMemoryLength){
    if(newMemoryLength < 16){newMemoryLength = 16;}
    else{
        int n = newMemoryLength - 1;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        newMemoryLength = n + 1;
    }
    const SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* oldPointer = data_;
    const int oldMemoryLength = memoryTotalLength_;
    memoryTotalLength_ = newMemoryLength;
    data_ = new SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>[newMemoryLength];
    memoryUsedLength_ = 0;
    for(int i=0; i<oldMemoryLength; i++){
        if((*(oldPointer + i)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){
            hashInto((*(oldPointer + i)).keyObject_, (*(oldPointer + i)).valueObject_);
            (*(oldPointer + i)).keyObject_.~Key();
            (*(oldPointer + i)).valueObject_.~Value();
        }
    }
    delete[] oldPointer;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::length() const {
    return activeLength_;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryTotalLength_){return;}
    rehashAll(newMemoryLength);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::insert(const Key& key, const Value& value){
    if(memoryTotalLength_ == 0 || static_cast<float>(memoryUsedLength_) / static_cast<float>(memoryTotalLength_) >= loadFactor_){rehashAll(3 * memoryTotalLength_ + 3);}
    if(memoryUsedLength_ > 0 && static_cast<float>(memoryUsedLength_ - activeLength_) / static_cast<float>(memoryUsedLength_) >= efficiencyFactor_){rehashAll(memoryTotalLength_);}
    const bool result = hashInto(key, value);
    if(result == true){activeLength_++;}
    return result;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::erase(const Key& x){
    HashMapIterator i = find(x);
    return erase(i);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::clear(){
    activeLength_ = 0;
    memoryUsedLength_ = 0;
    for(int i=0; i<memoryTotalLength_; i++){
        if((*(data_ + i)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){
            (*(data_ + i)).keyObject_.~Key();
            (*(data_ + i)).valueObject_.~Value();
        }
        (*(data_ + i)).status_ = SGEXTN::Containers::HashMapSlotStatus::Unused;
    }
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::contains(const Key& x) const {
    return (constFind(x) != constEnd());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::count(const Key& x) const {
    if(memoryTotalLength_ == 0){return 0;}
    int hash = getHashIndex(x);
    int count = 0;
    while(true){
        if(hash == memoryTotalLength_){hash = 0;}
        if((*(data_ + hash)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active && equalityCheckInstance_((*(data_ + hash)).keyObject_, x) == true){count++;}
        if((*(data_ + hash)).status_ == SGEXTN::Containers::HashMapSlotStatus::Unused){break;}
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
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slotToDelete = i.associatedSlot_;
    if(slotToDelete == nullptr || (*slotToDelete).status_ != SGEXTN::Containers::HashMapSlotStatus::Active){return false;}
    i--;
    (*slotToDelete).keyObject_.~Key();
    (*slotToDelete).valueObject_.~Value();
    (*slotToDelete).status_ = SGEXTN::Containers::HashMapSlotStatus::Deleted;
    activeLength_--;
    return true;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::getSlotFromKey(const Key& x) const {
    if(memoryTotalLength_ == 0){return nullptr;}
    int hash = getHashIndex(x);
    while(true){
        if(hash == memoryTotalLength_){hash = 0;}
        if((*(data_ + hash)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active && equalityCheckInstance_((*(data_ + hash)).keyObject_, x) == true){return (data_ + hash);}
        if((*(data_ + hash)).status_ == SGEXTN::Containers::HashMapSlotStatus::Unused){return nullptr;}
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

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::HashMapIterator(SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slot, SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>* map) : associatedSlot_(slot), associatedMap_(map) {}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::HashMapConstIterator(SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slot, const SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>* map) : associatedSlot_(slot), associatedMap_(map) {}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::getPreviousSlot(SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* x) const {
    if(memoryTotalLength_ == 0){return nullptr;}
    int offset = memoryTotalLength_;
    if(x != nullptr){offset = x - data_;}
    while(true){
        offset--;
        if(offset == -1){return nullptr;}
        if((*(data_ + offset)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){return (data_ + offset);}
    }
    return nullptr;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>::getNextSlot(SGEXTN::Containers::HashMapSlot<Key, Value, EqualityCheck, HashFunction>* x) const {
    if(memoryTotalLength_ == 0){return nullptr;}
    int offset = -1;
    if(x != nullptr){offset = x - data_;}
    while(true){
        offset++;
        if(offset == memoryTotalLength_){return nullptr;}
        if((*(data_ + offset)).status_ == SGEXTN::Containers::HashMapSlotStatus::Active){return (data_ + offset);}
    }
    return nullptr;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    associatedSlot_ = (*associatedMap_).getNextSlot(associatedSlot_);
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::HashMapIterator prev = (*this);
    associatedSlot_ = (*associatedMap_).getNextSlot(associatedSlot_);
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    associatedSlot_ = (*associatedMap_).getPreviousSlot(associatedSlot_);
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::HashMapIterator prev = (*this);
    associatedSlot_ = (*associatedMap_).getPreviousSlot(associatedSlot_);
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& x) const {
    return (associatedSlot_ == x.associatedSlot_ && associatedMap_ == x.associatedMap_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>& x) const {
    return (associatedSlot_ != x.associatedSlot_ || associatedMap_ != x.associatedMap_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::key() const {
    return (*associatedSlot_).keyObject_;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::value() const {
    return (*associatedSlot_).valueObject_;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction>::isEndIterator() const {
    return (associatedSlot_ == nullptr);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    associatedSlot_ = (*associatedMap_).getNextSlot(associatedSlot_);
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::HashMapConstIterator prev = (*this);
    associatedSlot_ = (*associatedMap_).getNextSlot(associatedSlot_);
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    associatedSlot_ = (*associatedMap_).getPreviousSlot(associatedSlot_);
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::HashMapConstIterator prev = (*this);
    associatedSlot_ = (*associatedMap_).getPreviousSlot(associatedSlot_);
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x) const {
    return (associatedSlot_ == x.associatedSlot_ && associatedMap_ == x.associatedMap_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x) const {
    return (associatedSlot_ != x.associatedSlot_ || associatedMap_ != x.associatedMap_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::key() const {
    return (*associatedSlot_).keyObject_;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::value() const {
    return (*associatedSlot_).valueObject_;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>::isEndIterator() const {
    return (associatedSlot_ == nullptr);
}
