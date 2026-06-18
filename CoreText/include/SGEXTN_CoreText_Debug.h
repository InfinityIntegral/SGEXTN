#pragma once
#include <SGEXTN_CoreText_String.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Vector;
}

namespace CoreText {
class Character;

enum class BuildLah_SGEXTN_CoreText DebugPrintMetadataMode : unsigned char {None, Line, All};
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
enum class BuildLah_SGEXTN_CoreText DebugPrintCCharMode : unsigned char {Byte, Character};
enum class BuildLah_SGEXTN_CoreText DebugPrintStringMode : unsigned char {Byte, CodePoint, String};
enum class BuildLah_SGEXTN_CoreText DebugPrintPointerMode : unsigned char {NullCheck, TryDeref};

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

#include <private_api/SGEXTN_CoreText_Debug_impl.h>

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
