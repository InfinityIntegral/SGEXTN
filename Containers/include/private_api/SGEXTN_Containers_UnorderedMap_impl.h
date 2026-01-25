#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::UnorderedMap(){
    private_hashMap = SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::length() const {
    return private_hashMap.length();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    private_hashMap.reserve(newMemoryLength);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::insert(const Key& key, const Value& value){
    return private_hashMap.insert(key, value, false);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::erase(const Key& x){
    return private_hashMap.erase(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::contains(const Key& x) const {
    return private_hashMap.contains(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::at(const Key& x){
    if(contains(x) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMap::at crashed because the provided key is not in the map");}
    return private_hashMap.at(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::at(const Key& x) const {
    if(contains(x) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMap::at crashed because the provided key is not in the map");}
    return private_hashMap.at(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::begin(){
    return SGEXTN::Containers::UnorderedMapIterator(private_hashMap.begin());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::begin() const {
    return SGEXTN::Containers::UnorderedMapConstIterator(private_hashMap.begin());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::end(){
    return SGEXTN::Containers::UnorderedMapIterator(private_hashMap.end());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::end() const {
    return SGEXTN::Containers::UnorderedMapConstIterator(private_hashMap.end());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::erase(SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& i){
    return private_hashMap.erase(i.private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::find(const Key& x){
    return SGEXTN::Containers::UnorderedMapIterator(private_hashMap.find(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMap<Key, Value, EqualityCheck, HashFunction>::find(const Key& x) const {
    return SGEXTN::Containers::UnorderedMapConstIterator(private_hashMap.find(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::UnorderedMapIterator(SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> i){
    private_hashMapIterator = i;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    private_hashMapIterator++;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedMapIterator prev = (*this);
    private_hashMapIterator++;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    private_hashMapIterator--;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedMapIterator prev = (*this);
    private_hashMapIterator--;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (private_hashMapIterator == private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (private_hashMapIterator != private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::key(){
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMapIterator::key crashed because the iterator is the end iterator");}
    return private_hashMapIterator.key();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::value(){
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMapIterator::value crashed because the iterator is the end iterator");}
    return private_hashMapIterator.value();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::UnorderedMapConstIterator(SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> i){
    private_hashMapIterator = i;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    private_hashMapIterator++;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedMapConstIterator prev = (*this);
    private_hashMapIterator++;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    private_hashMapIterator--;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedMapConstIterator prev = (*this);
    private_hashMapIterator--;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (private_hashMapIterator == private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (private_hashMapIterator != private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::key(){
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMapConstIterator::key crashed because the iterator is the end iterator");}
    return private_hashMapIterator.key();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::value(){
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMapConstIterator::value crashed because the iterator is the end iterator");}
    return private_hashMapIterator.value();
}
