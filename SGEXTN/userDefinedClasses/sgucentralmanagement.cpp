#include "sgucentralmanagement.h"
#include "../primitives/sgxstring.h"
#include "../primitives/sgxcolourrgba.h"

// pls update README and license
// do not forget to replace the icons font file and app icon in assets.qrc based on the app, do not change their file paths though
// the icons font file can be of any type (otf, ttf, etc) that Qt support, but its name must be AppIcons.sg and the internal font family name must be AppIcons.sg

// name of your application
SGXString SGUCentralManagement::applicationName = "SGEXTN";
// version number of your application, does not have to be number
SGXString SGUCentralManagement::applicationVersion = "v5.1.0";
// name of your organisation
SGXString SGUCentralManagement::organisationName = "05524F.sg (Singapore)";
// name of root folder of your application, only use uppercase or lowercase letters, definitely no banned characters, no dots, no spaces, no hyphens, no underscores, avoid numbers, avoid non ASCII characters
SGXString SGUCentralManagement::rootFolderName = "SGEXTN";

// theme colours of your application
SGXColourRGBA SGUCentralManagement::themeColour0 = SGXColourRGBA(0, 0, 0);
SGXColourRGBA SGUCentralManagement::themeColour1 = SGXColourRGBA(64, 0, 50);
SGXColourRGBA SGUCentralManagement::themeColour2 = SGXColourRGBA(128, 0, 100);
SGXColourRGBA SGUCentralManagement::themeColour3 = SGXColourRGBA(191, 0, 150);
SGXColourRGBA SGUCentralManagement::themeColour4 = SGXColourRGBA(255, 0, 200);
SGXColourRGBA SGUCentralManagement::themeColour5 = SGXColourRGBA(255, 64, 214);
SGXColourRGBA SGUCentralManagement::themeColour6 = SGXColourRGBA(255, 128, 227);
SGXColourRGBA SGUCentralManagement::themeColour7 = SGXColourRGBA(255, 191, 241);
SGXColourRGBA SGUCentralManagement::themeColour8 = SGXColourRGBA(255, 255, 255);
#include "../containers/sglmap.h"
#include "../primitives/sgxstring.h"
#include "../containers/sgllesserthan.h"
#include <QDebug>
// this is run immediately after GUI is created, use it to initialise the UI
void SGUCentralManagement::initialise(){
    SGLMap<int, SGXString, SGLLesserThan<int>> s = SGLMap<int, SGXString, SGLLesserThan<int>>();
    qDebug() << s.length();
    s.insert(2, "two");
    qDebug() << s.length();
    s.insert(3, "three");
    qDebug() << s.length();
    s.insert(5, "five");
    qDebug() << s.length();
    s.insert(6, "six");
    qDebug() << s.length();
    s.insert(7, "seven");
    qDebug() << s.length();
    s.insert(11, "eleven");
    qDebug() << s.length();
    s.erase(6);
    qDebug() << s.length();
    qDebug() << "start";
    qDebug() << s.contains(1) << s.contains(6) << s.contains(11);
    qDebug() << (*s.lowerBound(4).value().data) << (*s.upperBound(4).value().data) << (*s.lowerBound(3).value().data) << (*s.upperBound(3).value().data);
    qDebug() << "start";
    for(SGLMap<int, SGXString, SGLLesserThan<int>>::ConstIterator i=s.constBegin(); i!=s.constEnd(); i++){qDebug() << i.key() << (*i.value().data);}
    qDebug() << "end";
    SGLMap<int, SGXString, SGLLesserThan<int>> t = s;
    qDebug() << s.length();
    qDebug() << "start";
    for(SGLMap<int, SGXString, SGLLesserThan<int>>::ConstIterator i=t.constBegin(); i!=t.constEnd(); i++){qDebug() << i.key() << (*i.value().data);}
    qDebug() << "start";
    for(SGLMap<int, SGXString, SGLLesserThan<int>>::Iterator i=t.begin(); i!=t.end(); i++){if(i.key() == 5 || i.key() == 11){t.erase(i);} else {qDebug() << i.key() << (*i.value().data);}}
    qDebug() << "A";
    for(SGLMap<int, SGXString, SGLLesserThan<int>>::ConstIterator i=t.constBegin(); i!=t.constEnd(); i++){qDebug() << i.key() << (*i.value().data);}
    SGLMap<int, SGXString, SGLLesserThan<int>> u;
    qDebug() << u.length() << u.contains(0);
    u = SGLMap<int, SGXString, SGLLesserThan<int>>(s);
    qDebug() << u.indexOf(-2) << u.indexOf(11) << u.indexOf(3);
    qDebug() << (*u.valueAt(0).data) << (*u.valueAt(u.length()-1).data);
    qDebug() << (*s.at(11).data);
    s.at(11) = "hi";
    for(SGLMap<int, SGXString, SGLLesserThan<int>>::ConstIterator i=s.constBegin(); i!=s.constEnd(); i++){qDebug() << i.key() << (*i.value().data);}
}

// this is run after the application is created but before the GUI, use it to edit theme colours from configuration files
// do not use anything GUI related in this function, they are not set up yet
void SGUCentralManagement::earlyInitialise(){

}

// this is run after builtin fonts are imported, use it to import other fonts
// use commands in the format
// QFontDatabase::addApplicationFont([path to your fonts in your assets folder]);
void SGUCentralManagement::initialiseExtraFonts(){

}

// this is run after builtin custom rendered widgets are registered with QML, use it to register your own custom rendering widgets
// use commands in the format
// qmlRegisterType<[type of custom widget]>([name of custom widget], 0, 0, [name of custom widget]);
void SGUCentralManagement::initialiseCustomRendering(){

}

// this is run before the application terminates, use it to save user data
void SGUCentralManagement::terminate(){

}
