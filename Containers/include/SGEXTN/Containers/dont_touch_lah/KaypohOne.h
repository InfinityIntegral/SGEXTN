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

namespace SGEXTN::KaypohOne {
template <int Index, typename ClassName, typename MemberType, MemberType Target> class StealMemberFunction;

template <int Index, typename ClassName, typename MemberType> class MemberFunction {
private:
    template <int OtherIndex, typename OtherClassName, typename OtherMemberType, OtherMemberType OtherTarget> friend class SGEXTN::KaypohOne::StealMemberFunction;
    static MemberType pointer;
public:
    [[nodiscard]] static MemberType beKaypoh();
};

template <int Index, typename ClassName, typename MemberType, MemberType Target> class StealMemberFunction {
private:
    static bool activation;
};
}

template <int Index, typename ClassName, typename MemberType> constinit MemberType SGEXTN::KaypohOne::MemberFunction<Index, ClassName, MemberType>::pointer = nullptr;

template <int Index, typename ClassName, typename MemberType> MemberType SGEXTN::KaypohOne::MemberFunction<Index, ClassName, MemberType>::beKaypoh(){
    return SGEXTN::KaypohOne::MemberFunction<Index, ClassName, MemberType>::pointer;
}

template <int Index, typename ClassName, typename MemberType, MemberType Target> bool SGEXTN::KaypohOne::StealMemberFunction<Index, ClassName, MemberType, Target>::activation = (SGEXTN::KaypohOne::MemberFunction<Index, ClassName, MemberType>::pointer = Target, true);

namespace SGEXTN::KaypohOne {
template <int Index, typename ClassName, typename MemberType, MemberType ClassName::* Target> class StealMemberVariable;

template <int Index, typename ClassName, typename MemberType> class MemberVariable {
private:
    template <int OtherIndex, typename OtherClassName, typename OtherMemberType, OtherMemberType OtherClassName::*OtherTarget> friend class SGEXTN::KaypohOne::StealMemberVariable;
    static MemberType ClassName::*offset;
public:
    [[nodiscard]] static MemberType& beKaypoh(ClassName& x);
    [[nodiscard]] static const MemberType& beKaypoh(const ClassName& x);
};

template <int Index, typename ClassName, typename MemberType, MemberType ClassName::* Target> class StealMemberVariable {
private:
    static bool activation;
};
}

template <int Index, typename ClassName, typename MemberType> constinit MemberType ClassName::* SGEXTN::KaypohOne::MemberVariable<Index, ClassName, MemberType>::offset = nullptr;

template <int Index, typename ClassName, typename MemberType> MemberType& SGEXTN::KaypohOne::MemberVariable<Index, ClassName, MemberType>::beKaypoh(ClassName& x){
    return x.*(SGEXTN::KaypohOne::MemberVariable<Index, ClassName, MemberType>::offset);
}

template <int Index, typename ClassName, typename MemberType> const MemberType& SGEXTN::KaypohOne::MemberVariable<Index, ClassName, MemberType>::beKaypoh(const ClassName& x){
    return x.*(SGEXTN::KaypohOne::MemberVariable<Index, ClassName, MemberType>::offset);
}

template <int Index, typename ClassName, typename MemberType, MemberType ClassName::* Target> bool SGEXTN::KaypohOne::StealMemberVariable<Index, ClassName, MemberType, Target>::activation = (SGEXTN::KaypohOne::MemberVariable<Index, ClassName, MemberType>::offset = Target, true);

namespace SGEXTN::KaypohOne {
template <int Index, typename ClassName, typename MemberType, MemberType Target> class StealStaticFunction;

template <int Index, typename ClassName, typename MemberType> class StaticFunction {
private:
    template <int OtherIndex, typename OtherClassName, typename OtherMemberType, OtherMemberType OtherTarget> friend class SGEXTN::KaypohOne::StealStaticFunction;
    static MemberType pointer;
public:
    [[nodiscard]] static MemberType beKaypoh();
};

template <int Index, typename ClassName, typename MemberType, MemberType Target> class StealStaticFunction {
private:
    static bool activation;
};
}

template <int Index, typename ClassName, typename MemberType> constinit MemberType SGEXTN::KaypohOne::StaticFunction<Index, ClassName, MemberType>::pointer = nullptr;

template <int Index, typename ClassName, typename MemberType> MemberType SGEXTN::KaypohOne::StaticFunction<Index, ClassName, MemberType>::beKaypoh(){
    return SGEXTN::KaypohOne::StaticFunction<Index, ClassName, MemberType>::pointer;
}

template <int Index, typename ClassName, typename MemberType, MemberType Target> bool SGEXTN::KaypohOne::StealStaticFunction<Index, ClassName, MemberType, Target>::activation = (SGEXTN::KaypohOne::StaticFunction<Index, ClassName, MemberType>::pointer = Target, true);

namespace SGEXTN::KaypohOne {
template <int Index, typename ClassName, typename MemberType, MemberType* Target> class StealStaticVariable;

template <int Index, typename ClassName, typename MemberType> class StaticVariable {
private:
    template <int OtherIndex, typename OtherClassName, typename OtherMemberType, OtherMemberType* OtherTarget> friend class SGEXTN::KaypohOne::StealStaticVariable;
    static MemberType* pointer;
public:
    [[nodiscard]] static MemberType& beKaypoh();
};

template <int Index, typename ClassName, typename MemberType, MemberType* Target> class StealStaticVariable {
private:
    static bool activation;
};
}

template <int Index, typename ClassName, typename MemberType> constinit MemberType* SGEXTN::KaypohOne::StaticVariable<Index, ClassName, MemberType>::pointer = nullptr;

template <int Index, typename ClassName, typename MemberType> MemberType& SGEXTN::KaypohOne::StaticVariable<Index, ClassName, MemberType>::beKaypoh(){
    return (*(SGEXTN::KaypohOne::StaticVariable<Index, ClassName, MemberType>::pointer));
}

template <int Index, typename ClassName, typename MemberType, MemberType* Target> bool SGEXTN::KaypohOne::StealStaticVariable<Index, ClassName, MemberType, Target>::activation = (SGEXTN::KaypohOne::StaticVariable<Index, ClassName, MemberType>::pointer = Target, true);
