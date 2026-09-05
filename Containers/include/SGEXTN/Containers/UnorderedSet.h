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
#include <SGEXTN/Containers/private_api/HashMap.h>
#include <SGEXTN/Containers/EqualTo.h>
#include <SGEXTN/Containers/Hash.h>

namespace SGEXTN::Containers {
template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetCustomisable;
template <typename T> using UnorderedSet = UnorderedSetCustomisable<T, SGEXTN::Containers::EqualTo<T>, SGEXTN::Containers::Hash<T>>;

template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetIterator;
template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetConstIterator;

template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetCustomisable {
private:
    HashMap<T, bool, EqualityCheck, HashFunction> hashMap_;
public:
    UnorderedSetCustomisable();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    bool insert(const T& x);
    bool erase(const T& x);
    void clear();
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] UnorderedSetIterator<T, EqualityCheck, HashFunction> begin();
    [[nodiscard]] UnorderedSetConstIterator<T, EqualityCheck, HashFunction> constBegin() const;
    [[nodiscard]] UnorderedSetIterator<T, EqualityCheck, HashFunction> end();
    [[nodiscard]] UnorderedSetConstIterator<T, EqualityCheck, HashFunction> constEnd() const;
    bool erase(UnorderedSetIterator<T, EqualityCheck, HashFunction>& i);
    [[nodiscard]] UnorderedSetIterator<T, EqualityCheck, HashFunction> find(const T& x);
    [[nodiscard]] UnorderedSetConstIterator<T, EqualityCheck, HashFunction> constFind(const T& x) const;
};

template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetIterator {
private:
    friend class UnorderedSetCustomisable<T, EqualityCheck, HashFunction>;
    HashMapIterator<T, bool, EqualityCheck, HashFunction> hashMapIterator_;
    explicit UnorderedSetIterator(HashMapIterator<T, bool, EqualityCheck, HashFunction> i);
public:
    UnorderedSetIterator& operator++();
    UnorderedSetIterator operator++(int);
    UnorderedSetIterator& operator--();
    UnorderedSetIterator operator--(int);
    [[nodiscard]] bool operator==(const UnorderedSetIterator& x) const;
    [[nodiscard]] bool operator!=(const UnorderedSetIterator& x) const;
    [[nodiscard]] const T& operator*() const;
};

template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetConstIterator {
private:
    friend class UnorderedSetCustomisable<T, EqualityCheck, HashFunction>;
    HashMapConstIterator<T, bool, EqualityCheck, HashFunction> hashMapIterator_;
    explicit UnorderedSetConstIterator(HashMapConstIterator<T, bool, EqualityCheck, HashFunction> i);
public:
    UnorderedSetConstIterator& operator++();
    UnorderedSetConstIterator operator++(int);
    UnorderedSetConstIterator& operator--();
    UnorderedSetConstIterator operator--(int);
    [[nodiscard]] bool operator==(const UnorderedSetConstIterator& x) const;
    [[nodiscard]] bool operator!=(const UnorderedSetConstIterator& x) const;
    [[nodiscard]] const T& operator*() const;
};
}

#include <SGEXTN/Containers/private_api/UnorderedSet_impl.h>
