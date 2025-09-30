#ifndef SGLMAP_H
#define SGLMAP_H

#include "sglcrash.h"

template <typename K, typename V, typename Comparator> class SGLMap{
protected:
    class Node {
        friend class SGLMap;
    public:
        Node* parent;
        Node* leftChild;
        Node* rightChild;
        int height;
        int subtreeSize;
        K key;
        V value;
        Node(K xKey, V xValue, Node* parentNode);
        Node(Node* oldNode, Node* newParent);
        void recursiveDelete();
    };
    
    Node* root;
    Comparator comparatorInstance;
    int getEffectiveHeight(Node* x) const;
    int getEffectiveSubtreeSize(Node* x) const;
    void updateHeightRecurseToRoot(Node* x);
    Node* rebalanceAtNode(Node* x);
    Node* leftRotate(Node* x);
    Node* rightRotate(Node* x);
    int heightLeftMinusRight(Node* x) const;
    [[nodiscard]] int maximumOf2Ints(int a, int b) const;
    void updateHeightNoRecurse(Node* x);
    void updateSubtreeSizeNoRecurse(Node* x);
    Node* getParentWithThisAsLeftChild(Node* x) const;
    Node* getParentWithThisAsRightChild(Node* x) const;
    Node* getLeftmostSubchild(Node* x) const;
    Node* getRightmostSubchild(Node* x) const;
    void replaceChildren(Node* parent, Node* child, Node* newChild);
    void replaceParent(Node* child, Node* newParent);
    Node* findNode(K x) const;
    Node* lowerBoundNode(K x) const;
    Node* upperBoundNode(K x) const;
    Node* getNodeByIndex(int x) const;
    int getIndexOfNode(Node* x) const;
    
public:
    SGLMap();
    SGLMap(const SGLMap& x);
    SGLMap& operator=(const SGLMap& x);
    SGLMap(SGLMap&& x) noexcept;
    SGLMap& operator=(SGLMap&& x) noexcept;
    ~SGLMap();
    [[nodiscard]] int length() const;
    void insert(K xKey, V xValue);
    void erase(K x);
    [[nodiscard]] bool contains(K x) const;
    [[nodiscard]] int count(K x) const;
    [[nodiscard]] V& at(K x);
    [[nodiscard]] const V& at(K x) const;
    
    class Iterator {
        friend class SGLMap;
    public:
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(Iterator x);
        bool operator!=(Iterator x);
        K key();
        V value();
    protected:
        Iterator(Node* x, SGLMap* s);
        Node* node;
        SGLMap* associatedSet;
    };
    
    class ConstIterator {
        friend class SGLMap;
    public:
        ConstIterator& operator++();
        ConstIterator operator++(int);
        ConstIterator& operator--();
        ConstIterator operator--(int);
        bool operator==(ConstIterator x);
        bool operator!=(ConstIterator x);
        K key();
        V value();
    protected:
        ConstIterator(Node* x, const SGLMap* s);
        Node* node;
        const SGLMap* associatedSet;
    };
    
    [[nodiscard]] Iterator begin();
    [[nodiscard]] ConstIterator constBegin() const;
    [[nodiscard]] Iterator end();
    [[nodiscard]] ConstIterator constEnd() const;
    void erase(Iterator& i);
    [[nodiscard]] Iterator find(K x);
    [[nodiscard]] ConstIterator find(K x) const;
    
    [[nodiscard]] Iterator lowerBound(K x);
    [[nodiscard]] ConstIterator lowerBound(K x) const;
    [[nodiscard]] Iterator upperBound(K x);
    [[nodiscard]] ConstIterator upperBound(K x) const;
    
    [[nodiscard]] int indexOf(K x) const;
    [[nodiscard]] int indexOf(Iterator i) const;
    [[nodiscard]] int indexOf(ConstIterator i) const;
    [[nodiscard]] K keyAt(int n) const;
    [[nodiscard]] V valueAt(int n) const;
    [[nodiscard]] Iterator iteratorAt(int n);
    [[nodiscard]] ConstIterator constIteratorAt(int n) const;
};

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::SGLMap(){
    root = nullptr;
    comparatorInstance = Comparator();
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node::Node(K xKey, V xValue, Node* parentNode){
    key = xKey;
    value = xValue;
    parent = parentNode;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 0;
    subtreeSize = 1;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node::Node(Node* oldNode, Node* newParent){
    key = (*oldNode).key;
    value = (*oldNode).value;
    height = (*oldNode).height;
    subtreeSize = (*oldNode).subtreeSize;
    parent = newParent;
    if((*oldNode).leftChild != nullptr){leftChild = new Node((*oldNode).leftChild, this);}
    else{leftChild = nullptr;}
    if((*oldNode).rightChild != nullptr){rightChild = new Node((*oldNode).rightChild, this);}
    else{rightChild = nullptr;}
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::SGLMap(const SGLMap& x){
    if(x.root != nullptr){root = new Node(x.root, nullptr);}
    else{root = nullptr;}
    comparatorInstance = Comparator();
}

template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::Node::recursiveDelete(){
    if(leftChild != nullptr){(*leftChild).recursiveDelete();}
    if(rightChild != nullptr){(*rightChild).recursiveDelete();}
    delete this;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>& SGLMap<K, V, Comparator>::operator=(const SGLMap& x){
    if(this == &x){return (*this);}
    if(root != nullptr){(*root).recursiveDelete();}
    if(x.root != nullptr){root = new Node(x.root, nullptr);}
    else{root = nullptr;}
    return (*this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::SGLMap(SGLMap&& x) noexcept {
    root = x.root;
    x.root = nullptr;
    comparatorInstance = Comparator();
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>& SGLMap<K, V, Comparator>::operator=(SGLMap&& x) noexcept {
    if(root != nullptr){(*root).recursiveDelete();}
    root = x.root;
    x.root = nullptr;
    return (*this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::~SGLMap(){
    if(root != nullptr){(*root).recursiveDelete();}
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::length() const {
    return getEffectiveSubtreeSize(root);
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::getEffectiveHeight(Node* x) const {
    if(x == nullptr){return -1;}
    return (*x).height;
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::getEffectiveSubtreeSize(Node* x) const {
    if(x == nullptr){return 0;}
    return (*x).subtreeSize;
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::heightLeftMinusRight(Node* x) const {
    if(x == nullptr){return 0;}
    return (getEffectiveHeight((*x).leftChild) - getEffectiveHeight((*x).rightChild));
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::maximumOf2Ints(int a, int b) const {
    if(a >= b){return a;}
    return b;
}

template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::updateHeightNoRecurse(Node* x){
    if(x == nullptr){return;}
    (*x).height = maximumOf2Ints(getEffectiveHeight((*x).leftChild) + 1, getEffectiveHeight((*x).rightChild) + 1);
}

template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::updateSubtreeSizeNoRecurse(Node* x){
    if(x == nullptr){return;}
    (*x).subtreeSize = getEffectiveSubtreeSize((*x).leftChild) + getEffectiveSubtreeSize((*x).rightChild) + 1;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::leftRotate(Node* x){
    Node* y = (*x).rightChild;
    Node* z = (*y).leftChild;
    Node* p = (*x).parent;
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

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::rightRotate(Node* x){
    Node* y = (*x).leftChild;
    Node* z = (*y).rightChild;
    Node* p = (*x).parent;
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

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::rebalanceAtNode(Node* x){
    if(heightLeftMinusRight(x) > 1){
        if(heightLeftMinusRight((*x).leftChild) >= 0){return rightRotate(x);}
        leftRotate((*x).leftChild);
        return rightRotate(x);
    }
    if(heightLeftMinusRight((*x).rightChild) <= 0){return leftRotate(x);}
    rightRotate((*x).rightChild);
    return leftRotate(x);
}

template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::updateHeightRecurseToRoot(Node* x){
    if(x == nullptr){return;}
    while(true){
        updateHeightNoRecurse(x);
        updateSubtreeSizeNoRecurse(x);
        int heightDiff = heightLeftMinusRight(x);
        if(heightDiff < -1 || heightDiff > 1){x = rebalanceAtNode(x);}
        if(x == root){break;}
        x = (*x).parent;
    }
}

template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::insert(K xKey, V xValue){
    Node* currentNode = root;
    if(root == nullptr){
        root = new Node(xKey, xValue, nullptr);
        return;
    }
    while(true){
        if(comparatorInstance(xKey, (*currentNode).key) == true){
            if((*currentNode).leftChild == nullptr){
                (*currentNode).leftChild = new Node(xKey, xValue, currentNode);
                currentNode = (*currentNode).leftChild;
                break;
            }
            currentNode = (*currentNode).leftChild;
        }
        else if(comparatorInstance((*currentNode).key, xKey) == true){
            if((*currentNode).rightChild == nullptr){
                (*currentNode).rightChild = new Node(xKey, xValue, currentNode);
                currentNode = (*currentNode).rightChild;
                break;
            }
            currentNode = (*currentNode).rightChild;
        }
        else{SGLCrash::crashOnInsert();}
    }
    updateHeightRecurseToRoot(currentNode);
}

template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::erase(K x){
    Iterator i = find(x);
    erase(i);
}

template <typename K, typename V, typename Comparator> bool SGLMap<K, V, Comparator>::contains(K x) const {
    if(find(x) == constEnd()){return false;}
    return true;
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::count(K x) const {
    if(contains(x) == true){return 1;}
    return 0;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator::Iterator(Node* x, SGLMap* s){
    node = x;
    associatedSet = s;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator::ConstIterator(Node* x, const SGLMap* s){
    node = x;
    associatedSet = s;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::getLeftmostSubchild(Node* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).leftChild == nullptr){return x;}
        x = (*x).leftChild;
    }
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::getRightmostSubchild(Node* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).rightChild == nullptr){return x;}
        x = (*x).rightChild;
    }
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::getParentWithThisAsLeftChild(Node* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).parent == nullptr){return nullptr;}
        if((*(*x).parent).leftChild == x){return (*x).parent;}
        x = (*x).parent;
    }
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::getParentWithThisAsRightChild(Node* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).parent == nullptr){return nullptr;}
        if((*(*x).parent).rightChild == x){return (*x).parent;}
        x = (*x).parent;
    }
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator& SGLMap<K, V, Comparator>::Iterator::operator++(){
    if(node == nullptr){node = (*associatedSet).getLeftmostSubchild((*associatedSet).root);}
    else if((*node).rightChild == nullptr){node = (*associatedSet).getParentWithThisAsLeftChild(node);}
    else{node = (*associatedSet).getLeftmostSubchild((*node).rightChild);}
    return (*this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator& SGLMap<K, V, Comparator>::ConstIterator::operator++(){
    if(node == nullptr){node = (*associatedSet).getLeftmostSubchild((*associatedSet).root);}
    else if((*node).rightChild == nullptr){node = (*associatedSet).getParentWithThisAsLeftChild(node);}
    else{node = (*associatedSet).getLeftmostSubchild((*node).rightChild);}
    return (*this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator SGLMap<K, V, Comparator>::Iterator::operator++(int){
    Iterator prev = (*this);
    if(node == nullptr){node = (*associatedSet).getLeftmostSubchild((*associatedSet).root);}
    else if((*node).rightChild == nullptr){node = (*associatedSet).getParentWithThisAsLeftChild(node);}
    else{node = (*associatedSet).getLeftmostSubchild((*node).rightChild);}
    return prev;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator SGLMap<K, V, Comparator>::ConstIterator::operator++(int){
    ConstIterator prev = (*this);
    if(node == nullptr){node = (*associatedSet).getLeftmostSubchild((*associatedSet).root);}
    else if((*node).rightChild == nullptr){node = (*associatedSet).getParentWithThisAsLeftChild(node);}
    else{node = (*associatedSet).getLeftmostSubchild((*node).rightChild);}
    return prev;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator& SGLMap<K, V, Comparator>::Iterator::operator--(){
    if(node == nullptr){node = (*associatedSet).getRightmostSubchild((*associatedSet).root);}
    else if((*node).leftChild == nullptr){node = (*associatedSet).getParentWithThisAsRightChild(node);}
    else{node = (*associatedSet).getRightmostSubchild((*node).leftChild);}
    return (*this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator& SGLMap<K, V, Comparator>::ConstIterator::operator--(){
    if(node == nullptr){node = (*associatedSet).getRightmostSubchild((*associatedSet).root);}
    else if((*node).leftChild == nullptr){node = (*associatedSet).getParentWithThisAsRightChild(node);}
    else{node = (*associatedSet).getRightmostSubchild((*node).leftChild);}
    return (*this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator SGLMap<K, V, Comparator>::Iterator::operator--(int){
    Iterator prev = (*this);
    if(node == nullptr){node = (*associatedSet).getRightmostSubchild((*associatedSet).root);}
    else if((*node).leftChild == nullptr){node = (*associatedSet).getParentWithThisAsRightChild(node);}
    else{node = (*associatedSet).getRightmostSubchild((*node).leftChild);}
    return prev;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator SGLMap<K, V, Comparator>::ConstIterator::operator--(int){
    ConstIterator prev = (*this);
    if(node == nullptr){node = (*associatedSet).getRightmostSubchild((*associatedSet).root);}
    else if((*node).leftChild == nullptr){node = (*associatedSet).getParentWithThisAsRightChild(node);}
    else{node = (*associatedSet).getRightmostSubchild((*node).leftChild);}
    return prev;
}

template <typename K, typename V, typename Comparator> K SGLMap<K, V, Comparator>::Iterator::key(){
    return (*node).key;
}

template <typename K, typename V, typename Comparator> V SGLMap<K, V, Comparator>::Iterator::value(){
    return (*node).value;
}

template <typename K, typename V, typename Comparator> K SGLMap<K, V, Comparator>::ConstIterator::key(){
    return (*node).key;
}

template <typename K, typename V, typename Comparator> V SGLMap<K, V, Comparator>::ConstIterator::value(){
    return (*node).value;
}

template <typename K, typename V, typename Comparator> bool SGLMap<K, V, Comparator>::Iterator::operator==(Iterator x){
    return (node == x.node && associatedSet == x.associatedSet);
}

template <typename K, typename V, typename Comparator> bool SGLMap<K, V, Comparator>::Iterator::operator!=(Iterator x){
    return (node != x.node || associatedSet != x.associatedSet);
}

template <typename K, typename V, typename Comparator> bool SGLMap<K, V, Comparator>::ConstIterator::operator==(ConstIterator x){
    return (node == x.node && associatedSet == x.associatedSet);
}

template <typename K, typename V, typename Comparator> bool SGLMap<K, V, Comparator>::ConstIterator::operator!=(ConstIterator x){
    return (node != x.node || associatedSet != x.associatedSet);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator SGLMap<K, V, Comparator>::begin(){
    return Iterator(getLeftmostSubchild(root), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator SGLMap<K, V, Comparator>::constBegin() const {
    return ConstIterator(getLeftmostSubchild(root), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator SGLMap<K, V, Comparator>::end(){
    return Iterator(nullptr, this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator SGLMap<K, V, Comparator>::constEnd() const {
    return ConstIterator(nullptr, this);
}

template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::replaceChildren(Node* parent, Node* child, Node* newChild){
    if(parent == nullptr){return;}
    if((*parent).leftChild == child){(*parent).leftChild = newChild;}
    else{(*parent).rightChild = newChild;}
}

template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::replaceParent(Node* child, Node* newParent){
    if(child == nullptr){return;}
    (*child).parent = newParent;
}


template <typename K, typename V, typename Comparator> void SGLMap<K, V, Comparator>::erase(Iterator& i){
    Node* nodeToDelete = i.node;
    if(nodeToDelete == nullptr){SGLCrash::crashOnRemove();}
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
        Node* replace = getLeftmostSubchild((*nodeToDelete).rightChild);
        Node* updateStart = nullptr;
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
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::findNode(K x) const {
    Node* currentNode = root;
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

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator SGLMap<K, V, Comparator>::find(K x){
    return Iterator(findNode(x), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator SGLMap<K, V, Comparator>::find(K x) const {
    return ConstIterator(findNode(x), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::lowerBoundNode(K x) const {
    Node* output = nullptr;
    Node* currentNode = root;
    while(currentNode != nullptr){
        if(comparatorInstance((*currentNode).key, x) == false){
            output = currentNode;
            currentNode = (*currentNode).leftChild;
        }
        else{currentNode = (*currentNode).rightChild;}
    }
    return output;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::upperBoundNode(K x) const {
    Node* output = nullptr;
    Node* currentNode = root;
    while(currentNode != nullptr){
        if(comparatorInstance(x, (*currentNode).key) == true){
            output = currentNode;
            currentNode = (*currentNode).leftChild;
        }
        else{currentNode = (*currentNode).rightChild;}
    }
    return output;
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator SGLMap<K, V, Comparator>::lowerBound(K x){
    return Iterator(lowerBoundNode(x), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator SGLMap<K, V, Comparator>::lowerBound(K x) const {
    return ConstIterator(lowerBoundNode(x), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator SGLMap<K, V, Comparator>::upperBound(K x){
    return Iterator(upperBoundNode(x), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator SGLMap<K, V, Comparator>::upperBound(K x) const {
    return ConstIterator(upperBoundNode(x), this);
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::indexOf(K x) const {
    return indexOf(find(x));
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::indexOf(Iterator i) const {
    return getIndexOfNode(i.node);
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::indexOf(ConstIterator i) const {
    return getIndexOfNode(i.node);
}

template <typename K, typename V, typename Comparator> int SGLMap<K, V, Comparator>::getIndexOfNode(Node* x) const {
    if(x == nullptr){return -1;}
    Node* currentNode = root;
    int index = 0;
    while(true){
        if(currentNode == x){return (index + getEffectiveSubtreeSize((*currentNode).leftChild));}
        if(comparatorInstance((*x).key, (*currentNode).key) == true){currentNode = (*currentNode).leftChild;}
        else{
            index += (1 + getEffectiveSubtreeSize((*currentNode).leftChild));
            currentNode = (*currentNode).rightChild;
        }
    }
}

template <typename K, typename V, typename Comparator> K SGLMap<K, V, Comparator>::keyAt(int n) const {
    return constIteratorAt(n).key();
}

template <typename K, typename V, typename Comparator> V SGLMap<K, V, Comparator>::valueAt(int n) const {
    return constIteratorAt(n).value();
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Iterator SGLMap<K, V, Comparator>::iteratorAt(int n){
    return Iterator(getNodeByIndex(n), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::ConstIterator SGLMap<K, V, Comparator>::constIteratorAt(int n) const {
    return ConstIterator(getNodeByIndex(n), this);
}

template <typename K, typename V, typename Comparator> SGLMap<K, V, Comparator>::Node* SGLMap<K, V, Comparator>::getNodeByIndex(int x) const {
    if(root == nullptr){return nullptr;}
    if(x < 0 || x >= (*root).subtreeSize){return nullptr;}
    Node* currentNode = root;
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

template <typename K, typename V, typename Comparator> V& SGLMap<K, V, Comparator>::at(K x){
    ConstIterator i = find(x);
    if(i == constEnd()){SGLCrash::crash();}
    return i.value();
}

template <typename K, typename V, typename Comparator> const V& SGLMap<K, V, Comparator>::at(K x) const {
    ConstIterator i = find(x);
    if(i == constEnd()){SGLCrash::crash();}
    return i.value();
}

#endif // SGLMAP_H
