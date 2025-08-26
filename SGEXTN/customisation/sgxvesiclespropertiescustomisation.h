#ifndef SGXVESICLESPROPERTIESCUSTOMISATION_H
#define SGXVESICLESPROPERTIESCUSTOMISATION_H

#include <QObject>
#include <qtmetamacros.h>

class SGXVesiclesPropertiesCustomisation : public QObject
{
    Q_OBJECT
public:
    SGXVesiclesPropertiesCustomisation() = delete;
    static void loadVesicleProperties();
    static void syncVesicleProperties();
};

#endif // SGXVESICLESPROPERTIESCUSTOMISATION_H
