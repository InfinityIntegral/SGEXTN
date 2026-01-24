#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T, typename Comparator> SGEXTN::Containers::Set<T, Comparator>::Set(){
    private_avlTree = SGEXTN::Containers::AVLTree<T, bool, Comparator>();
}

template <typename T, typename Comparator> int SGEXTN::Containers::Set<T, Comparator>::length() const {
    return private_avlTree.length();
}

template <typename T, typename Comparator> bool SGEXTN::Containers::Set<T, Comparator>::insert(const T& x){
    return private_avlTree.insert(x, false, false);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::Set<T, Comparator>::erase(const T& x){
    return private_avlTree.erase(x);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::Set<T, Comparator>::contains(const T& x) const {
    return private_avlTree.contains(x);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::begin(){
    return SGEXTN::Containers::SetIterator(private_avlTree.begin());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::begin() const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.begin());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::end(){
    return SGEXTN::Containers::SetIterator(private_avlTree.end());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::end() const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.end());
}

template <typename T, typename Comparator> bool SGEXTN::Containers::Set<T, Comparator>::erase(SGEXTN::Containers::SetIterator<T, Comparator>& i){
    return private_avlTree.erase(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::find(const T& x){
    return SGEXTN::Containers::SetIterator(private_avlTree.find(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::find(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.find(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::lowerBound(const T& x){
    return SGEXTN::Containers::SetIterator(private_avlTree.lowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::lowerBound(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.lowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::upperBound(const T& x){
    return SGEXTN::Containers::SetIterator(private_avlTree.upperBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::upperBound(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.upperBound(x));
}

template <typename T, typename Comparator> int SGEXTN::Containers::Set<T, Comparator>::indexOf(const T& x) const {
    return private_avlTree.indexOf(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::Set<T, Comparator>::indexOf(SGEXTN::Containers::SetIterator<T, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> int SGEXTN::Containers::Set<T, Comparator>::indexOf(SGEXTN::Containers::SetConstIterator<T, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::Set<T, Comparator>::elementAt(int n) const {
    if(n < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set::elementAt crashed because the index is negative");}
    if(n >= length()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set::elementAt crashed because the index points beyond the end of the set");}
    return private_avlTree.keyAt(n);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::SetIterator(private_avlTree.iteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::iteratorAt(int n) const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.iteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::SetIterator(AVLTreeIterator<T, bool, Comparator> i){
    private_avlTreeIterator = i;
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>& SGEXTN::Containers::SetIterator<T, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::operator++(int){
    SetIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>& SGEXTN::Containers::SetIterator<T, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::operator--(int){
    SetIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetIterator<T, Comparator>::operator==(const SGEXTN::Containers::SetIterator<T, Comparator>& x){
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetIterator<T, Comparator>::operator!=(const SGEXTN::Containers::SetIterator<T, Comparator>& x){
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::SetIterator<T, Comparator>::operator*(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::SetIterator::operator* crashed as the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::SetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i){
    private_avlTreeIterator = i;
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::operator++(int){
    SGEXTN::Containers::SetConstIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::operator--(int){
    SGEXTN::Containers::SetConstIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetConstIterator<T, Comparator>::operator==(const SGEXTN::Containers::SetConstIterator<T, Comparator>& x){
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetConstIterator<T, Comparator>::operator!=(const SGEXTN::Containers::SetConstIterator<T, Comparator>& x){
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator*(){
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::SetConstIterator::operator* crashed as the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}
