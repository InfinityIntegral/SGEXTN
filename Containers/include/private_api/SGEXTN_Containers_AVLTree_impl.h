#pragma once

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::AVLTree(){
    root = nullptr;
    comparatorInstance = Comparator();
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>::AVLTreeNode(const Key& k, const Value& v, AVLTreeNode* parentNode){
    key = k;
    value = v;
    parent = parentNode;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 0;
    subtreeSize = 1;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>::AVLTreeNode(AVLTreeNode* oldNode, AVLTreeNode* newParent){
    key = (*oldNode).key;
    value = (*oldNode).value;
    height = (*oldNode).height;
    subtreeSize = (*oldNode).subtreeSize;
    parent = newParent;
    if((*oldNode).leftChild != nullptr){leftChild = new AVLTreeNode((*oldNode).leftChild, this);}
    else{leftChild = nullptr;}
    if((*oldNode).rightChild != nullptr){rightChild = new AVLTreeNode((*oldNode).rightChild, this);}
    else{rightChild = nullptr;}
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::AVLTree(const AVLTree& x){
    if(x.root != nullptr){root = new AVLTreeNode(x.root, nullptr);}
    else{root = nullptr;}
    comparatorInstance = x.comparatorInstance;
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>::recursiveDelete(){
    if(leftChild != nullptr){(*leftChild).recursiveDelete();}
    if(rightChild != nullptr){(*rightChild).recursiveDelete();}
    delete this;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::operator=(const AVLTree& x){
    if(this == &x){return (*this);}
    if(root != nullptr){(*root).recursiveDelete();}
    if(x.root != nullptr){root = new AVLTreeNode(x.root, nullptr);}
    else{root = nullptr;}
    comparatorInstance = x.comparatorInstance;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::AVLTree(AVLTree&& x) noexcept {
    root = x.root;
    x.root = nullptr;
    comparatorInstance = x.comparatorInstance;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::operator=(AVLTree&& x) noexcept {
    if(root != nullptr){(*root).recursiveDelete();}
    root = x.root;
    x.root = nullptr;
    comparatorInstance = x.comparatorInstance;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::~AVLTree(){
    if(root != nullptr){(*root).recursiveDelete();}
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::length() const {
    return getEffectiveSubtreeSize(root);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getEffectiveHeight(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return -1;}
    return (*x).height;
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getEffectiveSubtreeSize(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return 0;}
    return (*x).subtreeSize;
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::heightLeftMinusRight(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return 0;}
    return (getEffectiveHeight((*x).leftChild) - getEffectiveHeight((*x).rightChild));
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::maximumOf2Ints(int a, int b) const {
    if(a >= b){return a;}
    return b;
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::updateHeightNoRecurse(AVLTreeNode<Key, Value, Comparator>* x){
    if(x == nullptr){return;}
    (*x).height = maximumOf2Ints(getEffectiveHeight((*x).leftChild) + 1, getEffectiveHeight((*x).rightChild) + 1);
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::updateSubtreeSizeNoRecurse(AVLTreeNode<Key, Value, Comparator>* x){
    if(x == nullptr){return;}
    (*x).subtreeSize = getEffectiveSubtreeSize((*x).leftChild) + getEffectiveSubtreeSize((*x).rightChild) + 1;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::leftRotate(AVLTreeNode<Key, Value, Comparator>* x){
    AVLTreeNode<Key, Value, Comparator>* y = (*x).rightChild;
    AVLTreeNode<Key, Value, Comparator>* z = (*y).leftChild;
    AVLTreeNode<Key, Value, Comparator>* p = (*x).parent;
    (*y).leftChild = x;
    (*x).parent = y;
    (*x).rightChild = z;
    if(z != nullptr){(*z).parent = x;}
    updateHeightNoRecurse(x);
    updateSubtreeSizeNoRecurse(x);
    updateHeightNoRecurse(y);
    updateSubtreeSizeNoRecurse(y);
    if(p == nullptr){
        root = y;
        (*y).parent = nullptr;
    }
    else{
        if((*p).leftChild == x){(*p).leftChild = y;}
        else{(*p).rightChild = y;}
        (*y).parent = p;
        updateHeightNoRecurse(p);
        updateSubtreeSizeNoRecurse(p);
    }
    return y;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::rightRotate(AVLTreeNode<Key, Value, Comparator>* x){
    AVLTreeNode<Key, Value, Comparator>* y = (*x).leftChild;
    AVLTreeNode<Key, Value, Comparator>* z = (*y).rightChild;
    AVLTreeNode<Key, Value, Comparator>* p = (*x).parent;
    (*y).rightChild = x;
    (*x).parent = y;
    (*x).leftChild = z;
    if(z != nullptr){(*z).parent = x;}
    updateHeightNoRecurse(x);
    updateSubtreeSizeNoRecurse(x);
    updateHeightNoRecurse(y);
    updateSubtreeSizeNoRecurse(y);
    if(p == nullptr){
        root = y;
        (*y).parent = nullptr;
    }
    else{
        if((*p).leftChild == x){(*p).leftChild = y;}
        else{(*p).rightChild = y;}
        (*y).parent = p;
        updateHeightNoRecurse(p);
        updateSubtreeSizeNoRecurse(p);
    }
    return y;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::rebalanceAtNode(AVLTreeNode<Key, Value, Comparator>* x){
    if(heightLeftMinusRight(x) > 1){
        if(heightLeftMinusRight((*x).leftChild) >= 0){return rightRotate(x);}
        leftRotate((*x).leftChild);
        return rightRotate(x);
    }
    if(heightLeftMinusRight(x) < -1){
        if(heightLeftMinusRight((*x).rightChild) <= 0){return leftRotate(x);}
        rightRotate((*x).rightChild);
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
        if(x == root){break;}
        x = (*x).parent;
    }
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTree<Key, Value, Comparator>::insert(const Key& key, const Value& value, bool allowDuplicate){
    AVLTreeNode<Key, Value, Comparator>* currentNode = root;
    if(root == nullptr){
        root = new AVLTreeNode<Key, Value, Comparator>(key, value, nullptr);
        return true;
    }
    while(true){
        if(comparatorInstance(key, (*currentNode).key) == true){
            if((*currentNode).leftChild == nullptr){
                (*currentNode).leftChild = new AVLTreeNode(key, value, currentNode);
                currentNode = (*currentNode).leftChild;
                break;
            }
            currentNode = (*currentNode).leftChild;
        }
        else if(comparatorInstance((*currentNode).key, key) == true || allowDuplicate == true){
            if((*currentNode).rightChild == nullptr){
                (*currentNode).rightChild = new AVLTreeNode(key, value, currentNode);
                currentNode = (*currentNode).rightChild;
                break;
            }
            currentNode = (*currentNode).rightChild;
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

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTree<Key, Value, Comparator>::contains(const Key& x) const {
    return (find(x) != end());
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::count(const Key& x) const {
    AVLTreeConstIterator i = find(x);
    if(i == end()){return 0;}
    int count = 1;
    AVLTreeConstIterator currentNode = i;
    while(true){
        currentNode--;
        if(currentNode == end()){break;}
        if(comparatorInstance(currentNode.key(), x) == false && comparatorInstance(x, currentNode.key()) == false){count++;}
        else{break;}
    }
    currentNode = i;
    while(true){
        currentNode++;
        if(currentNode == end()){break;}
        if(comparatorInstance(currentNode.key(), x) == false && comparatorInstance(x, currentNode.key()) == false){count++;}
        else{break;}
    }
    return count;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::AVLTreeIterator(AVLTreeNode<Key, Value, Comparator>* node, AVLTree<Key, Value, Comparator>* tree){
    associatedNode = node;
    associatedTree = tree;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::AVLTreeConstIterator(AVLTreeNode<Key, Value, Comparator>* node, const AVLTree<Key, Value, Comparator>* tree){
    associatedNode = node;
    associatedTree = tree;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getLeftMostSubchild(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).leftChild == nullptr){return x;}
        x = (*x).leftChild;
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getRightMostSubchild(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).rightChild == nullptr){return x;}
        x = (*x).rightChild;
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getParentWithThisAsLeftChild(AVLTreeNode<Key, Value, Comparator>* x) const {
    while(true){
        if((*x).parent == nullptr){return nullptr;}
        if((*(*x).parent).leftChild == x){return (*x).parent;}
        x = (*x).parent;
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getParentWithThisAsRightChild(AVLTreeNode<Key, Value, Comparator>* x) const {
    while(true){
        if((*x).parent == nullptr){return nullptr;}
        if((*(*x).parent).rightChild == x){return (*x).parent;}
        x = (*x).parent;
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>& SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator++(){
    if(associatedNode == nullptr){associatedNode = (*associatedTree).getLeftMostSubchild((*associatedTree).root);}
    else if((*associatedNode).rightChild == nullptr){associatedNode = (*associatedTree).getParentWithThisAsLeftChild(associatedNode);}
    else{associatedNode = (*associatedTree).getLeftMostSubchild((*associatedNode).rightChild);}
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>& SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator++(){
    if(associatedNode == nullptr){associatedNode = (*associatedTree).getLeftMostSubchild((*associatedTree).root);}
    else if((*associatedNode).rightChild == nullptr){associatedNode = (*associatedTree).getParentWithThisAsLeftChild(associatedNode);}
    else{associatedNode = (*associatedTree).getLeftMostSubchild((*associatedNode).rightChild);}
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator++(int){
    AVLTreeIterator prev = (*this);
    if(associatedNode == nullptr){associatedNode = (*associatedTree).getLeftMostSubchild((*associatedTree).root);}
    else if((*associatedNode).rightChild == nullptr){associatedNode = (*associatedTree).getParentWithThisAsLeftChild(associatedNode);}
    else{associatedNode = (*associatedTree).getLeftMostSubchild((*associatedNode).rightChild);}
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator++(int){
    AVLTreeConstIterator prev = (*this);
    if(associatedNode == nullptr){associatedNode = (*associatedTree).getLeftMostSubchild((*associatedTree).root);}
    else if((*associatedNode).rightChild == nullptr){associatedNode = (*associatedTree).getParentWithThisAsLeftChild(associatedNode);}
    else{associatedNode = (*associatedTree).getLeftMostSubchild((*associatedNode).rightChild);}
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>& SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator--(){
    if(associatedNode == nullptr){associatedNode = (*associatedTree).getRightMostSubchild((*associatedTree).root);}
    else if((*associatedNode).leftChild == nullptr){associatedNode = (*associatedTree).getParentWithThisAsRightChild(associatedNode);}
    else{associatedNode = (*associatedTree).getRightMostSubchild((*associatedNode).leftChild);}
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>& SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator--(){
    if(associatedNode == nullptr){associatedNode = (*associatedTree).getRightMostSubchild((*associatedTree).root);}
    else if((*associatedNode).leftChild == nullptr){associatedNode = (*associatedTree).getParentWithThisAsRightChild(associatedNode);}
    else{associatedNode = (*associatedTree).getRightMostSubchild((*associatedNode).leftChild);}
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator--(int){
    AVLTreeIterator prev = (*this);
    if(associatedNode == nullptr){associatedNode = (*associatedTree).getRightMostSubchild((*associatedTree).root);}
    else if((*associatedNode).leftChild == nullptr){associatedNode = (*associatedTree).getParentWithThisAsRightChild(associatedNode);}
    else{associatedNode = (*associatedTree).getRightMostSubchild((*associatedNode).leftChild);}
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator--(int){
    AVLTreeConstIterator prev = (*this);
    if(associatedNode == nullptr){associatedNode = (*associatedTree).getRightMostSubchild((*associatedTree).root);}
    else if((*associatedNode).leftChild == nullptr){associatedNode = (*associatedTree).getParentWithThisAsRightChild(associatedNode);}
    else{associatedNode = (*associatedTree).getRightMostSubchild((*associatedNode).leftChild);}
    return prev;
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::key(){
    return (*associatedNode).key;
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::key(){
    return (*associatedNode).key;
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::value(){
    return (*associatedNode).value;
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::value(){
    return (*associatedNode).value;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator==(const AVLTreeIterator& x){
    return (associatedNode == x.associatedNode && associatedTree == x.associatedTree);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator==(const AVLTreeConstIterator& x){
    return (associatedNode == x.associatedNode && associatedTree == x.associatedTree);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator>::operator!=(const AVLTreeIterator& x){
    return (associatedNode != x.associatedNode || associatedTree != x.associatedTree);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator>::operator!=(const AVLTreeConstIterator& x){
    return (associatedNode != x.associatedNode || associatedTree != x.associatedTree);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::begin(){
    return AVLTreeIterator<Key, Value, Comparator>(getLeftMostSubchild(root), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::begin() const {
    return AVLTreeConstIterator<Key, Value, Comparator>(getLeftMostSubchild(root), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::end(){
    return AVLTreeIterator<Key, Value, Comparator>(nullptr, this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::end() const {
    return AVLTreeConstIterator<Key, Value, Comparator>(nullptr, this);
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::replaceChildren(AVLTreeNode<Key, Value, Comparator>* parent, AVLTreeNode<Key, Value, Comparator>* child, AVLTreeNode<Key, Value, Comparator>* newChild){
    if(parent == nullptr){return;}
    if((*parent).leftChild == child){(*parent).leftChild = newChild;}
    else{(*parent).rightChild = newChild;}
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::AVLTree<Key, Value, Comparator>::replaceParent(AVLTreeNode<Key, Value, Comparator>* child, AVLTreeNode<Key, Value, Comparator>* newParent){
    if(child == nullptr){return;}
    (*child).parent = newParent;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::AVLTree<Key, Value, Comparator>::erase(AVLTreeIterator<Key, Value, Comparator>& i){
    AVLTreeNode<Key, Value, Comparator>* nodeToDelete = i.associatedNode;
    if(nodeToDelete == nullptr){return false;}
    i++;
    if((*nodeToDelete).leftChild == nullptr && (*nodeToDelete).rightChild == nullptr){
        replaceChildren((*nodeToDelete).parent, nodeToDelete, nullptr);
        if(nodeToDelete == root){root = nullptr;}
        updateHeightRecurseToRoot((*nodeToDelete).parent);
        delete nodeToDelete;
    }
    else if((*nodeToDelete).rightChild == nullptr){
        replaceChildren((*nodeToDelete).parent, nodeToDelete, (*nodeToDelete).leftChild);
        replaceParent((*nodeToDelete).leftChild, (*nodeToDelete).parent);
        if(nodeToDelete == root){root = (*nodeToDelete).leftChild;}
        updateHeightRecurseToRoot((*nodeToDelete).parent);
        delete nodeToDelete;
    }
    else if((*nodeToDelete).leftChild == nullptr){
        replaceChildren((*nodeToDelete).parent, nodeToDelete, (*nodeToDelete).rightChild);
        replaceParent((*nodeToDelete).rightChild, (*nodeToDelete).parent);
        if(nodeToDelete == root){root = (*nodeToDelete).rightChild;}
        updateHeightRecurseToRoot((*nodeToDelete).parent);
        delete nodeToDelete;
    }
    else{
        AVLTreeNode<Key, Value, Comparator>* replace = getLeftMostSubchild((*nodeToDelete).rightChild);
        AVLTreeNode<Key, Value, Comparator>* updateStart = nullptr;
        if((*replace).parent == nodeToDelete){
            updateStart = replace;
            replaceChildren((*nodeToDelete).parent, nodeToDelete, replace);
            replaceParent((*nodeToDelete).leftChild, replace);
            (*replace).parent = (*nodeToDelete).parent;
            (*replace).leftChild = (*nodeToDelete).leftChild;
            if(nodeToDelete == root){root = replace;}
        }
        else{
            replaceChildren((*replace).parent, replace, (*replace).rightChild);
            replaceParent((*replace).rightChild, (*replace).parent);
            updateStart = (*replace).parent;
            replaceChildren((*nodeToDelete).parent, nodeToDelete, replace);
            replaceParent((*nodeToDelete).leftChild, replace);
            replaceParent((*nodeToDelete).rightChild, replace);
            (*replace).parent = (*nodeToDelete).parent;
            (*replace).leftChild = (*nodeToDelete).leftChild;
            (*replace).rightChild = (*nodeToDelete).rightChild;
            if(nodeToDelete == root){root = replace;}
        }
        updateHeightRecurseToRoot(updateStart);
        delete nodeToDelete;
    }
    i--;
    return true;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::findNode(const Key& x) const {
    AVLTreeNode<Key, Value, Comparator>* currentNode = root;
    if(root == nullptr){return nullptr;}
    while(true){
        if(comparatorInstance(x, (*currentNode).key) == true){
            if((*currentNode).leftChild == nullptr){return nullptr;}
            currentNode = (*currentNode).leftChild;
        }
        else if(comparatorInstance((*currentNode).key, x) == true){
            if((*currentNode).rightChild == nullptr){return nullptr;}
            currentNode = (*currentNode).rightChild;
        }
        else{return currentNode;}
    }
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::find(const Key& x){
    return AVLTreeIterator(findNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::find(const Key& x) const {
    return AVLTreeConstIterator<Key, Value, Comparator>(findNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::lowerBoundNode(const Key& x) const {
    AVLTreeNode<Key, Value, Comparator>* output = nullptr;
    AVLTreeNode<Key, Value, Comparator>* currentNode = root;
    while(currentNode != nullptr){
        if(comparatorInstance((*currentNode).key, x) == false){
            output = currentNode;
            currentNode = (*currentNode).leftChild;
        }
        else{currentNode = (*currentNode).rightChild;}
    }
    return output;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::lowerBound(const Key& x){
    return AVLTreeIterator(lowerBoundNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::lowerBound(const Key& x) const {
    return AVLTreeConstIterator(lowerBoundNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::upperBoundNode(const Key& x) const {
    AVLTreeNode<Key, Value, Comparator>* output = nullptr;
    AVLTreeNode<Key, Value, Comparator>* currentNode = root;
    while(currentNode != nullptr){
        if(comparatorInstance(x, (*currentNode).key) == true){
            output = currentNode;
            currentNode = (*currentNode).leftChild;
        }
        else{currentNode = (*currentNode).rightChild;}
    }
    return output;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::upperBound(const Key& x){
    return AVLTreeIterator(upperBoundNode(x), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::upperBound(const Key& x) const {
    return AVLTreeConstIterator(upperBoundNode(x), this);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getIndexOfNode(AVLTreeNode<Key, Value, Comparator>* x) const {
    if(x == nullptr){return -1;}
    AVLTreeNode<Key, Value, Comparator>* currentNode = x;
    int index = 0;
    while(true){
        if(currentNode == nullptr){return index;}
        if((*currentNode).parent != nullptr && (*(*currentNode).parent).rightChild == currentNode){index += (1 + getEffectiveSubtreeSize((*(*currentNode).parent).leftChild));}
        currentNode = (*currentNode).parent;
    }
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::indexOf(const Key& x) const {
    return indexOf(find(x));
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::indexOf(AVLTreeIterator<Key, Value, Comparator> i) const {
    return getIndexOfNode(i.associatedNode);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::AVLTree<Key, Value, Comparator>::indexOf(AVLTreeConstIterator<Key, Value, Comparator> i) const {
    return getIndexOfNode(i.associatedNode);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeNode<Key, Value, Comparator>* SGEXTN::Containers::AVLTree<Key, Value, Comparator>::getNodeByIndex(int x) const {
    if(root == nullptr || x < 0 || x >= length()){return nullptr;}
    AVLTreeNode<Key, Value, Comparator>* currentNode = root;
    while(true){
        int leftSize = getEffectiveSubtreeSize((*currentNode).leftChild);
        if(x == leftSize){return currentNode;}
        if(x < leftSize){currentNode = (*currentNode).leftChild;}
        else{
            x -= (1 + leftSize);
            currentNode = (*currentNode).rightChild;
        }
    }
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::keyAt(int n) const {
    return iteratorAt(n).key();
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::valueAt(int n){
    return iteratorAt(n).value();
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::iteratorAt(int n){
    return AVLTreeIterator(getNodeByIndex(n), this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> SGEXTN::Containers::AVLTree<Key, Value, Comparator>::iteratorAt(int n) const {
    return AVLTreeConstIterator<Key, Value, Comparator>(getNodeByIndex(n), this);
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::at(const Key& x){
    return find(x).value();
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::AVLTree<Key, Value, Comparator>::at(const Key& x) const {
    return find(x).value();
}
