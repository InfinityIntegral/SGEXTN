#include <SGEXTN_ApplicationBase_Debug.h>
#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_ApplicationBase_Char.h>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <iostream>
#include <QString>

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::Debug::logFile = "";

SGEXTN::ApplicationBase::Debug::Debug(const SGEXTN::ApplicationBase::String& fileName, int lineNumber){
    debugInfo = "";
    SGEXTN::ApplicationBase::String actualFileName = fileName.replace("\\", "/");
    actualFileName = actualFileName.substringRight(actualFileName.length() - actualFileName.findFirstFromRight("/") - 1);
    metaInfo = actualFileName + ", line " + SGEXTN::ApplicationBase::String::stringFromInt(lineNumber, 10);
}

SGEXTN::ApplicationBase::Debug::~Debug(){
    SGEXTN::ApplicationBase::String logData = "";
    if(debugInfo == ""){logData = SGEXTN::ApplicationBase::String("SG - ") + metaInfo;}
    else{logData = SGEXTN::ApplicationBase::String("SG") + debugInfo;}
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

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(char x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromInt(static_cast<int>(x), 10) + " or " + SGEXTN::ApplicationBase::Char(x);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(signed char x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromInt(static_cast<int>(x), 10) + " or " + SGEXTN::ApplicationBase::Char(static_cast<char>(x));
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned char x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromInt(static_cast<int>(x), 10) + " or " + SGEXTN::ApplicationBase::Char(static_cast<char>(x));
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(short x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromShort(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned short x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromUnsignedShort(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(int x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromInt(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned int x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromUnsignedInt(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(long long x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromLongLong(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned long long x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromUnsignedLongLong(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(float x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromFloat(x, SGEXTN::ApplicationBase::FloatDisplayFormat::Default, 5);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(double x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromDouble(x, SGEXTN::ApplicationBase::FloatDisplayFormat::Default, 5);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const SGEXTN::ApplicationBase::Char& x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + x;
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const SGEXTN::ApplicationBase::String& x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + x;
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const char* x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + x;
    return (*this);
}

void SGEXTN::ApplicationBase::Debug::logCrashMessage(const char* msg){
    SG(msg);
}
