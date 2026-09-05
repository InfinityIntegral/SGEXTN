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

#include <SGEXTN/InternalTest/private_api/CanOneTest.h>
#include <SGEXTN/CanOne/Action.h>
#include <SGEXTN/Containers/ForceCrash.h>

namespace {
class FunctionStruct {
private:
    int value_;
public:
    static int globalValue;
    explicit FunctionStruct(int value);
    [[nodiscard]] int getValue() const;
    void setValue(int x);
    void funcV1(int x);
    void funcV2(int x);
    [[nodiscard]] int funcI1(int x);
    [[nodiscard]] int funcI2(int x);
    [[nodiscard]] FunctionStruct funcS1(int x);
    [[nodiscard]] FunctionStruct funcS2(int x);
    [[nodiscard]] const FunctionStruct* funcP1(int x);
    [[nodiscard]] const FunctionStruct* funcP2(int x);
    void funcCv1(int x) const;
    void funcCv2(int x) const;
    [[nodiscard]] int funcCi1(int x) const;
    [[nodiscard]] int funcCi2(int x) const;
    [[nodiscard]] FunctionStruct funcCs1(int x) const;
    [[nodiscard]] FunctionStruct funcCs2(int x) const;
    [[nodiscard]] const FunctionStruct* funcCp1(int x) const;
    [[nodiscard]] const FunctionStruct* funcCp2(int x) const;
};

int FunctionStruct::globalValue = 0;

FunctionStruct::FunctionStruct(int value) : value_(value){}

int FunctionStruct::getValue() const {
    return value_;
}

void FunctionStruct::setValue(int x){
    value_ = x;
}

void func1(){
    FunctionStruct::globalValue = 1;
}

void func2(){
    FunctionStruct::globalValue = 2;
}

void func3(int x){
    FunctionStruct::globalValue = 3 * x;
}

void func4(int x){
    FunctionStruct::globalValue = 4 * x;
}

void func5(int v1, int& v2, const int& v3, int* v4, const int* v5, FunctionStruct v6, FunctionStruct& v7, const FunctionStruct& v8, FunctionStruct* v9, const FunctionStruct* v10){
    const int ans = v1 + v3 + (*v5) + v6.getValue() + v8.getValue() + (*v10).getValue();
    v2 = ans;
    (*v4) = 2 + ans;
    v7.setValue(3 + ans);
    (*v9).setValue(4 + ans);
}

void func6(int v1, int& v2, const int& v3, int* v4, const int* v5, FunctionStruct v6, FunctionStruct& v7, const FunctionStruct& v8, FunctionStruct* v9, const FunctionStruct* v10){
    const int ans = v1 * v3 * (*v5) * v6.getValue() * v8.getValue() * (*v10).getValue();
    v2 = ans;
    (*v4) = 2 * ans;
    v7.setValue(3 * ans);
    (*v9).setValue(4 * ans);
}

int func7(int x){
    return x;
}

int func8(int x){
    return ((-1) * x);
}

FunctionStruct func9(int x){
    return FunctionStruct(x);
}

FunctionStruct func10(int x){
    return FunctionStruct((-1) * x);
}

const FunctionStruct* func11(int x){
    return new FunctionStruct(x);
}

const FunctionStruct* func12(int x){
    return new FunctionStruct((-1) * x);
}

void FunctionStruct::funcV1(int x){
    const int temp = value_;
    value_ = temp;
    FunctionStruct::globalValue = 2 * value_ * x;
}

void FunctionStruct::funcV2(int x){
    const int temp = value_;
    value_ = temp;
    FunctionStruct::globalValue = 3 * value_ * x;
}

int FunctionStruct::funcI1(int x){
    const int temp = value_;
    value_ = temp;
    return (2 * value_ * x);
}

int FunctionStruct::funcI2(int x){
    const int temp = value_;
    value_ = temp;
    return (3 * value_ * x);
}

FunctionStruct FunctionStruct::funcS1(int x){
    const int temp = value_;
    value_ = temp;
    return FunctionStruct(2 * value_ * x);
}

FunctionStruct FunctionStruct::funcS2(int x){
    const int temp = value_;
    value_ = temp;
    return FunctionStruct(3 * value_ * x);
}

const FunctionStruct* FunctionStruct::funcP1(int x){
    const int temp = value_;
    value_ = temp;
    return new FunctionStruct(2 * value_ * x);
}

const FunctionStruct* FunctionStruct::funcP2(int x){
    const int temp = value_;
    value_ = temp;
    return new FunctionStruct(3 * value_ * x);
}

void FunctionStruct::funcCv1(int x) const {
    FunctionStruct::globalValue = 2 * value_ * x;
}

void FunctionStruct::funcCv2(int x) const {
    FunctionStruct::globalValue = 3 * value_ * x;
}

int FunctionStruct::funcCi1(int x) const {
    return (2 * value_ * x);
}

int FunctionStruct::funcCi2(int x) const {
    return (3 * value_ * x);
}

FunctionStruct FunctionStruct::funcCs1(int x) const {
    return FunctionStruct(2 * value_ * x);
}

FunctionStruct FunctionStruct::funcCs2(int x) const {
    return FunctionStruct(3 * value_ * x);
}

const FunctionStruct* FunctionStruct::funcCp1(int x) const {
    return new FunctionStruct(2 * value_ * x);
}

const FunctionStruct* FunctionStruct::funcCp2(int x) const {
    return new FunctionStruct(3 * value_ * x);
}
}

void SGEXTN::InternalTest::CanOneTest::testAction(){
    SGEXTN::CanOne::Action<void> voidReturningAction(&func1);
    if(voidReturningAction.function(static_cast<void (*)()>(nullptr)) != &func1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with no args get function pointer fail");}
    voidReturningAction.function(static_cast<void (*)()>(nullptr)) = &func2;
    if(voidReturningAction.function(static_cast<void (*)()>(nullptr)) != &func2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with no args set function pointer fail");}
    voidReturningAction.execute();
    if(FunctionStruct::globalValue != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with no args execute fail");}

    voidReturningAction = SGEXTN::CanOne::Action<void>(&func3, 3);
    if(voidReturningAction.function(static_cast<void (*)(int)>(nullptr)) != &func3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with int arg get function pointer fail");}
    voidReturningAction.function(static_cast<void (*)(int)>(nullptr)) = &func4;
    if(voidReturningAction.function(static_cast<void (*)(int)>(nullptr)) != &func4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with int arg set function pointer fail");}
    if(voidReturningAction.argument<0>(static_cast<void (*)(int)>(nullptr)) != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with int arg get argument fail");}
    voidReturningAction.argument<0>(static_cast<void (*)(int)>(nullptr)) = 4;
    if(voidReturningAction.argument<0>(static_cast<void (*)(int)>(nullptr)) != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with int arg set argument fail");}
    voidReturningAction.execute();
    if(FunctionStruct::globalValue != 16){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with int arg execute fail");}

    int i1 = -1;
    int i2 = -2;
    i1 = 1;
    i2 = 2;
    const int ci1 = 1;
    const int ci2 = 2;
    FunctionStruct fs1 = FunctionStruct(-1);
    FunctionStruct fs2 = FunctionStruct(-2);
    fs1.setValue(1);
    fs2.setValue(2);
    const FunctionStruct cfs1 = FunctionStruct(1);
    const FunctionStruct cfs2 = FunctionStruct(2);
    voidReturningAction = SGEXTN::CanOne::Action<void>(&func5, 1, &i1, ci1, &i2, &ci1, FunctionStruct(1), &fs1, cfs1, &fs2, &cfs1);
    void (*longTypeIndicator)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) = nullptr;
    if(voidReturningAction.function(longTypeIndicator) != &func5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get function pointer fail");}
    voidReturningAction.function(longTypeIndicator) = &func6;
    if(voidReturningAction.function(longTypeIndicator) != &func6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set function pointer fail");}
    if(voidReturningAction.argument<0>(longTypeIndicator) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 0 fail");}
    voidReturningAction.argument<0>(longTypeIndicator) = 2;
    if(voidReturningAction.argument<0>(longTypeIndicator) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 0 fail");}
    if(voidReturningAction.argument<1>(longTypeIndicator) != &i1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 1 fail");}
    voidReturningAction.argument<1>(longTypeIndicator) = &i2;
    if(voidReturningAction.argument<1>(longTypeIndicator) != &i2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 1 fail");}
    if(voidReturningAction.argument<2>(longTypeIndicator) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 2 fail");}
    voidReturningAction.argument<2>(longTypeIndicator) = 2;
    if(voidReturningAction.argument<2>(longTypeIndicator) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 2 fail");}
    if(voidReturningAction.argument<3>(longTypeIndicator) != &i2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 3 fail");}
    voidReturningAction.argument<3>(longTypeIndicator) = &i1;
    if(voidReturningAction.argument<3>(longTypeIndicator) != &i1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 3 fail");}
    if(voidReturningAction.argument<4>(longTypeIndicator) != &ci1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 4 fail");}
    voidReturningAction.argument<4>(longTypeIndicator) = &ci2;
    if(voidReturningAction.argument<4>(longTypeIndicator) != &ci2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 4 fail");}
    if(voidReturningAction.argument<5>(longTypeIndicator).getValue() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 5 fail");}
    voidReturningAction.argument<5>(longTypeIndicator).setValue(2);
    if(voidReturningAction.argument<5>(longTypeIndicator).getValue() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 5 fail");}
    if(voidReturningAction.argument<6>(longTypeIndicator) != &fs1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 6 fail");}
    voidReturningAction.argument<6>(longTypeIndicator) = &fs2;
    if(voidReturningAction.argument<6>(longTypeIndicator) != &fs2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 6 fail");}
    if(voidReturningAction.argument<7>(longTypeIndicator).getValue() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 7 fail");}
    voidReturningAction.argument<7>(longTypeIndicator).setValue(2);
    if(voidReturningAction.argument<7>(longTypeIndicator).getValue() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 7 fail");}
    if(voidReturningAction.argument<8>(longTypeIndicator) != &fs2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 8 fail");}
    voidReturningAction.argument<8>(longTypeIndicator) = &fs1;
    if(voidReturningAction.argument<8>(longTypeIndicator) != &fs1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 8 fail");}
    if(voidReturningAction.argument<9>(longTypeIndicator) != &cfs1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args get argument 9 fail");}
    voidReturningAction.argument<9>(longTypeIndicator) = &cfs2;
    if(voidReturningAction.argument<9>(longTypeIndicator) != &cfs2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args set argument 9 fail");}
    voidReturningAction.execute();
    if(i2 != 64 || i1 != 128 || fs2.getValue() != 192 || fs1.getValue() != 256){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning static function with many args execute fail");}

    SGEXTN::CanOne::Action<int> intReturningAction(&func7, 1);
    if(intReturningAction.function(static_cast<int (*)(int)>(nullptr)) != &func7){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning static function get function pointer fail");}
    intReturningAction.function(static_cast<int (*)(int)>(nullptr)) = &func8;
    if(intReturningAction.function(static_cast<int (*)(int)>(nullptr)) != &func8){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning static function set function pointer fail");}
    if(intReturningAction.argument<0>(static_cast<int (*)(int)>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning static function get argument fail");}
    intReturningAction.argument<0>(static_cast<int (*)(int)>(nullptr)) = 2;
    if(intReturningAction.argument<0>(static_cast<int (*)(int)>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning static function set argument fail");}
    if(intReturningAction.execute() != -2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning static function execute fail");}

    SGEXTN::CanOne::Action<FunctionStruct> structReturningAction(&func9, 1);
    if(structReturningAction.function(static_cast<FunctionStruct (*)(int)>(nullptr)) != &func9){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning static function get function pointer fail");}
    structReturningAction.function(static_cast<FunctionStruct (*)(int)>(nullptr)) = &func10;
    if(structReturningAction.function(static_cast<FunctionStruct (*)(int)>(nullptr)) != &func10){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning static function set function pointer fail");}
    if(structReturningAction.argument<0>(static_cast<FunctionStruct (*)(int)>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning static function get argument fail");}
    structReturningAction.argument<0>(static_cast<FunctionStruct (*)(int)>(nullptr)) = 2;
    if(structReturningAction.argument<0>(static_cast<FunctionStruct (*)(int)>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning static function set argument fail");}
    if(structReturningAction.execute().getValue() != -2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning static function execute fail");}

    SGEXTN::CanOne::Action<const FunctionStruct*> pointerReturningAction(&func11, 1);
    if(pointerReturningAction.function(static_cast<const FunctionStruct* (*)(int)>(nullptr)) != &func11){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning static function get function pointer fail");}
    pointerReturningAction.function(static_cast<const FunctionStruct* (*)(int)>(nullptr)) = &func12;
    if(pointerReturningAction.function(static_cast<const FunctionStruct* (*)(int)>(nullptr)) != &func12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning static function set function pointer fail");}
    if(pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (*)(int)>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning static function get argument fail");}
    pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (*)(int)>(nullptr)) = 2;
    if(pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (*)(int)>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning static function set argument fail");}
    const FunctionStruct* returnedPointer = pointerReturningAction.execute();
    if((*returnedPointer).getValue() != -2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning static function execute fail");}
    delete returnedPointer;

    FunctionStruct nonConstInstance1(-1);
    nonConstInstance1.setValue(1);
    FunctionStruct nonConstInstance2(-2);
    nonConstInstance2.setValue(2);

    voidReturningAction = SGEXTN::CanOne::Action<void>(&FunctionStruct::funcV1, &nonConstInstance1, 1);
    if(voidReturningAction.function(static_cast<void (FunctionStruct::*)(int)>(nullptr)) != &FunctionStruct::funcV1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning non const member function get function pointer fail");}
    voidReturningAction.function(static_cast<void (FunctionStruct::*)(int)>(nullptr)) = &FunctionStruct::funcV2;
    if(voidReturningAction.function(static_cast<void (FunctionStruct::*)(int)>(nullptr)) != &FunctionStruct::funcV2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning non const member function set function pointer fail");}
    if(voidReturningAction.objectInstance(static_cast<void (FunctionStruct::*)(int)>(nullptr)) != &nonConstInstance1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning non const member function get object instance fail");}
    voidReturningAction.objectInstance(static_cast<void (FunctionStruct::*)(int)>(nullptr)) = &nonConstInstance2;
    if(voidReturningAction.objectInstance(static_cast<void (FunctionStruct::*)(int)>(nullptr)) != &nonConstInstance2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning non const member function set object instance fail");}
    if(voidReturningAction.argument<0>(static_cast<void (FunctionStruct::*)(int)>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning non const member function get argument fail");}
    voidReturningAction.argument<0>(static_cast<void (FunctionStruct::*)(int)>(nullptr)) = 2;
    if(voidReturningAction.argument<0>(static_cast<void (FunctionStruct::*)(int)>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning non const member function set argument fail");}
    voidReturningAction.execute();
    if(FunctionStruct::globalValue != 12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning non const member function execute fail");}

    intReturningAction = SGEXTN::CanOne::Action<int>(&FunctionStruct::funcI1, &nonConstInstance1, 1);
    if(intReturningAction.function(static_cast<int (FunctionStruct::*)(int)>(nullptr)) != &FunctionStruct::funcI1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning non const member function get function pointer fail");}
    intReturningAction.function(static_cast<int (FunctionStruct::*)(int)>(nullptr)) = &FunctionStruct::funcI2;
    if(intReturningAction.function(static_cast<int (FunctionStruct::*)(int)>(nullptr)) != &FunctionStruct::funcI2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning non const member function set function pointer fail");}
    if(intReturningAction.objectInstance(static_cast<int (FunctionStruct::*)(int)>(nullptr)) != &nonConstInstance1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning non const member function get object instance fail");}
    intReturningAction.objectInstance(static_cast<int (FunctionStruct::*)(int)>(nullptr)) = &nonConstInstance2;
    if(intReturningAction.objectInstance(static_cast<int (FunctionStruct::*)(int)>(nullptr)) != &nonConstInstance2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning non const member function set object instance fail");}
    if(intReturningAction.argument<0>(static_cast<int (FunctionStruct::*)(int)>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning non const member function get argument fail");}
    intReturningAction.argument<0>(static_cast<int (FunctionStruct::*)(int)>(nullptr)) = 2;
    if(intReturningAction.argument<0>(static_cast<int (FunctionStruct::*)(int)>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning non const member function set argument fail");}
    if(intReturningAction.execute() != 12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning non const member function execute fail");}

    structReturningAction = SGEXTN::CanOne::Action<FunctionStruct>(&FunctionStruct::funcS1, &nonConstInstance1, 1);
    if(structReturningAction.function(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) != &FunctionStruct::funcS1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning non const member function get function pointer fail");}
    structReturningAction.function(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) = &FunctionStruct::funcS2;
    if(structReturningAction.function(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) != &FunctionStruct::funcS2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning non const member function set function pointer fail");}
    if(structReturningAction.objectInstance(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) != &nonConstInstance1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning non const member function get object instance fail");}
    structReturningAction.objectInstance(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) = &nonConstInstance2;
    if(structReturningAction.objectInstance(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) != &nonConstInstance2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning non const member function set object instance fail");}
    if(structReturningAction.argument<0>(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning non const member function get argument fail");}
    structReturningAction.argument<0>(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) = 2;
    if(structReturningAction.argument<0>(static_cast<FunctionStruct (FunctionStruct::*)(int)>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning non const member function set argument fail");}
    if(structReturningAction.execute().getValue() != 12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning non const member function execute fail");}

    pointerReturningAction = SGEXTN::CanOne::Action<const FunctionStruct*>(&FunctionStruct::funcP1, &nonConstInstance1, 1);
    if(pointerReturningAction.function(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) != &FunctionStruct::funcP1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning non const member function get function pointer fail");}
    pointerReturningAction.function(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) = &FunctionStruct::funcP2;
    if(pointerReturningAction.function(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) != &FunctionStruct::funcP2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning non const member function set function pointer fail");}
    if(pointerReturningAction.objectInstance(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) != &nonConstInstance1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning non const member function get object instance fail");}
    pointerReturningAction.objectInstance(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) = &nonConstInstance2;
    if(pointerReturningAction.objectInstance(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) != &nonConstInstance2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning non const member function set object instance fail");}
    if(pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning non const member function get argument fail");}
    pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) = 2;
    if(pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (FunctionStruct::*)(int)>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning non const member function set argument fail");}
    returnedPointer = pointerReturningAction.execute();
    if((*returnedPointer).getValue() != 12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning non const member function execute fail");}
    delete returnedPointer;

    const FunctionStruct constInstance1(1);
    const FunctionStruct constInstance2(2);

    voidReturningAction = SGEXTN::CanOne::Action<void>(&FunctionStruct::funcCv1, &constInstance1, 1);
    if(voidReturningAction.function(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) != &FunctionStruct::funcCv1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning const member function get function pointer fail");}
    voidReturningAction.function(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) = &FunctionStruct::funcCv2;
    if(voidReturningAction.function(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) != &FunctionStruct::funcCv2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning const member function set function pointer fail");}
    if(voidReturningAction.objectInstance(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) != &constInstance1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning const member function get object instance fail");}
    voidReturningAction.objectInstance(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) = &constInstance2;
    if(voidReturningAction.objectInstance(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) != &constInstance2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning const member function set object instance fail");}
    if(voidReturningAction.argument<0>(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning const member function get argument fail");}
    voidReturningAction.argument<0>(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) = 2;
    if(voidReturningAction.argument<0>(static_cast<void (FunctionStruct::*)(int) const>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning const member function set argument fail");}
    voidReturningAction.execute();
    if(FunctionStruct::globalValue != 12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action void returning const member function execute fail");}

    intReturningAction = SGEXTN::CanOne::Action<int>(&FunctionStruct::funcCi1, &constInstance1, 1);
    if(intReturningAction.function(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) != &FunctionStruct::funcCi1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning const member function get function pointer fail");}
    intReturningAction.function(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) = &FunctionStruct::funcCi2;
    if(intReturningAction.function(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) != &FunctionStruct::funcCi2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning const member function set function pointer fail");}
    if(intReturningAction.objectInstance(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) != &constInstance1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning const member function get object instance fail");}
    intReturningAction.objectInstance(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) = &constInstance2;
    if(intReturningAction.objectInstance(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) != &constInstance2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning const member function set object instance fail");}
    if(intReturningAction.argument<0>(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning const member function get argument fail");}
    intReturningAction.argument<0>(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) = 2;
    if(intReturningAction.argument<0>(static_cast<int (FunctionStruct::*)(int) const>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning const member function set argument fail");}
    if(intReturningAction.execute() != 12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action int returning const member function execute fail");}

    structReturningAction = SGEXTN::CanOne::Action<FunctionStruct>(&FunctionStruct::funcCs1, &constInstance1, 1);
    if(structReturningAction.function(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) != &FunctionStruct::funcCs1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning const member function get function pointer fail");}
    structReturningAction.function(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) = &FunctionStruct::funcCs2;
    if(structReturningAction.function(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) != &FunctionStruct::funcCs2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning const member function set function pointer fail");}
    if(structReturningAction.objectInstance(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) != &constInstance1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning const member function get object instance fail");}
    structReturningAction.objectInstance(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) = &constInstance2;
    if(structReturningAction.objectInstance(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) != &constInstance2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning const member function set object instance fail");}
    if(structReturningAction.argument<0>(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning const member function get argument fail");}
    structReturningAction.argument<0>(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) = 2;
    if(structReturningAction.argument<0>(static_cast<FunctionStruct (FunctionStruct::*)(int) const>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning const member function set argument fail");}
    if(structReturningAction.execute().getValue() != 12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action struct returning const member function execute fail");}

    pointerReturningAction = SGEXTN::CanOne::Action<const FunctionStruct*>(&FunctionStruct::funcCp1, &constInstance1, 1);
    if(pointerReturningAction.function(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) != &FunctionStruct::funcCp1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning const member function get function pointer fail");}
    pointerReturningAction.function(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) = &FunctionStruct::funcCp2;
    if(pointerReturningAction.function(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) != &FunctionStruct::funcCp2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning const member function set function pointer fail");}
    if(pointerReturningAction.objectInstance(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) != &constInstance1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning const member function get object instance fail");}
    pointerReturningAction.objectInstance(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) = &constInstance2;
    if(pointerReturningAction.objectInstance(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) != &constInstance2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning const member function set object instance fail");}
    if(pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning const member function get argument fail");}
    pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) = 2;
    if(pointerReturningAction.argument<0>(static_cast<const FunctionStruct* (FunctionStruct::*)(int) const>(nullptr)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning const member function set argument fail");}
    returnedPointer = pointerReturningAction.execute();
    if((*returnedPointer).getValue() != 12){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action pointer returning const member function execute fail");}
    delete returnedPointer;
}

void SGEXTN::InternalTest::CanOneTest::testAll(){
    testAction();
}

template class SGEXTN::CanOne::Action<void>;
template class SGEXTN::CanOne::Action<int>;
template class SGEXTN::CanOne::Action<FunctionStruct>;
template class SGEXTN::CanOne::Action<const FunctionStruct*>;

template SGEXTN::CanOne::StaticFunction<void>& SGEXTN::CanOne::Action<void>::function(void (*)());
template const SGEXTN::CanOne::StaticFunction<void>& SGEXTN::CanOne::Action<void>::function(void (*)()) const;

template SGEXTN::CanOne::StaticFunction<void, int>& SGEXTN::CanOne::Action<void>::function(void (*)(int));
template const SGEXTN::CanOne::StaticFunction<void, int>& SGEXTN::CanOne::Action<void>::function(void (*)(int)) const;
template int& SGEXTN::CanOne::Action<void>::argument<0>(void (*)(int));
template const int& SGEXTN::CanOne::Action<void>::argument<0>(void (*)(int)) const;

template SGEXTN::CanOne::StaticFunction<void, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<void>::function(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const SGEXTN::CanOne::StaticFunction<void, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<void>::function(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<void>::argument<0>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<void>::argument<0>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<void>::argument<1>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<void>::argument<1>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<void>::argument<2>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<void>::argument<2>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<void>::argument<3>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<void>::argument<3>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const int*& SGEXTN::CanOne::Action<void>::argument<4>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int*const& SGEXTN::CanOne::Action<void>::argument<4>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<void>::argument<5>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<void>::argument<5>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<6>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<6>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<void>::argument<7>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<void>::argument<7>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<8>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<8>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<9>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<9>(void (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;

template SGEXTN::CanOne::StaticFunction<int>& SGEXTN::CanOne::Action<int>::function(int (*)());
template const SGEXTN::CanOne::StaticFunction<int>& SGEXTN::CanOne::Action<int>::function(int (*)()) const;

template SGEXTN::CanOne::StaticFunction<int, int>& SGEXTN::CanOne::Action<int>::function(int (*)(int));
template const SGEXTN::CanOne::StaticFunction<int, int>& SGEXTN::CanOne::Action<int>::function(int (*)(int)) const;
template int& SGEXTN::CanOne::Action<int>::argument<0>(int (*)(int));
template const int& SGEXTN::CanOne::Action<int>::argument<0>(int (*)(int)) const;

template SGEXTN::CanOne::StaticFunction<int, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<int>::function(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const SGEXTN::CanOne::StaticFunction<int, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<int>::function(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<int>::argument<0>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<int>::argument<0>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<int>::argument<1>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<int>::argument<1>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<int>::argument<2>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<int>::argument<2>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<int>::argument<3>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<int>::argument<3>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const int*& SGEXTN::CanOne::Action<int>::argument<4>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int*const& SGEXTN::CanOne::Action<int>::argument<4>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<int>::argument<5>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<int>::argument<5>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<6>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<6>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<int>::argument<7>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<int>::argument<7>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<8>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<8>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<9>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<9>(int (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;

template SGEXTN::CanOne::StaticFunction<FunctionStruct>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (*)());
template const SGEXTN::CanOne::StaticFunction<FunctionStruct>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (*)()) const;

template SGEXTN::CanOne::StaticFunction<FunctionStruct, int>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (*)(int));
template const SGEXTN::CanOne::StaticFunction<FunctionStruct, int>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (*)(int)) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (*)(int));
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (*)(int)) const;

template SGEXTN::CanOne::StaticFunction<FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const SGEXTN::CanOne::StaticFunction<FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<1>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<1>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<2>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<2>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<3>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<3>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<4>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<4>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<5>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<5>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<6>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<6>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<7>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<7>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<8>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<8>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<9>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<9>(FunctionStruct (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;

template SGEXTN::CanOne::StaticFunction<const FunctionStruct*>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (*)());
template const SGEXTN::CanOne::StaticFunction<const FunctionStruct*>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (*)()) const;

template SGEXTN::CanOne::StaticFunction<const FunctionStruct*, int>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (*)(int));
template const SGEXTN::CanOne::StaticFunction<const FunctionStruct*, int>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (*)(int)) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (*)(int));
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (*)(int)) const;

template SGEXTN::CanOne::StaticFunction<const FunctionStruct*, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const SGEXTN::CanOne::StaticFunction<const FunctionStruct*, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<1>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<1>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<2>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<2>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<3>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<3>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<4>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<4>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<5>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<5>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<6>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<6>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<7>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<7>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<8>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<8>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<9>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<9>(const FunctionStruct* (*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;

template SGEXTN::CanOne::NonConstMemberFunction<void, FunctionStruct>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)());
template const SGEXTN::CanOne::NonConstMemberFunction<void, FunctionStruct>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)()) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)());
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)()) const;

template SGEXTN::CanOne::NonConstMemberFunction<void, FunctionStruct, int>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)(int));
template const SGEXTN::CanOne::NonConstMemberFunction<void, FunctionStruct, int>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)(int)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)(int));
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)(int)) const;
template int& SGEXTN::CanOne::Action<void>::argument<0>(void (FunctionStruct::*)(int));
template const int& SGEXTN::CanOne::Action<void>::argument<0>(void (FunctionStruct::*)(int)) const;

template SGEXTN::CanOne::NonConstMemberFunction<void, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const SGEXTN::CanOne::NonConstMemberFunction<void, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<void>::argument<0>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<void>::argument<0>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<void>::argument<1>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<void>::argument<1>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<void>::argument<2>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<void>::argument<2>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<void>::argument<3>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<void>::argument<3>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const int*& SGEXTN::CanOne::Action<void>::argument<4>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int*const& SGEXTN::CanOne::Action<void>::argument<4>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<void>::argument<5>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<void>::argument<5>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<6>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<6>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<void>::argument<7>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<void>::argument<7>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<8>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<8>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<9>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<9>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;

template SGEXTN::CanOne::NonConstMemberFunction<int, FunctionStruct>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)());
template const SGEXTN::CanOne::NonConstMemberFunction<int, FunctionStruct>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)()) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)());
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)()) const;

template SGEXTN::CanOne::NonConstMemberFunction<int, FunctionStruct, int>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)(int));
template const SGEXTN::CanOne::NonConstMemberFunction<int, FunctionStruct, int>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)(int)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)(int));
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)(int)) const;
template int& SGEXTN::CanOne::Action<int>::argument<0>(int (FunctionStruct::*)(int));
template const int& SGEXTN::CanOne::Action<int>::argument<0>(int (FunctionStruct::*)(int)) const;

template SGEXTN::CanOne::NonConstMemberFunction<int, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const SGEXTN::CanOne::NonConstMemberFunction<int, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<int>::argument<0>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<int>::argument<0>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<int>::argument<1>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<int>::argument<1>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<int>::argument<2>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<int>::argument<2>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<int>::argument<3>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<int>::argument<3>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const int*& SGEXTN::CanOne::Action<int>::argument<4>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int*const& SGEXTN::CanOne::Action<int>::argument<4>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<int>::argument<5>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<int>::argument<5>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<6>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<6>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<int>::argument<7>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<int>::argument<7>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<8>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<8>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<9>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<9>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;

template SGEXTN::CanOne::NonConstMemberFunction<FunctionStruct, FunctionStruct>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)());
template const SGEXTN::CanOne::NonConstMemberFunction<FunctionStruct, FunctionStruct>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)()) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)());
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)()) const;

template SGEXTN::CanOne::NonConstMemberFunction<FunctionStruct, FunctionStruct, int>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)(int));
template const SGEXTN::CanOne::NonConstMemberFunction<FunctionStruct, FunctionStruct, int>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)(int)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)(int));
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)(int)) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (FunctionStruct::*)(int));
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (FunctionStruct::*)(int)) const;

template SGEXTN::CanOne::NonConstMemberFunction<FunctionStruct, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const SGEXTN::CanOne::NonConstMemberFunction<FunctionStruct, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<1>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<1>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<2>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<2>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<3>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<3>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<4>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<4>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<5>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<5>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<6>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<6>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<7>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<7>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<8>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<8>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<9>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<9>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;

template SGEXTN::CanOne::NonConstMemberFunction<const FunctionStruct*, FunctionStruct>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)());
template const SGEXTN::CanOne::NonConstMemberFunction<const FunctionStruct*, FunctionStruct>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)()) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)());
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)()) const;

template SGEXTN::CanOne::NonConstMemberFunction<const FunctionStruct*, FunctionStruct, int>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)(int));
template const SGEXTN::CanOne::NonConstMemberFunction<const FunctionStruct*, FunctionStruct, int>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)(int)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)(int));
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)(int)) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (FunctionStruct::*)(int));
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (FunctionStruct::*)(int)) const;

template SGEXTN::CanOne::NonConstMemberFunction<const FunctionStruct*, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const SGEXTN::CanOne::NonConstMemberFunction<const FunctionStruct*, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<1>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<1>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<2>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<2>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<3>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<3>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<4>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<4>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<5>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<5>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<6>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<6>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<7>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<7>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<8>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<8>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<9>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*));
template const FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<9>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*)) const;

template SGEXTN::CanOne::ConstMemberFunction<void, FunctionStruct>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)() const);
template const SGEXTN::CanOne::ConstMemberFunction<void, FunctionStruct>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)() const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)() const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)() const) const;

template SGEXTN::CanOne::ConstMemberFunction<void, FunctionStruct, int>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)(int) const);
template const SGEXTN::CanOne::ConstMemberFunction<void, FunctionStruct, int>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)(int) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)(int) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)(int) const) const;
template int& SGEXTN::CanOne::Action<void>::argument<0>(void (FunctionStruct::*)(int) const);
template const int& SGEXTN::CanOne::Action<void>::argument<0>(void (FunctionStruct::*)(int) const) const;

template SGEXTN::CanOne::ConstMemberFunction<void, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const SGEXTN::CanOne::ConstMemberFunction<void, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<void>::function(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<void>::objectInstance(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int& SGEXTN::CanOne::Action<void>::argument<0>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int& SGEXTN::CanOne::Action<void>::argument<0>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int*& SGEXTN::CanOne::Action<void>::argument<1>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template int*const& SGEXTN::CanOne::Action<void>::argument<1>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int& SGEXTN::CanOne::Action<void>::argument<2>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int& SGEXTN::CanOne::Action<void>::argument<2>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int*& SGEXTN::CanOne::Action<void>::argument<3>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template int*const& SGEXTN::CanOne::Action<void>::argument<3>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const int*& SGEXTN::CanOne::Action<void>::argument<4>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int*const& SGEXTN::CanOne::Action<void>::argument<4>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct& SGEXTN::CanOne::Action<void>::argument<5>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct& SGEXTN::CanOne::Action<void>::argument<5>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<6>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<6>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct& SGEXTN::CanOne::Action<void>::argument<7>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct& SGEXTN::CanOne::Action<void>::argument<7>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<8>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<8>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<void>::argument<9>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<void>::argument<9>(void (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;

template SGEXTN::CanOne::ConstMemberFunction<int, FunctionStruct>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)() const);
template const SGEXTN::CanOne::ConstMemberFunction<int, FunctionStruct>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)() const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)() const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)() const) const;

template SGEXTN::CanOne::ConstMemberFunction<int, FunctionStruct, int>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)(int) const);
template const SGEXTN::CanOne::ConstMemberFunction<int, FunctionStruct, int>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)(int) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)(int) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)(int) const) const;
template int& SGEXTN::CanOne::Action<int>::argument<0>(int (FunctionStruct::*)(int) const);
template const int& SGEXTN::CanOne::Action<int>::argument<0>(int (FunctionStruct::*)(int) const) const;

template SGEXTN::CanOne::ConstMemberFunction<int, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const SGEXTN::CanOne::ConstMemberFunction<int, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<int>::function(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<int>::objectInstance(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int& SGEXTN::CanOne::Action<int>::argument<0>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int& SGEXTN::CanOne::Action<int>::argument<0>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int*& SGEXTN::CanOne::Action<int>::argument<1>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template int*const& SGEXTN::CanOne::Action<int>::argument<1>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int& SGEXTN::CanOne::Action<int>::argument<2>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int& SGEXTN::CanOne::Action<int>::argument<2>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int*& SGEXTN::CanOne::Action<int>::argument<3>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template int*const& SGEXTN::CanOne::Action<int>::argument<3>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const int*& SGEXTN::CanOne::Action<int>::argument<4>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int*const& SGEXTN::CanOne::Action<int>::argument<4>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct& SGEXTN::CanOne::Action<int>::argument<5>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct& SGEXTN::CanOne::Action<int>::argument<5>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<6>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<6>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct& SGEXTN::CanOne::Action<int>::argument<7>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct& SGEXTN::CanOne::Action<int>::argument<7>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<8>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<8>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<int>::argument<9>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<int>::argument<9>(int (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;

template SGEXTN::CanOne::ConstMemberFunction<FunctionStruct, FunctionStruct>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)() const);
template const SGEXTN::CanOne::ConstMemberFunction<FunctionStruct, FunctionStruct>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)() const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)() const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)() const) const;

template SGEXTN::CanOne::ConstMemberFunction<FunctionStruct, FunctionStruct, int>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)(int) const);
template const SGEXTN::CanOne::ConstMemberFunction<FunctionStruct, FunctionStruct, int>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)(int) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)(int) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)(int) const) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (FunctionStruct::*)(int) const);
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (FunctionStruct::*)(int) const) const;

template SGEXTN::CanOne::ConstMemberFunction<FunctionStruct, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const SGEXTN::CanOne::ConstMemberFunction<FunctionStruct, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<FunctionStruct>::function(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::objectInstance(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<0>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<1>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<1>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int& SGEXTN::CanOne::Action<FunctionStruct>::argument<2>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int& SGEXTN::CanOne::Action<FunctionStruct>::argument<2>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<3>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<3>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const int*& SGEXTN::CanOne::Action<FunctionStruct>::argument<4>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<4>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<5>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<5>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<6>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<6>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<7>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct& SGEXTN::CanOne::Action<FunctionStruct>::argument<7>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<8>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<8>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<FunctionStruct>::argument<9>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<FunctionStruct>::argument<9>(FunctionStruct (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;

template SGEXTN::CanOne::ConstMemberFunction<const FunctionStruct*, FunctionStruct>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)() const);
template const SGEXTN::CanOne::ConstMemberFunction<const FunctionStruct*, FunctionStruct>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)() const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)() const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)() const) const;

template SGEXTN::CanOne::ConstMemberFunction<const FunctionStruct*, FunctionStruct, int>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)(int) const);
template const SGEXTN::CanOne::ConstMemberFunction<const FunctionStruct*, FunctionStruct, int>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)(int) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)(int) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)(int) const) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (FunctionStruct::*)(int) const);
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (FunctionStruct::*)(int) const) const;

template SGEXTN::CanOne::ConstMemberFunction<const FunctionStruct*, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const SGEXTN::CanOne::ConstMemberFunction<const FunctionStruct*, FunctionStruct, int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*>& SGEXTN::CanOne::Action<const FunctionStruct*>::function(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::objectInstance(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<0>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<1>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<1>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<2>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<2>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<3>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<3>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const int*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<4>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const int*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<4>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<5>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<5>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<6>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<6>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<7>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<7>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<8>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<8>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
template const FunctionStruct*& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<9>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const);
template const FunctionStruct*const& SGEXTN::CanOne::Action<const FunctionStruct*>::argument<9>(const FunctionStruct* (FunctionStruct::*)(int, int&, const int&, int*, const int*, FunctionStruct, FunctionStruct&, const FunctionStruct&, FunctionStruct*, const FunctionStruct*) const) const;
