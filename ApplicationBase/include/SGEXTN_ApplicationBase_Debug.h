#pragma once
#include <SGEXTN_ApplicationBase_String.h>
#define SG SGEXTN::ApplicationBase::Debug(__FILE__, __LINE__)

namespace SGEXTN {
namespace ApplicationBase {
class BUILDLAH_DLL_SGEXTN_ApplicationBase Debug {
public:
    Debug(const SGEXTN::ApplicationBase::String& fileName, int lineNumber);
    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;
    Debug(Debug&&) = delete;
    Debug& operator=(Debug&&) = delete;
    ~Debug();
    SGEXTN::ApplicationBase::String debugInfo;
    SGEXTN::ApplicationBase::String metaInfo;
    template <typename T> Debug& operator()(const T& x);
    Debug& operator()(bool x);
    Debug& operator()(char x);
    Debug& operator()(signed char x);
    Debug& operator()(unsigned char x);
    Debug& operator()(short x);
    Debug& operator()(unsigned short x);
    Debug& operator()(int x);
    Debug& operator()(unsigned int x);
    Debug& operator()(long long x);
    Debug& operator()(unsigned long long x);
    Debug& operator()(float x);
    Debug& operator()(double x);
    Debug& operator()(const SGEXTN::ApplicationBase::Char& x);
    Debug& operator()(const SGEXTN::ApplicationBase::String& x);
    Debug& operator()(const char* x);
    static SGEXTN::ApplicationBase::String logFile;
    static void logCrashMessage(const char* msg);
};
}
}

template <typename T> SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const T& x){
    return x.debugLog();
}
