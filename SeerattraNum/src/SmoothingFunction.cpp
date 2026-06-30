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

#include <SGEXTN/SeerattraNum/SmoothingFunction.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/Math/FloatConstants.h>

SGEXTN::SeerattraNum::SmoothingFunction::SmoothingFunction(float (*function)(float)) : private_function(function){}

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::polynomial2(&SGEXTN::SeerattraNum::SmoothingFunction::private_polynomial2);

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::polynomial3(&SGEXTN::SeerattraNum::SmoothingFunction::private_polynomial3);

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::trigonometric2(&SGEXTN::SeerattraNum::SmoothingFunction::private_trigonometric2);

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::rational2(&SGEXTN::SeerattraNum::SmoothingFunction::private_rational2);

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::rational3(&SGEXTN::SeerattraNum::SmoothingFunction::private_rational3);

float SGEXTN::SeerattraNum::SmoothingFunction::private_polynomial2(float x){
    return (((6 * x - 15) * x + 10) * x * x * x);
}

float SGEXTN::SeerattraNum::SmoothingFunction::private_polynomial3(float x){
    return ((((-20 * x + 70) * x - 84) * x + 35) * x * x * x * x);
}

float SGEXTN::SeerattraNum::SmoothingFunction::private_trigonometric2(float x){
    const float twoPi = 2.0f * SGEXTN::Math::FloatConstants<float>::pi();
    return (x - SGEXTN::Math::FloatMath<float>::sine(twoPi * x) / twoPi);
}

float SGEXTN::SeerattraNum::SmoothingFunction::private_rational2(float x){
    return ((x * x * x) / (x * x * x + (1-x) * (1-x) * (1-x)));
}

float SGEXTN::SeerattraNum::SmoothingFunction::private_rational3(float x){
    return ((x * x * x * x) / (x * x * x * x + (1-x) * (1-x) * (1-x) * (1-x)));
}
