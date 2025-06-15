#include "sgxcentral.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QCoreApplication>
#include <QFontDatabase>
#include <QFont>
#include <QtCore/Qt>
#include <QList>
#include <memory>
#include "../userDefinedClasses/sgusignalemitter.h"

std::unique_ptr<QFont> SGXCentral::standardFont = nullptr;
std::unique_ptr<QFont> SGXCentral::iconsFont = nullptr;
std::unique_ptr<SGUSignalEmitter> SGXCentral::signalEmitter = nullptr;

void SGXCentral::initialise(){
    connect(qApp, &QCoreApplication::aboutToQuit, &SGXCentral::terminate);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);
    {
        QList l = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/standard.otf"));
        SGXCentral::standardFont = std::make_unique<QFont>(l.first());
        l = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/icons.otf"));
        SGXCentral::iconsFont = std::make_unique<QFont>(l.first());
    }
    SGXCentral::signalEmitter = std::make_unique<SGUSignalEmitter>();
    SGUCentralManagement::initialise();
}

void SGXCentral::terminate(){
    SGUCentralManagement::terminate();
}
