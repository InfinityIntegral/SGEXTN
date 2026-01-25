#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::UnorderedMultiMap(){
    private_hashMap = SGEXTN::Containers::HashMap<Key, Value, EqualityCheck, HashFunction>();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::length() const {
    return private_hashMap.length();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    private_hashMap.reserve(newMemoryLength);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::insert(const Key& key, const Value& value){
    return private_hashMap.insert(key, value, true);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::erase(const Key& x){
    return private_hashMap.erase(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::contains(const Key& x) const {
    return private_hashMap.contains(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::count(const Key& x) const {
    return private_hashMap.count(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::at(const Key& x){
    if(contains(x) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMultiMap::at crashed because the provided key is not in the map");}
    return private_hashMap.at(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::at(const Key& x) const {
    if(contains(x) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMultiMap::at crashed because the provided key is not in the map");}
    return private_hashMap.at(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::begin(){
    return SGEXTN::Containers::UnorderedMultiMapIterator(private_hashMap.begin());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::begin() const {
    return SGEXTN::Containers::UnorderedMultiMapConstIterator(private_hashMap.begin());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::end(){
    return SGEXTN::Containers::UnorderedMultiMapIterator(private_hashMap.end());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::end() const {
    return SGEXTN::Containers::UnorderedMultiMapConstIterator(private_hashMap.end());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::erase(SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>& i){
    return private_hashMap.erase(i.private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::find(const Key& x){
    return SGEXTN::Containers::UnorderedMultiMapIterator(private_hashMap.find(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::find(const Key& x) const {
    return SGEXTN::Containers::UnorderedMultiMapConstIterator(private_hashMap.find(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::equalRangeBegin(const Key& x){
    return SGEXTN::Containers::UnorderedMultiMapIterator(private_hashMap.find(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::equalRangeBegin(const Key& x) const {
    return SGEXTN::Containers::UnorderedMultiMapConstIterator(private_hashMap.find(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::equalRangeEnd(const Key& x){
    return SGEXTN::Containers::UnorderedMultiMapIterator(private_hashMap.findLast(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMap<Key, Value, EqualityCheck, HashFunction>::equalRangeEnd(const Key& x) const {
    return SGEXTN::Containers::UnorderedMultiMapConstIterator(private_hashMap.findLast(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::UnorderedMultiMapIterator(SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> i){
    private_hashMapIterator = i;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    private_hashMapIterator++;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedMultiMapIterator prev = (*this);
    private_hashMapIterator++;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    private_hashMapIterator--;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedMultiMapIterator prev = (*this);
    private_hashMapIterator--;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (private_hashMapIterator == x.private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (private_hashMapIterator != x.private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::key(){
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMultiMapIterator::key crashed because the iterator is the end iterator");}
    return private_hashMapIterator.key();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>::value(){
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMultiMapIterator::value crashed because the iterator is the end iterator");}
    return private_hashMapIterator.value();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::UnorderedMultiMapConstIterator(SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> i){
    private_hashMapIterator = i;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    private_hashMapIterator++;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedMultiMapConstIterator prev = (*this);
    private_hashMapIterator++;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    private_hashMapIterator--;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedMultiMapConstIterator prev = (*this);
    private_hashMapIterator--;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (private_hashMapIterator == x.private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x){
    return (private_hashMapIterator != x.private_hashMapIterator);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::key(){
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMultiMapConstIterator::key crashed because the iterator is the end iterator");}
    return private_hashMapIterator.key();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction>::value(){
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::UnorderedMultiMapConstIterator::value crashed because the iterator is the end iterator");}
    return private_hashMapIterator.value();
}
