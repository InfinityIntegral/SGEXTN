#include <QApplication>
#include <QIcon>
#include <QCoreApplication>
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "sgxcentral.h"

int main(int argc, char** argv){ // NOLINT(misc-include-cleaner)
    QCoreApplication::setApplicationName(SGUCentralManagement::applicationName);
    QCoreApplication::setApplicationVersion(SGUCentralManagement::applicationVersion);
    QCoreApplication::setOrganizationName("05524F.sg");
    QApplication app(argc, argv); // NOLINT(misc-const-correctness)
    const QIcon temp_appicon(":/assets/05524Flogo.png");
    QApplication::setWindowIcon(temp_appicon);
    SGXCentral::initialise();
    return QApplication::exec();
}
