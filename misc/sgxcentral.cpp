#include "sgxcentral.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QCoreApplication>
#include <QFontDatabase>
#include <QFont>
#include <QtCore/Qt>
#include <QList>
#include <memory>

std::unique_ptr<QFont> SGXCentral::standardFont = nullptr;
std::unique_ptr<QFont> SGXCentral::iconsFont = nullptr;

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
    
    SGUCentralManagement::initialise();
}

void SGXCentral::terminate(){
    SGUCentralManagement::terminate();
}
