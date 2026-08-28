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

namespace SGEXTN::Math {
template <typename T> class BuildLah_SGEXTN_Math Bitwise {
public:
    [[nodiscard]] static bool isPowerOf2(T x);
    [[nodiscard]] static T ceilingToPowerOf2(T x);
    [[nodiscard]] static T floorToPowerOf2(T x);
    [[nodiscard]] static int requiredStorageBits(T x);
    [[nodiscard]] static T leftRotate(T x, int amount);
    [[nodiscard]] static T rightRotate(T x, int amount);
    [[nodiscard]] static int leftCountConsecutiveZero(T x);
    [[nodiscard]] static int rightCountConsecutiveZero(T x);
    [[nodiscard]] static int leftCountConsecutiveOne(T x);
    [[nodiscard]] static int rightCountConsecutiveOne(T x);
    [[nodiscard]] static int countNumberOfOne(T x);
    [[nodiscard]] static int countNumberOfZero(T x);
};
}
