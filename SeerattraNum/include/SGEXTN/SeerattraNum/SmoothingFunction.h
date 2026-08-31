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

namespace SGEXTN::Containers {
template <typename T> class Span;
}

namespace SGEXTN::SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum SmoothingFunction {
private:
    float (*function_)(float);
    static float polynomial2Internal(float x);
    static float polynomial3Internal(float x);
    static float trigonometric2Internal(float x);
    static float rational2Internal(float x);
    static float rational3Internal(float x);
public:
    explicit SmoothingFunction();
    explicit SmoothingFunction(float (*function)(float));
    static SmoothingFunction polynomial2;
    static SmoothingFunction polynomial3;
    static SmoothingFunction trigonometric2;
    static SmoothingFunction rational2;
    static SmoothingFunction rational3;
    [[nodiscard]] static bool sendOut(SmoothingFunction x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(SmoothingFunction& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
    [[nodiscard]] float useFunction(float x) const;
};
}
