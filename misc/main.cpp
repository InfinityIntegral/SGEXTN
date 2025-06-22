#include <QCoreApplication>
#include "sgxcentral.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include "../quickui/sgxquickuiinterface.h"

int main(int argc, char** argv){ // NOLINT(misc-include-cleaner)
    QGuiApplication app(argc, argv); // NOLINT(misc-const-correctness)
    QQmlApplicationEngine e;
    SGXQuickUIInterface::e = &e;
    SGXCentral::initialise();
    return QGuiApplication::exec();
}
