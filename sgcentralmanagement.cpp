#include "sgcentralmanagement.h"
#include <QCoreApplication>
#include <QFontDatabase>
#include "sggenerallibrary.h"
#include "sgstatusbarmanagement.h"

QString SGCentralManagement::colour0 = "rgba(255, 255, 255, 0)";
QString SGCentralManagement::colour1 = "rgba(255, 0, 200, 255)";
QString SGCentralManagement::colour2 = "rgba(255, 255, 255, 255)";
QString SGCentralManagement::colour3 = "rgba(255, 128, 228, 255)";
float SGCentralManagement::screenw = 0.0f;
float SGCentralManagement::screenh = 0.0f;
float SGCentralManagement::renderw = 0.0f;
float SGCentralManagement::renderh = 0.0f;
float SGCentralManagement::sizeunit = 0.0f;
SGRootWindow* SGCentralManagement::rootwindow = nullptr;
SGSignalsEmitter* SGCentralManagement::signalsemitter = nullptr;
SGWidget000451103* SGCentralManagement::mainbackground = nullptr;

void SGCentralManagement::initialise(){
    connect(qApp, &QCoreApplication::aboutToQuit, &SGCentralManagement::terminate);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents);

    QList templist = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/SingScript.sg.otf"));
    SGGeneralLibrary::SingScriptSG = new QFont(templist.first());

    SGCentralManagement::signalsemitter = new SGSignalsEmitter();
    SGCentralManagement::rootwindow = new SGRootWindow();
    (*SGCentralManagement::rootwindow).updatescreensize();
    SGStatusBarManagement::initialisestatusbar();
    SGCentralManagement::mainbackground = new SGWidget000451103(SGCentralManagement::rootwindow, 0.0f, 1.0f, 1.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatescreen, SGCentralManagement::mainbackground, &SGWidget000451103::ResizeObj);
}

void SGCentralManagement::terminate(){
    delete SGCentralManagement::rootwindow;
    //delete SGGeneralLibrary::SingScriptSG;
}
