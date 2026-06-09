#pragma once

namespace SGEXTN {
namespace Containers {
template <int... Sequence> class private_CountingSequence {};
template <int N, int... PartiallyGeneratedSequence> class private_CountingSequenceGenerator : public private_CountingSequenceGenerator<N - 1, N - 1, PartiallyGeneratedSequence...> {};
template <int... Sequence> class private_CountingSequenceGenerator<0, Sequence...> {
public:
    using private_GeneratedCountingSequence = private_CountingSequence<Sequence...>;
};
template <int I, typename T> class private_TupleComponent {
public:
    T storedObject;
};
template <typename CountingSequence, typename... Ts> class private_TupleInternalStorage;
template <int... Is, typename... Ts> class private_TupleInternalStorage<private_CountingSequence<Is...>, Ts...> : public private_TupleComponent<Is, Ts>... {
public:

};

template <typename... Ts> class Tuple {
public:
    private_TupleInternalStorage<typename private_CountingSequenceGenerator<sizeof...(Ts)>::private_GeneratedCountingSequence, Ts...> private_internalStorage;
    // constructor from elements
    // default constructor (if all types default constructible)
    // copy constructor
    // copy assignment
    // move constructor
    // move assignment
    ~Tuple() = default;
    // at non const ref
    // at const ref
    // == (if all types can use EqualTo)
    // != (if all types can use EqualTo)
    // < (if all types can use LessThan)
    // > (if all types can use MoreThan)
    // hash (if all types can use Hash)
};
}
}