#ifndef SGUCENTRALMANAGEMENT_H
#define SGUCENTRALMANAGEMENT_H

#include <QObject>
#include <qtmetamacros.h>

class SGUCentralManagement : public QObject // non instantiable class for essential application data that should be define by the user, including application name, theme colours, custom initialisation and custom termination
{
    Q_OBJECT
public:
    SGUCentralManagement() = delete;
    SGUCentralManagement(const SGUCentralManagement&) = delete;
    SGUCentralManagement(SGUCentralManagement&&) = delete;
    SGUCentralManagement& operator=(const SGUCentralManagement&) = delete;
    SGUCentralManagement& operator=(SGUCentralManagement&&) = delete;
    ~SGUCentralManagement() override = default;
    static void initialise(); // initialisation function run when app opens
    static void terminate(); // temination function run when app closes
    static QString applicationName; // name of application displayed
    static QString applicationVersion; // version number of application
};

#endif // SGUCENTRALMANAGEMENT_H
