#ifndef SGLPRIMITIVETYPECHECKER_H
#define SGLPRIMITIVETYPECHECKER_H

template <typename T> struct SGLPrimitiveTypeChecker {static const bool x = false;};
template <> struct SGLPrimitiveTypeChecker<char> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<unsigned char> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<signed char> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<bool> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<float> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<double> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<long double> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<short> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<unsigned short> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<int> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<unsigned int> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<long> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<unsigned long> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<long long> {static const bool x = true;};
template <> struct SGLPrimitiveTypeChecker<unsigned long long> {static const bool x = true;};

#endif // SGLPRIMITIVETYPECHECKER_H
