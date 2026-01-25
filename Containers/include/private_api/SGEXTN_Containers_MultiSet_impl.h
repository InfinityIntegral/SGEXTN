#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T, typename Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::MultiSet(){
    private_avlTree = SGEXTN::Containers::AVLTree<T, bool, Comparator>();
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::length() const {
    return private_avlTree.length();
}

template <typename T, typename Comparator> void SGEXTN::Containers::MultiSet<T, Comparator>::insert(const T& x){
    private_avlTree.insert(x, false, true);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSet<T, Comparator>::erase(const T& x){
    return private_avlTree.erase(x);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSet<T, Comparator>::contains(const T& x) const {
    return private_avlTree.contains(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::count(const T& x) const {
    return private_avlTree.count(x);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::begin(){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.begin());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constBegin() const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.begin());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::end(){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.end());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constEnd() const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.end());
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSet<T, Comparator>::erase(SGEXTN::Containers::MultiSetIterator<T, Comparator>& i){
    return private_avlTree.erase(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::find(const T& x){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.find(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constFind(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.find(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::lowerBound(const T& x){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.lowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constLowerBound(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.lowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::upperBound(const T& x){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.upperBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constUpperBound(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.upperBound(x));
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::indexOf(const T& x) const {
    return private_avlTree.indexOf(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::indexOf(SGEXTN::Containers::MultiSetIterator<T, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::indexOf(SGEXTN::Containers::MultiSetConstIterator<T, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSet<T, Comparator>::elementAt(int n) const {
    if(n < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiSet::elementAt crashed because the index is negative");}
    if(n >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiSet::elementAt crashed because the index points beyond the end of the set");}
    return private_avlTree.keyAt(n);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.iteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constIteratorAt(int n) const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.iteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::MultiSetIterator(AVLTreeIterator<T, bool, Comparator> i){
    private_avlTreeIterator = i;
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator++(int){
    MultiSetIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator--(int){
    MultiSetIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator==(const SGEXTN::Containers::MultiSetIterator<T, Comparator>& x){
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator!=(const SGEXTN::Containers::MultiSetIterator<T, Comparator>& x){
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator*(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiSetIterator::operator* crashed as the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::MultiSetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i){
    private_avlTreeIterator = i;
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator++(int){
    SGEXTN::Containers::MultiSetConstIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator--(int){
    SGEXTN::Containers::MultiSetConstIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator==(const SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& x){
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator!=(const SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& x){
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator*(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MultiSetConstIterator::operator* crashed as the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}
