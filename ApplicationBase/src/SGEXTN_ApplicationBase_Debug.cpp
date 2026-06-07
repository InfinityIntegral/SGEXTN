#include <SGEXTN_ApplicationBase_Debug.h>
#include <SGEXTN_ApplicationBase_OldString.h>
#include <SGEXTN_ApplicationBase_OldChar.h>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <iostream>
#include <QString>

SGEXTN::ApplicationBase::OldString SGEXTN::ApplicationBase::Debug::logFile = "";

SGEXTN::ApplicationBase::Debug::Debug(const SGEXTN::ApplicationBase::OldString& fileName, int lineNumber) : debugInfo(""), metaInfo("") {
    SGEXTN::ApplicationBase::OldString actualFileName = fileName.replace("\\", "/");
    actualFileName = actualFileName.substringRight(actualFileName.length() - actualFileName.findFirstFromRight("/") - 1);
    metaInfo = actualFileName + ", line " + SGEXTN::ApplicationBase::OldString::stringFromInt(lineNumber, 10);
}

SGEXTN::ApplicationBase::Debug::~Debug(){
    SGEXTN::ApplicationBase::OldString logData = "";
    if(debugInfo == ""){logData = SGEXTN::ApplicationBase::OldString("SG - ") + metaInfo;}
    else{logData = SGEXTN::ApplicationBase::OldString("SG") + debugInfo;}
    std::cerr << (*logData.private_data).toUtf8().constData() << "\n";
    if(SGEXTN::ApplicationBase::Debug::logFile != ""){
        QFile file(*SGEXTN::ApplicationBase::Debug::logFile.private_data);
        if(file.open(QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file);
            stream << (*logData.private_data) << "\n";
            file.close();
        }
    }
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(bool x){
    if(x == true){debugInfo += " - true";}
    else{debugInfo += " - false";}
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned char x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromInt(static_cast<int>(x), 10) + " or " + SGEXTN::ApplicationBase::OldChar(x);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(short x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromShort(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned short x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromUnsignedShort(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(int x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromInt(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned int x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromUnsignedInt(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(long long x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromLongLong(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned long long x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromUnsignedLongLong(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(float x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromFloat(x, SGEXTN::ApplicationBase::FloatDisplayFormat::Default, 5);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(double x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + SGEXTN::ApplicationBase::OldString::stringFromDouble(x, SGEXTN::ApplicationBase::FloatDisplayFormat::Default, 5);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const SGEXTN::ApplicationBase::OldChar& x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + x;
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const SGEXTN::ApplicationBase::OldString& x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + x;
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const char* x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + x;
    return (*this);
}

void SGEXTN::ApplicationBase::Debug::logCrashMessage(const char* msg){
    SG(msg);
}
