#ifndef SGLSET_H
#define SGLSET_H

#include "sglcrash.h"

template <typename T, typename Comparator> class SGLSet{
protected:
    class Node {
        friend class SGLSet;
    public:
        Node* parent;
        Node* leftChild;
        Node* rightChild;
        int height;
        int subtreeSize;
        T value;
        Node(const T& x, Node* parentNode);
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
    Node* findNode(const T& x) const;
    Node* lowerBoundNode(const T& x) const;
    Node* upperBoundNode(const T& x) const;
    Node* getNodeByIndex(int x) const;
    int getIndexOfNode(Node* x) const;
    
public:
    SGLSet();
    SGLSet(const SGLSet& x);
    SGLSet& operator=(const SGLSet& x);
    SGLSet(SGLSet&& x) noexcept;
    SGLSet& operator=(SGLSet&& x) noexcept;
    ~SGLSet();
    [[nodiscard]] int length() const;
    void insert(const T& x);
    void erase(const T& x);
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] int count(const T& x) const;
    
    class Iterator {
        friend class SGLSet;
    public:
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(Iterator x);
        bool operator!=(Iterator x);
        const T& operator*();
    protected:
        Iterator(Node* x, SGLSet* s);
        Node* node;
        SGLSet* associatedSet;
    };
    
    class ConstIterator {
        friend class SGLSet;
    public:
        ConstIterator& operator++();
        ConstIterator operator++(int);
        ConstIterator& operator--();
        ConstIterator operator--(int);
        bool operator==(ConstIterator x);
        bool operator!=(ConstIterator x);
        const T& operator*();
    protected:
        ConstIterator(Node* x, const SGLSet* s);
        Node* node;
        const SGLSet* associatedSet;
    };
    
    [[nodiscard]] Iterator begin();
    [[nodiscard]] ConstIterator constBegin() const;
    [[nodiscard]] Iterator end();
    [[nodiscard]] ConstIterator constEnd() const;
    void erase(Iterator& i);
    [[nodiscard]] Iterator find(const T& x);
    [[nodiscard]] ConstIterator find(const T& x) const;
    
    [[nodiscard]] Iterator lowerBound(const T& x);
    [[nodiscard]] ConstIterator lowerBound(const T& x) const;
    [[nodiscard]] Iterator upperBound(const T& x);
    [[nodiscard]] ConstIterator upperBound(const T& x) const;
    
    [[nodiscard]] int indexOf(const T& x) const;
    [[nodiscard]] int indexOf(Iterator i) const;
    [[nodiscard]] int indexOf(ConstIterator i) const;
    [[nodiscard]] const T& elementAt(int n) const;
    [[nodiscard]] Iterator iteratorAt(int n);
    [[nodiscard]] ConstIterator constIteratorAt(int n) const;
};

template <typename T, typename Comparator> SGLSet<T, Comparator>::SGLSet(){
    root = nullptr;
    comparatorInstance = Comparator();
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node::Node(const T& x, Node* parentNode){
    value = x;
    parent = parentNode;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 0;
    subtreeSize = 1;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node::Node(Node* oldNode, Node* newParent){
    value = (*oldNode).value;
    height = (*oldNode).height;
    subtreeSize = (*oldNode).subtreeSize;
    parent = newParent;
    if((*oldNode).leftChild != nullptr){leftChild = new Node((*oldNode).leftChild, this);}
    else{leftChild = nullptr;}
    if((*oldNode).rightChild != nullptr){rightChild = new Node((*oldNode).rightChild, this);}
    else{rightChild = nullptr;}
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::SGLSet(const SGLSet& x){
    if(x.root != nullptr){root = new Node(x.root, nullptr);}
    else{root = nullptr;}
    comparatorInstance = Comparator();
}

template <typename T, typename Comparator> void SGLSet<T, Comparator>::Node::recursiveDelete(){
    if(leftChild != nullptr){(*leftChild).recursiveDelete();}
    if(rightChild != nullptr){(*rightChild).recursiveDelete();}
    delete this;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>& SGLSet<T, Comparator>::operator=(const SGLSet& x){
    if(this == &x){return (*this);}
    if(root != nullptr){(*root).recursiveDelete();}
    if(x.root != nullptr){root = new Node(x.root, nullptr);}
    else{root = nullptr;}
    return (*this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::SGLSet(SGLSet&& x) noexcept {
    root = x.root;
    x.root = nullptr;
    comparatorInstance = Comparator();
}

template <typename T, typename Comparator> SGLSet<T, Comparator>& SGLSet<T, Comparator>::operator=(SGLSet&& x) noexcept {
    if(root != nullptr){(*root).recursiveDelete();}
    root = x.root;
    x.root = nullptr;
    return (*this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::~SGLSet(){
    if(root != nullptr){(*root).recursiveDelete();}
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::length() const {
    return getEffectiveSubtreeSize(root);
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::getEffectiveHeight(Node* x) const {
    if(x == nullptr){return -1;}
    return (*x).height;
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::getEffectiveSubtreeSize(Node* x) const {
    if(x == nullptr){return 0;}
    return (*x).subtreeSize;
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::heightLeftMinusRight(Node* x) const {
    if(x == nullptr){return 0;}
    return (getEffectiveHeight((*x).leftChild) - getEffectiveHeight((*x).rightChild));
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::maximumOf2Ints(int a, int b) const {
    if(a >= b){return a;}
    return b;
}

template <typename T, typename Comparator> void SGLSet<T, Comparator>::updateHeightNoRecurse(Node* x){
    if(x == nullptr){return;}
    (*x).height = maximumOf2Ints(getEffectiveHeight((*x).leftChild) + 1, getEffectiveHeight((*x).rightChild) + 1);
}

template <typename T, typename Comparator> void SGLSet<T, Comparator>::updateSubtreeSizeNoRecurse(Node* x){
    if(x == nullptr){return;}
    (*x).subtreeSize = getEffectiveSubtreeSize((*x).leftChild) + getEffectiveSubtreeSize((*x).rightChild) + 1;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::leftRotate(Node* x){
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

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::rightRotate(Node* x){
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

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::rebalanceAtNode(Node* x){
    if(heightLeftMinusRight(x) > 1){
        if(heightLeftMinusRight((*x).leftChild) >= 0){return rightRotate(x);}
        leftRotate((*x).leftChild);
        return rightRotate(x);
    }
    if(heightLeftMinusRight((*x).rightChild) <= 0){return leftRotate(x);}
    rightRotate((*x).rightChild);
    return leftRotate(x);
}

template <typename T, typename Comparator> void SGLSet<T, Comparator>::updateHeightRecurseToRoot(Node* x){
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

template <typename T, typename Comparator> void SGLSet<T, Comparator>::insert(const T& x){
    Node* currentNode = root;
    if(root == nullptr){
        root = new Node(x, nullptr);
        return;
    }
    while(true){
        if(comparatorInstance(x, (*currentNode).value) == true){
            if((*currentNode).leftChild == nullptr){
                (*currentNode).leftChild = new Node(x, currentNode);
                currentNode = (*currentNode).leftChild;
                break;
            }
            currentNode = (*currentNode).leftChild;
        }
        else if(comparatorInstance((*currentNode).value, x) == true){
            if((*currentNode).rightChild == nullptr){
                (*currentNode).rightChild = new Node(x, currentNode);
                currentNode = (*currentNode).rightChild;
                break;
            }
            currentNode = (*currentNode).rightChild;
        }
        else{SGLCrash::crashOnInsert();}
    }
    updateHeightRecurseToRoot(currentNode);
}

template <typename T, typename Comparator> void SGLSet<T, Comparator>::erase(const T& x){
    Iterator i = find(x);
    erase(i);
}

template <typename T, typename Comparator> bool SGLSet<T, Comparator>::contains(const T& x) const {
    if(find(x) == constEnd()){return false;}
    return true;
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::count(const T& x) const {
    if(contains(x) == true){return 1;}
    return 0;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator::Iterator(Node* x, SGLSet* s){
    node = x;
    associatedSet = s;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator::ConstIterator(Node* x, const SGLSet* s){
    node = x;
    associatedSet = s;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::getLeftmostSubchild(Node* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).leftChild == nullptr){return x;}
        x = (*x).leftChild;
    }
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::getRightmostSubchild(Node* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).rightChild == nullptr){return x;}
        x = (*x).rightChild;
    }
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::getParentWithThisAsLeftChild(Node* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).parent == nullptr){return nullptr;}
        if((*(*x).parent).leftChild == x){return (*x).parent;}
        x = (*x).parent;
    }
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::getParentWithThisAsRightChild(Node* x) const {
    if(x == nullptr){return nullptr;}
    while(true){
        if((*x).parent == nullptr){return nullptr;}
        if((*(*x).parent).rightChild == x){return (*x).parent;}
        x = (*x).parent;
    }
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator& SGLSet<T, Comparator>::Iterator::operator++(){
    if(node == nullptr){node = (*associatedSet).getLeftmostSubchild((*associatedSet).root);}
    else if((*node).rightChild == nullptr){node = (*associatedSet).getParentWithThisAsLeftChild(node);}
    else{node = (*associatedSet).getLeftmostSubchild((*node).rightChild);}
    return (*this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator& SGLSet<T, Comparator>::ConstIterator::operator++(){
    if(node == nullptr){node = (*associatedSet).getLeftmostSubchild((*associatedSet).root);}
    else if((*node).rightChild == nullptr){node = (*associatedSet).getParentWithThisAsLeftChild(node);}
    else{node = (*associatedSet).getLeftmostSubchild((*node).rightChild);}
    return (*this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator SGLSet<T, Comparator>::Iterator::operator++(int){
    Iterator prev = (*this);
    if(node == nullptr){node = (*associatedSet).getLeftmostSubchild((*associatedSet).root);}
    else if((*node).rightChild == nullptr){node = (*associatedSet).getParentWithThisAsLeftChild(node);}
    else{node = (*associatedSet).getLeftmostSubchild((*node).rightChild);}
    return prev;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator SGLSet<T, Comparator>::ConstIterator::operator++(int){
    ConstIterator prev = (*this);
    if(node == nullptr){node = (*associatedSet).getLeftmostSubchild((*associatedSet).root);}
    else if((*node).rightChild == nullptr){node = (*associatedSet).getParentWithThisAsLeftChild(node);}
    else{node = (*associatedSet).getLeftmostSubchild((*node).rightChild);}
    return prev;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator& SGLSet<T, Comparator>::Iterator::operator--(){
    if(node == nullptr){node = (*associatedSet).getRightmostSubchild((*associatedSet).root);}
    else if((*node).leftChild == nullptr){node = (*associatedSet).getParentWithThisAsRightChild(node);}
    else{node = (*associatedSet).getRightmostSubchild((*node).leftChild);}
    return (*this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator& SGLSet<T, Comparator>::ConstIterator::operator--(){
    if(node == nullptr){node = (*associatedSet).getRightmostSubchild((*associatedSet).root);}
    else if((*node).leftChild == nullptr){node = (*associatedSet).getParentWithThisAsRightChild(node);}
    else{node = (*associatedSet).getRightmostSubchild((*node).leftChild);}
    return (*this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator SGLSet<T, Comparator>::Iterator::operator--(int){
    Iterator prev = (*this);
    if(node == nullptr){node = (*associatedSet).getRightmostSubchild((*associatedSet).root);}
    else if((*node).leftChild == nullptr){node = (*associatedSet).getParentWithThisAsRightChild(node);}
    else{node = (*associatedSet).getRightmostSubchild((*node).leftChild);}
    return prev;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator SGLSet<T, Comparator>::ConstIterator::operator--(int){
    ConstIterator prev = (*this);
    if(node == nullptr){node = (*associatedSet).getRightmostSubchild((*associatedSet).root);}
    else if((*node).leftChild == nullptr){node = (*associatedSet).getParentWithThisAsRightChild(node);}
    else{node = (*associatedSet).getRightmostSubchild((*node).leftChild);}
    return prev;
}

template <typename T, typename Comparator> const T& SGLSet<T, Comparator>::Iterator::operator*(){
    return (*node).value;
}

template <typename T, typename Comparator> const T& SGLSet<T, Comparator>::ConstIterator::operator*(){
    return (*node).value;
}

template <typename T, typename Comparator> bool SGLSet<T, Comparator>::Iterator::operator==(Iterator x){
    return (node == x.node && associatedSet == x.associatedSet);
}

template <typename T, typename Comparator> bool SGLSet<T, Comparator>::Iterator::operator!=(Iterator x){
    return (node != x.node || associatedSet != x.associatedSet);
}

template <typename T, typename Comparator> bool SGLSet<T, Comparator>::ConstIterator::operator==(ConstIterator x){
    return (node == x.node && associatedSet == x.associatedSet);
}

template <typename T, typename Comparator> bool SGLSet<T, Comparator>::ConstIterator::operator!=(ConstIterator x){
    return (node != x.node || associatedSet != x.associatedSet);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator SGLSet<T, Comparator>::begin(){
    return Iterator(getLeftmostSubchild(root), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator SGLSet<T, Comparator>::constBegin() const {
    return ConstIterator(getLeftmostSubchild(root), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator SGLSet<T, Comparator>::end(){
    return Iterator(nullptr, this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator SGLSet<T, Comparator>::constEnd() const {
    return ConstIterator(nullptr, this);
}

template <typename T, typename Comparator> void SGLSet<T, Comparator>::replaceChildren(Node* parent, Node* child, Node* newChild){
    if(parent == nullptr){return;}
    if((*parent).leftChild == child){(*parent).leftChild = newChild;}
    else{(*parent).rightChild = newChild;}
}

template <typename T, typename Comparator> void SGLSet<T, Comparator>::replaceParent(Node* child, Node* newParent){
    if(child == nullptr){return;}
    (*child).parent = newParent;
}


template <typename T, typename Comparator> void SGLSet<T, Comparator>::erase(Iterator& i){
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

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::findNode(const T& x) const {
    Node* currentNode = root;
    if(root == nullptr){return nullptr;}
    while(true){
        if(comparatorInstance(x, (*currentNode).value) == true){
            if((*currentNode).leftChild == nullptr){return nullptr;}
            currentNode = (*currentNode).leftChild;
        }
        else if(comparatorInstance((*currentNode).value, x) == true){
            if((*currentNode).rightChild == nullptr){return nullptr;}
            currentNode = (*currentNode).rightChild;
        }
        else{return currentNode;}
    }
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator SGLSet<T, Comparator>::find(const T& x){
    return Iterator(findNode(x), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator SGLSet<T, Comparator>::find(const T& x) const {
    return ConstIterator(findNode(x), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::lowerBoundNode(const T& x) const {
    Node* output = nullptr;
    Node* currentNode = root;
    while(currentNode != nullptr){
        if(comparatorInstance((*currentNode).value, x) == false){
            output = currentNode;
            currentNode = (*currentNode).leftChild;
        }
        else{currentNode = (*currentNode).rightChild;}
    }
    return output;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::upperBoundNode(const T& x) const {
    Node* output = nullptr;
    Node* currentNode = root;
    while(currentNode != nullptr){
        if(comparatorInstance(x, (*currentNode).value) == true){
            output = currentNode;
            currentNode = (*currentNode).leftChild;
        }
        else{currentNode = (*currentNode).rightChild;}
    }
    return output;
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator SGLSet<T, Comparator>::lowerBound(const T& x){
    return Iterator(lowerBoundNode(x), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator SGLSet<T, Comparator>::lowerBound(const T& x) const {
    return ConstIterator(lowerBoundNode(x), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator SGLSet<T, Comparator>::upperBound(const T& x){
    return Iterator(upperBoundNode(x), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator SGLSet<T, Comparator>::upperBound(const T& x) const {
    return ConstIterator(upperBoundNode(x), this);
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::indexOf(const T& x) const {
    return indexOf(find(x));
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::indexOf(Iterator i) const {
    return getIndexOfNode(i.node);
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::indexOf(ConstIterator i) const {
    return getIndexOfNode(i.node);
}

template <typename T, typename Comparator> int SGLSet<T, Comparator>::getIndexOfNode(Node* x) const {
    if(x == nullptr){return -1;}
    Node* currentNode = root;
    int index = 0;
    while(true){
        if(currentNode == x){return (index + getEffectiveSubtreeSize((*currentNode).leftChild));}
        if(comparatorInstance((*x).value, (*currentNode).value) == true){currentNode = (*currentNode).leftChild;}
        else{
            index += (1 + getEffectiveSubtreeSize((*currentNode).leftChild));
            currentNode = (*currentNode).rightChild;
        }
    }
}

template <typename T, typename Comparator> const T& SGLSet<T, Comparator>::elementAt(int n) const {
    return (*constIteratorAt(n));
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Iterator SGLSet<T, Comparator>::iteratorAt(int n){
    return Iterator(getNodeByIndex(n), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::ConstIterator SGLSet<T, Comparator>::constIteratorAt(int n) const {
    return ConstIterator(getNodeByIndex(n), this);
}

template <typename T, typename Comparator> SGLSet<T, Comparator>::Node* SGLSet<T, Comparator>::getNodeByIndex(int x) const {
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

#endif // SGLSET_H
