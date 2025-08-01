#include "sgxsingcorrectcore.h"
#include <QHash>
#include <QChar>
#include <QString>
#include "sgxsingcorrectquickinterface.h"

QString SGXSingCorrectCore::correctionPrefix = "SG-\\";
QHash<QString, QChar>* SGXSingCorrectCore::database = nullptr;
SGXSingCorrectQuickInterface* SGXSingCorrectCore::instance = nullptr;

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
    (*SGXSingCorrectCore::database).insert("lparen", QChar(0x0028));
    (*SGXSingCorrectCore::database).insert("rparen", QChar(0x0029));
    (*SGXSingCorrectCore::database).insert("lbrack", QChar(0x005B));
    (*SGXSingCorrectCore::database).insert("rbrack", QChar(0x005D));
    (*SGXSingCorrectCore::database).insert("lbrace", QChar(0x007B));
    (*SGXSingCorrectCore::database).insert("rbrace", QChar(0x007D));
    (*SGXSingCorrectCore::database).insert("langle", QChar(0x27E8));
    (*SGXSingCorrectCore::database).insert("rangle", QChar(0x27E9));
    (*SGXSingCorrectCore::database).insert("vert", QChar(0x007C));
    (*SGXSingCorrectCore::database).insert("Vert", QChar(0x2225));
    (*SGXSingCorrectCore::database).insert("lvert", QChar(0x007C));
    (*SGXSingCorrectCore::database).insert("rvert", QChar(0x007C));
    (*SGXSingCorrectCore::database).insert("lVert", QChar(0x2225));
    (*SGXSingCorrectCore::database).insert("rVert", QChar(0x2225));
    (*SGXSingCorrectCore::database).insert("lang", QChar(0x27E8));
    (*SGXSingCorrectCore::database).insert("rang", QChar(0x27E9));
    (*SGXSingCorrectCore::database).insert("lt", QChar(0x003C));
    (*SGXSingCorrectCore::database).insert("gt", QChar(0x003E));
    (*SGXSingCorrectCore::database).insert("lceil", QChar(0x2308));
    (*SGXSingCorrectCore::database).insert("rceil", QChar(0x2309));
    (*SGXSingCorrectCore::database).insert("lfloor", QChar(0x230A));
    (*SGXSingCorrectCore::database).insert("rfloor", QChar(0x230B));
    (*SGXSingCorrectCore::database).insert("lgroup", QChar(0x0028));
    (*SGXSingCorrectCore::database).insert("lgroup", QChar(0x0029));
    (*SGXSingCorrectCore::database).insert("ulcorner", QChar(0x231C));
    (*SGXSingCorrectCore::database).insert("urcorner", QChar(0x231D));
    (*SGXSingCorrectCore::database).insert("llcorner", QChar(0x231E));
    (*SGXSingCorrectCore::database).insert("lrcorner", QChar(0x231F));
    (*SGXSingCorrectCore::database).insert("llbracket", QChar(0x27E6));
    (*SGXSingCorrectCore::database).insert("rrbracket", QChar(0x27E7));
    (*SGXSingCorrectCore::database).insert("uparrow", QChar(0x2191));
    (*SGXSingCorrectCore::database).insert("downarrow", QChar(0x2193));
    (*SGXSingCorrectCore::database).insert("updownarrow", QChar(0x2195));
    (*SGXSingCorrectCore::database).insert("Uparrow", QChar(0x21D1));
    (*SGXSingCorrectCore::database).insert("Downarrow", QChar(0x21D3));
    (*SGXSingCorrectCore::database).insert("Updownarrow", QChar(0x21D5));
    (*SGXSingCorrectCore::database).insert("backslash", QChar(0x005C));
    (*SGXSingCorrectCore::database).insert("Alpha", QChar(0x0391));
    (*SGXSingCorrectCore::database).insert("Beta", QChar(0x0392));
    (*SGXSingCorrectCore::database).insert("Gamma", QChar(0x0393));
    (*SGXSingCorrectCore::database).insert("Delta", QChar(0x0394));
    (*SGXSingCorrectCore::database).insert("Epsilon", QChar(0x0395));
    (*SGXSingCorrectCore::database).insert("Zeta", QChar(0x0396));
    (*SGXSingCorrectCore::database).insert("Eta", QChar(0x0397));
    (*SGXSingCorrectCore::database).insert("Theta", QChar(0x0398));
    (*SGXSingCorrectCore::database).insert("Iota", QChar(0x0399));
    (*SGXSingCorrectCore::database).insert("Kappa", QChar(0x039A));
    (*SGXSingCorrectCore::database).insert("Lambda", QChar(0x039B));
    (*SGXSingCorrectCore::database).insert("Mu", QChar(0x039C));
    (*SGXSingCorrectCore::database).insert("Nu", QChar(0x039D));
    (*SGXSingCorrectCore::database).insert("Xi", QChar(0x039E));
    (*SGXSingCorrectCore::database).insert("Omicron", QChar(0x039F));
    (*SGXSingCorrectCore::database).insert("Pi", QChar(0x03A0));
    (*SGXSingCorrectCore::database).insert("Rho", QChar(0x03A1));
    (*SGXSingCorrectCore::database).insert("Sigma", QChar(0x03A3));
    (*SGXSingCorrectCore::database).insert("Tau", QChar(0x03A4));
    (*SGXSingCorrectCore::database).insert("Upsilon", QChar(0x03A5));
    (*SGXSingCorrectCore::database).insert("Phi", QChar(0x03A6));
    (*SGXSingCorrectCore::database).insert("Chi", QChar(0x03A7));
    (*SGXSingCorrectCore::database).insert("Psi", QChar(0x03A8));
    (*SGXSingCorrectCore::database).insert("Omega", QChar(0x03A9));
    (*SGXSingCorrectCore::database).insert("alpha", QChar(0x03B1));
    (*SGXSingCorrectCore::database).insert("beta", QChar(0x03B2));
    (*SGXSingCorrectCore::database).insert("gamma", QChar(0x03B3));
    (*SGXSingCorrectCore::database).insert("delta", QChar(0x03B4));
    (*SGXSingCorrectCore::database).insert("epsilon", QChar(0x03B5));
    (*SGXSingCorrectCore::database).insert("zeta", QChar(0x03B6));
    (*SGXSingCorrectCore::database).insert("eta", QChar(0x03B7));
    (*SGXSingCorrectCore::database).insert("theta", QChar(0x03B8));
    (*SGXSingCorrectCore::database).insert("iota", QChar(0x03B9));
    (*SGXSingCorrectCore::database).insert("kappa", QChar(0x03BA));
    (*SGXSingCorrectCore::database).insert("lambda", QChar(0x03BB));
    (*SGXSingCorrectCore::database).insert("mu", QChar(0x03BC));
    (*SGXSingCorrectCore::database).insert("nu", QChar(0x03BD));
    (*SGXSingCorrectCore::database).insert("xi", QChar(0x03BE));
    (*SGXSingCorrectCore::database).insert("omicron", QChar(0x03BF));
    (*SGXSingCorrectCore::database).insert("pi", QChar(0x03C0));
    (*SGXSingCorrectCore::database).insert("rho", QChar(0x03C1));
    (*SGXSingCorrectCore::database).insert("sigma", QChar(0x03C3));
    (*SGXSingCorrectCore::database).insert("tau", QChar(0x03C4));
    (*SGXSingCorrectCore::database).insert("upsilon", QChar(0x03C5));
    (*SGXSingCorrectCore::database).insert("phi", QChar(0x03C6));
    (*SGXSingCorrectCore::database).insert("chi", QChar(0x03C7));
    (*SGXSingCorrectCore::database).insert("psi", QChar(0x03C8));
    (*SGXSingCorrectCore::database).insert("omega", QChar(0x03C9));
    (*SGXSingCorrectCore::database).insert("aleph", QChar(0x2135));
    (*SGXSingCorrectCore::database).insert("alef", QChar(0x2135));
    (*SGXSingCorrectCore::database).insert("alefsym", QChar(0x2135));
    (*SGXSingCorrectCore::database).insert("beth", QChar(0x2136));
    (*SGXSingCorrectCore::database).insert("gimel", QChar(0x2137));
    (*SGXSingCorrectCore::database).insert("daleth", QChar(0x2138));
    (*SGXSingCorrectCore::database).insert("nabla", QChar(0x2207));
    (*SGXSingCorrectCore::database).insert("partial", QChar(0x2202));
    (*SGXSingCorrectCore::database).insert("cnums", QChar(0x2102));
    (*SGXSingCorrectCore::database).insert("Complex", QChar(0x2102));
    (*SGXSingCorrectCore::database).insert("ell", QChar(0x2113));
    (*SGXSingCorrectCore::database).insert("hbar", QChar(0x210F));
    (*SGXSingCorrectCore::database).insert("hslash", QChar(0x210F));
    (*SGXSingCorrectCore::database).insert("Im", QChar(0x2111));
    (*SGXSingCorrectCore::database).insert("image", QChar(0x2111));
    (*SGXSingCorrectCore::database).insert("N", QChar(0x2115));
    (*SGXSingCorrectCore::database).insert("natnums", QChar(0x2115));
    (*SGXSingCorrectCore::database).insert("R", QChar(0x211D));
    (*SGXSingCorrectCore::database).insert("Re", QChar(0x211C));
    (*SGXSingCorrectCore::database).insert("real", QChar(0x211C));
    (*SGXSingCorrectCore::database).insert("reals", QChar(0x211D));
    (*SGXSingCorrectCore::database).insert("Reals", QChar(0x211D));
    (*SGXSingCorrectCore::database).insert("wp", QChar(0x2118));
    (*SGXSingCorrectCore::database).insert("weierp", QChar(0x2118));
    (*SGXSingCorrectCore::database).insert("Z", QChar(0x2124));
    (*SGXSingCorrectCore::database).insert("o", QChar(0x2205));
    (*SGXSingCorrectCore::database).insert("O", QChar(0x2205));
    (*SGXSingCorrectCore::database).insert("forall", QChar(0x2200));
    (*SGXSingCorrectCore::database).insert("exists", QChar(0x2203));
    (*SGXSingCorrectCore::database).insert("exist", QChar(0x2203));
    (*SGXSingCorrectCore::database).insert("nexists", QChar(0x2204));
    (*SGXSingCorrectCore::database).insert("in", QChar(0x2208));
    (*SGXSingCorrectCore::database).insert("isin", QChar(0x2208));
    (*SGXSingCorrectCore::database).insert("notin", QChar(0x2209));
    (*SGXSingCorrectCore::database).insert("complement", QChar(0x2201));
    (*SGXSingCorrectCore::database).insert("subset", QChar(0x2282));
    (*SGXSingCorrectCore::database).insert("supset", QChar(0x2283));
    (*SGXSingCorrectCore::database).insert("mid", QChar(0x2223));
    (*SGXSingCorrectCore::database).insert("land", QChar(0x2227));
    (*SGXSingCorrectCore::database).insert("lor", QChar(0x2228));
    (*SGXSingCorrectCore::database).insert("ni", QChar(0x220B));
    (*SGXSingCorrectCore::database).insert("therefore", QChar(0x2234));
    (*SGXSingCorrectCore::database).insert("because", QChar(0x2235));
    (*SGXSingCorrectCore::database).insert("mapsto", QChar(0x21A6));
    (*SGXSingCorrectCore::database).insert("to", QChar(0x2192));
    (*SGXSingCorrectCore::database).insert("gets", QChar(0x2190));
    (*SGXSingCorrectCore::database).insert("leftrightarrow", QChar(0x2194));
    (*SGXSingCorrectCore::database).insert("notni", QChar(0x220C));
    (*SGXSingCorrectCore::database).insert("emptyset", QChar(0x2205));
    (*SGXSingCorrectCore::database).insert("empty", QChar(0x2205));
    (*SGXSingCorrectCore::database).insert("varnothing", QChar(0x2205));
    (*SGXSingCorrectCore::database).insert("implies", QChar(0x21D2));
    (*SGXSingCorrectCore::database).insert("impliedby", QChar(0x21D0));
    (*SGXSingCorrectCore::database).insert("iff", QChar(0x21D4));
    (*SGXSingCorrectCore::database).insert("neg", QChar(0x00AC));
    (*SGXSingCorrectCore::database).insert("lnot", QChar(0x00AC));
    (*SGXSingCorrectCore::database).insert("sum", QChar(0x2211));
    (*SGXSingCorrectCore::database).insert("int", QChar(0x222B));
    (*SGXSingCorrectCore::database).insert("iint", QChar(0x222C));
    (*SGXSingCorrectCore::database).insert("iiint", QChar(0x222D));
    (*SGXSingCorrectCore::database).insert("oint", QChar(0x222E));
    (*SGXSingCorrectCore::database).insert("prod", QChar(0x220F));
    (*SGXSingCorrectCore::database).insert("coprod", QChar(0x2210));
    (*SGXSingCorrectCore::database).insert("intop", QChar(0x222B));
    (*SGXSingCorrectCore::database).insert("smallint", QChar(0x222B));
    (*SGXSingCorrectCore::database).insert("oiint", QChar(0x222F));
    (*SGXSingCorrectCore::database).insert("bigotimes", QChar(0x2297));
    (*SGXSingCorrectCore::database).insert("bigoplus", QChar(0x2295));
    (*SGXSingCorrectCore::database).insert("bigodot", QChar(0x2299));
    (*SGXSingCorrectCore::database).insert("biguplus", QChar(0x228E));
    (*SGXSingCorrectCore::database).insert("oiiint", QChar(0x2230));
    (*SGXSingCorrectCore::database).insert("bigvee", QChar(0x22C1));
    (*SGXSingCorrectCore::database).insert("bigwedge", QChar(0x22C0));
    (*SGXSingCorrectCore::database).insert("bigcap", QChar(0x22C2));
    (*SGXSingCorrectCore::database).insert("bigcup", QChar(0x22C3));
    (*SGXSingCorrectCore::database).insert("bigsqcup", QChar(0x2294));
    (*SGXSingCorrectCore::database).insert("plus", QChar(0x002B));
    (*SGXSingCorrectCore::database).insert("minus", QChar(0x002D));
    (*SGXSingCorrectCore::database).insert("slash", QChar(0x002F));
    (*SGXSingCorrectCore::database).insert("asterisk", QChar(0x002A));
    (*SGXSingCorrectCore::database).insert("And", QChar(0x0026));
    (*SGXSingCorrectCore::database).insert("ast", QChar(0x002A));
    (*SGXSingCorrectCore::database).insert("barwedge", QChar(0x22BC));
    (*SGXSingCorrectCore::database).insert("bigcirc", QChar(0x25CB));
    (*SGXSingCorrectCore::database).insert("boxdot", QChar(0x22A1));
    (*SGXSingCorrectCore::database).insert("boxminus", QChar(0x229F));
    (*SGXSingCorrectCore::database).insert("boxplus", QChar(0x229E));
    (*SGXSingCorrectCore::database).insert("boxtimes", QChar(0x22A0));
    (*SGXSingCorrectCore::database).insert("bullet", QChar(0x00B7));
    (*SGXSingCorrectCore::database).insert("Cap", QChar(0x22D2));
    (*SGXSingCorrectCore::database).insert("cap", QChar(0x2229));
    (*SGXSingCorrectCore::database).insert("cdot", QChar(0x00B7));
    (*SGXSingCorrectCore::database).insert("cdotp", QChar(0x00B7));
    (*SGXSingCorrectCore::database).insert("centerdot", QChar(0x00B7));
    (*SGXSingCorrectCore::database).insert("circ", QChar(0x2218));
    (*SGXSingCorrectCore::database).insert("circledast", QChar(0x229B));
    (*SGXSingCorrectCore::database).insert("circledcirc", QChar(0x229A));
    (*SGXSingCorrectCore::database).insert("circleddash", QChar(0x229D));
    (*SGXSingCorrectCore::database).insert("Cup", QChar(0x22D3));
    (*SGXSingCorrectCore::database).insert("cup", QChar(0x222A));
    (*SGXSingCorrectCore::database).insert("curlyvee", QChar(0x22CE));
    (*SGXSingCorrectCore::database).insert("curlywedge", QChar(0x22CF));
    (*SGXSingCorrectCore::database).insert("div", QChar(0x00F7));
    (*SGXSingCorrectCore::database).insert("divideontimes", QChar(0x22C7));
    (*SGXSingCorrectCore::database).insert("dotplus", QChar(0x2214));
    (*SGXSingCorrectCore::database).insert("doublebarwedge", QChar(0x2306));
    (*SGXSingCorrectCore::database).insert("doublecap", QChar(0x22D2));
    (*SGXSingCorrectCore::database).insert("doublecup", QChar(0x22D3));
    (*SGXSingCorrectCore::database).insert("gtrdot", QChar(0x22D7));
    (*SGXSingCorrectCore::database).insert("intercal", QChar(0x22BA));
    (*SGXSingCorrectCore::database).insert("land", QChar(0x2227));
    (*SGXSingCorrectCore::database).insert("leftthreetimes", QChar(0x22CB));
    (*SGXSingCorrectCore::database).insert("ldotp", QChar(0x00B7));
    (*SGXSingCorrectCore::database).insert("lor", QChar(0x2228));
    (*SGXSingCorrectCore::database).insert("lessdot", QChar(0x22D6));
    (*SGXSingCorrectCore::database).insert("lhd", QChar(0x22B2));
    (*SGXSingCorrectCore::database).insert("ltimes", QChar(0x22C9));
    (*SGXSingCorrectCore::database).insert("mp", QChar(0x2213));
    (*SGXSingCorrectCore::database).insert("odot", QChar(0x2299));
    (*SGXSingCorrectCore::database).insert("ominus", QChar(0x2296));
    (*SGXSingCorrectCore::database).insert("oplus", QChar(0x2295));
    (*SGXSingCorrectCore::database).insert("otimes", QChar(0x2297));
    (*SGXSingCorrectCore::database).insert("oslash", QChar(0x2298));
    (*SGXSingCorrectCore::database).insert("pm", QChar(0x00B1));
    (*SGXSingCorrectCore::database).insert("plusmn", QChar(0x00B1));
    (*SGXSingCorrectCore::database).insert("rhd", QChar(0x22B3));
    (*SGXSingCorrectCore::database).insert("rightthreetimes", QChar(0x22CC));
    (*SGXSingCorrectCore::database).insert("rtimes", QChar(0x22CA));
    (*SGXSingCorrectCore::database).insert("setminus", QChar(0x2216));
    (*SGXSingCorrectCore::database).insert("smallsetminus", QChar(0x2216));
    (*SGXSingCorrectCore::database).insert("sqcap", QChar(0x2293));
    (*SGXSingCorrectCore::database).insert("sqcup", QChar(0x2294));
    (*SGXSingCorrectCore::database).insert("times", QChar(0x00D7));
    (*SGXSingCorrectCore::database).insert("unlhd", QChar(0x22B4));
    (*SGXSingCorrectCore::database).insert("unrhd", QChar(0x22B5));
    (*SGXSingCorrectCore::database).insert("uplus", QChar(0x228E));
    (*SGXSingCorrectCore::database).insert("vee", QChar(0x2228));
    (*SGXSingCorrectCore::database).insert("veebar", QChar(0x22BB));
    (*SGXSingCorrectCore::database).insert("wedge", QChar(0x2227));
    (*SGXSingCorrectCore::database).insert("wr", QChar(0x2240));
    (*SGXSingCorrectCore::database).insert("sqrt", QChar(0x221A));
    (*SGXSingCorrectCore::database).insert("cbrt", QChar(0x221B));
    (*SGXSingCorrectCore::database).insert("squareroot", QChar(0x221A));
    (*SGXSingCorrectCore::database).insert("cuberoot", QChar(0x221B));
    (*SGXSingCorrectCore::database).insert("fourthroot", QChar(0x221C));
}

void SGXSingCorrectCore::terminate(){
    delete SGXSingCorrectCore::database;
    SGXSingCorrectCore::database = nullptr;
    delete SGXSingCorrectCore::instance;
}
