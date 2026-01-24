#pragma once

namespace SGEXTN {
namespace Containers {
template <typename Key, typename Value, typename Comparator> class AVLTree;

template <typename Key, typename Value, typename Comparator> class AVLTreeNode {
public:
    AVLTreeNode* parent;
    AVLTreeNode* leftChild;
    AVLTreeNode* rightChild;
    int height;
    int subtreeSize;
    Key key;
    Value value;
    AVLTreeNode(const Key& k, const Value& v, AVLTreeNode* parentNode);
    AVLTreeNode(AVLTreeNode* oldNode, AVLTreeNode* newParent);
    void recursiveDelete();
};

template <typename Key, typename Value, typename Comparator> class AVLTreeIterator;
template <typename Key, typename Value, typename Comparator> class AVLTreeConstIterator;

template <typename Key, typename Value, typename Comparator> class AVLTree {
public:
    AVLTreeNode<Key, Value, Comparator>* root;
    Comparator comparatorInstance;
    int getEffectiveHeight(AVLTreeNode<Key, Value, Comparator>* x) const;
    int getEffectiveSubtreeSize(AVLTreeNode<Key, Value, Comparator>* x) const;
    void updateHeightRecurseToRoot(AVLTreeNode<Key, Value, Comparator>* x);
    AVLTreeNode<Key, Value, Comparator>* rebalanceAtNode(AVLTreeNode<Key, Value, Comparator>* x);
    AVLTreeNode<Key, Value, Comparator>* leftRotate(AVLTreeNode<Key, Value, Comparator>* x);
    AVLTreeNode<Key, Value, Comparator>* rightRotate(AVLTreeNode<Key, Value, Comparator>* x);
    int heightLeftMinusRight(AVLTreeNode<Key, Value, Comparator>* x) const;
    [[nodiscard]] int maximumOf2Ints(int a, int b) const;
    void updateHeightNoRecurse(AVLTreeNode<Key, Value, Comparator>* x);
    void updateSubtreeSizeNoRecurse(AVLTreeNode<Key, Value, Comparator>* x);
    AVLTreeNode<Key, Value, Comparator>* getParentWithThisAsLeftChild(AVLTreeNode<Key, Value, Comparator>* x) const;
    AVLTreeNode<Key, Value, Comparator>* getParentWithThisAsRightChild(AVLTreeNode<Key, Value, Comparator>* x) const;
    AVLTreeNode<Key, Value, Comparator>* getLeftMostSubchild(AVLTreeNode<Key, Value, Comparator>* x) const;
    AVLTreeNode<Key, Value, Comparator>* getRightMostSubchild(AVLTreeNode<Key, Value, Comparator>* x) const;
    void replaceChildren(AVLTreeNode<Key, Value, Comparator>* parent, AVLTreeNode<Key, Value, Comparator>* child, AVLTreeNode<Key, Value, Comparator>* newChild);
    void replaceParent(AVLTreeNode<Key, Value, Comparator>* child, AVLTreeNode<Key, Value, Comparator>* newParent);
    AVLTreeNode<Key, Value, Comparator>* findNode(const Key& x) const;
    AVLTreeNode<Key, Value, Comparator>* lowerBoundNode(const Key& x) const;
    AVLTreeNode<Key, Value, Comparator>* upperBoundNode(const Key& x) const;
    AVLTreeNode<Key, Value, Comparator>* getNodeByIndex(int x) const;
    int getIndexOfNode(AVLTreeNode<Key, Value, Comparator>* x) const;
    AVLTree();
    AVLTree(const AVLTree& x);
    AVLTree& operator=(const AVLTree& x);
    AVLTree(AVLTree&& x) noexcept;
    AVLTree& operator=(AVLTree&& x) noexcept;
    ~AVLTree();
    [[nodiscard]] int length() const;
    bool insert(const Key& key, const Value& value, bool allowDuplicate);
    bool erase(const Key& x);
    [[nodiscard]] bool contains(const Key& x) const;
    [[nodiscard]] int count(const Key& x) const;
    [[nodiscard]] Value& at(const Key& x);
    [[nodiscard]] const Value& at(const Key& x) const;
    [[nodiscard]] AVLTreeIterator<Key, Value, Comparator> begin();
    [[nodiscard]] AVLTreeConstIterator<Key, Value, Comparator> begin() const;
    [[nodiscard]] AVLTreeIterator<Key, Value, Comparator> end();
    [[nodiscard]] AVLTreeConstIterator<Key, Value, Comparator> end() const;
    bool erase(AVLTreeIterator<Key, Value, Comparator>& i);
    [[nodiscard]] AVLTreeIterator<Key, Value, Comparator> find(const Key& x);
    [[nodiscard]] AVLTreeConstIterator<Key, Value, Comparator> find(const Key& x) const;
    [[nodiscard]] AVLTreeIterator<Key, Value, Comparator> lowerBound(const Key& x);
    [[nodiscard]] AVLTreeConstIterator<Key, Value, Comparator> lowerBound(const Key& x) const;
    [[nodiscard]] AVLTreeIterator<Key, Value, Comparator> upperBound(const Key& x);
    [[nodiscard]] AVLTreeConstIterator<Key, Value, Comparator> upperBound(const Key& x) const;
    [[nodiscard]] int indexOf(const Key& x) const;
    [[nodiscard]] int indexOf(AVLTreeIterator<Key, Value, Comparator> i) const;
    [[nodiscard]] int indexOf(AVLTreeConstIterator<Key, Value, Comparator> i) const;
    [[nodiscard]] const Key& keyAt(int n) const;
    [[nodiscard]] Value& valueAt(int n);
    [[nodiscard]] const Value& valueAt(int n) const;
    [[nodiscard]] AVLTreeIterator<Key, Value, Comparator> iteratorAt(int n);
    [[nodiscard]] AVLTreeConstIterator<Key, Value, Comparator> iteratorAt(int n) const;
};

template <typename Key, typename Value, typename Comparator> class AVLTreeIterator {
public:
    AVLTreeIterator& operator++();
    AVLTreeIterator operator++(int);
    AVLTreeIterator& operator--();
    AVLTreeIterator operator--(int);
    bool operator==(const AVLTreeIterator& x);
    bool operator!=(const AVLTreeIterator& x);
    const Key& key();
    Value& value();
    AVLTreeIterator() = default;
    AVLTreeIterator(AVLTreeNode<Key, Value, Comparator>* node, AVLTree<Key, Value, Comparator>* tree);
    AVLTreeNode<Key, Value, Comparator>* associatedNode;
    AVLTree<Key, Value, Comparator>* associatedTree;
};

template <typename Key, typename Value, typename Comparator> class AVLTreeConstIterator {
public:
    AVLTreeConstIterator& operator++();
    AVLTreeConstIterator operator++(int);
    AVLTreeConstIterator& operator--();
    AVLTreeConstIterator operator--(int);
    bool operator==(const AVLTreeConstIterator& x);
    bool operator!=(const AVLTreeConstIterator& x);
    const Key& key();
    const Value& value();
    AVLTreeConstIterator() = default;
    AVLTreeConstIterator(AVLTreeNode<Key, Value, Comparator>* node, const AVLTree<Key, Value, Comparator>* tree);
    AVLTreeNode<Key, Value, Comparator>* associatedNode;
    const AVLTree<Key, Value, Comparator>* associatedTree;
};
}
}

#include <private_api/SGEXTN_Containers_AVLTree_impl.h>
