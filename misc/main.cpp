#include <QApplication>
#include <QIcon>
#include <QCoreApplication>

int main(int argc, char** argv){ // NOLINT
    QCoreApplication::setApplicationName("SGEXTN template app");
    QCoreApplication::setApplicationVersion("1");
    QCoreApplication::setOrganizationName("05524F.sg");
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/05524Flogo.png"));
    return app.exec();
}
