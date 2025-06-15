#include <QApplication>
#include <QIcon>
#include <QCoreApplication>

int main(int argc, char** argv){ // NOLINT(misc-include-cleaner)
    QCoreApplication::setApplicationName("SGEXTN template app");
    QCoreApplication::setApplicationVersion("1");
    QCoreApplication::setOrganizationName("05524F.sg");
    QApplication app(argc, argv); // NOLINT(misc-const-correctness)
    const QIcon temp_appicon(":/assets/05524Flogo.png");
    QApplication::setWindowIcon(temp_appicon);
    return QApplication::exec();
}
