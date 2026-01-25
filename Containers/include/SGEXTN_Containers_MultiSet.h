#pragma once
#include <private_api/SGEXTN_Containers_AVLTree.h>

namespace SGEXTN {
namespace Containers {
template <typename T, typename Comparator> class MultiSetIterator;
template <typename T, typename Comparator> class MultiSetConstIterator;

template <typename T, typename Comparator> class MultiSet {
public:
    AVLTree<T, bool, Comparator> private_avlTree;
    MultiSet();
    [[nodiscard]] int length() const;
    void insert(const T& x);
    bool erase(const T& x);
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] int count(const T& x) const;
    [[nodiscard]] MultiSetIterator<T, Comparator> begin();
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constBegin() const;
    [[nodiscard]] MultiSetIterator<T, Comparator> end();
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constEnd() const;
    bool erase(MultiSetIterator<T, Comparator>& i);
    [[nodiscard]] MultiSetIterator<T, Comparator> find(const T& x);
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constFind(const T& x) const;
    [[nodiscard]] MultiSetIterator<T, Comparator> lowerBound(const T& x);
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constLowerBound(const T& x) const;
    [[nodiscard]] MultiSetIterator<T, Comparator> upperBound(const T& x);
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constUpperBound(const T& x) const;
    [[nodiscard]] int indexOf(const T& x) const;
    [[nodiscard]] int indexOf(MultiSetIterator<T, Comparator> i) const;
    [[nodiscard]] int indexOf(MultiSetConstIterator<T, Comparator> i) const;
    [[nodiscard]] const T& elementAt(int n) const;
    [[nodiscard]] MultiSetIterator<T, Comparator> iteratorAt(int n);
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constIteratorAt(int n) const;
};

template <typename T, typename Comparator> class MultiSetIterator {
public:
    AVLTreeIterator<T, bool, Comparator> private_avlTreeIterator;
    MultiSetIterator(AVLTreeIterator<T, bool, Comparator> i);
    MultiSetIterator& operator++();
    MultiSetIterator operator++(int);
    MultiSetIterator& operator--();
    MultiSetIterator operator--(int);
    bool operator==(const MultiSetIterator& x);
    bool operator!=(const MultiSetIterator& x);
    const T& operator*();
};

template <typename T, typename Comparator> class MultiSetConstIterator {
public:
    AVLTreeConstIterator<T, bool, Comparator> private_avlTreeIterator;
    MultiSetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i);
    MultiSetConstIterator& operator++();
    MultiSetConstIterator operator++(int);
    MultiSetConstIterator& operator--();
    MultiSetConstIterator operator--(int);
    bool operator==(const MultiSetConstIterator& x);
    bool operator!=(const MultiSetConstIterator& x);
    const T& operator*();
};
}
}

#include <private_api/SGEXTN_Containers_MultiSet_impl.h>
