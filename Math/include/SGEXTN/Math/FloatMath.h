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

namespace SGEXTN {
namespace Math {
template <typename T> class BuildLah_SGEXTN_Math FloatMath {
public:
    [[nodiscard]] static T absoluteValue(T x);
    [[nodiscard]] static T modulo(T a, T b);
    [[nodiscard]] static T maximum(T a, T b);
    [[nodiscard]] static T minimum(T a, T b);
    [[nodiscard]] static T powerOfE(T x);
    [[nodiscard]] static T powerOf2(T x);
    [[nodiscard]] static T naturalLog(T x);
    [[nodiscard]] static T logBase2(T x);
    [[nodiscard]] static T logBase10(T x);
    [[nodiscard]] static T powerOf(T a, T b);
    [[nodiscard]] static T squareRoot(T x);
    [[nodiscard]] static T cubeRoot(T x);
    [[nodiscard]] static T sine(T x);
    [[nodiscard]] static T cosine(T x);
    [[nodiscard]] static T tangent(T x);
    [[nodiscard]] static T arcsine(T x);
    [[nodiscard]] static T arccosine(T x);
    [[nodiscard]] static T arctangent(T x);
    [[nodiscard]] static T arctangentQuadrantAware(T y, T x);
    [[nodiscard]] static T extendedFactorial(T x);
    [[nodiscard]] static T errorFunction(T x);
    [[nodiscard]] static T complementaryErrorFunction(T x);
    [[nodiscard]] static T ceiling(T x);
    [[nodiscard]] static int ceilingToInt(T x);
    [[nodiscard]] static T floor(T x);
    [[nodiscard]] static int floorToInt(T x);
    [[nodiscard]] static T round(T x);
    [[nodiscard]] static int roundToInt(T x);
};
}
}
