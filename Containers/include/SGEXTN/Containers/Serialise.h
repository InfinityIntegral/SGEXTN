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
#include <SGEXTN/Containers/Array.h>

namespace SGEXTN {
namespace Containers {
class BuildLah_SGEXTN_Containers MemoryCopySerialise {
public:
    static void copySection(SGEXTN::Containers::Array<unsigned char>& mainArray, int& offset, const SGEXTN::Containers::Array<unsigned char>& section);
    static void copyOutSection(const SGEXTN::Containers::Array<unsigned char>& mainArray, int& offset, SGEXTN::Containers::Array<unsigned char>& destination);
};

template <typename... Ts> class Serialise {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialiseTogether(Ts... xs);
};

template <typename T> class Serialise<T> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(const T& x);
    [[nodiscard]] static T unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(const T& x);
};

template <typename T> class Serialise<SGEXTN::Containers::Array<T>> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(const SGEXTN::Containers::Array<T>& x);
    [[nodiscard]] static SGEXTN::Containers::Array<T> unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(const SGEXTN::Containers::Array<T>& x);
};

template <typename T> class Serialise<T*> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(const T* x);
    [[nodiscard]] static int lengthof(const T* x);
};

template <typename ReturnType, typename... ArgTypes> class Serialise<ReturnType (*)(ArgTypes...)> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(ReturnType (*x)(ArgTypes...));
    [[nodiscard]] static int lengthof(ReturnType (*x)(ArgTypes...));
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class Serialise<ReturnType (ClassName::*)(ArgTypes...)> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(ReturnType (ClassName::*x)(ArgTypes...));
    [[nodiscard]] static int lengthof(ReturnType (ClassName::*x)(ArgTypes...));
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class Serialise<ReturnType (ClassName::*)(ArgTypes...) const> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(ReturnType (ClassName::*x)(ArgTypes...) const);
    [[nodiscard]] static int lengthof(ReturnType (ClassName::*x)(ArgTypes...) const);
};

template <> class BuildLah_SGEXTN_Containers Serialise<bool> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(bool x);
    [[nodiscard]] static bool unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(bool x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<unsigned char> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(unsigned char x);
    [[nodiscard]] static unsigned char unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(unsigned char x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<short> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(short x);
    [[nodiscard]] static short unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(short x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<unsigned short> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(unsigned short x);
    [[nodiscard]] static unsigned short unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(unsigned short x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<int> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(int x);
    [[nodiscard]] static int unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(int x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<unsigned int> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(unsigned int x);
    [[nodiscard]] static unsigned int unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(unsigned int x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<long long> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(long long x);
    [[nodiscard]] static long long unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(long long x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<unsigned long long> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(unsigned long long x);
    [[nodiscard]] static unsigned long long unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(unsigned long long x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<float> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(float x);
    [[nodiscard]] static float unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(float x);
};

template <> class BuildLah_SGEXTN_Containers Serialise<double> {
public:
    [[nodiscard]] static SGEXTN::Containers::Array<unsigned char> serialise(double x);
    [[nodiscard]] static double unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success);
    [[nodiscard]] static int lengthof(double x);
};
}
}

#include <SGEXTN/Containers/private_api/Serialise_impl.h>
