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
namespace SeerattraNum {
class BuildLah_SGEXTN_SeerattraNum SmoothingFunction {
public:
    float (*private_function)(float);
    static float private_polynomial2(float x);
    static float private_polynomial3(float x);
    static float private_trigonometric2(float x);
    static float private_rational2(float x);
    static float private_rational3(float x);
    SmoothingFunction(float (*function)(float));
    static SmoothingFunction polynomial2;
    static SmoothingFunction polynomial3;
    static SmoothingFunction trigonometric2;
    static SmoothingFunction rational2;
    static SmoothingFunction rational3;
};
}
}
