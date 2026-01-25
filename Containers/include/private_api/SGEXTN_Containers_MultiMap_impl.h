#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>
#include <private_api/SGEXTN_Containers_MultiMap_impl.h>

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::MultiMap(){
    private_avlTree = SGEXTN::Containers::AVLTree<Key, Value, Comparator>();
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMap<Key, Value, Comparator>::length() const {
    return private_avlTree.length();
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::MultiMap<Key, Value, Comparator>::insert(const Key& key, const Value& value){
    private_avlTree.insert(key, value, true);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMap<Key, Value, Comparator>::erase(const Key& x){
    return private_avlTree.erase(x);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMap<Key, Value, Comparator>::contains(const Key& x) const {
    return private_avlTree.contains(x);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMap<Key, Value, Comparator>::count(const Key& x) const {
    return private_avlTree.count(x);
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::MultiMap<Key, Value, Comparator>::at(const Key& x){
    if(contains(x) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMap::at crashed because the key is not in the map");}
    return private_avlTree.at(x);
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::MultiMap<Key, Value, Comparator>::at(const Key& x) const {
    if(contains(x) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMap::at crashed because the key is not in the map");}
    return private_avlTree.at(x);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::begin(){
    return SGEXTN::Containers::MultiMapIterator(private_avlTree.begin());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::constBegin() const {
    return SGEXTN::Containers::MultiMapConstIterator(private_avlTree.begin());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::end(){
    return SGEXTN::Containers::MultiMapIterator(private_avlTree.end());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::constEnd() const {
    return SGEXTN::Containers::MultiMapConstIterator(private_avlTree.end());
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMap<Key, Value, Comparator>::erase(SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& i){
    return private_avlTree.erase(i.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::find(const Key& x){
    return SGEXTN::Containers::MultiMapIterator(private_avlTree.find(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::constFind(const Key& x) const {
    return SGEXTN::Containers::MultiMapConstIterator(private_avlTree.find(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::lowerBound(const Key& x){
    return SGEXTN::Containers::MultiMapIterator(private_avlTree.lowerBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::constLowerBound(const Key& x) const {
    return SGEXTN::Containers::MultiMapConstIterator(private_avlTree.lowerBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::upperBound(const Key& x){
    return SGEXTN::Containers::MultiMapIterator(private_avlTree.upperBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::constUpperBound(const Key& x) const {
    return SGEXTN::Containers::MultiMapConstIterator(private_avlTree.upperBound(x));
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMap<Key, Value, Comparator>::indexOf(const Key& x) const {
    return private_avlTree.indexOf(x);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMap<Key, Value, Comparator>::indexOf(SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMap<Key, Value, Comparator>::indexOf(SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::MultiMap<Key, Value, Comparator>::keyAt(int n) const {
    if(n < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMap::keyAt crashed because index is negative");}
    if(n >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMap::keyAt crashed because index points beyond the end of the data structure");}
    return private_avlTree.keyAt(n);
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::MultiMap<Key, Value, Comparator>::valueAt(int n){
    if(n < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMap::valueAt crashed because index is negative");}
    if(n >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMap::valueAt crashed because index points beyond the end of the data structure");}
    return private_avlTree.valueAt(n);
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::MultiMap<Key, Value, Comparator>::valueAt(int n) const {
    if(n < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMap::valueAt crashed because index is negative");}
    if(n >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMap::valueAt crashed because index points beyond the end of the data structure");}
    return private_avlTree.valueAt(n);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::MultiMapIterator(private_avlTree.iteratorAt(n));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMap<Key, Value, Comparator>::constIteratorAt(int n) const {
    return SGEXTN::Containers::MultiMapConstIterator(private_avlTree.iteratorAt(n));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::MultiMapIterator(SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> i){
    private_avlTreeIterator = i;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator++(int){
    SGEXTN::Containers::MultiMapIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator--(int){
    SGEXTN::Containers::MultiMapIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator==(const SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& x){
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator!=(const SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& x){
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::key(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMapIterator::key crashed because the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::value(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMapIterator::value crashed because the iterator is the end iterator");}
    return private_avlTreeIterator.value();
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::MultiMapConstIterator(SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> i){
    private_avlTreeIterator = i;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>& SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator++(int){
    SGEXTN::Containers::MultiMapConstIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>& SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator--(int){
    SGEXTN::Containers::MultiMapConstIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator==(const SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>& x){
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator!=(const SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>& x){
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::key(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMapConstIterator::key crashed because the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::value(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiMapConstIterator::value crashed because the iterator is the end iterator");}
    return private_avlTreeIterator.value();
}
