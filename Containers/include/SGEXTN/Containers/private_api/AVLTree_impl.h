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

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::AVLTree() : root_(nullptr), comparatorInstance_() {}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>::AVLTreeNode(const Key& k, const Value& v, AVLTreeNode* parentNode) : key_(k), value_(v), parent_(parentNode), leftChild_(nullptr), rightChild_(nullptr), height_(0), subtreeSize_(1) {}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>::AVLTreeNode(AVLTreeNode* oldNode, AVLTreeNode* newParent) : key_((*oldNode).key_), value_((*oldNode).value_), height_((*oldNode).height_), subtreeSize_((*oldNode).subtreeSize_), parent_(newParent), leftChild_(nullptr), rightChild_(nullptr) {
    if((*oldNode).leftChild_ != nullptr){leftChild_ = new AVLTreeNode((*oldNode).leftChild_, this);}
    if((*oldNode).rightChild_ != nullptr){rightChild_ = new AVLTreeNode((*oldNode).rightChild_, this);}
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::AVLTree(const AVLTree& x) : root_(nullptr), comparatorInstance_(x.comparatorInstance_) {
    if(x.root_ != nullptr){root_ = new AVLTreeNode<Key, Value, Comparator>(x.root_, nullptr);}
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::recursiveDeleteAtRoot(){
    AVLTreeNode<Key, Value, Comparator>* current = root_;
    root_ = nullptr;
    while(current != nullptr){
        if((*current).leftChild_ != nullptr){
            AVLTreeNode<Key, Value, Comparator>* left = (*current).leftChild_;
            (*current).leftChild_ = (*left).rightChild_;
            (*left).rightChild_ = current;
            current = left;
        }
        else{
            AVLTreeNode<Key, Value, Comparator>* next = (*current).rightChild_;
            delete current;
            current = next;
        }
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::operator=(const AVLTree& x){
    if(this == &x){return (*this);}
    if(root_ != nullptr){recursiveDeleteAtRoot();}
    if(x.root_ != nullptr){root_ = new AVLTreeNode<Key, Value, Comparator>(x.root_, nullptr);}
    else{root_ = nullptr;}
    comparatorInstance_ = x.comparatorInstance_;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::AVLTree(AVLTree&& x) noexcept : root_(x.root_), comparatorInstance_(static_cast<Comparator&&>(x.comparatorInstance_)) {
    x.root_ = nullptr;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::operator=(AVLTree&& x) noexcept {
    if(this == &x){return (*this);}
    if(root_ != nullptr){recursiveDeleteAtRoot();}
    root_ = x.root_;
    x.root_ = nullptr;
    comparatorInstance_ = static_cast<Comparator&&>(x.comparatorInstance_);
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::~AVLTree(){
    if(root_ != nullptr){recursiveDeleteAtRoot();}
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::length() const {
    return getEffectiveSubtreeSize(root_);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getEffectiveHeight(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return -1;}
    return (*x).height_;
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getEffectiveSubtreeSize(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return 0;}
    return (*x).subtreeSize_;
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::heightLeftMinusRight(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return 0;}
    return (getEffectiveHeight((*x).leftChild_) - getEffectiveHeight((*x).rightChild_));
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::maximumOf2Ints(int a, int b) const {
    if(a >= b){return a;}
    return b;
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::updateHeightNoRecurse(AVLTreeNode<Key, Value, Comparator>* x){
    if(x == nullptr){return;}
    (*x).height_ = maximumOf2Ints(getEffectiveHeight((*x).leftChild_) + 1, getEffectiveHeight((*x).rightChild_) + 1);
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::updateSubtreeSizeNoRecurse(AVLTreeNode<Key, Value, Comparator>* x){
    if(x == nullptr){return;}
    (*x).subtreeSize_ = getEffectiveSubtreeSize((*x).leftChild_) + getEffectiveSubtreeSize((*x).rightChild_) + 1;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::leftRotate(AVLTreeNode<Key, Value, Comparator>* x){
    AVLTreeNode<Key, Value, Comparator>* y = (*x).rightChild_;
    AVLTreeNode<Key, Value, Comparator>* z = (*y).leftChild_;
    AVLTreeNode<Key, Value, Comparator>* p = (*x).parent_;
    (*y).leftChild_ = x;
    (*x).parent_ = y;
    (*x).rightChild_ = z;
    if(z != nullptr){(*z).parent_ = x;}
    updateHeightNoRecurse(x);
    updateSubtreeSizeNoRecurse(x);
    updateHeightNoRecurse(y);
    updateSubtreeSizeNoRecurse(y);
    if(p == nullptr){
        root_ = y;
        (*y).parent_ = nullptr;
    }
    else{
        if((*p).leftChild_ == x){(*p).leftChild_ = y;}
        else{(*p).rightChild_ = y;}
        (*y).parent_ = p;
        updateHeightNoRecurse(p);
        updateSubtreeSizeNoRecurse(p);
    }
    return y;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::rightRotate(AVLTreeNode<Key, Value, Comparator>* x){
    AVLTreeNode<Key, Value, Comparator>* y = (*x).leftChild_;
    AVLTreeNode<Key, Value, Comparator>* z = (*y).rightChild_;
    AVLTreeNode<Key, Value, Comparator>* p = (*x).parent_;
    (*y).rightChild_ = x;
    (*x).parent_ = y;
    (*x).leftChild_ = z;
    if(z != nullptr){(*z).parent_ = x;}
    updateHeightNoRecurse(x);
    updateSubtreeSizeNoRecurse(x);
    updateHeightNoRecurse(y);
    updateSubtreeSizeNoRecurse(y);
    if(p == nullptr){
        root_ = y;
        (*y).parent_ = nullptr;
    }
    else{
        if((*p).leftChild_ == x){(*p).leftChild_ = y;}
        else{(*p).rightChild_ = y;}
        (*y).parent_ = p;
        updateHeightNoRecurse(p);
        updateSubtreeSizeNoRecurse(p);
    }
    return y;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::rebalanceAtNode(AVLTreeNode<Key, Value, Comparator>* x){
    if(heightLeftMinusRight(x) > 1){
        if(heightLeftMinusRight((*x).leftChild_) >= 0){return rightRotate(x);}
        leftRotate((*x).leftChild_);
        return rightRotate(x);
    }
    if(heightLeftMinusRight(x) < -1){
        if(heightLeftMinusRight((*x).rightChild_) <= 0){return leftRotate(x);}
        rightRotate((*x).rightChild_);
        return leftRotate(x);
    }
    return x;
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::updateHeightRecurseToRoot(AVLTreeNode<Key, Value, Comparator>* x){
    if(x == nullptr){return;}
    while(true){
        updateHeightNoRecurse(x);
        updateSubtreeSizeNoRecurse(x);
        x = rebalanceAtNode(x);
        if(x == root_){break;}
        x = (*x).parent_;
    }
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTree<Key, Value, Comparator>::insert(const Key& key, const Value& value, bool allowDuplicate){
    AVLTreeNode<Key, Value, Comparator>* currentNode = root_;
    if(root_ == nullptr){
        root_ = new AVLTreeNode<Key, Value, Comparator>(key, value, nullptr);
        return true;
    }
    while(true){
        if(comparatorInstance_(key, (*currentNode).key_) == true){
            if((*currentNode).leftChild_ == nullptr){
                (*currentNode).leftChild_ = new AVLTreeNode(key, value, currentNode);
                currentNode = (*currentNode).leftChild_;
                break;
            }
            currentNode = (*currentNode).leftChild_;
        }
        else if(comparatorInstance_((*currentNode).key_, key) == true || allowDuplicate == true){
            if((*currentNode).rightChild_ == nullptr){
                (*currentNode).rightChild_ = new AVLTreeNode(key, value, currentNode);
                currentNode = (*currentNode).rightChild_;
                break;
            }
            currentNode = (*currentNode).rightChild_;
        }
        else{return false;}
    }
    updateHeightRecurseToRoot(currentNode);
    return true;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTree<Key, Value, Comparator>::erase(const Key& x){
    AVLTreeIterator i = find(x);
    return erase(i);
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::clear(){
    if(root_ != nullptr){recursiveDeleteAtRoot();}
    root_ = nullptr;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTree<Key, Value, Comparator>::contains(const Key& x) const {
    return (constFind(x) != constEnd());
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::count(const Key& x) const {
    const AVLTreeConstIterator i = constFind(x);
    if(i == constEnd()){return 0;}
    int count = 1;
    AVLTreeConstIterator currentNode = i;
    while(true){
        currentNode--;
        if(currentNode == constEnd()){break;}
        if(comparatorInstance_(currentNode.key(), x) == false && comparatorInstance_(x, currentNode.key()) == false){count++;}
        else{break;}
    }
    currentNode = i;
    while(true){
        currentNode++;
        if(currentNode == constEnd()){break;}
        if(comparatorInstance_(currentNode.key(), x) == false && comparatorInstance_(x, currentNode.key()) == false){count++;}
        else{break;}
    }
    return count;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::AVLTreeIterator(AVLTreeNode<Key, Value, Comparator>* node, AVLTree<Key, Value, Comparator>* tree) : associatedNode_(node), associatedTree_(tree) {}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::AVLTreeConstIterator(AVLTreeNode<Key, Value, Comparator>* node, const AVLTree<Key, Value, Comparator>* tree) : associatedNode_(node), associatedTree_(tree) {}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getLeftMostSubchild(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).leftChild_ == nullptr){return x;}
        x = (*x).leftChild_;
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getRightMostSubchild(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).rightChild_ == nullptr){return x;}
        x = (*x).rightChild_;
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getParentWithThisAsLeftChild(AVLTreeNode<Key, Value, Comparator>* x) const {
    while(true){
        if((*x).parent_ == nullptr){return nullptr;}
        if((*(*x).parent_).leftChild_ == x){return (*x).parent_;}
        x = (*x).parent_;
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getParentWithThisAsRightChild(AVLTreeNode<Key, Value, Comparator>* x) const {
    while(true){
        if((*x).parent_ == nullptr){return nullptr;}
        if((*(*x).parent_).rightChild_ == x){return (*x).parent_;}
        x = (*x).parent_;
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>& SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator++(){
    if(associatedNode_ == nullptr){associatedNode_ = (*associatedTree_).getLeftMostSubchild((*associatedTree_).root_);}
    else if((*associatedNode_).rightChild_ == nullptr){associatedNode_ = (*associatedTree_).getParentWithThisAsLeftChild(associatedNode_);}
    else{associatedNode_ = (*associatedTree_).getLeftMostSubchild((*associatedNode_).rightChild_);}
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>& SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator++(){
    if(associatedNode_ == nullptr){associatedNode_ = (*associatedTree_).getLeftMostSubchild((*associatedTree_).root_);}
    else if((*associatedNode_).rightChild_ == nullptr){associatedNode_ = (*associatedTree_).getParentWithThisAsLeftChild(associatedNode_);}
    else{associatedNode_ = (*associatedTree_).getLeftMostSubchild((*associatedNode_).rightChild_);}
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator++(int){
    AVLTreeIterator prev = (*this);
    if(associatedNode_ == nullptr){associatedNode_ = (*associatedTree_).getLeftMostSubchild((*associatedTree_).root_);}
    else if((*associatedNode_).rightChild_ == nullptr){associatedNode_ = (*associatedTree_).getParentWithThisAsLeftChild(associatedNode_);}
    else{associatedNode_ = (*associatedTree_).getLeftMostSubchild((*associatedNode_).rightChild_);}
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator++(int){
    AVLTreeConstIterator prev = (*this);
    if(associatedNode_ == nullptr){associatedNode_ = (*associatedTree_).getLeftMostSubchild((*associatedTree_).root_);}
    else if((*associatedNode_).rightChild_ == nullptr){associatedNode_ = (*associatedTree_).getParentWithThisAsLeftChild(associatedNode_);}
    else{associatedNode_ = (*associatedTree_).getLeftMostSubchild((*associatedNode_).rightChild_);}
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>& SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator--(){
    if(associatedNode_ == nullptr){associatedNode_ = (*associatedTree_).getRightMostSubchild((*associatedTree_).root_);}
    else if((*associatedNode_).leftChild_ == nullptr){associatedNode_ = (*associatedTree_).getParentWithThisAsRightChild(associatedNode_);}
    else{associatedNode_ = (*associatedTree_).getRightMostSubchild((*associatedNode_).leftChild_);}
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>& SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator--(){
    if(associatedNode_ == nullptr){associatedNode_ = (*associatedTree_).getRightMostSubchild((*associatedTree_).root_);}
    else if((*associatedNode_).leftChild_ == nullptr){associatedNode_ = (*associatedTree_).getParentWithThisAsRightChild(associatedNode_);}
    else{associatedNode_ = (*associatedTree_).getRightMostSubchild((*associatedNode_).leftChild_);}
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator--(int){
    AVLTreeIterator prev = (*this);
    if(associatedNode_ == nullptr){associatedNode_ = (*associatedTree_).getRightMostSubchild((*associatedTree_).root_);}
    else if((*associatedNode_).leftChild_ == nullptr){associatedNode_ = (*associatedTree_).getParentWithThisAsRightChild(associatedNode_);}
    else{associatedNode_ = (*associatedTree_).getRightMostSubchild((*associatedNode_).leftChild_);}
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator--(int){
    AVLTreeConstIterator prev = (*this);
    if(associatedNode_ == nullptr){associatedNode_ = (*associatedTree_).getRightMostSubchild((*associatedTree_).root_);}
    else if((*associatedNode_).leftChild_ == nullptr){associatedNode_ = (*associatedTree_).getParentWithThisAsRightChild(associatedNode_);}
    else{associatedNode_ = (*associatedTree_).getRightMostSubchild((*associatedNode_).leftChild_);}
    return prev;
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::key() const {
    return (*associatedNode_).key_;
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::key() const {
    return (*associatedNode_).key_;
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::value() const {
    return (*associatedNode_).value_;
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::value() const {
    return (*associatedNode_).value_;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator==(const AVLTreeIterator& x) const {
    return (associatedNode_ == x.associatedNode_ && associatedTree_ == x.associatedTree_);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator==(const AVLTreeConstIterator& x) const {
    return (associatedNode_ == x.associatedNode_ && associatedTree_ == x.associatedTree_);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator!=(const AVLTreeIterator& x) const {
    return (associatedNode_ != x.associatedNode_ || associatedTree_ != x.associatedTree_);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator!=(const AVLTreeConstIterator& x) const {
    return (associatedNode_ != x.associatedNode_ || associatedTree_ != x.associatedTree_);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::begin(){
    return AVLTreeIterator<Key, Value, Comparator>(getLeftMostSubchild(root_), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::constBegin() const {
    return AVLTreeConstIterator<Key, Value, Comparator>(getLeftMostSubchild(root_), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::end(){
    return AVLTreeIterator<Key, Value, Comparator>(nullptr, this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::constEnd() const {
    return AVLTreeConstIterator<Key, Value, Comparator>(nullptr, this);
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::replaceChildren(AVLTreeNode<Key, Value, Comparator>* parent, AVLTreeNode<Key, Value, Comparator>* child, AVLTreeNode<Key, Value, Comparator>* newChild){
    if(parent == nullptr){return;}
    if((*parent).leftChild_ == child){(*parent).leftChild_ = newChild;}
    else{(*parent).rightChild_ = newChild;}
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::replaceParent(AVLTreeNode<Key, Value, Comparator>* child, AVLTreeNode<Key, Value, Comparator>* newParent){
    if(child == nullptr){return;}
    (*child).parent_ = newParent;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTree<Key, Value, Comparator>::erase(AVLTreeIterator<Key, Value, Comparator>& i){
    AVLTreeNode<Key, Value, Comparator>* nodeToDelete = i.associatedNode_;
    if(nodeToDelete == nullptr){return false;}
    i++;
    if((*nodeToDelete).leftChild_ == nullptr && (*nodeToDelete).rightChild_ == nullptr){
        replaceChildren((*nodeToDelete).parent_, nodeToDelete, nullptr);
        if(nodeToDelete == root_){root_ = nullptr;}
        updateHeightRecurseToRoot((*nodeToDelete).parent_);
        delete nodeToDelete;
    }
    else if((*nodeToDelete).rightChild_ == nullptr){
        replaceChildren((*nodeToDelete).parent_, nodeToDelete, (*nodeToDelete).leftChild_);
        replaceParent((*nodeToDelete).leftChild_, (*nodeToDelete).parent_);
        if(nodeToDelete == root_){root_ = (*nodeToDelete).leftChild_;}
        updateHeightRecurseToRoot((*nodeToDelete).parent_);
        delete nodeToDelete;
    }
    else if((*nodeToDelete).leftChild_ == nullptr){
        replaceChildren((*nodeToDelete).parent_, nodeToDelete, (*nodeToDelete).rightChild_);
        replaceParent((*nodeToDelete).rightChild_, (*nodeToDelete).parent_);
        if(nodeToDelete == root_){root_ = (*nodeToDelete).rightChild_;}
        updateHeightRecurseToRoot((*nodeToDelete).parent_);
        delete nodeToDelete;
    }
    else{
        AVLTreeNode<Key, Value, Comparator>* replace = getLeftMostSubchild((*nodeToDelete).rightChild_);
        AVLTreeNode<Key, Value, Comparator>* updateStart = nullptr;
        if((*replace).parent_ == nodeToDelete){
            updateStart = replace;
            replaceChildren((*nodeToDelete).parent_, nodeToDelete, replace);
            replaceParent((*nodeToDelete).leftChild_, replace);
            (*replace).parent_ = (*nodeToDelete).parent_;
            (*replace).leftChild_ = (*nodeToDelete).leftChild_;
            if(nodeToDelete == root_){root_ = replace;}
        }
        else{
            replaceChildren((*replace).parent_, replace, (*replace).rightChild_);
            replaceParent((*replace).rightChild_, (*replace).parent_);
            updateStart = (*replace).parent_;
            replaceChildren((*nodeToDelete).parent_, nodeToDelete, replace);
            replaceParent((*nodeToDelete).leftChild_, replace);
            replaceParent((*nodeToDelete).rightChild_, replace);
            (*replace).parent_ = (*nodeToDelete).parent_;
            (*replace).leftChild_ = (*nodeToDelete).leftChild_;
            (*replace).rightChild_ = (*nodeToDelete).rightChild_;
            if(nodeToDelete == root_){root_ = replace;}
        }
        updateHeightRecurseToRoot(updateStart);
        delete nodeToDelete;
    }
    i--;
    return true;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::findNode(const Key& x) const {
    AVLTreeNode<Key, Value, Comparator>* currentNode = root_;
    if(root_ == nullptr){return nullptr;}
    while(true){
        if(comparatorInstance_(x, (*currentNode).key_) == true){
            if((*currentNode).leftChild_ == nullptr){return nullptr;}
            currentNode = (*currentNode).leftChild_;
        }
        else if(comparatorInstance_((*currentNode).key_, x) == true){
            if((*currentNode).rightChild_ == nullptr){return nullptr;}
            currentNode = (*currentNode).rightChild_;
        }
        else{return currentNode;}
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::find(const Key& x){
    return AVLTreeIterator(findNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::constFind(const Key& x) const {
    return AVLTreeConstIterator<Key, Value, Comparator>(findNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::lowerBoundNode(const Key& x) const {
    AVLTreeNode<Key, Value, Comparator>* output = nullptr;
    AVLTreeNode<Key, Value, Comparator>* currentNode = root_;
    while(currentNode != nullptr){
        if(comparatorInstance_((*currentNode).key_, x) == false){
            output = currentNode;
            currentNode = (*currentNode).leftChild_;
        }
        else{currentNode = (*currentNode).rightChild_;}
    }
    return output;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::lowerBound(const Key& x){
    return AVLTreeIterator(lowerBoundNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::constLowerBound(const Key& x) const {
    return AVLTreeConstIterator(lowerBoundNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::upperBoundNode(const Key& x) const {
    AVLTreeNode<Key, Value, Comparator>* output = nullptr;
    AVLTreeNode<Key, Value, Comparator>* currentNode = root_;
    while(currentNode != nullptr){
        if(comparatorInstance_(x, (*currentNode).key_) == true){
            output = currentNode;
            currentNode = (*currentNode).leftChild_;
        }
        else{currentNode = (*currentNode).rightChild_;}
    }
    return output;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::upperBound(const Key& x){
    return AVLTreeIterator(upperBoundNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::constUpperBound(const Key& x) const {
    return AVLTreeConstIterator(upperBoundNode(x), this);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getIndexOfNode(const AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return -1;}
    const AVLTreeNode<Key, Value, Comparator>* currentNode = x;
    int index = 0;
    while(true){
        if(currentNode == nullptr){return index;}
        if((*currentNode).parent_ != nullptr && (*(*currentNode).parent_).rightChild_ == currentNode){index += (1 + getEffectiveSubtreeSize((*(*currentNode).parent_).leftChild_));}
        currentNode = (*currentNode).parent_;
    }
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::indexOf(const Key& x) const {
    return indexOf(constFind(x));
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::indexOf(AVLTreeIterator<Key, Value, Comparator> i) const {
    return getIndexOfNode(i.associatedNode_);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::indexOf(AVLTreeConstIterator<Key, Value, Comparator> i) const {
    return getIndexOfNode(i.associatedNode_);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getNodeByIndex(int x) const {
    if(root_ == nullptr || x < 0 || x >= length()){return nullptr;}
    AVLTreeNode<Key, Value, Comparator>* currentNode = root_;
    while(true){
        const int leftSize = getEffectiveSubtreeSize((*currentNode).leftChild_);
        if(x == leftSize){return currentNode;}
        if(x < leftSize){currentNode = (*currentNode).leftChild_;}
        else{
            x -= (1 + leftSize);
            currentNode = (*currentNode).rightChild_;
        }
    }
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::keyAt(int n) const {
    return constIteratorAt(n).key();
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::valueAt(int n){
    return iteratorAt(n).value();
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::valueAt(int n) const {
    return constIteratorAt(n).value();
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::iteratorAt(int n){
    return AVLTreeIterator(getNodeByIndex(n), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::constIteratorAt(int n) const {
    return AVLTreeConstIterator<Key, Value, Comparator>(getNodeByIndex(n), this);
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::at(const Key& x){
    return find(x).value();
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::at(const Key& x) const {
    return constFind(x).value();
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::isEndIterator() const {
    return (associatedNode_ == nullptr);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::isEndIterator() const {
    return (associatedNode_ == nullptr);
}
