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
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::SeerattraNum::SmoothingFunction::SmoothingFunction() : SGEXTN::SeerattraNum::SmoothingFunction(&SGEXTN::SeerattraNum::SmoothingFunction::polynomial2Internal){}

SGEXTN::SeerattraNum::SmoothingFunction::SmoothingFunction(float (*function)(float)) : function_(function){}

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::polynomial2(&SGEXTN::SeerattraNum::SmoothingFunction::polynomial2Internal);

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::polynomial3(&SGEXTN::SeerattraNum::SmoothingFunction::polynomial3Internal);

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::trigonometric2(&SGEXTN::SeerattraNum::SmoothingFunction::trigonometric2Internal);

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::rational2(&SGEXTN::SeerattraNum::SmoothingFunction::rational2Internal);

SGEXTN::SeerattraNum::SmoothingFunction SGEXTN::SeerattraNum::SmoothingFunction::rational3(&SGEXTN::SeerattraNum::SmoothingFunction::rational3Internal);

float SGEXTN::SeerattraNum::SmoothingFunction::polynomial2Internal(float x){
    return (((6 * x - 15) * x + 10) * x * x * x);
}

float SGEXTN::SeerattraNum::SmoothingFunction::polynomial3Internal(float x){
    return ((((-20 * x + 70) * x - 84) * x + 35) * x * x * x * x);
}

float SGEXTN::SeerattraNum::SmoothingFunction::trigonometric2Internal(float x){
    const float twoPi = 2.0f * SGEXTN::Math::FloatConstants<float>::pi();
    return (x - SGEXTN::Math::FloatMath<float>::sine(twoPi * x) / twoPi);
}

float SGEXTN::SeerattraNum::SmoothingFunction::rational2Internal(float x){
    return ((x * x * x) / (x * x * x + (1-x) * (1-x) * (1-x)));
}

float SGEXTN::SeerattraNum::SmoothingFunction::rational3Internal(float x){
    return ((x * x * x * x) / (x * x * x * x + (1-x) * (1-x) * (1-x) * (1-x)));
}

bool SGEXTN::SeerattraNum::SmoothingFunction::sendOut(SGEXTN::SeerattraNum::SmoothingFunction x, SGEXTN::Containers::Span<unsigned char> data){
    unsigned char c = static_cast<unsigned char>(0);
    if(x.function_ == &SGEXTN::SeerattraNum::SmoothingFunction::polynomial2Internal){c = 1;}
    else if(x.function_ == &SGEXTN::SeerattraNum::SmoothingFunction::polynomial3Internal){c = 2;}
    else if(x.function_ == &SGEXTN::SeerattraNum::SmoothingFunction::trigonometric2Internal){c = 3;}
    else if(x.function_ == &SGEXTN::SeerattraNum::SmoothingFunction::rational2Internal){c = 4;}
    else if(x.function_ == &SGEXTN::SeerattraNum::SmoothingFunction::rational3Internal){c = 5;}
    else{return false;}
    return SGEXTN::Containers::Serialise<unsigned char>::sendOut(c, data);
}

bool SGEXTN::SeerattraNum::SmoothingFunction::sendIn(SGEXTN::SeerattraNum::SmoothingFunction& x, SGEXTN::Containers::Span<unsigned char> data){
    unsigned char c = static_cast<unsigned char>(0);
    const bool isValid = SGEXTN::Containers::Serialise<unsigned char>::sendIn(c, data);
    if(isValid == false || static_cast<int>(c) > 5 || c == static_cast<unsigned char>(0)){return false;}
    if(c == static_cast<unsigned char>(1)){x.function_ = &SGEXTN::SeerattraNum::SmoothingFunction::polynomial2Internal;}
    else if(c == static_cast<unsigned char>(2)){x.function_ = &SGEXTN::SeerattraNum::SmoothingFunction::polynomial3Internal;}
    else if(c == static_cast<unsigned char>(3)){x.function_ = &SGEXTN::SeerattraNum::SmoothingFunction::trigonometric2Internal;}
    else if(c == static_cast<unsigned char>(4)){x.function_ = &SGEXTN::SeerattraNum::SmoothingFunction::rational2Internal;}
    else if(c == static_cast<unsigned char>(5)){x.function_ = &SGEXTN::SeerattraNum::SmoothingFunction::rational3Internal;}
    else{return false;}
    return true;
}

int SGEXTN::SeerattraNum::SmoothingFunction::size(){
    return 1;
}

float SGEXTN::SeerattraNum::SmoothingFunction::useFunction(float x) const {
    return function_(x);
}
