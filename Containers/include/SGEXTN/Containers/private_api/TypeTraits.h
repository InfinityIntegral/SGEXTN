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
namespace Containers {
template <typename T> class IsPointer {};
template <typename T> class IsPointer<T*> {public: static const bool isPointer = true;};
template <typename ReturnType, typename... ArgTypes> class IsPointer<ReturnType (*)(ArgTypes...)> {public: static const bool isPointer = true;};
template <typename ReturnType, typename ClassName, typename... ArgTypes> class IsPointer<ReturnType (ClassName::*)(ArgTypes...)> {public: static const bool isPointer = true;};
template <typename ReturnType, typename ClassName, typename... ArgTypes> class IsPointer<ReturnType (ClassName::*)(ArgTypes...) const> {public: static const bool isPointer = true;};

template <typename T> class IsObjectPointer {};
template <typename T> class IsObjectPointer<T*> {public: static const bool isPointer = true;};

template <typename T1, typename T2> class IsSameType {};
template <typename T> class IsSameType<T, T> {public: static const bool same = true;};

template <typename T, bool B> class IsTrue {};
template <typename T> class IsTrue<T, true> {public: static const bool isTrue = true;};

template <typename T> class CreateInstance {public: static T&& getInstance() noexcept;};

template <typename T> class CreateAssignable {public: static T& getInstance() noexcept;};
}
}
