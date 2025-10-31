#ifndef SGXDEBUG_H
#define SGXDEBUG_H

#include <SGXString.h>

#include <private_api_Core/SG_Build_Core.h>

#define SG SGXDebug(__FILE__, __LINE__)

class SGXChar;
class SGXColourRGBA;
class SGXColourHSLA;
class SGXIdentifier;
class SGXTimeStamp;
class SGXVector2;
class SG_CORE_DLL SGXDebug {
public:
    SGXDebug(const SGXString& fileName, int lineNumber);
    SGXDebug(const SGXDebug&) = delete;
    SGXDebug& operator=(const SGXDebug&) = delete;
    SGXDebug(SGXDebug&&) = delete;
    SGXDebug& operator=(SGXDebug&&) = delete;
    ~SGXDebug();
    SGXString debugInfo;
    SGXString metaInfo;
    SGXDebug& operator()(bool x);
    SGXDebug& operator()(char x);
    SGXDebug& operator()(int x);
    SGXDebug& operator()(unsigned int x);
    SGXDebug& operator()(long long x);
    SGXDebug& operator()(unsigned long long x);
    SGXDebug& operator()(float x);
    SGXDebug& operator()(double x);
    SGXDebug& operator()(const SGXChar& x);
    SGXDebug& operator()(const SGXString& x);
    SGXDebug& operator()(const SGXColourRGBA& x);
    SGXDebug& operator()(const SGXColourHSLA& x);
    SGXDebug& operator()(const SGXIdentifier& x);
    SGXDebug& operator()(const SGXTimeStamp& x);
    SGXDebug& operator()(const SGXVector2& x);
    SGXDebug& operator()(void* x);
    SGXDebug& operator()(const char* x);
};

#endif // SGXDEBUG_H
