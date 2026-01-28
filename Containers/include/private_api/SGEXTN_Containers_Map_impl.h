#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::Map(){
    private_avlTree = SGEXTN::Containers::AVLTree<Key, Value, Comparator>();
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::Map<Key, Value, Comparator>::length() const {
    return private_avlTree.length();
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::Map<Key, Value, Comparator>::insert(const Key& key, const Value& value){
    return private_avlTree.insert(key, value, false);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::Map<Key, Value, Comparator>::erase(const Key& x){
    return private_avlTree.erase(x);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::Map<Key, Value, Comparator>::contains(const Key& x) const {
    return private_avlTree.contains(x);
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::Map<Key, Value, Comparator>::at(const Key& x){
    if(contains(x) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Map::at crashed because the key is not in the map");}
    return private_avlTree.at(x);
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::Map<Key, Value, Comparator>::at(const Key& x) const {
    if(contains(x) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Map::at crashed because the key is not in the map");}
    return private_avlTree.at(x);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::begin(){
    return SGEXTN::Containers::MapIterator(private_avlTree.begin());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::constBegin() const {
    return SGEXTN::Containers::MapConstIterator(private_avlTree.constBegin());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::end(){
    return SGEXTN::Containers::MapIterator(private_avlTree.end());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::constEnd() const {
    return SGEXTN::Containers::MapConstIterator(private_avlTree.constEnd());
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::Map<Key, Value, Comparator>::erase(SGEXTN::Containers::MapIterator<Key, Value, Comparator>& i){
    return private_avlTree.erase(i.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::find(const Key& x){
    return SGEXTN::Containers::MapIterator(private_avlTree.find(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::constFind(const Key& x) const {
    return SGEXTN::Containers::MapConstIterator(private_avlTree.constFind(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::lowerBound(const Key& x){
    return SGEXTN::Containers::MapIterator(private_avlTree.lowerBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::constLowerBound(const Key& x) const {
    return SGEXTN::Containers::MapConstIterator(private_avlTree.constLowerBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::upperBound(const Key& x){
    return SGEXTN::Containers::MapIterator(private_avlTree.upperBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::constUpperBound(const Key& x) const {
    return SGEXTN::Containers::MapConstIterator(private_avlTree.constUpperBound(x));
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::Map<Key, Value, Comparator>::indexOf(const Key& x) const {
    return private_avlTree.indexOf(x);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::Map<Key, Value, Comparator>::indexOf(SGEXTN::Containers::MapIterator<Key, Value, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::Map<Key, Value, Comparator>::indexOf(SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::Map<Key, Value, Comparator>::keyAt(int n) const {
    if(n < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Map::keyAt crashed because index is negative");}
    if(n >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Map::keyAt crashed because index points beyond the end of the data structure");}
    return private_avlTree.keyAt(n);
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::Map<Key, Value, Comparator>::valueAt(int n){
    if(n < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Map::valueAt crashed because index is negative");}
    if(n >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Map::valueAt crashed because index points beyond the end of the data structure");}
    return private_avlTree.valueAt(n);
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::Map<Key, Value, Comparator>::valueAt(int n) const {
    if(n < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Map::valueAt crashed because index is negative");}
    if(n >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Map::valueAt crashed because index points beyond the end of the data structure");}
    return private_avlTree.valueAt(n);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::MapIterator(private_avlTree.iteratorAt(n));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> SGEXTN::Containers::Map<Key, Value, Comparator>::constIteratorAt(int n) const {
    return SGEXTN::Containers::MapConstIterator(private_avlTree.constIteratorAt(n));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator>::MapIterator(SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> i){
    private_avlTreeIterator = i;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator>& SGEXTN::Containers::MapIterator<Key, Value, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator>::operator++(int){
    SGEXTN::Containers::MapIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator>& SGEXTN::Containers::MapIterator<Key, Value, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator> SGEXTN::Containers::MapIterator<Key, Value, Comparator>::operator--(int){
    SGEXTN::Containers::MapIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MapIterator<Key, Value, Comparator>::operator==(const SGEXTN::Containers::MapIterator<Key, Value, Comparator>& x){
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MapIterator<Key, Value, Comparator>::operator!=(const SGEXTN::Containers::MapIterator<Key, Value, Comparator>& x){
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::MapIterator<Key, Value, Comparator>::key(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MapIterator::key crashed because the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::MapIterator<Key, Value, Comparator>::value(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MapIterator::value crashed because the iterator is the end iterator");}
    return private_avlTreeIterator.value();
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::MapConstIterator(SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> i){
    private_avlTreeIterator = i;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>& SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::operator++(int){
    SGEXTN::Containers::MapConstIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>& SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::operator--(int){
    SGEXTN::Containers::MapConstIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::operator==(const SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>& x){
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::operator!=(const SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>& x){
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::key(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MapConstIterator::key crashed because the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::MapConstIterator<Key, Value, Comparator>::value(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MapConstIterator::value crashed because the iterator is the end iterator");}
    return private_avlTreeIterator.value();
}
