#pragma once
#include <private_api/SGEXTN_Containers_AVLTree.h>

namespace SGEXTN {
namespace Containers {
template <typename Key, typename Value, typename Comparator> class MapIterator;
template <typename Key, typename Value, typename Comparator> class MapConstIterator;

template <typename Key, typename Value, typename Comparator> class Map {
public:
    AVLTree<Key, Value, Comparator> private_avlTree;
    Map();
    [[nodiscard]] int length() const;
    bool insert(const Key& key, const Value& value);
    bool erase(const Key& x);
    [[nodiscard]] bool contains(const Key& x) const;
    [[nodiscard]] Value& at(const Key& x);
    [[nodiscard]] const Value& at(const Key& x) const;
    [[nodiscard]] MapIterator<Key, Value, Comparator> begin();
    [[nodiscard]] MapConstIterator<Key, Value, Comparator> begin() const;
    [[nodiscard]] MapIterator<Key, Value, Comparator> end();
    [[nodiscard]] MapConstIterator<Key, Value, Comparator> end() const;
    bool erase(MapIterator<Key, Value, Comparator>& i);
    [[nodiscard]] MapIterator<Key, Value, Comparator> find(const Key& x);
    [[nodiscard]] MapConstIterator<Key, Value, Comparator> find(const Key& x) const;
    [[nodiscard]] MapIterator<Key, Value, Comparator> lowerBound(const Key& x);
    [[nodiscard]] MapConstIterator<Key, Value, Comparator> lowerBound(const Key& x) const;
    [[nodiscard]] MapIterator<Key, Value, Comparator> upperBound(const Key& x);
    [[nodiscard]] MapConstIterator<Key, Value, Comparator> upperBound(const Key& x) const;
    [[nodiscard]] int indexOf(const Key& x) const;
    [[nodiscard]] int indexOf(MapIterator<Key, Value, Comparator> i) const;
    [[nodiscard]] int indexOf(MapConstIterator<Key, Value, Comparator> i) const;
    [[nodiscard]] const Key& keyAt(int n) const;
    [[nodiscard]] Value& valueAt(int n);
    [[nodiscard]] const Value& valueAt(int n) const;
    [[nodiscard]] MapIterator<Key, Value, Comparator> iteratorAt(int n);
    [[nodiscard]] MapConstIterator<Key, Value, Comparator> iteratorAt(int n) const;
};

template <typename Key, typename Value, typename Comparator> class MapIterator {
public:
    AVLTreeIterator<Key, Value, Comparator> private_avlTreeIterator;
    MapIterator(AVLTreeIterator<Key, Value, Comparator> i);
    MapIterator& operator++();
    MapIterator operator++(int);
    MapIterator& operator--();
    MapIterator operator--(int);
    bool operator==(const MapIterator& x);
    bool operator!=(const MapIterator& x);
    const Key& key();
    Value& value();
};

template <typename Key, typename Value, typename Comparator> class MapConstIterator {
public:
    AVLTreeConstIterator<Key, Value, Comparator> private_avlTreeIterator;
    MapConstIterator(AVLTreeConstIterator<Key, Value, Comparator> i);
    MapConstIterator& operator++();
    MapConstIterator operator++(int);
    MapConstIterator& operator--();
    MapConstIterator operator--(int);
    bool operator==(const MapConstIterator& x);
    bool operator!=(const MapConstIterator& x);
    const Key& key();
    const Value& value();
};
}
}

#include <private_api/SGEXTN_Containers_Map_impl.h>
