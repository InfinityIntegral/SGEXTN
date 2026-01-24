#pragma once
#include <private_api/SGEXTN_Containers_AVLTree.h>

namespace SGEXTN {
namespace Containers {
template <typename T, typename Comparator> class SetIterator;
template <typename T, typename Comparator> class SetConstIterator;

template <typename T, typename Comparator> class Set {
public:
    AVLTree<T, bool, Comparator> private_avlTree;
    Set();
    [[nodiscard]] int length() const;
    bool insert(const T& x);
    bool erase(const T& x);
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] SetIterator<T, Comparator> begin();
    [[nodiscard]] SetConstIterator<T, Comparator> begin() const;
    [[nodiscard]] SetIterator<T, Comparator> end();
    [[nodiscard]] SetConstIterator<T, Comparator> end() const;
    bool erase(SetIterator<T, Comparator>& i);
    [[nodiscard]] SetIterator<T, Comparator> find(const T& x);
    [[nodiscard]] SetConstIterator<T, Comparator> find(const T& x) const;
    [[nodiscard]] SetIterator<T, Comparator> lowerBound(const T& x);
    [[nodiscard]] SetConstIterator<T, Comparator> lowerBound(const T& x) const;
    [[nodiscard]] SetIterator<T, Comparator> upperBound(const T& x);
    [[nodiscard]] SetConstIterator<T, Comparator> upperBound(const T& x) const;
    [[nodiscard]] int indexOf(const T& x) const;
    [[nodiscard]] int indexOf(SetIterator<T, Comparator> i) const;
    [[nodiscard]] int indexOf(SetConstIterator<T, Comparator> i) const;
    [[nodiscard]] const T& elementAt(int n) const;
    [[nodiscard]] SetIterator<T, Comparator> iteratorAt(int n);
    [[nodiscard]] SetConstIterator<T, Comparator> iteratorAt(int n) const;
};

template <typename T, typename Comparator> class SetIterator {
public:
    AVLTreeIterator<T, bool, Comparator> private_avlTreeIterator;
    SetIterator(AVLTreeIterator<T, bool, Comparator> i);
    SetIterator& operator++();
    SetIterator operator++(int);
    SetIterator& operator--();
    SetIterator operator--(int);
    bool operator==(const SetIterator& x);
    bool operator!=(const SetIterator& x);
    const T& operator*();
};

template <typename T, typename Comparator> class SetConstIterator {
public:
    AVLTreeConstIterator<T, bool, Comparator> private_avlTreeIterator;
    SetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i);
    SetConstIterator& operator++();
    SetConstIterator operator++(int);
    SetConstIterator& operator--();
    SetConstIterator operator--(int);
    bool operator==(const SetConstIterator& x);
    bool operator!=(const SetConstIterator& x);
    const T& operator*();
};
}
}

#include <private_api/SGEXTN_Containers_Set_impl.h>
