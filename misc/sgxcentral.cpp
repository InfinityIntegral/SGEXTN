#include "sgxcentral.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QCoreApplication>
#include <QFontDatabase>
#include <QFont>
#include <QtCore/Qt>
#include <QList>
#include "../widgets/sgxrootwidget.h"
#include "../userDefinedClasses/sgusignalemitter.h"
#include "../primitives/sgxcolourrgba.h"
#include "../widgets/sgxparentwidget.h"
#include <QColor>

QFont* SGXCentral::standardFont = nullptr;
QFont* SGXCentral::iconsFont = nullptr;
SGUSignalEmitter* SGXCentral::signalEmitter = nullptr;
float SGXCentral::applicationWindowWidth = 0.0f;
float SGXCentral::applicationWindowHeight = 0.0f;
float SGXCentral::renderAreaWidth = 0.0f;
float SGXCentral::renderAreaHeight = 0.0f;
float SGXCentral::sizeUnit = 0.0f;
SGXRootWidget* SGXCentral::rootWindow = nullptr;
SGXColourRGBA SGXCentral::noColour = SGXColourRGBA(255, 255, 255, 0);
SGXParentWidget* SGXCentral::parentWindow = nullptr;
void SGXCentral::doNothing(){}

void SGXCentral::initialise(){
    connect(qApp, &QCoreApplication::aboutToQuit, &SGXCentral::terminate);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);
    {
        QList l = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/standard.otf"));
        SGXCentral::standardFont = new QFont(l.first()); // NOLINT(cppcoreguidelines-owning-memory)
        l = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/icons.otf"));
        SGXCentral::iconsFont = new QFont(l.first()); // NOLINT(cppcoreguidelines-owning-memory)
    }
    SGXCentral::signalEmitter = new SGUSignalEmitter(); // NOLINT(cppcoreguidelines-owning-memory)
    SGXCentral::rootWindow = new SGXRootWidget(); // NOLINT(cppcoreguidelines-owning-memory)
    SGXCentral::parentWindow = new SGXParentWidget(); // NOLINT(cppcoreguidelines-owning-memory)
    (*SGXCentral::rootWindow).checkScreenSizeUpdate();
    SGUCentralManagement::initialise();
}

void SGXCentral::terminate(){
    SGUCentralManagement::terminate();
    delete SGXCentral::rootWindow; // NOLINT(cppcoreguidelines-owning-memory)
    delete SGXCentral::signalEmitter; // NOLINT(cppcoreguidelines-owning-memory)
    delete SGXCentral::iconsFont; // NOLINT(cppcoreguidelines-owning-memory)
    delete SGXCentral::standardFont; // NOLINT(cppcoreguidelines-owning-memory)
}

QColor SGXCentral::getThemeColourAsQColour(int themeColourIndex, SGXColourRGBA defaultColour){
    if(themeColourIndex == 0){return SGUCentralManagement::themeColour0.getQColour();}
    if(themeColourIndex == 1){return SGUCentralManagement::themeColour1.getQColour();}
    if(themeColourIndex == 2){return SGUCentralManagement::themeColour2.getQColour();}
    if(themeColourIndex == 3){return SGUCentralManagement::themeColour3.getQColour();}
    if(themeColourIndex == 4){return SGUCentralManagement::themeColour4.getQColour();}
    if(themeColourIndex == 5){return SGUCentralManagement::themeColour5.getQColour();}
    if(themeColourIndex == 6){return SGUCentralManagement::themeColour6.getQColour();}
    if(themeColourIndex == 7){return SGUCentralManagement::themeColour7.getQColour();}
    if(themeColourIndex == 8){return SGUCentralManagement::themeColour8.getQColour();}
    return defaultColour.getQColour();
}
