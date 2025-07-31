#include "sgxsingcorrectcore.h"
#include <QHash>
#include <QChar>
#include <QString>

QString SGXSingCorrectCore::correctionPrefix = "SG-\\";
QHash<QString, QChar>* SGXSingCorrectCore::database = nullptr;

QString SGXSingCorrectCore::correct(const QString &s){
    if(SGXSingCorrectCore::database == nullptr){return s;}
    QString s0 = "";
    bool maybeCommandActive = false;
    QString maybeCommand = "";
    for(int i=0; i<s.length(); i++){
        if(s[i] == SGXSingCorrectCore::correctionPrefix[0] && i <= s.length() - SGXSingCorrectCore::correctionPrefix.length() && s.mid(i, SGXSingCorrectCore::correctionPrefix.length()) == SGXSingCorrectCore::correctionPrefix){
            maybeCommandActive = true;
            i += static_cast<int>(SGXSingCorrectCore::correctionPrefix.length());
            while(i < s.length()){
                if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')){
                    maybeCommand += s[i];
                    i++;
                }
                else{
                    if((*SGXSingCorrectCore::database).contains(maybeCommand)){maybeCommand = (*SGXSingCorrectCore::database)[maybeCommand];}
                    else{maybeCommand = SGXSingCorrectCore::correctionPrefix + maybeCommand + s[i];}
                    s0 += maybeCommand;
                    maybeCommand = "";
                    maybeCommandActive = false;
                    break;
                }
            }
        }
        else{s0 += s[i];}
    }
    if(maybeCommandActive == true){s0 += (SGXSingCorrectCore::correctionPrefix + maybeCommand);}
    return s0;
}

void SGXSingCorrectCore::initialise(){
    SGXSingCorrectCore::database = new QHash<QString, QChar>();
    (*SGXSingCorrectCore::database).insert("SGhome", QChar(0x0378));
}

void SGXSingCorrectCore::terminate(){
    delete SGXSingCorrectCore::database;
    SGXSingCorrectCore::database = nullptr;
}
