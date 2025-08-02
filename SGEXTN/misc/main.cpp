#include <QCoreApplication>
#include "sgxcentral.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include "../quickui/sgxquickuiinterface.h"
#include <QQuickStyle>
#include <QLocale>

int main(int argc, char** argv){ // NOLINT(misc-include-cleaner)
    QGuiApplication app(argc, argv); // NOLINT(misc-const-correctness)
    QLocale::setDefault(QLocale(QLocale::English, QLocale::Singapore));
    QQuickStyle::setStyle("Basic");
    QQmlApplicationEngine e;
    SGXQuickUIInterface::e = &e;
    SGXCentral::initialise();
    return QGuiApplication::exec();
}
