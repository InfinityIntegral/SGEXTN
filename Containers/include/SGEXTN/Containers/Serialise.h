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
template <typename T> class Array;

template <typename... Ts> class Serialise {
public:
    [[nodiscard]] static bool sendOut(const Ts&... xs, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(Ts&... xs, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(const Ts&... xs);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <typename T> class Serialise<T> {
public:
    [[nodiscard]] static bool sendOut(const T& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(T& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(const T& x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <typename T> class Serialise<SGEXTN::Containers::Array<T>> {
public:
    [[nodiscard]] static bool sendOut(const SGEXTN::Containers::Array<T>& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(SGEXTN::Containers::Array<T>& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(const SGEXTN::Containers::Array<T>& x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<bool> {
public:
    [[nodiscard]] static bool sendOut(bool x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(bool& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(bool x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<unsigned char> {
public:
    [[nodiscard]] static bool sendOut(unsigned char x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(unsigned char& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(unsigned char x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<short> {
public:
    [[nodiscard]] static bool sendOut(short x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(short& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(short x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<unsigned short> {
public:
    [[nodiscard]] static bool sendOut(unsigned short x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(unsigned short& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(unsigned short x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<int> {
public:
    [[nodiscard]] static bool sendOut(int x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(int& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(int x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<unsigned int> {
public:
    [[nodiscard]] static bool sendOut(unsigned int x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(unsigned int& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(unsigned int x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<long long> {
public:
    [[nodiscard]] static bool sendOut(long long x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(long long& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(long long x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<unsigned long long> {
public:
    [[nodiscard]] static bool sendOut(unsigned long long x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(unsigned long long& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(unsigned long long x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<float> {
public:
    [[nodiscard]] static bool sendOut(float x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(float& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(float x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};

template <> class BuildLah_SGEXTN_Containers Serialise<double> {
public:
    [[nodiscard]] static bool sendOut(double x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(double& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int sizeOut(double x);
    [[nodiscard]] static int sizeIn(SGEXTN::Containers::Span<unsigned char> data);
};
}

#include <SGEXTN/Containers/private_api/Serialise_impl.h>
