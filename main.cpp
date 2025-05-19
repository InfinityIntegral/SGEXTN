#include <QApplication>
#include "sgcentralmanagement.h"

int main(int argc, char** argv){
    QCoreApplication::setApplicationName("app template");
    QCoreApplication::setApplicationVersion("1");
    QCoreApplication::setOrganizationName("05524F.sg");
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/05524Flogo.png"));
    SGCentralManagement::initialise();
    return app.exec();
}
