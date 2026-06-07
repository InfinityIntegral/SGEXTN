#pragma once
#include <SGEXTN_CoreText_String.h>
#define SG SGEXTN::CoreText::Debug(__FILE__, __LINE__)

namespace SGEXTN {
namespace CoreText {
class BUILDLAH_DLL_SGEXTN_CoreText Debug {
public:
    Debug(const SGEXTN::CoreText::String& fileName, int lineNumber);
    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;
    Debug(Debug&&) = delete;
    Debug& operator=(Debug&&) = delete;
    ~Debug();
    SGEXTN::CoreText::String debugInfo;
    SGEXTN::CoreText::String metaInfo;
    template <typename T> Debug& operator()(const T& x);
    Debug& operator()(bool x);
    Debug& operator()(unsigned char x);
    Debug& operator()(short x);
    Debug& operator()(unsigned short x);
    Debug& operator()(int x);
    Debug& operator()(unsigned int x);
    Debug& operator()(long long x);
    Debug& operator()(unsigned long long x);
    Debug& operator()(float x);
    Debug& operator()(double x);
    Debug& operator()(const SGEXTN::CoreText::Character& x);
    Debug& operator()(const SGEXTN::CoreText::String& x);
    Debug& operator()(const char* x);
    static void logCrashMessage(const char* msg);
};
}
}

#include <private_api/SGEXTN_CoreText_Debug_impl.h>