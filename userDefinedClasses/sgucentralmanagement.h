#ifndef SGUCENTRALMANAGEMENT_H
#define SGUCENTRALMANAGEMENT_H

#include <QObject>

class SGUCentralManagement : public QObject
{
    Q_OBJECT // NOLINT
public:
    SGUCentralManagement() = delete;
    SGUCentralManagement(const SGUCentralManagement&) = delete;
    SGUCentralManagement(SGUCentralManagement&&) = delete;
    SGUCentralManagement& operator=(const SGUCentralManagement&) = delete;
    SGUCentralManagement& operator=(SGUCentralManagement&&) = delete;
    ~SGUCentralManagement() override = default;
    static void initialise();
    static void terminate();
    static QString applicationName;
    static QString applicationVersion;
};

#endif // SGUCENTRALMANAGEMENT_H
