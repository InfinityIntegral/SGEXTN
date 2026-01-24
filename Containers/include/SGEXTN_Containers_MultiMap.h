#pragma once
#include <private_api/SGEXTN_Containers_AVLTree.h>

namespace SGEXTN {
namespace Containers {
template <typename Key, typename Value, typename Comparator> class MultiMapIterator;
template <typename Key, typename Value, typename Comparator> class MultiMapConstIterator;

template <typename Key, typename Value, typename Comparator> class MultiMap {
public:
    AVLTree<Key, Value, Comparator> private_avlTree;
    MultiMap();
    [[nodiscard]] int length() const;
    void insert(const Key& key, const Value& value);
    bool erase(const Key& x);
    [[nodiscard]] bool contains(const Key& x) const;
    [[nodiscard]] int count(const Key& x) const;
    [[nodiscard]] Value& at(const Key& x);
    [[nodiscard]] const Value& at(const Key& x) const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> begin();
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> begin() const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> end();
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> end() const;
    bool erase(MultiMapIterator<Key, Value, Comparator>& i);
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> find(const Key& x);
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> find(const Key& x) const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> lowerBound(const Key& x);
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> lowerBound(const Key& x) const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> upperBound(const Key& x);
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> upperBound(const Key& x) const;
    [[nodiscard]] int indexOf(const Key& x) const;
    [[nodiscard]] int indexOf(MultiMapIterator<Key, Value, Comparator> i) const;
    [[nodiscard]] int indexOf(MultiMapConstIterator<Key, Value, Comparator> i) const;
    [[nodiscard]] const Key& keyAt(int n) const;
    [[nodiscard]] Value& valueAt(int n);
    [[nodiscard]] const Value& valueAt(int n) const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> iteratorAt(int n);
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> iteratorAt(int n) const;
};

template <typename Key, typename Value, typename Comparator> class MultiMapIterator {
public:
    AVLTreeIterator<Key, Value, Comparator> private_avlTreeIterator;
    MultiMapIterator(AVLTreeIterator<Key, Value, Comparator> i);
    MultiMapIterator& operator++();
    MultiMapIterator operator++(int);
    MultiMapIterator& operator--();
    MultiMapIterator operator--(int);
    bool operator==(const MultiMapIterator& x);
    bool operator!=(const MultiMapIterator& x);
    const Key& key();
    Value& value();
};

template <typename Key, typename Value, typename Comparator> class MultiMapConstIterator {
public:
    AVLTreeConstIterator<Key, Value, Comparator> private_avlTreeIterator;
    MultiMapConstIterator(AVLTreeConstIterator<Key, Value, Comparator> i);
    MultiMapConstIterator& operator++();
    MultiMapConstIterator operator++(int);
    MultiMapConstIterator& operator--();
    MultiMapConstIterator operator--(int);
    bool operator==(const MultiMapConstIterator& x);
    bool operator!=(const MultiMapConstIterator& x);
    const Key& key();
    const Value& value();
};
}
}

#include <private_api/SGEXTN_Containers_MultiMap_impl.h>
