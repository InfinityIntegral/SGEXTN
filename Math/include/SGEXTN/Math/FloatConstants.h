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
template <typename T> class BuildLah_SGEXTN_Math FloatConstants {
public:
    [[nodiscard]] static T eulerNumber();
    [[nodiscard]] static T eulerNumberLog2();
    [[nodiscard]] static T eulerNumberLog10();
    [[nodiscard]] static T pi();
    [[nodiscard]] static T naturalLog2();
    [[nodiscard]] static T naturalLog10();
    [[nodiscard]] static T squareRoot2();
    [[nodiscard]] static T squareRoot3();
    [[nodiscard]] static T goldenRatio();
};
}
}
