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
#pragma message("debug header included in __FILE__")
#endif

#include <SGEXTN/CoreText/String.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Array;
template <typename T> class Vector;
}

namespace CoreText {
class Character;

enum class DebugPrintMetadataMode : unsigned char {
    None = 1,
    Line = 2,
    All = 3
};

class BuildLah_SGEXTN_CoreText DebugPrintIntegerMode {
public:
    DebugPrintIntegerMode(int base);
    int base;
};

class BuildLah_SGEXTN_CoreText DebugPrintFloatingPointMode {
public:
    DebugPrintFloatingPointMode(int base, SGEXTN::CoreText::FloatPrecisionFormat format, int precision);
    int base;
    SGEXTN::CoreText::FloatPrecisionFormat format;
    int precision;
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

class BuildLah_SGEXTN_CoreText Debug {
public:
    Debug(const SGEXTN::CoreText::String& fileName, int lineNumber);
    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;
    Debug(Debug&&) = delete;
    Debug& operator=(Debug&&) = delete;
    ~Debug();
    static SGEXTN::Containers::Vector<void (*)(const char*)>* logFunctionList;
    static void logToCerr(const char* msg);
    SGEXTN::CoreText::String debugInfo;
    SGEXTN::CoreText::String fileName;
    SGEXTN::CoreText::String lineNumber;
    SGEXTN::CoreText::DebugPrintMetadataMode metadataMode;
    SGEXTN::CoreText::DebugPrintIntegerMode integerMode;
    SGEXTN::CoreText::DebugPrintFloatingPointMode floatingPointMode;
    SGEXTN::CoreText::DebugPrintCCharMode cCharMode;
    SGEXTN::CoreText::DebugPrintStringMode stringMode;
    SGEXTN::CoreText::DebugPrintPointerMode pointerMode;
    template <typename T> SGEXTN::CoreText::String debugPrint(const T& x) const;
    template <typename T> SGEXTN::CoreText::String debugPrint(const T* x) const;
    template <typename T> SGEXTN::CoreText::String debugPrint(T* x) const;
    template <typename ReturnType, typename... ArgTypes> SGEXTN::CoreText::String debugPrint(ReturnType (*x)(ArgTypes...)) const;
    template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CoreText::String debugPrint(ReturnType (ClassName::*x)(ArgTypes...)) const;
    template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CoreText::String debugPrint(ReturnType (ClassName::*x)(ArgTypes...) const) const;
    template <typename T> SGEXTN::CoreText::String debugPrint(const SGEXTN::Containers::Array<T>& x) const;
    SGEXTN::CoreText::String debugPrint(bool x) const;
    SGEXTN::CoreText::String debugPrint(unsigned char x) const;
    SGEXTN::CoreText::String debugPrint(short x) const;
    SGEXTN::CoreText::String debugPrint(unsigned short x) const;
    SGEXTN::CoreText::String debugPrint(int x) const;
    SGEXTN::CoreText::String debugPrint(unsigned int x) const;
    SGEXTN::CoreText::String debugPrint(long long x) const;
    SGEXTN::CoreText::String debugPrint(unsigned long long x) const;
    SGEXTN::CoreText::String debugPrint(float x) const;
    SGEXTN::CoreText::String debugPrint(double x) const;
    SGEXTN::CoreText::String debugPrint(const SGEXTN::CoreText::Character& x) const;
    SGEXTN::CoreText::String debugPrint(const SGEXTN::CoreText::String& x) const;
    SGEXTN::CoreText::String debugPrint(char x) const;
    SGEXTN::CoreText::String debugPrint(const char* x) const;
    template <typename T> Debug& operator()(const T& x);
    Debug& operator()(SGEXTN::CoreText::DebugPrintMetadataMode mode);
    Debug& operator()(SGEXTN::CoreText::DebugPrintIntegerMode mode);
    Debug& operator()(SGEXTN::CoreText::DebugPrintFloatingPointMode mode);
    Debug& operator()(SGEXTN::CoreText::DebugPrintCCharMode mode);
    Debug& operator()(SGEXTN::CoreText::DebugPrintStringMode mode);
    Debug& operator()(SGEXTN::CoreText::DebugPrintPointerMode mode);
};

class BuildLah_SGEXTN_CoreText DebugLogFunctionRegistrarInstance {
public:
    DebugLogFunctionRegistrarInstance(void (*func)(const char*));
};
}
}

#include <SGEXTN/CoreText/private_api/Debug_impl.h>

#define SGEXTN_DEBUG_PRINT SGEXTN::CoreText::Debug(__FILE__, __LINE__)
#define SGEXTN_DEBUG_PRINT_LINE_LOG SGEXTN::CoreText::Debug(__FILE__, __LINE__)(SGEXTN::CoreText::DebugPrintMetadataMode::Line)
#define SGEXTN_DEBUG_PRINT_FULL_LOG SGEXTN::CoreText::Debug(__FILE__, __LINE__)(SGEXTN::CoreText::DebugPrintMetadataMode::All)

#ifndef SGEXTN_NO_DEFINE_SHORTCUT_MACROS
#ifndef SG
#define SG SGEXTN::CoreText::Debug(__FILE__, __LINE__)
#endif

#ifndef SG_L
#define SG_L SGEXTN::CoreText::Debug(__FILE__, __LINE__)(SGEXTN::CoreText::DebugPrintMetadataMode::Line)
#endif

#ifndef SG_A
#define SG_A SGEXTN::CoreText::Debug(__FILE__, __LINE__)(SGEXTN::CoreText::DebugPrintMetadataMode::All)
#endif
#endif
