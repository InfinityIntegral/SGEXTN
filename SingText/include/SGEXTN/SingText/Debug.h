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

#ifndef SGEXTN_internal_permanentAllowDebug
#pragma message("debug header included")
#endif

#include <SGEXTN/SingText/String.h>

namespace SGEXTN::Containers {
template <typename T> class Array;
template <typename T> class Vector;
}

namespace SGEXTN::SingText {
class Character;
class Debug;

class BuildLah_SGEXTN_SingText DebugPrintIntegerMode {
private:
    friend class SGEXTN::SingText::Debug;
    int base_;
public:
    explicit DebugPrintIntegerMode(int base);
};

class BuildLah_SGEXTN_SingText DebugPrintFloatingPointMode {
private:
    friend class SGEXTN::SingText::Debug;
    int base_;
    SGEXTN::SingText::FloatPrecisionFormat format_;
    int precision_;
public:
    explicit DebugPrintFloatingPointMode(int base, SGEXTN::SingText::FloatPrecisionFormat format, int precision);
};

enum class DebugPrintCCharMode : unsigned char {
    Byte = 1,
    Character = 2
};

enum class DebugPrintStringMode : unsigned char {
    Byte = 1,
    CodePoint = 2,
    String = 3
};

enum class DebugPrintPointerMode : unsigned char {
    NullCheck = 1,
    TryDeref = 2
};

class DebugLogFunctionRegistrarInstance;
class DebugDefaultModeOverride;

class BuildLah_SGEXTN_SingText Debug {
private:
    friend class SGEXTN::SingText::DebugLogFunctionRegistrarInstance;
    friend class SGEXTN::SingText::DebugDefaultModeOverride;
    static SGEXTN::Containers::Vector<void (*)(const char*)>* logFunctionList;
    static void logToCerr(const char* msg);
    static SGEXTN::SingText::DebugPrintIntegerMode defaultIntegerMode;
    static SGEXTN::SingText::DebugPrintFloatingPointMode defaultFloatingPointMode;
    static SGEXTN::SingText::DebugPrintCCharMode defaultCCharMode;
    static SGEXTN::SingText::DebugPrintStringMode defaultStringMode;
    static SGEXTN::SingText::DebugPrintPointerMode defaultPointerMode;
    SGEXTN::SingText::String debugInfo_;
    SGEXTN::SingText::String fileName_;
    SGEXTN::SingText::String lineNumber_;
    SGEXTN::SingText::DebugPrintIntegerMode integerMode_;
    SGEXTN::SingText::DebugPrintFloatingPointMode floatingPointMode_;
    SGEXTN::SingText::DebugPrintCCharMode cCharMode_;
    SGEXTN::SingText::DebugPrintStringMode stringMode_;
    SGEXTN::SingText::DebugPrintPointerMode pointerMode_;
    template <typename T> SGEXTN::SingText::String debugPrint(const T& x) const;
    template <typename T> SGEXTN::SingText::String debugPrint(const SGEXTN::Containers::Array<T>& x) const;
    SGEXTN::SingText::String debugPrint(bool x) const;
    SGEXTN::SingText::String debugPrint(unsigned char x) const;
    SGEXTN::SingText::String debugPrint(short x) const;
    SGEXTN::SingText::String debugPrint(unsigned short x) const;
    SGEXTN::SingText::String debugPrint(int x) const;
    SGEXTN::SingText::String debugPrint(unsigned int x) const;
    SGEXTN::SingText::String debugPrint(long long x) const;
    SGEXTN::SingText::String debugPrint(unsigned long long x) const;
    SGEXTN::SingText::String debugPrint(float x) const;
    SGEXTN::SingText::String debugPrint(double x) const;
    SGEXTN::SingText::String debugPrint(const SGEXTN::SingText::Character& x) const;
    SGEXTN::SingText::String debugPrint(const SGEXTN::SingText::String& x) const;
    SGEXTN::SingText::String debugPrint(char x) const;
    SGEXTN::SingText::String debugPrint(const char* x) const;
    static bool registerFunction;
public:
    explicit Debug(const SGEXTN::SingText::String& fileName, int lineNumber);
    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;
    Debug(Debug&&) = delete;
    Debug& operator=(Debug&&) = delete;
    ~Debug();
    template <typename T> Debug& operator()(const T& x);
    Debug& operator()(SGEXTN::SingText::DebugPrintIntegerMode mode);
    Debug& operator()(SGEXTN::SingText::DebugPrintFloatingPointMode mode);
    Debug& operator()(SGEXTN::SingText::DebugPrintCCharMode mode);
    Debug& operator()(SGEXTN::SingText::DebugPrintStringMode mode);
    Debug& operator()(SGEXTN::SingText::DebugPrintPointerMode mode);
};

class BuildLah_SGEXTN_SingText DebugLogFunctionRegistrarInstance {
public:
    explicit DebugLogFunctionRegistrarInstance(void (*func)(const char*));
};

class BuildLah_SGEXTN_SingText DebugDefaultModeOverride {
private:
    SGEXTN::SingText::DebugPrintIntegerMode previousIntegerMode_;
    SGEXTN::SingText::DebugPrintFloatingPointMode previousFloatingPointMode_;
    SGEXTN::SingText::DebugPrintCCharMode previousCCharMode_;
    SGEXTN::SingText::DebugPrintStringMode previousStringMode_;
    SGEXTN::SingText::DebugPrintPointerMode previousPointerMode_;
public:
    explicit DebugDefaultModeOverride(SGEXTN::SingText::DebugPrintIntegerMode newIntegerMode, SGEXTN::SingText::DebugPrintFloatingPointMode newFloatingPointMode, SGEXTN::SingText::DebugPrintCCharMode newCCharMode, SGEXTN::SingText::DebugPrintStringMode newStringMode, SGEXTN::SingText::DebugPrintPointerMode newPointerMode);
    DebugDefaultModeOverride(const DebugDefaultModeOverride&) = delete;
    DebugDefaultModeOverride& operator=(const DebugDefaultModeOverride&) = delete;
    DebugDefaultModeOverride(DebugDefaultModeOverride&&) = delete;
    DebugDefaultModeOverride& operator=(DebugDefaultModeOverride&&) = delete;
    ~DebugDefaultModeOverride();
};
}

#include <SGEXTN/SingText/private_api/Debug_impl.h>

#ifndef SGEXTN_NO_DEFINE_DEBUG_MACRO
#define SG SGEXTN::SingText::Debug(__FILE__, __LINE__)
#endif
