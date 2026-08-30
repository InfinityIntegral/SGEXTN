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

namespace SGEXTN::CanIsCanCannotAlsoMustCan {
template <int Index, typename ClassName, typename MemberType, MemberType Target> class PrivateFunctionTheftIsNotACrime;
template <int Index, typename ClassName, typename MemberType, MemberType ClassName::* Target> class PrivateVariableTheftIsNotACrime;

template <int Index, typename ClassName, typename MemberType> class FunctionKaypohOne {
private:
    template <int OtherIndex, typename OtherClassName, typename OtherMemberType, OtherMemberType OtherTarget> friend class SGEXTN::CanIsCanCannotAlsoMustCan::PrivateFunctionTheftIsNotACrime;
    static MemberType iStealPointerThenIPutIntoHere;
public:
    [[nodiscard]] static MemberType youKaypohUsePrivateFunctionForWhatLaterBreakOtherLibraryCodeThenHow();
};

template <int Index, typename ClassName, typename MemberType, MemberType Target> class PrivateFunctionTheftIsNotACrime {
private:
    static bool iUseThisThenIGotPointerLiao;
};

template <int Index, typename ClassName, typename MemberType> class VariableKaypohOne {
private:
    template <int OtherIndex, typename OtherClassName, typename OtherMemberType, OtherMemberType OtherClassName::*OtherTarget> friend class SGEXTN::CanIsCanCannotAlsoMustCan::PrivateVariableTheftIsNotACrime;
    static MemberType ClassName::*iStealOffsetThenIPutIntoHere;
public:
    [[nodiscard]] static MemberType& youKaypohLookAtPrivateMemberForWhatLaterBreakOtherLibraryCodeThenHow(ClassName& x);
    [[nodiscard]] static const MemberType& youKaypohLookAtPrivateMemberForWhatLaterBreakOtherLibraryCodeThenHow(const ClassName& x);
};

template <int Index, typename ClassName, typename MemberType, MemberType ClassName::* Target> class PrivateVariableTheftIsNotACrime {
private:
    static bool iUseThisThenIGotOffsetLiao;
};
}

template <int Index, typename ClassName, typename MemberType> constinit MemberType SGEXTN::CanIsCanCannotAlsoMustCan::FunctionKaypohOne<Index, ClassName, MemberType>::iStealPointerThenIPutIntoHere = nullptr;

template <int Index, typename ClassName, typename MemberType> MemberType SGEXTN::CanIsCanCannotAlsoMustCan::FunctionKaypohOne<Index, ClassName, MemberType>::youKaypohUsePrivateFunctionForWhatLaterBreakOtherLibraryCodeThenHow(){
    return SGEXTN::CanIsCanCannotAlsoMustCan::FunctionKaypohOne<Index, ClassName, MemberType>::iStealPointerThenIPutIntoHere;
}

template <int Index, typename ClassName, typename MemberType, MemberType Target> bool SGEXTN::CanIsCanCannotAlsoMustCan::PrivateFunctionTheftIsNotACrime<Index, ClassName, MemberType, Target>::iUseThisThenIGotPointerLiao = (SGEXTN::CanIsCanCannotAlsoMustCan::FunctionKaypohOne<Index, ClassName, MemberType>::iStealPointerThenIPutIntoHere = Target, true);

template <int Index, typename ClassName, typename MemberType> constinit MemberType ClassName::* SGEXTN::CanIsCanCannotAlsoMustCan::VariableKaypohOne<Index, ClassName, MemberType>::iStealOffsetThenIPutIntoHere = nullptr;

template <int Index, typename ClassName, typename MemberType> MemberType& SGEXTN::CanIsCanCannotAlsoMustCan::VariableKaypohOne<Index, ClassName, MemberType>::youKaypohLookAtPrivateMemberForWhatLaterBreakOtherLibraryCodeThenHow(ClassName& x){
    return x.*(SGEXTN::CanIsCanCannotAlsoMustCan::VariableKaypohOne<Index, ClassName, MemberType>::iStealOffsetThenIPutIntoHere);
}

template <int Index, typename ClassName, typename MemberType> const MemberType& SGEXTN::CanIsCanCannotAlsoMustCan::VariableKaypohOne<Index, ClassName, MemberType>::youKaypohLookAtPrivateMemberForWhatLaterBreakOtherLibraryCodeThenHow(const ClassName& x){
    return x.*(SGEXTN::CanIsCanCannotAlsoMustCan::VariableKaypohOne<Index, ClassName, MemberType>::iStealOffsetThenIPutIntoHere);
}

template <int Index, typename ClassName, typename MemberType, MemberType ClassName::* Target> bool SGEXTN::CanIsCanCannotAlsoMustCan::PrivateVariableTheftIsNotACrime<Index, ClassName, MemberType, Target>::iUseThisThenIGotOffsetLiao = (SGEXTN::CanIsCanCannotAlsoMustCan::VariableKaypohOne<Index, ClassName, MemberType>::iStealOffsetThenIPutIntoHere = Target, true);
