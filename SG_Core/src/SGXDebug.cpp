#include <SGXDebug.h>
#include <QDebug>
#include <SGXString.h>
#include <SGXChar.h>
#include <SGXColourRGBA.h>
#include <SGXColourHSLA.h>
#include <SGXIdentifier.h>
#include <SGXTimeStamp.h>
#include <SGXVector2.h>
#include <QString>
#include <cstdio>
#include <qlogging.h>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

SGXString SGXDebug::logFile = "";

SGXDebug::SGXDebug(const SGXString& fileName, int lineNumber){
    debugInfo = "";
    metaInfo = "";
    for(int i=fileName.length()-1; i>=0; i--){
        if(fileName.at(i) == '/' || fileName.at(i) == '\\'){
            metaInfo = (fileName.substring(i+1, fileName.length()-i-1) + ", line " + SGXString::intToString(lineNumber));
            break;
        }
    }
    if(metaInfo == ""){metaInfo = (fileName + ", line" + SGXString::intToString(lineNumber));}
}

SGXDebug::~SGXDebug(){
    SGXString logData = "";
    if(debugInfo == ""){logData = SGXString("SG - ") + metaInfo;}
    else{logData = SGXString("SG") + debugInfo;}
    qDebug().noquote() << (*logData.data);
    if(SGXDebug::logFile != ""){
        QFile file(*SGXDebug::logFile.data);
        if(file.open(QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file);
            stream << (*logData.data) << "\n";
            file.close();
        }
    }
}

SGXDebug& SGXDebug::operator()(bool x){
    if(x == true){debugInfo += " - true";}
    else{debugInfo += " - false";}
    return (*this);
}

SGXDebug& SGXDebug::operator()(char x){
    debugInfo += (SGXString(" - ") + SGXString::intToString(static_cast<int>(x)) + " or " + SGXChar(x));
    return (*this);
}

SGXDebug& SGXDebug::operator()(int x){
    debugInfo += (SGXString(" - ") + SGXString::intToString(x));
    return (*this);
}

SGXDebug& SGXDebug::operator()(unsigned int x){
    debugInfo +=  (SGXString(" - ") + SGXString::unsignedIntToString(x));
    return (*this);
}

SGXDebug& SGXDebug::operator()(long long x){
    debugInfo += (SGXString(" - ") + SGXString::longLongToString(x));
    return (*this);
}

SGXDebug& SGXDebug::operator()(unsigned long long x){
    debugInfo += (SGXString(" - ") + SGXString::unsignedLongLongToString(x));
    return (*this);
}

SGXDebug& SGXDebug::operator()(float x){
    debugInfo += (SGXString(" - ") + SGXString::floatToString(x));
    return (*this);
}

SGXDebug& SGXDebug::operator()(double x){
    debugInfo += (SGXString(" - ") + SGXString::doubleToString(x));
    return (*this);
}

SGXDebug& SGXDebug::operator()(const SGXChar& x){
    debugInfo += (SGXString(" - ") + x);
    return (*this);
}

SGXDebug& SGXDebug::operator()(const SGXString& x){
    debugInfo += (SGXString(" - ") + x);
    return (*this);
}

SGXDebug& SGXDebug::operator()(const SGXColourRGBA& x){
    debugInfo += (SGXString(" - ") + x.getStringForPrintingRGBAHex() + " red " + SGXString::intToString(x.getRed()) + " green " + SGXString::intToString(x.getGreen()) + " blue " + SGXString::intToString(x.getBlue()) + " transparency " + SGXString::intToString(x.getTransparency()));
    return (*this);
}

SGXDebug& SGXDebug::operator()(const SGXColourHSLA& x){
    debugInfo += (SGXString(" - ") + "hue " + SGXString::floatToStringDecimalPlaces(x.h, 2) + " saturation " + SGXString::floatToStringDecimalPlaces(x.s, 2) + " lightness " + SGXString::floatToStringDecimalPlaces(x.l, 2) + " transparency " + SGXString::floatToStringDecimalPlaces(x.a, 2));
    return (*this);
}

SGXDebug& SGXDebug::operator()(const SGXIdentifier& x){
    const SGXString s = x.getStringForPrinting();
    SGXString s0 = "";
    for(int i=0; i<s.length()/4; i++){
        s0 += s.substring(4 * i, 4) + "-";
    }
    s0 = s0.substringLeft(s0.length() - 1);
    debugInfo += (SGXString(" - ") + s0);
    return (*this);
}

SGXDebug& SGXDebug::operator()(const SGXTimeStamp& x){
    debugInfo += (SGXString(" - ") + x.getString());
    return (*this);
}

SGXDebug& SGXDebug::operator()(const SGXVector2& x){
    debugInfo += (SGXString(" - ") + "(" + SGXString::floatToString(x.x) + ", " + SGXString::floatToString(x.y) + ")");
    return (*this);
}

SGXDebug& SGXDebug::operator()(void* x){
    char* pointerAsCString = new char[20];
    std::sprintf(pointerAsCString, "%p", x); // NOLINT(cppcoreguidelines-pro-type-vararg)
    debugInfo += (SGXString(" - ") + pointerAsCString);
    delete[] pointerAsCString;
    return (*this);
}

SGXDebug& SGXDebug::operator()(const char* x){
    debugInfo += (SGXString(" - ") + x);
    return (*this);
}
